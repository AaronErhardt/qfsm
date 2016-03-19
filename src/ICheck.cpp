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

#include <math.h>
#include <qcursor.h>
#include <QProgressDialog>
#include <QString>
#include "ICheck.h"
#include "Machine.h"
#include "GState.h"
#include "GTransition.h"
#include "TransitionInfo.h"
#include "IOInfoBin.h"
#include "MainWindow.h"
#include "Convert.h"


/// Constructor
ICheck::ICheck(QWidget* m)
{
  main = (MainWindow*)m;
  icheckdlg = new ICheckDlgImpl(m);
}

/// Destructor
ICheck::~ICheck()
{
  delete icheckdlg;
}


/// Performs the whole set of checks and updates the dialog
int ICheck::checkMachine(Machine* m)
{
  QProgressDialog progress("Checking machine...", "Cancel", 0, 5);
  progress.setWindowModality(Qt::WindowModal);
  progress.setMinimumDuration(1000);



  if (m==NULL)
    return -1;

  progress.setValue(0);
  progress.setLabelText(QObject::tr("Check unambiguous conditions"));



  protocol=QString("");
  m->resetMarks();

  m->updateDefaultTransitions();

  double comp, sreach, esreach, connect;
  QString stmp;

  main->setCursor(Qt::WaitCursor);

  protocol+="Check: unambiguous conditions..\n";
  icheckdlg->setUnambiguous(checkUnambiguousCond(m, main->getOptions()));

  progress.setValue(1);
  progress.setLabelText(QObject::tr("Check deadlocks"));


  icheckdlg->setInitial(checkInitialState(m));
  icheckdlg->setFinal((checkFinalState(m)));
  protocol+="Check: deadlocks..\n";
  icheckdlg->setNoDeadLocks(checkDeadLocks(m));

  progress.setLabelText(QObject::tr("Check completeness"));
  progress.setValue(2);


  protocol+="Check: completeness..\n";

  comp = checkCompleteness(m);
  stmp = QString::number(int(comp*100+0.5)) + "%";

  progress.setValue(3);
  progress.setLabelText(QObject::tr("Check state codes"));



  if (m->getType()==Text)
  {
    icheckdlg->setComplete("");
    icheckdlg->enableCompleteness(FALSE);
  }
  else
  {
    icheckdlg->enableCompleteness(TRUE);
    icheckdlg->setComplete(stmp);
  }
  protocol+="Check: unambiguous state codes..\n";
  icheckdlg->setStateCodes(checkStateCodes(m));

  progress.setValue(4);
  progress.setLabelText(QObject::tr("Check reachable states"));


  protocol+="Check: states reachable..\n";
  sreach = checkStatesReachable(m);

  progress.setValue(5);

  stmp = QString::number(int(sreach*100+0.5)) + "%";
  icheckdlg->setStatesReachable(stmp);

  protocol+="Check: end states reachable..\n";
  esreach = checkFinalStatesReachable(m);
  stmp = QString::number(int(esreach*100+0.5)) + "%";
  icheckdlg->setFinalStatesReachable(stmp);

  protocol+="Check: connections..\n";
  connect = checkConnections(m);
  stmp = QString::number(int(connect*100+0.5)) + "%";
  icheckdlg->setTransConnected(stmp);

  main->setCursor(Qt::ArrowCursor);
  main->repaintViewport();
  
  icheckdlg->setProtocolText(protocol);
  qDebug("Protocol:");
  qDebug(protocol);
  qDebug("End Protocol");


  return 0;
}


