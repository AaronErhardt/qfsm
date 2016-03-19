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

removed constructor of struct dtlist, which disables the AutoDelete feature
of QList. In Qt 4, this feature does no longer exist.
replaced Qt 3 interator through Qt 4 iterators
*/

#ifndef EDIT_H
#define EDIT_H

#include <qobject.h>
#include <qstring.h>

class Selection;
class Machine;
class Project;

/**
 * @class Edit
 * @brief Class providing various editing features.
 *
 */
class Edit : public QObject
{
  Q_OBJECT
  public:
    Edit(QWidget* parent=0, const char* name=0);

    void deleteSelection(Selection* , Machine* );
    bool copy(Selection*, Project*, Machine*, QString& data);
    bool paste(Selection*, Project*, Machine*, QString data);
};


#endif
