/*
 * UriBuilder.cs - Implementation of "System.UriBuilder".
 *
 * Copyright (C) 2002 Free Software Foundation, Inc.
 *
 * Contributed by Stephen Compall <rushing@sigecom.net>
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
Some implementation details.

This class and Uri have a very close relationship. This is because they rely
on the same parsing mechanisms. After mulling over whether to put the parsers
in either this class or Uri (for efficiency), I chose this class because it
needs the verifiers anyway for the setty properties.

Also note that there is a special package constructor in Uri for use by this
class. This is because, upon getting the this.Uri property, these methods have
already done the necessary verification.

One more thing...the whole "escaping" thing makes things about a million times
more complicated.

The reason this.path can be String.Empty, not per spec, is so that ToString() will
know if the user doesn't really want the path to be "/".
*/

namespace System
{

// StringBuilders are cool
using System.Text;

public class UriBuilder
{
	// State. After construction, these are never null!

	// Holds the scheme information. (search 0->:)
	private String scheme;

	// authority = userinfo+host+port
	// userinfo = username:password
	private String username;
	private String password;
	private String host;
	private int port;

	// technically optional, but they want a path :)
	// contains the slash
	private String path;

	// doesn't contain the ? mark
	private String query;

	// remember: this is not part of the uri
	// doesn't contain the #
	private String fragment;
	// also known as hash

	// Constructors.
	public UriBuilder()
	{
		this.fragment = "";
		// localhost, not loopback!
		this.host = "localhost";
		this.password = "";
		this.path = "";
		this.port = 80;
		this.scheme = "http";
		this.username = "";
	}

	public UriBuilder(String uri) : this(new Uri(uri))
	{
	}

	[TODO]
	public UriBuilder(Uri uri)
	{

	}

	public UriBuilder(String schemeName, String hostName) : this(schemeName,
		hostName, 80, "", "")
	{
		// no implementation needed :)
	}

	public UriBuilder(String scheme, String host, int portNumber) :
		this(scheme, host, portNumber, "", "")
	{
	}

	public UriBuilder(String scheme, String host, int port, String pathValue) :
		this(scheme, host, port, pathValue, "")
	{
	}

	[TODO]
	public UriBuilder(String scheme, String host, int port, String path,
		String extraValue)
	{
		// capitalised where using built-in validation
		this.Scheme = scheme;
		this.host = host;
		if (port < 0) throw new ArgumentOutOfRangeException("port");
		this.port = port;
		this.path = path;
		if (extraValue[0] == '?')
			this.query = extraValue.Substring(1, extraValue.Length-1);
		else if (extraValue[0] == '#')
			this.fragment = extraValue.Substring(1, extraValue.Length-1);
		else if (extraValue != null && extraValue.Length != 0)
			throw new ArgumentException
				(S._("Exception_Argument"), "extraValue");
		this.username = "";
		this.password = "";
	}

	// Methods.

	// takes the string and sets all values on that basis
	private void ParseString(String instr, bool escaped)
	{

		// TODO: make default scheme "http://" if none given (OK done)
		int curpos = instr.IndexOf(':');
		if (curpos < 0)
			throw new UriFormatException();
		try
		{
			this.scheme = ValidateScheme(instr.Substring(0, curpos++), escaped);
		}
		catch (UriFormatException ufe)
		{
			this.scheme = Uri.UriSchemeHttp;
			curpos = 0;
		}

		// here's a real hack
		if (curpos != 0 && scheme != Uri.UriSchemeNews && 
			scheme != Uri.UriSchemeMailto)
		{
			if (curpos + 2 >= instr.Length ||
			    instr.Substring(curpos, 2) != "//")
				throw new UriFormatException();
			else
				curpos += 3;
		}

		// parsing Authority:
		// note: fixed this to stop before ? or #, which don't require
		// path to come first (look at mailto:)
		char[] sqh = {'/', '?', '#'};
		int eoAuthority = instr.IndexOfAny(sqh, curpos);
		if (eoAuthority == -1) eoAuthority = instr.Length;
		int eoSect = instr.IndexOf('@', curpos, eoAuthority - curpos);
		if (eoSect > 0)
		{
			// parsing username:password
			// input: curpos = first character
			// eoSect = @ sign separating it from rest of authority
			int eoUname = instr.IndexOf(':', curpos, eoSect-curpos);
			if (eoUname > 0)
			{
				this.username = ValidateUsername(instr.Substring
					(curpos, eoUname-curpos), escaped);
				this.password = ValidatePassword(instr.Substring
					(eoUname+1, eoSect-eoUname-1), escaped);
			}
			else
				this.username = ValidateUsername(instr.Substring
					(curpos, eoSect-curpos), escaped);
			curpos = eoSect + 1;
		}

		// parsing port
		int startPort = instr.LastIndexOf(':', curpos, eoAuthority-curpos) + 1;
		if (startPort > 0)
		{
			// parsePort input: startPort = first character of port
			// eoAuthority = the /, ?, or # that ends the port
			// have made default this.port = -1 (throw later @ runtime)
			try
			{
				this.port = Int32.Parse(instr.Substring(startPort,
					eoAuthority - startPort));
			}
			catch (FormatException fe) { this.port = -1; }
			catch (OverflowException oe)
			{
				throw new UriFormatException();
			}
			// you shouldn't type "-1" if you mean -1...type ""
			if (this.port < 0 || this.port > 65535)
				throw new UriFormatException();
			eoAuthority = startPort - 1;
		}
		else
			this.port = -1;

		// let's get our bearings:
		// curpos should be the beginning of server...done
		// eoAuthority should be separating character...done
		// now parse server
		this.host = ValidateHost(instr.Substring(curpos, eoAuthority));
		curpos = eoAuthority;

		// next up, parse path, query, and fragment
		// then it's done!

		if (curpos == instr.Length) return;

		// redefining eoSect to be the start of the #fragment
		eoSect = instr.LastIndexOf('#', curpos);
		if (eoSect == -1) eoSect = instr.Length;

		// redefining eoAuthority to be start of ?query
		eoAuthority = instr.IndexOf('?', curpos, eoSect - curpos);
		if (eoAuthority == -1) eoAuthority = eoSect;

		if (curpos < eoAuthority)
			this.path = ValidatePath(instr.Substring(curpos,
				eoAuthority - curpos), escaped);
		else
			this.path = "/";

		if (eoAuthority < eoSect)
			this.query = ValidateQuery(instr.Substring(eoAuthority + 1,
				eoSect - eoAuthority-1), escaped);
		else
			this.query = "";

		if (eoSect < instr.Length)
			this.fragment = ValidateFragment(instr.Substring(eoSect+1,
				instr.Length - eoSect-1), escaped);
		else
			this.fragment = "";
	}