/// Checks if there are ambiguous conditions
bool ICheck::checkUnambiguousCond(Machine* m, Options* opt)
{
  GState* s;
  GTransition *t, *ttmp;
  TransitionInfo *info, *infotmp;
  bool ret=TRUE;
  

  QMutableListIterator<GState*> sit(m->getSList());
  for(; sit.hasNext();)
  {
    s = sit.next();

    if (!s->isDeleted())
    {
      protocol+=QString("  checking state: "+s->getStateName());
      /*
      QMutableListIterator<GTransition*> tit(s->tlist);
      for(; tit.hasNext();)
      {
      t = tit.next();
      if (!t->isDeleted())
      {
      info = t->getInfo();

      QMutableListIterator<GTransition*> tit2(s->tlist);
      for(; tit2.hasNext();)
      {
      ttmp = tit2.next();
      if (!ttmp->isDeleted())
      {
      infotmp = ttmp->getInfo();
      if (infotmp!=info)
      {
      if (info->intersection(infotmp))
      return FALSE;
    }
    }
    }
    }
    }
      */
      QString sin, sintmp;
      for(int tit=0; tit<s->tlist.size(); tit++)
      {
        t = s->tlist[tit];
        if (!t->isDeleted())
        {
          info = t->getInfo();

          for(int tit2=tit+1; tit2<s->tlist.size(); tit2++)
          {
            ttmp = s->tlist[tit2];
            if (!ttmp->isDeleted())
            {
              infotmp = ttmp->getInfo();
	      //if (infotmp!=info)
              {
                if (info->intersection(infotmp))
                {
                  ret=false;
                  s->setMark(true);
                  //protocol+=" ambiguous condition "+info->getInputsStr()+" ";
                  protocol+=" ambiguous condition "+info->getCompleteInputsStr(m, opt)+"<->"+infotmp->getCompleteInputsStr(m, opt)+" ";
                }
              }
            }
          }
        }
      }
      protocol+="\n";
    }
  }
  return ret;
}

/// Checks if the machine @a m has an initial state
bool ICheck::checkInitialState(Machine* m)
{
  if (m->getInitialState()==NULL)
    return FALSE;
  return TRUE;
}

/// Checks if the machine @a m has at least one final state
bool ICheck::checkFinalState(Machine* m)
{
  QMutableListIterator<GState*> it(m->getSList());
  GState* s;
  for(; it.hasNext();)
  {
    s = it.next();
    if (!s->isDeleted() && s->isFinalState())
      return TRUE;
  }
  return FALSE;
}

/// Checks if there are dead locks in the machine @a m
bool ICheck::checkDeadLocks(Machine* m)
{
  /*
  GState *s, *es;
  QList<GState*> elist = m->getEndStates();
//  elist.setAutoDelete(FALSE);

  QMutableListIterator<GState*> it(m->getSList());
  for(; it.hasNext();)
  {
    s = it.next();

    if (!s->isDeleted())
    {
      bool deadlock=TRUE;
      QMutableListIterator<GState*> eit(elist);
      while (eit.hasNext() && deadlock)
      {
	es = eit.next();
	QList<GState*> visited, ivisited;
	if (isStateReachable(m, s, es, &visited) || 
	    !isStateReachable(m, m->getInitialState(), s, &ivisited))
	  deadlock=FALSE;
      }

      // check loops of non-end states

      if (!s->isEndState() && m->getNumInputs()<=31)
      {
	bool loop=TRUE;
	int i=0;
	int comb = (int)pow(2.0, m->getNumInputs());
	IOInfo *io_out;

	while (i<comb && loop)
	{
	  IOInfoBin iobin(IO_MealyIn, i, m->getNumInputs());
	  if (s->next(&iobin, io_out)!=s)
	    loop=FALSE;
	  i++;
	}
	if (loop)
	  deadlock=TRUE;
      }

      if (deadlock)
	return FALSE;
    }
  }
  return TRUE;
  */
  /*
  QList<GState*> visited_states, blocking_states;
  return !isStateBlocking(m->getInitialState(), visited_states, blocking_states);
  */
  QList<GState*> blocking = m->getSList();
  QList<GState*> visited; // = m->getEndStates();
  //QListIterator<GState*> eit(m->getEndStates());
  QList<GState*> templist = m->getFinalStates();;
  GState *stmp, *sstart;
  GTransition* t;

  // compute blocking states starting reversely from the end states
  while (templist.count()>0)
  {
    stmp = templist.takeFirst();
    if (!visited.contains(stmp))  // not yet visited
    {
      //qDebug("Visiting: %s", stmp->getStateName().latin1());
      visited.append(stmp);

      QListIterator<GTransition*> it(stmp->reflist);
      for( ; it.hasNext(); )
      {
	t = it.next();
	sstart = (GState*)t->getStart();
	if (!t->isDeleted() && !sstart->isDeleted() && sstart!=m->getPhantomState() && sstart!=stmp)
	{
	  templist.append(sstart);
	  //qDebug("  appending: %s", sstart->getStateName().latin1());
	}
      }
    }
    blocking.removeAll(stmp);
  }
  // for debugging
  /*
  qDebug("Blocking states:");
  QListIterator<GState*> it(blocking);
  for(; it.hasNext();)
  {
    qDebug("%s", it.next()->getStateName().latin1());
  }
  */
  // end debugging

  return (blocking.count()==0);
}


