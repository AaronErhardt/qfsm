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

#include <qwidget.h>
#include <QFileDialog>
#include <q3textstream.h>
#include <qcolor.h>
#include <qmap.h>
#include <qdom.h>

#include "FileIO.h"
#include "Project.h"
#include "GState.h"
#include "Machine.h"
#include "AppInfo.h"
#include "TransitionInfoBin.h"
#include "TransitionInfoText.h"
#include "Convert.h"
#include "MainWindow.h"
#include "Import.h"
#include "Export.h"
#include "IOInfoASCII.h"
#include "IOInfoText.h"
#include "TransitionInfoASCII.h"
#include "XMLHandler.h"
#include "Error.h"


/**
 * Constructor.
 * Initialises the FileIO object with the parent @a parent.
 */
FileIO::FileIO(QWidget* parent)
      : QObject(parent)
{
 
//  filedlg = new Q3FileDialog(act_dir.dirName(), "Finite State Machine (*.fsm)", 
//    parent, "filedlg", TRUE);
//  filedlg->setMode(Q3FileDialog::AnyFile);
  filedlg = new QFileDialog (parent,"",act_dir.dirName(), "Finite State Machine (*.fsm)" );
  filedlg->setFileMode(QFileDialog::AnyFile);
  filedlg->setAcceptMode(QFileDialog::AcceptSave);
  filedlg->setConfirmOverwrite(FALSE);

  
  importdlg = new QFileDialog (parent,"",act_dir.dirName(), "" );
  importdlg->setFileMode(QFileDialog::AnyFile);
  importdlg->setAcceptMode(QFileDialog::AcceptSave);
  importdlg->setConfirmOverwrite(FALSE);

//  exportdlg = new Q3FileDialog(act_dir.dirName(), QString::null, parent, "exportdlg", TRUE);
//  exportdlg->setMode(Q3FileDialog::AnyFile);
  exportdlg = new QFileDialog (parent,"",act_dir.dirName(), "" );
  exportdlg->setFileMode(QFileDialog::AnyFile);
  exportdlg->setAcceptMode(QFileDialog::AcceptSave);
  exportdlg->setConfirmOverwrite(FALSE);
  
    
  mb_statecode = new QMessageBox("qfsm", 
    tr("The file cannot be saved because of incorrect state codes. Do you want to correct that?"), 
    QMessageBox::Critical, 
    QMessageBox::Yes | QMessageBox::Default,
    QMessageBox::No, 
    QMessageBox::Cancel | QMessageBox::Escape);
  mb_statecode->setButtonText(QMessageBox::Yes, tr("Yes"));
  mb_statecode->setButtonText(QMessageBox::No, tr("No"));
  mb_statecode->setButtonText(QMessageBox::Cancel, tr("Cancel"));

  act_file = QString::null;
  act_exportfile = QString::null;
  act_export_dir = QString::null;
  main = (MainWindow*)parent;

}


/// Destructor
FileIO::~FileIO()
{
  delete filedlg;
  delete importdlg;
  delete exportdlg;
  delete mb_statecode;
}


/**
 * Opens a 'fsm'-file. DEPRECATED!
 * Asks for a file name and opens the specified 'fsm'-file.
 */ 
//Project* FileIO::openFile(QString mrufile /*=QString::null*/)
/*
{
  Project* p=NULL;
//  filedlg->setMode(Q3FileDialog::ExistingFile);
  filedlg->setAcceptMode(QFileDialog::AcceptOpen);
  filedlg->setFileMode(QFileDialog::ExistingFile);

  if (mrufile.isNull())
  {
    if (!filedlg->exec())
    {
      act_file = QString::null;
      return p;
    }
    act_file = filedlg->selectedFile();
  }
  else
    act_file = mrufile;

  QFile file(act_file);
  if (!file.open(QIODevice::ReadOnly))
    return NULL;

  Q3TextStream s(&file);

  int version_major, version_minor;
  QString mname, mversion, mauthor, mdescription;
  int mtype, numbits, numin, numout, initial;
  int num_states;
  int scode;
  QString str_moore;
  IOInfo* smoore;
  QString sname, sdescription;
  double xpos, ypos;
  double c1x, c1y, c2x, c2y;
  double endx, endy;
  int radius, linewidth;
  unsigned int pencolor, brushcolor;
  QString sfamily, tfamily;
  int spointsize, tpointsize;
  int dest_code, anz, type;
  QString in, out;
  QString tdescription;
  int straight;
  GState *state, *dest_state;
  Convert conv;
  TransitionInfo* info=NULL;
  Machine* m;
  int arrowtype;
  QString inames, onames, onamesm;
  int endstate;

  s >> version_major;
  s >> version_minor;
  s.readLine();
  mname = s.readLine();
  mversion = s.readLine();
  mauthor = s.readLine();
  mdescription = s.readLine();
  s >> mtype >> numbits >> numin >> numout;
  if (mtype==Ascii)
  {
    numbits=32;
    numin=8;
    numout=8;
  }
  s.readLine();
  onamesm = s.readLine();
  inames = s.readLine();
  onames = s.readLine();
  s >> num_states;
  s >> initial;
  s.readLine();
  sfamily = s.readLine(); 
  spointsize = s.readLine().toInt();
  tfamily = s.readLine(); 
  tpointsize = s.readLine().toInt();
  s >> arrowtype;
  QFont sfont(sfamily, spointsize);
  QFont tfont(tfamily, tpointsize);

  p = new Project(main);
  p->addMachine(mname, mversion, mauthor, mdescription, mtype, numbits, onamesm, numin, inames, numout, onames, sfont, tfont, arrowtype, TRUE);
  m = p->machine;

  for (int i=0; i<num_states; i++)
  {
    s >> scode;
    s >> str_moore;

    if (m->getType()==Binary)
    {
      //smoore = conv.binStrToX10(numbits, str_moore);
      smoore = new IOInfoBin(IO_MooreOut);
      smoore->setBin(str_moore, numbits);
    }
    else if (m->getType()==Ascii)
      smoore = new IOInfoASCII(IO_MooreOut, str_moore);
    else
      smoore = new IOInfoText(IO_MooreOut, str_moore);


    s.readLine();
    sname=s.readLine();
    sdescription=s.readLine();
    s >> xpos >> ypos >> radius;
    s >> pencolor >> linewidth;
    s >> brushcolor;
    s >> endstate;

    QColor pcol((QRgb)pencolor);
    QColor bcol((QRgb)brushcolor);
    QPen pen(pcol, linewidth );
    QBrush brush(bcol);

    m->addState(sname, sdescription, scode, smoore, xpos, ypos, radius, 1.0, pen, 
	bool(endstate));
  }
  
  state = m->getState(initial);
  if (state)
    m->setInitialState(state);
  else
    m->setInitialState(m->getSList().first());

  for(int ii=0; ii<num_states; ii++)
  {
    s >> scode;
    state = m->getState(scode);
    s >> anz;
    for (int j=0; j<anz; j++)
    {
      s >> dest_code;
      if (dest_code==-1)
	dest_state=NULL;
      else
	dest_state = m->getState(dest_code);
      s >> type;
      s >> tdescription;
      s >> in >> out;
      s >> xpos >> ypos >> c1x >> c1y >> c2x >> c2y >> endx >> endy;
      s >> straight;

      if (type == Binary)
      {
        IOInfoBin bin(IO_MealyIn), bout(IO_MealyOut);

	bin = conv.binStrToX10(numin, in, IO_MealyIn);
       
	if (out!="<noout>")
	{
	  bout = conv.binStrToX10(numout, out, IO_MealyOut);
	}

	info = new TransitionInfoBin(bin,bout);
      }
      else if (type == Ascii)
      {
	if (out=="<noout>")
	  out="";

        IOInfoASCII ain(IO_MealyIn, in), aout(IO_MealyOut, out);

	info = new TransitionInfoASCII(ain, aout);
      }
      else
      {
	if (out=="<noout>")
	  out="";

        IOInfoText tin(IO_MealyIn, in), tout(IO_MealyOut, out);

	info = new TransitionInfoText(tin, tout);
      }
      
      if (state)
      {
	state->addTransition(p, dest_state, info, xpos, ypos, endx, endy,
	  c1x, c1y, c2x, c2y, tdescription, (bool)straight);
      } 
    }
  }

  // phantom state
  state = m->getPhantomState();
  s >> anz;
  for (int j=0; j<anz; j++)
  {
    s >> dest_code;
    if (dest_code==-1)
      dest_state=NULL;
    else
      dest_state = m->getState(dest_code);
    s >> type;
    s >> tdescription;
    s >> in >> out;
    s >> xpos >> ypos >> c1x >> c1y >> c2x >> c2y >> endx >> endy;
    s >> straight;

    if (type == Binary)
    {
      IOInfoBin bin(IO_MealyIn), bout(IO_MealyOut);

      bin = conv.binStrToX10(numin, in, IO_MealyIn);
      bout = conv.binStrToX10(numout, out, IO_MealyOut);
      
      info = new TransitionInfoBin(bin,bout);
    }
    else if (type == Ascii)
    {
      IOInfoASCII ain(IO_MealyIn, in), aout(IO_MealyOut, out);

      info = new TransitionInfoASCII(ain, aout);
    }
    else
    {
      IOInfoText tin(IO_MealyIn, in), tout(IO_MealyOut, out);

      info = new TransitionInfoText(tin, tout);
    }
    
    if (state)
    {
      state->addTransition(p, dest_state, info, xpos, ypos, endx, endy,
	c1x, c1y, c2x, c2y, tdescription, (bool)straight);
    } 
  }       
  m->calcCanvasSize();   

  file.close();

  return p;
}
*/



