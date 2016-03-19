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

#include "UndoBuffer.h"
#include "GState.h"
#include "Project.h"
#include "Machine.h"
#include "GTransition.h"
#include "MainWindow.h"
#include "Selection.h"
#include "DrawArea.h"


/// Constructor
UndoBuffer::UndoBuffer(QObject* parent)
{
  project = (Project*)parent;
//  undolist.setAutoDelete(TRUE);
}

/// Destructor
UndoBuffer::~UndoBuffer()
{
  tidyUp();
  undolist.clear();
//  while (undolist.removeLast());
}


/// Tidys up old undo actions.
void UndoBuffer::tidyUp()
{
  QListIterator<Undo*> i(undolist);

  Undo* u;
  GTransition* t;
  GITransition* it;
  QList<GTransition*>* l;

  for(; i.hasNext();)
  {
    u = i.next();
    
    switch (u->getAction())
    {
      case ChangeState:
        delete u->getState();
	break;
      case ChangeTransition:
        delete u->getTransition();
	break;
      case ChangeInitialTransition:
        delete u->getInitialTransition();
	break;
      case ChangeTransitions:
	l = u->getTList();
	t = l->first();
//	while (l->remove());
	while (!l->isEmpty())
	  delete l->takeFirst();
	break;
      case SetInitialState:
	it = u->getInitialTransition();
        if (it)
	  delete it;
    }
  }
}

/**
 * Adds undo information about adding a state.
 * @param s state which was added
 */
void UndoBuffer::addState(Machine* m, GState* s)
{
  Undo* undo = new Undo(project);
  undo->setModified(project->hasChanged());
  undo->setAction(AddState);
  undo->setState(s);

  if (s==m->getInitialState())
    undo->setInitialTransition(m->getInitialTransition());
  else
    undo->setInitialTransition(NULL);

  undolist.append(undo);
}

/**
 * Adds undo information about adding a transition.
 * @param t transition which was added
 */
void UndoBuffer::addTransition(GTransition* t)
{
  Undo* undo = new Undo(project);
  undo->setModified(project->hasChanged());

  undo->setAction(AddTransition);
  undo->setTransition(t);

  undolist.append(undo);
}
  
/**
 * Adds undo information about changing a state.
 * @param old state containing old information
 * @param newSt state containing new information
 * @param oldit information about the old initial transition
 */
void UndoBuffer::changeState(GState* old, GState* newSt, GITransition* oldit)
{
  Undo* undo = new Undo(project);
  undo->setModified(project->hasChanged());
  undo->setAction(ChangeState);
  
  GState* tmp = new GState(project->machine);
  GITransition* it;

  tmp->copyAttributes(old);
  tmp->copyTransitions(old);

  QListIterator<GTransition*> i(newSt->tlist);
  QListIterator<GTransition*> j(newSt->reflist);
  QList<GTransition*>* ulist;

  ulist = undo->getCopyList();

  for(; i.hasNext();)
    ulist->append(i.next());
  for(; j.hasNext();)
    ulist->append(j.next());

  if (newSt==project->machine->getInitialState())
    it = new GITransition(*oldit);
  else
    it=NULL;

  undo->setInitialTransition(it);

//  ulist->setAutoDelete(FALSE);

  undo->setState(tmp);
  undo->setState2(newSt);

  undolist.append(undo);
}
 

/**
 * Adds undo information about changing a transition.
 * @param t transition containing old information
 */
void UndoBuffer::changeTransition(GTransition* t)
{
  if (!t)
    return;

  Undo* undo = new Undo(project);
  undo->setModified(project->hasChanged());
  undo->setAction(ChangeTransition);

  GState *oldstart=NULL, *oldend=NULL;
  if (t)
  {
    oldstart = (GState*)t->getStart();
    oldend = (GState*)t->getEnd();
  }

  GTransition* tmp = new GTransition();
  *tmp = *t;

  undo->setTransition(tmp);
  undo->setTransition2(t);
  undo->setState(oldstart);
  undo->setState2(oldend);

  undolist.append(undo);
}


/**
 * Adds undo information about changing several transitions
 * @param tl list containing transitions with old information
 */