/// Checks if the machine @a m is complete (i.e. all possible input values are covered)
double ICheck::checkCompleteness(Machine* m)
{
  double rate;
  int match; //, nonmatch=0;
  int total_match;
  int nmaxinputs;
  int nstates;
  GState* s;
  IOInfo* io_out;
  int ntrans;
  GState* phantom = m->getPhantomState();
  GState* snext;

  if (m->countStates()<2)
    return 1;

  nmaxinputs = (int)pow(2.0, m->getNumInputs());
  nstates=0;
  total_match=0;

  QMutableListIterator<GState*> si(m->getSList());
  for(; si.hasNext();)
  {
    s = si.next();

    match=0;
    if (!s->isDeleted())
    {
      protocol+="  checking state:  "+s->getStateName();
      /*
      int in;
      in = (int)pow(2.0, m->getNumInputs());
      */
      ntrans = s->countTransitions();
      if (s->hasDefaultTransition() || s->hasAnyTransition())
        match=nmaxinputs;
      else if (ntrans>1)
      {
        for(int i=0; i<nmaxinputs; i++)
        {
          IOInfoBin iobin(IO_MealyIn, i, m->getNumInputs());
          snext = s->next(&iobin, io_out);
          if (snext && snext!=phantom)
            match++;
	  /*
          else
          nonmatch++;
      */
        }
      }
      else if (ntrans==0)
        match=0;
      else  // ntrans==1
      {
        bool deleted=true;
        QListIterator<GTransition*> it(s->tlist);
        GTransition* ttmp;
        IOInfo* ioinfo;

        while (deleted)
        {
          ttmp = it.next();
          deleted = ttmp->isDeleted();
          ioinfo = ttmp->getInfo()->getInputInfo();
        }
        match = ioinfo->getNumSingles();
      }
      nstates++;
      if(match!=nmaxinputs)
      {
        s->setMark(true);
        protocol+=" incomplete ";
      }
      protocol+="\n";
    }
    total_match += match;
  }
  
  /*
  if (match+nonmatch>0)
  rate = (double)match/(match+nonmatch);
  else
  rate = 1;
  */
  rate = (double)total_match/(nstates*nmaxinputs);
  return rate;
}

/// Checks if all states of the machine @a m are reachable
double ICheck::checkStatesReachable(Machine* m)
{
  int reach=0, nonreach=0;
  double rate;
  GState* istate;
  GState* s;

  istate = m->getInitialState();

  if (m->countStates()==0)
    return 1;

  if (!istate)
    return 0;

  QMutableListIterator<GState*> it(m->getSList());
  for(; it.hasNext();)
  {
    s = it.next();
    QList<GState*> visited;
    if (!s->isDeleted())
    {
      protocol+="  checking state:  "+s->getStateName();
//      if (isStateReachable(m, istate, it.next(), &visited))
      if (isStateReachable(m, istate, s, &visited))
        reach++;
      else
      {
        nonreach++;
        s->setMark(true);
        protocol+=" unreachable ";
      }
      protocol+="\n";
    }
  }

  if (reach+nonreach>0)
    rate = (double)reach/(reach+nonreach);
  else
    rate = 1;
  return rate;
}


