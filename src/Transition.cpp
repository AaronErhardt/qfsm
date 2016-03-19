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

#include <stdlib.h>
//#include <typeinfo>

#include "Transition.h"
#include "State.h"
#include "TransitionInfoBin.h"
#include "TransitionInfoASCII.h"
#include "IOInfoASCII.h"
#include "Convert.h"


/**
 * Constructor.
 * Initialises the transition with starting state @a s and end state @a e and
 * the info about the condition @a i.
 */
Transition::Transition(State* s, State* e, TransitionInfo* i)
{
  start = s;
  end = e;
  info=i; //NULL;
}

/// Destructor
Transition::~Transition()
{
  if (info)
    delete info;
}

/// Copy constructor.
Transition::Transition(const Transition& t)
{
  start = t.start;
  end = t.end;

  /*
  TransitionInfoBin p;

  if (t.info)
  {
    if (typeid(*t.info).name()==typeid(p).name())
    {
      info = new TransitionInfoBin(*(TransitionInfoBin*)t.info);
    }
    else
    {
      info = new TransitionInfoASCII(*(TransitionInfoASCII*)t.info);
    }
  }
  else
    info=NULL;
   */
  if (t.info)
    info = t.info->clone();
  else
    info = NULL;
}

/// Overloaded assignment operator.
Transition& Transition::operator=(const Transition& t)
{
  if (this!=&t)
  {
    start = t.start;
    end = t.end;

    if (info)
    {
      delete info;
      info=NULL;
    }

    /*
    TransitionInfoBin p;
    if (t.info)
    {
      if (typeid(*t.info).name()==typeid(p).name())
      {
	info = new TransitionInfoBin(*(TransitionInfoBin*)t.info);
      }
      else
      {
        info = new TransitionInfoASCII(*(TransitionInfoASCII*)t.info);
      }
    }
    else
      info=NULL;
      */

    if (t.info)
      info = t.info->clone();
    else
      info = NULL;
  }
  return *this;
}


/**
 * Validates a condition.
 * @param bits string with bits to validate
 * @param input if TRUE string may contain 'don't care'-positions ('x's)
 *   otherwise string may only contain 0's and 1's.
 * @return TRUE if condition is valid otherwise FALSE.
 */
int Transition::conditionValid(int type, QString string, bool input/*=TRUE*/)
{
  Convert conv;

  if (type==Binary) 	// **************** Binary
  {
    QChar c;
    int count=0;

    do
    {
      c = string[count++];
      if (input)
      {
        if (c!='1' && c!='0' && c!='|' && c!='x' && c!=QChar::null)
          return 1;
      }
      else
      {
        if (c!='1' && c!='0' && c!=QChar::null)
          return 1;
      }


    } while (c!=QChar::Null);

    return 0;
  }
  else if (type==Ascii)			// ****************** ASCII
  {
    int i=0;
    int len;
    char ctmp, cprev=0, cnext; 
    int ccount=0;

    len = string.length();

    while (i<len)
    {
      ctmp = string[i].latin1();
      if (ctmp=='\\')
      {
        if (i==len-1)
          return 2;

        cnext = string[i+1].latin1();
        if (cnext=='0')
        {
          if (i>=len-3)
            return 2;

          QString hexStr;
          int ires;
          hexStr.sprintf("%c%c", string[i+2].latin1(), string[i+3].latin1());

          if (!conv.hexStrToInt(hexStr, ires) || ires>255)
            return 5;

          cnext = (char)ires;
          i+=2;
        }
        else
          ctmp = IOInfoASCII::escapeToChar(cnext);

        i++;
        ccount++;
      }
      else if (ctmp=='-' && len>1)
      {
        if (i==0 || i==len-1)
          return 3;

        cnext = string[i+1].latin1();
        if (cnext=='-' || cprev=='-')
          return 3;

        if (cnext=='\\')
        {
          if (i==len-2)
            return 2;

          cnext = string[i+2].latin1();
          if (cnext=='0')
          {
            if (i>=len-4)
              return 2;

            QString hexStr;
            int ires;
            hexStr.sprintf("%c%c", string[i+3].latin1(), string[i+4].latin1());

            if (!conv.hexStrToInt(hexStr, ires) || ires>255)
              return 5;

            cnext = (char)ires;
            i+=2;
          }
          else
            cnext = IOInfoASCII::escapeToChar(string[i+2].latin1());

          i++;
        }
//	if (cnext<cprev)
//	  return 4;
        ccount+=abs(cnext-cprev);
        i++;
      }
      else
        ccount++;

      cprev = ctmp;
      i++;
    }
    if (!input)			// output must be only one character
    {
      if (ccount>1)
        return 4;
    }	
/*    else
    {
    if (ccount<1)
    return FALSE;
  }
*/

    return 0;
  }
  else
    return 0;
}



