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

#ifndef EXPORTVVVVDLGIMPL_H
#define EXPORTVVVVDLGIMPL_H

#include "ui_ExportVVVVDlg.h"

class Options;
class Machine;

class ExportVVVVDlgImpl : public QDialog
{
    Q_OBJECT
    Ui::ExportVVVVDlg exportVVVVDlg;

public:
    ExportVVVVDlgImpl( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, Qt::WFlags fl = 0 );
    ~ExportVVVVDlgImpl();

    void init(Options* opt, Machine* m);

    /// Returns the reset option
    bool getVVVVReset() { return vvvv_reset; };
    /// Sets the reset option
    void setVVVVReset(bool vr) { vvvv_reset = vr; };
    /// Returns the vvvv reset event name
    QString getVVVVResetEvent() { reset_event.replace(QRegExp(" "), "_"); return reset_event; }
    /// Sets the vvvv reset event name
    void setVVVVResetEvent(QString re) { reset_event = re; }
    /// Returns the vvvv reset action name
    QString getVVVVResetAction() { reset_action.replace(QRegExp(" "), "_"); return reset_action; }
      /// Sets the vvvv reset action name
    void setVVVVResetAction(QString ra) { reset_action = ra; }

    void setText(QString s);

signals:
    void updateCode();

public slots:
    void resetClicked();
    //void updateCode();
    void resetEventChanged();
    void resetActionChanged();

private:    
    Options* options;
    bool vvvv_reset;
    QString reset_event;
    QString reset_action;

};

#endif

