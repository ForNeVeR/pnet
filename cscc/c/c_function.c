/*
 * c_function.c - Declare and output functions for the C language.
 *
 * Copyright (C) 2002  Southern Storm Software, Pty Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include <cscc/c/c_internal.h>
#include "il_dumpasm.h"

#ifdef	__cplusplus
extern	"C" {
#endif

/*
 * Variables that keep track of special features that are used in a function.
 */
static int numSetJmpRefs = 0;
static int currSetJmpRef = 0;
static unsigned markerVar = 0;
static unsigned valueVar = 0;

/*
 * Report an error that resulted from the compiler trying to
 * infer the prototype of a forwardly-declared function, but
 * failing to do so correctly.
 */
static void ReportInferError(ILGenInfo *info, ILNode *node,
							 char *name, ILType *signature)
{
	char *typeName;
	unsigned long numParams;
	unsigned long param;
	int needComma;

	/* Print the start of the error message */
	fputs(yygetfilename(node), stderr);
	fprintf(stderr, ":%ld: ", yygetlinenum(node));
	fputs(_("previously inferred prototype was `"), stderr);

	/* Print the return type */
	typeName = CTypeToName(info, ILTypeGetReturnWithPrefixes(signature));
	fputs(typeName, stderr);
	ILFree(typeName);

	/* Print the function name */
	fprintf(stderr, " %s(", name);

	/* Print the function parameter types */
	numParams = ILTypeNumParams(signature);
	needComma = 0;
	for(param = 1; param <= numParams; ++param)
	{
		if(needComma)
		{
			fputs(", ", stderr);
		}
		else
		{
			needComma = 1;
		}
		typeName = CTypeToName
			(info, ILTypeGetParamWithPrefixes(signature, param));
		fputs(typeName, stderr);
		ILFree(typeName);
	}

	/* Print the elipsis argument or "void" for no parameters */
	if((ILType_CallConv(signature) & IL_META_CALLCONV_MASK)
				== IL_META_CALLCONV_VARARG)
	{
		if(needComma)
		{
			fputs(", ...", stderr);
		}
		else
		{
			fputs("...", stderr);
		}
	}
	else if(!needComma)
	{
		fputs("void", stderr);
	}

	/* Terminate the error message */
	fputs(")'\n", stderr);
}

ILMethod *CFunctionCreate(ILGenInfo *info, char *name, ILNode *node,
						  CDeclSpec spec, CDeclarator decl,
						  ILNode *declaredParams)
{
	ILMethod *method;
	void *data;
	ILNode *prevNode = 0;
	char newName[64];
	ILType *signature;
	ILType *checkForward = 0;
	ILUInt32 attrs = IL_META_METHODDEF_STATIC | IL_META_METHODDEF_PUBLIC;

	/* Set the "extern" vs "static" attributes for the method */
	attrs = IL_META_METHODDEF_STATIC;
	if((spec.specifiers & C_SPEC_STATIC) != 0)
	{
		attrs |= IL_META_METHODDEF_PRIVATE;
	}
	else
	{
		attrs |= IL_META_METHODDEF_PUBLIC;
	}

	/* See if we already have a definition for this name */
	data = CScopeLookup(name);
	if(data)
	{
		if(CScopeGetKind(data) == C_SCDATA_FUNCTION_FORWARD)
		{
			/* Process a forward declaration from an "extern" declaration */
			checkForward = CScopeGetType(data);
			prevNode = CScopeGetNode(data);
		}
		else if(CScopeGetKind(data) == C_SCDATA_FUNCTION_INFERRED)
		{
			/* Process a forward declaration from an inferred prototype */
			checkForward = CScopeGetType(data);
			prevNode = 0;
		}
		else
		{
			/* Report an error for the function redefinition */
			CCErrorOnLine(yygetfilename(node), yygetlinenum(node),
						  _("redefinition of `%s'"), name);
			prevNode = CScopeGetNode(data);
			if(prevNode)
			{
				CCErrorOnLine(yygetfilename(node), yygetlinenum(node),
							  _("`%s' previously defined here"), name);
			}

			/* Generate a new name to be used from now on */
			sprintf(newName, "function(%lu)",
					ILImageNumTokens
						(info->image, IL_META_TOKEN_METHOD_DEF) + 1);
			name = newName;
		}
	}

	/* Create a new method block for the function */
	method = ILMethodCreate
		(ILClass_FromToken(info->image, IL_META_TOKEN_TYPE_DEF | 1),
		 0, name, attrs);
	if(!method)
	{
		ILGenOutOfMemory(info);
	}

	/* Finalize the declarator and get the method signature */
	signature = CDeclFinalize(info, spec, decl, declaredParams, method);

	/* Update the scope with the required information */
	if(checkForward != 0)
	{
		/* Check that the re-declaration matches the forward declaration */
		if(!ILTypeIdentical(signature, checkForward))
		{
			CCErrorOnLine(yygetfilename(node), yygetlinenum(node),
						  _("conflicting types for `%s'"), name);
			if(prevNode)
			{
				CCErrorOnLine(yygetfilename(prevNode), yygetlinenum(prevNode),
							  _("previous declaration of `%s'"), name);
			}
			else
			{
				ReportInferError(info, node, name, checkForward);
			}
		}

		/* Update the scope data item with the actual information */
		CScopeUpdateFunction(data, node, signature);
	}
	else
	{
		/* Add a new entry to the scope */
		CScopeAddFunction(name, node, signature);
	}

	/* The method block is ready to go */
	return method;
}

