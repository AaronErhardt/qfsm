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

#include "IOInfoList.h"
#include "IOInfo.h"
#include "Const.h"



IOInfoList& IOInfoList::operator=(const QList<IOInfo*>& iolist)
{
  QListIterator<IOInfo*> i(iolist);
  for(; i.hasNext(); )
    append(i.next());

  invert=false;
  return (*this);
}



//int IOInfoList::compareItems(IOInfo* io1, IOInfo* io2)

/**
 * Compares two items of the list. 
 * Attention: This does not take into account inversion.
 * 
 * @returns 
 * - 1, if @a ci1 is greater than @a ci2 
 * - -1, if @a ci1 is less than @a ci2 
 * - 0 if they are equal
 */
int IOInfoList::compareItems(IOInfo* ci1, IOInfo* ci2)
{
  IOInfo* io1 = (IOInfo*)ci1;
  IOInfo* io2 = (IOInfo*)ci2;

  /*
  char ascii1[MAX_CHARARRAY_LENGTH];
  char ascii2[MAX_CHARARRAY_LENGTH];
  int len1, len2;
  int count;

  io1->convertToASCII(ascii1, MAX_CHARARRAY_LENGTH, len1);
  io2->convertToASCII(ascii2, MAX_CHARARRAY_LENGTH, len2);

  
  count=0;

  while (count<len1)
  {
    if (count>=len2)
      return 1;
    if (ascii1[count]>ascii2[count])
      return 1;
    else if (ascii1[count]<ascii2[count])
      return -1;
    count++;
  }
  if (len1<len2)
    return -1;
  
  return 0;
  */
  /*
  if (io1->equals(io2))
    return 0;
    */

  if (io1->isInverted() && !io2->isInverted())
    return 1;
  else if (!io1->isInverted() && io2->isInverted())
    return -1;

  QString s1, s2;
  s1 = io1->convertToComparableString();
  s2 = io2->convertToComparableString();
  //qDebug("IO %s %d  %s %d", io1->convertToString().latin1(), io1->getRole(), io2->convertToString().latin1(), io2->getRole());
  if (s1>s2)
    return 1;
  else if (s1<s2)
    return -1;
  else
  {
    //qDebug("identical IO %s %s", s1.latin1(), s2.latin1());
    //qDebug("identical IO %s %s", io1->convertToString().latin1(), io2->convertToString().latin1());
    /*
    if (io1->isInverted() && !io2->isInverted())
      return 1;
    else if (!io1->isInverted() && io2->isInverted())
      return -1;
      */

    bool role1, role2;
    role1 = io1->getRole();
    role2 = io2->getRole();
    if (role1==role2)
      return 0;
    else if (role1==TRUE && role2==FALSE)
      return -1;
    else
      return 1;
  }
}

bool IOInfoList::contains(IOInfo *info)
{
  if(info==NULL)
    return false;
  QListIterator<IOInfo*> it(*this);
  IOInfo* io;

  for(; it.hasNext();)
  {
    io = it.next();
    //if(io->equals(info))
    if(compareItems(io, info)==0)
    {
      return true;
    }
  }
  return false;
}


void IOInfoList::setInvert( bool inv )
{
  QListIterator<IOInfo*> it(*this);
  IOInfo* io;

  for(; it.hasNext();)
  {
    io = it.next();
    io->setInvert(inv);
  }
}

bool IOInfoList::lessThan(IOInfo*& ci1, IOInfo*& ci2) {return (IOInfoList::compareItems(ci1,ci2)==-1);}

