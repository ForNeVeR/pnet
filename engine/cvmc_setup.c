/*
 * cvmc_setup.c - Coder implementation for CVM method entry setup.
 *
 * Copyright (C) 2001  Southern Storm Software, Pty Ltd.
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

#ifdef IL_CVMC_CODE

/*
 * Allocate enough space for "n" arguments.
 */
#define	ALLOC_ARGS(n)	\
			do { \
				ILUInt32 temp = (ILUInt32)(((n) + 7) & ~7); \
				if(temp > coder->maxArgs) \
				{ \
					ILUInt32 *newArgs = \
						(ILUInt32 *)ILRealloc(coder->argOffsets, \
											  temp * sizeof(ILUInt32)); \
					if(!newArgs) \
					{ \
						return 0; \
					} \
					coder->argOffsets = newArgs; \
					coder->maxArgs = temp; \
				} \
			} while (0)

/*
 * Allocate enough space for "n" locals.
 */
#define	ALLOC_LOCALS(n)	\
			do { \
				ILUInt32 temp = (ILUInt32)(((n) + 7) & ~7); \
				if(temp > coder->maxLocals) \
				{ \
					ILUInt32 *newLocals = \
						(ILUInt32 *)ILRealloc(coder->localOffsets, \
											  temp * sizeof(ILUInt32)); \
					if(!newLocals) \
					{ \
						return 0; \
					} \
					coder->localOffsets = newLocals; \
					coder->maxLocals = temp; \
				} \
			} while (0)

/*
 * Output the entry point code to fix up the arguments
 * and allocate the local variables.
 */