/**
 * Opens a 'fsm'-file.
 * Opens the '.fsm' file @a mrufile. 
 * If @a mrufile is null a file dialog is opened first.
 */ 
Project* FileIO::openFileXML(QString mrufile /*=QString::null*/)
{
  Project* p=NULL;
//  filedlg->setMode(Q3FileDialog::ExistingFile);
  filedlg->setAcceptMode(QFileDialog::AcceptOpen);
  filedlg->setFileMode(QFileDialog::ExistingFile);

  if (mrufile.isNull())
  {
    if (!filedlg->exec())
    {
      act_file = QString::null;
      return p;
    }
    act_file = filedlg->selectedFile();
  }
  else
  {
    if (!QFile::exists(mrufile))
      return NULL;

    act_file = mrufile;
  }

  emit sbMessage(tr("File loading..."));
  QFile file(act_file);
//  if (!file.open(IO_ReadOnly))
//    return NULL;
  
  p = new Project(main);
  XMLHandler handler(p);
  QXmlInputSource source(file);
  QXmlSimpleReader reader;

  reader.setContentHandler(&handler);
  emit setWaitCursor();
  if (reader.parse(source))
  {
    file.close();
    emit setPreviousCursor();
    return p;
  }
  file.close();

  p->machine->updateDefaultTransitions();

  emit setPreviousCursor();
  return NULL;

/*  QTextStream s(&file);

  QDomDocument domdoc("domdoc");

  if ( !domdoc.setContent( &file ) ) 
  {
    file.close();
    return NULL;
  }
  qDebug(domdoc.toString());

  QDomDocumentType domdoctype=domdoc.docType();
  if (domdoctype.name!="fsmproject")
    return NULL;

  QDomElement domroot=domdoc.documentElement();
*/ 

  /*
  int version_major, version_minor;
  QString mname;
  int mtype, numbits, numin, numout, initial;
  int num_states;
  int scode;
  QString sname;
  double xpos, ypos;
  double c1x, c1y, c2x, c2y;
  double endx, endy;
  int radius, linewidth;
  unsigned int pencolor, brushcolor;
  QString sfamily, tfamily;
  int spointsize, tpointsize;
  int dest_code, anz, type;
  QString in, out;
  int straight;
  GState *state, *dest_state;
  Convert conv;
  TransitionInfo* info=NULL;
  Machine* m;
  int arrowtype;
  QString inames, onames, onamesm;
  int endstate;

  s >> version_major;
  s >> version_minor;
  s.readLine();
  mname = s.readLine();
  s >> mtype >> numbits >> numin >> numout;
  if (mtype==Ascii)
  {
    numbits=32;
    numin=8;
    numout=8;
  }
  s.readLine();
  onamesm = s.readLine();
  inames = s.readLine();
  onames = s.readLine();
  s >> num_states;
  s >> initial;
  s.readLine();
  sfamily = s.readLine(); 
  spointsize = s.readLine().toInt();
  tfamily = s.readLine(); 
  tpointsize = s.readLine().toInt();
  s >> arrowtype;
  QFont sfont(sfamily, spointsize);
  QFont tfont(tfamily, tpointsize);

  p = new Project(main);
  p->addMachine(mname, mtype, numbits, onamesm, numin, inames, numout, onames, sfont, tfont, arrowtype);
  m = p->machine;

  for (int i=0; i<num_states; i++)
  {
    s >> scode;
    s.readLine();
    sname=s.readLine();
    s >> xpos >> ypos >> radius;
    s >> pencolor >> linewidth;
    s >> brushcolor;
    s >> endstate;

    QColor pcol((QRgb)pencolor);
    QColor bcol((QRgb)brushcolor);
    QPen pen(pcol, linewidth );
    QBrush brush(bcol);

    m->addState(sname, scode, xpos, ypos, radius, 1.0, pen, bool(endstate));
  }
  
  state = m->getState(initial);
  if (state)
    m->setInitialState(state);
  else
    m->setInitialState(m->getSList().first());

  for(int i=0; i<num_states; i++)
  {
    s >> scode;
    state = m->getState(scode);
    s >> anz;
    for (int j=0; j<anz; j++)
    {
      s >> dest_code;
      if (dest_code==-1)
	dest_state=NULL;
      else
	dest_state = m->getState(dest_code);
      s >> type;
      s >> in >> out;
      s >> xpos >> ypos >> c1x >> c1y >> c2x >> c2y >> endx >> endy;
      s >> straight;

      if (type == Binary)
      {
        IOInfoBin bin, bout;

	bin = conv.binStrToX10(numin, in);
       
	if (out!="<noout>")
	{
	  bout = conv.binStrToX10(numout, out);
	}

	info = new TransitionInfoBin(bin,bout);
      }
      else
      {
	if (out=="<noout>")
	  out="";

        IOInfoASCII ain(in), aout(out);

	info = new TransitionInfoASCII(ain, aout);
      }
      
      if (state)
      {
	state->addTransition(p, dest_state, info, xpos, ypos, endx, endy,
	  c1x, c1y, c2x, c2y, (bool)straight);
      } 
    }
  }

  // phantom state
  state = m->getPhantomState();
  s >> anz;
  for (int j=0; j<anz; j++)
  {
    s >> dest_code;
    if (dest_code==-1)
      dest_state=NULL;
    else
      dest_state = m->getState(dest_code);
    s >> type;
    s >> in >> out;
    s >> xpos >> ypos >> c1x >> c1y >> c2x >> c2y >> endx >> endy;
    s >> straight;

    if (type == Binary)
    {
      IOInfoBin bin, bout;

      bin = conv.binStrToX10(numin, in);
      bout = conv.binStrToX10(numout, out);
      
      info = new TransitionInfoBin(bin/,bout);
    }
    else
    {
      IOInfoASCII ain(in), aout(out);

      info = new TransitionInfoASCII(ain, aout);
    }
    
    if (state)
    {
      state->addTransition(p, dest_state, info, xpos, ypos, endx, endy,
	c1x, c1y, c2x, c2y, (bool)straight);
    } 
  }       
  m->calcCanvasSize();   
*/
}