/// Checks if all end states of the machine @a m are reachable
double ICheck::checkFinalStatesReachable(Machine* m)
{
  int reach=0, nonreach=0;
  double rate;
  GState* istate;
  GState* s;

  istate = m->getInitialState();

  if (m->countStates()==0)
    return 1;

  if (!istate)
    return 0;

  QMutableListIterator<GState*> it(m->getSList());
  for(; it.hasNext();)
  {
    s = it.next();

    if (!s->isDeleted() && s->isFinalState())
    {
      QList<GState*> visited;
//      if (isStateReachable(m, istate, it.current(), &visited))
      if (isStateReachable(m, istate, s, &visited))
	reach++;
      else 
	nonreach++;
    }
  }

  if (reach+nonreach>0)
    rate = (double)reach/(reach+nonreach);
  else
    rate = 1;
  return rate;
}

/// Checks if all transitions starting from a state have an end state
double ICheck::checkConnections(Machine* m)
{
  int connect=0, nonconnect=0;
  double rate;
  QMutableListIterator<GState*> it(m->getSList());
  GState* s;
  GTransition* t;

  for(; it.hasNext();)
  {
    s = it.next();
    if (!s->isDeleted())
    {
      protocol+="  checking state: "+s->getStateName();
      QMutableListIterator<GTransition*> jt(s->tlist);
      for(; jt.hasNext();)
      {
	t = jt.next();
	if (t->getEnd()==NULL)
    {
	  nonconnect++;
      protocol+=" "+t->getInfo()->getInputsStrBin()+" not connected ";
    }
	else
	  connect++;
      }
    }
    protocol+="\n";
  }

  s = m->getPhantomState();
  QMutableListIterator<GTransition*> jt(s->tlist);
  protocol+="  transitions without start state: ";
  for(; jt.hasNext();)
  {
    
    t = jt.next();
//    if (t->getEnd()!=NULL)  
      nonconnect++;
      protocol+=" "+t->getInfo()->getInputsStrBin();
  }
  protocol+="\n";

  if (connect+nonconnect>0)
    rate = (double)connect/(nonconnect+connect);
  else
    rate = 1;
  return rate;
}


/// Checks if all state codes were used only once
bool ICheck::checkStateCodes(Machine* m)
{
  bool ret=true,codeComplete;
  int stateCodeCount,c,stateCodeSize;
  QListIterator<GState*> i1(m->getSList());
  GState* s1,*s2;

  while(i1.hasNext())
  {
    s1 = i1.next();
    if (!s1->isDeleted())
    {
      protocol+="  checking state: "+s1->getStateName();
      QListIterator<GState*> i2(m->getSList());
      i2.findNext(s1);
      while( i2.hasNext())
      {
        s2=i2.next();
        if(s2->getEncoding()==s1->getEncoding())
        {
          ret=false;
          protocol+=" Code "+s1->getCodeStr()+" also used for state "+s2->getStateName();
        }
      }
    }
    protocol+="\n";
  }

  

  stateCodeSize=m->getNumEncodingBits();

  stateCodeCount=1<<stateCodeSize;

  codeComplete=true;
  Convert conv;

  for(c=0; c<stateCodeCount; c++)
  {
    if(m->getState(c)==NULL)
    {
      if(codeComplete)
        protocol+="Unused state codes:";
      protocol+=" "+conv.intToBinStr(c,stateCodeSize);
      codeComplete=false;
    }
  }
  if(!codeComplete)
    protocol+="\n";

  return ret;
}



