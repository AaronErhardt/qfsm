/*
Copyright (C) 2000,2001 Stefan Duffner 

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/

#include <qregexp.h>

#include "Utils.h"

/// Transforms a string @a s to upper case, removes leading and trailing white spaces and replaces other white spaces to underscores
QString Utils::toUpperNoWS(QString s)
{
  s = s.stripWhiteSpace();
  s = s.replace(QRegExp("\\s"), "_");
  s = s.upper();
  return s;
}

/// Removes leading and trailing white spaces and replaces other white spaces to underscores of string @a s
QString Utils::noWS(QString s)
{
  s = s.stripWhiteSpace();
  s = s.replace(QRegExp("\\s"), "_");
  return s;
}

/**
 * Validates the a string of binary digits.
 * @returns TRUE if string valid, otherwise FALSE.
 */
bool Utils::binStringValid(QString s)
{
  QChar c;
  char cl;
  int count=0;

  do
  {
    c = s[count++];
    cl = c.latin1();
    if (cl!='0' && cl!='1' && c!=QChar::null)
      return FALSE;
  } while (c!=QChar::Null);

  return TRUE;
}
