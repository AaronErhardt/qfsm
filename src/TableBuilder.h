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

replaced Qt 3 iterators by Qt 4 iterators

in constructor:
removed setAutoDelete
changed sort call to qSort(..)

*/

#ifndef TABLEBUILDER_H
#define TABLEBUILDER_H

#include <qstring.h>
#include <qobject.h>

#include "GState.h"
#include "IOInfoList.h"

class Machine;
class State;
class Options;

/**
 * @class TableBuilder
 * @brief Base class for all classes that build state tables.
 *
 */
class TableBuilder : public QObject
{
  Q_OBJECT

  public:
    TableBuilder(QObject* parent, Machine* m, Options* opt);
    virtual ~TableBuilder();
    /// Returns the head of the table
    virtual QString getHead()=0;
    /// Returns the foot of the table
    virtual QString getFoot()=0;
    virtual QString getBody();
    /// Returns the file filter to use for the file dialog
    virtual QString fileFilter()=0;
	/// Returns the default file extension
	virtual QString defaultExtension()=0;
    /// Returns the comment start string
    virtual QString getCommentStart()=0;
    /// Returns the comment end string
    virtual QString getCommentEnd()=0;

  protected:
    /// Returns a row of the table corresponding to the state @a s
    virtual QString getRow(GState* s)=0;
    virtual QString getRow(IOInfo* io)=0;

    /// List of events (columns of the table)
    IOInfoList eventlist;
    /// Pointer to the machine
    Machine* machine;
    /// Pointer to the application options
    Options* options;
}; 



#endif

