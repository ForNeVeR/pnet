/*
 * property3.cs - Test duplicate property declarations.
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

class Test
{
	public int x { get { return 0; } }
	public char x { get { return ' '; } }	// error

	public void y() {}
	public int y { get { return 0; } }		// error

	private int z { get { return 0; } }

	public int w;
	public int w { get { return 0; } }		// error
}

class Test2 : Test
{
	public int x { get { return 0; } }		// error
	public new int y { get { return 0; } }
	public int z { get { return 0; } }
}