void UndoBuffer::changeTransitions(QList<GTransition*>* tl)
{
  Undo* undo = new Undo(project);
  undo->setModified(project->hasChanged());
  undo->setAction(ChangeTransitions);

  QListIterator<GTransition*> i(*tl);

  GTransition* tmp;

  for(; i.hasNext();)
  {
    tmp = new GTransition();
    *tmp = *i.peekNext();

    undo->getTList()->append(tmp);
    undo->getTList2()->append(i.next());
  }

  undolist.append(undo);
}

/**
 * Adds undo information about changing the initial transition.
 * @param t initial transition containing old information
 */
void UndoBuffer::changeInitialTransition(GITransition* t)
{
  Undo* undo = new Undo(project);
  undo->setModified(project->hasChanged());
  undo->setAction(ChangeInitialTransition);

  GITransition* tmp= new GITransition();
  *tmp = *t;

  undo->setInitialTransition(tmp);

  undolist.append(undo);
}


/**
 * Adds undo information about moving several objects
 * @param sl list of moved states with old information
 * @param tl list of moved transitions with old information
 * @param movedbyx x value the objects were moved by
 * @param movedbyy y value the objects were moved by
 */
void UndoBuffer::moveMultiple(QList<GState*>* sl, QList<GTransition*>* tl,
		double movedbyx, double movedbyy)
{
  Undo* undo = new Undo(project);
//  QList<GObject>* sellist= undo->getSelList();
  QList<GState*> ssellist;
  QList<GTransition*> tsellist;
//  ssellist.setAutoDelete(FALSE);
//  tsellist.setAutoDelete(FALSE);
  
  undo->setModified(project->hasChanged());
  undo->setAction(MoveMultiple);

  undo->setMovedBy(movedbyx, movedbyy);

  ssellist = project->getMain()->getScrollView()->getDrawArea()->getSelection()->getSList();
  tsellist = project->getMain()->getScrollView()->getDrawArea()->getSelection()->getTList();

  QListIterator<GState*> si(ssellist);
  QListIterator<GTransition*> ti(tsellist);
  for(; si.hasNext();)
    undo->getSList2()->append(si.next());
  for(; ti.hasNext();)
    undo->getTList2()->append(ti.next());


  QListIterator<GState*> i(*sl);
  QListIterator<GTransition*> j(*tl);


  for(; i.hasNext();)
    undo->getSList()->append(i.next());
  for(; j.hasNext();)
    undo->getTList()->append(j.next());

  undolist.append(undo);
}


/**
 * Adds undo information about deleting the selection
 * @param sl list of deleted states
 * @param tl list of deleted transitions
 */
void UndoBuffer::deleteSelection(QList<GState*>* sl, QList<GTransition*>* tl)
{
  Undo* undo = new Undo(project);
  undo->setModified(project->hasChanged());
  undo->setAction(DeleteSelection);
  
//  QListIterator<GState> si(*undo->getSList());
//  QListIterator<GTransition> ti(*undo->getTList());
  QListIterator<GState*> si(*sl);
  QListIterator<GTransition*> ti(*tl);
  GTransition* t;
  GITransition* it=NULL;

  // delete states
  for(; si.hasNext();)
  {
    GState* s;
    
    s = si.next();

    QListIterator<GTransition*> i(s->tlist);
    QListIterator<GTransition*> j(s->reflist);
    dtlist* dl = new dtlist;

    for(;i.hasNext();)
    {
      t = i.next();
      dl->tlist.append(t);
    }
    for(;j.hasNext();)
    {
      t = j.next();
      dl->rlist.append(t);
    }
    undo->getSList()->append(s);
    undo->getDoubleTList()->append(dl);

    if (s==project->machine->getInitialState())
    {
      it = new GITransition(*project->machine->getInitialTransition());
      undo->setInitialState(s);
    }
  }

  // delete transitions
  for(; ti.hasNext();)
  {
    t = ti.next();

    undo->getTList()->append(t);
  }

  undo->setInitialTransition(it);

  undolist.append(undo);
}



/// Adds undo information about deleting the state @a s
void UndoBuffer::deleteState(GState* s)
{
  Undo* undo = new Undo(project);
  undo->setModified(project->hasChanged());
  undo->setAction(DeleteState);
  
//  QListIterator<GState> si(*sl);
//  QListIterator<GTransition> ti(*tl);
  GTransition* t;
  GITransition* it=NULL;


  QListIterator<GTransition*> i(s->tlist);
  QListIterator<GTransition*> j(s->reflist);
  dtlist* dl = new dtlist;

  for(;i.hasNext();)
  {
    t = i.next();
    dl->tlist.append(t);
  }
  for(;j.hasNext();)
  {
    t = j.next();
    dl->rlist.append(t);
  }
//  undo->getSList()->append(s);
  undo->setState(s);
  undo->getDoubleTList()->append(dl);

  if (s==project->machine->getInitialState())
  {
    it = new GITransition(*project->machine->getInitialTransition());
    undo->setInitialState(s);
  }

  undo->setInitialTransition(it);

  undolist.append(undo);
}



