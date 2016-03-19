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

#ifndef OPTIONS_H
#define OPTIONS_H

#include <qcolor.h>
#include <qobject.h>

class MainWindow;


/**
 * @class Options
 * @brief Stores the application options.
 */
class Options : public QObject
{
  Q_OBJECT
  public:
    Options(QObject* parent=NULL, const char* name=0);
    
    /// Returns TRUE if states encoding should be displayed otherwise FALSE
    bool getViewStateEncoding() { return viewStateEncoding; }
    /// If @a v is TRUE moore outputs will be displayed otherwise not
    void setViewStateEncoding(bool s) { viewStateEncoding = s; }
    /// Returns TRUE if moore outputs should be displayed otherwise FALSE
    bool getViewMoore() { return viewMoore; }
    /// If @a v is TRUE moore outputs will be displayed otherwise not
    void setViewMoore(bool v) { viewMoore = v; }
    /// Returns TRUE if mealy inputs should be displayed otherwise FALSE
    bool getViewMealyIn() { return viewMealyIn; }
    /// If @a v is TRUE mealy inputs will be displayed otherwise not
    void setViewMealyIn(bool v) { viewMealyIn = v; }
    /// Returns TRUE if mealy outputs should be displayed otherwise FALSE
    bool getViewMealyOut() { return viewMealyOut; }
    /// If @a v is TRUE mealy outputs will be displayed otherwise not
    void setViewMealyOut(bool v) { viewMealyOut = v; }

    /// Returns TRUE if the IO view dialog is displayed otherwise FALSE
    bool getViewIOView() { return viewIOView; }
    /// If @a v is TRUE the IO view dialog will be displayed otherwise not
    void setViewIOView(bool v) { viewIOView = v; }

    /// Returns TRUE if the grid is displayed otherwise FALSE
    bool getViewGrid() { return viewGrid; }
    /// If @a v is TRUE the grid will be displayed otherwise not
    void setViewGrid(bool v) { viewGrid = v; }
    /// Gets the color of the grid
    QColor getGridColor() { return gridColor; }
    /// Sets the color of the grid
    void setGridColor(QColor c) { gridColor = c; }
    /// Gets the grid size
    int getGridSize() { return gridSize; }
    /// Sets the grid size 
    void setGridSize(int s) { gridSize = s; }
    /// Returns TRUE if states are locked to the grid
    bool getLockStates() { return lockstates; }
    /// If @a ls is TRUE states are locked to the grid
    void setLockStates(bool ls) { lockstates = ls; }
    /// Returns TRUE if transitions are locked to the grid
    bool getLockTransitions() { return locktransitions; }
    /// If @a lt is TRUE transitions are locked to the grid
    void setLockTransitions(bool lt) { locktransitions = lt; }

    /// Returns TRUE if state shadows should be displayed
    bool getStateShadows() { return stateShadows; }
    /// If @a sh is TRUE states are displayed with shadows
    void setStateShadows(bool sh) { stateShadows = sh; }
    /// Returns the color of the state shadows
    QColor getStateShadowColor() { return stateShadowColor; }
    /// Sets the state shadow color to @a col
    void setStateShadowColor(QColor col) { stateShadowColor = col; }

    /// Returns the 'show tooltips' flag
    bool getToolTips() { return tooltips; }
    /// Sets the 'show tooltips' flag
    void setToolTips(bool t) { tooltips = t; }
    /// Returns TRUE if ?/! shall be shown, otherwise FALSE
    bool getIOMark() { return iomark; }
    /// Sets/clears the 'show ?/!' flag
    void setIOMark(bool m) { iomark = m; }
    /// Returns TRUE if I/O names (e.g. in1=...) shall be shown over the transitions
    bool getDisplayIONames() { return ionames; }
    /// Sets/clears the 'Display I/O names' flag
    void setDisplayIONames(bool dio) { ionames = dio; }
    /// Returns TRUE if a box shall be drawn around the I/O over transitions
    bool getDrawBox() { return bdrawbox; }
    /// Sets/clears the 'Draw Box' flag
    void setDrawBox(bool db) { bdrawbox = db; }
    /// Returns the initial transition descriptor
    QString getInitialDescriptor() { return initial_descriptor; }
    /// Sets the initial transition descriptor to @a sd
    void setInitialDescriptor(QString sd) { initial_descriptor = sd; }
    /// Returns the inversion descriptor
    QString getInversionDescriptor() { return inversion_descriptor; }
    /// Sets the inversion descriptor to @a id
    void setInversionDescriptor(QString id) { inversion_descriptor = id; }
    /// Returns the "any input" descriptor
    QString getAnyInputDescriptor() { return any_input_descriptor; }
    /// Sets the "any input" descriptor to @a ad
    void setAnyInputDescriptor(QString ad) { any_input_descriptor = ad; }
    /// Returns the default transition descriptor
    QString getDefaultTransitionDescriptor() { return default_descriptor; }
    /// Sets the default transition descriptor to @a dd
    void setDefaultTransitionDescriptor(QString dd) { default_descriptor = dd; }

