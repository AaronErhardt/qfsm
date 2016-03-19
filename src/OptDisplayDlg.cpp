#include "OptDisplayDlg.h"

#include <qvariant.h>
#include "OptDisplayDlg.ui.h"
/*
 *  Constructs a OptDisplayDlg as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  true to construct a modal dialog.
 */
OptDisplayDlg::OptDisplayDlg(QWidget* parent, const char* name, bool modal, Qt::WindowFlags fl)
    : QDialog(parent, name, modal, fl)
{
    setupUi(this);

}

/*
 *  Destroys the object and frees any allocated resources
 */
OptDisplayDlg::~OptDisplayDlg()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void OptDisplayDlg::languageChange()
{
    retranslateUi(this);
}