/// Adds undo information about deleting the transition @a t
void UndoBuffer::deleteTransition(GTransition* t)
{
  Undo* undo = new Undo(project);
  undo->setModified(project->hasChanged());
  undo->setAction(DeleteTransition);

//  undo->getTList()->append(t);
  undo->setTransition(t);

  undolist.append(undo);
}

/**
 * Adds undo information about setting the initial state
 * @param t old initial transition
 */
void UndoBuffer::setInitialState(GITransition* t)
{
  Undo* undo = new Undo(project);
  undo->setModified(project->hasChanged());
  undo->setAction(SetInitialState);

  GITransition* tmp;

  if (t)
  {
    tmp= new GITransition();
    *tmp = *t;
  }
  else 
    tmp = NULL;

  undo->setInitialTransition(tmp);

  undolist.append(undo);
}  

/**
 * Adds undo information about setting/resetting the end state
 * @param s state that is to toggle its state
 */
void UndoBuffer::setFinalStates(const QList<GState*>& sl)
{
  Undo* undo = new Undo(project);
  undo->setModified(project->hasChanged());
  undo->setAction(SetFinalStates);

  *(undo->getSList()) = sl;
//  undo->getSList()->setAutoDelete(FALSE);

  undolist.append(undo);
}  


/**
 * Adds undo information about changing the properties of the machine.
 * @param m machine containing the old properties
 */
void UndoBuffer::changeMachine(Machine* m)
{
  Undo* undo = new Undo(project);
  undo->setModified(project->hasChanged());
  undo->setAction(ChangeMachine);

  QString n;
  int nb, ni, no;
  QFont sf, tf;
  int at, t;
  bool dit;

  n = m->getName();
  t = m->getType();
  nb = m->getNumMooreOutputs();
  ni = m->getNumInputs();
  no = m->getNumOutputs();
  sf = m->getSFont();
  tf = m->getTFont();
  at = m->getArrowType();
  dit = m->getDrawITrans();

  undo->setMachineInfo(m, n, t, nb, m->getMooreOutputList(), ni, m->getInputNameList(), 
    no, m->getOutputNameList(), sf, tf, at, dit);

  undolist.append(undo);
}


/**
 * Adds undo information about pasting in objects
 *
 * @param sl List of states that were pasted
 * @param tl List of transitions that were pasted
 * @param oldistate Old initial state
 * @param newistate New initial state
 * @param olditrans Old initial transition
 * @param newitrans New initial transition
 * @param numbits Old number of bits
 * @param numin Old number of inputs
 * @param numout Old number of outputs
 */
void UndoBuffer::paste(QList<GState*>* sl, QList<GTransition*>* tl, GState* oldistate,
  GState* newistate, GITransition* olditrans, GITransition* newitrans, int numbits,
  int numin, int numout)
{
  Undo* undo = new Undo(project);
  undo->setModified(project->hasChanged());

  undo->setAction(Paste);
  *(undo->getSList()) = *sl;
  *(undo->getTList()) = *tl;
//  undo->getSList()->setAutoDelete(FALSE);
//  undo->getTList()->setAutoDelete(FALSE);
  undo->setState(oldistate);
  undo->setState2(newistate);
  undo->setInitialTransition(olditrans);
  undo->setInitialTransition2(newitrans);
  undo->setNumMooreOutputs(numbits);
  undo->setNumInputs(numin);
  undo->setNumOutputs(numout);

  undolist.append(undo);
}




