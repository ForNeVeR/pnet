/*
 * IList_1.cs - Implementation of the
 *		"System.Collections.Generic.IList<T>" class.
 *
 * Copyright (C) 2007  Southern Storm Software, Pty Ltd.
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

namespace System.Collections.Generic
{

#if CONFIG_FRAMEWORK_2_0

public interface IList<T> : ICollection<T>
{
	int IndexOf(T value);
	void Insert(int index, T value);
	void RemoveAt(int index);
	T this[int index] { get; set; }

}; // interface IList<T>

#endif //  CONFIG_FRAMEWORK_2_0

}; // namespace System.Collections.Generic
