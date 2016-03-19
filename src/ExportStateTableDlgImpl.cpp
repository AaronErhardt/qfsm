#include "ExportStateTableDlgImpl.h"

#include <qcheckbox.h>
#include <q3buttongroup.h>

#include "Options.h"

/* 
 *  Constructs a ExportStateTableDlgImpl which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f' 
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
ExportStateTableDlgImpl::ExportStateTableDlgImpl( QWidget* parent,  const char* name, bool modal, Qt::WFlags fl )
    : QDialog( parent, name, modal, fl )
{
  exportStateTableDlg.setupUi(this);

}

/*  
 *  Destroys the object and frees any allocated resources
 */
ExportStateTableDlgImpl::~ExportStateTableDlgImpl()
{
    // no need to delete child widgets, Qt does it all for us
}

void ExportStateTableDlgImpl::includeOutputsClicked()
{
  includeout = exportStateTableDlg.cb_includeout->isChecked();
}

void ExportStateTableDlgImpl::resolveInvertedClicked()
{
  resolve_inverted = exportStateTableDlg.cb_resolve_invert->isChecked();
  qDebug("%d\n", resolve_inverted);
}

void ExportStateTableDlgImpl::orientationClicked(int id)
{
  orientation = id;
}

/**
 * Initialises the dialog according to the current options @a opt.
 */
void ExportStateTableDlgImpl::init(Options* opt)
{
  includeout = opt->getStateTableIncludeOut();
  exportStateTableDlg.cb_includeout->setChecked(includeout);
  resolve_inverted = opt->getStateTableResolveInverted();
  exportStateTableDlg.cb_resolve_invert->setChecked(resolve_inverted);
  orientation = opt->getStateTableOrientation();
  exportStateTableDlg.bg_orientation->setButton(orientation);
}


