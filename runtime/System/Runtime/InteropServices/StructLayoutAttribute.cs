/*
 * StructLayoutAttribute.cs - Implementation of the
 *			"System.Runtime.InteropServices.StructLayoutAttribute" class.
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

namespace System.Runtime.InteropServices
{

[AttributeUsage(AttributeTargets.Class | AttributeTargets.Struct,
				AllowMultiple=false, Inherited=false)]
public sealed class StructLayoutAttribute : Attribute
{
	// Internal state.
	private LayoutKind kind;

	// Constructors.
	public StructLayoutAttribute(LayoutKind layoutKind)
			{
				kind = layoutKind;
			}

	public StructLayoutAttribute(short layoutKind)
			{
				kind = (LayoutKind)layoutKind;
			}

	// Public fields.
	public System.Runtime.InteropServices.CharSet CharSet;
	public int Size;
	public int Pack;

	// Properties.
	public LayoutKind Value
			{
				get
				{
					return kind;
				}
			}

}; // class StructLayoutAttribute

}; // namespace System.Runtime.InteropServices