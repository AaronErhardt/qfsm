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

#include <qstring.h>
#include <q3textstream.h>
#include <qmessagebox.h>
#include <qmap.h>
#include <qxml.h>

#include "Edit.h"
#include "AppInfo.h"
#include "Selection.h"
#include "Machine.h"
#include "UndoBuffer.h"
#include "TransitionInfo.h"
#include "TransitionInfoBin.h"
#include "TransitionInfoASCII.h"
#include "Convert.h"
#include "Error.h"
#include "XMLHandler.h"

/// Constructor
Edit::Edit(QWidget* parent, const char* name)
     : QObject(parent, name)
{
}

/**
 * Deletes all selected objects.
 * @param sel selection object containing all selected objects
 * @param m machine containing the selected objects
 */
void Edit::deleteSelection(Selection* sel, Machine* m)
{
//  QListIterator<GState> si(sel->getSList());
//  QListIterator<GTransition> ti(sel->getTList());
  QMutableListIterator<GState*> si(sel->getSList());
  QMutableListIterator<GTransition*> ti(sel->getTList());

  GState* s;
  GTransition* t;
  GObject* obj;
  int type=0;

  obj = NULL; //sel->getContextObject(type);
  if (obj)
  {
    switch(type)
    {
      case StateT:
	s = (GState*)obj;
        m->getProject()->getUndoBuffer()->deleteState(s);

	if (s==m->getInitialState())
	  sel->selectITrans(FALSE);
	m->removeState(s);
	break;

      case TransitionT:
	t = (GTransition*)obj;
        m->getProject()->getUndoBuffer()->deleteTransition(t);

	s = (GState*)t->getStart();
        s->removeTransition(t);
	break;

      default:
	break;
    }
  }
  else
  {
    m->getProject()->getUndoBuffer()->deleteSelection(&sel->getSList(),
      &sel->getTList());

    // delete Transitions
    for (; ti.hasNext();)
    {
      t = ti.next();
      s = (GState*)t->getStart();
      s->removeTransition(t);
    }

    // delete States
    for (; si.hasNext();)
    {
      s = si.next();
      if (s==m->getInitialState())
	sel->selectITrans(FALSE);
      m->removeState(s);
    }

    sel->getSList().clear();
    sel->getTList().clear();
  }
}


/**
 * Serializes the selected objects into a string (to be put in the clipboard).
 * The string is in the same format as a .fsm file (XML).
 *
 * @param p Pointer to the project that contains the objects to copy.
 * @param m Pointer to the machine that contains the objects to copy.
 * @param s String that contains the XML data
 * @returns TRUE if successful
 */
bool Edit::copy(Selection* , Project* p, Machine* m, QString& s)
{
    if (!p || !m)
      return FALSE;

    GObject* contextobject;
    QDomDocument domdoc;
//    int otype;

    contextobject = NULL; //sel->getContextObject(otype);

    domdoc = p->getDomDocument(TRUE, contextobject);

    QTextStream tstream(&s, QIODevice::WriteOnly);

//    qDebug(domdoc.toString());

    domdoc.save(tstream, 1);

    return TRUE;
    /*
    QList<GState> list;
    QList<GTransition> tlist; 
    GState *state;
    State* start_state;
    State* dest_state;
    GTransition* t;
    QByteArray array;

    list = sel->getSList();
    tlist = sel->getTList();
    QListIterator<GState> i(list);
    AppInfo info((QWidget*)m->getProject()->getMain());
    double xpos, ypos;
    double c1x, c1y, c2x, c2y;
    double endx, endy;
    int initial;
    QString transio;

    s = QString::number(info.getVersionMajor()) + " " 
      + QString::number(info.getVersionMinor()) + "\n";
    s += m->getName() +"\n";
    s += QString::number(m->getNumBits()) + " " + QString::number(m->getNumInputs()) 
      + " " + QString::number(m->getNumOutputs()) + "\n";
    state = m->getInitialState();
    if (state && sel->isStateSelected(state) && sel->isITransSelected())
      initial= state->getCode();
    else
      initial=-1;

    s += QString::number(initial) + "\n";
    s += QString::number(list.count()) + " " + QString::number(tlist.count()) + "\n";

    for(; i.current(); ++i)
    {
      state = i.current();

      state->getPos(xpos, ypos);
      
      s += QString::number(state->getCode()) + "\n";

      s += state->getName() + "\n";
      s += QString::number(xpos) + " " + QString::number(ypos) + " " 
        + QString::number(state->getRadius()) + "\n";
      s += QString::number(state->getPen().color().rgb()) + " " 
        + QString::number(state->getLineWidth()) + "\n";
      s += QString::number(state->getBrush().color().rgb()) + "\n";
    }

      QListIterator<GTransition> j(tlist);

      for(; j.current(); ++j)
      {
        t = j.current();

	start_state = t->getStart();
	if (start_state && sel->isStateSelected(start_state))
	  s += QString::number(start_state->getCode()) + "\n";
	else
	  s += "-1\n";

        dest_state = t->getEnd();
	if (dest_state && sel->isStateSelected(dest_state))
	  s += QString::number(dest_state->getCode()) + "\n";
	else
	  s += "-1\n";

        s += QString::number(t->getInfo()->getType()) + "\n";
	s += t->getInfo()->getInputsStr() + " ";
	transio = t->getInfo()->getOutputsStr();
	if (transio.isEmpty())
	  transio="<noout>";
	s += transio + "\n";
        
        t->getPos(xpos, ypos);
	t->getEndPos(endx, endy);
	t->getCPoint1(c1x, c1y);
	t->getCPoint2(c2x, c2y);
	
	s += QString::number(xpos) + " " + QString::number(ypos) + " ";
	s += QString::number(c1x) + " " + QString::number(c1y) + " " 
	  + QString::number(c2x) + " " + QString::number(c2y) + " ";
	s += QString::number(endx) + " " + QString::number(endy) + " ";
	s += QString::number((int)t->isStraight()) + "\n";
        
      }


    return TRUE;
*/
}