/**
 * Checks recursively if a state is reachable from another state
 *
 * @param m Machine that contains the states
 * @param from Starting state
 * @param state State that is to be checked for reachability
 * @param visited List of visited states.
 * @returns TRUE if state @a state is reachable from state @a from.
 */
bool ICheck::isStateReachable(Machine* m, GState* from, GState* state, 
    QList<GState*>* visited)
{
  GTransition* t;
  GState* s;

//  visited->setAutoDelete(FALSE);

  if (!from || !state)
    return FALSE;

  if (from==state)
    return TRUE;

//  QListIterator<GState> it(m->getSList());
  visited->append(state);

  QListIterator<GTransition*> it(state->reflist);
  for(; it.hasNext();)
  {
    t = it.next();
    if (!t->isDeleted())
    {
      s = (GState*)t->getStart();
      if (s && s!=m->getPhantomState() && !s->isDeleted() && !visited->contains(s))
      {
	if (isStateReachable(m, from, s, visited))
	  return TRUE;
      }
    }
  }
  return FALSE;
}

/**
 * Connects the Machine m to the current ICheckDlg
 *
 * @param m Machine that contains the states
 */
void ICheck::connectMachine(Machine*m)
{
  QObject::connect(icheckdlg,SIGNAL(finished(int)),m,SLOT(checkFinished(int)));
  //QObject::connect(icheckdlg,SIGNAL(finished(int)),main,SLOT(repaintViewport()));
}

/**
 * Disconnects the Machine m from the current ICheckDlg
 *
 * @param m Machine that contains the states
 */
void ICheck::disconnectMachine(Machine*m)
{
  QObject::disconnect(icheckdlg,SIGNAL(finished(int)),m,SLOT(checkFinished(int)));
  //QObject::disconnect(icheckdlg,SIGNAL(finished(int)),main,SLOT(repaintViewport()));
}


/*
bool ICheck::isStateBlocking(GState* state, QList<GState*> visited_states, QList<GState*> blocking_states)
{
  bool result = true;
  GTransition* t;
  int tcount;
  bool self_loop;
  QListIterator<GTransition*> it(state->tlist);

  qDebug("Visiting state %s", state->getStateName().latin1());

  if (state->isEndState())
  {
    if (!visited_states.contains(state))
      visited_states.append(state);
    result = false;
  }
  else   // state is not an end state
  {
    if (!visited_states.contains(state))  // state has not been visited
    {
      qDebug("  not visited");
      if (!visited_states.contains(state))
	visited_states.append(state);

      // count transition and detect self-loops
      self_loop=true;
      tcount=0;
      for(; it.hasNext(); )
      {
	t = it.next();
	if (!t->isDeleted() && !((GState*)t->getEnd())->isDeleted())
	{
	  tcount++;
	  if (t->getEnd()!=state)
	    self_loop=false;
	}
      }

      if (tcount==0 || self_loop)
	result = true;
      else if (tcount>0)
      {
	result=false;
	it.toFront();
	for(; it.hasNext(); )
	{
	  t = it.next();
	  if (!t->isDeleted() && !((GState*)t->getEnd())->isDeleted() && t->getEnd()!=state)
	  {
	    if (isStateBlocking((GState*)t->getEnd(), visited_states, blocking_states))
	    {
	      // TODO find error here
	      qDebug("  %s is marked blocking", state->getStateName().latin1());
	      result = true;
	      continue;
	    }
	  }
	}
      }
    }
    else   // state has been visited
    {
      qDebug("  visited");
      result = blocking_states.contains(state);
    }
  }
  if (result==true && !blocking_states.contains(state))
    blocking_states.append(state);
  else if (result==false)
    blocking_states.removeAll(state);

  qDebug("Result %s: %d", state->getStateName().latin1(), result);

  return result;
}
*/