    /// Returns the 'synchronous reset' flag (AHDL export)
    bool getAHDLSyncReset() { return ahdl_sync_reset; }
    /// Sets the 'synchronous reset' flag (AHDL export)
    void setAHDLSyncReset(bool sr) { ahdl_sync_reset = sr; }
    /// Returns the 'use moore outputs' flag (AHDL export)
    bool getAHDLUseMoore() { return ahdl_use_moore; }
    /// Sets the 'use moore outputs' flag (AHDL export)
    void setAHDLUseMoore(bool um) { ahdl_use_moore = um; }

    /// Returns the 'symbolic states' flag (VHDL export)
    bool getVHDLSymbolicStates() { return vhdl_symbolic_states; }
    /// Sets the 'symbolic states' flag (VHDL export)
    void setVHDLSymbolicStates(bool ss) { vhdl_symbolic_states = ss; }
    /// Returns the 'synchronous reset' flag (VHDL export)
    bool getVHDLSyncReset() { return vhdl_sync_reset; }
    /// Sets the 'synchronous reset' flag (VHDL export)
    void setVHDLSyncReset(bool sr) { vhdl_sync_reset = sr; }
    /// Returns the 'synchronous enable' flag (VHDL export)
    bool getVHDLSyncEnable() { return vhdl_sync_enable; }
    /// Sets the 'synchronous enable' flag (VHDL export)
    void setVHDLSyncEnable(bool se) { vhdl_sync_enable = se; }
    /// Returns the 'negated reset' flag (VHDL export)
    bool getVHDLNegReset() { return vhdl_neg_reset; }
    /// Sets the 'negated reset' flag (VHDL export)
    void setVHDLNegReset(bool nr) { vhdl_neg_reset = nr; }
    /// Returns the 'input/output names' flag (VHDL export)
    bool getVHDLInOutNames() { return vhdl_inout_names; }
    /// Sets the 'inpu/output names' flag (VHDL export)
    void setVHDLInOutNames(bool ion) { vhdl_inout_names=ion; }
    /// Returns the 'std_logic package' flag (VHDL export)
    bool getVHDLStdLogic() { return vhdl_stdlogic; }
    /// Sets the 'std_logic package' flag (VHDL export)
    void setVHDLStdLogic(bool sl) { vhdl_stdlogic = sl; }
    /// Returns the 'io header' flag (VHDL export)
    bool getVHDLIOheader() { return vhdl_io_header; }
    /// Sets the 'io header' flag (VHDL export)
    void setVHDLIOheader(bool ioh) { vhdl_io_header = ioh; }
    /// Returns the 'alliance' flag (VHDL export)
    bool getVHDLAlliance() { return vhdl_alliance; }
    /// Sets the 'alliance' flag (VHDL export)
    void setVHDLAlliance(bool al) { vhdl_alliance = al; }
    /// Returns the condition notation (0: if-then   1: case-when)
    int getVHDLCondNotation() { return vhdl_cond_notation; }
    /// Sets the condition notation (0: if-then   1: case-when)
    void setVHDLCondNotation(int cn) { vhdl_cond_notation = cn; }
    /// Returns true when state codes were exported
    bool getVHDLStateCode() { return vhdl_state_code; }
    /// Sets the state code export flag
    void setVHDLStateCode(bool sc) { vhdl_state_code = sc; }
    /// Returns the flag for exporting two VHDL files for architecture and entity
    bool getVHDLSepFiles() { return vhdl_sep_files; }
    /// Sets the flag for exporting two VHDL files
    void setVHDLSepFiles(bool sc) { vhdl_sep_files = sc; }
    /// Returns the flag for the export of a state machine with synchronous look-ahead buffers
    bool getVHDLSyncLookAhead() { return vhdl_sync_look_ahead; }
    /// Sets the flag for the export of a state machine with synchronous look-ahead buffers
    void setVHDLSyncLookAhead(bool sc) { vhdl_sync_look_ahead = sc; }
    /// Returns the VHDL architecture name
    QString getVHDLArchitectureName() { return vhdl_architecture_name; }
    /// Sets the VHDL architecture name
    void setVHDLArchitectureName(QString n) { vhdl_architecture_name = n; }
    /// Returns the VHDL architecture name
    QString getVHDLArchitecturePath() { return vhdl_architecture_path; }
    /// Sets the VHDL architecture name
    void setVHDLArchitecturePath(QString n) { vhdl_architecture_path = n; }
    /// Returns the VHDL architecture name
    QString getVHDLEntityPath() { return vhdl_entity_path; }
    /// Sets the VHDL architecture name
    void setVHDLEntityPath(QString n) { vhdl_entity_path = n; }
    /// Returns true when user wants state debug outputs
    bool getVHDLDebugState() { return vhdl_state_debug; }
    /// sets state_debug flag
    void setVHDLDebugState(bool sd) { vhdl_state_debug = sd; }

