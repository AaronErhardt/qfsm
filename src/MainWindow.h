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

added Qt:: to all constants
changed QList.getFirst calls to QList.front

modified method ExportVHDL to switch between 
ExportVHDL and ExportVHDLFHA class

in constructor:
disabled all dialogs for testing
added menu item for Export VHDL FH Augsburg and Export IO description
the menu bar is requested from QMainWindow by calling menuBar()


in method updateMenuBar:
the setItemChecked and setItemEnabled calls for the menus
were now called for the sub-menus directly, instead of menubar,
because this did not work under qt 4

int method editCopy:
replaced cb->setData  by cb->setMimeData call, which is compatible
with Qt 4

in method editPaste:
replaced old code to access clipboard data by code, which uses
the Qt 4 class QMimeData

in method createToolBar:
The toolbar can be requested by addToolBar from QMainWindow.
All buttons must be added to the toolbar by calling addWidget.

*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <qmenubar.h>
#include <qmessagebox.h>
#include <qtoolbutton.h>
#include <qcursor.h>
#include <QKeyEvent>
#include <QPixmap>
#include <QFocusEvent>
#include <QCloseEvent>
#include <QToolBar>
#include <QMenu>

#include "ScrollView.h"
#include "DocStatus.h"
#include "StateManager.h"
#include "MachineManager.h"
#include "TransitionManager.h"
#include "Options.h"
#include "Edit.h"
#include "OptGeneralDlgImpl.h"
#include "OptDisplayDlgImpl.h"
#include "OptPrintingDlgImpl.h"
#include "ExportVHDLDlgImpl.h"
#include "ExportVerilogDlgImpl.h"
#include "ExportAHDLDlgImpl.h"
#include "ExportStateTableDlgImpl.h"
#include "ExportRagelDlgImpl.h"
#include "IOViewDlgImpl.h"
#include "ExportTestbenchDlgImpl.h"
#include "ExportTestbenchVHDL.h"
#include "ExportTestvectorASCII.h"
#include "ExportVVVVDlgImpl.h"
#include "TabDialog.h"


//class QTranslator;
class QToolBar;
class Project;
class FileIO;
class StatusBar;
class PrintManager;
class Simulator;
class MainControl;
class ICheck;

/**
 * @class MainWindow
 * @brief The main window of the application.
 *
 * Stores all the menus, the status bar, the project, the file-io object, the
 * options and the control classes.
 */
class MainWindow : public QMainWindow
{
  Q_OBJECT
  public:
    MainWindow(QObject* parent=0, const char* name=0);
    ~MainWindow();

    /// Returns the options.
    Options* getOptions() { return &doc_options; }
    /// Returns the scroll view.
    ScrollView* getScrollView() { return wscroll; }
    /// Returns the status bar.
    StatusBar* getStatusBar() { return statusbar; }
    /// Returns the tab dialog for the general options
    OptGeneralDlgImpl* getOptGeneral() { return opt_general; }
    /// Returns the tab dialog for the display options
    OptDisplayDlgImpl* getOptDisplay() { return opt_display; }
    /// Returns the tab dialog for the printing options
    OptPrintingDlgImpl* getOptPrinting() { return opt_printing; }
    /// Returns the AHDL export dialog 
    ExportAHDLDlgImpl* getExportAHDL() { return ahdl_export; }
    /// Returns the VHDL export dialog 
    ExportVHDLDlgImpl* getExportVHDL() { return vhdl_export; }
        /// Returns the VHDL export dialog
    ExportTestbenchDlgImpl* getExportTestbench() { return testbench_export; }
    /// Returns the Verilog export dialog 
    ExportVerilogDlgImpl* getExportVerilog() { return ver_export; }
    /// Returns the State table export dialog 
    ExportStateTableDlgImpl* getExportStateTable() {return statetable_export;}
    /// Returns the Ragel export dialog
    ExportRagelDlgImpl* getExportRagel() { return ragel_export; }
    /// Returns the VVVV export dialog 
    ExportVVVVDlgImpl* getExportVVVV() { return vvvv_export; }
    /// Sets the string with the language 
    void setLanguage(QString s) { language = s; 
      opt_general->setLanguage(language);}
    /// Gets the string with the language 
    QString getLanguage() { return language; }
    void updateIOView(Machine*);
    bool runDragOperation(bool force_copy);
 
//    void repaintView() { wscroll->viewport()->repaint(); };
    /// Returns true if the shift key is pressed otherwise false
    bool shiftPressed() { return shift_pressed; }
    /// Returns true if the control key is pressed otherwise false
    bool controlPressed() { return control_pressed; }

