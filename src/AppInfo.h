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

#ifndef APPINFO_H
#define APPINFO_H

#include <qobject.h>
#include <qstring.h>

class MainWindow;

/** 
 * @class AppInfo
 * @brief Provides general information about the application.
 *
 * Stores version and author of the application and a method to
 * display a info dialogbox.
 */

class AppInfo : public QObject
{
  Q_OBJECT
  public:
    AppInfo(QWidget*);

    int getVersionMajor() /// returns major version number. 
      { return version_major; }; 
    int getVersionMinor() /// returns minor version number. 
      { return version_minor; }; 
    /// Returns the version number as a single double value
    double getVersionDouble();
    QString getVersion() /// returns version string.
      { return QString::number(version_major)+"."+QString::number(version_minor); };
	QString getDate() /// returns date string.
	{ return date; };
    QString getAuthor() /// returns author of application
      { return author; }; 

    void about();

  private:
    /// Parent widget (used as parent of the about dialog)
    QWidget* parent_widget;  
    /// Major version number
    int version_major; 
    /// Minor version number
    int version_minor;
    /// Author
    QString author;
	/// Date
	QString date;
};

#endif
