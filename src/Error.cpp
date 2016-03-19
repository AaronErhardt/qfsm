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

#include "Error.h"


/// Constructor
Error::Error()
{
}

/**
 * Displays an information message box.
 * @param text text to be displayed.
 * @return return value of the message box
 */

int Error::info(QString text)
{
  return QMessageBox::information(NULL, "Qfsm", text);
}


/**
 * Displays an warning message box with Ok and Cancel button.
 * @param text text to be displayed.
 * @return return value of message box
 */
int Error::warningOkCancel(QString text)
{
  return QMessageBox::warning(NULL, "Qfsm", text, 
    QMessageBox::Ok | QMessageBox::Default, 
    QMessageBox::Cancel | QMessageBox::Escape);
}

/**
 * Displays an warning message box with Ok button.
 * @param text text to be displayed.
 * @return return value of message box
 */
int Error::warningOk(QString text)
{
  return QMessageBox::warning(NULL, "Qfsm", text, 
    QMessageBox::Ok | QMessageBox::Default, QMessageBox::NoButton);
}



