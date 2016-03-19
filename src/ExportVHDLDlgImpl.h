/*
Copyright (C) Stefan Duffner 

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

#ifndef EXPORTVHDLDLGIMPL_H
#define EXPORTVHDLDLGIMPL_H
#include "ui_ExportVHDLDlg.h"

class Options;
class Machine;

class ExportVHDLDlgImpl : public QDialog
{
    Q_OBJECT
    Ui::ExportVHDLDlg exportVHDLDlg;

public:
    ExportVHDLDlgImpl( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, Qt::WFlags fl = 0 );
    ~ExportVHDLDlgImpl();

    /// Returns the 'symbolic states' flag 
    bool getSymbolicStates() { return symbolic_states; }
    /// Sets the 'symbolic states' flag 
    void setSymbolicStates(bool ss) { symbolic_states = ss; }
    /// Returns the 'input/output names' flag 
    bool getInOutNames() { return inout_names; }
    /// Sets the 'input/output names' flag 
    void setInOutNames(bool ion) { inout_names = ion; }
    /// Returns the 'synchronous reset' flag 
    bool getSyncReset() { return sync_reset; }
    /// Sets the 'synchronous reset' flag
    void setSyncReset(bool sr) { sync_reset = sr; }
    /// Returns the 'synchronous enable' flag
    bool getSyncEnable() { return sync_enable; }
    /// Sets the 'synchronous enable' flag
    void setSyncEnable(bool se) { sync_enable = se; }
    /// Returns the 'negated reset' flag
    bool getNegReset() { return neg_reset; }
    /// Sets the 'synchronous reset' flag
    void setNegReset(bool nr) { neg_reset = nr; }
    /// Returns the 'std_logic package' flag
    bool getStdLogic() { return stdlogic; }
    /// Sets the 'std_logic package' flag
    void setStdLogic(bool sl) { stdlogic = sl; }
    /// Returns the 'IO header' flag
    bool getIOheader() { return io_header; }
    /// Sets the 'IO header' flag
    void setIOheader(bool ioh) { io_header = ioh; }
    /// Returns the 'alliance' flag
    bool getAlliance() { return alliance; }
    /// Sets the 'alliance' flag
    void setAlliance(bool al) { alliance = al; }
    /// Returns the condition notation
    int getCondNotation() { return cond_notation; }
    /// Sets the condition notation
    void setCondNotation(int cn) { cond_notation = cn; }
    /// Returns the state code export flag
    bool getStateCode() { return state_code; }
    /// Sets the state code export flag
    void setStateCode(bool sc) { state_code = sc; }
    /// Set the architecture name
    void setArchitectureName(QString n) {architecture_name=n;}
    /// Get the architecture name
    QString getArchitectureName() {return architecture_name;}
    void setSepFiles(bool sep);
    /// Get the flag for exporting the state machine in two files
    bool getSepFiles() {return sep_files;}
    /// Set the flag to export state machine with synchronous look-ahead buffer
    void setLookAhead(bool a) {sync_look_ahead=a;}
    /// Get the flag to export state machine with synchronous look-ahead buffer
    bool getLookAhead() {return sync_look_ahead;}
    /// Set the export path for the entity file
    void setEntityPath(QString n) {path_entity=n;}
    /// Get the export path for the entity file
    QString getEntityPath() {return path_entity;}
    /// Set the export path for the entity file
    void setArchitecturePath(QString n) {path_architecture=n;}
    /// Get the export path for the entity file
    QString getArchitecturePath() {return path_architecture;}
    /// Returns the debug state export flag
    bool getDebugState() { return debug_state; }
    /// Sets the state code export flag
    void setDebugState(bool sd) { debug_state = sd; }

    void init(Options* opt, Machine* m);

public slots:
    void symbolicNamesClicked();
    void inOutNamesClicked();
    void synchronousResetClicked();
    void synchronousEnableClicked();
    void negResetClicked();
    void useStdLogicClicked();
    void ioHeaderClicked();
    void allianceClicked();
    void stateCodeClicked();
    void condNotationClicked(int);
    void sepFilesClicked();
    void lookAheadClicked();
    void selectArchitectureFileClicked();
    void selectEntityFileClicked();
    void architectureNameChanged(QString);
    void entityPathChanged(QString);
    void archtitecturePathChanged(QString);
    void debugStateClicked();

private:
    /// If TRUE use symbolic names for states
    bool symbolic_states;
    /// if TRUE use input/output names
    bool inout_names;
    /// If TRUE use synchronous reset, otherwise asynchronous reset
    bool sync_reset;
    /// If TRUE add synchronous enable port
    bool sync_enable;
    /// If TRUE use negated reset
    bool neg_reset;
    /// if TRUE use std_logic_1164 package
    bool stdlogic;
    /// if TRUE write input/output description into header
    bool io_header;
    /// if TRUE write Alliance compliant code
    bool alliance;
    /// 0: IF-THEN condition notation  1: CASE-WHEN notation
    int cond_notation;
    /// if TRUE state codes were exported
    bool state_code;
    /// architecture name
    QString architecture_name;
    /// if TRUE, export architecture and entity in separate files
    bool sep_files;
    /// export state machine with synchronous look-ahead-buffer
    bool sync_look_ahead;
    /// Path to save the entity file or path for the whole VHDL file when only one file is exported
    QString path_entity;
    /// Path to save the architecture file
    QString path_architecture;
    /// Name of the current machine (used to generate default file names)
    QString machine_name;
    ///if TRUE debug state is exported
    bool debug_state;

};

#endif // EXPORTVHDLDLGIMPL_H
