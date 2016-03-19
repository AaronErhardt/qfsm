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

#include "Selection.h"
#include "ScrollView.h"
#include "Machine.h"
#include "DrawArea.h"


/// Constructor
Selection::Selection(QWidget* parent, const char* name)
 	  :QObject(parent, name)
{
  itrans=false;
  context_object=NULL;
  co_type=0;
}

/// Destructor
Selection::~Selection()
{
}


/**
 * Selects the object at point @a p.
 * @param sview pointer to scroll view
 * @param m machine containing the objects
 * @param p point on which will be look for an object
 * @param scale current scale
 * @param otype object type of resulting object
 */
GObject* Selection::select(DrawArea* sview, Machine* m, QPoint p,
 			   double scale, int& otype)
{
  GState* tmp;
  GTransition* t;
  GITransition* itr;
  GObject* o;

  if (!m)
    return NULL;

  o = m->getObject(p, scale, otype);
  bool sel=FALSE;

  // clear previous selection

  // clear state selection
  QListIterator<GState*> i(ssel_list);

  for(; i.hasNext();)
  {
    tmp = i.next();
    sel=TRUE;
    tmp->select(FALSE);
  }
  ssel_list.clear();

  // clear transition selection
  QListIterator<GTransition*> it(tsel_list);

  for(; it.hasNext();)
  {
    t = it.next();
    sel=TRUE;
    t->select(FALSE);
  }
  tsel_list.clear();

  // clear initial transition selection
  itr = m->getInitialTransition();
  if (itr)
  {
    itr->select(FALSE);
    sel=TRUE;
    itrans=FALSE;
  }

  // select object
  if (o)
  {
    o->select(); 
    if (otype==StateT)
      ssel_list.append((GState*)o);
    else if (otype==TransitionT)
      tsel_list.append((GTransition*)o);
    else if (otype==ITransitionT)
      itrans=TRUE;

    sview->repaint();
//    emit updateAll();
    return o;
  }
  if (sel)
    sview->repaint();

//  emit updateAll();
  return NULL;

}


/// Selects/deselects the state @a s
void Selection::select(GState* s, bool sel/*=TRUE*/)
{
  if (!s)
    return;

  s->select(sel);
  if (sel)
    ssel_list.append(s);
  else
    ssel_list.remove(s);
}


/// Selects/deselects the transition @a t
void Selection::select(GTransition* t, bool sel/*=TRUE*/)
{
  if (!t)
    return;

  t->select(sel);
  if (sel)
    tsel_list.append(t);
  else
    tsel_list.remove(t);
}

/// Selects/deselects the initial transition @a t
void Selection::select(GITransition* t, bool sel/*=TRUE*/)
{
  if (!t)
    return;

  t->select(sel);
  itrans = sel;
}

/**
 * Select all objects lying in the specified rectangle
 * @param m machine containing the objects
 * @param r rectangle which will be looked in
 * @return TRUE if any object lies in the rectangle otherwise FALSE.
 */
bool Selection::selectRect(Machine* m, DRect& r, bool add)
{
  GState* tmp;
  GTransition* t;
  GITransition* itr;
//  GObject* o;
//  int otype;
  double tmpx, tmpy;
  double tsx, tsy, tex, tey;//, tc1x, tc1y, tc2x, tc2y;
  bool success=FALSE;

  if (!m)
    return FALSE;

//  o = m->getObject(p, scale, otype);
  QList<GState*> ls = m->getSList();
  
  QListIterator<GState*> lsi(ls);

  bool sel=FALSE;

  QListIterator<GState*> i(ssel_list);

  if (!add)
  {
  // clear previous selection
  for(; i.hasNext();)
  {
    tmp = i.next();
    sel=TRUE;
    tmp->select(FALSE);
  }
  ssel_list.clear();

  QListIterator<GTransition*> it(tsel_list);

  for(; it.hasNext();)
  {
    t = it.next();
    sel=TRUE;
    t->select(FALSE);
  }
  tsel_list.clear();
  }

  for(; lsi.hasNext();)
  {
    tmp = lsi.next();
    if (!tmp->isDeleted())
    {
      tmp->getPos(tmpx, tmpy);

      if (r.contains(tmpx, tmpy) )
      {
//	tmp->select();
	tmp->toggleSelect();
	if (tmp->isSelected())
	{
	  ssel_list.append(tmp);
	}
	else if (add)
	  ssel_list.remove(tmp);

	success=TRUE;
      }
      
      QListIterator<GTransition*> lti(tmp->tlist);
      
      for (; lti.hasNext();)
      {
	t = lti.next();
	if (!t->isDeleted())
	{
	  t->getPos(tsx, tsy);
	  t->getEndPos(tex, tey);

	  if (r.contains(tsx, tsy) ||
	      r.contains(tex, tey ))
	  {
	    t->toggleSelect();
//	    t->select();
	    if (t->isSelected())
	    {
	      tsel_list.append(t);
	    }
	    else if (add)
            {
	      tsel_list.remove(t);
	    }
	    success=TRUE;
	  }
        }
      }
    }
  }

  // phantom transitions

  tmp = (GState*)m->getPhantomState();

  QListIterator<GTransition*> pti(tmp->tlist);

  for (; pti.hasNext();)
  {
    t = pti.next();
    if (!t->isDeleted())
    {
      t->getPos(tsx, tsy);
      t->getEndPos(tex, tey);

      if (r.contains(tsx, tsy) ||
	  r.contains(tex, tey ))
      {
//	t->select();
	t->toggleSelect();
        if (t->isSelected())
	{
	  tsel_list.append(t);
	}
	else if (add)
	  tsel_list.remove(t);

	success=TRUE;
      }
    }
  }

  itr = m->getInitialTransition();
  if (itr)
  {
    itr->getEndPos(tex, tey);
    if (r.contains(tex, tey))
    {
//      itr->select();
      itr->toggleSelect();
      if (itr->isSelected())
      {
	itrans=TRUE;
      }
      else if (add)
	itrans=FALSE;
      success=TRUE;
    }
  }

  if (success)
  {
    double le, te, re, be;
    getBoundingRect(le, te, re, be, m->getPhantomState());
    
    r.setCoords(le, te, re, be);
  }

  emit updateAll();
  return success;

}