static int CVMEntryPoint(ILCVMCoder *coder, unsigned char **start,
						 ILMethod *method, ILStandAloneSig *localVarSig,
						 ILType *returnType, int isConstructor,
						 int isExtern, int suppressThis)
{
	ILUInt32 offset;
	ILUInt32 maxArgOffset;
	ILUInt32 num;
	ILUInt32 current;
	ILUInt32 argIndex;
	ILUInt32 extraLocals;
	ILType *signature;
	ILType *type;
	unsigned long pushDown;

	/* Set the current method */
	coder->currentMethod = method;

	/* Clear the label pool */
	ILMemPoolClear(&(coder->labelPool));
	coder->labelList = 0;
	coder->labelOutOfMemory = 0;

	/* Determine where the new method will start output within the buffer */
	if(coder->posn >= coder->len)
	{
		/* Flush the current contents of the method buffer */
		coder->posn = 0;
		coder->start = 0;
		++(coder->generation);
	}
	else
	{
		coder->start = coder->posn;
	}

	/* If this method is a constructor, then we need to output
	   some extra entry point code just before the main entry */
	if(isConstructor)
	{
		CVM_BYTE(COP_NEW);
		CVM_BYTE(COP_PUSHDOWN);
		pushDown = coder->posn;
		CVM_WORD(0);
		coder->start = coder->posn;
	}
	else
	{
		pushDown = 0;
	}

	/* Return the start of the method code to the caller */
	*start = coder->buffer + coder->start;

	/* Allocate offsets for the arguments */
	signature = ILMethod_Signature(method);
	num = ILTypeNumParams(signature);
	if(ILType_HasThis(signature) && !suppressThis)
	{
		/* Allocate an argument slot for the "this" parameter */
		ALLOC_ARGS(num + 1);
		coder->argOffsets[0] = 0;
		argIndex = 1;
		offset = 1;
	}
	else
	{
		/* No "this" parameter, or it is explicitly provided in the
		   signature, or this is an allocating constructor which must
		   create its own "this" parameter during execution */
		ALLOC_ARGS(num);
		argIndex = 0;
		offset = 0;
	}
	extraLocals = 0;
	for(current = 1; current <= num; ++current)
	{
		type = ILTypeGetEnumType(ILTypeGetParam(signature, current));
		coder->argOffsets[argIndex++] = offset;
		if(type == ILType_Float32 || type == ILType_Float64)
		{
			offset += CVM_WORDS_PER_NATIVE_FLOAT;
		}
		else
		{
			offset += GetTypeSize(type);

			/* We need an extra local to pass value types
			   by pointer to native methods */
			if(ILType_IsValueType(type))
			{
				++extraLocals;
			}
		}
	}
	maxArgOffset = offset;

	/* We need an extra local to pass return value types
	   by pointer to native methods */
	if(returnType && ILType_IsValueType(returnType))
	{
		++extraLocals;
	}

	/* Set the number of arguments, which initialize's the method's frame */
	CVM_WIDE(COP_SET_NUM_ARGS, offset);

	/* Is this a static constructor? */
	if(ILMethod_IsStaticConstructor(method))
	{
		/* Output a "cctor_once" instruction to ensure that this
		   method's body can only be executed once */
		CVM_BYTE(COP_CCTOR_ONCE);
	}

	/* If this is a constructor, then back-patch the push down size,
	   which is one less than the number of argument words */
	if(isConstructor)
	{
		--offset;
		coder->buffer[pushDown]     = (unsigned char)(offset);
		coder->buffer[pushDown + 1] = (unsigned char)(offset >> 8);
		coder->buffer[pushDown + 2] = (unsigned char)(offset >> 16);
		coder->buffer[pushDown + 3] = (unsigned char)(offset >> 24);
		++offset;
	}

	/* Fix up any arguments that are larger than their true types */
	if(ILType_HasThis(signature) && !suppressThis)
	{
		/* Allocate an argument slot for the "this" parameter */
		argIndex = 1;
	}
	else
	{
		/* No "this" parameter, or it is explicitly provided in the signature */
		argIndex = 0;
	}
	for(current = 1; current <= num; ++current)
	{
		type = ILTypeGetEnumType(ILTypeGetParam(signature, current));
		offset = coder->argOffsets[argIndex++];
		switch((unsigned long)type)
		{
		#ifndef CVM_X86		/* Not needed for 32-bit little-endian machines */
			case (unsigned long)ILType_Boolean:
			case (unsigned long)ILType_Int8:
			case (unsigned long)ILType_UInt8:
			{
				CVM_WIDE(COP_BFIXUP, offset);
			}
			break;

			case (unsigned long)ILType_Int16:
			case (unsigned long)ILType_UInt16:
			case (unsigned long)ILType_Char:
			{
				CVM_WIDE(COP_SFIXUP, offset);
			}
			break;
		#endif

			case (unsigned long)ILType_Float32:
			{
				CVM_WIDE(COP_FFIXUP, offset);
			}
			break;

			case (unsigned long)ILType_Float64:
			{
				CVM_WIDE(COP_DFIXUP, offset);
			}
			break;

			default: break;
		}
	}

	/* Allocate offsets for the local variables */
	offset = maxArgOffset;
	if(localVarSig)
	{
		signature = ILStandAloneSigGetType(localVarSig);
		num = ILTypeNumLocals(signature);
		ALLOC_LOCALS(num);
		for(current = 0; current < num; ++current)
		{
			type = ILTypeGetLocal(signature, current);
			coder->localOffsets[current] = offset;
			offset += GetTypeSize(type);
		}
	}
	else if(isExtern)
	{
		/* Allocate locals for external native methods */
		if(returnType)
		{
			/* We need a temporary local for the return value,
			   plus temporary locals for the value type arguments */
			ALLOC_LOCALS(1 + extraLocals);
			coder->localOffsets[0] = offset;
			offset += GetTypeSize(returnType);
			for(current = 0; current < extraLocals; ++current)
			{
				coder->localOffsets[current + 1] = offset;
				++offset;
			}
		}
		else
		{
			/* We need temporary locals for the value type arguments */
			ALLOC_LOCALS(extraLocals);
			for(current = 0; current < extraLocals; ++current)
			{
				coder->localOffsets[current] = offset;
				++offset;
			}
		}
	}

	/* Output the stack height check instruction, which is fixed
	   up at the end of the method with the maximum height */
	coder->stackCheck = coder->posn;
	CVM_BYTE(COP_CKHEIGHT_N);
	CVM_BYTE(0);
	CVM_BYTE(0);
	CVM_BYTE(0);
	CVM_BYTE(0);

	/* Output CVM code to allocate space for the local variables */
	offset -= maxArgOffset;
	if(offset == 1)
	{
		CVM_BYTE(COP_MK_LOCAL_1);
	}
	else if(offset == 2)
	{
		CVM_BYTE(COP_MK_LOCAL_2);
	}
	else if(offset == 3)
	{
		CVM_BYTE(COP_MK_LOCAL_3);
	}
	else if(offset != 0)
	{
		CVM_WIDE(COP_MK_LOCAL_N, offset);
	}

	/* Set the current stack height */
	coder->height = (long)offset;
	coder->minHeight = (long)offset;
	coder->maxHeight = (long)offset;

	/* Done */
	return 1;
}

