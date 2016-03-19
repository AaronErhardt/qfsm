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
/*
Qt 4 Port by Rainer Strobel

changed base class of IOInfoList to QList<IOInfo*>
changed parameters the method compareItems to IOInfo* because
generic items do not exist in Qt 4
*/



#ifndef IOINFOLIST_H
#define IOINFOLIST_H

#include <q3ptrlist.h>
#include <q3ptrcollection.h>
#include "IOInfo.h"
//class IOInfo;

/**
 * @class IOInfoList
 * @brief List of IOInfo objects.
 */
class IOInfoList : public QList<IOInfo*>
{
//  int compareItems(IOInfo* io1, IOInfo* io2);
  public:
    static int compareItems(IOInfo* ci1, IOInfo* ci2);
    static bool lessThan(IOInfo*& ci1, IOInfo*& ci2);
    IOInfoList& operator=(const QList<IOInfo*>& iolist);


    //bool isInverted() { return invert; };
    void setInvert( bool inv );
    
    bool contains(IOInfo *info);

  private:
    bool invert;

};

#endif