    /// The project this window contains
    Project* project;
    /// State manager
    StateManager* statemanager;
    /// Machine manager
    MachineManager* machinemanager;
    /// Transition manager
    TransitionManager* transmanager;
    /// File I/O
    FileIO* fileio;
    /// Print manager
    PrintManager* printmanager;

    /// Returns the current mode.
    int getMode() { return doc_status.getMode(); }

    /// true if this window is about to close
    bool aboutToClose;

  protected:
    virtual void keyPressEvent(QKeyEvent* );
    virtual void keyReleaseEvent(QKeyEvent* );
    virtual void closeEvent(QCloseEvent* );
    virtual void focusInEvent(QFocusEvent* );
    virtual void dragEnterEvent(QDragEnterEvent* );
    virtual void dropEvent(QDropEvent* );


private:
    void createToolBar();
    void destroyToolBar();

    /// Pointer to the main control
    MainControl* control;
    /// Scroll view
    ScrollView* wscroll;
    /// Menu bar
    QMenuBar* menubar;
    /// File menu
    QMenu* menu_file;
    /// File->Import menu
    QMenu* menu_import;
    /// File->Export menu
    QMenu* menu_export;
    /// Edit menu
    QMenu* menu_edit;
    /// View menu
    QMenu* menu_view;
    /// Machine menu
    QMenu* menu_machine;
    /// State menu
    QMenu* menu_state;
    /// Transition menu
    QMenu* menu_trans;
    /// Help menu
    QMenu* menu_help;
    /// 'File->Most recently used' menu
    QMenu* menu_mru;
    /// Context menu (state)
    QMenu* cmenu_state;
    /// Context menu (transition)
    QMenu* cmenu_trans;
    /// Context menu (scroll view)
    QMenu* cmenu_sview;
    /// Toolbar
    QToolBar* toolbar;
    /// Application icon
    QPixmap* pappicon;
    /// New file icon
    QPixmap* pnew;
    /// Open file icon
    QPixmap* popen;
    /// Zoom in icon
    QPixmap* pzoomin;
    /// Zoom out icon
    QPixmap* pzoomout;
    /// New file tool button
    QToolButton* tbnew;
    /// Open file tool button
    QToolButton* tbopen;
    /// Save file tool button
    QToolButton* tbsave;
    /// Print file tool button
    QToolButton* tbprint;
    /// Undo tool button
    QToolButton* tbundo;
    /// Cut tool button
    QToolButton* tbcut;
    /// Copy tool button
    QToolButton* tbcopy;
    /// Paste tool button
    QToolButton* tbpaste;
    /// Select tool button
    QToolButton* tbselect;
    /// Pan tool button
    QToolButton* tbpan;
    /// Zoom tool button
    QToolButton* tbzoom;
    /// New state tool button
    QToolButton* tbstatenew;
    /// New transition tool button
    QToolButton* tbtransnew;
    /// Simulate machine tool button
    QToolButton* tbmachinesim;
    /// Zoom in tool button
    QToolButton* tbzoomin;
    /// Zoom out tool button
    QToolButton* tbzoomout;
    /// Straighten transition tool button
    QToolButton* tbtransstraighten;
    /// Save file icon set
    QIcon* saveset;
    /// Print file icon set
    QIcon* printset;
    /// Undo icon set
    QIcon* undoset;
    /// Cut icon set
    QIcon* cutset;
    /// Copy icon set
    QIcon* copyset;
    /// Paste icon set
    QIcon* pasteset;
    /// Select icon set
    QIcon* selset;
    /// Pan icon set
    QIcon* panset;
    /// Zoom icon set
    QIcon* zoomset;
    /// New state icon set
    QIcon* statenewset;
    /// New transition icon set
    QIcon* transnewset;
    /// Straighten transition icon set
    QIcon* transstraightenset;
    /// Simulate machine icon set
    QIcon* machinesimset;
    /// Zoom cursor
    QCursor* zoomCursor;