/*
 * Set up a CVM coder instance to process a specific method.
 */
static int CVMCoder_Setup(ILCoder *_coder, unsigned char **start,
						  ILMethod *method, ILMethodCode *code)
{
	return CVMEntryPoint((ILCVMCoder *)_coder, start, method,
						 code->localVarSig, 0,
						 ILMethod_IsConstructor(method), 0, 0);
}

/*
 * Determine if a type looks like "System.String".
 */
static int IsStringType(ILType *type)
{
	ILClass *classInfo;
	const char *namespace;
	ILImage *image;
	ILImage *systemImage;
	if(ILType_IsClass(type))
	{
		classInfo = ILClassResolve(ILType_ToClass(type));
		if(!strcmp(ILClass_Name(classInfo), "String"))
		{
			namespace = ILClass_Namespace(classInfo);
			if(namespace && !strcmp(namespace, "System"))
			{
				image = ILClassToImage(classInfo);
				systemImage = ILContextGetSystem(ILImageToContext(image));
				if(!systemImage || image == systemImage)
				{
					return 1;
				}
			}
		}
	}
	return 0;
}

/*
 * Determine if a type looks like a reference to "System.String".
 */
static int IsStringRefType(ILType *type)
{
	if(type != ILType_Invalid && ILType_IsComplex(type))
	{
		if(ILType_Kind(type) == IL_TYPE_COMPLEX_BYREF)
		{
			return IsStringType(ILType_Ref(type));
		}
	}
	return 0;
}

/*
 * Set up a CVM coder instance to process a specific external method.
 */
