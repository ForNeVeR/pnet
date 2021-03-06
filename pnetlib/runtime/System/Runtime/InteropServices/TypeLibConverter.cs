/*
 * TypeLibConverter.cs - Implementation of the
 *			"System.Runtime.InteropServices.TypeLibConverter" class.
 *
 * Copyright (C) 2003  Southern Storm Software, Pty Ltd.
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

#if CONFIG_COM_INTEROP

using System.Reflection;
using System.Reflection.Emit;

// We don't support COM type library conversion in this implementation.

[ClassInterface(ClassInterfaceType.None)]
[Guid("F1C3BF79-C3E4-11d3-88E7-00902754C43A")]
public sealed class TypeLibConverter : ITypeLibConverter
{

	// Constructor.
	public TypeLibConverter() {}

	// Convert an assembly into a type library.
	public Object ConvertAssemblyToTypeLib
				(Assembly assembly, String typeLibName,
				 TypeLibExporterFlags flags,
				 ITypeLibExporterNotifySink notifySink)
			{
				throw new NotImplementedException();
			}

#if CONFIG_REFLECTION_EMIT

	// Convert a type library into an emitted assembly.
	public AssemblyBuilder ConvertTypeLibToAssembly
				(Object typeLib, String asmFileName,
				 int flags, ITypeLibImporterNotifySink notifySink,
				 byte[] publicKey, StrongNameKeyPair keyPair,
				 bool unsafeInterfaces)
			{
				throw new NotImplementedException();
			}
	public AssemblyBuilder ConvertTypeLibToAssembly
				(Object typeLib, String asmFileName,
				 TypeLibImporterFlags flags,
				 ITypeLibImporterNotifySink notifySink,
				 byte[] publicKey, StrongNameKeyPair keyPair,
				 String asmNamespace, Version asmVersion)
			{
				throw new NotImplementedException();
			}

#endif // CONFIG_REFLECTION_EMIT

	// Get a primary interoperability assembly.
	public bool GetPrimaryInteropAssembly
				(Guid g, int major, int minor, int lcid,
				 out String asmName, out String asmCodeBase)
			{
				throw new NotImplementedException();
			}

}; // class TypeLibConverter

#endif // CONFIG_COM_INTEROP

}; // namespace System.Runtime.InteropServices
