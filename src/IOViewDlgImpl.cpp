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


#include <QCloseEvent>

#include "IOViewDlgImpl.h"
#include "MainWindow.h"

/**
 *  Constructs a IOViewDlgImpl which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f' 
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
IOViewDlgImpl::IOViewDlgImpl( QWidget* parent,  const char* name, bool modal, Qt::WFlags fl )
    : QDialog( parent, name, modal, fl )
{
  ioViewDlg.setupUi(this);

    main = (MainWindow*)parent;

}

/**
 *  Destroys the object and frees any allocated resources
 */
IOViewDlgImpl::~IOViewDlgImpl()
{
}

/**
 * Updates the list.
 * Emits the closing signal and hides the dialog.
 */
void IOViewDlgImpl::updateIOList(Machine*m)
{

  QStringList list;
  QString joinedList;
  QRect dialogGeometry;
  int vertSize=0,horzSize=180;
  QFontMetrics fontSize(QFont("DejaVu Sans",9,400,false));
  content=tr("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
      "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
          "p, li { white-space: pre-wrap; }\n"
          "</style></head><body style=\" font-family:'DejaVu Sans'; font-size:9pt; font-weight:400; font-style:normal;\">\n");




  if(m->getNumInputs()>0)
  {
    list=m->getInputNameList();
    joinedList=list.join(",");

    content+="<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:600;\">Inputs:</span></p>\n";
    content+="<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-weight:600;\"><span style=\" font-weight:400;\">";
    content+=joinedList;
    content+="</span></p>\n";
    vertSize+=40;
    if(horzSize<fontSize.width(joinedList))
      horzSize=fontSize.width(joinedList);
  }

  if(m->getNumOutputs()>0)
  {
    list=m->getOutputNameList();
    joinedList=list.join(",");

    content+="<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:600;\">Mealy Outputs:</span></p>\n";
    content+="<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-weight:600;\"><span style=\" font-weight:400;\">";
    content+=joinedList;
    content+="</span></p>\n";
    vertSize+=40;
    if(horzSize<fontSize.width(joinedList))
      horzSize=fontSize.width(joinedList);
  }

  if(m->getNumMooreOutputs()>0)
  {
    list=m->getMooreOutputList();
    joinedList=list.join(",");

    content+="<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:600;\">Moore Outputs:</span></p>\n";
    content+="<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-weight:600;\"><span style=\" font-weight:400;\">";
    content+=joinedList;
    content+="</span></p>\n";
    vertSize+=40;
    if(horzSize<fontSize.width(joinedList))
      horzSize=fontSize.width(joinedList);
  }

  content+="</body></html>";
  ioViewDlg.textBrowser->setHtml(content);

  dialogGeometry=geometry();
  dialogGeometry.setWidth(horzSize+40);
  dialogGeometry.setHeight(vertSize+40);
  setGeometry(dialogGeometry);
}

/**
 * Is invoked when the window is shown.
 * Updates the text of the text browser.
 */
void IOViewDlgImpl::showEvent(QShowEvent*)
{
    ioViewDlg.textBrowser->setHtml(content);
}


/**
 * Is invoked when the user closes the window.
 * Emits the closing signal and hides the dialog.
 */
void IOViewDlgImpl::closeEvent(QCloseEvent* e)
{
  emit closing();
  e->accept();
}