/**
 * Pastes objects into the the current machine.
 *
 * @param sel Pointer to the selection object.
 * @param p Project to paste the objects into
 * @param m Machine to paste the objects into
 * @param data XML string (produced by Edit::copy())
 * @returns TRUE if successful
 */
bool Edit::paste(Selection* sel, Project* p, Machine* m, QString data)
{
    if (!p || !m || data == QString::null || data.isEmpty())
      return FALSE;

//    QTextStream s(&data, IO_ReadOnly);

    QXmlInputSource source;
    source.setData(data);
    XMLHandler handler(p, sel, FALSE, FALSE);
    QXmlSimpleReader reader;

    reader.setContentHandler(&handler);

    return reader.parse(source);

    /*
    int version_major, version_minor;
    QString mname;
    int numbits, numin, numout, initial;
    int scode;
    QString sname;
    double xpos, ypos;
    double c1x, c1y, c2x, c2y;
    double endx, endy;
    int radius, linewidth;
    unsigned int pencolor, brushcolor;
    QString sfamily, tfamily;
    int dest_code, start_code, type;
    QString in, out;
    int straight;
    GState *dest_state, *start_state;
    Convert conv;
    IOInfoBin bin, bout;
    TransitionInfo* info=NULL;
    int scount, tcount;
    bool ok = FALSE;
    QList<GState> undostatelist;
    QList<GTransition> undotranslist;
    GState *oldinitialstate, *newinitialstate;
    GITransition *oldinitialtrans, *newinitialtrans;
    int oldnumbits, oldnumin, oldnumout;
    QValueList<int> rstatelist;
    QMap<int, int> codemap;
    bool hasinitialstate;
 
    if (m->getInitialState())
      hasinitialstate=TRUE;
    else 
      hasinitialstate=FALSE;

    undostatelist.setAutoDelete(FALSE);
    undotranslist.setAutoDelete(FALSE);

    oldinitialstate = m->getInitialState();
    oldinitialtrans = m->getInitialTransition();
    newinitialstate = oldinitialstate;
    newinitialtrans = oldinitialtrans;

    s >> version_major;
    s >> version_minor;
    if (version_major==0 && version_minor<2)
      return FALSE;
    s.readLine();
    mname = s.readLine();
    s >> numbits >> numin >> numout;
    s.readLine();
    s >> initial;
    s >> scount >> tcount;

    if (s.atEnd())
      return FALSE;

    oldnumbits = m->getNumBits();
    oldnumin = m->getNumInputs();
    oldnumout = m->getNumOutputs();

    if (numbits>m->getNumBits())
    {
      if (Error::warningOkCancel(tr("The number of moore outputs exceeds the limit "
        "of this machine.\nDo you want to increase the number of moore outputs of the "
	"machine?")) == QMessageBox::Ok)
      {
        m->setNumBits(numbits);
      }
    }
    if (numin>m->getNumInputs())
    {
      if (Error::warningOkCancel(tr("The number of mealy inputs exceeds the limit "
        "of this machine.\nDo you want to increase the number of mealy inputs of the "
	"machine?")) == QMessageBox::Ok)
      {
        m->setNumInputs(numin);
      }
    }
    if (numout>m->getNumOutputs())

    {
      if (Error::warningOkCancel(tr("The number of mealy outputs exceeds the limit "
        "of this machine.\nDo you want to increase the number of mealy outputs of the "
	"machine?")) == QMessageBox::Ok)
      {
        m->setNumOutputs(numout);
      }
    }

    for (int i=0; i<scount; i++)
    {
      s >> scode;
      s.readLine();
      sname=s.readLine();
      s >> xpos >> ypos >> radius;
      s >> pencolor >> linewidth;
      s >> brushcolor;

      QColor pcol((QRgb)pencolor);
      QColor bcol((QRgb)brushcolor);
      QPen pen(pcol, linewidth );
      QBrush brush(bcol);
      bool addstate=TRUE;

      if (m->getState(scode))
      {
	if (m->getType()==Binary)
	{
	  if (Error::warningOkCancel(tr("State %1 has a code "
	      "(Moore outputs) that exists already.\nProceed with the remaining "
	      "objects?").arg(sname)) == QMessageBox::Cancel)
	    return ok;
	  else
	    rstatelist.append(scode);
	  addstate=FALSE;
	}
	else
	{
	  int newcode = m->getNewCode();
	  codemap.insert(scode, newcode);
	  scode=newcode;
	  addstate=TRUE;
	}
      }
      if (addstate)
      {
        m->addState(sname, scode, xpos, ypos, radius, 1.0, pen, FALSE);
	undostatelist.append(m->getSList().last());
        sel->select(m->getSList().last());
        ok = TRUE;
      }
    }
    
    QMap<int, int>::Iterator mit;
    mit = codemap.find(initial);
    if (mit!=codemap.end())
      initial = mit.data();
    if (!hasinitialstate && initial!=-1 && m->getState(initial))
    {
      m->setInitialState(m->getState(initial));
      if (!oldinitialtrans)
      {
        m->setInitialTransition(new GITransition(m->getPhantomState(),
	  m->getState(initial)));
      }
    }
    newinitialstate = m->getInitialState();
    newinitialtrans=m->getInitialTransition();

      for (int j=0; j<tcount; j++)
      {
        s >> start_code >> dest_code;
	QMap<int, int>::Iterator mit;
	mit = codemap.find(start_code);
	if (mit!=codemap.end())
	  start_code = mit.data();
	mit = codemap.find(dest_code);
	if (mit!=codemap.end())
	  dest_code = mit.data();

	if (dest_code==-1)
	  dest_state=NULL;
	else
	  dest_state = m->getState(dest_code);
	if (start_code==-1)
	  start_state = m->getPhantomState();
        else
	  start_state = m->getState(start_code);

	s >> type;
	s >> in >> out;
	s >> xpos >> ypos >> c1x >> c1y >> c2x >> c2y >> endx >> endy;
	s >> straight;

	if (type == Binary)
	{
	  bin = conv.binStrToX10(m->getNumInputs(), in);
	 
	  if (out!="<noout>")
	  {
	    bout = conv.binStrToX10(m->getNumOutputs(), out);
	  }

	  info = new TransitionInfoBin(bin, bout);
	}
	else
	{
          IOInfoASCII ain(in), aout(out);

	  info = new TransitionInfoASCII(ain, aout);
	}
        
	if (start_state)
	{
	  GState* desttmp;
	  if (rstatelist.contains(start_state->getCode()))
            start_state = m->getPhantomState();
	  desttmp=dest_state;
          if (desttmp && rstatelist.contains(desttmp->getCode()))
	    desttmp = NULL;

	  start_state->addTransition(m->getProject(), desttmp, info, xpos, ypos, 
	    endx, endy, c1x, c1y, c2x, c2y, (bool)straight, FALSE);
	  undotranslist.append(start_state->tlist.last());
	  sel->select(start_state->tlist.last());
	  ok = TRUE;
        } 

      }
  
  m->getProject()->getUndoBuffer()->paste(&undostatelist, &undotranslist,
    oldinitialstate, newinitialstate, oldinitialtrans, newinitialtrans,
    oldnumbits, oldnumin, oldnumout);

  return ok;
*/
}



