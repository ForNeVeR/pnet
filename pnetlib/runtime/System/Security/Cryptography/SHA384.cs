/*
 * SHA384.cs - Implementation of the
 *		"System.Security.Cryptography.SHA384" class.
 *
 * Copyright (C) 2002  Southern Storm Software, Pty Ltd.
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

namespace System.Security.Cryptography
{

#if CONFIG_CRYPTO

using System;

public abstract class SHA384 : HashAlgorithm
{
	// Constructor.
	public SHA384()
			{
				HashSizeValue = 384;
			}

	// Create a new instance of the "SHA384" class.
	public new static SHA384 Create()
			{
				return (SHA384)(CryptoConfig.CreateFromName
						(CryptoConfig.SHA384Default, null));
			}
	public new static SHA384 Create(String algName)
			{
				return (SHA384)(CryptoConfig.CreateFromName(algName, null));
			}

}; // class SHA384

#endif // CONFIG_CRYPTO

}; // namespace System.Security.Cryptography
