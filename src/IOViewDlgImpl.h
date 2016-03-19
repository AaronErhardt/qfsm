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

#ifndef IOVIEWDLGIMPL_H
#define IOVIEWDLGIMPL_H

#include <QCloseEvent>
#include <QShowEvent>
#include "Machine.h"
#include "ui_IOViewDlg.h"

class MainWindow;


/**
 * @class IOViewDlgImpl
 * @brief IO view dialog
 */
class IOViewDlgImpl : public QDialog
{ 
    Q_OBJECT
        
        Ui::IOViewDlg ioViewDlg;


public:


    IOViewDlgImpl( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, Qt::WFlags fl = 0 );
    ~IOViewDlgImpl();


    void updateIOList(Machine*m);

signals:
    /// Emited when the dialog is about to close
    void closing();

public slots:


private:
    /// Pointer to the main window
    MainWindow* main;
    ///Content of text window
    QString content;

    virtual void closeEvent(QCloseEvent* );
    virtual void showEvent(QShowEvent* );

};

#endif // SIMULATORDLGIMPL_H