/**
 * Adds an object to the selection.
 * Searches for an object lying at point @a p and adds it to the current
 * selection.
 * @param sview pointer to scroll view
 * @param m machine containing the objects
 * @param p point on which will be looked for an object
 * @param scale current scale
 * @return TRUE if any object lies at point @p otherwise FALSE.
 */
bool Selection::selectAdd(DrawArea* sview, Machine* m, QPoint p, double scale)
{
//  GState* s;
//  GState* tmp;
//  GTransition* t;
  GObject* o;
  int otype;

  if (!m)
    return FALSE;

  o = m->getObject(p, scale, otype);
  bool sel=FALSE;

  QListIterator<GState*> i(ssel_list);

  if (o)
  {
    if (!o->isSelected())
    {
      o->select(); 
      if (otype==StateT)
	ssel_list.append((GState*)o);
      else if (otype==TransitionT)
	tsel_list.append((GTransition*)o);
      else if (otype==ITransitionT)
        itrans=TRUE;

      sview->repaint();
      emit updateAll();
      return TRUE;
    }
    else
    {
      if (otype==StateT)
        deselect((GState*)o);
      else if (otype==TransitionT)
        deselect((GTransition*)o);
      else if (otype==ITransitionT)
        deselect((GITransition*)o);

      sel=TRUE;
    }
  }
  if (sel)
  {
    sview->repaint();
    emit updateAll();
  }
  return FALSE;

}


/**
 * Checks if a control point of a transition lies at point @a p.
 * @param m machine containing the transitions
 * @param p point on which will be looked for the control point
 * @param scale current scale
 * @param ctrans transition which owns the resulting control point. If no
 *   control point is found ctrans is NULL.
 * @return Type of control point: 
 * @arg 1: start point
 * @arg 2: first control point
 * @arg 3: second control point
 * @arg 4: end point
 */
int Selection::selectControl(Machine* m, QPoint p, double scale, 
			     GTransition*& ctrans)
{
  double x, y;
  int csel;
  GTransition* t;
  GITransition* itr;

  x = p.x()/scale;
  y = p.y()/scale;

  QListIterator<GTransition*> it(tsel_list);

  for(; it.hasNext();)
  {
    t = it.next();
    if (!t->isDeleted())
    {
      csel = t->onControlPoint(x, y, scale);
      if (csel)
      {
	ctrans = t;
	
	return csel;
      }
    }
  }

  itr = m->getInitialTransition();
  if (itr)
  {
    csel = itr->onControlPoint(x, y, scale);
    if (csel)
      return csel;
  }

  ctrans=NULL;
  return 0;
}


