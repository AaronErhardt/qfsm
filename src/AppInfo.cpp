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

#include <qmessagebox.h>
#include <QIcon>

#include "AppInfo.h"


/**
 * Constructor.
 * Initialises the AppInfo object by setting version und author.
 * @param par parent widget.
 */
AppInfo::AppInfo(QWidget* par)
	:QObject(par)
{
  parent_widget = par;
  version_major = 0;

  version_minor = 54;
  date = "2015-01-01";
  author = "Stefan Duffner, Rainer Strobel";
}

double AppInfo::getVersionDouble()
{
  double dec;
  double res;

  dec = version_minor;
  while (dec>1)
    dec /= 10;

  res = dec + version_major;

  return res;
}
 
/**
 * Display about-dialogbox.
 */
void AppInfo::about()
{
  QString text;
  text = tr("Qfsm - A graphical tool for designing and simulating "
      	    "finite state machines")+"\n";
  text += tr("Version %1.%2").arg(version_major).arg(version_minor)+"\n";
  text += tr("Development version %1").arg(date)+"\n";
  text += tr("Copyright 2000-2015 by ")+ author+"\n";
  text += tr("email: qfsm@duffner-net.de");

  //QMessageBox::about(parent_widget, tr("Qfsm"), text);

  QMessageBox mbox(parent_widget);

  mbox.setIconPixmap(parent_widget->windowIcon().pixmap(64.64));
  mbox.setCaption(tr("About Qfsm"));
  mbox.setText(text);
  mbox.exec();
}