/**
 * Save project as 'fsm'-file with a new name.
 * Asks for a file name and saves the project @a p as a 'fsm'-file.
 */
bool FileIO::saveFileAs(Project* p)
{
  if(!p->machine->checkStateCodes())
  {
    switch(mb_statecode->exec())
    {
      case QMessageBox::Yes:
        break;
      case QMessageBox::No:
        return FALSE;
        break;
      case QMessageBox::Cancel:
        return FALSE;
        break;
    }
  }
//  filedlg->setMode(Q3FileDialog::AnyFile);
  filedlg->setAcceptMode(QFileDialog::AcceptSave);
  filedlg->setFileMode(QFileDialog::AnyFile);
  if (act_file!=QString::null)
//    filedlg->setSelection(act_file);
    filedlg->selectFile(act_file);

  if (filedlg->exec())
  {
    act_file = filedlg->selectedFile();
	
	QString name=act_file.right(act_file.length()-act_file.lastIndexOf("/"));
  if(name.right(4)!=".fsm")
		act_file.append(".fsm");

    QFile ftmp(act_file);
    if (ftmp.exists())
    {
      //if (QMessageBox::warning(main, tr("Warning"), tr("File exists. Do you want to overwrite it?"), QMessageBox::Ok|QMessageBox::Default, QMessageBox::Cancel|QMessageBox::Escape)!=QMessageBox::Ok)
      if (Error::warningOkCancel(tr("File exists. Do you want to overwrite it?"))!=QMessageBox::Ok)
	return FALSE;
    }

    return doSaveXML(p);
  }
  return FALSE;
}


/**
 * Saves project as 'fsm'-file.
 * If no file name is given, it first asks for the file name.
 */
bool FileIO::saveFile(Project* p)
{
  if(!p->machine->checkStateCodes())
  {
    switch(mb_statecode->exec())
    {
      case QMessageBox::Yes:
        break;
      case QMessageBox::No:
        return FALSE;
      case QMessageBox::Cancel:
        return FALSE;
    }
  }
  if (act_file == QString::null)
    return saveFileAs(p);
  else
    return doSaveXML(p);
}


/**
 * Performs the actual saving of project @a p.
 */
