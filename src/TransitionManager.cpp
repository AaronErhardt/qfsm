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

#include <qregexp.h>

#include "TransitionManager.h"
#include "GState.h"
#include "MainWindow.h"
#include "TransitionInfoBin.h"
#include "TransitionInfoASCII.h"
#include "TransitionInfoText.h"
#include "Convert.h"
#include "Project.h"
#include "UndoBuffer.h"
#include "Machine.h"
#include "Const.h"
//#include "dialogs/DTransitionProperties.h"
#include "TransitionPropertiesDlgImpl.h"


/// Constructor
TransitionManager::TransitionManager(MainWindow* m)
{
  main = m;
//  trans_props = new DTransitionProperties;
  trans_props = new TransitionPropertiesDlgImpl((QWidget*)m, 0, TRUE);
}

/// Destructor
TransitionManager::~TransitionManager()
{
  delete trans_props;
}


/**
 * Adds a new transition to the current machine.
 * @param from starting state
 * @param to end state
 * @param numin number of input bits
 * @param numout number of output bits
 * @param sx x coordinate of starting point
 * @param sy y coordinate of starting point
 * @param ex x coordinate of end point
 * @param ey y coordinate of end point
 * @param c1x x coordinate of first control point
 * @param c1y y coordinate of first control point
 * @param c2x x coordinate of second control point
 * @param c2y y coordinate of second control point
 */
bool TransitionManager::addTransition(GState* from, GState* to, int numin, 
                         int numout, double sx, double sy, double ex, 
			 double ey, double c1x, double c1y, double c2x,
			 double c2y)
{
  Machine* m = main->project->machine;
  int mtype;

  mtype = m->getType();

  if (mtype==Binary)
  {
    trans_props->setInputMaxLength(MAX_ASCII_INPUTLENGTH);
    trans_props->setOutputMaxLength(numout);
  }
  else if (mtype==Ascii)
  {
    trans_props->setInputMaxLength(MAX_ASCII_INPUTLENGTH);
    trans_props->setOutputMaxLength(MAX_ASCII_OUTPUTLENGTH);
  }
  else
  {
    trans_props->setInputMaxLength(MAX_TEXT_INPUTLENGTH);
    trans_props->setOutputMaxLength(MAX_TEXT_OUTPUTLENGTH);
  }

  trans_props->resetFields();
  trans_props->setType(mtype);
  //trans_props->setBinMaxLength(numin, numout);
  trans_props->setBinMaxLength(MAX_BIN_INPUTLENGTH, numout);
  trans_props->selectFirst();  
  trans_props->setDescription(""); //"Enter your description here...");
  trans_props->setInvert(FALSE);
  trans_props->setDefaultTransition(FALSE);
  trans_props->setAnyInput(FALSE);
  trans_props->setType(mtype); // once more to properly enable/disable fields

  if (trans_props->exec())
  {
    QString sin, sout;    
    QString description;
//    char in[numin];
//    char out[numout];
    IOInfoBin in(IO_MealyIn), out(IO_MealyOut);
    Convert conv;
    TransitionInfo* info;

//    int len_in, len_out;

    if (trans_props->getAnyInput())
      sin="";

    sin = trans_props->getInputs();
    sout = trans_props->getOutputs();
    description = trans_props->getDescription();

    if (trans_props->getType()==Binary)
    {
      sin.replace(QRegExp(" "), "");
      sout.replace(QRegExp(" "), "");

//      in = conv.binStrToX10(numin, sin, IO_MealyIn);
//      out = conv.binStrToX10(numout, sout, IO_MealyOut);

      in.setInfo(sin);
      out.setInfo(sout);
      in.setSize(numin);
      out.setSize(numout);

      info = new TransitionInfoBin(/*numin,*/ in/*, numout*/, out);

    }
    else if (trans_props->getType()==Ascii)
    {
      sin.replace(QRegExp(" "), "");
      sout.replace(QRegExp(" "), "");

      info = new TransitionInfoASCII(sin, sout);
    }
    else
    {
      info = new TransitionInfoText(sin, sout);
    }
    IOInfo* ininfo = info->getInputInfo();
    ininfo->setInvert(trans_props->getInvert());
    ininfo->setAnyInput(trans_props->getAnyInput());
    ininfo->setDefault(trans_props->getDefaultTransition());

    from->addTransition(main->project, to, info, sx, sy, ex, ey, 
      c1x, c1y, c2x, c2y, description);

    return TRUE;
  }
  return FALSE;
}


