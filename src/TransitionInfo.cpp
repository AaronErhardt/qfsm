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

#include "TransitionInfo.h"
#include "IOInfo.h"
#include "IOInfoList.h"
#include "Const.h"
#include "IOInfoASCII.h"
#include "IOInfoBin.h"

/// Constructor
TransitionInfo::TransitionInfo()
{
  inputs=NULL;
  outputs=NULL;
  type=Binary;
}

/// Destructor
TransitionInfo::~TransitionInfo()
{
}

/// Returns TRUE if this transition info has common input values with @a ti
bool TransitionInfo::intersection(TransitionInfo* ti)
{
  IOInfo* ioinf;
  bool ret_val=FALSE;
  /*
  unsigned char buf[MAX_CHARARRAY_LENGTH];
  int length;
  */
  QList<IOInfo*> list;

  ioinf = ti->getInputInfo();

  if(ti->getInputInfo()->isDefault() && inputs->isDefault())
    return TRUE;
  else if(ti->getInputInfo()->isDefault() || inputs->isDefault())
    return FALSE;

  if (type==Text && ti->getType()==Text)
  {
    if (inputs->equals(ti->getInputInfo()))
      return TRUE;
  }
  else
  {
    if (type==Text || ti->getType()==Text)  // one is text, the other isn't
      return FALSE;
    else if (type==Binary && ti->getType()==Binary)
    {
      
      IOInfoBin* io1 = (IOInfoBin*)inputs;
      IOInfoBin* io2 = (IOInfoBin*)ioinf;
      IOInfoList l1,l2;
      io1->split(l1,true);
      io2->split(l2,true);



      IOInfoList::const_iterator i1,i2;
      for(i1=l1.constBegin(); i1!=l1.constEnd(); ++i1)
      {
        for(i2=l2.constBegin(); i2!=l2.constEnd(); ++i2)
        {
          if(((IOInfoBin*)(*i1))->getInfo() == ((IOInfoBin*)(*i2))->getInfo())
          {
            while (!l1.isEmpty())
              delete l1.takeFirst();
            while (!l2.isEmpty())
              delete l2.takeFirst();
            return TRUE;
          }
        }
      }
     while (!l1.isEmpty())
       delete l1.takeFirst();
     while (!l2.isEmpty())
       delete l2.takeFirst();
      return FALSE;

    }

    /*
    if (!ioinf->convertToASCII(buf, MAX_CHARARRAY_LENGTH, length, FALSE))
    return FALSE;
    */
    list = ioinf->getSinglesInversion();
    QListIterator<IOInfo*> i(list);

    //for(int i=0; i<length; i++)
    for(; i.hasNext();)
    {
      //IOInfoASCII single(IO_MealyIn, buf[i]);
      IOInfo* single = i.next();
      //if (inputs->matches(&single))
      /*
      qDebug("checking if %s (in %s) matches %s", 
      single->convertToString().latin1(), 
      ioinf->convertToString().latin1(),
      inputs->convertToString().latin1());
      */
      if (inputs->matches(single))
      {
	/*
        qDebug("%s (in %s) matches %s", 
        single->convertToString().latin1(), 
        ioinf->convertToString().latin1(),
        inputs->convertToString().latin1());
	*/
	
	//exit(-1);
        ret_val=true;
        break;
      }
    }

    while (!list.isEmpty())
     delete list.takeFirst();
  }
  return ret_val;
}