static int CVMCoder_SetupExtern(ILCoder *_coder, unsigned char **start,
								ILMethod *method, void *fn, void *cif,
								int isInternal)
{
	ILCVMCoder *coder = (ILCVMCoder *)_coder;
	ILType *signature = ILMethod_Signature(method);
	ILType *returnType = ILTypeGetReturn(signature);
	int numArgs;
	ILUInt32 param;
	ILUInt32 numParams;
	ILUInt32 extraLocals;
	int returnIsTop;
	ILType *tempType;
	ILPInvoke *pinv;
	ILUInt32 pinvAttrs;

	/* Output the entry point code */
	returnType = ILTypeGetEnumType(returnType);
	if(returnType == ILType_Void)
	{
		if(!CVMEntryPoint(coder, start, method, 0, (ILType *)0,
						  ILMethod_IsConstructor(method), 1, 0))
		{
			return 0;
		}
	}
	else
	{
		if(!CVMEntryPoint(coder, start, method, 0, returnType,
						  ILMethod_IsConstructor(method), 1, 0))
		{
			return 0;
		}
	}

	/* If this is a PInvoke call, then scan for string parameters
	   and convert them into "char *" buffers of some description */
	if(!isInternal)
	{
		pinv = ILPInvokeFind(method);
		if(pinv)
		{
			pinvAttrs = ILPInvoke_Attrs(pinv);
		}
		else
		{
			pinvAttrs = 0;
		}
		numParams = ILTypeNumParams(signature);
		for(param = 1; param <= numParams; ++param)
		{
			if(ILType_HasThis(signature))
			{
				extraLocals = param;
			}
			else
			{
				extraLocals = param - 1;
			}
			tempType = ILTypeGetParam(signature, param);
			if(IsStringType(tempType))
			{
				/* String value parameter: convert into a "const char *" */
				CVM_WIDE(COP_PLOAD, coder->argOffsets[extraLocals]);
				CVM_ADJUST(1);
				switch(pinvAttrs & IL_META_PINVOKE_CHAR_SET_MASK)
				{
					case IL_META_PINVOKE_CHAR_SET_NOT_SPEC:
					{
						CVM_BYTE(COP_PREFIX);
						CVM_BYTE(COP_PREFIX_STR2UTF8);
					}
					break;

					case IL_META_PINVOKE_CHAR_SET_ANSI:
					case IL_META_PINVOKE_CHAR_SET_AUTO:
					{
						CVM_BYTE(COP_PREFIX);
						CVM_BYTE(COP_PREFIX_STR2ANSI);
					}
					break;

					case IL_META_PINVOKE_CHAR_SET_UNICODE:
					{
						/* TODO: convert into a "const wchar_t *" value */
					}
					break;
				}
				CVM_WIDE(COP_PSTORE, coder->argOffsets[extraLocals]);
				CVM_ADJUST(-1);
			}
			else if(IsStringRefType(tempType))
			{
				/* String reference parameter: convert into a blank buffer */
				/* TODO */
			}
		}
	}

	/* Push the arguments for the call onto the stack */
	numArgs = -1;
	if(isInternal)
	{
		/* Push a pointer to the thread value */
		CVM_BYTE(COP_PUSH_THREAD);
		++numArgs;
	}
	extraLocals = 0;
	returnIsTop = 1;
	if(ILType_IsValueType(returnType))
	{
		/* Value type return pointers are pushed just after the thread */
		CVM_WIDE(COP_WADDR, coder->localOffsets[0]);
		CVM_ADJUST(1);
		CVM_WIDE(COP_PSTORE, coder->localOffsets[1]);
		CVM_ADJUST(-1);
		CVM_WIDE(COP_WADDR_NATIVE_0 + numArgs, coder->localOffsets[1]);
		extraLocals = 2;
		++numArgs;
	}
	else if(returnType != ILType_Void)
	{
		++extraLocals;
	}
	if(ILType_HasThis(signature))
	{
		if(!ILMethod_IsVirtual(method))
		{
			/* This is a non-virtual instance method.  We need to check the
			   "this" argument for null before we push the pointer args.
			   This takes the burden off the underlying code to check for
			   null.  Virtual method calls check for null elsewhere */
			CVM_BYTE(COP_PLOAD_0);
			CVM_ADJUST(1);
			CVM_BYTE(COP_CKNULL);
			CVM_BYTE(COP_POP);
			CVM_ADJUST(-1);
		}
		numParams = ILTypeNumParams(signature);
		for(param = 0; param <= numParams; ++param)
		{
			if(param > 0 &&
			   ILType_IsValueType(ILTypeGetEnumType
			   		(ILTypeGetParam(signature, param))))
			{
				CVM_WIDE(COP_WADDR, coder->argOffsets[param]);
				CVM_ADJUST(1);
				CVM_WIDE(COP_PSTORE, coder->localOffsets[extraLocals]);
				CVM_ADJUST(-1);
				CVM_WIDE(COP_WADDR_NATIVE_0 + numArgs,
						 coder->localOffsets[extraLocals]);
				++extraLocals;
				returnIsTop = 0;
			}
			else
			{
				CVM_WIDE(COP_WADDR_NATIVE_0 + numArgs,
						 coder->argOffsets[param]);
			}
			++numArgs;
		}
	}
	else
	{
		/* This method does not have a "this" pointer */
		numParams = ILTypeNumParams(signature);
		for(param = 0; param < numParams; ++param)
		{
			if(ILType_IsValueType(ILTypeGetEnumType
			   		(ILTypeGetParam(signature, param + 1))))
			{
				CVM_WIDE(COP_WADDR, coder->argOffsets[param]);
				CVM_ADJUST(1);
				CVM_WIDE(COP_PSTORE, coder->localOffsets[extraLocals]);
				CVM_ADJUST(-1);
				CVM_WIDE(COP_WADDR_NATIVE_0 + numArgs,
						 coder->localOffsets[extraLocals]);
				++extraLocals;
				returnIsTop = 0;
			}
			else
			{
				CVM_WIDE(COP_WADDR_NATIVE_0 + numArgs,
						 coder->argOffsets[param]);
			}
			++numArgs;
		}
	}

	/* If "numArgs" has overflowed, then abort */
	if(numArgs > CVM_MAX_NATIVE_ARGS)
	{
		fputs("Native argument stack has overflowed.  Aborting.", stderr);
		exit(1);
	}

	/* Output the call to the external method */
	if(returnType != ILType_Void && !ILType_IsValueType(returnType))
	{
		/* Push a pointer to the local containing the return value */
		CVM_WIDE(COP_WADDR, coder->localOffsets[0]);
		CVM_ADJUST(1);

		/* Call the native method */
		CVM_BYTE(COP_CALL_NATIVE);
		CVM_PTR(fn);
		CVM_PTR(cif);
		CVM_ADJUST(-1);
	}
	else
	{
		/* Call the native method, with no return value */
		CVM_BYTE(COP_CALL_NATIVE_VOID);
		CVM_PTR(fn);
		CVM_PTR(cif);
	}

	/* Push the return value onto the stack and exit the method.
	   We can usually take a short-cut and assume that the top
	   of the stack is the local containing the return value,
	   and that a simple return will do the right thing */
	if(returnType != ILType_Void)
	{
		switch((unsigned long)returnType)
		{
			case (unsigned long)ILType_Boolean:
			case (unsigned long)ILType_Int8:
			{
				CVM_WIDE(COP_WADDR, coder->localOffsets[0]);
				CVM_ADJUST(1);
				CVM_BYTE(COP_BREAD);
				CVM_BYTE(COP_RETURN_1);
				CVM_ADJUST(-1);
			}
			break;

			case (unsigned long)ILType_UInt8:
			{
				CVM_WIDE(COP_WADDR, coder->localOffsets[0]);
				CVM_ADJUST(1);
				CVM_BYTE(COP_UBREAD);
				CVM_BYTE(COP_RETURN_1);
				CVM_ADJUST(-1);
			}
			break;

			case (unsigned long)ILType_Int16:
			{
				CVM_WIDE(COP_WADDR, coder->localOffsets[0]);
				CVM_ADJUST(1);
				CVM_BYTE(COP_SREAD);
				CVM_BYTE(COP_RETURN_1);
				CVM_ADJUST(-1);
			}
			break;

			case (unsigned long)ILType_UInt16:
			case (unsigned long)ILType_Char:
			{
				CVM_WIDE(COP_WADDR, coder->localOffsets[0]);
				CVM_ADJUST(1);
				CVM_BYTE(COP_USREAD);
				CVM_BYTE(COP_RETURN_1);
				CVM_ADJUST(-1);
			}
			break;

			case (unsigned long)ILType_Float32:
			{
				CVM_WIDE(COP_WADDR, coder->localOffsets[0]);
				CVM_BYTE(COP_FREAD);
				CVM_ADJUST(CVM_WORDS_PER_NATIVE_FLOAT);
				CVM_RETURN(CVM_WORDS_PER_NATIVE_FLOAT);
				CVM_ADJUST(-CVM_WORDS_PER_NATIVE_FLOAT);
			}
			break;

			case (unsigned long)ILType_Float64:
			{
				CVM_WIDE(COP_WADDR, coder->localOffsets[0]);
				CVM_BYTE(COP_DREAD);
				CVM_ADJUST(CVM_WORDS_PER_NATIVE_FLOAT);
				CVM_RETURN(CVM_WORDS_PER_NATIVE_FLOAT);
				CVM_ADJUST(-CVM_WORDS_PER_NATIVE_FLOAT);
			}
			break;

			default:
			{
				if(returnIsTop)
				{
					param = GetTypeSize(returnType);
					CVM_RETURN(param);
				}
				else
				{
					param = GetTypeSize(returnType);
					CVM_DWIDE(COP_MLOAD, coder->localOffsets[0], param);
					CVM_ADJUST(param);
					CVM_RETURN(param);
					CVM_ADJUST(-((ILInt32)param));
				}
			}
			break;
		}
	}
	else
	{
		CVM_BYTE(COP_RETURN);
	}

	/* Done */
	return 1;
}

