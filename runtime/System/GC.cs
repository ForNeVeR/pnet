/*
 * GC.cs - Implementation of the "System.GC" class.
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

public sealed class GC
{

	// Keep an object reference alive.
	[MethodImpl(MethodImplOptions.InternalCall)]
	extern public static void KeepAlive(Object obj);

	// Re-register an object for finalization.
	[MethodImpl(MethodImplOptions.InternalCall)]
	extern public static void ReRegisterForFinalize(Object obj);

	// Suppress finalization for an object.
	[MethodImpl(MethodImplOptions.InternalCall)]
	extern public static void SuppressFinalize(Object obj);

	// Wait for all pending finalizers to be run.
	[MethodImpl(MethodImplOptions.InternalCall)]
	extern public static void WaitForPendingFinalizers();

}; // class GC

}; // namespace System