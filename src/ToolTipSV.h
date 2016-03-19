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

The class ToolTipSV now inherits QObject instead of
QScrollView, because the Qt 4 QScrollView class includes
only static methods and it can't be overloaded.

The implementation of the ToolTipSV class has been changed, so
that it calls the static functions of QToolTip
*/

#ifndef TOOLTIPSV_H
#define TOOLTIPSV_H

#include <qtooltip.h>


/**
 * @class ToolTipSV
 * @brief Tooltip for the scroll view.
 */
class ToolTipSV : public QObject
{
  public:
    ToolTipSV(QWidget* parent);

  protected:
    void maybeTip(const QPoint& );
    
  private:
    QWidget *par;
};


#endif

