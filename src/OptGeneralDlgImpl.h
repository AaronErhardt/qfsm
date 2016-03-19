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

if(!QString) replaced by if(QString.isEmpty())
*/

#ifndef OPTGENERALDLGIMPL_H
#define OPTGENERALDLGIMPL_H

#include <qcombobox.h>
#include "ui_OptGeneralDlg.h"

/**
 * @class OptGeneralDlgImpl
 * @brief Tab dialog for the general options.
 */
class OptGeneralDlgImpl : public QDialog
{ 
    Q_OBJECT
        
        Ui::OptGeneralDlg optGeneralDlg;

public:
    OptGeneralDlgImpl( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, Qt::WFlags fl = 0 );
    ~OptGeneralDlgImpl();

    void init();
    QString getLanguage();
    void setLanguage(QString s); 

};



#endif // OPTGENERALDLGIMPL_H
