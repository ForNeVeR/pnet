/*
 * Version.cs - Implementation of the "System.Version" class.
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

namespace System
{

public sealed class Version : ICloneable, IComparable
{
	// Internal state.
	private int major, minor, build, revision;

	// Constructors.
	public Version(String version)
			{
				// TODO
			}
	public Version(int major, int minor)
			{
				if(major < 0)
				{
					throw new ArgumentOutOfRangeException
						("major",
						 Environment.GetResourceString
						 	("ArgRange_NonNegative"));
				}
				if(minor < 0)
				{
					throw new ArgumentOutOfRangeException
						("minor",
						 Environment.GetResourceString
						 	("ArgRange_NonNegative"));
				}
				this.major = major;
				this.minor = minor;
				this.build = -1;
				this.revision = -1;
			}
	public Version(int major, int minor, int build)
			{
				if(major < 0)
				{
					throw new ArgumentOutOfRangeException
						("major",
						 Environment.GetResourceString
						 	("ArgRange_NonNegative"));
				}
				if(minor < 0)
				{
					throw new ArgumentOutOfRangeException
						("minor",
						 Environment.GetResourceString
						 	("ArgRange_NonNegative"));
				}
				if(build < 0)
				{
					throw new ArgumentOutOfRangeException
						("build",
						 Environment.GetResourceString
						 	("ArgRange_NonNegative"));
				}
				this.major = major;
				this.minor = minor;
				this.build = build;
				this.revision = -1;
			}
	public Version(int major, int minor, int build, int revision)
			{
				if(major < 0)
				{
					throw new ArgumentOutOfRangeException
						("major",
						 Environment.GetResourceString
						 	("ArgRange_NonNegative"));
				}
				if(minor < 0)
				{
					throw new ArgumentOutOfRangeException
						("minor",
						 Environment.GetResourceString
						 	("ArgRange_NonNegative"));
				}
				if(build < 0)
				{
					throw new ArgumentOutOfRangeException
						("build",
						 Environment.GetResourceString
						 	("ArgRange_NonNegative"));
				}
				if(revision < 0)
				{
					throw new ArgumentOutOfRangeException
						("revision",
						 Environment.GetResourceString
						 	("ArgRange_NonNegative"));
				}
				this.major = major;
				this.minor = minor;
				this.build = build;
				this.revision = revision;
			}

	// Get the version components.
	public int Major	{ get { return major; } }
	public int Minor	{ get { return minor; } }
	public int Build	{ get { return build; } }
	public int Revision	{ get { return revision; } }

	// Implement ICloneable.
	public Object Clone()
			{
				if(build == -1)
				{
					return new Version(major, minor);
				}
				else if(revision == -1)
				{
					return new Version(major, minor, build);
				}
				else
				{
					return new Version(major, minor, build, revision);
				}
			}

	// Compare two version objects.
	public int CompareTo(Object version)
			{
				Version vers = (version as Version);
				if(vers != null)
				{
					if(major > vers.major)
					{
						return 1;
					}
					else if(major < vers.major)
					{
						return -1;
					}
					if(minor > vers.minor)
					{
						return 1;
					}
					else if(minor < vers.minor)
					{
						return -1;
					}
					if(build > vers.build)
					{
						return 1;
					}
					else if(build < vers.build)
					{
						return -1;
					}
					if(revision > vers.revision)
					{
						return 1;
					}
					else if(revision < vers.revision)
					{
						return -1;
					}
					return 0;
				}
				else if(version != null)
				{
					throw new ArgumentException
						(Environment.GetResourceString("Arg_MustBeVersion"));
				}
				else
				{
					throw new ArgumentNullException("version");
				}
			}

	// Determine if two Version objects are equal.
	public override bool Equals(Object obj)
			{
				Version version = (obj as Version);
				if(version != null)
				{
					return (major == version.major &&
							minor == version.minor &&
							build == version.build &&
							revision == version.revision);
				}
				else
				{
					return false;
				}
			}

	// Get a hash code for this Version object.
	public override int GetHashCode()
			{
				return (major << 24) ^ (minor << 16) ^
				       ((build & 0xFF) << 8) ^ (revision & 0xFFFF);
			}

	// Convert this object into a string.
	public override String ToString()
			{
				if(build == -1)
				{
					return major.ToString() + "." + minor.ToString();
				}
				else if(revision == -1)
				{
					return major.ToString() + "." + minor.ToString() +
						   "." + build.ToString();
				}
				else
				{
					return major.ToString() + "." + minor.ToString() +
						   "." + build.ToString() + "." + revision.ToString();
				}
			}

	// Convert this object into a string with a specified number of components.
	public String ToString(int fieldCount)
			{
				if(fieldCount < 0 || fieldCount > 4 ||
				   (fieldCount > 2 && build == -1) ||
				   (fieldCount > 3 && revision == -1))
				{
					throw new ArgumentException
						(Environment.GetResourceString
							("Arg_VersionFields"));
				}
				switch(fieldCount)
				{
					case 1:	return major.ToString();

					case 2:	return major.ToString() + "." + minor.ToString();

					case 3:	return major.ToString() + "." + minor.ToString()
								   + "." + build.ToString();

					case 4:	return major.ToString() + "." + minor.ToString()
								   + "." + build.ToString()
								   + "." + revision.ToString();
				}
				return String.Empty;
			}

	// Relational operators.
	public static bool operator==(Version v1, Version v2)
			{
				return v1.Equals(v2);
			}
	public static bool operator!=(Version v1, Version v2)
			{
				return !v1.Equals(v2);
			}
	public static bool operator<(Version v1, Version v2)
			{
				return (v1.CompareTo(v2) < 0);
			}
	public static bool operator<=(Version v1, Version v2)
			{
				return (v1.CompareTo(v2) <= 0);
			}
	public static bool operator>(Version v1, Version v2)
			{
				return (v1.CompareTo(v2) > 0);
			}
	public static bool operator>=(Version v1, Version v2)
			{
				return (v1.CompareTo(v2) >= 0);
			}

}; // class Version

}; // namespace System