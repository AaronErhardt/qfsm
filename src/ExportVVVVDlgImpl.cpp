#include "ExportVVVVDlgImpl.h"
#include "Options.h"

ExportVVVVDlgImpl::ExportVVVVDlgImpl( QWidget* parent,  const char* name, bool modal, Qt::WFlags fl )
:QDialog(parent)
{
  //load ui design for the current object
  exportVVVVDlg.setupUi(this);

  exportVVVVDlg.pb_update->setVisible(FALSE);
  //connect(exportVVVVDlg.pb_update, SIGNAL(clicked()), this, SIGNAL(updateClicked()));
}

/*  
 *  Destroys the object and frees any allocated resources
 */
ExportVVVVDlgImpl::~ExportVVVVDlgImpl()
{
    // no need to delete child widgets, Qt does it all for us
}

void ExportVVVVDlgImpl::init(Options* opt, Machine* m)
{
  options = opt;
  vvvv_reset = opt->getVVVVReset();
  reset_event = opt->getVVVVResetEvent();
  reset_action = opt->getVVVVResetAction();
  exportVVVVDlg.cb_reset->setChecked(vvvv_reset);
  exportVVVVDlg.le_reset_event->setEnabled(vvvv_reset);
  exportVVVVDlg.le_reset_event->setText(opt->getVVVVResetEvent());
  exportVVVVDlg.le_reset_action->setEnabled(vvvv_reset);
  exportVVVVDlg.le_reset_action->setText(opt->getVVVVResetAction());
}

void ExportVVVVDlgImpl::resetClicked()
{
  vvvv_reset = exportVVVVDlg.cb_reset->isChecked();
  exportVVVVDlg.le_reset_event->setEnabled(vvvv_reset);
  exportVVVVDlg.le_reset_action->setEnabled(vvvv_reset);
  emit updateCode();
}

/*
void ExportVVVVDlgImpl::updateCode()
{
}
*/

void ExportVVVVDlgImpl::resetEventChanged()
{
  reset_event = exportVVVVDlg.le_reset_event->text();
  options->setVVVVResetEvent(reset_event);
  emit updateCode();
}

void ExportVVVVDlgImpl::resetActionChanged()
{
  reset_action = exportVVVVDlg.le_reset_action->text();
  options->setVVVVResetAction(reset_action);
  emit updateCode();
}



void ExportVVVVDlgImpl::setText(QString s)
{
  exportVVVVDlg.tb_output->setText(s);
}

