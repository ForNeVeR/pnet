/*
 * HashAlgorithm.cs - Implementation of the
 *		"System.Security.Cryptography.HashAlgorithm" class.
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

#if !ECMA_COMPAT

using System;
using System.IO;

public abstract class HashAlgorithm : ICryptoTransform
{
	// Internal state which is set by subclasses.
	protected int HashSizeValue;
	protected byte[] HashValue;
	protected int State;

	// Create an instance of the default hash algorithm.
	public static HashAlgorithm Create()
			{
				return (HashAlgorithm)
					(CryptoConfig.CreateFromName
						(CryptoConfig.HashDefault, null));
			}

	// Create an instance of a specific hash algorithm.
	public static HashAlgorithm Create(String hashName)
			{
				return (HashAlgorithm)
					(CryptoConfig.CreateFromName(hashName, null));
			}

	// Determine if multiple blocks can be transformed.
	public virtual bool CanTransformMultipleBlocks
			{
				get
				{
					return true;
				}
			}

	// Get the value of the computed hash code.
	public virtual byte[] Hash
			{
				get
				{
					if(HashValue != null)
					{
						return HashValue;
					}
					throw new CryptographicUnexpectedOperationException
						(_("Crypto_HashNotComputed"));
				}
			}

	// Get the size of the computed hash value.
	public virtual int HashSize
			{
				get
				{
					return HashSizeValue;
				}
			}

	// Get the input block size.
	public virtual int InputBlockSize
			{
				get
				{
					return 1;
				}
			}

	// Get the output block size.
	public virtual int OutputBlockSize
			{
				get
				{
					return 1;
				}
			}

	// Compute the hash value for a specified byte array.
	public byte[] ComputeHash(byte[] buffer)
			{
				HashCore(buffer, 0, buffer.Length);
				HashValue = HashFinal();
				Initialize();
				return HashValue;
			}

	// Compute the hash value for a region within a byte array.
	public byte[] ComputeHash(byte[] buffer, int offset, int count)
			{
				HashCore(buffer, offset, count);
				HashValue = HashFinal();
				Initialize();
				return HashValue;
			}

	// Compute the hash value for a specified input stream.
	public byte[] ComputeHash(Stream inputStream)
			{
				byte[] buf = new byte [512];
				int len;
				while((len = inputStream.Read(buf, 0, 512)) > 0)
				{
					HashCore(buf, 0, len);
				}
				HashValue = HashFinal();
				Initialize();
				return HashValue;
			}

	// Transform an input block into an output block.
	public int TransformBlock(byte[] inputBuffer, int inputOffset,
							  int inputCount, byte[] outputBuffer,
							  int outputOffset)
			{
				State = 1;
				HashCore(inputBuffer, inputOffset, inputCount);
				Array.Copy(inputBuffer, inputOffset,
						   outputBuffer, outputOffset, inputCount);
				return inputCount;
			}

	// Transform the final input block into a hash value.
	public byte[] TransformFinalBlock(byte[] inputBuffer,
									  int inputOffset,
									  int inputCount)
			{
				HashCore(inputBuffer, inputOffset, inputCount);
				HashValue = HashFinal();
				Initialize();
				byte[] outbuf = new byte [inputCount];
				Array.Copy(inputBuffer, inputOffset, outbuf, 0, inputCount);
				State = 0;
				return outbuf;
			}

	// Initialize the hash algorithm.
	public abstract void Initialize();

	// Write data to the underlying hash algorithm.
	protected abstract void HashCore(byte[] array, int ibStart, int cbSize);

	// Finalize the hash and return the final hash value.
	protected abstract byte[] HashFinal();

}; // class HashAlgorithm

#endif // !ECMA_COMPAT

}; // namespace System.Security.Cryptography