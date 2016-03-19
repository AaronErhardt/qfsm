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

#include <qcheckbox.h>

#include "ExportVerilogDlgImpl.h"
#include "Options.h"

/* 
 *  Constructs a ExportVerilogDlgImpl which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f' 
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
ExportVerilogDlgImpl::ExportVerilogDlgImpl( QWidget* parent,  const char* name, bool modal, Qt::WFlags fl )
    : QDialog( parent, name, modal, fl )
{
  exportVerilogDlg.setupUi(this);

}

/*  
 *  Destroys the object and frees any allocated resources
 */
ExportVerilogDlgImpl::~ExportVerilogDlgImpl()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 * public slot
 */
void ExportVerilogDlgImpl::syncResetClicked()
{
  sync_reset = exportVerilogDlg.cb_synchreset->isChecked();
}

/*
void ExportVerilogDlgImpl::registerOutClicked()
{
  register_out = cb_registerout->isChecked();
}
*/

/**
 * Initialises the dialog according to the current options @a opt.
 */
void ExportVerilogDlgImpl::init(Options* opt)
{
  sync_reset = opt->getVerilogSyncReset();
  exportVerilogDlg.cb_synchreset->setChecked(sync_reset);
  /*
  register_out = opt->getVerilogRegisterOut();
  cb_registerout->setChecked(register_out);
  */
}