    /// Returns the 'synchronous reset' flag (Verilog export)
    bool getVerilogSyncReset() { return ver_sync_reset; }
    /// Sets the 'synchronous reset' flag (Verilog export)
    void setVerilogSyncReset(bool sr) { ver_sync_reset = sr; }


     /// Returns the 'stdlogic' flag (Testbench export)
    bool getTestbenchStdLogic() { return testbench_stdlogic; }
    /// Sets the 'stdlogic' flag (Testbench export)
    void setTestbenchStdLogic(bool sl) { testbench_stdlogic = sl; }
     /// Returns the 'synchronous reset' flag (Testbench export)
    bool getTestbenchSynchronousReset() { return testbench_synchronousreset; }
    /// Sets the 'synchronous reset' flag (Testbench export)
    void setTestbenchSynchronousReset(bool sr) { testbench_synchronousreset = sr; }

    /// Returns the 'synchronous enable' flag (Testbench export)
    bool getTestbenchSynchronousEnable() { return testbench_synchronousenable; }
    /// Sets the 'synchronous enable' flag (Testbench export)
    void setTestbenchSynchronousEnable(bool se) { testbench_synchronousenable = se; }

    /// Returns the 'negated reset' flag (Testbench export)
    bool getTestbenchNegatedReset() { return testbench_negatedreset; }
    /// Sets the 'negated reset' flag (Testbench export)
    void setTestbenchNegatedReset(bool nr) { testbench_negatedreset = nr; }

    /// Returns the 'io names' flag (Testbench export)
    bool getTestbenchIONames() { return testbench_ionames; }
    /// Sets the 'io names' flag (Testbench export)
    void setTestbenchIONames(bool io) { testbench_ionames = io; }


    /// Returns the 'io header' flag (Testbench export)
    bool getTestbenchIOHeader() { return testbench_io_header; }
    /// Sets the 'io header' flag (Testbench export)
    void setTestbenchIOHeader(bool io) { testbench_io_header = io; }
    /// Returns the testbench algorithm (0: Algorithm 1    1: Algorithm 1)
    int getTestbenchAlgorithm() { return testbench_algorithm; }
    /// Sets the testbench algorithm
    void setTestbenchAlgorithm(int a) { testbench_algorithm = a; }
    /// Returns the path of the VHDL testbench file relative to the testbench base directory
    QString getTestbenchVHDLPath() { return testbench_vhdl_path; }
    /// Sets the path of the VHDL testbench file relative to the testbench base directory
    void setTestbenchVHDLPath(QString vp) { testbench_vhdl_path = vp; }
    /// Returns the path of the ASCII testvector file relative to the testbench base directory
    QString getTestpackageVHDLPath() { return testpackage_vhdl_path; }
    /// Sets the path of the ASCII testvector file relative to the testbench base directory
    void setTestpackageVHDLPath(QString ap) { testpackage_vhdl_path = ap; }
    /// Returns the path of the ASCII testvector file relative to the testbench base directory
    QString getTestvectorASCIIPath() { return testvector_ascii_path; }
    /// Sets the path of the ASCII testvector file relative to the testbench base directory
    void setTestvectorASCIIPath(QString ap) { testvector_ascii_path = ap; }
    /// Returns the path of the logfile relative to the testbench base directory
    QString getTestbenchLogfilePath() { return testbench_logfile_path; }
    /// Sets the path of the logfile relative to the testbench base directory
    void setTestbenchLogfilePath(QString lf) { testbench_logfile_path = lf; }
    /// Returns the testbench base directory
    QString getTestbenchBaseDirectory() { return testbench_base_directory; }
    /// Sets the testbench base directory
    void setTestbenchBaseDirectory(QString bd) { testbench_base_directory = bd; }


