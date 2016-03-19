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

removed setAutoDelete calls, beacause this feature does not exist in Qt 4
replaced Qt 3 iterators through Qt 4 iterators

in method removeStates:
replaced removeRef calls by the code that replaces a list item from the new QList
*/

#ifndef MACHINE_H
#define MACHINE_H

#include <math.h>
#include <q3ptrlist.h>
#include <qobject.h>
#include <qstringlist.h>

#include "GState.h"
#include "GITransition.h"
#include "Project.h"

class GTransition;
class ICheck;

/**
 * @enum ObjectType
 * @brief Type of an graphical object
 */
enum ObjectType {NoT, StateT, TransitionT, ITransitionT};


/**
 * @class Machine
 * @brief Stores all information about a machine.
 */
class Machine : public QObject
{
  Q_OBJECT
  public:
    Machine(QObject* parent=NULL, const char* name=0);
    Machine(QObject* name, const QString, QString, QString, QString, int type, int, QString, int, QString, int, 
	QString, QFont, QFont, int);
    ~Machine();

    /// Returns initial state of the machine
    GState* getInitialState() { return initial_state; };
    /// Sets the initial state of the machine to @a s.
    void setInitialState(GState* s) { initial_state = s; };
    /// Returns the initial transition
    GITransition* getInitialTransition() { return initial_transition; };
    /// Sets the initial transition
    void setInitialTransition(GITransition* t) { initial_transition = t; };
    /// Attaches initial transition graphically to the initial state. 
    void attachInitialTransition();

    /** 
     * Returns the phantom state.
     * A phantom state is the state containing all the transitions which have
     * no starting states.
     */
    GState* getPhantomState() { return phantom_state; };
    /// Sets the phantom state
    void setPhantomState(GState* s) { phantom_state = s; };
    /// Returns the state list
    QList<GState*>& getSList() { return state_list; };
    /// Returns the name of the machine
    QString getName() { return name; };
    /// Sets the name of the machine
    void setName(const QString n) { name = n; };
    /// Returns the version of the machine
    QString getVersion() { return version; };
    /// Sets the version of the machine
    void setVersion( QString v) { version = v; };


    /// Returns the author of the machine
    QString getAuthor() { return author; };
    /// Sets the author of the machine
    void setAuthor( QString a) { author = a; };
    /// Returns the description of the machine
    QString getDescription() { return description; };
    /// Sets the description of the machine
    void setDescription( QString d) { description = d; };
    
    
    /// Returns the type of the machine. 0: Binary / 1: ASCII
    int getType() { return type; };
    /// Sets the type of the machine to @a t
    void setType(int t) { type = t; };
    /// Returns the number of bits used to code the state
    int getNumMooreOutputs() { return num_moore_output; };
    /// Sets the number of bits.
    void setNumMooreOutputs(int);
    /// Returns the number of input bits
    int getNumInputs() { return num_input; };
    /// Sets the number of input bits
    void setNumInputs(int );
    /// Returns the number of output bits
    int getNumOutputs() { return num_output; };
    /// Sets the number of output bits
    void setNumOutputs(int );
    /// Returns the effective number of encoding bits
    int getNumEncodingBits();
    /// Returns the font used to draw the state names
    QFont& getSFont() { return state_font; };
    /// Sets the font used to draw the state names
    void setSFont(const QFont& f) { state_font = f; };
    /// Returns the font used to draw the transition conditions
    QFont& getTFont() { return transition_font; };
    /// Sets the font used to draw the transition conditions
    void setTFont(const QFont& f) { transition_font = f; };
    /// Returns the arrow type (0: unfilled, 1: filled)
    int getArrowType() { return arrow_type; };
    /// Sets the arrow type (0: unfilled, 1: filled)
    void setArrowType(int t) { arrow_type=t; };
    /// Returns a pointer to the current project
    void setProject(Project* p) { project = p; };
    /// Returns a pointer to the project
    Project* getProject() { return project; };
    int countStates();
    int getNewCode();
    void correctCodes();
    bool checkStateCodes();
    QStringList translateNames(QString);
    QString retranslateNames(QStringList);
    bool addState(const QString , QString, int code, IOInfo* mooreout, double , double , 
	int , double, QPen, bool endstate, bool withundo=TRUE, QString entry_actions="", QString exit_actions="");
    bool addState(GState* , bool withundo=TRUE);
    GState* getState(QPoint , double );
    GObject* getObject(QPoint p, double scale, int& type);
    void removeState(GState* );
    GState* getState(int );
    GState* getState(QString name);
    QList<GState*> getFinalStates();

    /// Returns current canvas size
    void getCanvasSize(int& w, int& h) { w=canvas_size.width();
    					 h=canvas_size.height(); };
    void setCanvasSize(int, int);
    void calcCanvasSize();
    int getNumStates();

    QString getStateEncodingOutputNames(QString separator=", ");
    void setMooreOutputNames(int, QString );
    QString getMooreOutputNames(QString separator=", ");
    QString getMooreOutputNamesAsync(QString separator=", ");
    void setMealyInputNames(int, QString );
    QString getMealyInputNames(QString separator=", ");
    void setMealyOutputNames(int, QString );
    QString getMealyOutputNames(QString separator=", ");

    /// Returns the list of moore output names
    QStringList getMooreOutputList() { return output_names_moore; };
    /// Sets the list of moore output names
    void setMooreOutputList(QStringList l) { output_names_moore = l; };
    /// Returns the list of input names
    QStringList getInputNameList() { return input_names; };
    /// Sets the list of input names
    void setInputNameList(QStringList l) { input_names = l; };
    /// Returns the list of output names
    QStringList getOutputNameList() { return output_names; };
    /// Sets the list of output names
    void setOutputNameList(QStringList l) { output_names = l; };

    bool getDrawITrans() { return drawITrans; };
    void setDrawITrans(bool di) { drawITrans = di; };

    static void replaceChar(QString& s, QChar c1, QChar c2);

    void checkIntegrity(ICheck* );

    void getEventList(IOInfoList& , Options* opt);
    void updateDefaultTransitions();
    void addDefaultTransitionsToEveryState();

  private:
    /// Pointer to the project this machine belongs to
    Project* project;
    /// Name of the machine
    QString name;
    /// Version of the machine
    QString version;
    /// Author of the machine
    QString author;
    /// Description of the machine
    QString description;
    /// Type: 0: Binary / 1: ASCII / 2: Free Text
    int type;
    /// Number of bits for the Moore outputs
    int num_moore_output;
    /// Number of bits for the input conditions
    int num_input;
    /// Number of bits for the outputs
    int num_output;
    /// Names of the input bits
    QStringList input_names;
    /// Names of the output bits
    QStringList output_names;
    /// Names of the moore outputs (state coding)
    QStringList output_names_moore;
    /// Font for the state name
    QFont state_font;
    /// Font for the transition
    QFont transition_font;
    /// Arrow type: 0: line arrow / 1: solid arrow
    int arrow_type;
    /// List of states
    QList<GState*> state_list;
    /// Pointer to the start state (initial state)
    GState* initial_state;
    /// Phantom state
    GState* phantom_state;
    /// Start transition (initial transition)
    GITransition* initial_transition;
    /// Size of the drawingarea
    QSize canvas_size;
    ///Pointer to the integrity checker
    ICheck*checker;

    bool drawITrans;

  signals:
    /// Emited when the canvas size needs to be set to a new value
    void newCanvasSize(int, int);
    void repaint();

  public slots:
    void updateCanvasSize(int, int, double);
    void updateCanvasSize(int, int);
    void resetMarks();
    void checkFinished(int);
};




#endif