/// Selects all objects in the machine @a m and returns the bounding rectangle @a r.
bool Selection::selectAll(Machine* m, DRect& r)
{
  GState* tmp;
  GTransition* t;
  GITransition* itr;
//  double tmpx, tmpy;
//  double tsx, tsy, tex, tey;//, tc1x, tc1y, tc2x, tc2y;
  bool success=FALSE;

  if (!m)
    return FALSE;

  QList<GState*> ls = m->getSList();
  
  QListIterator<GState*> lsi(ls);

//  bool sel=FALSE;

  QListIterator<GState*> i(ssel_list);

  /*
  // clear previous selection
  for(; i.current(); ++i)
  {
    tmp = i.current();
    sel=TRUE;
    tmp->select(FALSE);
  }
  ssel_list.clear();

  QListIterator<GTransition> it(tsel_list);

  for(; it.current(); ++it)
  {
    t = it.current();
    sel=TRUE;
    t->select(FALSE);
  }
  tsel_list.clear();
*/
  ssel_list.clear();
  tsel_list.clear();

  for(; lsi.hasNext();)
  {
    tmp = lsi.next();
    if (!tmp->isDeleted())
    {
	tmp->select();
	ssel_list.append(tmp);
	success=TRUE;
      
      QListIterator<GTransition*> lti(tmp->tlist);
      
      for (; lti.hasNext();)
      {
	t = lti.next();
	if (!t->isDeleted())
	{
	    t->select();
	    tsel_list.append(t);
	    success=TRUE;
        }
      }
    }
  }

  // phantom transitions

  tmp = (GState*)m->getPhantomState();

  QListIterator<GTransition*> pti(tmp->tlist);

  for (; pti.hasNext();)
  {
    t = pti.next();
    if (!t->isDeleted())
    {
	t->select();
	tsel_list.append(t);
	success=TRUE;
    }
  }

  itr = m->getInitialTransition();
  if (itr)
  {
      itr->select();
      itrans=TRUE;
      success=TRUE;
  }

  if (success)
  {
    double le, te, re, be;
    getBoundingRect(le, te, re, be, m->getPhantomState());
    
    r.setCoords(le, te, re, be);
  }

  emit updateAll();
  return success;

}

/**
 * Checks if point @a p lies on a selected object.
 * @param p point on which an object will be looked for
 * @param scale current scale
 * @return TRUE if @a p is on a seleted object otherwise FALSE
 */
bool Selection::onSelectionOld(QPoint p, double scale)
{
  QListIterator<GState*> si(ssel_list);
  QListIterator<GTransition*> ti(tsel_list);
  GState* s;
//  GTransition* t;
  double x, y;
  double rleft, rright, rtop, rbottom;
  double rad;
  double mx, my;

  mx = (double)p.x()/scale;
  my = (double)p.y()/scale;

  if (ssel_list.isEmpty())
    return FALSE;

  for(; si.hasNext();)
  {
    s = si.next();
    s->getPos(x,y);
    rad = s->getRadius();
    
    rleft = x-rad;
    rright = x+rad;
    rtop = y-rad;
    rbottom = y+rad;

    if (mx>rleft && mx<rright && my>rtop && my<rbottom)
      return TRUE;
  }

  return FALSE;
}

/**
 * Checks if point @a p lies on a selected object taking into account that a
 * non-selected state can cover a selected state.
 * @param p point on which an object will be looked for
 * @param m machine containing the objects
 * @param scale current scale
 * @return TRUE if @a p is on a seleted object otherwise FALSE
 */
bool Selection::onSelection(Machine* m, QPoint p, double scale)
{
  QListIterator<GState*> si(m->getSList());
  //QListIterator<GTransition> ti(tsel_list);
  GState* s=NULL;
//  GTransition* t;
  double x, y;
  double rleft, rright, rtop, rbottom;
  double rad;
  double mx, my;
  bool found=FALSE;

  mx = (double)p.x()/scale;
  my = (double)p.y()/scale;

  if (ssel_list.isEmpty())
    return FALSE;

  while(si.hasNext() && !found)
  {
    s = si.next();
    s->getPos(x,y);
    rad = s->getRadius();
    rleft = x-rad;
    rright = x+rad;
    rtop = y-rad;
    rbottom = y+rad;

    if (mx>rleft && mx<rright && my>rtop && my<rbottom && !s->isDeleted())
      found = TRUE;


  }
  if (!found)
    return FALSE;

  if (s && ssel_list.contains(s))
      return TRUE;

  return FALSE;
}


/**
 * Deselects the state @a s.
 * @return TRUE if state was selected otherwise FALSE.
 */
bool Selection::deselect(GState* s)
{
  bool found;

  s->select(FALSE);
  found = ssel_list.remove(s);
  return found;
}

/**
 * Deselects the transition @a t.
 * @return TRUE if transition was selected otherwise FALSE.
 */
bool Selection::deselect(GTransition* t)
{
  bool found;

  t->select(FALSE);
  found = tsel_list.remove(t);
  return found;
}

/**
 * Deselects initial transition @a t.
 * @return TRUE if initial transition was selected otherwise FALSE.
 */
bool Selection::deselect(GITransition* t)
{
  bool wasselected;
  wasselected = t->isSelected();

  t->select(FALSE);
  itrans=FALSE;

  return wasselected;
}