bool FileIO::doSave(Project* p)
{
    Machine* m = p->machine;
    if (!m)
      return FALSE;

    QList<GState*> list;
    QList<GTransition*> tlist; 
    GState *state;
    State* dest_state;
    GTransition* t;

    QFile file(act_file);
    if (!file.open(QIODevice::WriteOnly))
    {
      Error::info(tr("File cannot be written."));
      qDebug("file cannot be opened for writing");
      return FALSE;
    }
    Q3TextStream s(&file);

    list = m->getSList();
    QMutableListIterator<GState*> i(list);
    AppInfo info(main);
    double xpos, ypos;
    double c1x, c1y, c2x, c2y;
    double endx, endy;
    int initial;
//    int canvasw, canvash;
    QString transio;
    
    s << info.getVersionMajor() << " ";
    s << info.getVersionMinor() << endl;
    s << m->getName() << endl;
    s << m->getVersion() << endl;
    s << m->getAuthor() << endl;
    s << m->getDescription() << endl;
    s << m->getType() << " ";
    s << m->getNumMooreOutputs() << " ";
    s << m->getNumInputs() << " ";
    s << m->getNumOutputs() << endl;
    s << m->getMooreOutputNames() << endl;
    s << m->getMealyInputNames() << endl;
    s << m->getMealyOutputNames() << endl;
    s << m->countStates() << endl;
    state = m->getInitialState();
    if (state)
      initial= state->getEncoding();
    else
      initial=-1;

    s << initial << endl;
//    m->getCanvasSize(canvasw, canvash);
//    s << canvasw << " " << canvash << endl;
    s << m->getSFont().family() << endl << m->getSFont().pointSize() << endl;
    s << m->getTFont().family() << endl << m->getTFont().pointSize() << endl;
    s << m->getArrowType() << endl;
    s << endl;

    for(; i.hasNext();)
    {

      state = i.next();
      state->getPos(xpos, ypos);
      
      s.setf(Q3TextStream::bin);
      s << state->getEncoding() << endl;
      s << state->getMooreOutputsStr() << endl;
      s.setf(Q3TextStream::dec);

      s << state->getStateName() << endl;
      s << state->getDescription() << endl;
      s << xpos << " " << ypos << " " << state->getRadius() << endl;
      s << state->getPen().color().rgb() << " " << state->getLineWidth() << endl;
      s << state->getBrush().color().rgb() << endl;
      s << state->isFinalState() << endl;
      s << endl;
    }
    s << endl;

    i.toFront();

    for(; i.hasNext();)
    {
      state = i.next();

      s.setf(Q3TextStream::bin);
      s << state->getEncoding() << endl;
      s.setf(Q3TextStream::dec);

      tlist = state->tlist;
      QMutableListIterator<GTransition*> j(tlist);

      s << state->countTransitions() << endl;

      for(; j.hasNext();)
      {
        t = j.next();

        dest_state = t->getEnd();

	s.setf(Q3TextStream::bin);
	if (dest_state)
	  s << dest_state->getEncoding() << endl;
	else
	  s << -1 << endl;
	s.setf(Q3TextStream::dec);

        s << t->getInfo()->getType() << endl;
        s << t->getDescription() << endl;
//	if (t->getInfo()->getType()==Binary)
	{
          s << t->getInfo()->getInputsStr(NULL) << " ";
          transio = t->getInfo()->getOutputsStr(NULL);
	  if (transio.isEmpty())
	    transio="<noout>";
	  s << transio << endl;
        }
	
        t->getPos(xpos, ypos);
	t->getEndPos(endx, endy);
	t->getCPoint1(c1x, c1y);
	t->getCPoint2(c2x, c2y);
	
	s << xpos << " " << ypos << " ";
	s << c1x << " " << c1y << " " << c2x << " " << c2y << " ";
	s << endx << " " << endy << " ";
	s << (int)t->isStraight() << endl;
        
	s << endl;
      }
      s << endl;
    }

    // phantom state
    state = m->getPhantomState();

    tlist = state->tlist;
    QMutableListIterator<GTransition*> ph(tlist);

    s << state->countTransitions() << endl;

    for(; ph.hasNext();)
    {
      t = ph.next();

      dest_state = t->getEnd();

      s.setf(Q3TextStream::bin);
      if (dest_state)
	s << dest_state->getEncoding() << endl;
      else
	s << -1 << endl;
      s.setf(Q3TextStream::dec);

      s << t->getInfo()->getType() << endl;
      s << t->getDescription() << endl;
//      if (t->getInfo()->getType()==Binary)
      {
	s << t->getInfo()->getInputsStr(NULL) << " ";
	transio = t->getInfo()->getOutputsStr(NULL);
	if (transio.isEmpty())
	  transio="<noout>";
	s << transio << endl;
      }
      t->getPos(xpos, ypos);
      t->getEndPos(endx, endy);
      t->getCPoint1(c1x, c1y);
      t->getCPoint2(c2x, c2y);
      
      s << xpos << " " << ypos << " ";
      s << c1x << " " << c1y << " " << c2x << " " << c2y << " ";
      s << endx << " " << endy << " ";
      s << (int)t->isStraight() << endl;
      
      s << endl;
    }

    file.close();

    p->setChanged(FALSE);
    return TRUE;
}



/**
 * Performs the actual saving of project @a p in XML format.
 */
