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

added #include <QFont>
*/

#ifndef PROJECT_H
#define PROJECT_H

#include <qobject.h>
#include <qdom.h>
#include <QFont>

class Machine;
class MainWindow;
class UndoBuffer;
class GObject;


/**
 * @class Project
 * @brief Stores project information.
 */
class Project : public QObject
{
  Q_OBJECT
  public:
    Project(QObject* parent=NULL, const char* name=0);
    ~Project();

    void addMachine(QString, QString, QString, QString, int type, int numbits, QString, int, QString, int, 
	QString,  QFont , QFont, int , bool draw_it);
    void addMachine(Machine* m);

    /// Returns TRUE if the project has changed otherwise FALSE
    bool hasChanged() { return changed; };
    /** If @a ch is TRUE marks the project as changed otherwise marks it as
      unchanged */
    void setChanged(bool ch = TRUE) { changed=ch; };
    /// Returns the undo buffer
    UndoBuffer* getUndoBuffer() { return undobuffer; };
    /// Returns the main window
    MainWindow* getMain() { return main; };

    QDomDocument getDomDocument(bool onlyselected=FALSE, GObject* obj=NULL);

    /// Machine (projects can currently contain only a single machine)
    Machine* machine;

  private:
    /// Pointer to the main window
    MainWindow* main;
    /// Undo buffer
    UndoBuffer* undobuffer;
    /// If TRUE, the project has been changed
    bool changed;
};


#endif