/// Undo the last action.
void UndoBuffer::undo()
{
  Undo* u;

  u = undolist.last();

  if (u)
  {
    switch (u->getAction())
    {
      case AddState: undoAddState(u); break;
      case AddTransition: undoAddTransition(u); break;
      case ChangeState: undoChangeState(u); break;
      case ChangeTransition: undoChangeTransition(u); break;
      case ChangeInitialTransition: undoChangeInitialTransition(u); break;
      case ChangeTransitions: undoChangeTransitions(u); break;
      case MoveMultiple: undoMoveMultiple(u); break;
      case DeleteSelection: undoDeleteSelection(u); break;
      case DeleteState: undoDeleteState(u); break;
      case DeleteTransition: undoDeleteTransition(u); break;
      case SetInitialState: undoSetInitialState(u); break;
      case SetFinalStates: undoSetFinalStates(u); break;
      case ChangeMachine: undoChangeMachine(u); break;
      case Paste: undoPaste(u); break;
    }
    project->setChanged(u->getModified());
 //   undolist.remove();
    delete undolist.takeLast();
  }
}



/// Undo adding a state
void UndoBuffer::undoAddState(Undo* u)
{
  Project* p;
  int i;
  //QList <GState*> l;
  p = u->getProject();

  if (u->getInitialTransition())
  {
    delete p->machine->getInitialTransition(); //u->getInitialTransition();
    p->machine->setInitialTransition(NULL);
    u->setInitialTransition(NULL);
  }

  p->getMain()->getScrollView()->getDrawArea()->getSelection()->select(u->getState(), FALSE);
//  p->machine->getSList().removeRef(u->getState());
  //l=p->machine->getSList();
  i = p->machine->getSList().indexOf(u->getState());
  if (i != -1)
    delete p->machine->getSList().takeAt(i);
}

/// Undo adding a transition.
void UndoBuffer::undoAddTransition(Undo* u)
{
  Project* p;
  p = u->getProject();

  GTransition* t;
  GState *from, *to;
  t = u->getTransition();

  from = (GState*)t->getStart();
  to = (GState*)t->getEnd();

  p->getMain()->getScrollView()->getDrawArea()->getSelection()->select(t, FALSE);
//  if (t->isSelected())
//    t->select(FALSE);

  if (to)
    to->reflist.remove(t);
  if (from)
    from->tlist.remove(t);

}

/// Undo changing a state.
void UndoBuffer::undoChangeState(Undo* u)
{
  Project* p;
  p = u->getProject();

  GState *olds, *news;
  GITransition* oldit;
  bool sel;

  olds = u->getState();
  news = u->getState2();

  sel = news->isSelected();
  news->copyAttributes(olds);
  news->select(sel);

  news->copyTransitionAttributes(olds, u->getCopyList());

  oldit = u->getInitialTransition();
  if (oldit)
  {
    GITransition* t;
    t = project->machine->getInitialTransition();
    if (t)
      *t=*oldit;
    delete oldit;
  }

  news->setTransitionsToRadius(project->machine, news->getRadius());

//  news->tlist.setAutoDelete(TRUE);
//  olds->tlist.setAutoDelete(TRUE);
//  olds->reflist.setAutoDelete(TRUE);
  delete olds;
}

  
/// Undo changing a transition
void UndoBuffer::undoChangeTransition(Undo* u)
{
  Project* p;
  p = u->getProject();
  bool result;
  bool sel;

  GTransition *oldt, *newt;
  GState *oldstart, *oldend, *newstart, *newend;

  oldt = u->getTransition();
  newt = u->getTransition2();

  newstart = (GState*)newt->getStart();
  newend = (GState*)newt->getEnd();
  oldstart = u->getState();
  oldend = u->getState2();

  sel = newt->isSelected();
  *newt = *oldt;
  newt->select(sel);

//  newstart->tlist.setAutoDelete(FALSE);
//  result = newstart->tlist.removeRef(newt);
  result = newstart->tlist.removeAll(newt);
//  newstart->tlist.setAutoDelete(TRUE);
  oldstart->tlist.append(newt);

  if (newend)
//    newend->reflist.removeRef(newt);
    newend->reflist.removeAll(newt);
  if (oldend)
    oldend->reflist.append(newt);

  delete oldt;
}


/// Undo changing several transitions.
void UndoBuffer::undoChangeTransitions(Undo* u)
{
  Project* p;
  p = u->getProject();
  bool sel;

  GTransition *oldt, *newt;
  QListIterator<GTransition*> oldti(*u->getTList());
  QListIterator<GTransition*> newti(*u->getTList2());

  for(;oldti.hasNext();)
  {
    oldt = oldti.next();
    newt = newti.next();

    sel = newt->isSelected();
    *newt = *oldt;
    newt->select(sel);
    
    delete oldt;
  }
}


