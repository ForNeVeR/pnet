/*
 * RefreshPropertiesAttribute.cs - Implementation of 
 *						"System.ComponentModel.RefreshPropertiesAttribute" 
 *
 * Copyright (C) 2002  Southern Storm Software, Pty Ltd.
 * Copyright (C) 2002  Free Software Foundation,Inc.
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

using System;

namespace System.ComponentModel
{
#if !ECMA_COMPAT
	public sealed class RefreshPropertiesAttribute: Attribute
	{
		[TODO]
		public RefreshPropertiesAttribute(RefreshProperties refresh)
		{
			throw new NotImplementedException(".ctor");
		}

		[TODO]
		public override bool Equals(Object obj)
		{
			throw new NotImplementedException("Equals");
		}

		[TODO]
		public override int GetHashCode()
		{
			throw new NotImplementedException("GetHashCode");
		}

		[TODO]
		public override bool IsDefaultAttribute()
		{
			throw new NotImplementedException("IsDefaultAttribute");
		}

		[TODO]
		public static readonly RefreshPropertiesAttribute All;

		[TODO]
		public static readonly RefreshPropertiesAttribute Default;

		[TODO]
		public static readonly RefreshPropertiesAttribute Repaint;

		public RefreshProperties RefreshProperties 
		{
			get
			{
				throw new NotImplementedException("RefreshProperties");
			}
		}

	}
#endif	
}//namespace