/*
 * Win32Exception.cs - Implementation of "System.ComponentModel.Win32Exception" 
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
using System.Runtime.InteropServices;

namespace System.ComponentModel
{
#if !ECMA_COMPAT
	public class Win32Exception: ExternalException
	{
		[TODO]
		public Win32Exception()
		{
			throw new NotImplementedException(".ctor");
		}

		[TODO]
		public Win32Exception(int error)
		{
			throw new NotImplementedException(".ctor");
		}

		[TODO]
		public Win32Exception(int error, String message)
		{
			throw new NotImplementedException(".ctor");
		}

		public int NativeErrorCode 
		{
			get
			{
				throw new NotImplementedException("NativeErrorCode");
			}
		}

	}
#endif	
}//namespace