/// Undo changing the initial transition.
void UndoBuffer::undoChangeInitialTransition(Undo* u)
{
  Project* p;
  p = u->getProject();

  GITransition* old;
  GITransition* t;

  old = u->getInitialTransition();
  t = project->machine->getInitialTransition();

  if (old && t)
  {
    *t = *old;
    delete old;
  }
}
  
  

/// Undo moving several objects.
void UndoBuffer::undoMoveMultiple(Undo* u)
{
  Project* p;
  p = u->getProject();

//  QListIterator<GState> i(*u->getSList());
//  QList<GTransition>* tl = u->getTList();
//  GState* s;
//  GTransition* t;
  double x, y;
//  QList<GObject>* sellist;
  Selection* sel;
  QList<GState*>* ssellist;
  QList<GTransition*>* tsellist;
//  bool dragmultiple;
  ScrollView* sv;

  u->getMovedBy(x, y);

  sv = project->getMain()->getScrollView();
  sel = sv->getDrawArea()->getSelection();
  sel->deselectAll(project->machine);
  
  ssellist = u->getSList2();
  tsellist = u->getTList2();

  QListIterator<GState*> sit(*ssellist);
  for(;sit.hasNext();)
    sel->select(sit.next());

  QListIterator<GTransition*> tit(*tsellist);
  for(;tit.hasNext();)
    sel->select(tit.next());

  /*
  for(; i.current(); ++i)
  {
    s = i.current();
    s->move(-x, -y, project->getMain()->getScrollView(), project->machine, FALSE);
  }
  */
//  dragmultiple = sv->getDragMultiple();

  sel->move(-x, -y, project->getMain()->getScrollView()->getDrawArea(), p->machine);

  /*
  s = project->machine->getPhantomState();
  QListIterator<GTransition> j(s->tlist);

  for(; j.current(); ++j)
  {
    t = j.current();
    if (t->getEnd()==NULL && tl->containsRef(t))
      t->move(-x, -y);
  }
  */
  /*
  sit.toFirst();
  for(;sit.current(); ++sit)
    sel->deselect(sit.current());
    */
  sel->deselectAll(p->machine);
}



/// Undo deleting the selection.
void UndoBuffer::undoDeleteSelection(Undo* u)
{
  Project* p;
  p = u->getProject();

  GState *s, *ph;
  GTransition* t;
  GITransition* it=NULL;

  QListIterator<GState*> si(*u->getSList());
  QListIterator<dtlist*> i(*u->getDoubleTList());
  QListIterator<GTransition*> j(*u->getTList());

  ph = p->machine->getPhantomState();

  // undo delete states
  for(; si.hasNext();)
  {
    s = si.next();

    QListIterator<GTransition*> ti1(i.peekNext()->tlist);
    QListIterator<GTransition*> ti2(i.next()->rlist);

    for(; ti1.hasNext();)
    {
      t = ti1.next();
      t->setStart(s);
      s->tlist.append(t);
//      ph->tlist.setAutoDelete(FALSE);
//      ph->tlist.removeRef(t);
      ph->tlist.removeAll(t);
    }
    for(; ti2.hasNext();)
    {
      t = ti2.next();
      t->setEnd(s);
      s->reflist.append(t);
    }
    
    s->setDeleted(FALSE);
  }

  // undo delete transitions
  for(; j.hasNext();)
  {
    t = j.next();

    t->setDeleted(FALSE);
  }
  
  it = u->getInitialTransition();
  if (it)
  {
    project->machine->setInitialTransition(it);
    project->machine->setInitialState(u->getInitialState());
//    delete it;
  }
}


/// Undo deleting a state
void UndoBuffer::undoDeleteState(Undo* u)
{
  Project* p;
  p = u->getProject();

  GState *s, *ph;
  GTransition* t;
  GITransition* it=NULL;

  QListIterator<GState*> si(*u->getSList());
  QListIterator<dtlist*> i(*u->getDoubleTList());
  QListIterator<GTransition*> j(*u->getTList());

  ph = p->machine->getPhantomState();

    s = u->getState();

    QListIterator<GTransition*> ti1(i.peekNext()->tlist);
    QListIterator<GTransition*> ti2(i.next()->rlist);

    for(; ti1.hasNext();)
    {
      t = ti1.next();
      t->setStart(s);
      s->tlist.append(t);
//      ph->tlist.setAutoDelete(FALSE);
//      ph->tlist.removeRef(t);
      ph->tlist.removeAll(t);
    }
    for(; ti2.hasNext();)
    {
      t = ti2.next();
      t->setEnd(s);
      s->reflist.append(t);
    }
    
    s->setDeleted(FALSE);


  it = u->getInitialTransition();
  if (it)
  {
    project->machine->setInitialTransition(it);
    project->machine->setInitialState(u->getInitialState());
  }
}


