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

#include "MainControl.h"
#include "MainWindow.h"
#include "Const.h"

/// Constructor
MainControl::MainControl(QString lang)
{
//  if (lang==QString::null || lang==0)
  if(lang.isEmpty())
    language = tr("English");
  else
    language = lang;
}


/// Creates a new main window and opens it
void MainControl::newWindow()
{
  MainWindow* w = new MainWindow(this);
  w->setLanguage(language);
  w->show();
}

/// Creates a new main window and opens the file named @a fileName in it
void MainControl::newWindow(const char* fileName)
{
  MainWindow* w = new MainWindow(this);
  w->setLanguage(language);
  w->show();
  w->fileOpenRecent(fileName);
}

/// Closes the main window @a w
void MainControl::quitWindow(MainWindow* w)
{
//  w->hide();
//  w->close();
  if (w->aboutToClose)
    delete w;
}

/// Adds an entry to the MRU file list
void MainControl::addMRUEntry(QString fileName)
{
  QStringList::Iterator it;
//  it = mru_list.find(fileName);

//  if (it != mru_list.end())
//  {
  mru_list.remove(fileName);

  mru_list.prepend(fileName);
  
  if (mru_list.count()>MAX_MRUENTRIES)
  {
    it = mru_list.fromLast();
    if (it != mru_list.end())
      mru_list.remove(it);
  }
}

/// Removes an entry from the MRU file list
void MainControl::removeMRUEntry(QString fileName)
{
  mru_list.remove(fileName);
}


