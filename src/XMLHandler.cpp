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

#include <qmessagebox.h>

#include "XMLHandler.h"
#include "AppInfo.h"
#include "Project.h"
#include "Machine.h"
#include "FileIO.h"
#include "TransitionInfo.h"
#include "TransitionInfoText.h"
#include "IOInfoBin.h"
#include "IOInfoASCII.h"
#include "IOInfoText.h"
#include "Convert.h"
#include "TransitionInfoBin.h"
#include "TransitionInfoASCII.h"
#include "Error.h"
#include "Selection.h"
#include "UndoBuffer.h"


/// Constructor
XMLHandler::XMLHandler(Project* newProject, Selection* sel/*=NULL*/, bool keepquiet/*=TRUE*/,
    bool createnewmachine/*=TRUE*/)
  	  : QObject((QObject*)newProject)
{
  project=newProject;
  machine=NULL;
  quiet=keepquiet;
  create_new_machine = createnewmachine;
  selection=sel;

  state=NULL;
  itransition=NULL;
  transition=NULL;
  oldinitialstate=NULL;
  oldinitialtrans=NULL;
  oldnummooreout=0;
  oldnumin=0;
  oldnumout=0;
  version=1;
  saveinitialstate=0;
  inamescont=false;
  onamescont=false;
  monamescont=false;
  snamecont=false;
  hascode=true;
  ttype=0;
  invert=false;
  any=false;
  def=false;
  fromcont=false;
  tocont=false;
  tincont=false;
  toutcont=false;
  hasfrom=false;
  hasto=false;
  addstate=false;
  hasinitialstate=true;
  newinitialstate=NULL;
  newinitialtrans=NULL;
  nummooreout=0;
  numin=0;
  numout=0;
  state_code_size=1;
//  undostatelist.setAutoDelete(FALSE);
//  undotranslist.setAutoDelete(FALSE);
}


/// Starts a new document
bool XMLHandler::startDocument()
{
  AppInfo ai(NULL);

  version = ai.getVersionDouble();
  itransition=NULL;
  saveinitialstate=-1;
  inamescont=FALSE;
  onamescont=FALSE;
  monamescont=FALSE;
  snamecont=FALSE;
  hascode=FALSE;
  fromcont=FALSE;
  tocont=FALSE;
  tincont=FALSE;
  toutcont=FALSE;
  hasfrom=FALSE;
  hasto=FALSE;
  rstatelist.clear();
  codemap.clear();
  return TRUE;
}


