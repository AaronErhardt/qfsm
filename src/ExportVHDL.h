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
/*
Qt 4 Port by Rainer Strobel

replaced Qt 3 iterators through Qt 4 iterators
in method writeStateProcess:
replaced QList through Q3PtrList for compatibility
*/

#ifndef EXPORTVHDL_H
#define EXPORTVHDL_H

#include <QString>
#include <QStringList>
#include "Options.h"
#include "Machine.h"
#include "Export.h"


/**
 * @class ExportVHDL
 * @brief Class that manages export to VHDL.
 *
 */

class ExportVHDL : public Export
{
  public:
    ExportVHDL(Options* opt);

    void init(std::ofstream* ,std::ofstream* ,Machine*, QString fn=QString::null, ScrollView* sv=NULL);


    void doExport();
    QString fileFilter();
	QString defaultExtension();

  /**
 * Checks if @a s is a valid name for
 * the VHDL code
 */
  static bool checkName(QString s)
      {
  QStringList keywords;
  int c,bracket_pos;

  keywords << "abs" << "access" << "after" << "alias" << "all" << "and" << "architecture";
  keywords << "array" << " assert" << "attribute" << "begin" << "block" << "body" << "buffer";
  keywords << "bus" << "case" << "component" << "configuration" << "constant";
  keywords << "disconnect" << "downto" << "else" << "elsif" << "end" << "entity" << "exit";
  keywords << "file" << "for" << "function" << "generate" << "generic" << "group";
  keywords << "guarded" << "if" << "impure" << "in" << "inertial" << "inout" << "is";
  keywords << "label" << "library" << "linkage" << "literal" << "loop" << "map" << "mod";
  keywords << "nand" << "new" << "next" << "nor" << "not" << "null" << "of" << "on";
  keywords << "open" << "or" << "others" << "out" << "package" << "port" << "postponend";
  keywords << "procedure" << "process" << "pure" << "range" << "record" << "register";
  keywords << "reject" << "rem" << "report" << "return" << "rol" << "ror" << "select";
  keywords << "severity" << "shared" << "signal" << "sla" << "sll" << "sra" << "srl";
  keywords << "subtype" << "then" << "to" << "transport" << "type" << "unaffected";
  keywords << "units" << "until" << "use" << "variable" << "wait" << "when" << "while";
  keywords << "with" << "xnor" << "xor";
  //keywords are not allowed
  //not case sensitive
  //names must begin with an alphabetic character
  //the following characters may be aplphabetic or numerich characters or an underscore
  //two underscores __ are not allowed
  //the last character must not be an underscore

  if(s.length()<=0)
    return false;

  if(!((s[0]>='a' && s[0]<='z') || (s[0]>='A' && s[0]<='Z')))
    return false;

  for(c=1; c<s.length(); c++)
  {
    if(s[c]=='[')
      break;
    if(!((s[c]>='a' && s[c]<='z') || (s[c]>='A' && s[c]<='Z') ||
      (s[c]>='0' && s[c]<='9') ||
      s[c]=='_'))
      return false;
    if(s[c]=='_' && s[c-1]=='_')
      return false;

  }

  if(s[c-1]=='_')
    return false;

  for(c=0; c<keywords.size(); c++)
  {
    bracket_pos=s.find('[');
    if(keywords[c]==s.lower())
      return false;
    if(bracket_pos!=-1 && s.left(bracket_pos).lower()==keywords[c])
      return false;
  }

  return true;
}


/**
 * Checks all names of the machine @a m for a valid VHDL syntax
 * and returns all invalid names in @a invalidNames
 */