/*
 * Set up a CVM coder instance to process a specific external constructor.
 */
static int CVMCoder_SetupExternCtor(ILCoder *_coder, unsigned char **start,
								    ILMethod *method, void *fn, void *cif,
								    void *ctorfn, void *ctorcif,
									int isInternal)
{
	ILCVMCoder *coder = (ILCVMCoder *)_coder;
	ILType *signature = ILMethod_Signature(method);
	int numArgs;
	ILUInt32 param;
	ILUInt32 numParams;
	ILUInt32 extraLocals;
	int returnIsTop;
	ILInt32 dest;
	unsigned char *start2;

	/* Output the code for the main method entry point, which will
	   include the prefix code for allocating fixed-sized objects */
	if(!CVMCoder_SetupExtern(_coder, start, method, fn, cif, isInternal))
	{
		return 0;
	}

	/* If we don't have an allocating constructor, then we are done */
	if(!ctorfn)
	{
		return 0;
	}

	/* If the coder buffer is full, then don't go any further.
	   The "Finish" code will cause a cache flush and restart */
	if(coder->posn >= coder->len)
	{
		return 1;
	}

	/* Output the entry point code for the allocating constructor */
	if(!CVMEntryPoint(coder, &start2, method, 0,
					  ILType_FromClass(ILMethod_Owner(method)), 0, 1, 1))
	{
		return 0;
	}

	/* Back-patch the prefix code to jump to the allocating constructor */
	dest = (ILInt32)(start2 - (*start - 6));
	(*start)[-6] = COP_BR_LONG;
	(*start)[-5] = COP_BR;
	(*start)[-4] = (unsigned char)(dest);
	(*start)[-3] = (unsigned char)(dest >> 8);
	(*start)[-2] = (unsigned char)(dest >> 16);
	(*start)[-1] = (unsigned char)(dest >> 24);

	/* Push the arguments for the call onto the stack */
	numArgs = -1;
	returnIsTop = 1;
	extraLocals = 1;
	if(isInternal)
	{
		/* Push a pointer to the thread value */
		CVM_BYTE(COP_PUSH_THREAD);
		++numArgs;
	}
	numParams = ILTypeNumParams(signature);
	for(param = 0; param < numParams; ++param)
	{
		if(ILType_IsValueType(ILTypeGetEnumType
		   		(ILTypeGetParam(signature, param + 1))))
		{
			CVM_WIDE(COP_WADDR, coder->argOffsets[param]);
			CVM_ADJUST(1);
			CVM_WIDE(COP_PSTORE, coder->localOffsets[extraLocals]);
			CVM_ADJUST(-1);
			CVM_WIDE(COP_WADDR_NATIVE_0 + numArgs,
					 coder->localOffsets[extraLocals]);
			++extraLocals;
			returnIsTop = 0;
		}
		else
		{
			CVM_WIDE(COP_WADDR_NATIVE_0 + numArgs,
					 coder->argOffsets[param]);
		}
		++numArgs;
	}
	CVM_WIDE(COP_WADDR, coder->localOffsets[0]);
	CVM_ADJUST(1);

	/* Output the call to the external method */
	CVM_BYTE(COP_CALL_NATIVE);
	CVM_PTR(ctorfn);
	CVM_PTR(ctorcif);
	CVM_ADJUST(-1);

	/* Return the contents of the local, which is the allocated object */
	if(returnIsTop)
	{
		CVM_RETURN(1);
	}
	else
	{
		CVM_WIDE(COP_PLOAD, coder->localOffsets[0]);
		CVM_ADJUST(1);
		CVM_RETURN(1);
		CVM_ADJUST(-1);
	}

	/* Done */
	return 1;
}

