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

#include "TableBuilder.h"
#include "Machine.h"
#include "State.h"
#include "Options.h"

/// Constructor
TableBuilder::TableBuilder(QObject* parent, Machine* m, Options* opt)
  	     : QObject(parent)
{
  machine = m;
  machine->updateDefaultTransitions();
//  eventlist.setAutoDelete(TRUE);
  machine->getEventList(eventlist, opt);
//  eventlist.sort();
  qSort(eventlist.begin(), eventlist.end(), IOInfoList::lessThan);
//  qDebug("%d", eventlist.count());
  options = opt;
}

/// Destructor
TableBuilder::~TableBuilder()
{
}

/// Returns the body of the table
QString TableBuilder::getBody()
{
  QString result;
  QString srow;
  GState* s;

  if (options->getStateTableOrientation()==0)
  {
    QListIterator<GState*> it(machine->getSList());
    for(; it.hasNext();)
    {
      s = it.next();
      if (!s->isDeleted())
      {
	srow = getRow(s);
	result += srow;
      }
    }
  }
  else
  {
    QListIterator<IOInfo*> it(eventlist);
    for(; it.hasNext();)
    {
      srow = getRow(it.next());
      result += srow;
    }
  }
  return result;
}

