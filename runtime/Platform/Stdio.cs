/*
 * Stdio.cs - Implementation of the "Platform.Stdio" class.
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

namespace Platform
{

using System;
using System.Runtime.CompilerServices;

internal class Stdio
{
	// Close a standard file descriptor.
	[MethodImpl(MethodImplOptions.InternalCall)]
	extern public static void StdClose(int fd);

	// Flush a standard file descriptor.
	[MethodImpl(MethodImplOptions.InternalCall)]
	extern public static void StdFlush(int fd);

	// Write to a standard file descriptor.
	[MethodImpl(MethodImplOptions.InternalCall)]
	extern public static void StdWrite(int fd, char value);

	[MethodImpl(MethodImplOptions.InternalCall)]
	extern public static void StdWrite(int fd, char[] value,
									   int index, int count);

	[MethodImpl(MethodImplOptions.InternalCall)]
	extern public static void StdWrite(int fd, String value);

	// Read from a standard file descriptor.
	[MethodImpl(MethodImplOptions.InternalCall)]
	extern public static int StdRead(int fd);

	[MethodImpl(MethodImplOptions.InternalCall)]
	extern public static int StdRead(int fd, char[] value,
								     int index, int count);

	// Peek from a standard file descriptor.
	[MethodImpl(MethodImplOptions.InternalCall)]
	extern public static int StdPeek(int fd);

}; // class Stdio

}; // namespace Platform