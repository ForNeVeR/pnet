/*
 * ClrHelpers.cs - Implementation of the "System.Reflection.ClrHelpers" class.
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

namespace System.Reflection
{

using System;
using System.Runtime.CompilerServices;

internal sealed class ClrHelpers
{

	///////////////////////////////////////////////////////////////////
	//
	// Useful wrappers
	//
	///////////////////////////////////////////////////////////////////

	// Get all custom attributes attached to a program item.
	public static Object[] GetCustomAttributes
					(IClrProgramItem item, bool inherit)
			{
				return GetCustomAttributes(item.ClrHandle,
										   IntPtr.Zero, inherit);
			}

	// Get the custom attributes of a specific type that are
	// attached to a program item.
	public static Object[] GetCustomAttributes
					(IClrProgramItem item, Type type, bool inherit)
			{
				return GetCustomAttributes(item.ClrHandle,
										   TypeToClrHandle(type, "type"),
										   inherit);
			}

	// Determine if there are custom attributes of a specified
	// type attached to a program item.
	public static bool IsDefined(IClrProgramItem item, Type type, bool inherit)
			{
				return IsDefined(item.ClrHandle,
								 TypeToClrHandle(type, "type"),
								 inherit);
			}

	// Get the declaring type for a program item.
	public static Type GetDeclaringType(IClrProgramItem item)
			{
				return Type.GetTypeFromHandle
					(new RuntimeTypeHandle(GetDeclaringType(item.ClrHandle)));
			}

	// Get the reflected type for a program item.
	public static Type GetReflectedType(IClrProgramItem item)
			{
				return Type.GetTypeFromHandle
					(new RuntimeTypeHandle(GetReflectedType(item.ClrHandle)));
			}

	// Get the name that is associated with a program item.
	public static String GetName(IClrProgramItem item)
			{
				return GetName(item.ClrHandle);
			}

	// Get a ParameterInfo block for a specific method parameter.
	// Zero indicates the return type.
	public static ParameterInfo GetParameterInfo(MemberInfo member,
												 IClrProgramItem item,
												 int num)
			{
				IntPtr param;
				Type type;
				param = GetParameter(item.ClrHandle, num);
				type = GetParameterType(item.ClrHandle, num);
				return new ClrParameter(member, param, num, type);
			}

	// Convert a type into a CLR handle value, after validating
	// that it is indeed a CLR type.
	public static IntPtr TypeToClrHandle(Type type, String name)
			{
				ClrType clrType;
				IntPtr handle;

				// Validate the supplied type.
				if(type == null)
				{
					throw new ArgumentNullException(name);
				}
				if((clrType = (type.UnderlyingSystemType as ClrType)) == null)
				{
					throw new ArgumentException(_("Arg_MustBeType"), name);
				}

				// Get the handle and validate it.
				handle = clrType.ClrHandle;
				if(handle == IntPtr.Zero)
				{
					throw new ArgumentException(_("Arg_MustBeType"));
				}

				// Return the handle to the caller.
				return handle;
			}

	///////////////////////////////////////////////////////////////////
	//
	// Primitive facilities provided directly by the CLR
	//
	///////////////////////////////////////////////////////////////////

	// Get the custom attributes for a program item.
	[MethodImpl(MethodImplOptions.InternalCall)]
	extern public static Object[] GetCustomAttributes
					(IntPtr item, IntPtr type, bool inherit);

	// Determine if custom attributes exist on a program item.
	[MethodImpl(MethodImplOptions.InternalCall)]
	extern public static bool IsDefined
					(IntPtr item, IntPtr type, bool inherit);

	// Get the declaring type for a program item.
	[MethodImpl(MethodImplOptions.InternalCall)]
	extern public static IntPtr GetDeclaringType(IntPtr item);

	// Get the reflected type for a program item.
	[MethodImpl(MethodImplOptions.InternalCall)]
	extern public static IntPtr GetReflectedType(IntPtr item);

	// Get the name that is associated with a program item.
	[MethodImpl(MethodImplOptions.InternalCall)]
	extern public static String GetName(IntPtr item);

	// Get the parameter block that is associated with a method item.
	// If "num" is zero, then get the return type parameter block.
	// Returns 0 if there is no underlying parameter information.
	[MethodImpl(MethodImplOptions.InternalCall)]
	extern public static IntPtr GetParameter(IntPtr item, int num);

	// Get the type of a method parameter.  If "num" is zero, then
	// get the method's return type.
	[MethodImpl(MethodImplOptions.InternalCall)]
	extern public static Type GetParameterType(IntPtr item, int num);

	// Get the number of parameters for a method program item.
	[MethodImpl(MethodImplOptions.InternalCall)]
	extern public static int GetNumParameters(IntPtr item);

	// Get the attributes for a member program item.
	[MethodImpl(MethodImplOptions.InternalCall)]
	extern public static int GetMemberAttrs(IntPtr item);

	// Get the calling conventions for a method program item.
	[MethodImpl(MethodImplOptions.InternalCall)]
	extern public static CallingConventions GetCallConv(IntPtr item);

	// Get the implementation attributes for a method program item.
	[MethodImpl(MethodImplOptions.InternalCall)]
	extern public static MethodImplAttributes GetImplAttrs(IntPtr item);

	// Get a particular method semantics value from an event or property.
	[MethodImpl(MethodImplOptions.InternalCall)]
	extern public static MethodInfo GetSemantics
			(IntPtr item, MethodSemanticsAttributes type, bool nonPublic);

	// Determine if an event or property has a particular method semantics.
	[MethodImpl(MethodImplOptions.InternalCall)]
	extern public static bool HasSemantics
			(IntPtr item, MethodSemanticsAttributes type, bool nonPublic);

}; // class ClrHelpers

}; // namespace System.Reflection