/// Called when a start element was parsed
bool XMLHandler::startElement ( const QString & /*namespaceURI*/, const QString &
    /*localName*/, const QString & qName, const QXmlAttributes & atts )
{
  QString aname, avalue;

  if (qName=="qfsmproject")
  {
    // validate author and version
    int len = atts.length();
    for(int i=0; i<len; i++)
    {
      aname = atts.qName(i);
      if (aname=="version")
      {
        version = atts.value(i).toDouble();
      }
    }
  }
  else if (qName=="machine")
  {
    machine=project->machine;
    if (create_new_machine || !machine)
      machine = new Machine(project);
    if (machine->getInitialState())
      hasinitialstate=TRUE;
    else 
      hasinitialstate=FALSE;
    if (!create_new_machine)
    {
      oldnummooreout = machine->getNumMooreOutputs();
      oldnumin = machine->getNumInputs();
      oldnumout = machine->getNumOutputs();
      oldinitialstate = machine->getInitialState();
      oldinitialtrans = machine->getInitialTransition();
      undostatelist.clear();
      undotranslist.clear();
    }
    saveinitialstate=-1;
    inamescont=FALSE;
    onamescont=FALSE;
    monamescont=FALSE;
    snamecont=FALSE;
    itransition=NULL;
    rstatelist.clear();
    codemap.clear();

    int len = atts.length();

    for(int i=0; i<len; i++)
    {
      aname = atts.qName(i);

      if (create_new_machine)
      {
	if (aname=="name")
	  machine->setName(atts.value(i));
	else if (aname == "version")
	  machine->setVersion(atts.value(i));
    else if (aname == "author")
      machine->setAuthor(atts.value(i));
    else if (aname == "description")
      machine->setDescription(atts.value(i));
	else if (aname=="type")
	{
	  int mtype = atts.value(i).toInt();
	  machine->setType(mtype);
	}
	else if (aname=="statefont")
	{
	  QFont ftmp = machine->getSFont();
	  ftmp.setStyleHint(QFont::Helvetica);
	  //ftmp.setStyleStrategy(QFont::PreferBitmap);
	  ftmp.setFamily(atts.value(i));
	  machine->setSFont(ftmp);
	}
	else if (aname=="statefontsize")
	{
	  QFont ftmp = machine->getSFont();
	  ftmp.setPointSize(atts.value(i).toInt());
	  machine->setSFont(ftmp);
	}
	else if (aname=="statefontweight")
	{
	  QFont ftmp = machine->getSFont();
	  ftmp.setWeight(atts.value(i).toInt());
	  machine->setSFont(ftmp);
	}
	else if (aname=="statefontitalic")
	{
	  QFont ftmp = machine->getSFont();
	  ftmp.setItalic(atts.value(i).toInt());
	  machine->setSFont(ftmp);
	}
	else if (aname=="transfont")
	{
	  QFont ftmp = machine->getTFont();
	  ftmp.setStyleHint(QFont::Helvetica);
	  //ftmp.setStyleStrategy(QFont::PreferBitmap);
	  ftmp.setFamily(atts.value(i));
	  machine->setTFont(ftmp);
	}
	else if (aname=="transfontsize")
	{
	  QFont ftmp = machine->getTFont();
	  ftmp.setPointSize(atts.value(i).toInt());
	  machine->setTFont(ftmp);
	}
	else if (aname=="transfontweight")
	{
	  QFont ftmp = machine->getTFont();
	  ftmp.setWeight(atts.value(i).toInt());
	  machine->setTFont(ftmp);
	}
	else if (aname=="transfontitalic")
	{
	  QFont ftmp = machine->getTFont();
	  ftmp.setItalic(atts.value(i).toInt());
	  machine->setTFont(ftmp);
	}
	else if (aname=="arrowtype")
	  machine->setArrowType(atts.value(i).toInt());
	else if (aname=="draw_it")
	  machine->setDrawITrans((bool)atts.value(i).toInt());
      }
      else  // !create_new_machine
      {
	if (aname=="type")
	{
	  int mtype = atts.value(i).toInt();
	  if (mtype!=machine->getType())
	  {
	    //if (!quiet)
	    Error::warningOk(tr("The types of the two machines are not compatible."));
	    return FALSE;
	  }
	}
      }

      if ((aname=="numbits" && version<=0.41) || aname=="nummooreout")
      {
	nummooreout = atts.value(i).toInt();
      }
      else if (aname=="numin")
      {
	numin = atts.value(i).toInt();
      }
      else if (aname=="numout")
      {
	numout = atts.value(i).toInt();
      }
      else if (aname=="initialstate")
	saveinitialstate=atts.value(i).toInt();

    } // end for
    
    if (!quiet && nummooreout>machine->getNumMooreOutputs())
    {
      if (Error::warningOkCancel(tr("The number of moore outputs exceeds the limit "
	"of this machine.\nDo you want to increase the number of moore outputs of the "
	"machine?")) == QMessageBox::Ok)
      {
	machine->setNumMooreOutputs(nummooreout);
      }
    }
    else if (create_new_machine)
      machine->setNumMooreOutputs(nummooreout);

    if (!quiet && numin>machine->getNumInputs())
    {
      if (Error::warningOkCancel(tr("The number of mealy inputs exceeds the limit "
	"of this machine.\nDo you want to increase the number of mealy inputs of the "
	"machine?")) == QMessageBox::Ok)
      {
	machine->setNumInputs(numin);
      }
    }
    else if (create_new_machine)
      machine->setNumInputs(numin);

    if (!quiet && numout>machine->getNumOutputs())
    {
      if (Error::warningOkCancel(tr("The number of mealy outputs exceeds the limit "
	"of this machine.\nDo you want to increase the number of mealy outputs of the "
	"machine?")) == QMessageBox::Ok)
      {
	machine->setNumOutputs(numout);
      }
    }
    else if (create_new_machine)
      machine->setNumOutputs(numout);

  }
  else if (qName=="outputnames_moore")
  {
    monames="";
    monamescont=TRUE;
  }
  else if (qName=="inputnames")
  {
    inames="";
    inamescont=TRUE;
  }
  else if (qName=="outputnames")
  {
    onames="";
    onamescont=TRUE;
  }
  else if (qName=="state")
  {
    if (machine)
    {
      QString aname;
      state = new GState(machine);
      
      hascode=FALSE;

      for(int i=0; i<atts.length(); i++)
      {
	aname = atts.qName(i);
	if (aname=="code")
	{
	  int code;
          code = atts.value(i).toInt();

	  if (machine->getState(code))
	  {
	    int newcode = machine->getNewCode();
	    codemap.insert(code, newcode);
	    code=newcode;
	    addstate=TRUE;
	  }
	  else
	    addstate=TRUE;
	  state->setEncoding(code);
	  hascode=TRUE;
	  if (version<=0.41)
	  {
	    IOInfoBin* iotmp = new IOInfoBin(IO_MooreOut, code, machine->getNumMooreOutputs());
	    state->setMooreOutputs(iotmp);
	  }
	}
	else if (aname=="moore_outputs")
	{
	  Convert conv;
	  IOInfo* iotmp;
	  if (machine->getType()==Binary || version<=0.41)
	  {
	    iotmp = new IOInfoBin(IO_MooreOut);
	    iotmp->setBin(atts.value(i), machine->getNumMooreOutputs());
	  }
	  else if (machine->getType()==Ascii)
	  {
	    iotmp = new IOInfoASCII(IO_MooreOut, atts.value(i));
	  }
	  else 
	  {
	    iotmp = new IOInfoText(IO_MooreOut, atts.value(i));
	  }
	  //iotmp = conv.binStrToX10(machine->getNumMooreOutputs(), atts.value(i));
	  state->setMooreOutputs(iotmp);
	}
	else if (aname=="description")
	  state->setDescription(atts.value(i));
	else if (aname=="xpos")
	  state->setXPos(atts.value(i).toDouble());
	else if (aname=="ypos")
	  state->setYPos(atts.value(i).toDouble());
	else if (aname=="radius")  
	  state->setRadius(atts.value(i).toInt());
	else if (aname=="finalstate" || aname=="endstate")
	  state->setFinalState(atts.value(i).toInt());
	else if (aname=="brushcolor")
	{
	  QBrush b(QColor(atts.value(i).toInt()));
	  state->setBrush(b);
	}
	else if (aname=="pencolor")
	  state->setColor(QColor(QRgb(atts.value(i).toInt())));
	else if (aname=="linewidth")
	  state->setLineWidth(atts.value(i).toInt());
	else if (aname=="entry_actions")
	  state->setEntryActions(atts.value(i));
	else if (aname=="exit_actions")
	  state->setExitActions(atts.value(i));
      }

      sname="";
      snamecont=TRUE;
    }
  }
  else if (qName=="transition")
  {
    iinfo="";
    oinfo="";
    tincont=FALSE;
    toutcont=FALSE;
    fromcont=FALSE;
    tocont=FALSE;
    hasfrom=FALSE;
    hasto=FALSE;
    if (machine)
    {
      QString aname;
      transition = new GTransition();
      ttype=1;

      for(int i=0; i<atts.length(); i++)
      {
	aname = atts.qName(i);
	if (aname=="type")
	  ttype = atts.value(i).toInt();
	else if (aname=="description")
	  transition->setDescription(atts.value(i));
	else if (aname=="xpos")
          transition->setXPos(atts.value(i).toDouble());
	else if (aname=="ypos")
          transition->setYPos(atts.value(i).toDouble());
	else if (aname=="endx")
          transition->setEndPosX(atts.value(i).toDouble());
	else if (aname=="endy")
          transition->setEndPosY(atts.value(i).toDouble());
	else if (aname=="c1x")
	  transition->setCPoint1X(atts.value(i).toDouble());
	else if (aname=="c1y")
	  transition->setCPoint1Y(atts.value(i).toDouble());
	else if (aname=="c2x")
	  transition->setCPoint2X(atts.value(i).toDouble());
	else if (aname=="c2y")
	  transition->setCPoint2Y(atts.value(i).toDouble());
	else if (aname=="straight")
          transition->setStraight(atts.value(i).toDouble());
      } 
    }
  }
  else if (qName=="from")
  {
    hasfrom=TRUE;
    from="";
    fromcont=TRUE;
  }
  else if (qName=="to")
  {
    hasto=TRUE;
    to="";
    tocont=TRUE;
  }
  else if (qName=="inputs")
  {
    iinfo="";
    invert=FALSE;
    any=FALSE;
    def=FALSE;
    int len = atts.length();
    for(int i=0; i<len; i++)
    {
      aname = atts.qName(i);
      if (aname=="invert")
        invert = (bool)atts.value(i).toInt();
      else if (aname=="any")
        any = (bool)atts.value(i).toInt();
      else if (aname=="default")
        def = (bool)atts.value(i).toInt();
    }
    tincont=TRUE;
  }
  else if (qName=="outputs")
  {
    oinfo="";
    toutcont=TRUE;
  }
  else if (qName=="itransition")
  {
    if (machine)
    {
      QString aname;
      itransition = new GITransition();
      itransition->setStart(machine->getPhantomState());

      for(int i=0; i<atts.length(); i++)
      {
	aname = atts.qName(i);
	if (aname=="xpos")
	  itransition->setXPos(atts.value(i).toDouble());
	if (aname=="ypos")
	  itransition->setYPos(atts.value(i).toDouble());
	if (aname=="endx")
	  itransition->setEndPosX(atts.value(i).toDouble());
	if (aname=="endy")
	  itransition->setEndPosY(atts.value(i).toDouble());
      }
    }
  }
  return TRUE;
}


