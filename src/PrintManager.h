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

#ifndef PRINTMANAGER_H
#define PRINTMANAGER_H

#include <qobject.h>

class QWidget;
class QPrinter;
class MainWindow;
class Draw;


/**
 * @class PrintManager
 * @brief Control class for printing.
 */
class PrintManager : public QObject
{
  Q_OBJECT
  public:
    PrintManager(QWidget* );
    ~PrintManager();

    void print();

  private:
    /// Pointer to the main window
    MainWindow* main;
    /// QPrinter object
    QPrinter* printer;
    /// Draw object
    Draw* draw;
};


#endif
