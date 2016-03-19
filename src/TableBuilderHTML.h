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
*/

#ifndef TABLEBUILDERHTML_H
#define TABLEBUILDERHTML_H

#include "TableBuilder.h"

/**
 * @class TableBuilderHTML
 * @brief Constructs a state table in HTML format.
 */
class TableBuilderHTML : public TableBuilder
{
  Q_OBJECT

  public:
    TableBuilderHTML(QObject* par, Machine* m, Options* opt);
    ~TableBuilderHTML();

    QString getHead();
    QString getFoot();
    QString fileFilter();
	QString defaultExtension();
    QString getCommentStart() { return "<!--"; };
    QString getCommentEnd() { return "-->"; };

  private:
    QString getRow(GState* );
    QString getRow(IOInfo* );
};

#endif
