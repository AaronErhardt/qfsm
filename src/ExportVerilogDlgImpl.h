/*
Copyright (C) Stefan Duffner 

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

#ifndef EXPORTVERILOGDLGIMPL_H
#define EXPORTVERILOGDLGIMPL_H
#include "ui_ExportVerilogDlg.h"

class Options;

class ExportVerilogDlgImpl : public QDialog
{
    Q_OBJECT
        
        Ui::ExportVerilogDlg exportVerilogDlg;


public:
    ExportVerilogDlgImpl( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, Qt::WFlags fl = 0 );
    ~ExportVerilogDlgImpl();

    /// Returns the 'synchronous reset' flag 
    bool getSyncReset() { return sync_reset; };
    /// Sets the 'synchronous reset' flag 
    void setSyncReset(bool sr) { sync_reset = sr; };
    /*
    /// Returns the 'register mealy outputs' flag 
    bool getRegisterOut() { return register_out; };
    /// Sets the 'register mealy outputs' flag 
    void setRegisterOut(bool ro) { register_out = ro; };
    */

    void init(Options* opt);

public slots:
    void syncResetClicked();
    //void registerOutClicked();

private:
    bool sync_reset;
    //bool register_out;
};

#endif // EXPORTVERILOGDLGIMPL_H