/// Undo deleting a transition
void UndoBuffer::undoDeleteTransition(Undo* u)
{
  Project* p;
  p = u->getProject();

//  GState *s, *ph;
  GTransition* t;
//  GITransition* it=NULL;

  t = u->getTransition();
  t->setDeleted(FALSE);
}


/// Undo setting the initial state.
void UndoBuffer::undoSetInitialState(Undo* u)
{
  Project* p;
  p = u->getProject();

  GITransition* old;
  GITransition* t;

  old = u->getInitialTransition();
  t = project->machine->getInitialTransition();

  if (old && t)
  {
    *t = *old;
    delete old;
  }
  else if (t && !old)
  {
    delete t;
    t = NULL;
  }
    
  if (old)
    project->machine->setInitialState((GState*)old->getEnd());
  else
  {
    project->machine->setInitialState(NULL);
    project->machine->setInitialTransition(NULL);
  }
}
  

/// Undo setting/resetting the end state
void UndoBuffer::undoSetFinalStates(Undo* u)
{
//  GState* s;
  
  QListIterator<GState*> it(*(u->getSList()));

  for(; it.hasNext();)
    it.next()->toggleFinalState();

}



/// Undo changing the machine properties.
void UndoBuffer::undoChangeMachine(Undo* u)
{
  Project* p;
  p = u->getProject();

  Machine* m;
  QString n;
  int nb, ni, no;
  QFont sf, tf;
  int at, t;
  QStringList ilist, olist, olistm;
  bool dit;

  u->getMachineInfo(m, n, t, nb, olistm, ni, ilist, no, olist, sf, tf, at, dit);

  m->setName(n);
  m->setType(t);
  m->setNumMooreOutputs(nb);
  m->setNumInputs(ni);
  m->setNumOutputs(no);
  m->setMooreOutputList(olistm);
  m->setInputNameList(ilist);
  m->setOutputNameList(olist);
  m->setSFont(sf);
  m->setTFont(tf);
  m->setArrowType(at);
  m->setDrawITrans(dit);
}


/// Undo pasting of objects
void UndoBuffer::undoPaste(Undo* u)
{
  Project* p;
  p = u->getProject();

  QListIterator<GState*> i(*u->getSList());
  QListIterator<GTransition*> j(*u->getTList());

  GState *oldistate, *newistate;
  GITransition *olditrans, *newitrans;
  bool anyobject=FALSE;

  oldistate = u->getState();
  newistate = u->getState2();
  olditrans = u->getInitialTransition();
  newitrans = u->getInitialTransition2();

  if (oldistate!=newistate)
  {
    p->machine->setInitialState(oldistate);
    anyobject=TRUE;
  }
  if (olditrans!=newitrans)
  {
    p->machine->setInitialTransition(olditrans);
    if (newitrans)
      delete newitrans;
    anyobject=TRUE;
  }

  for(; j.hasNext();)
  {
    GState* start;
    start = (GState*)j.peekNext()->getStart();
//    start->tlist.removeRef(j.current());
    delete j.peekNext();
    start->tlist.removeAll(j.next());
//    p->machine->getTList().removeRef(j.current());
    anyobject=TRUE;
  }

  for(; i.hasNext();)
  {
//    p->machine->getSList().removeRef(i.current());
    delete i.peekNext();
    p->machine->getSList().removeAll(i.next());
    anyobject=TRUE;
  }

  if (p->machine->getNumMooreOutputs()!=u->getNumMooreOutputs())
    p->machine->setNumMooreOutputs(u->getNumMooreOutputs());
  if (p->machine->getNumInputs()!=u->getNumInputs())
    p->machine->setNumInputs(u->getNumInputs());
  if (p->machine->getNumOutputs()!=u->getNumOutputs())
    p->machine->setNumOutputs(u->getNumOutputs());

  if (anyobject)
  {
    p->getMain()->getScrollView()->getDrawArea()->reset();
    p->getMain()->updateAll();
  }
}