    /// Returns the 'include asynchronous outputs' option (State table export)
    bool getStateTableIncludeOut() { return statetable_includeout; }
    /// Sets the 'include asynchronous outputs' option (State table export)
    void setStateTableIncludeOut(bool io) { statetable_includeout = io; }
    /// Returns the 'resolve inverted conditions' option (State table export)
    bool getStateTableResolveInverted() { return statetable_resolve_inverted; }
    /// Sets the 'resolve inverted conditions outputs' option (State table export)
    void setStateTableResolveInverted(bool ri) { statetable_resolve_inverted = ri; }
    /// Returns the orientation of the state table
    int getStateTableOrientation() { return statetable_orientation; }
    /// Sets the orientation of the state table
    void setStateTableOrientation(int orient) { statetable_orientation = orient; }

    /// Returns the 'create action file' flag (Ragel export)
    bool getRagelCreateAction() { return ragel_create_action; }
    /// Sets the 'create action file' flag (Ragel export)
    void setRagelCreateAction(bool ca) { ragel_create_action = ca; }
    /// Returns the language of the ragel file to export
    int getRagelLangAction() { return ragel_lang_action; }
    /// Sets the language of the ragel file to export
    void setRagelLangAction(int la) { ragel_lang_action = la; }
    /// Returns the 'create default transitions' flag (Ragel export)
    bool getRagelDefaultTransitions() { return ragel_default_transitions; }
    /// Sets the 'create default transitions' flag (Ragel export)
    void setRagelDefaultTransitions(bool rd) { ragel_default_transitions = rd; }

    /// Returns the 'vvvv reset' option
    bool getVVVVReset() { return vvvv_reset; }
    /// Sets the 'vvvv reset' option
    void setVVVVReset(bool vr) { vvvv_reset = vr; }
    /// Returns the vvvv reset event name
    QString getVVVVResetEvent() { return vvvv_reset_event; }
    /// Sets the vvvv reset event name
    void setVVVVResetEvent(QString re) { vvvv_reset_event = re; }
    /// Returns the vvvv reset action name
    QString getVVVVResetAction() { return vvvv_reset_action; }
    /// Sets the vvvv reset action name
    void setVVVVResetAction(QString ra) { vvvv_reset_action = ra; }


    /// Returns the 'print header' option
    bool getPrintHeader() { return print_header; }
    /// Sets the 'print header' option
    void setPrintHeader(bool ph) { print_header = ph; }


    void applyOptions(MainWindow* ); 
  private:
    /// If TRUE, state encodings are shown
    bool viewStateEncoding;
    /// If TRUE, moore outputs are shown
    bool viewMoore;
    /// If TRUE, mealy inputs are shown
    bool viewMealyIn;
    /// If TRUE, mealy outputs are shown
    bool viewMealyOut;
    /// If TRUE, the grid is shown
    bool viewGrid;
    /// If TRUE; the IO view dialog is shown
    bool viewIOView;
    /// Grid color
    QColor gridColor;
    /// Grid size
    int gridSize;
    /// If TRUE, states are locked to the grid
    bool lockstates;
    /// If TRUE, transitions are locked to the grid
    bool locktransitions;
    /// If TRUE, state are displayed with shadows
    bool stateShadows;
    /// State shadow color
    QColor stateShadowColor;

    /// If TRUE tooltips are shown
    bool tooltips;
    /// If TRUE ?/! are shown
    bool iomark;
    /// If TRUE I/O names are displayed over the transitions
    bool ionames;
    /// If TRUE a box is drawn around the I/O over transitions
    bool bdrawbox;
    /// Initial transition descriptor 
    QString initial_descriptor;
    /// Inversion descriptor (e.g. NOT or !)
    QString inversion_descriptor;
    /// "Any input" descriptor (e.g. "any")
    QString any_input_descriptor;
    /// Default transition descriptor
    QString default_descriptor;

