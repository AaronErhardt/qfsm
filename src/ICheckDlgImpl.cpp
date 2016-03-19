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

#include <qpixmap.h>
#include "ICheckDlgImpl.h"
#include "../pics/cross.xpm"
#include "../pics/tick.xpm"


/** 
 *  Constructs a ICheckDlgImpl which is a child of @a parent, with the 
 *  name @a name and widget flags set to @a f 
 *
 *  The dialog will by default be modeless, unless you set @a modal to
 *  TRUE to construct a modal dialog.
 */
ICheckDlgImpl::ICheckDlgImpl( QWidget* parent,  const char* name, bool modal, Qt::WFlags fl )
    : QDialog( parent, name, modal, fl )
{
  pm_tick = new QPixmap((const char**)tick_xpm);
  pm_cross = new QPixmap((const char**)cross_xpm);
  
  iCheckDlg.setupUi(this);
}

/**  
 *  Destroys the object and frees any allocated resources
 */
ICheckDlgImpl::~ICheckDlgImpl()
{
  delete pm_tick;
  delete pm_cross;
}

/// Sets/Clears the 'unambigous' status
void ICheckDlgImpl::setUnambiguous(bool b)
{
  if (b)
    iCheckDlg.pm_unambcond->setPixmap(*pm_tick);
  else
    iCheckDlg.pm_unambcond->setPixmap(*pm_cross);
}


/// Sets/Clears the 'initial state' status
void ICheckDlgImpl::setInitial(bool b)
{
  if (b)
    iCheckDlg.pm_startstate->setPixmap(*pm_tick);
  else
    iCheckDlg.pm_startstate->setPixmap(*pm_cross);
}


/// Sets/Clears the 'end state' status
void ICheckDlgImpl::setFinal(bool b)
{
  if (b)
    iCheckDlg.pm_endstate->setPixmap(*pm_tick);
  else
    iCheckDlg.pm_endstate->setPixmap(*pm_cross);
}


/// Sets/Clears the 'no deadlocks' status
void ICheckDlgImpl::setNoDeadLocks(bool b)
{
  if (b)
    iCheckDlg.pm_deadlocks->setPixmap(*pm_tick);
  else
    iCheckDlg.pm_deadlocks->setPixmap(*pm_cross);
}


/// Sets/Clears the 'unambiguous state codes' status
void ICheckDlgImpl::setStateCodes(bool b)
{
  if (b)
    iCheckDlg.pm_statecodes->setPixmap(*pm_tick);
  else
    iCheckDlg.pm_statecodes->setPixmap(*pm_cross);
}