  static bool checkMachineNames(Machine*m,Options*o,QStringList*invalidNames)
      {
  bool result=TRUE;
  QStringList names;
  QString mname,sname;
  QStringList::const_iterator i,i2;
  int c;
  GState* s, *s2;
  QMutableListIterator<GState*> is(m->getSList());
  QMutableListIterator<GState*> is2(m->getSList());

  o->getVHDLInOutNames(); //do not check io names

  mname = m->getName();



  if(!checkName(mname))
  {
    (*invalidNames) << mname;
    result=FALSE;
  }

  if(o->getVHDLInOutNames())
  {
    names.clear();
    if(m->getNumInputs()>0)
      names=names+m->getInputNameList();

    if(m->getNumOutputs()>0)
      names=names+m->getOutputNameList();

    if(m->getNumMooreOutputs()>0)
      names=names+m->getMooreOutputList();

    names.append(o->getVHDLArchitectureName());


    if(names.size()>0)
    {
      for(i=names.constBegin(); i!=names.constEnd(); ++i)
      {
        if(!checkName(*i))
        {
          (*invalidNames) << *i;
          result =FALSE;
        }
      }

      for(c=0; c<names.size(); c++)
      {
        if(names.indexOf(names.at(c),c+1)!=-1)
        {
              (*invalidNames) << names.at(c);
              result =FALSE;
        }
      }
    }
  }

  if(o->getVHDLSymbolicStates())
  {
    //check states - states - input - mealy - moore
    while(is.hasNext())
    {
      s=is.next();
      sname=s->getStateName();

      if(!checkName(sname))
      {
        (*invalidNames) << sname;
        result =FALSE;
      }

      is2.toFront();
      while(is2.hasNext())
      {
        s2=is2.next();
        if(sname.compare(s2->getStateName())==0 && s!=s2)
        {
            (*invalidNames) << *i;
            result =FALSE;
        }
      }

      if(m->getNumInputs()>0)
      {
        names=m->getInputNameList();
        for(i=names.constBegin(); i!=names.constEnd(); ++i)
        {
          if(sname.compare(*i)==0)
          {
            (*invalidNames) << *i;
            result =FALSE;
          }
        }
      }
      if(m->getNumOutputs()>0)
      {
        names=m->getOutputNameList();
        for(i=names.constBegin(); i!=names.constEnd(); ++i)
        {
          if(sname.compare(*i)==0)
          {
            (*invalidNames) << *i;
            result =FALSE;
          }
        }
      }
      if(m->getNumMooreOutputs()>0)
      {
        names=m->getMooreOutputList();
        for(i=names.constBegin(); i!=names.constEnd(); ++i)
        {
          if(sname.compare(*i)==0)
          {
            (*invalidNames) << *i;
            result =FALSE;
          }
        }
      }

    }
  }

  return result;
}


  private:
    /// Name of the machine to export
    QString mname;
    /// If TRUE, the fixed encoding for the states is used, otherwise an enum type.
    bool state_encoding;
    /// If TRUE, the names of the inputs/outputs are used, otherwise the vectors a,o,q
    bool io_names;
    /// If TRUE, the reset signal will be handled synchronously, otherwise asynchronously.
    bool synchronous_reset;
    /// If TRUE, add synchronous enable port
    bool synchronous_enable;
    /// If TRUE, the negated reset signal will be used
    bool neg_reset;
    /// If TRUE, 'std_logic' is used instead of 'bit'
    bool use_std_logic;
    /// If TRUE, an I/O description is written in the header
    bool io_header;
    /// If TRUE, produce Alliance compliant code
    bool alliance;
    /// 0: IF-THEN condition notation,  1: CASE-WHEN notation
    int cond_notation;
    /// If TRUE, state codes were exported
    bool state_code;
    /// architecture name
    QString architecture_name;
    /// if TRUE, export architecture and entity in separate files
    bool sep_files;
    /// export state machine with synchronous look-ahead-buffer
    bool sync_look_ahead;
    /// output stream for architecture file
    std::ofstream *outa;
    /// output stream for entity file
    std::ofstream *oute;
    bool debug_state;


    void writeEnvironment(std::ofstream*out);
    void writeEntity(std::ofstream*out);
    void writeArchitecture(std::ofstream*out);
    void writeClockProcess(std::ofstream*out);
    void writeStateProcess(std::ofstream*out);
    void writeOutputBufferProcess(std::ofstream*out);
    void writeOutputProcess(std::ofstream*out);
    void writeDescription(std::ofstream*out);
    void writeHeader(std::ofstream*out,QString,QString);
};

#endif
