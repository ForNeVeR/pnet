/*
 * ArgIterator.cs - Implementation of the "System.ArgIterator" class.
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

namespace System
{

using System.Runtime.CompilerServices;

public struct ArgIterator
{
	private int cookie1;
	private int cookie2;
	private int cookie3;
	private int cookie4;

	// Construct an iterator for an argument list.
	[MethodImpl(MethodImplOptions.InternalCall)]
	extern public ArgIterator(RuntimeArgumentHandle argList);

	// Construct an iterator for an argument list.
	[MethodImpl(MethodImplOptions.InternalCall), CLSCompliant(false)]
	extern public unsafe ArgIterator(RuntimeArgumentHandle argList, void *ptr);

	// Move the iterator to the end of the argument list.
	public void End() {}

	// Inherited methods.
	public override bool Equals(Object obj)
	{
		throw new NotSupportedException
				(Environment.GetResourceString("Exception_NotImplemented"));
	}
	public override int GetHashCode()
	{
		return cookie1 ^ cookie2 ^ cookie3 ^ cookie4;
	}

	// Get the next argument.
	[MethodImpl(MethodImplOptions.InternalCall), CLSCompliant(false)]
	extern public TypedReference GetNextArg();

	// Get the next argument of a specified type.
	[MethodImpl(MethodImplOptions.InternalCall), CLSCompliant(false)]
	extern public TypedReference GetNextArg(RuntimeTypeHandle type);

	// Get the type of the next argument.
	[MethodImpl(MethodImplOptions.InternalCall)]
	extern public RuntimeTypeHandle GetNextArgType();

	// Get the count of the remaining arguments.
	[MethodImpl(MethodImplOptions.InternalCall)]
	extern public int GetRemainingCount();

}; // class ArgIterator

}; // namespace System