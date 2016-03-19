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

removed setAutoDelete calls from constructor
*/

#ifndef QXMLHANDLER_H
#define QXMLHANDLER_H


#include <qobject.h>
#include <qxml.h>
#include <qmap.h>
//Added by qt3to4:
#include <Q3ValueList>

#include "GState.h"
#include "GTransition.h"

class Project;
class Machine;
class GState;
class GTransition;
class GITransition;
class Selection;

/**
 * @class XMLHandler
 * @brief XML parser that parses .fsm files
 */
class XMLHandler : public QObject, public QXmlDefaultHandler
{
  Q_OBJECT
  public:
    XMLHandler(Project* newProject, Selection* sel=NULL,bool keepquiet=TRUE, bool createnewmachine=TRUE);
    bool startDocument();
    bool startElement ( const QString & namespaceURI, const QString & localName, const
	QString & qName, const QXmlAttributes & atts );
    bool endElement( const QString&, const QString&, const QString& );
    bool characters ( const QString & ch );

    ~XMLHandler()
    {
  //    if(transition!=NULL)
  //      delete transition;
    }
    
  private:
    /// Pointer to the project
    Project* project;
    /// Pointer to the machine
    Machine* machine;
    /// If TRUE, no error messages are print (or dialog boxes opened) during parsing 
    bool quiet;
    /// If TRUE a new machine is created, otherwise an existing one is used
    bool create_new_machine;
    /// Pointer to the selection object
    Selection* selection;

    /// Version of Qfsm that created the document
    double version;
    /// Current state
    GState* state;
    /// Current transition
    GTransition* transition;
    /// Current initial transition
    GITransition* itransition;
    /// Code of the initial state (that has to be saved during parsing)
    int saveinitialstate;
    /// Input names
    QString inames;
    /// Output names
    QString onames;
    /// Moore output names
    QString monames;
    /// State name
    QString sname;
    /// deprecated
    bool inamescont;
    /// deprecated
    bool onamescont;
    /// deprecated
    bool monamescont;
    /// deprecated
    bool snamecont;
    /// TRUE is the current state has a code 
    bool hascode;
    /// Transition tyoe
    int ttype;
    /// Input info
    QString iinfo;
    /// Output info
    QString oinfo;
    /// Invert input info
    bool invert;
    /// any input info
    bool any;
    /// default transition 
    bool def;
    /// deprecated
    bool fromcont;
    /// deprecated
    bool tocont;
    /// deprecated
    bool tincont;
    /// deprecated
    bool toutcont;
    /// TRUE if the transition has a starting state
    bool hasfrom;
    /// TRUE if the transition has an end state
    bool hasto;
    /// Starting state
    QString from;
    /// End state
    QString to;
    /// List of removed states
    Q3ValueList<int> rstatelist;
    /// Mapping of old state codes to new state codes
    QMap<int, int> codemap;
    /// If TRUE the current state will be added to the machine
    bool addstate;
    /// TRUE if there is ann initial state
    bool hasinitialstate;
    /// List of added states (used for undo)
    QList<GState*> undostatelist;
    /// List of added transitions (used for undo)
    QList<GTransition*> undotranslist;
    /// Old initial state (used for undo)
    GState *oldinitialstate;
    /// New initial state (used for undo)
    GState *newinitialstate;
    /// Old initial transition (used for undo)
    GITransition *oldinitialtrans;
    /// New initial transition (used for undo)
    GITransition *newinitialtrans;
    // Number of moore output bits
    int nummooreout;
    // Number of mealy input bits
    int numin;
    // Number of mealy output bits
    int numout;
    /// Number of bits for state encoding
    int state_code_size;
    /// Old number of moore output bits (used for undo)
    int oldnummooreout;
    /// Old number of input bits (used for undo)
    int oldnumin;
    /// Old number of output bits (used for undo)
    int oldnumout;
};

#endif

