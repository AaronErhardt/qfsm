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

#ifndef IMPORT_H
#define IMPORT_H

#include <fstream>
#include <qstring.h>
#include <QObject>

 
class Project;
class Options;
class ScrollView;
class MainWindow;

/**
 * @class Import
 * @brief Base class for all export classes.
 *
 */

class Import : public QObject
{
  Q_OBJECT

  public:
    Import(Options* opt);
    virtual ~Import();

    void init(std::istream* , MainWindow* main, QString fn=QString::null, ScrollView* sv=NULL);
    /// Does the actual exporting
    virtual Project* doImport()=0;
    /// Returns the appropriate filter string for the file dialog.
    virtual QString fileFilter()=0;
    /// Verifies if the machine is in a valid form for exporting 
    //virtual bool validateMachine(Machine* ) { return TRUE; };
    /// Returns the default file extension
    virtual QString defaultExtension()=0;


  protected:
    /// Input stream 
    std::istream* in;
    /// Pointer to the project that is imported
    Project* project;
    /// Application options
    Options* options;
    /// Input filename 
    QString fileName;
    /// ScrollView pointer 
    ScrollView* scrollview;

};

#endif
