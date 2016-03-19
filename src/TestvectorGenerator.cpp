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


#include <QProgressDialog>
#include "TestvectorGenerator.h"
#include "Machine.h"
#include "TransitionInfo.h"
#include "IOInfoList.h"

/// Standard Constructor
TestvectorGenerator::TestvectorGenerator()
{

  machine=NULL;

  synchronous_reset=false;
  testvector_length=0;
  synchronous_enable=false;
  negated_reset=false;
}

/// Destructor
TestvectorGenerator::~TestvectorGenerator()
{

  while (!control_signal_vector.isEmpty())
  {
    if(control_signal_vector.first()!=NULL)
      delete control_signal_vector.takeFirst();
  }

}


/**
 * Initializes the generator object.
 * @a m is a pointer to machine used for testvector generation.
 * @a sr is the synchronous reset flag to enable the synchronous reset
 * @a se is the synchronous enable flag
 * @a neg is the negated reset flag
 */
void TestvectorGenerator::init(Machine *m,bool sr, bool se, bool neg)
{
  machine=m;
  synchronous_reset=sr;
  synchronous_enable=se;
  negated_reset=neg;
}

/**
 * Runs the testvector generator algorithm
 */
void TestvectorGenerator::generateTestvector()
{
  GState*s1,*s2;
  GTransition*t;
  QList<GState*>start_path;
  QList<GState*>return_path;
  IOInfoList inputs;
  bool ctl_in_finished=false;

  QString message;
  QString controlInput;
  int num_transitions=0;
  QProgressDialog progress("Checking machine...", "Cancel", 0, 5);
  progress.setWindowModality(Qt::WindowModal);
  progress.setMinimumDuration(1000);


  QMutableListIterator <GState*> is(machine->getSList());

  while(is.hasNext())
  {
    s1=is.next();
    num_transitions+=s1->tlist.size();
  }

  if(synchronous_reset || synchronous_enable)
    progress.setRange(0,num_transitions+machine->getNumStates());
  else progress.setRange(0,num_transitions);



  machine->resetMarks();
  input_vector.clear();
  mealy_output_vector.clear();
  moore_output_vector.clear();
//  control_signal_vector.clear();

  while (!control_signal_vector.isEmpty())
  {
    if(control_signal_vector.first()!=NULL)
      delete control_signal_vector.takeFirst();
  }


  s1=machine->getInitialState();

  if(!(synchronous_reset || synchronous_enable))
    ctl_in_finished=true;

  while(true)
  {
    start_path.clear();
    start_path.append(s1);

    if((synchronous_reset  || synchronous_enable) && !ctl_in_finished)
    {
      return_path=getResetPathRec(start_path);

      if(return_path.isEmpty())
      {
        ctl_in_finished=true;
        machine->resetMarks();
        continue;
      }
    }

    else
    {
      return_path=getPathRec(start_path);
      if(return_path.isEmpty())
        break;
    }


      QMutableListIterator<GState*> is(return_path);
      s1=is.next();
      s2=s1;
      while(is.hasNext())
      {
        s2=s1;
        s1=is.next();
        moore_output_vector.append(s1->getMooreOutputs());
        QMutableListIterator<GTransition*> it(s2->tlist);
        while(it.hasNext())
        {
          t=it.next();
          if(t->getEnd()==s1)
          {

            message="Transition: "+s2->getStateName()+" -> "+t->getInfo()->getInputsStr(machine)+" -> "+s1->getStateName();
            message+="Mark: "+QString::number(t->getMark());
            qDebug(message.latin1());

            if(t->checkMark())
            {
              t->getInfo()->getInputInfo()->split(inputs,s2);
              input_vector.append(inputs[0]);
            }
            else {
              t->getInfo()->getInputInfo()->split(inputs,s2);
              input_vector.append(inputs[t->getMark()]);
              t->setMark(t->getMark()+1);
              if(t->checkMark() && ctl_in_finished)
                progress.setValue(progress.value()+1);
            }


            controlInput="";

            if(synchronous_reset)
            {
              if(negated_reset)
                controlInput.append("1");
              else controlInput.append("0");
            }
            if(synchronous_enable)
              controlInput.append("1");

            control_signal_vector.append(new IOInfoBin(IO_MealyIn,controlInput,false));
            mealy_output_vector.append(t->getInfo()->getOutputInfo());
            break;
          }
        }
      }
      QMutableListIterator<GTransition*>it(s1->tlist);

      while(it.hasNext())
      {
        t=it.next();
        if(!t->checkMark())
        {
          s2=(GState*)t->getEnd();
          if(s2==NULL)
            continue;
          message="Transition: "+s1->getStateName()+" -> "+t->getInfo()->getInputsStr(machine)+" -> "+s2->getStateName();
          t->getInfo()->getInputInfo()->split(inputs,s1);
          input_vector.append(inputs[t->getMark()]);

          controlInput="";

          if(synchronous_reset)
          {
            if(negated_reset)
              controlInput.append("1");
            else controlInput.append("0");
          }
          if(synchronous_enable)
            controlInput.append("1");
          control_signal_vector.append(new IOInfoBin(IO_MealyIn,controlInput,false));


          mealy_output_vector.append(t->getInfo()->getOutputInfo());
          qDebug(message.latin1());
          t->setMark(t->getMark()+1);
          if(t->checkMark() && ctl_in_finished)
            progress.setValue(progress.value()+1);
          break;
        }
      }

      if(s2==NULL)
      {
        return;
      }

      moore_output_vector.append(s2->getMooreOutputs());
      s1=s2;

      if(!ctl_in_finished)
      {
        if(synchronous_enable)
        {
          for(int c=0; c<(1<<(machine->getNumInputs())); c++)
          {
            controlInput="";
            if(synchronous_reset)
            {
              if(negated_reset)
                controlInput.append("1");
              else controlInput.append("0");
            }
            if(synchronous_enable)
              controlInput.append("0");
            input_vector.append(new IOInfoBin(IO_MealyIn,c,machine->getNumInputs(),false));
            moore_output_vector.append(s2->getMooreOutputs());
            mealy_output_vector.append(t->getInfo()->getOutputInfo());
            control_signal_vector.append(new IOInfoBin(IO_MealyIn,controlInput,false));
          }
        }

        if(synchronous_reset)
        {
          if(negated_reset)
            controlInput="0";
          else controlInput="1";
          if(synchronous_enable)
            controlInput.append("1");
          s1=machine->getInitialState();
          input_vector.append(new IOInfoBin(IO_MealyIn,0,machine->getNumInputs(),false));
          moore_output_vector.append(s1->getMooreOutputs());
          mealy_output_vector.append(t->getInfo()->getOutputInfo());
          control_signal_vector.append(new IOInfoBin(IO_MealyIn,controlInput,false));
        }

        if(!s2->getMark())
        {
          progress.setValue(progress.value()+1);
          qDebug(QString::number(progress.value()));
        }

        s2->setMark(true);

      }
/*      else {
        controlInput="";
        if(synchronous_reset)
          controlInput.append("1");
        if(synchronous_enable)
          controlInput.append("1");
        control_signal_vector.append(new IOInfoBin(IO_MealyIn,controlInput,false));

      }*/

  }
  machine->resetMarks();
  message="Size Moore Outputs: "+QString::number(moore_output_vector.size());
  message+=" Size Mealy Outputs: "+QString::number(mealy_output_vector.size());
  message+=" Size Inputs: "+QString::number(input_vector.size());
  message+=" Size Control Inputs: "+QString::number(control_signal_vector.size());
  qDebug(message.latin1());


}