/*
 * Get the offset of an allocation constructor entry point
 * relative to the main method entry point.
 */
static int CVMCoder_CtorOffset(ILCoder *coder)
{
	return 6;
}

/*
 * Finish processing a method using a CVM coder instance.
 */
static int CVMCoder_Finish(ILCoder *_coder)
{
	ILCVMCoder *coder = (ILCVMCoder *)_coder;

	/* Clear the label pool */
	ILMemPoolClear(&(coder->labelPool));
	coder->labelList =0;
	if(coder->labelOutOfMemory)
	{
		/* We ran out of memory trying to allocate labels */
		return 0;
	}

	if(coder->posn < coder->len)
	{
		/* Back-patch the stack height check instruction */
		if(coder->maxHeight <= 8)
		{
			coder->buffer[coder->stackCheck] = COP_CKHEIGHT;
		}
		else
		{
			coder->buffer[coder->stackCheck + 1] =
					(unsigned char)(coder->maxHeight);
			coder->buffer[coder->stackCheck + 2] =
					(unsigned char)(coder->maxHeight >> 8);
			coder->buffer[coder->stackCheck + 3] =
					(unsigned char)(coder->maxHeight >> 16);
			coder->buffer[coder->stackCheck + 4] =
					(unsigned char)(coder->maxHeight >> 24);
		}
		return 1;
	}
	else
	{
		/* The buffer overflowed while outputting the code */
		return 0;
	}
}

#endif	/* IL_CVMC_CODE */