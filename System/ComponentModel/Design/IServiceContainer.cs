/*
 * IServiceContainer.cs - Implementation of 
 *							"System.ComponentModel.Design.IServiceContainer" 
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

namespace System.ComponentModel.Design
{
#if !ECMA_COMPAT
	public abstract interface IServiceContainer: IServiceProvider
	{
		void AddService(Type serviceType,Object serviceInstance);
		
		void AddService(Type serviceType, ServiceCreatorCallback callback);
		
		void AddService(Type serviceType, Object serviceInstance, bool promote);
		
		void AddService(Type serviceType, ServiceCreatorCallback callback, 
		bool promote);
		
		void RemoveService(Type serviceType);

		void RemoveService(Type serviceType, bool promote);
	}
#endif
}//namespace