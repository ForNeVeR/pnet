/*
 * Encoding.cs - Implementation of the "System.Text.Encoding" class.
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

/*

Note: code pages are not really handled by this class yet.  They are
a very Windows-specific thing.  However, it is possible to create your
own code page handlers if you wish.  Create a "private" class called
"System.Text.CPnnnn" that inherits from "Encoding" where "nnnn" is
the code page number.  The "Encoding.GetEncoding" function will detect
this class and create an instance of it.

Code page "0" is used to represent the default encoding used by the
underlying runtime engine.  Nothing more is known about it.

*/

namespace System.Text
{

using System;
using System.Reflection;

public abstract class Encoding
{
	// Code page used by this encoding.
	private int codePage;

	// Constructor.
	protected Encoding()
			{
				codePage = 0;
			}
	protected Encoding(int codePage)
			{
				this.codePage = codePage;
			}

	// Convert between two encodings.
	public static byte[] Convert(Encoding srcEncoding, Encoding dstEncoding,
								 byte[] bytes)
			{
				if(srcEncoding == null)
				{
					throw new ArgumentNullException("srcEncoding");
				}
				if(dstEncoding == null)
				{
					throw new ArgumentNullException("dstEncoding");
				}
				if(bytes == null)
				{
					throw new ArgumentNullException("bytes");
				}
				return dstEncoding.GetBytes(srcEncoding.GetChars
							(bytes, 0, bytes.Length));
			}
	public static byte[] Convert(Encoding srcEncoding, Encoding dstEncoding,
								 byte[] bytes, int index, int count)
			{
				if(srcEncoding == null)
				{
					throw new ArgumentNullException("srcEncoding");
				}
				if(dstEncoding == null)
				{
					throw new ArgumentNullException("dstEncoding");
				}
				if(bytes == null)
				{
					throw new ArgumentNullException("bytes");
				}
				if(index < 0 || index > bytes.Length)
				{
					throw new ArgumentOutOfRangeException
						("index",
						 Environment.GetResourceString("ArgRange_Array"));
				}
				if(count < 0 || (bytes.Length - index) < count)
				{
					throw new ArgumentOutOfRangeException
						("count",
						 Environment.GetResourceString("ArgRange_Array"));
				}
				return dstEncoding.GetBytes(srcEncoding.GetChars
							(bytes, index, count));
			}

	// Determine if two Encoding objects are equal.
	public override bool Equals(Object obj)
			{
				Encoding enc = (obj as Encoding);
				if(enc != null)
				{
					return (this == enc);
				}
				else
				{
					return false;
				}
			}

	// Get the number of characters needed to encode a character buffer.
	public abstract int GetByteCount(char[] chars, int index, int count);

	// Convenience wrappers for "GetByteCount".
	public virtual int GetByteCount(String s)
			{
				if(s != null)
				{
					char[] chars = s.ToCharArray();
					return GetByteCount(chars, 0, chars.Length);
				}
				else
				{
					throw new ArgumentNullException("s");
				}
			}
	public virtual int GetByteCount(char[] chars)
			{
				if(chars != null)
				{
					return GetByteCount(chars, 0, chars.Length);
				}
				else
				{
					throw new ArgumentNullException("chars");
				}
			}

	// Get the bytes that result from encoding a character buffer.
	public abstract int GetBytes(char[] chars, int charIndex, int charCount,
								 byte[] bytes, int byteIndex);

	// Convenience wrappers for "GetBytes".
	public virtual int GetBytes(String s, int charIndex, int charCount,
								byte[] bytes, int byteIndex)
			{
				if(s == null)
				{
					throw new ArgumentNullException("s");
				}
				return GetBytes(s.ToCharArray(), charIndex, charCount,
								bytes, byteIndex);
			}
	public virtual byte[] GetBytes(String s)
			{
				if(s == null)
				{
					throw new ArgumentNullException("s");
				}
				char[] chars = s.ToCharArray();
				int numBytes = GetByteCount(chars, 0, chars.Length);
				byte[] bytes = new byte [numBytes];
				GetBytes(chars, 0, chars.Length, bytes, 0);
				return bytes;
			}
	public virtual byte[] GetBytes(char[] chars, int index, int count)
			{
				int numBytes = GetByteCount(chars, index, count);
				byte[] bytes = new byte [numBytes];
				GetBytes(chars, index, count, bytes, 0);
				return bytes;
			}
	public virtual byte[] GetBytes(char[] chars)
			{
				int numBytes = GetByteCount(chars, 0, chars.Length);
				byte[] bytes = new byte [numBytes];
				GetBytes(chars, 0, chars.Length, bytes, 0);
				return bytes;
			}

