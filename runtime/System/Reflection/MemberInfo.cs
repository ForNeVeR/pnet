/*
 * MemberInfo.cs - Implementation of the "System.Reflection.MemberInfo" class.
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

public abstract class MemberInfo
{

	// Constructor.
	protected MemberInfo() : base() {}

	// Get the type that declares this member.
	public abstract Type DeclaringType { get; }

	// Get the type of member that this is.
	public abstract MemberTypes MemberType { get; }

	// Get the name of this member.
	public abstract String Name { get; }

	// Get the reflected type that was used to locate this member.
	public abstract Type ReflectedType { get; }

	// Get the custom attributes that are associated with this member.
	public abstract Object[] GetCustomAttributes(bool inherit);
	public abstract Object[] GetCustomAttributes(Type type, bool inherit);

	// Determine if custom attributes are defined for this member.
	public abstract bool IsDefined(Type type, bool inherit);

}; // class MemberInfo

}; // namespace System.Reflection