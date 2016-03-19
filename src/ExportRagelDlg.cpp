#include "ExportRagelDlg.h"

#include <qvariant.h>
#include <qimage.h>
#include <qpixmap.h>

/*
 *  Constructs a ExportRagelDlg as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  true to construct a modal dialog.
 */
ExportRagelDlg::ExportRagelDlg(QWidget* parent, const char* name, bool modal, Qt::WindowFlags fl)
    : QDialog(parent, name, modal, fl)
{
    setupUi(this);

}

/*
 *  Destroys the object and frees any allocated resources
 */
ExportRagelDlg::~ExportRagelDlg()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void ExportRagelDlg::languageChange()
{
    retranslateUi(this);
}

void ExportRagelDlg::createActionClicked()
{
    qWarning("ExportRagelDlg::createActionClicked(): Not implemented yet");
}

void ExportRagelDlg::langCClicked()
{
    qWarning("ExportRagelDlg::langCClicked(): Not implemented yet");
}

void ExportRagelDlg::langJavaClicked()
{
    qWarning("ExportRagelDlg::langJavaClicked(): Not implemented yet");
}

void ExportRagelDlg::langRubyClicked()
{
    qWarning("ExportRagelDlg::langRubyClicked(): Not implemented yet");
}

