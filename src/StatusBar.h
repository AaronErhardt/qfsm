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

#ifndef STATUSBAR_H
#define STATUSBAR_H

#include <qstatusbar.h>
#include <qlabel.h>


/**
 * @class StatusBar
 * @brief Class for handling the statusbar of the main window.
 */
class StatusBar : public QStatusBar
{
  Q_OBJECT
  public:
    StatusBar(QWidget* =NULL, const char* =0);
    ~StatusBar();

    void setSelected(int sel);
    void setPosition(double x, double y);

  private:
    /// Label showing the number of selected objects
    QLabel* selected;
    /// Label showing the current zoom factor
    QLabel* zoom;
    /// Label showing the current mouse cursor position
    QLabel* position;
    /// Label showing messages
    QLabel* lmessage;

  public slots:
    void setZoom(int z);
};




#endif