void CFunctionDeclareParams(ILGenInfo *info, ILMethod *method)
{
	ILType *signature = ILMethod_Signature(method);
	ILParameter *param;
	const char *name;

	/* Scan the parameter information blocks for the method */
	param = 0;
	while((param = ILMethodNextParam(method, param)) != 0)
	{
		name = ILParameter_Name(param);
		if(name)
		{
			/* Declare this parameter into the scope with the given index */
			CScopeAddParam(name, (unsigned)(ILParameter_Num(param) - 1),
						   ILTypeGetParamWithPrefixes
						   		(signature, ILParameter_Num(param)));
		}
	}
}

void CFunctionOutput(ILGenInfo *info, ILMethod *method, ILNode *body)
{
	FILE *stream = info->asmOutput;
	unsigned indexVar = 0;
	unsigned exceptVar = 0;
	ILLabel label = ILLabel_Undefined;
	ILType *signature = ILMethod_Signature(method);
	ILMachineType returnMachineType;
	int index, outputLabel;

	/* Set up the code generation state for this function */
	numSetJmpRefs = 0;
	currSetJmpRef = 0;

	/* Perform semantic analysis on the function body */
	info->currentScope = CCurrentScope;
	if(body != 0)
	{
		ILNode_CSemAnalysis(body, info, &body, 1);
	}
	info->currentScope = CGlobalScope;

	/* Bail out if we don't have an assembly stream */
	if(!stream)
	{
		return;
	}

	/* Output the function header */
	fputs(".method ", stream);
	ILDumpFlags(stream, ILMethod_Attrs(method), ILMethodDefinitionFlags, 0);
	ILDumpMethodType(stream, info->image, signature,
					 IL_DUMP_QUOTE_NAMES, 0, ILMethod_Name(method), method);
	putc(' ', stream);
	ILDumpFlags(stream, ILMethod_ImplAttrs(method),
	            ILMethodImplementationFlags, 0);
	fputs("\n{\n", stream);

	/* Output the attributes that are attached to the method */
	CGenOutputAttributes(info, stream, ILToProgramItem(method));

	/* Notify the code generator as to what the return type is */
	info->returnType = ILTypeGetReturn(signature);
	returnMachineType = ILTypeToMachineType(info->returnType);

	/* Create the "setjmp" header if necessary */
	if(numSetJmpRefs > 0)
	{
		/* Get temporary variables to hold the values that we need:

		   marker - base of the marker range for this call frame.
		   index  - index of the marker which activated, or -1 on entry.
		   value  - the "longjmp" value that was thrown to us.
		   except - temporary storage for the "LongJmpException" object.
		*/
		markerVar = ILGenTempTypedVar(info, ILType_Int32);
		indexVar = ILGenTempTypedVar(info, ILType_Int32);
		valueVar = ILGenTempTypedVar(info, ILType_Int32);
		exceptVar = ILGenTempTypedVar
			(info, ILFindNonSystemType(info, "LongJmpException",
									   "OpenSystem.Languages.C"));

		/* Initialize the setjmp control variables */
		ILGenInt32(info, (ILInt32)numSetJmpRefs);
		fputs("\tcall\tint32 'OpenSystem.Languages.C'.'LongJmpException'"
					"::'GetMarkers'(int32)\n", stream);
		ILGenStoreLocal(info, markerVar);
		ILGenSimple(info, IL_OP_LDC_I4_M1);
		ILGenStoreLocal(info, indexVar);
		ILGenSimple(info, IL_OP_LDC_I4_0);
		ILGenStoreLocal(info, valueVar);
		ILGenExtend(info, 1);

		/* Output the setjmp restart label.  The exception handler
		   jumps here when a "longjmp" is detected with the index
		   set to indicate which "setjmp" should be re-activated */
		fputs("Lrestart:\n", stream);

		/* Wrap the rest of the function code in an exception block */
		fputs(".try {\n", stream);

		/* Generate code to check which "setjmp" in the function
		   triggered us to restart execution of the function */
		for(index = 0; index < numSetJmpRefs; ++index)
		{
			ILGenLoadLocal(info, indexVar);
			ILGenInt32(info, (ILInt32)index);
			fprintf(stream, "\tbeq\tLsetjmp%d\n", index);
		}
		ILGenExtend(info, 2);

		/* Tell the code generator to enter a "try" context so that
		   it will cause all "return" sequences to jump to the end
		   of the method before doing the actual return */
		ILGenPushTry(info);
	}

	/* Generate code for the function body */
	if(body != 0)
	{
		ILNode_GenDiscard(body, info);
	}

	/* Create the "setjmp" footer if necessary */
	if(numSetJmpRefs > 0)
	{
		/* Generate a fake return statement to force the function to jump
		   to the end of the method if control reaches here */
		if(!ILNodeEndsInReturn(body))
		{
			ILNode *node = ILNode_Return_create();
			ILNode_GenDiscard(node, info);
		}

		/* Output the start of the catch block for "LongJmpException" */
		fputs("} catch 'OpenSystem.Languages.C'.'LongJmpException' {\n",
			  stream);

		/* Store the exception reference */
		ILGenExtend(info, 1);
		ILGenStoreLocal(info, exceptVar);

		/* Get the "Marker" value from the "LongJmpException" object,
		   and subtract our local "marker" reference from it */
		ILGenLoadLocal(info, exceptVar);
		fputs("\tcall\tinstance int32 'OpenSystem.Languages.C'."
					"'LongJmpException'::get_Marker()\n", stream);
		ILGenLoadLocal(info, markerVar);
		ILGenAdjust(info, 2);
		ILGenSimple(info, IL_OP_SUB);
		ILGenStoreLocal(info, indexVar);
		ILGenAdjust(info, -2);

		/* Determine if "index" is in range for this call frame */
		ILGenLoadLocal(info, indexVar);
		ILGenInt32(info, (ILInt32)numSetJmpRefs);
		ILGenJump(info, IL_OP_BGE_UN, &label);

		/* Get the "Value" from the "LongJmpException" object and then
		   jump back to the top of the function to restart it */
		ILGenLoadLocal(info, exceptVar);
		fputs("\tcall\tinstance int32 'OpenSystem.Languages.C'."
					"'LongJmpException'::get_Value()\n", stream);
		ILGenStoreLocal(info, valueVar);
		fputs("\tleave\tLrestart\n", stream);

		/* Re-throw the "LongJmpException" object because it isn't ours */
		ILGenLabel(info, &label);
		ILGenSimple(info, IL_OP_PREFIX + IL_PREFIX_OP_RETHROW);

		/* Output the end of the catch block */
		fputs("}\n", stream);

		/* Exit the try context */
		ILGenPopTry(info);
	}

	/* Add an explicit return instruction if the body didn't */
	outputLabel = 0;
	if(!ILNodeEndsInReturn(body))
	{
		if(info->returnLabel != ILLabel_Undefined &&
		   info->returnType == ILType_Void)
		{
			/* Use this point in the code for return labels
			   to prevent outputting two "ret"'s in a row */
			ILGenLabel(info, &(info->returnLabel));
			outputLabel = 1;
		}
		ILGenCast(info, ILMachineType_Void, returnMachineType);
		ILGenSimple(info, IL_OP_RET);
		if(info->returnType != ILType_Void)
		{
			ILGenAdjust(info, -1);
		}
	}

	/* If we have a return label, we need to output some final
	   code to return the contents of a temporary local variable.
	   This is used when returning from inside a "try" block */
	if(!outputLabel && info->returnLabel != ILLabel_Undefined)
	{
		ILGenLabel(info, &(info->returnLabel));
		if(info->returnType != ILType_Void)
		{
			ILGenLoadLocal(info, info->returnVar);
			ILGenExtend(info, 1);
		}
		ILGenSimple(info, IL_OP_RET);
	}

	/* Output the function footer */
	fprintf(stream, "} // method %s\n", ILMethod_Name(method));

	/* Clean up temporary state that was used for code generation */
	ILGenEndMethod(info);
}

