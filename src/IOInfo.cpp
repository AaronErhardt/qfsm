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

#include <qstring.h>
#include <q3valuelist.h>
//Added by qt3to4:
#include <Q3PtrList>

#include "TransitionInfo.h"
#include "IOInfoBin.h"
#include "IOInfoList.h"
#include "IOInfo.h"
//#include "IOInfoASCII.h"


/// Constructor
IOInfo::IOInfo(IOType t, bool inv/*=FALSE*/)
{
  type = t;
  role = FALSE;
  invert = inv;
  range = FALSE;
  any = FALSE;
  def = FALSE;
  range_start = 0;
  range_end = 0;
}

/// Destructor
IOInfo::~IOInfo()
{
}


/// Returns TRUE if @a io equals this object
bool IOInfo::equals(IOInfo* io)
{
  if(io==NULL)
    return FALSE;
  if (io->type!=type)
    return FALSE;
  if (io->isInverted()!=invert)
    return FALSE;
  if ((io->any && any)==TRUE)
    return TRUE;

  IOInfoBin b1(type), b2(type);
  int len1, len2, maxlen;
  len1 = getLength();
  len2 = io->getLength();

  maxlen = len1>len2? len1 : len2;

  b1 = convertToBin(maxlen);
  b2 = io->convertToBin(maxlen);

  QList<IOInfo*> l1=b1.getSingles();
  QList<IOInfo*> l2=b2.getSingles();
  
  IOInfoList::const_iterator i1,i2;
  for(i1=l1.constBegin(); i1!=l1.constEnd(); ++i1)
  {
    for(i2=l2.constBegin(); i2!=l2.constEnd(); ++i2)
    {
      if(((IOInfoBin*)(*i1))->getInfo() != ((IOInfoBin*)(*i2))->getInfo())
        return FALSE;
    }
  }
  return TRUE;

}


/// Returns TRUE if @a io matches this object (i.e. this I/O info contains @a io)
bool IOInfo::matches(IOInfo* io)
{
  bool io_matches;
  IOInfoList l1,l2;
  IOInfoBin b1(type), b2(type);
  int len1, len2, maxlen;
  len1 = getLength();
  len2 = io->getLength();

  maxlen = len1>len2? len1 : len2;

  b1 = convertToBin(maxlen);
  b2 = io->convertToBin(maxlen);

  //if ((any && io->getAnyInput()))
  if (any) // any input is accepted
    return TRUE;

  if(def && io->isDefault())   // can this case occur? 
    return FALSE;

  //qDebug("b1: %s", b1.convertToString().latin1());
  //qDebug("b2: %s", b2.convertToString().latin1());

  b1.split(l1,true);
  b2.split(l2,true);

  // all b2 must be "contained" in b1
  
  IOInfoList::const_iterator i1,i2;

  for(i2=l2.constBegin(); i2!=l2.constEnd(); ++i2)
  {
    io_matches=false;
    for(i1=l1.constBegin(); i1!=l1.constEnd(); ++i1)
    {
      if(((IOInfoBin*)(*i1))->getInfo() == ((IOInfoBin*)(*i2))->getInfo())
      {
        //qDebug("match: %s (in %s) matches %s", (*i1)->convertToString().latin1(), convertToString().latin1(), (*i2)->convertToString().latin1());
        io_matches=true;
	break;
      }
    }
    if (io_matches==false)
      return false;
  }

   while (!l1.isEmpty())
     delete l1.takeFirst();
   while (!l2.isEmpty())
     delete l2.takeFirst();

  return true;
}


void IOInfo::expandList(IOInfoList& input, IOInfoList& list, bool resolve_invert)
{
  // creating eventlist (with events that could change a state) using all input conditions
  IOInfoList eventlist;
//  eventlist.setAutoDelete(TRUE);
  IOInfo *io;
  IOInfo *start, *end;
  IOInfo *new_start, *new_end;
  QMutableListIterator<IOInfo*> inputit(input);
  for(; inputit.hasNext();)
  {
    IOInfoList iolist;
//    iolist.setAutoDelete(TRUE);
    inputit.next()->split(iolist, resolve_invert);

    /*
    if (inputit.current()->isInverted())
    qDebug("NOT %s\n", inputit.current()->convertToString().latin1());
    else
    qDebug("%s\n", inputit.current()->convertToString().latin1());
    */

    QMutableListIterator<IOInfo*> it(iolist);
    for(; it.hasNext();)
    {
      io = it.next();
      //qDebug("io: %s", io->convertToString().latin1());

      QList<IOInfo*> list;
 //     list.setAutoDelete(TRUE);
      if (resolve_invert || !io->isInverted())
      {
        list = io->getSinglesInversion();

        if (!list.isEmpty())
        {
          start = list.front();
          end = list.back();

          new_start = start->clone();
          new_end = end->clone();
          new_start->setRole(TRUE);
          new_end->setRole(FALSE);

          eventlist.append(new_start);
          eventlist.append(new_end);
        }
      }
      else eventlist.append(io->clone());
    }
  }

  // creating output while traversing eventlist (sort of line sweep algorithm)

  int open_counter=0;  // open ranges
  //int prev_open;
  IOInfo* previo=NULL;
  IOInfo *io_minus1=NULL, *io_plus1=NULL;
  QString s, e;
  
//  eventlist.sort();
  qSort(eventlist.begin(), eventlist.end(), IOInfoList::lessThan);
  //qHeapSort(eventlist.first(), eventlist.last());
  //qHeapSort(eventlist);
  start=end=NULL;
  io = NULL;
  QMutableListIterator<IOInfo*> evit(eventlist);
  
  /*
  for(; evit.hasNext();)
  {
    io = evit.next();
    qDebug("second loop:"+io->convertToString());
    if(!list.contains(io))
      list.append(io);
  }
  */
  for(; evit.hasNext();)
  {
    previo = io;
    io = evit.next();
    if (io->isInverted())
    {
      if (!list.contains(io))
      {
        list.append(io->clone());
      }
    }
    else // not inverted
    {
      if (io->getRole()==TRUE)	// start event
      {
        if (open_counter==0)
          start = io;
        else
        {
          io_minus1 = io->getMinus1();
          if (io_minus1==NULL)
          {
            open_counter++;
            continue;
          }
          s = start->convertToString();
          e = io_minus1->convertToString();
          if (eventlist.compareItems(start, io_minus1)<=0)
          {
            IOInfo* new_io = start->clone();
            new_io->setRangeInfo(start, io_minus1);
            if (!list.contains(new_io))
            {
              list.append(new_io);
            }
          }

          delete io_minus1;
	  
          start = io;
        }
        open_counter++;
      }
      else			// end event
      {
        open_counter--;
        if (!io->equals(previo) || (io->equals(previo) 
             && previo!=NULL && io->getRole()!=previo->getRole()))
          end = io;

        if (start && end)
        {
          s = start->convertToString();
          e = end->convertToString();
          if (eventlist.compareItems(start, end)<=0)
          {
            IOInfo* new_io = start->clone();
            new_io->setRangeInfo(start, end);
            if (!list.contains(new_io))
            {
              list.append(new_io);
            }
          }
        }
        if (open_counter>0)
        {
          if (io_plus1)
            delete io_plus1;
          io_plus1 = io->getPlus1();
          start = io_plus1;
          if (io_plus1==NULL)
            return;
        }
      } // end if start/end
    } // end not inverted
  }
}