	// all validation methods should throw if bad, return the valid string otherwise
	// and they should be static

	private static String ValidateScheme(String scheme, bool escaped)
	{
		// TODO
		return scheme;
	}

	private static String ValidateUsername(String username, bool escaped)
	{
		// TODO
		return username;
	}

	private static String ValidatePassword(String password, bool escaped)
	{
		// TODO
		return password;
	}

	private static String ValidateHost(String host)
	{
		// TODO
		return host;
	}

	private static String ValidatePath(String path, bool escaped)
	{
		// TODO
		return path;
	}

	private static String ValidateQuery(String query, bool escaped)
	{
		// TODO
		return query;
	}

	private static String ValidateFragment(String fragment, bool escaped)
	{
		// TODO
		return fragment;
	}

	public override bool Equals(Object rparam)
	{
		return this.Uri.Equals(rparam);
	}

	public override int GetHashCode()
	{
		String full = this.ToString();
		int hash = full.IndexOf('#');
		if (hash == -1)
			return full.GetHashCode();
		else
			return full.Substring(0, hash).GetHashCode();
	}

	[TODO]
	public override String ToString()
	{
		// TODO
		return null;
	}

	// Properties.
	// note: property setties don't do validation, for some stupid reason
	// and to whoever thought of it: 'ni! ni ni ni! ni ni ni ni ni!'
	// all unescaped?

	// the fragment is not technically part of the URI. So when anything
	// says, "end of the URI", it means before this, if present. It is
	// separated from the URI by the # character; thus, this is reserved.
	public String Fragment
	{
		get
		{
			// gets with the #
			if (this.fragment.Length != 0)
				return this.fragment;
			else
				// whoops...return frag, not query!
				return String.Concat("#", this.fragment);

		}
		set
		{
			if (value == null)
				this.fragment = "";
			else
				this.fragment = value;
			this.query = "";
		}
	}

	public String Host
	{
		get
		{
			return this.host;
		}
		set
		{
			this.host = value;
		}
	}

	public String Password
	{
		get
		{
			return this.password;
		}
		set
		{
			if (value == null)
				this.password = "";
			else
				this.password = value;
		}
	}

	public String Path
	{
		get
		{
			return this.path;
		}
		set
		{
			if (value.Length == 0)
				this.path = "/";
			else if (value[0] == '/')
				this.path = value;
			else
				this.path = String.Concat("/", value);
		}
	}

	public int Port
	{
		get
		{
			return this.port;
		}
		set
		{
			if (value < 0 && !String.Equals(this.scheme, "file"))
				throw new ArgumentOutOfRangeException("value");
			else
				this.port = value;
		}
	}

	public String Query
	{
		get
		{
			// gets with the ?
			if (this.query == "")
				return this.query;
			else
				return new StringBuilder(this.query.Length+1).Append('?').Append(this.query).ToString();
		}
		set
		{
			if (value == null)
				this.query = "";
			else
				this.query = value;
			this.fragment = "";
		}
	}

	public String Scheme
	{
		get
		{
			return this.scheme;
		}
		set
		{
			if (value == null)
				this.scheme = "";
			else
			{
				int colon = value.IndexOf(':');
				if (colon > -1)
					this.scheme = value.ToLower();
				else
					this.scheme = value.Substring(0, colon).
						ToLower();
			}
		}
	}

	[TODO]
	public Uri Uri
	{
		get
		{
			// TODO
			return null;
		}
	}

	public String UserName
	{
		get
		{
			return this.username;
		}
		set
		{
			this.username = value;
		}
	}

}; // class UriBuilder

}; // namespace System