    /// ExportAHDL: If TRUE use synchronous reset, otherwise asynchronous reset
    bool ahdl_sync_reset;
    /// ExportAHDL: If TRUE use moore outputs, otherwise use state codes
    bool ahdl_use_moore;

    /// ExportVHDL: If TRUE use symbolic names for states
    bool vhdl_symbolic_states;
    /// ExportVHDL: If TRUE use synchronous reset, otherwise asynchronous reset
    bool vhdl_sync_reset;
    /// ExportVHDL: If TRUE add synchronous enable port
    bool vhdl_sync_enable;
    /// ExportVHDL: If TRUE use negated reset
    bool vhdl_neg_reset;
    /// ExportVHDL: if TRUE use std_logic_1164 package
    bool vhdl_stdlogic;
    /// ExportVHDL: if TRUE use I/O names instead of vectors a,o,q
    bool vhdl_inout_names;
    /// ExportVHDL: if TRUE write I/O description into header
    bool vhdl_io_header;
    /// ExportVHDL: if TRUE write Alliance compliant code
    bool vhdl_alliance;
    /// ExportVHDL: 0: IF-THEN condition notation  1: CASE-WHEN notation
    int vhdl_cond_notation;
    /// ExportVHDL: if this is true, state codes will be exported
    bool vhdl_state_code;
    /// ExportVHDL: architecture name
    QString vhdl_architecture_name;
    /// ExportVHDL: if TRUE, export architecture and entity in separate files
    bool vhdl_sep_files;
    /// ExportVHDL: export state machine with synchronous look-ahead-buffer
    bool vhdl_sync_look_ahead;
    /// ExportVHDL: architecture path
    QString vhdl_architecture_path;
    /// ExportVHDL: VHDL export path or entity export path if one file is exported
    QString vhdl_entity_path;
    /// EXPORTVHDL: if this is true, the state will be exported for debugging the state. 
    bool vhdl_state_debug;

    /// ExportVerilog: If TRUE use synchronous reset, otherwise asynchronous reset
    bool ver_sync_reset;

    /// ExportTestbench: If TRUE use std_logic_1164 package
    bool testbench_stdlogic;
    /// ExportTestbench: if TRUE use synchronous reset
    bool testbench_synchronousreset;
    /// ExportTestbench: if TRUE write I/O description into header
    bool testbench_io_header;
    /// ExportTestbench: 0: Use algorithm 0 1: Use algorithm 1
    int testbench_algorithm;
    /// ExportTestbench: if TRUE write testbench with input and output names
    bool testbench_ionames;
    /// ExportTestbench: if TRUE export testbench with synchronous enable
    bool testbench_synchronousenable;
    /// ExportTestbench: if TRUE export testbench with negated reset
    bool testbench_negatedreset;
    /// ExportTestbench: Testbench export file path
    QString testbench_vhdl_path;
    /// ExportTestbench: Testvector export file path
    QString testvector_ascii_path;
    /// ExportTestbench: VHDL testbench package file path
    QString testpackage_vhdl_path;
    /// ExportTestbench: logfile path
    QString testbench_logfile_path;
    /// ExportTestbench: VHDL testbench base directory
    QString testbench_base_directory;

    /// Export State table: If TRUE include asynchronous outputs
    bool statetable_includeout;
    /// Export State table: If TRUE resolve inverted conditions
    bool statetable_resolve_inverted;
    /// Export State table: If 0 events are columns and states are rows, otherwise the inverse
    int statetable_orientation;

    /// Export Ragel: If TRUE create action file
    bool ragel_create_action;
    /// Export Ragel: Language of action file:  0: C/C++   1: Java  2: Ruby 
    int ragel_lang_action;
    /// Export Ragel: If TRUE adds a default transition to every state for exporting 
    bool ragel_default_transitions;

    //// Export VVVV: If TRUE outputs an reset transition for each state
    bool vvvv_reset;
    /// Export VVVV: reset event name
    QString vvvv_reset_event;;
    /// Export VVVV: reset action name
    QString vvvv_reset_action;;


    /// If TRUE a header is printed at the top of the page when printing a diagram
    bool print_header;
};


#endif
