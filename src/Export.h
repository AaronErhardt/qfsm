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

in method writeHeader:
one of the .latin1() calls did not exist
*/

#ifndef EXPORT_H
#define EXPORT_H

#include <fstream>
#include <qstring.h>
#include <QObject>

 
class Machine;
class Options;
class ScrollView;

/**
 * @class Export
 * @brief Base class for all export classes.
 *
 */

class Export : public QObject
{
  Q_OBJECT

  public:
    Export(Options* opt);
    virtual ~Export();

    //void init(std::ofstream* ,Machine*, QString fn=QString::null, ScrollView* sv=NULL);
    void init(std::ostream* ,Machine*, QString fn=QString::null, ScrollView* sv=NULL);
    /// Does the actual exporting
    virtual void doExport()=0;
    /// Returns the appropriate filter string for the file dialog.
    virtual QString fileFilter()=0;
    /// Verifies if the machine is in a valid form for exporting 
    virtual bool validateMachine(Machine* ) { return TRUE; };
	/// Returns the default file extension
	virtual QString defaultExtension()=0;


  protected:
    /// Output stream 
    //std::ofstream* out;
    std::ostream* out;
    /// Pointer to the machine that shall be exported
    Machine* machine;
    /// Application options
    Options* options;
    /// Output filename (only used for EPS and SVG export)
    QString fileName;
    /// ScrollView pointer (only used for EPS and SVG export);
    ScrollView* scrollview;

    /// Writes a comment to the top of the output stream 
    virtual void writeHeader(QString commentstart, QString commentend="");
};

#endif
