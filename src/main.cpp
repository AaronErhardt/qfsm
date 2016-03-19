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
/*
Qt 4 Port by Rainer Strobel

added code parts for Windows, which were only enabled, when
the code is compiled for a Windows system.
There, the additional include windows.h is needed and
the WinMain function is used instead of main.
*/

#include <stdlib.h>
#include <iostream>
#include <qtranslator.h>
#include <QApplication>
#include <qstring.h>
#include <qdir.h>
#include <qstringlist.h>
#include <QTextStream>
#include <QMainWindow>
#include <qsettings.h>

/*
#include "Convert.h"
#include "IOInfoASCII.h"
#include "IOInfoList.h"
*/

#if QT_VERSION>=0x030300
  #include <qlocale.h>
#endif
#ifdef WIN32
#include <windows.h>
#endif
#include "MainWindow.h"
#include "MainControl.h"

//using namespace std;

QString loadLanguage(QTranslator* trans);

#ifdef WIN32

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR szCmdLine,int iCmdShow)
{


  LPWSTR*argw;
  char**argv;
  int argc;

  argw = CommandLineToArgvW(GetCommandLineW(),&argc);

  argv=(char**)malloc(sizeof(char*)*(argc+1));
  argv[argc]=NULL;

  for(int c=0; c<argc; c++)
  {
    size_t slen = wcslen(argw[c]) + 1;
    size_t convertedChars = 0;
    argv[c]=(char*)malloc(slen);
#ifdef __STDC_LIB_EXT1__
    wcstombs_s(&convertedChars, argv[c], slen, argw[c], _TRUNCATE);
#else
    convertedChars = wcstombs(argv[c], argw[c], slen);
#endif
  }

#else 
int main(int argc, char** argv)
{
#endif
  //qDebug("%d", QT_VERSION);
  QString lang="";
  QApplication qfsm(argc, argv);

  QTranslator trans(0);
  lang = loadLanguage(&trans);
  qfsm.installTranslator(&trans);

  MainControl control(lang);
  
//  MainWindow wmain;

//  qfsm.setMainWidget(&wmain);
//  wmain.setLanguage(lang);
//  wmain.resize(600, 500);
//  wmain.show();

  /*
  IOInfoList res;
  Convert conv;
  char str[]="ac deghjlmn opqqqaer fo";
  str[13]=5;
  str[14]=0;
  conv.asciiToIOList(str, 23, res);
  QListIterator<IOInfo> it(res);
  for(;it.current(); ++it)
  {
    qDebug("%s", it.current()->convertToString().latin1());
  }
  */
  /*
  IOInfoASCII io(IO_MealyIn, "f");
  IOInfoASCII io2(IO_MealyIn, "a-z");
  IOInfoList list;
  io.split(&io2, list);
  QListIterator<IOInfo> it(list);
  for(;it.current(); ++it)
  {
    qDebug("%s", it.current()->convertToString().latin1());
  }
  */
  
  if (argc<=1)
    control.newWindow();
  else
  {
    for(int i=1; i<argc; i++)
      control.newWindow(argv[i]);
  }



//  QApplication::connect(&qfsm, SIGNAL(lastWindowClosed()), qApp, SLOT(quit()) );

//  QMessageBox::information(NULL, "debug info", "End of initialisation");

 
  return qfsm.exec();

}

/*
void loadLanguage(QTranslator* trans)
{
  QDir dir;
  QStringList flist, list;
  QString fn;
//  int len;

  dir.cd("i18n");
  dir.setNameFilter("*.qm");
  flist = dir.entryList();

  QStringList::Iterator it;

  for (it=flist.begin(); it!=flist.end(); ++it)
  {
    fn = *it;
    if (!trans->load(fn, "i18n"))
      qDebug("Language "+fn+" not loaded.");
//    len = fn.length();
//    fn = fn.left(len-3);
//    list.append(fn);
  }

//  cmb_language->insertStringList(list);
}
*/



QString loadLanguage(QTranslator* trans)
{
  using namespace std;

  QString qfsmpath;
  QDir dir = QDir::home();
  QDir qfsmdir(dir.absPath()+"/.qfsm");
  if (!qfsmdir.exists())
  {
    if (!dir.mkdir(".qfsm"))
      qDebug(".qfsm not created");
//    qDebug(dir.absPath());
  }

  QFile file(qfsmdir.absPath()+"/language");
  QTextStream fin(&file);
  
//  qDebug(file.name());

  if (file.isOpen())
  {
    qDebug("language file already open");
    file.close();
  }

  /*
  if (!file.exists())
  {
    qDebug("language file does not exist");
  }
  */
    
  QString s;

  if (!file.open(QIODevice::ReadOnly))
  {
    qDebug("language file could not be opened.");

#if QT_VERSION>=0x030300
    QLocale loc = QLocale::system();
    switch (loc.language())
    {
      case QLocale::German: s="German"; break;
      case QLocale::French: s="French"; break;
      default: s="English"; break;
    }
    qDebug("Most appropriate system locale: %s", s.latin1());
#else
      //return QString::null;
    QString s_lang, s2;
    s_lang = getenv("LANG"); 
    s2 = s_lang.left(2);
    if (s2=="de")
      s="German";
    else if (s2=="fr")
      s="French";
    else if (s2=="ru")
      s="Russian";
    else
      s="Englisch";
    qDebug("Locale by $LANG: %s", s.latin1());
#endif
  }
  else
  {
    fin >> s;
    qDebug("Locale by language file: %s", s.latin1());
  }


  qfsmpath = getenv("QFSMDIR");
//  QDir dir; //(qfsmpath);
  if (qfsmpath.isEmpty())
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
    qfsmpath = dir.absolutePath();
#else
    qfsmpath = QFSM_LANGUAGE_DIR;
    dir = QDir(qfsmpath); //QDir::current();
#endif
    qDebug("Looking for language files in %s", qfsmpath.latin1());
//	QMessageBox::information(NULL, "debug info", qfsmpath);
  }
  else
  {
    dir = QDir(qfsmpath); //QDir::current();
    if (!dir.cd("po"))
		dir.cd(QFSM_LANGUAGE_DIR);
  }

  if (dir.exists())
    trans->load(s+".qm", dir.absPath());


  file.close();

  return s;
}