bool FileIO::doSaveXML(Project* p)
{
    Machine* m = p->machine;
    if (!m)
      return FALSE;

    /*
    QList<GState> list;
    QList<GTransition> tlist; 
    GState *state;
    State* dest_state;
    GTransition* t;
    */

    QFile file(act_file);
    if (!file.open(QIODevice::WriteOnly))
    {
      Error::info(tr("File cannot be written."));
      qDebug("file cannot be opened for writing");
      return FALSE;
    }
    QTextStream tstream(&file);


    /*
    QString prolog="<?xml version=\"1.0\"?>\n"
      		   "<!DOCTYPE qfsmproject SYSTEM \"qfsm.dtd\">\n\n"
                   "<qfsmproject>\n"
                   "</qfsmproject>\n";
    */

    QDomDocument domdoc;
    domdoc = p->getDomDocument();
    /*
    QDomElement root, me, one, ine, onme, itranse;
    QDomText ontext, intext, onmtext;
    QString stmp;
    int inits;
    GState* s;
    GITransition* initt;
    GTransition* t;
    QList<GState> slist;
    QList<GTransition> tlist; 
    double xpos, ypos, endx, endy, c1x, c1y, c2x, c2y;

    domdoc.setContent(prolog);

    root = domdoc.documentElement();

    // Machine

    me = domdoc.createElement("machine");
    me.setAttribute("name", m->getName());
    me.setAttribute("type", m->getType());
    me.setAttribute("numbits", m->getNumBits());
    me.setAttribute("numin", m->getNumInputs());
    me.setAttribute("numout", m->getNumOutputs());
    s = m->getInitialState();
    if (s)
    {
      inits = s->getCode();
      me.setAttribute("initialstate", inits);
    }
    me.setAttribute("statefont", m->getSFont().family());
    me.setAttribute("statefontsize", m->getSFont().pointSize());
    me.setAttribute("transfont", m->getTFont().family());
    me.setAttribute("transfontsize", m->getTFont().pointSize());
    me.setAttribute("arrowtype", m->getArrowType());
    
    root.appendChild(me);


    // Input/Output names

    onme = domdoc.createElement("outputnames_moore");
    ine = domdoc.createElement("inputnames");
    one = domdoc.createElement("outputnames");
    intext = domdoc.createTextNode(m->getMealyInputNames());
    ontext = domdoc.createTextNode(m->getMealyOutputNames());
    onmtext = domdoc.createTextNode(m->getMooreOutputNames());
    ine.appendChild(intext);
    one.appendChild(ontext);
    onme.appendChild(onmtext);
    me.appendChild(onme);
    me.appendChild(ine);
    me.appendChild(one);


    // Initial Transition

    initt = m->getInitialTransition();
    if (initt)
    {
      initt->getPos(xpos, ypos);
      initt->getEndPos(endx, endy);
      itranse = domdoc.createElement("itransition");
      itranse.setAttribute("xpos", xpos);
      itranse.setAttribute("ypos", ypos);
      itranse.setAttribute("endx", endx);
      itranse.setAttribute("endy", endy);

      me.appendChild(itranse);
    }


    // States
    
    slist = m->getSList();
    QListIterator<GState> sit(slist);

    for(;sit.current(); ++sit)
    {
      s = sit.current();
      s->getPos(xpos, ypos);
      QDomElement se = domdoc.createElement("state");
      QDomText st = domdoc.createTextNode(s->getName());
      
      se.setAttribute("code", s->getCode());
      se.setAttribute("xpos", xpos);
      se.setAttribute("ypos", ypos);
      se.setAttribute("radius", s->getRadius());
      se.setAttribute("pencolor", s->getColor().rgb() & 0xffffff);
      se.setAttribute("linewidth", s->getLineWidth());
      se.setAttribute("endstate", s->isEndState());

      se.appendChild(st);

      me.appendChild(se);
    }


    // Transitions

    sit.toFirst();
    for(; sit.current(); ++sit)
    {
      s = sit.current();
      QListIterator<GTransition> tit(s->tlist);
      GState *send;

      for(;tit.current(); ++tit)
      {
	t = tit.current();
	t->getPos(xpos, ypos);
	t->getEndPos(endx, endy);
	t->getCPoint1(c1x, c1y);
	t->getCPoint2(c2x, c2y);
	QDomElement te = domdoc.createElement("transition");
	
	te.setAttribute("type", t->getInfo()->getType());
	te.setAttribute("xpos", xpos);
	te.setAttribute("ypos", ypos);
	te.setAttribute("endx", endx);
	te.setAttribute("endy", endy);
	te.setAttribute("c1x", c1x);
	te.setAttribute("c1y", c1y);
	te.setAttribute("c2x", c2x);
	te.setAttribute("c2y", c2y);
	te.setAttribute("straight", t->isStraight());

	send = (GState*)t->getEnd();
        QDomElement from = domdoc.createElement("from");
	QString sfrom;
	sfrom.sprintf("%d", s->getCode());
	QDomText fromt = domdoc.createTextNode(sfrom);
	from.appendChild(fromt);
	te.appendChild(from);

	if (send)
	{
	  QDomElement to = domdoc.createElement("to");
	  QString sto;
	  sto.sprintf("%d", send->getCode());
	  QDomText tot = domdoc.createTextNode(sto);
	  to.appendChild(tot);
	  te.appendChild(to);
	}

        QDomElement inpute, outpute;
	QDomText inputt, outputt;

	inpute = domdoc.createElement("inputs");
	outpute = domdoc.createElement("outputs");

	inputt = domdoc.createTextNode(t->getInfo()->getInputsStr());
	outputt = domdoc.createTextNode(t->getInfo()->getOutputsStr());

	inpute.appendChild(inputt);
	outpute.appendChild(outputt);

        te.appendChild(inpute);
	te.appendChild(outpute);

	me.appendChild(te);
      }
    }


    // Phantom State

    s = m->getPhantomState();
    QListIterator<GTransition> tit(s->tlist);
    GState *send;

    for(;tit.current(); ++tit)
    {
      t = tit.current();
      t->getPos(xpos, ypos);
      t->getEndPos(endx, endy);
      t->getCPoint1(c1x, c1y);
      t->getCPoint2(c2x, c2y);
      QDomElement te = domdoc.createElement("transition");
      
      te.setAttribute("type", t->getInfo()->getType());
      te.setAttribute("xpos", xpos);
      te.setAttribute("ypos", ypos);
      te.setAttribute("endx", endx);
      te.setAttribute("endy", endy);
      te.setAttribute("c1x", c1x);
      te.setAttribute("c1y", c1y);
      te.setAttribute("c2x", c2x);
      te.setAttribute("c2y", c2y);
      te.setAttribute("straight", t->isStraight());

      send = (GState*)t->getEnd();
      if (send)
      {
	QDomElement to = domdoc.createElement("to");
	QString sto;
	sto.sprintf("%d", send->getCode());
	QDomText tot = domdoc.createTextNode(sto);
	to.appendChild(tot);
	te.appendChild(to);
      }

      QDomElement inpute, outpute;
      QDomText inputt, outputt;

      inpute = domdoc.createElement("inputs");
      outpute = domdoc.createElement("outputs");

      inputt = domdoc.createTextNode(t->getInfo()->getInputsStr());
      outputt = domdoc.createTextNode(t->getInfo()->getOutputsStr());

      inpute.appendChild(inputt);
      outpute.appendChild(outputt);

      te.appendChild(inpute);
      te.appendChild(outpute);

      me.appendChild(te);
    }
    */

    domdoc.save(tstream, 2);

    file.close();

    p->setChanged(FALSE);
    return TRUE;

    // old save code
    /*
    list = m->getSList();
    QListIterator<GState> i(list);
    AppInfo info(main);
    double xpos, ypos;
    double c1x, c1y, c2x, c2y;
    double endx, endy;
    int initial;
//    int canvasw, canvash;
    QString transio;
    
    s << info.getVersionMajor() << " ";
    s << info.getVersionMinor() << endl;
    s << m->getName() << endl;
    s << m->getType() << " ";
    s << m->getNumBits() << " ";
    s << m->getNumInputs() << " ";
    s << m->getNumOutputs() << endl;
    s << m->getMooreOutputNames() << endl;
    s << m->getMealyInputNames() << endl;
    s << m->getMealyOutputNames() << endl;
    s << m->countStates() << endl;
    state = m->getInitialState();
    if (state)
      initial= state->getCode();
    else
      initial=-1;

    s << initial << endl;
//    m->getCanvasSize(canvasw, canvash);
//    s << canvasw << " " << canvash << endl;
    s << m->getSFont().family() << endl << m->getSFont().pointSize() << endl;
    s << m->getTFont().family() << endl << m->getTFont().pointSize() << endl;
    s << m->getArrowType() << endl;
    s << endl;

    for(; i.current(); ++i)
    {

      state = i.current();
      state->getPos(xpos, ypos);
      
      s.setf(QTextStream::bin);
      s << state->getCode() << endl;
      s.setf(QTextStream::dec);

      s << state->getName() << endl;
      s << xpos << " " << ypos << " " << state->getRadius() << endl;
      s << state->getPen().color().rgb() << " " << state->getLineWidth() << endl;
      s << state->getBrush().color().rgb() << endl;
      s << state->isEndState() << endl;
      s << endl;
    }
    s << endl;

    i.toFirst();

    for(; i.current(); ++i)
    {
      state = i.current();

      s.setf(QTextStream::bin);
      s << state->getCode() << endl;
      s.setf(QTextStream::dec);

      tlist = state->tlist;
      QListIterator<GTransition> j(tlist);

      s << state->countTransitions() << endl;

      for(; j.current(); ++j)
      {
        t = j.current();

        dest_state = t->getEnd();

	s.setf(QTextStream::bin);
	if (dest_state)
	  s << dest_state->getCode() << endl;
	else
	  s << -1 << endl;
	s.setf(QTextStream::dec);

        s << t->getInfo()->getType() << endl;
//	if (t->getInfo()->getType()==Binary)
	{
          s << t->getInfo()->getInputsStr() << " ";
          transio = t->getInfo()->getOutputsStr();
	  if (transio.isEmpty())
	    transio="<noout>";
	  s << transio << endl;
        }
	
        t->getPos(xpos, ypos);
	t->getEndPos(endx, endy);
	t->getCPoint1(c1x, c1y);
	t->getCPoint2(c2x, c2y);
	
	s << xpos << " " << ypos << " ";
	s << c1x << " " << c1y << " " << c2x << " " << c2y << " ";
	s << endx << " " << endy << " ";
	s << (int)t->isStraight() << endl;
        
	s << endl;
      }
      s << endl;
    }

    // phantom state
    state = m->getPhantomState();

    tlist = state->tlist;
    QListIterator<GTransition> ph(tlist);

    s << state->countTransitions() << endl;

    for(; ph.current(); ++ph)
    {
      t = ph.current();

      dest_state = t->getEnd();

      s.setf(QTextStream::bin);
      if (dest_state)
	s << dest_state->getCode() << endl;
      else
	s << -1 << endl;
      s.setf(QTextStream::dec);

      s << t->getInfo()->getType() << endl;
//      if (t->getInfo()->getType()==Binary)
      {
	s << t->getInfo()->getInputsStr() << " ";
	transio = t->getInfo()->getOutputsStr();
	if (transio.isEmpty())
	  transio="<noout>";
	s << transio << endl;
      }
      t->getPos(xpos, ypos);
      t->getEndPos(endx, endy);
      t->getCPoint1(c1x, c1y);
      t->getCPoint2(c2x, c2y);
      
      s << xpos << " " << ypos << " ";
      s << c1x << " " << c1y << " " << c2x << " " << c2y << " ";
      s << endx << " " << endy << " ";
      s << (int)t->isStraight() << endl;
      
      s << endl;
    }
    */


}


