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

#ifndef EXPORTAHDLDLGIMPL_H
#define EXPORTAHDLDLGIMPL_H
#include "ui_ExportAHDLDlg.h"

class Options;

class ExportAHDLDlgImpl : public QDialog
{
    Q_OBJECT

        Ui::ExportAHDLDlg exportAHDLDlg;

public:
    ExportAHDLDlgImpl( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, Qt::WFlags fl = 0 );
    ~ExportAHDLDlgImpl();

    /// Returns the 'synchronous reset' flag 
    bool getSyncReset() { return sync_reset; };
    /// Sets the 'synchronous reset' flag 
    void setSyncReset(bool sr) { sync_reset = sr; };
    /// Returns the 'use moore outputs' flag 
    bool getUseMoore() { return use_moore; };
    /// Sets the 'use moore outputs' flag 
    void setUseMoore(bool um) { use_moore = um; };

    void init(Options* opt);

public slots:
    void syncResetClicked();
    void useMooreClicked();

private:
    /// If TRUE use synchronous reset, otherwise asynchronous reset
    bool sync_reset;
    /// If TRUE use moore outputs, otherwise use only state code
    bool use_moore;
};

#endif // EXPORTAHDLDLGIMPL_H