/**
 * Moves selection.
 * @param x x value to move rightwards
 * @param y y value to move downwards
 * @param sv pointer to scrollview
 * @param m machine containing seleted objects
 */
void Selection::move(double x, double y, DrawArea* sv, Machine* m)
{
  QListIterator<GState*> si(ssel_list);
  QListIterator<GTransition*> ti(tsel_list);

  GState* s;
  GTransition* t;

  sv->setDragMultiple();

  for(; si.hasNext();)
  {
    s = si.next();
    s->move(x, y, sv, m, FALSE);
  }
  s = m->getPhantomState();
  QListIterator<GTransition*> pi(s->tlist);

  for(; pi.hasNext();)
  {
    t = pi.next();
    if (t->isSelected() && t->getEnd()==NULL)
      t->move(x, y);
  }

}


/**
 * Returns the bounding rectangle of the selection.
 * @param l x coordinate of left border
 * @param t y coordinate of top border
 * @param r x coordinate of right border
 * @param b y coordinate of bottom border
 * @param phantom pointer to phantom state
 */
void Selection::getBoundingRect(double& l, double& t, double& r, double& b,
				GState* phantom)
{
  double x, y, rad;
  double ex, ey, c1x, c1y, c2x, c2y;

  l = 1000000000;
  t = 1000000000;
  r = -1000000000;
  b = -1000000000;

  QListIterator<GState*> si(ssel_list);
  QListIterator<GTransition*> ti(tsel_list);

  GState *s, *start, *end;
  GTransition* tr;

  for( ;si.hasNext();)
  {
    s = si.next();
    s->getPos(x, y);
    rad = s->getRadius();

    setMinMax(x-rad, y-rad, l, t, r, b);
    setMinMax(x+rad, y+rad, l, t, r, b);
  }

  for( ;ti.hasNext();)
  {
    tr = ti.next();
    start = (GState*)tr->getStart();
    end = (GState*)tr->getEnd();

    if ((end==NULL && start->isSelected()) || 
      (start==phantom && (end==NULL || end->isSelected()) ) )
    {
      tr->getPos(x, y);
      tr->getEndPos(ex, ey);
      tr->getCPoint1(c1x, c1y);
      tr->getCPoint2(c2x, c2y);

      setMinMax(x, y, l, t, r, b);
      setMinMax(ex, ey, l, t, r, b);
      setMinMax(c1x, c1y, l, t, r, b);
      setMinMax(c2x, c2y, l, t, r, b);
    }
  }
}


/**
 * Updates the the maximum rectangle coordinates @a l, @a t, @a r @a b if @x 
 * and @y lye outside of the rectangle
 */
void Selection::setMinMax(double x, double y, double& l, double& t, 
                          double& r, double& b)
{
    if (x<l)
      l=x;
    if (x>r)
      r=x;
    if (y<t)
      t=y;
    if (y>b)
      b=y;
}



/**
 * Updates the bounding rectangle @a rect.
 */
void Selection::updateBoundingRect(DRect& rect, GState* phantom)
{
  double l, t, r, b;

  getBoundingRect(l, t, r, b, phantom);

  rect.setCoords(l, t, r, b);

}


/**
 * Deselects all selected objects in the machine @a m.
 */
void Selection::deselectAll(Machine* m)
{
  GState* tmp;
  GTransition* t;
  GITransition* itr;

  if (!m)
    return ;

  QListIterator<GState*> i(m->getSList());

  for(; i.hasNext();)
  {
    tmp = i.next();
    tmp->select(FALSE);

    QListIterator<GTransition*> it(tmp->tlist);

    for(; it.hasNext();)
    {
      t = it.next();
      t->select(FALSE);
    }
  }

  tmp = m->getPhantomState();
  QListIterator<GTransition*> it(tmp->tlist);

  for(; it.hasNext();)
  {
    t = it.next();
    t->select(FALSE);
  }


  ssel_list.clear();
  tsel_list.clear();

  itr = m->getInitialTransition();
  if (itr)
  {
    itr->select(FALSE);
  }
  itrans=FALSE;
}


/// Returns TRUE if state @a sels is selected, otherwise FALSE
bool Selection::isStateSelected(State* sels)
{
  QListIterator<GState*> i(ssel_list);
  State* s;

  if (!sels)
    return FALSE;

  for(; i.hasNext();)
  {
    s = i.next();
    if (s==sels)
      return TRUE;
  }
  return FALSE;
}

/// Returns TRUE if transition @a selt is selected, otherwise FALSE
bool Selection::isTransitionSelected(Transition* selt)
{
  QListIterator<GTransition*> i(tsel_list);
  Transition* t;

  if (!selt)
    return FALSE;

  for(; i.hasNext();)
  {
    t = i.next();
    if (t==selt)
      return TRUE;
  }
  return FALSE;
}


