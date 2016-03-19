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

#ifndef ICHECKDLGIMPL_H
#define ICHECKDLGIMPL_H

#include <qlabel.h>
//Added by qt3to4:
#include <QPixmap>
#include "ui_ICheckDlg.h"

/**
 * @class ICheckDlgImpl
 * @brief Dialog that displays the integrity check results.
 */
class ICheckDlgImpl : public QDialog
{ 
    Q_OBJECT
        
        Ui::ICheckDlg iCheckDlg;


public:
    ICheckDlgImpl( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, Qt::WFlags fl = 0 );
    ~ICheckDlgImpl();

    void enableCompleteness(bool ec=TRUE) {
      iCheckDlg.lb_completeness_val->setEnabled(ec); iCheckDlg.lb_completeness->setEnabled(ec); };
    void setUnambiguous(bool );
    void setInitial(bool );
    void setFinal(bool );
    void setNoDeadLocks(bool );
    void setStateCodes(bool);
    /// Sets the text of the 'completeness' label (percentage)
    void setComplete(QString s ) { iCheckDlg.lb_completeness_val->setText(s); };
    /// Sets the text of the 'states reachable' label (percentage)
    void setStatesReachable(QString s) { iCheckDlg.lb_statesreachable_val->setText(s); };
    /// Sets the text of the 'end states reachable' label (percentage)
    void setFinalStatesReachable(QString s) { iCheckDlg.lb_endstatesreachable_val->setText(s); };
    /// Sets the text of the 'transitions connected' label (percentage)
    void setTransConnected(QString s) { iCheckDlg.lb_transconnected_val->setText(s); };
    /// Sets the protocol text
    void setProtocolText(QString t) {iCheckDlg.tb_protocol->setText(t);}

private:
    /// Pixmap for successfully checked items (green tick)
    QPixmap* pm_tick;
    /// Pixmap for failed items (red cross)
    QPixmap* pm_cross;
};

#endif // ICHECKDLGIMPL_H