/**
 * Straightens the currently selected transitions
 * @param l list of the selected transitions.
 */
void TransitionManager::straightenSelection(QList<GTransition*>* l)
{
  QListIterator<GTransition*> ti(*l);
  GTransition* t;

  if (ti.hasNext())
    main->project->getUndoBuffer()->changeTransitions(l);

  for(; ti.hasNext();)
  {
    t = ti.next();
    t->straighten();
  }
}

/**
 * Edit a transition.
 * @param m machine containing the transition
 * @param t transition to edit
 */
void TransitionManager::editTransition(Machine* m, GTransition* t)
{
  QString sin, sout;  
  QString description;
  TransitionInfo* info;
  int numin, numout;
  int type;

  info = t->getInfo();
  type = info->getType();
  numin = m->getNumInputs();
  numout = m->getNumOutputs();  
  description = t->getDescription();

  if (type==Binary)
  {
    trans_props->setInputMaxLength(MAX_ASCII_INPUTLENGTH);
    trans_props->setOutputMaxLength(numout);
  }
  else if (type==Ascii)
  {
    trans_props->setInputMaxLength(MAX_ASCII_INPUTLENGTH);
    trans_props->setOutputMaxLength(4);
  }
  else
  {
    trans_props->setInputMaxLength(MAX_TEXT_INPUTLENGTH);
    trans_props->setOutputMaxLength(MAX_TEXT_OUTPUTLENGTH);
  }

  trans_props->resetFields();
  trans_props->setType(type);
  //trans_props->setBinMaxLength(numin, numout);
  trans_props->setBinMaxLength(MAX_BIN_INPUTLENGTH, numout);
  trans_props->selectFirst();  
  trans_props->setDescription(description);

  sin = info->getInputsStr(/*numin*/);
  sout = info->getOutputsStr(/*numout*/);

  if (info->getInputInfo()->getAnyInput() || info->getInputInfo()->isDefault())
    sin="";

  trans_props->setInputs(sin);
  trans_props->setOutputs(sout);
  trans_props->setInvert(info->getInputInfo()->isInverted());
  if (info->getInputInfo()->isInverted())
    trans_props->invertClicked();
  trans_props->setAnyInput(info->getInputInfo()->getAnyInput());
  if (info->getInputInfo()->getAnyInput())
    trans_props->anyClicked();
  trans_props->setDefaultTransition(info->getInputInfo()->isDefault());
  if (info->getInputInfo()->isDefault())
    trans_props->defaultClicked();
  trans_props->setType(type); // once more to properly enable/disable fields

  if (trans_props->exec())
  {
    main->project->getUndoBuffer()->changeTransition(t);

    sin = trans_props->getInputs();
    sout = trans_props->getOutputs();
    type = trans_props->getType();    
    description = trans_props->getDescription();

    sin.replace(QRegExp(" "), "");
    sout.replace(QRegExp(" "), "");

    delete info;
    if (type==Binary)
      info = new TransitionInfoBin();
    else if (type==Ascii)
      info = new TransitionInfoASCII();
    else
      info = new TransitionInfoText();

    t->setInfo(info);
    t->setDescription(description);
    info->setInputs(sin, numin);
    info->setOutputs(sout, numout);
    IOInfo* ininfo = info->getInputInfo();
    ininfo->setInvert(trans_props->getInvert());
    ininfo->setAnyInput(trans_props->getAnyInput());
    ininfo->setDefault(trans_props->getDefaultTransition());

    main->project->setChanged();
    main->updateAll();
    main->repaintViewport();
  }
}