/**
 * Saves the application options.
 * Saves options @a opt in the qfsmrc-file which is in $HOME/.qfsm/.
 */
int FileIO::saveOptions(Options* opt)
{
  int result=0;
  QString stmp;
  QDir dir = QDir::home();

  QDir qfsmdir=createQfsmDir();


  QFile file(qfsmdir.absPath()+"/qfsmrc");
  if (!file.open(QIODevice::WriteOnly))
  {
    qDebug("options not saved");
    return 1;
  }

  Q3TextStream fout(&file);

  fout << "view_stateenc " << (int)opt->getViewStateEncoding() << endl;
  fout << "view_moore " << (int)opt->getViewMoore() << endl;
  fout << "view_mealyin " << (int)opt->getViewMealyIn() << endl;
  fout << "view_mealyout " << (int)opt->getViewMealyOut() << endl;
  fout << "view_grid " << (int)opt->getViewGrid() << endl;
  fout << "view_ioview " << (int)opt->getViewIOView() << endl;

  fout << "state_shadows " << (int)opt->getStateShadows() << endl;
  fout << "state_shadow_color " << (unsigned int)opt->getStateShadowColor().rgb() << endl;

  fout << "grid_size " << opt->getGridSize() << endl;
  fout << "grid_color " << (unsigned int)opt->getGridColor().rgb() << endl;

  fout << "tooltips " << (int)opt->getToolTips() << endl;
  fout << "iomark " << (int)opt->getIOMark() << endl;
  fout << "ionames " << (int)opt->getDisplayIONames() << endl;
  fout << "drawbox " << (int)opt->getDrawBox() << endl;

  stmp = opt->getInitialDescriptor().stripWhiteSpace();
  if (stmp.isEmpty())
    stmp = getEmptyFieldString();
  fout << "initial_descriptor " << stmp << endl;
  stmp = opt->getInversionDescriptor().stripWhiteSpace();
  if (stmp.isEmpty())
    stmp = getEmptyFieldString();
  fout << "inversion_descriptor " << stmp << endl;
  stmp = opt->getAnyInputDescriptor().stripWhiteSpace();
  if (stmp.isEmpty())
    stmp = getEmptyFieldString();
  fout << "any_input_descriptor " << stmp << endl;
  stmp = opt->getDefaultTransitionDescriptor().stripWhiteSpace();
  if (stmp.isEmpty())
    stmp = getEmptyFieldString();
  fout << "default_descriptor " << stmp << endl;

  fout << "ahdl_sync_reset " << (int)opt->getAHDLSyncReset() << endl;
  fout << "ahdl_use_moore " << (int)opt->getAHDLUseMoore() << endl;

  fout << "vhdl_symbolic_states " << (int)opt->getVHDLSymbolicStates() << endl;
  fout << "vhdl_debug_state " << (int)opt->getVHDLDebugState() << endl;
  fout << "vhdl_sync_reset " << (int)opt->getVHDLSyncReset() << endl;
  fout << "vhdl_sync_enable " << (int)opt->getVHDLSyncEnable() << endl;
  fout << "vhdl_stdlogic " << (int)opt->getVHDLStdLogic() << endl;
  fout << "vhdl_io_names " << (int)opt->getVHDLInOutNames() << endl;
  fout << "vhdl_neg_reset " << (int)opt->getVHDLNegReset() << endl;
  fout << "vhdl_io_header " << (int)opt->getVHDLIOheader() << endl;
  fout << "vhdl_alliance " << (int)opt->getVHDLAlliance() << endl;
  fout << "vhdl_cond_notation " << (int)opt->getVHDLCondNotation() << endl;
  fout << "vhdl_state_code " << (int)opt->getVHDLStateCode() << endl;
  fout << "vhdl_sync_look_ahead " << (int)opt->getVHDLSyncLookAhead() << endl;
  fout << "vhdl_sep_files " << (int)opt->getVHDLSepFiles()<< endl;
  stmp = opt->getVHDLArchitectureName().stripWhiteSpace();
  if (stmp.isEmpty())
    stmp = "behave";
  fout << "vhdl_architecture_name " << stmp << endl;


  fout << "testbench_stdlogic " << (int)opt->getTestbenchStdLogic() << endl;
  fout << "testbench_sync_reset " << (int)opt->getTestbenchSynchronousReset() << endl;
  fout << "testbench_sync_enable " << (int)opt->getTestbenchSynchronousEnable() << endl;
  fout << "testbench_negated_reset " << (int)opt->getTestbenchNegatedReset() << endl;
  fout << "testbench_io_header " << (int)opt->getTestbenchIOHeader() << endl;
  fout << "testbench_io_names " << (int)opt->getTestbenchIONames() << endl;
  stmp = opt->getTestbenchVHDLPath().stripWhiteSpace();
  if (stmp.isEmpty())
    stmp = getEmptyFieldString();
  fout << "testbench_vhdl_path " << stmp << endl;
    stmp = opt->getTestvectorASCIIPath().stripWhiteSpace();
  if (stmp.isEmpty())
    stmp = getEmptyFieldString();
  fout << "testvector_ascii_path " << stmp << endl;
    stmp = opt->getTestpackageVHDLPath().stripWhiteSpace();
  if (stmp.isEmpty())
    stmp = getEmptyFieldString();
  fout << "testpackage_vhdl_path " << stmp << endl;
    stmp = opt->getTestbenchLogfilePath().stripWhiteSpace();
  if (stmp.isEmpty())
    stmp = getEmptyFieldString();
  fout << "testbench_logfile_path " << stmp << endl;
    stmp = opt->getTestbenchBaseDirectory().stripWhiteSpace();
  if (stmp.isEmpty())
    stmp = getEmptyFieldString();
  fout << "testbench_base_directory " << stmp << endl;




  fout << "ver_sync_reset " << (int)opt->getVerilogSyncReset() << endl;
  //fout << "ver_register_out " << (int)opt->getVerilogRegisterOut() << endl;

  fout << "statetable_includeout " << (int)opt->getStateTableIncludeOut() << endl;
  fout << "statetable_resolve_inverted " << (int)opt->getStateTableResolveInverted() << endl;
  fout << "statetable_orientation " << (int)opt->getStateTableOrientation() << endl;

  fout << "ragel_create_action " << (int)opt->getRagelCreateAction() << endl;
  fout << "ragel_lang_action " << (int)opt->getRagelLangAction() << endl;
  fout << "ragel_default_transitions " << (int)opt->getRagelDefaultTransitions() << endl;
  fout << "vvvv_reset " << (int)opt->getVVVVReset() << endl;
  fout << "vvvv_reset_event " << opt->getVVVVResetEvent() << endl;
  fout << "vvvv_reset_action " << opt->getVVVVResetAction() << endl;
  fout << "print_header " << (int)opt->getPrintHeader() << endl;

  fout << endl;

  file.close();

  return result;
}