/**
 * This method searches the shortest path to a
 * state which is not marked recursiveley
 * @a path is a list that contains the the path from
 * the start state to the current state
 * Returns the complete path to a state with an unmarked
 * transition
 */
QList<GState*> TestvectorGenerator::getPathRec(QList<GState*> path)
{
  GState*s;
  GTransition*t;
  QList<GState*>return_list1;
  QList<GState*>return_list2;
  QList<GState*>tmp;
  bool found;


  QMutableListIterator<GState*> is(path);
  is.toBack();
  s=is.previous();
  QMutableListIterator<GTransition*> it(s->tlist);

  //check transitions
  if(!s->getMark())
  {
    while(it.hasNext())
    {
      t = it.next();
      if(!t->checkMark())
      {
        return path;
      }
    }
    qDebug(QString("State marked: ")+s->getStateName());
    s->setMark(TRUE);
  }

  //recursion
  it.toFront();
  while(it.hasNext())
  {
    found=false;
    t = it.next();
    is.toFront();
    while(is.hasNext())
    {
      s=(GState*)is.next();
      if(s==t->getEnd())
      {
        found=true;
        break;
      }
    }
    if(!found)
    {
      tmp.clear();
      if(t->getEnd()!=NULL)
      {
        tmp.append((GState*)t->getEnd());
        return_list1=getPathRec(path+tmp);
        if((return_list1.size()<return_list2.size() && !return_list1.isEmpty()) ||
          return_list2.isEmpty())
        {
          return_list2=return_list1;
        }
     }
    }
  }
  return return_list2;
}
/**
 * This method searches the shortest path to a
 * state which is not marked recursiveley
 * @a path is a list that contains the the path from
 * the start state to the current state
 * Returns the complete path to a state with an unmarked
 * transition
 */
QList<GState*> TestvectorGenerator::getResetPathRec(QList<GState*> path)
{
  GState*s;
  GTransition*t;
  QList<GState*>return_list1;
  QList<GState*>return_list2;
  QList<GState*>tmp;
  bool found;


  QMutableListIterator<GState*> is(path);
  is.toBack();
  s=is.previous();
  QMutableListIterator<GTransition*> it(s->tlist);

  //check transitions
  if(!s->getMark())
  {
    return path;
  }

  //recursion
  it.toFront();
  while(it.hasNext())
  {
    found=false;
    t = it.next();
    is.toFront();
    while(is.hasNext())
    {
      s=(GState*)is.next();
      if(s==t->getEnd())
      {
        found=true;
        break;
      }
    }
    if(!found)
    {
      tmp.clear();
      tmp.append((GState*)t->getEnd());
      return_list1=getPathRec(path+tmp);
      if((return_list1.size()<return_list2.size() && !return_list1.isEmpty()) ||
         return_list2.isEmpty())
      {
        return_list2=return_list1;
      }
    }
  }
  return return_list2;
}


