/*
 * GeneralFormatter.cs - Implementation of the
 *          "System.Private.NumberFormat.GeneralFormatter" class.
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

namespace System.Private.NumberFormat
{

using System;
using System.Text;

//
//  General Formatter 
//
internal class GeneralFormatter : Formatter
{
	char Ee;

	public GeneralFormatter(int precision, char Gg)
	{
		this.precision = precision;
		switch(Gg)
		{
			case 'G':
				Ee = 'E';
				break;
			case 'g':
				Ee = 'e';
				break;
			default:
				throw new FormatException(_("Format_StringException"));
				break;
		}
	}

	private static int PrecisionOf(Object o) 
	{
		if (o is Int16 || o is UInt16) return 5;
		if (o is Int32 || o is UInt32) return 10;
		if (o is Int64 || o is UInt64) return 19;
		if (o is Single) return 7;
		if (o is Double) return 15;
		if (o is Decimal) return 29;
		throw new FormatException(_("Format_TypeException"));
	}

	public override string Format(Object o, IFormatProvider provider)
	{
		int precision, exponent;

		if (this.precision == -1)
		{
			precision = PrecisionOf(o);
		}

		exponent = (int) Math.Floor(Math.Log10(OToDouble(o)));

		if (IsSignedInt(o) || IsUnsignedInt(o))
		{
			if (exponent < precision)
			{
				return new FixedPointFormatter(0).Format(o, provider);
			}
			else
			{
				return 
					new ScientificFormatter(-1, Ee).Format(o, provider);
			}
		}

		if (exponent >= -4 && exponent < precision)
		{
			return new FixedPointFormatter(precision).Format(o, provider);
		}
		else
		{
			return new ScientificFormatter(precision, Ee).Format(o, provider);
		}
	}		

} // class GeneralFormatter

} // namespace System.Private.NumberFormat