/**
 * Loads the application options.
 * Loads the options from $HOME/.qfsm/qfsmrc into @a opt.
 */
int FileIO::loadOptions(Options* opt)
{
  int result=0;
  QDir dir = QDir::home();
  QMap<QString, QString> _map;
  QString key, value;

#ifdef WIN32
  QFile file(dir.absPath()+"/Application Data/qfsm/qfsmrc");
#else
  QFile file(dir.absPath()+"/.qfsm/qfsmrc");
#endif

  if (!file.open(QIODevice::ReadOnly))
  {
    qDebug("options not loaded");
    return 1;
  }

  Q3TextStream fin(&file);

  fin >> key >> value;

  while (!fin.eof())
  {
    _map.insert(key, value);
    fin >> key >> value;
    if (value==getEmptyFieldString())
      value="";
  }

  setOptions(&_map, opt);

  return result;
}


/**
 * Sets the loaded application options.
 * @param map pairs of strings which contain the options
 * @param opt options object where the options will be saved
 */
void FileIO::setOptions(QMap<QString, QString>* _map, Options* opt)
{
  QMap<QString, QString>::Iterator it;
  QString key, data;
  int idata;
  unsigned int uidata;

  for(it = _map->begin(); it != _map->end(); ++it)
  {
    key = it.key();
    data = it.data();
    if (data==getEmptyFieldString())
      data="";
    idata = data.toInt();
    uidata = data.toUInt();

    if (key=="view_stateenc")
      opt->setViewStateEncoding(idata);
    else if (key=="view_moore")
      opt->setViewMoore(idata);
    else if (key=="view_mealyin")
      opt->setViewMealyIn(idata);
    else if (key=="view_mealyout")
      opt->setViewMealyOut(idata);
    else if (key=="view_grid")
      opt->setViewGrid(idata);
    else if (key=="view_ioview")
      opt->setViewIOView(idata);
    else if (key=="state_shadows")
      opt->setStateShadows(idata);
    else if (key=="state_shadow_color")
    {
      QColor c;
      c.setRgb((QRgb) uidata);
      opt->setStateShadowColor(c);
    }
    else if (key=="grid_size")
      opt->setGridSize(idata);
    else if (key=="grid_color")
    {
      QColor c;
      c.setRgb((QRgb) uidata);
      opt->setGridColor(c);
    }
    else if (key=="tooltips")
      opt->setToolTips(idata);
    else if (key=="iomark")
      opt->setIOMark(idata);
    else if (key=="ionames")
      opt->setDisplayIONames(idata);
    else if (key=="drawbox")
      opt->setDrawBox(idata);
    else if (key=="initial_descriptor" || key=="start_descriptor")
      opt->setInitialDescriptor(data);
    else if (key=="inversion_descriptor")
      opt->setInversionDescriptor(data);
    else if (key=="any_input_descriptor")
      opt->setAnyInputDescriptor(data);
    else if (key=="default_descriptor")
      opt->setDefaultTransitionDescriptor(data);
    else if (key=="ahdl_sync_reset")
      opt->setAHDLSyncReset(idata);
    else if (key=="ahdl_use_moore")
      opt->setAHDLUseMoore(idata);
    else if (key=="vhdl_symbolic_states")
      opt->setVHDLSymbolicStates(idata);
    else if (key=="vhdl_debug_state")
      opt->setVHDLDebugState(idata);
    else if (key=="vhdl_sync_reset")
      opt->setVHDLSyncReset(idata);
    else if (key=="vhdl_stdlogic")
      opt->setVHDLStdLogic(idata);
    else if (key=="vhdl_sync_reset")
      opt->setVHDLSyncReset(idata);
    else if (key=="vhdl_stdlogic")
      opt->setVHDLStdLogic(idata);
    else if (key=="vhdl_sync_look_ahead")
      opt->setVHDLSyncLookAhead(idata);
    else if (key=="vhdl_sep_files")
      opt->setVHDLSepFiles(idata);
    else if (key=="default_architecture_name")
      opt->setVHDLArchitectureName(data);
    else if (key=="vhdl_fha")  // deprecated
    {
      if (idata==1)
      {
	opt->setVHDLInOutNames(TRUE);
	opt->setVHDLNegReset(TRUE);
	opt->setVHDLIOheader(TRUE);
	opt->setVHDLAlliance(FALSE);
	opt->setVHDLCondNotation(1);
      }
    }
    else if (key=="vhdl_io_names")  
      opt->setVHDLInOutNames(idata);
    else if (key=="ver_sync_reset")
      opt->setVerilogSyncReset(idata);
    else if (key=="vhdl_sync_enable")
      opt->setVHDLSyncEnable(idata);
    else if (key=="vhdl_neg_reset")  
      opt->setVHDLNegReset(idata);
    else if (key=="vhdl_io_header")  
      opt->setVHDLIOheader(idata);
    else if (key=="vhdl_alliance")  
      opt->setVHDLAlliance(idata);
    else if (key=="vhdl_state_code")  
      opt->setVHDLStateCode(idata);
    else if (key=="vhdl_cond_notation")  
      opt->setVHDLCondNotation(idata);
    /*
    else if (key=="ver_register_out")
      opt->setVerilogRegisterOut(idata);
      */
    else if(key=="testbench_stdlogic")
      opt->setTestbenchStdLogic(idata);
    else if(key=="testbench_sync_reset")
      opt->setTestbenchSynchronousReset(idata);
    else if(key=="testbench_sync_enable")
      opt->setTestbenchSynchronousEnable(idata);
    else if(key=="testbench_negated_reset")
      opt->setTestbenchNegatedReset(idata);
    else if(key=="testbench_io_header")
      opt->setTestbenchIOHeader(idata);
    else if(key=="testbench_io_names")
      opt->setTestbenchIONames(idata);
    else if(key=="testbench_vhdl_path")
      opt->setTestbenchVHDLPath(data);
    else if(key=="testvector_ascii_path")
      opt->setTestvectorASCIIPath(data);
    else if(key=="testpackage_vhdl_path")
      opt->setTestpackageVHDLPath(data);
    else if(key=="testbench_logfile_path")
      opt->setTestbenchLogfilePath(data);
    else if(key=="testbench_base_directory")
      opt->setTestbenchBaseDirectory(data);
    else if (key=="statetable_includeout")
      opt->setStateTableIncludeOut(idata);
    else if (key=="statetable_resolve_inverted")
      opt->setStateTableResolveInverted(idata);
    else if (key=="statetable_orientation")
      opt->setStateTableOrientation(idata);
    else if (key=="ragel_create_action")
      opt->setRagelCreateAction(idata);
    else if (key=="ragel_lang_action")
      opt->setRagelLangAction(idata);
    else if (key=="ragel_default_transitions")
      opt->setRagelDefaultTransitions(idata);
    else if (key=="vvvv_reset")
      opt->setVVVVReset(idata);
    else if (key=="vvvv_reset_event")
      opt->setVVVVResetEvent(data);
    else if (key=="vvvv_reset_action")
      opt->setVVVVResetAction(data);
    else if (key=="print_header")
      opt->setPrintHeader(idata);
  }
}  





