/*
 * accept.c - Accept a connection on a socket.
 *
 * This file is part of the Portable.NET C library.
 * Copyright (C) 2004  Southern Storm Software, Pty Ltd.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "socket-glue.h"

int
__accept (int fd, struct sockaddr *addr, socklen_t *len)
{
  Socket *socket;
  Socket *newSocket;
  EndPoint *ep = null;
  int result;

  /* Get the socket object associated with the descriptor */
  socket = syscall_get_socket (fd);
  if (!socket)
    return -1;
  if (!__syscall_is_listening (fd))
    {
      errno = EINVAL;
      return -1;
    }

  /* Accept an incoming connection */
  try
    {
      newSocket = socket->Accept();
      ep = newSocket->LocalEndPoint;
    }
  catch (SocketException)
    {
      if (socket->Blocking)
        errno = EINVAL;
      else
        errno = EAGAIN;
      return -1;
    }

  /* Convert the end point into a socket address */
  result = __endpoint_to_sockaddr (fd, ep, addr, len);
  if (result < 0)
    {
      newSocket.Close();
      return -1;
    }
  return __syscall_wrap_accept (newSocket);
}

weak_alias (__accept, accept)