/// Called when a closing tag was parsed
bool XMLHandler::endElement( const QString&, const QString&, const QString& qName)
{
  if (qName=="machine")
  {
    QMap<int, int>::Iterator mit;
    mit = codemap.find(saveinitialstate);
    if (mit!=codemap.end())
      saveinitialstate = mit.data();

    if (!hasinitialstate && saveinitialstate>=0)
    {
      GState* is;
      GITransition* it;
      it = machine->getInitialTransition();

      if (it)
      {
	is = machine->getState(saveinitialstate);
	if (is)
	{
	  machine->setInitialState(is);
	  it->setEnd(is);
	}
	if (itransition)
	{
	  delete it;
	  itransition->setEnd(is);
	  machine->setInitialTransition(itransition);
	  machine->attachInitialTransition();
	  itransition=NULL;
	}
      }
    }

    if (itransition)
    {
      delete itransition;
      itransition=NULL;
    }

    if (create_new_machine)
      project->addMachine(machine);

    if (!create_new_machine)
    {
      newinitialstate = machine->getInitialState();
      newinitialtrans = machine->getInitialTransition();

      project->getUndoBuffer()->paste(&undostatelist, &undotranslist,
	oldinitialstate, newinitialstate, oldinitialtrans, newinitialtrans,
	oldnummooreout, oldnumin, oldnumout);
    }
  }
  else if (qName=="inputnames")
  {
    if (machine)
      machine->setMealyInputNames(machine->getNumInputs(), inames);
    inames="";
    inamescont=FALSE;
  }
  else if (qName=="outputnames")
  {
    if (machine)
      machine->setMealyOutputNames(machine->getNumOutputs(), onames);
    onames="";
    onamescont=FALSE;
  }
  else if (qName=="outputnames_moore")
  {
    if (machine)
      machine->setMooreOutputNames(machine->getNumMooreOutputs(), monames);
    monames="";
    monamescont=FALSE;
  }
  else if (qName=="state")
  {
    state->setStateName(sname);
    if (machine)
    {
      if (addstate)
      {
	machine->addState(state, FALSE);
	undostatelist.append(state);
	if (selection)
	  selection->select(state, FALSE);
	if (!hascode)
	  state->setEncoding(machine->getNewCode());
      }
    }
    sname="";
    snamecont=FALSE;
  }
  else if (qName=="transition")
  {
    if (machine)
    {
      TransitionInfo* info;
      GState* sfrom;
      Convert conv;

      if (ttype == Binary)
      {
        IOInfoBin bin(IO_MealyIn), bout(IO_MealyOut);

	bin = conv.binStrToX10(machine->getNumInputs(), iinfo, IO_MealyIn);
 	bout = conv.binStrToX10(machine->getNumOutputs(), oinfo, IO_MealyOut);
	bin.setInvert(invert);
	bin.setAnyInput(any);
	bin.setDefault(def);

	info = new TransitionInfoBin(bin, bout);
      }
      else if (ttype == Ascii)
      {
	ttype=Ascii;
        IOInfoASCII ain(IO_MealyIn, iinfo), aout(IO_MealyOut, oinfo);
	ain.setInvert(invert);
	ain.setAnyInput(any);
	ain.setDefault(def);

	info = new TransitionInfoASCII(ain, aout);
      }
      else
      {
	ttype=Text;
        IOInfoText tin(IO_MealyIn, iinfo), tout(IO_MealyOut, oinfo);
	tin.setAnyInput(any);
	tin.setDefault(def);

	info = new TransitionInfoText(tin, tout);
      }

      info->setType(ttype);
      transition->setInfo(info);

      QMap<int, int>::Iterator mit;

      if (hasto && !rstatelist.contains(to.toInt()))
      {
	int ito;
	ito = to.toInt();
	mit = codemap.find(ito);
	if (mit!=codemap.end())
	  ito = mit.data();
	transition->setEnd(machine->getState(ito));
      }
      else
	transition->setEnd(NULL);
      if (hasfrom && !rstatelist.contains(from.toInt()))
      {
	int ifrom = from.toInt();
	mit = codemap.find(ifrom);
	if (mit!=codemap.end())
	  ifrom = mit.data();
	sfrom = machine->getState(ifrom);
	if (!sfrom)
          sfrom=machine->getPhantomState();
      }
      else
	sfrom=machine->getPhantomState();
      transition->setStart(sfrom);
      if (transition->isStraight())
	transition->straighten();
      sfrom->addTransition(project, transition, FALSE);
      undotranslist.append(transition);
      if (selection)
	selection->select(transition, FALSE);
    }
    iinfo=""; 
    oinfo="";
    fromcont=tocont=tincont=toutcont=FALSE;
  }
  else if (qName=="from")
    fromcont=FALSE;
  else if (qName=="to")
    tocont=FALSE;
  else if (qName=="inputs")
    tincont=FALSE;
  else if (qName=="outputs")
    toutcont=FALSE;


  return TRUE;
}


/// Deprecated
bool XMLHandler::characters ( const QString & ch ) 
{
  if (inamescont)
    inames+=ch;
  else if (onamescont)
    onames+=ch;
  else if (monamescont)
    monames+=ch;
  else if (snamecont)
    sname+=ch;
  else if (tincont)
    iinfo+=ch;
  else if (toutcont)
    oinfo+=ch;
  else if (fromcont)
    from+=ch;
  else if (tocont)
    to+=ch;

  return TRUE;
}

