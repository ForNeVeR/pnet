/*
 * MarshalByRefObject.cs - Implementation of "System.MarshalByRefObject".
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

using System.Runtime.Remoting;

public abstract class MarshalByRefObject
{

	// Constructor.
	protected MarshalByRefObject() : base() {}

#if !ECMA_COMPAT

	// Create a marshalable reference for this object.
	public virtual ObjRef CreateObjRef()
			{
				// Remoting is not yet supported by this class library.
				throw new RemotingException(_("NotSupp_Remoting"));
			}

	// Get a lifetime service object for this object.
	[TODO]
	public Object GetLifetimeService()
			{
				// TODO
				return null;
			}

	// Initialize the lifetime service for this object.
	[TODO]
	public virtual Object InitializeLifetimeService()
			{
				// TODO
				return null;
			}

#endif // !ECMA_COMPAT

}; // class MarshalByRefObject

}; // namespace System