void CFunctionPredeclare(ILGenInfo *info)
{
	ILType *signature;
	ILType *type;

	/* Bail out if the "-fno-builtin" option was supplied */
	if(CCStringListContainsInv
			(extension_flags, num_extension_flags, "builtin"))
	{
		return;
	}

	/* Build the signature "int (*)(const char *, ...)" */
	signature = ILTypeCreateMethod(info->context, ILType_Int32);
	if(!signature)
	{
		ILGenOutOfMemory(info);
	}
	ILTypeSetCallConv(signature, IL_META_CALLCONV_VARARG);
	type = CTypeCreatePointer(info, CTypeAddConst(info, ILType_Int8), 0);
	if(!ILTypeAddParam(info->context, signature, type))
	{
		ILGenOutOfMemory(info);
	}

	/* Declare the inferred definitions of "printf" and "scanf" */
	CScopeAddInferredFunction("printf", signature);
	CScopeAddInferredFunction("scanf", signature);
}

ILType *CFunctionNaturalType(ILGenInfo *info, ILType *type, int vararg)
{
	if(ILType_IsPrimitive(type))
	{
		/* We pass unsigned types as their signed counterparts in
		   vararg mode, to get around cast issues in "refanyval" */
		switch(ILType_ToElement(type))
		{
			case IL_META_ELEMTYPE_I1:
			case IL_META_ELEMTYPE_U1:
			case IL_META_ELEMTYPE_I2:
			case IL_META_ELEMTYPE_U2:
			case IL_META_ELEMTYPE_CHAR:		return ILType_Int32;

			case IL_META_ELEMTYPE_U4:
			{
				if(vararg)
				{
					return ILType_Int32;
				}
				else
				{
					return ILType_UInt32;
				}
			}
			/* Not reached */

			case IL_META_ELEMTYPE_U8:
			{
				if(vararg)
				{
					return ILType_Int64;
				}
				else
				{
					return ILType_UInt64;
				}
			}
			/* Not reached */

			case IL_META_ELEMTYPE_U:
			{
				if(vararg)
				{
					return ILType_Int;
				}
				else
				{
					return ILType_UInt;
				}
			}
			/* Not reached */

			case IL_META_ELEMTYPE_R4:		return ILType_Float64;
		}
	}
	else if(type != 0 && ILType_IsComplex(type))
	{
		if(ILType_Kind(type) == IL_TYPE_COMPLEX_PTR || ILType_IsMethod(type))
		{
			/* Pointers are passed as "native int" in vararg mode to
			   get around cast issues in the "refanyval" instruction */
			if(vararg)
			{
				return ILType_Int;
			}
		}
		else if(ILType_Kind(type) == IL_TYPE_COMPLEX_CMOD_OPT ||
				ILType_Kind(type) == IL_TYPE_COMPLEX_CMOD_REQD)
		{
			return CFunctionNaturalType
				(info, type->un.modifier__.type__, vararg);
		}
	}
	else if(ILTypeIsEnum(type))
	{
		/* Enumerated values are passed as "int32" in vararg mode to
		   get around cast issues in the "refanyval" instruction */
		if(vararg)
		{
			return ILType_Int32;
		}
	}
	return type;
}

