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

#ifndef MACHINEMANAGER_H
#define MACHINEMANAGER_H

#include <qobject.h>

//class DMachineProperties;
class MachinePropertiesDlgImpl;
class MainWindow;
class Project;


/**
 * @class MachineManager
 * @brief Control class for machines in a project.
 */
class MachineManager : public QObject
{
  Q_OBJECT
  public:
    MachineManager(QObject* parent=NULL, const char* name=0);
    ~MachineManager();

    int addMachine(Project* );
    void editMachine(Project* );

  private:
    /// Pointer to the main window
    MainWindow* main;
    /// Machine properties dialog
    MachinePropertiesDlgImpl* machine_props;

};



#endif
