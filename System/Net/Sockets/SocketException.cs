/*
 * SocketException.cs - Implementation of the "System.Net.Sockets.SocketException" class.
 *
 * Copyright (C) 2002  Southern Storm Software, Pty Ltd.
*
 * This program is free software, you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY, without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program, if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

namespace System.Net.Sockets
{

using System;
using Platform;

//This class is commented out until the assembly problems with Errno\
//and SocketMethods are solved
public class SocketException : SystemException
{
/*	// Internal state.
	private Errno errno;

	// Constructors.
	public SocketException()
		: base(_("IO_Socket"))
		{
			errno = Errno.EREMOTEIO;
		}
	internal SocketException(String msg)
		: base(msg)
		{
			errno = Errno.EREMOTEIO;
		}
	internal SocketException(String msg, Exception inner)
		: base(msg, inner)
		{
			errno = Errno.EREMOTEIO;
		}

	// Internal constructors that are used to set correct error codes.
	internal SocketException(Errno errno)
		: base(null)
		{
			this.errno = errno;
		}
	internal SocketException(Errno errno, String msg)
		: base(msg)
		{
			this.errno = errno;
		}
	internal SocketException(Errno errno, String msg, Exception inner)
		: base(msg, inner)
		{
			this.errno = errno;
		}

	// Get the platform error code associated with this exception.
	internal Errno Errno
			{
				get
				{
					return errno;
				}
			}

	// Get the message that corresponds to a platform error number.
	internal static String GetErrnoMessage(Errno errno)
			{
				// See if the resource file has provided an override.
				String resource = "errno_" + errno.ToString();
				String str = _(resource);
				if(str != null)
				{
					return str;
				}

				// Try getting a message from the underlying platform.
				str = FileMethods.GetErrnoMessage(errno);
				if(str != null)
				{
					return str;
				}

				// Use the default Socket exception string.
				return _("IO_Socket");
			}

	// Get the default message to use for Socket exceptions.
	protected internal override String MessageDefault
			{
				get
				{
					if(errno == Errno.EREMOTEIO)
					{
						return _("IO_Socket");
					}
					else
					{
						return GetErrnoMessage(errno);
					}
				}
			}

				
*/			
}; // class SocketException

}; // namespace System.Net.Sockets
