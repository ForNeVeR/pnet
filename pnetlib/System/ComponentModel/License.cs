/*
 * License.cs - Implementation of the
 *		"System.ComponentModel.ComponentModel.License" class.
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

namespace System.ComponentModel
{

#if CONFIG_COMPONENT_MODEL

using System;

public abstract class License : IDisposable
{
	// Constructor.
	protected License() {}

	// Get the license key.
	public abstract String LicenseKey { get; }

	// Dispose of this license.
	public abstract void Dispose();

}; // class License

#endif // CONFIG_COMPONENT_MODEL

}; // namespace System.ComponentModel
