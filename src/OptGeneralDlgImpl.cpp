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

#include <stdlib.h>
#include <qdir.h>
#include <qstringlist.h>
#include <qsettings.h>

#include "OptGeneralDlgImpl.h"

/**
 *  Constructs a OptGeneralDlgImpl which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f' 
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
OptGeneralDlgImpl::OptGeneralDlgImpl( QWidget* parent,  const char* name, bool modal, Qt::WFlags fl )
    : QDialog( parent, name, modal, fl )
{
  optGeneralDlg.setupUi(this);

}

/**  
 *  Destroys the object and frees any allocated resources
 */
OptGeneralDlgImpl::~OptGeneralDlgImpl()
{
}

/// Returns the language set in the combo box
QString OptGeneralDlgImpl::getLanguage()
{ 
  QString tmp;
  if (optGeneralDlg.cmb_language->count()==0)
    return "English";

  tmp = optGeneralDlg.cmb_language->currentText(); 
  return tmp;
}


/**
 * Sets the language @a s in the combo box.
 */
void OptGeneralDlgImpl::setLanguage(QString s)
{
  QString tmp;

  for (int i=0; i<optGeneralDlg.cmb_language->count(); i++)
  {
    tmp = optGeneralDlg.cmb_language->text(i);
    if (tmp==s)
      optGeneralDlg.cmb_language->setCurrentItem(i);
  }
}

/**
 * Initialises the dialog with the current language
 */
void OptGeneralDlgImpl::init()
{
  QDir dir;
  QStringList flist, list;
  QString fn;
  int len;

  QString apppath=getenv("QFSMDIR");
  if (apppath.isEmpty())
  {
    qDebug("$QFSMDIR not set!");
#ifdef WIN32
	QString tmppath;
	QSettings settings("HKEY_LOCAL_MACHINE\\Software\\Qfsm", QSettings::NativeFormat);
	tmppath = settings.value("Install_Dir", QVariant("-1")).toString();
	qDebug("tmppath: %s", tmppath.latin1());
	if (tmppath=="-1")
		dir = QDir::current();
	else
		dir.cd(tmppath);
//	dir.cdUp();
	dir.cd(QFSM_LANGUAGE_DIR);
	apppath = dir.absolutePath();
#else
    apppath = QFSM_LANGUAGE_DIR;
    dir = QDir(apppath); //QDir::current();
#endif
    qDebug("Looking for language files in %s", apppath.latin1());
  }
  else
  {
    dir = QDir(apppath); //QDir::current();
    if (!dir.cd("po"))
		dir.cd(QFSM_LANGUAGE_DIR);
  }
  dir.setNameFilter("*.qm");
  flist = dir.entryList();

  optGeneralDlg.cmb_language->clear();

  QStringList::Iterator it;

  for (it=flist.begin(); it!=flist.end(); ++it)
  {
    fn = *it;
    len = fn.length();
    fn = fn.left(len-3);
    list.append(fn);
    qDebug(fn);
  }

  if (list.count()>0)
    optGeneralDlg.cmb_language->insertStringList(list);
}