	// Get the number of characters needed to decode a byte buffer.
	public abstract int GetCharCount(byte[] bytes, int index, int count);

	// Convenience wrappers for "GetCharCount".
	public virtual int GetCharCount(byte[] bytes)
			{
				if(bytes == null)
				{
					throw new ArgumentNullException("bytes");
				}
				return GetCharCount(bytes, 0, bytes.Length);
			}

	// Get the characters that result from decoding a byte buffer.
	public abstract int GetChars(byte[] bytes, int byteIndex, int byteCount,
								 char[] chars, int charIndex);

	// Convenience wrappers for "GetChars".
	public virtual char[] GetChars(byte[] bytes, int index, int count)
			{
				int numChars = GetCharCount(bytes, index, count);
				char[] chars = new char [numChars];
				GetChars(bytes, index, count, chars, 0);
				return chars;
			}
	public virtual char[] GetChars(byte[] bytes)
			{
				if(bytes == null)
				{
					throw new ArgumentNullException("bytes");
				}
				int numChars = GetCharCount(bytes, 0, bytes.Length);
				char[] chars = new char [numChars];
				GetChars(bytes, 0, bytes.Length, chars, 0);
				return chars;
			}

	// Get a decoder that forwards requests to this object.
	public virtual Decoder GetDecoder()
			{
				return new ForwardingDecoder(this);
			}

	// Get an encoder that forwards requests to this object.
	public virtual Encoder GetEncoder()
			{
				return new ForwardingEncoder(this);
			}

	// Get an encoder for a specific code page.
	public static Encoding GetEncoding(int codePage)
			{
				// Check for the builtin code pages first.
				switch(codePage)
				{
					case 0: return Default;

					case ASCIIEncoding.ASCII_CODE_PAGE:
						return ASCII;

					case UTF7Encoding.UTF7_CODE_PAGE:
						return UTF7;

					case UTF8Encoding.UTF8_CODE_PAGE:
						return UTF8;

					case UnicodeEncoding.UNICODE_CODE_PAGE:
						return Unicode;

					case UnicodeEncoding.BIG_UNICODE_CODE_PAGE:
						return BigEndianUnicode;

					default: break;
				}

				// Build a code page class name.
				String cpName = "System.Text.CP" + codePage.ToString();

				// Look for a code page converter in this assembly.
				Assembly assembly = Assembly.GetExecutingAssembly();
				Type type = assembly.GetType(cpName);
				if(type != null)
				{
					return (Encoding)(Activator.CreateInstance(type));
				}

				// Look in any assembly, in case the application
				// has provided its own code page handler.
				type = Type.GetType(cpName);
				if(type != null)
				{
					return (Encoding)(Activator.CreateInstance(type));
				}

				// We have no idea how to handle this code page.
				throw new NotSupportedException
					(String.Format
						(Environment.GetResourceString("NotSupp_CodePage"),
						 codePage.ToString()));
			}

	// Get a hash code for this instance.
	public override int GetHashCode()
			{
				return codePage;
			}

	// Get the maximum number of bytes needed to encode a
	// specified number of characters.
	public abstract int GetMaxByteCount(int charCount);

	// Get the maximum number of characters needed to decode a
	// specified number of bytes.
	public abstract int GetMaxCharCount(int byteCount);

	// Get the identifying preamble for this encoding.
	public virtual byte[] GetPreamble()
			{
				return new byte [0];
			}