    // menu item IDs
    // file
    QAction* id_open;		///< Menu id 'File->Open'
    QAction* id_save;		///< Menu id 'File->Save'
    QAction* id_saveas;		///< Menu id 'File->Save as'
    QAction* id_print;		///< Menu id 'File->Print'
    QAction* id_close; 		///< Menu id 'File->Close'
    QAction* id_import;		///< Menu id 'File->Import'
    QAction* id_import_graphviz;     ///< Menu id 'File->Import->Graphviz'
    QAction* id_export;		///< Menu id 'File->Export'
    QAction* id_export_eps;		///< Menu id 'File->Export->EPS'
    QAction* id_export_svg;		///< Menu id 'File->Export->SVG'
    QAction* id_export_png;      ///< Menu id 'File->Export->PNG'
    QAction* id_export_ahdl;		///< Menu id 'File->Export->AHDL'
    QAction* id_export_vhdl;		///< Menu id 'File->Export->VDHL'
    QAction* id_export_iodescription;   ///< Menu id 'File->Export->IO Description'
    QAction* id_export_testbench;   /// <Menu id 'File->Export->VHDL Testbench'
    QAction* id_export_verilog;	///< Menu id 'File->Export->Verilog HDL'
    QAction* id_export_kiss;		///< Menu id 'File->Export->KISS'
    QAction* id_export_vvvv;		///< Menu id 'File->Export->vvvv Automata code'
    QAction* id_export_scxml;	///< Menu id 'File->Export->SCXML'
    QAction* id_export_stascii;	///< Menu id 'File->Export->ASCII state table'
    QAction* id_export_stlat;	///< Menu id 'File->Export->Latex state table'
    QAction* id_export_sthtml;	///< Menu id 'File->Export->HTML state table'
    QAction* id_export_ragel;	///< Menu id 'File->Export->Ragel'
    QAction* id_export_smc;		///< Menu id 'File->Export->SMC'

    // edit
    QAction* id_undo;		///< Menu id 'Edit->Undo'
    QAction* id_cut;			///< Menu id 'Edit->Cut'
    QAction* id_copy;		///< Menu id 'Edit->Copy'
    QAction* id_paste;		///< Menu id 'Edit->Paste'
    QAction* id_delete;		///< Menu id 'Edit->Delete'
    QAction* id_select; 		///< Menu id 'Edit->Select'
    QAction* id_selectall;		///< Menu id 'Edit->Select all'
    QAction* id_deselectall;		///< Menu id 'Edit->Deselect all'

    // view
    QAction* id_pan; 		///< Menu id 'View->Pan'
    QAction* id_zoom;		///< Menu id 'View->Zoom'
    QAction* id_zoomin;		///< Menu id 'View->Zoom in'
    QAction* id_zoomout;		///< Menu id 'View->Zoom out'
    QAction* id_zoom100;		///< Menu id 'View->Zoom 100%'
    QAction* id_viewstateenc;	///< Menu id 'View->State codes'
    QAction* id_viewmoore;		///< Menu id 'View->Moore outputs'
    QAction* id_viewmealyin;		///< Menu id 'View->Mealy inputs'
    QAction* id_viewmealyout;	///< Menu id 'View->Mealy outputs'
    QAction* id_viewgrid;		///< Menu id 'View->Grid'
    QAction* id_viewshadows;		///< Menu id 'View->Shadows'
    QAction* id_ioview;		///<Menu id 'View->IO View'

    // machine
    QAction* id_machineedit;		///< Menu id 'Machine->Edit'
    QAction* id_machinesim;		///< Menu id 'Machine->Simulate'
    QAction* id_correctcodes;  ///<Menu id 'Machine->Auto correct State Codes'
    QAction* id_machineicheck;	///< Menu id 'Machine->Check integrity'

    // state
    QAction* id_editstate;		///< Menu id 'State->Edit'
    QAction* id_newstate;		///< Menu id 'State->New'
    QAction* id_setinitial;		///< Menu id 'State->Set initial'
    QAction* id_setend;		///< Menu id 'State->Toggle end state'

    // transition
    QAction* id_edittrans;		///< Menu id 'Transition->Edit'
    QAction* id_newtrans;		///< Menu id 'Transition->New'
    QAction* id_trans_straight;	///< Menu id 'Transition->Straighten'

    // context menu item IDs
    // state
    QAction* id_ceditstate;		///< Context menu id 'Edit state'
    QAction* id_csetinitial;		///< Context menu id 'Set initial state'
    QAction* id_csetend;		///< Context menu id 'Toggle end state'
    QAction* id_csundo;		///< Context menu id 'Undo' (State)
    QAction* id_cscut;		///< Context menu id 'Cut' (State)
    QAction* id_cscopy;		///< Context menu id 'Copy' (State)
    QAction* id_csdelete; 		///< Context menu id 'Delete' (State)

    // transition
    QAction* id_cedittrans;		///< Context menu id 'Edit transition'
    QAction* id_ctrans_straight;	///< Context menu id 'Straighten transition'
    QAction* id_ctundo;		///< Context menu id 'Undo' (Transition)
    QAction* id_ctcut;		///< Context menu id 'Cut' (Transition)
    QAction* id_ctcopy;		///< Context menu id 'Copy' (Transition)
    QAction* id_ctdelete; 		///< Context menu id 'Delete' (Transition)


