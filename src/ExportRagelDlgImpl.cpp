#include <qcheckbox.h>
#include <qradiobutton.h>
#include <q3buttongroup.h>

#include "ExportRagelDlgImpl.h"
#include "Options.h"

/* 
 *  Constructs a ExportRagelDlgImpl which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f' 
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
ExportRagelDlgImpl::ExportRagelDlgImpl( QWidget* parent,  const char* name, bool modal, Qt::WFlags fl )
    : QDialog( parent, name, modal, fl )
{
  exportRagelDlg.setupUi(this);

  
}

/*  
 *  Destroys the object and frees any allocated resources
 */
ExportRagelDlgImpl::~ExportRagelDlgImpl()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 * public slot
 */
void ExportRagelDlgImpl::createActionClicked()
{
  create_action = exportRagelDlg.cb_actionfile->isChecked();
  exportRagelDlg.bg_lang->setEnabled(create_action);

}

/*
 * public slot
 */
void ExportRagelDlgImpl::langCClicked()
{
  lang_action = 0;
}

/*
 * public slot
 */
void ExportRagelDlgImpl::langJavaClicked()
{
  lang_action = 1;
}

/*
 * public slot
 */
void ExportRagelDlgImpl::langRubyClicked()
{
  lang_action = 2;
}


void ExportRagelDlgImpl::init(Options* opt)
{
  create_action = FALSE; //opt->getRagelCreateAction();
  exportRagelDlg.cb_actionfile->setChecked(create_action);
  lang_action = opt->getRagelLangAction();
  exportRagelDlg.bg_lang->setEnabled(create_action);
  add_default_transitions = opt->getRagelDefaultTransitions();
  exportRagelDlg.cb_adddefault->setChecked(add_default_transitions);

//  bg_lang->setButton(lang_action);
  /*
  bg_lang->setButton(0);
  rb_java->setEnabled(FALSE);
  rb_ruby->setEnabled(FALSE);
  */

}

void ExportRagelDlgImpl::addDefaultTransClicked()
{
  add_default_transitions = exportRagelDlg.cb_adddefault->isChecked();
}

