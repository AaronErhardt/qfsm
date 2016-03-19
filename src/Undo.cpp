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

#include "Undo.h"
#include "Project.h"
#include "Machine.h"

/// Constructor
Undo::Undo(Project* p)
{
  project = p;
//  copylist.setAutoDelete(FALSE);
//  slist.setAutoDelete(FALSE);
//  slist2.setAutoDelete(FALSE);
//  tlist.setAutoDelete(FALSE);
//  tlist2.setAutoDelete(FALSE);
//  doubletlist.setAutoDelete(TRUE);
  action=AddState;
  modified=false;
  state=NULL;
  state2=NULL;
  istate=NULL;
  transition=NULL;
  transition2=NULL;
  itrans=NULL;
  itrans2=NULL;
  movedbyx=0;
  movedbyy=0;
  machine=NULL;
  type=0;
  numin=0;
  numout=0;
  nummooreout=0;
  arrowtype=0;
  ditrans=true;
}

/// Destructor
Undo::~Undo()
{
}


/// Returns the properties of the machine
void Undo::getMachineInfo(Machine*& m, QString& n, int& t, int& nb, QStringList& olistm, 
    int& ni, QStringList& ilist, int& no, QStringList& olist, QFont& sf, QFont& tf, int& at, bool& dit) 
{ 
  m = machine; 
  n = mname; 
  t = type;
  ni = numin; 
  ilist = strlist1; 
  no = numout; 
  olist = strlist2; 
  nb = nummooreout; 
  olistm = strlist3; 
  sf = sfont; 
  tf = tfont; 
  at = arrowtype; 
  dit = ditrans;
}


/// Sets the properties of a machine
void Undo::setMachineInfo(Machine* m, QString n, int t, int nb, QStringList olistm, int ni, 
	QStringList ilist, int no, QStringList olist, QFont sf, QFont tf, int at, bool dit)
{ 
  machine = m; 
  mname = n; 
  type = t;
  numin=ni; 
  strlist1=ilist, 
  numout=no; 
  strlist2=olist, 
  nummooreout=nb; 
  strlist3 = olistm;
  sfont = sf; 
  tfont = tf; 
  arrowtype=at; 
  ditrans=dit;
}