/**
 * Imports a file
 * Opens a file dialog, imports a file, and creates a new project
 */
Project* FileIO::importFile(Import* imp, ScrollView* sv/*=NULL*/)
{
  using namespace std;

  QString ext;

  if (!imp)
    return FALSE;

  Project* p=NULL;
  importdlg->setAcceptMode(QFileDialog::AcceptOpen);
  importdlg->setFileMode(QFileDialog::ExistingFile);
  importdlg->setFilter(imp->fileFilter()+";;All Files (*)");

  if (!importdlg->exec())
  {
    act_importfile = QString::null;
    return p;
  }
  act_importfile = importdlg->selectedFile();
  act_import_dir = importdlg->directory().absolutePath();

  QString name=act_importfile.right(act_importfile.length()-act_importfile.lastIndexOf("/"));
  if(name.right(1+imp->defaultExtension().length())!=QString("."+imp->defaultExtension()))
    act_importfile.append("."+imp->defaultExtension());

  //p = new Project(main);

  ifstream fin(act_importfile);

  if (!fin)
    return FALSE;

  emit setWaitCursor();

  imp->init(&fin, main, act_importfile, sv);
  p = imp->doImport();

  emit setPreviousCursor();

  return p;
}



/**
 * Exports the actual file.
 * Opens a file dialog and exports the actual machine into the specified format.
 */
bool FileIO::exportFile(Project* p, Export* exp, ScrollView* sv/*=NULL*/)
{
  using namespace std;

  QString ext;

  if (!p || !exp)
    return FALSE;

  if (!exp->validateMachine(p->machine))
    return FALSE;

//  exportdlg->setMode(Q3FileDialog::AnyFile);
  exportdlg->setFileMode(QFileDialog::AnyFile);
  if (act_exportfile!=QString::null)
//    exportdlg->setSelection(act_exportfile);
    exportdlg->selectFile(act_exportfile);
  else exportdlg->selectFile(p->machine->getName());

  exportdlg->setFilter(exp->fileFilter()+";;All Files (*)");

  if(exportdlg->exec())
  {
    act_exportfile = exportdlg->selectedFile();
//    act_export_dir = exportdlg->dirPath();
    act_export_dir = exportdlg->directory().absolutePath();
	
	QString name=act_exportfile.right(act_exportfile.length()-act_exportfile.lastIndexOf("/"));
  if(name.right(1+exp->defaultExtension().length())!=QString("."+exp->defaultExtension()))
		act_exportfile.append("."+exp->defaultExtension());


    QFile ftmp(act_exportfile);
    if (ftmp.exists())
    {
      if (Error::warningOkCancel(tr("File exists. Do you want to overwrite it?"))!=QMessageBox::Ok)
	return FALSE;
    }

    ofstream fout(act_exportfile);

    if (!fout)
      return FALSE;

    emit setWaitCursor();

    exp->init(&fout, p->machine, act_exportfile, sv);
    exp->doExport();

    emit setPreviousCursor();

    return TRUE;
  }
  return FALSE;
}


/// Saves the list of most recently used files
bool FileIO::saveMRU(QStringList list)
{
  QDir dir = QDir::home();
 
  QDir qfsmdir=createQfsmDir();

  QFile file(qfsmdir.absPath()+"/mru_files");
  if (!file.open(QIODevice::WriteOnly))
  {
    qDebug("mru_files not saved");
    return FALSE;
  }

  Q3TextStream fout(&file);

  QStringList::Iterator it;

  for (it = list.begin(); it != list.end(); ++it)
  {
    fout << (*it) << endl;
  }
  file.close();

  return TRUE;
}


/// Loads the list of most recently used files
bool FileIO::loadMRU(QStringList& _list)
{
  _list.clear();

  QString entry;


  QDir dir=QDir::home();
  
  QDir qfsmdir=createQfsmDir();


  QFile file(qfsmdir.absPath()+"/mru_files");
  if (!file.open(QIODevice::ReadOnly))
  {
    qDebug("mru_files not opened");
    return FALSE;
  }

  Q3TextStream fin(&file);

  do
  {
    entry = fin.readLine();
    entry = entry.stripWhiteSpace();

    if (!entry.isEmpty())
    {
      _list.append(entry);
    }
  } while (!entry.isEmpty());

  file.close();

  return TRUE;
}

QDir FileIO::createQfsmDir()
{
  QDir dir=QDir::home();
#ifdef WIN32
  QDir qfsmdir(dir.absPath()+"/Application Data/qfsm");
  if (!qfsmdir.exists())
  {
    QDir appdir(dir.absPath()+"/Application Data");
    if(!appdir.exists())
    {
      if (!dir.mkdir("Application Data"))
        qDebug("Application Data not created");
    }
    if (!dir.mkdir("Application Data/qfsm"))
      qDebug("Application Data/qfsm not created");
  }
  return qfsmdir;
#else
  QDir qfsmdir(dir.absPath()+"/.qfsm");
  if (!qfsmdir.exists())
  {
    if (!dir.mkdir(".qfsm"))
      qDebug(".qfsm not created");
  }
  return qfsmdir;
#endif
  
}

