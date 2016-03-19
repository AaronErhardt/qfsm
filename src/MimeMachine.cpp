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

#include "MimeMachine.h"


/// Constructor
MimeMachine::MimeMachine(const QString& str)
	   : QMimeData()
{
  setData("text/qfsm-objects",str.toAscii());
//  setSubtype("plain");
}


/**
 * Returns the format string (MIME-Type).
 * This is "text/qfsm-objects".
 * Only one format is available so if i!=0, this method will return NULL.
 */
const char* MimeMachine::format(int i) const
{
  if (i==0)
    return "text/qfsm-objects";
  else
    return NULL;
}

