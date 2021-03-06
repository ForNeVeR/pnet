/*
 * Glyphs.cs - Implementation of the
 *			"System.Windows.Forms.Themes.Glyphs" class.
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

namespace System.Windows.Forms.Themes
{

// This class contains a number of bitmap glyphs for drawing
// things like checkmarks, close boxes, scroll arrows, etc.
// All of these are in the form of an xbm.

internal class Glyphs
{
	// Arrow that indicates a submenu.
	public const int menu_arrow_width = 4;
	public const int menu_arrow_height = 7;
	public static readonly byte[] menu_arrow_bits =
		{0x01, 0x03, 0x07, 0x0f, 0x07, 0x03, 0x01};

	// Checkmark within a menu.
	public const int menu_checkmark_width = 7;
	public const int menu_checkmark_height = 7;
	public static readonly byte[] menu_checkmark_bits =
		{0x40, 0x60, 0x71, 0x3b, 0x1f, 0x0e, 0x04};

	// Bullet within a menu.
	public const int menu_bullet_width = 7;
	public const int menu_bullet_height = 7;
	public static readonly byte[] menu_bullet_bits =
		{0x1c, 0x3e, 0x7f, 0x7f, 0x7f, 0x3e, 0x1c};

	// Left scroll bar arrow.
	public const int left_arrow_width = 4;
	public const int left_arrow_height = 7;
	public static readonly byte[] left_arrow_bits =
		{0x08, 0x0c, 0x0e, 0x0f, 0x0e, 0x0c, 0x08};

	// Right scroll bar arrow.
	public const int right_arrow_width = 4;
	public const int right_arrow_height = 7;
	public static readonly byte[] right_arrow_bits =
		{0x01, 0x03, 0x07, 0x0f, 0x07, 0x03, 0x01};

	// Up scroll bar arrow.
	public const int up_arrow_width = 7;
	public const int up_arrow_height = 4;
	public static readonly byte[] up_arrow_bits =
		{0x08, 0x1c, 0x3e, 0x7f};

	// Down scroll bar arrow.
	public const int down_arrow_width = 7;
	public const int down_arrow_height = 4;
	public static readonly byte[] down_arrow_bits =
		{0x7f, 0x3e, 0x1c, 0x08};

	// Combo box drop down arrow.
	public const int drop_down_arrow_width = 7;
	public const int drop_down_arrow_height = 4;
	public static readonly byte[] drop_down_arrow_bits =
		{0x7f, 0x3e, 0x1c, 0x08};

	// Checkmark within a checkbox.
	public const int checkmark_width = 7;
	public const int checkmark_height = 7;
	public static readonly byte[] checkmark_bits =
		{0x40, 0x60, 0x71, 0x3b, 0x1f, 0x0e, 0x04};

	// Close caption button.
	public const int close_button_width = 9;
	public const int close_button_height = 9;
	public static readonly byte[] close_button_bits =
		{0x00, 0x00, 0x86, 0x01, 0xcc, 0x00, 0x78, 0x00, 0x30,
		 0x00, 0x78, 0x00, 0xcc, 0x00, 0x86, 0x01, 0x00, 0x00};

	// Minimize caption button.
	public const int minimize_button_width = 9;
	public const int minimize_button_height = 9;
	public static readonly byte[] minimize_button_bits =
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		 0x00, 0x00, 0x00, 0x00, 0x00, 0x7e, 0x00, 0x7e, 0x00};

	// Maximize caption button.
	public const int maximize_button_width = 9;
	public const int maximize_button_height = 9;
	public static readonly byte[] maximize_button_bits =
		{0xff, 0x01, 0xff, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
		 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0xff, 0x01};

	// Restore caption button.
	public const int restore_button_width = 9;
	public const int restore_button_height = 9;
	public static readonly byte[] restore_button_bits =
		{0xfc, 0x00, 0xfc, 0x00, 0x84, 0x00, 0xbf, 0x00, 0xbf,
		 0x00, 0xe1, 0x00, 0x21, 0x00, 0x21, 0x00, 0x3f, 0x00};

	// Help caption button.
	public const int help_button_width = 9;
	public const int help_button_height = 9;
	public static readonly byte[] help_button_bits =
		{0x78, 0x00, 0xcc, 0x00, 0xcc, 0x00, 0x60, 0x00, 0x30,
		 0x00, 0x30, 0x00, 0x00, 0x00, 0x30, 0x00, 0x30, 0x00};

	// The various components of a normal radio button's border.
	public const int radio_width = 12;
	public const int radio_height = 12;
	public static readonly byte[] radio1_bits =		// Dark
		{0xf0, 0x00, 0x0c, 0x03, 0x02, 0x00, 0x02, 0x00, 0x01,
		 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x02, 0x00,
		 0x02, 0x00, 0x00, 0x00, 0x00, 0x00};
	public static readonly byte[] radio2_bits =		// DarkDark
		{0x00, 0x00, 0xf0, 0x00, 0x0c, 0x03, 0x04, 0x00, 0x02,
		 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x04, 0x00,
		 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	public static readonly byte[] radio3_bits =		// LightLight
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x04, 0x00,
		 0x08, 0x00, 0x08, 0x00, 0x08, 0x00, 0x08, 0x00, 0x04,
		 0x00, 0x04, 0x0c, 0x03, 0xf0, 0x00};
	public static readonly byte[] radio4_bits =		// Light
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00,
		 0x04, 0x00, 0x04, 0x00, 0x04, 0x00, 0x04, 0x00, 0x02,
		 0x0c, 0x03, 0xf0, 0x00, 0x00, 0x00};
	public static readonly byte[] radio5_bits =		// Inside background
		{0x00, 0xf0, 0x00, 0xf0, 0xf0, 0xf0, 0xf8, 0xf1, 0xfc,
		 0xf3, 0xfc, 0xf3, 0xfc, 0xf3, 0xfc, 0xf3, 0xf8, 0xf1,
		 0xf0, 0xf0, 0x00, 0xf0, 0x00, 0xf0};

	// The various components of a flat radio button's border.
	public static readonly byte[] rflat1_bits =		// Border
		{0xf0, 0x00, 0x0c, 0x03, 0x02, 0x04, 0x02, 0x04, 0x01,
		 0x08, 0x01, 0x08, 0x01, 0x08, 0x01, 0x08, 0x02, 0x04,
		 0x02, 0x04, 0x0c, 0x03, 0xf0, 0x00};
	public static readonly byte[] rflat2_bits =		// Inside background
		{0x00, 0xf0, 0xf0, 0xf0, 0xfc, 0xf3, 0xfc, 0xf3, 0xfe,
		 0xf7, 0xfe, 0xf7, 0xfe, 0xf7, 0xfe, 0xf7, 0xfc, 0xf3,
		 0xfc, 0xf3, 0xf0, 0xf0, 0x00, 0xf0};

	// The bullet to draw on the inside of a radio button when selected.
	public static readonly byte[] radio_bullet_bits =
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60,
		 0x00, 0xf0, 0x00, 0xf0, 0x00, 0x60, 0x00, 0x00, 0x00,
		 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

}; // class Glyphs

}; // namespace System.Windows.Forms.Themes
