/*
 * ServicePoint.cs - Implementation of the "System.Net.ServicePoint" class.
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


[TODO]
public class ServicePoint
{
	public override int GetHashCode() { return 0; }
	
	public Uri Address { get{ return null; } }
	
	public int ConnectionLimit { get{ return 0; } set{} }
	
	public String ConnectionName { get{ return null; } }
	
	public int CurrentConnections { get{ return 0; } }
	
	public DateTime IdleSince { get{ return DateTime.MinValue; } }
	
	public int MaxIdleTime { get{ return 0; } set{} }
	
	public virtual Version ProtocolVersion { get{ return new Version(0, 0); } }
	
	public bool SupportsPipelining { get{ return false; } }
}; //class ServicePoint

}; //namespace System.Net