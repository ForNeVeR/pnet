/*
 * Authorization.cs - Implementation of the "System.Net.Authorization" class.
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
 
namespace System.Net
{


public class Authorization
{
	[TODO]
	public Authorization(string token) {}
	
	[TODO]
	public Authorization(string token, bool finished) {}
	
	[TODO]
	public Authorization(string token, bool finished, string connectionGroupId) {}
	
	[TODO]
	public bool Complete { get{ return false; } }
	
	[TODO]
	public String ConnectionGroupId { get{ return null; } }
	
	[TODO]
	public String Message { get{ return null; } }
	
	[TODO]
	public String[] ProtectionRealm { get{ return null; } set{} }
	
}; //class Authorization

}; //namespace System.Net