	// Decode a buffer of bytes into a string.
	public virtual String GetString(byte[] bytes, int index, int count)
			{
				return new String(GetChars(bytes, index, count));
			}
	public virtual String GetString(byte[] bytes)
			{
				return new String(GetChars(bytes));
			}

	// Get the code page represented by this object.
	public virtual int CodePage
			{
				get
				{
					return codePage;
				}
			}

	// Get the Windows code page represented by this object.
	public virtual int WindowsCodePage
			{
				get
				{
					// We make no distinction between normal and
					// Windows code pages in this implementation.
					return codePage;
				}
			}

	// Storage for standard encoding objects.
	private static Encoding asciiEncoding = null;
	private static Encoding bigEndianEncoding = null;
	private static Encoding defaultEncoding = null;
	private static Encoding utf7Encoding = null;
	private static Encoding utf8Encoding = null;
	private static Encoding unicodeEncoding = null;

	// Get the standard ASCII encoding object.
	public static Encoding ASCII
			{
				get
				{
					lock(typeof(Encoding))
					{
						if(asciiEncoding == null)
						{
							asciiEncoding = new ASCIIEncoding();
						}
						return asciiEncoding;
					}
				}
			}

	// Get the standard big-endian Unicode encoding object.
	public static Encoding BigEndianUnicode
			{
				get
				{
					lock(typeof(Encoding))
					{
						if(bigEndianEncoding == null)
						{
							bigEndianEncoding = new UnicodeEncoding(true, true);
						}
						return bigEndianEncoding;
					}
				}
			}

	// Get the default encoding object.
	public static Encoding Default
			{
				get
				{
					lock(typeof(Encoding))
					{
						if(defaultEncoding == null)
						{
							defaultEncoding = new DefaultEncoding();
						}
						return defaultEncoding;
					}
				}
			}

	// Get the standard UTF-7 encoding object.
	public static Encoding UTF7
			{
				get
				{
					lock(typeof(Encoding))
					{
						if(utf7Encoding == null)
						{
							utf7Encoding = new UTF7Encoding();
						}
						return utf7Encoding;
					}
				}
			}

	// Get the standard UTF-8 encoding object.
	public static Encoding UTF8
			{
				get
				{
					lock(typeof(Encoding))
					{
						if(utf8Encoding == null)
						{
							utf8Encoding = new UTF8Encoding();
						}
						return utf8Encoding;
					}
				}
			}

	// Get the standard little-endian Unicode encoding object.
	public static Encoding Unicode
			{
				get
				{
					lock(typeof(Encoding))
					{
						if(unicodeEncoding == null)
						{
							unicodeEncoding = new UnicodeEncoding();
						}
						return unicodeEncoding;
					}
				}
			}

	// Forwarding decoder implementation.
	private sealed class ForwardingDecoder : Decoder
	{
		private Encoding encoding;

		// Constructor.
		public ForwardingDecoder(Encoding enc)
				{
					encoding = enc;
				}

		// Override inherited methods.
		public override int GetCharCount(byte[] bytes, int index, int count)
				{
					return encoding.GetCharCount(bytes, index, count);
				}
		public override int GetChars(byte[] bytes, int byteIndex,
									 int byteCount, char[] chars,
									 int charCount)
				{
					return encoding.GetChars(bytes, byteIndex, byteCount,
											 chars, charCount);
				}

	} // ForwardingDecoder

	// Forwarding encoder implementation.
	private sealed class ForwardingEncoder : Encoder
	{
		private Encoding encoding;

		// Constructor.
		public ForwardingEncoder(Encoding enc)
				{
					encoding = enc;
				}

		// Override inherited methods.
		public override int GetByteCount(char[] chars, int index,
										 int count, bool flush)
				{
					return encoding.GetByteCount(chars, index, count);
				}
		public override int GetBytes(char[] chars, int charIndex,
									 int charCount, byte[] bytes,
									 int byteCount, bool flush)
				{
					return encoding.GetBytes(chars, charIndex, charCount,
											 bytes, byteCount);
				}

	} // ForwardingEncoder

}; // class Encoding

}; // namespace System.Text