    /// Messagebox that is opend when the user wants to close a changed file
    QMessageBox* mb_changed;
    /// Status bar
    StatusBar* statusbar;
    /// Doc status
    DocStatus doc_status;   
    /// Options
    Options doc_options;
    /// Edit object
    Edit* edit;
    
    /// Tabdialog (options)
    TabDialog* tabdialog;
    /// General options dialog
    OptGeneralDlgImpl* opt_general;
    /// Display options dialog
    OptDisplayDlgImpl* opt_display;
    /// Printing options dialog
    OptPrintingDlgImpl* opt_printing;
    /// VHDL export options dialog
    ExportVHDLDlgImpl* vhdl_export;
    /// Verilog export options dialog
    ExportVerilogDlgImpl* ver_export;
    /// AHDL export options dialog
    ExportAHDLDlgImpl* ahdl_export;
    /// State table export options dialog
    ExportStateTableDlgImpl* statetable_export;
    /// Ragel export options dialog
    ExportRagelDlgImpl* ragel_export;
    /// Testbench export options dialog
    ExportTestbenchDlgImpl *testbench_export;
    /// Testbench export options dialog
    ExportVVVVDlgImpl *vvvv_export;

    /// IO view dialog
    IOViewDlgImpl* view_io;

    /// Simulator
    Simulator* simulator;
    /// Integrity checker
    ICheck* ichecker;

    /// If true the shift key was pressed
    bool shift_pressed;
    /// If true the control key was pressed
    bool control_pressed;

    /// true if a cut operation, false if a copy operation is performed (used in paste)
    bool bcut;
    /// Language
    QString language;
    /// Previous view cursor (used when wait cursor is set)
    QCursor previous_viewcursor;

  signals:
    /// Emited when 'Select all' is performed
    void allSelected();
    /// Emited when a set of objects has been pasted into this main window
    void objectsPasted();
    /// Emited when this main window is about to close
    void quitWindow(MainWindow*);
    /// Emited when the zoom factor changes
    void updateStatusZoom(int );
    /// Emited when the escape key has been pressed
    void escapePressed();

  public slots:
    void refreshMRU();
    void setMode(int );
    void repaintViewport();
    void updateAll();
    void updatePaste();
    void updateMenuBar();
    void updateTitleBar();
    void updateStatusBar();
    void updateVVVV();

    void menuItemActivated(int id);
    void editMenuAboutToShow();
    void showContextState();
    void showContextTrans();
    void showContext();

    void sbMessage(QString s); 
    void sbMessage(QString s, int t);
    void setWaitCursor();
    void setPreviousCursor();

    void fileNew();
    void fileOpen();
    bool fileSave();
    bool fileSaveAs();

    void fileImportGraphviz();

    bool fileExportEPS();
    bool fileExportSVG();
    bool fileExportPNG();
    bool fileExportAHDL();
    bool fileExportVHDL();
    bool fileExportIODescription();
    bool fileExportVerilog();
    bool fileExportKISS();
    bool fileExportSCXML();
    bool fileExportVVVV();
    bool fileExportTestbench();
    bool fileExportSTASCII();
    bool fileExportSTLatex();
    bool fileExportSTHTML();
    bool fileExportRagel();
    bool fileExportSMC();
    void filePrint();
    bool fileClose();
    void fileQuit();

    void fileOpenRecent(QString fileName);
    void fileOpenRecent0();
    void fileOpenRecent1();
    void fileOpenRecent2();
    void fileOpenRecent3();
    void fileOpenRecent4();
    void fileOpenRecent5();
    void fileOpenRecent6();
    void fileOpenRecent7();
    void fileOpenRecent8();
    void fileOpenRecent9();

    void editUndo();
    void editCut();
    void editCopy();
    void editPaste();
    void editDelete();
    void editSelect();
    void editSelectAll();
    void editDeselectAll();
    void editOptions();

    void viewStateEncoding();
    void viewMooreOutputs();
    void viewMealyInputs();
    void viewMealyOutputs();
    void viewGrid();
    void viewShadows();
    void viewPan();
    void viewZoom();
    void viewZoomIn();
    void viewZoomOut();
    void viewZoom100();
    void viewIOView();

    void machineEdit();
    void machineSimulate();
    void machineICheck();
    void machineCorrectCodes();

    void stateNew();
    void stateEdit();
    void stateSetInitial();
    void stateSetFinal();

    void transNew();
    void transEdit();
    void transStraighten();

    void helpManual();
    void helpAbout();
    void helpAboutQt();
};


#endif