void CFunctionSawSetJmp(void)
{
	++numSetJmpRefs;
}

void CGenSetJmp(ILGenInfo *info)
{
	ILLabel label = ILLabel_Undefined;

	/* Get the marker value for this particular "setjmp" point */
	ILGenLoadLocal(info, markerVar);
	ILGenAdjust(info, 1);
	if(currSetJmpRef > 0)
	{
		ILGenInt32(info, (ILInt32)currSetJmpRef);
		ILGenSimple(info, IL_OP_ADD);
		ILGenExtend(info, 1);
	}

	/* Store the marker value into the "jmp_buf" array */
	ILGenSimple(info, IL_OP_STIND_I4);
	ILGenAdjust(info, -2);

	/* Push zero onto the stack and jump past the following code */
	ILGenSimple(info, IL_OP_LDC_I4_0);
	ILGenJump(info, IL_OP_BR, &label);

	/* Output the "setjmp" label.  The code at the top of the
	   function jumps here when a "longjmp" is detected */
	if(info->asmOutput)
	{
		fprintf(info->asmOutput, "Lsetjmp%d:\n", currSetJmpRef);
	}

	/* Load the "longjmp" value onto the stack */
	ILGenLoadLocal(info, valueVar);
	ILGenAdjust(info, 1);

	/* Mark the end of the "setjmp" handling code */
	ILGenLabel(info, &label);

	/* Advance the index for the next "setjmp" point in this function */
	++currSetJmpRef;
}

#ifdef	__cplusplus
};
#endif