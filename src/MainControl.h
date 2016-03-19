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

in constructor of MainControl:
changed request whether ins null or empty to .isEmpty()
*/

#ifndef MAINCONTROL_H
#define MAINCONTROL_H

#include <QObject>
#include <q3ptrlist.h>
#include <qstring.h>
#include <qstringlist.h>

class MainWindow;

/**
 * @class MainControl
 * @brief Top level object that controls all open main windows.
 *
 * It also holds a list of the most recently used files.
 */
class MainControl : public QObject
{
  Q_OBJECT

  public:
    MainControl(QString lang);
    void addMRUEntry(QString fileName);
    void removeMRUEntry(QString fileName);
    /// Returns the MRU file list
    QStringList& getMRUList() { return mru_list; }

  private:
    /// Language
    QString language;
    /// List of main windows
    QList<MainWindow*> window_list;
    /// List of most recently used files
    QStringList mru_list;

  public slots:
    void newWindow();
    void newWindow(const char* fileName);
    void quitWindow(MainWindow*);
};  


#endif
