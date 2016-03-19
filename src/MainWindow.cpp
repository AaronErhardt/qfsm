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

#include <qobject.h>
#include <QMainWindow>
#include <qapplication.h>
#include <qclipboard.h>
#include <q3toolbar.h>
#include <qtoolbutton.h>
#include <qcursor.h>
#include <QDesktopServices>
#include <QUrl>
#include <qsettings.h>
#include <q3textstream.h>
#include <QPixmap>
#include <QFocusEvent>
#include <QCloseEvent>
#include <QKeyEvent>
#include <QMenu>
#include <QMenu>
#include <string>
#include <sstream>
#include <fstream>

#include "MainWindow.h"
#include "MainControl.h"
#include "ScrollView.h"
#include "DocStatus.h"
#include "Project.h"
#include "StateManager.h"
#include "Selection.h"
#include "ImportGraphviz.h"
#include "ExportAHDL.h"
#include "ExportEPS.h"
#include "ExportKISS.h"
#include "ExportSVG.h"
#include "ExportPNG.h"
#include "ExportVHDL.h"
#include "ExportVVVV.h"
#include "ExportSCXML.h"
#include "ExportSMC.h"
#include "ExportIODescription.h"
#include "ExportVerilog.h"
#include "ExportRagel.h"
#include "ExportStateTable.h"
#include "TableBuilderASCII.h"
#include "TableBuilderLatex.h"
#include "TableBuilderHTML.h"
#include "FileIO.h"
#include "StatusBar.h"
#include "UndoBuffer.h"
#include "AppInfo.h"
#include "PrintManager.h"
#include "Simulator.h"
#include "MimeMachine.h"
#include "Error.h"
#include "ICheck.h"
#include "TransitionInfo.h"
#include "DrawArea.h"

#include "../pics/filenew.xpm"
#include "../pics/fileopen.xpm"
#include "../pics/filesave.xpm"
#include "../pics/filesaveoff.xpm"
#include "../pics/fileprint.xpm"
#include "../pics/fileprintoff.xpm"
#include "../pics/editundo.xpm"
#include "../pics/editundooff.xpm"
#include "../pics/editcut.xpm"
#include "../pics/editcutoff.xpm"
#include "../pics/editcopy.xpm"
#include "../pics/editcopyoff.xpm"
#include "../pics/editpaste.xpm"
#include "../pics/editpasteoff.xpm"
#include "../pics/select.xpm"
#include "../pics/selectoff.xpm"
#include "../pics/statenew.xpm"
#include "../pics/statenewoff.xpm"
#include "../pics/transnew.xpm"
#include "../pics/transnewoff.xpm"
#include "../pics/transstraighten.xpm"
#include "../pics/transstraightenoff.xpm"
#include "../pics/machinesim.xpm"
#include "../pics/machinesimoff.xpm"
#include "../pics/zoom.xpm"
#include "../pics/zoomoff.xpm"
#include "../pics/pan.xpm"
#include "../pics/panoff.xpm"
#include "../pics/zoomin.xpm"
#include "../pics/zoomout.xpm"
#include "../pics/c_mag.xpm"
#include "../pics/qfsm_64.xpm"

#include "IOInfo.h"


using namespace std;

/**
 * Constructor.
 * Initialises the mainwindow with all its menus.
 */
MainWindow::MainWindow(QObject* parent , const char* name )
           :QMainWindow(NULL, name)
{
  control = (MainControl*)parent;
  project = NULL;
  wscroll = new ScrollView(this);
  setCentralWidget(wscroll);

  setAcceptDrops(true);
  
  
//  QPixmap pix("qfsm_64.png", "PNG");
//  setIcon(pix);
  QPixmap paicon((const char**)qfsm_64_xpm);
  setIcon(paicon);

  createToolBar();

  menubar = menuBar();
  //menubar=new QMenuBar(this);
  menu_mru = new QMenu(this);

  menu_import = new QMenu(this);
  menu_import->setMouseTracking(TRUE);
#ifdef GRAPHVIZ_FOUND
  id_import_graphviz = menu_import->insertItem(tr("&Graphviz..."), this, SLOT(fileImportGraphviz()));
#endif

  /*
  qDebug("%d", IOInfo::isBinaryType("ANY 01101|0|101"));
  qDebug("%d", IOInfo::isBinaryType("DEF"));
  qDebug("%d", IOInfo::isBinaryType("ANY01101|0|101"));
  qDebug("%d", IOInfo::isBinaryType("ANY  01101101"));
  qDebug("%d", IOInfo::isBinaryType("ANY"));
  qDebug("%d", IOInfo::isBinaryType("01101|0|101"));
  qDebug("%d", IOInfo::isBinaryType("01101101"));
  */
  /*
  qDebug("%d", IOInfo::isASCIIType("01101|0|101"));
  qDebug("%d", IOInfo::isASCIIType("transition1"));
  qDebug("%d", IOInfo::isASCIIType("\\011"));
  qDebug("%d", IOInfo::isASCIIType("This is a test."));
  qDebug("%d", IOInfo::isASCIIType("abcde"));
  qDebug("%d", IOInfo::isASCIIType("abce\\n"));
  */

  // File -> Export
  menu_export = new QMenu(this);
  menu_export->setMouseTracking(TRUE);
  id_export_eps = menu_export->insertItem(tr("E&PS..."), this, SLOT(fileExportEPS()));
  id_export_svg = menu_export->insertItem(tr("&SVG..."), this, SLOT(fileExportSVG()));
  id_export_png = menu_export->insertItem(tr("&PNG..."), this, SLOT(fileExportPNG()));
  menu_export->insertSeparator();
  id_export_ahdl = menu_export->insertItem(tr("&AHDL..."), this, SLOT(fileExportAHDL()));
  id_export_vhdl = menu_export->insertItem(tr("&VHDL..."), this, SLOT(fileExportVHDL()));
  id_export_verilog = menu_export->insertItem(tr("V&erilog HDL..."), this,
      SLOT(fileExportVerilog()));
  id_export_kiss = menu_export->insertItem(tr("&KISS"), this, SLOT(fileExportKISS()));
  menu_export->insertSeparator();
  id_export_testbench = menu_export->insertItem(tr("VHDL &Testbench"),this,SLOT(fileExportTestbench()));
  id_export_iodescription = menu_export->insertItem(tr("I/O &Description"), this, SLOT(fileExportIODescription()));

  menu_export->insertSeparator();
  id_export_scxml = menu_export->insertItem(tr("SC&XML"), this, SLOT(fileExportSCXML()));
  id_export_vvvv = menu_export->insertItem(tr("vvvv A&utomata code"), this, SLOT(fileExportVVVV()));
  menu_export->insertSeparator();
  id_export_stascii = menu_export->insertItem(tr("State Table (ASC&II)..."), 
      this, SLOT(fileExportSTASCII()));
  id_export_stlat = menu_export->insertItem(tr("State Table (&Latex)..."), 
      this, SLOT(fileExportSTLatex()));
  id_export_sthtml = menu_export->insertItem(tr("State Table (&HTML)..."), 
      this, SLOT(fileExportSTHTML()));
  menu_export->insertSeparator();
  id_export_ragel = menu_export->insertItem(tr("&Ragel..."), this, SLOT(fileExportRagel()));
  id_export_smc = menu_export->insertItem(tr("SM&C..."), this, SLOT(fileExportSMC()));

  // File
  menu_file = new QMenu(this);
  menu_file->setMouseTracking(TRUE);
  menu_file->insertItem(*pnew, tr("&New..."), this, SLOT(fileNew()), Qt::CTRL+Qt::Key_N);
  id_open = menu_file->insertItem(*popen, tr("&Open..."), this, SLOT(fileOpen()), 
    Qt::CTRL+Qt::Key_O);
  menu_file->insertItem(tr("Open &Recent"), menu_mru);
  menu_file->insertSeparator();
  id_save = menu_file->insertItem(*saveset, tr("&Save"), this, SLOT(fileSave()), 
    Qt::CTRL+Qt::Key_S);
  id_saveas = menu_file->insertItem(tr("Save &As..."), this, SLOT(fileSaveAs()));
  menu_file->insertSeparator();
  id_import = menu_file->insertItem(tr("&Import"), menu_import);
  id_export = menu_file->insertItem(tr("&Export"), menu_export);
  menu_file->insertSeparator();
  id_print = menu_file->insertItem(*printset, tr("&Print..."), this, 
    SLOT(filePrint()), Qt::CTRL+Qt::Key_P);
  menu_file->insertSeparator();
  menu_file->insertItem(tr("New &Window"), control, SLOT(newWindow()) );
  menu_file->insertSeparator();
  id_close = menu_file->insertItem(tr("&Close"), this, SLOT(fileClose()),
    Qt::CTRL+Qt::Key_W );
  menu_file->insertItem(tr("&Quit"), this, SLOT(fileQuit()), Qt::CTRL+Qt::Key_Q);

  // Edit
  menu_edit = new QMenu(this);
  menu_edit->setCheckable(TRUE);
  menu_edit->setMouseTracking(TRUE);
  id_undo = menu_edit->insertItem(*undoset, tr("U&ndo"), this, SLOT(editUndo()), 
    Qt::CTRL+Qt::Key_Z);
  menu_edit->insertSeparator();
  id_cut = menu_edit->insertItem(*cutset, tr("C&ut"), this, SLOT(editCut()), Qt::CTRL+Qt::Key_X);
  id_copy = menu_edit->insertItem(*copyset, tr("&Copy"), this, 
    SLOT(editCopy()), Qt::CTRL+Qt::Key_C);
  id_paste = menu_edit->insertItem(*pasteset, tr("&Paste"), this, 
    SLOT(editPaste()), Qt::CTRL+Qt::Key_V);
  id_delete = menu_edit->insertItem(tr("De&lete"), this, SLOT(editDelete()),
   Qt::Key_Delete);
  menu_edit->insertSeparator();
  id_select = menu_edit->insertItem(*selset, tr("&Select"), this, 
    SLOT(editSelect()), Qt::CTRL+Qt::SHIFT+Qt::Key_S);
  id_selectall = menu_edit->insertItem(tr("Select &All"), this, 
    SLOT(editSelectAll()), Qt::CTRL+Qt::Key_A);
  id_deselectall = menu_edit->insertItem(tr("&Deselect All"), this, 
    SLOT(editDeselectAll()), Qt::CTRL+Qt::Key_D);
  menu_edit->insertSeparator();
  menu_edit->insertItem(tr("&Options"), this, SLOT(editOptions()));

  // View
  menu_view = new QMenu(this);
  menu_view->setCheckable(TRUE);
  menu_view->setMouseTracking(TRUE);
  id_viewstateenc = menu_view->insertItem(tr("State &Codes"), this,
    SLOT(viewStateEncoding()));
  id_viewmoore = menu_view->insertItem(tr("Moo&re Outputs"), this,
    SLOT(viewMooreOutputs()), Qt::CTRL+Qt::Key_M);
  id_viewmealyin = menu_view->insertItem(tr("Mealy I&nputs"), this,
    SLOT(viewMealyInputs()));
  id_viewmealyout = menu_view->insertItem(tr("Mea&ly Outputs"), this,
    SLOT(viewMealyOutputs()));
  menu_view->insertSeparator();
  id_viewshadows = menu_view->insertItem(tr("&Shadows"), this,
    SLOT(viewShadows()));
  id_viewgrid = menu_view->insertItem(tr("&Grid"), this, SLOT(viewGrid()));
  menu_view->insertSeparator();
  id_ioview = menu_view->insertItem(tr("&IO View"),this,SLOT(viewIOView()));
  menu_view->insertSeparator();
  id_pan = menu_view->insertItem(*panset, tr("&Pan view"), this, 
    SLOT(viewPan()), Qt::CTRL+Qt::SHIFT+Qt::Key_P);
  id_zoom = menu_view->insertItem(*zoomset, tr("&Zoom"), this, 
    SLOT(viewZoom()), Qt::CTRL+Qt::SHIFT+Qt::Key_Z);
  id_zoomin = menu_view->insertItem(*pzoomin, tr("Zoom &In"), this, 
    SLOT(viewZoomIn()), Qt::CTRL+Qt::Key_I);
  id_zoomout = menu_view->insertItem(*pzoomout, tr("Zoom &Out"), this, 
    SLOT(viewZoomOut()), Qt::CTRL+Qt::Key_U);
  id_zoom100 = menu_view->insertItem(tr("Zoom &100%"), this,
    SLOT(viewZoom100()), Qt::CTRL+Qt::Key_R);

  // Machine
  menu_machine = new QMenu(this);
  menu_machine->setMouseTracking(TRUE);
  id_machineedit = menu_machine->insertItem(tr("&Edit..."), this, 
    SLOT(machineEdit()));
  id_correctcodes = menu_machine->insertItem(tr("&Auto correct State Codes..."), this, 
                                            SLOT(machineCorrectCodes()));
  id_machinesim = menu_machine->insertItem(*machinesimset, tr("&Simulate..."), 
    this, SLOT(machineSimulate()), Qt::CTRL+Qt::SHIFT+Qt::Key_I);
  id_machineicheck = menu_machine->insertItem(tr("&Integrity Check"), this,
      SLOT(machineICheck()));
  
  // State
  menu_state = new QMenu(this);
  menu_state->setCheckable(TRUE);
  menu_state->setMouseTracking(TRUE);
  id_newstate = menu_state->insertItem(*statenewset, tr("&New"), this, 
    SLOT(stateNew()), Qt::CTRL+Qt::SHIFT+Qt::Key_N);
  id_editstate = menu_state->insertItem(tr("&Edit..."), this, 
      SLOT(stateEdit()));
  id_setinitial = menu_state->insertItem(tr("Set &Initial State"), this,
    SLOT(stateSetInitial()));
  id_setend = menu_state->insertItem(tr("&Toggle Final State"), this,
    SLOT(stateSetFinal()), Qt::CTRL+Qt::Key_E);


  // Transition
  menu_trans = new QMenu(this);
  menu_trans->setMouseTracking(TRUE);
  id_newtrans = menu_trans->insertItem(*transnewset, tr("&New"), this,
    SLOT(transNew()), Qt::CTRL+Qt::SHIFT+Qt::Key_T);
  id_edittrans = menu_trans->insertItem(tr("&Edit..."), this, 
      SLOT(transEdit()));
  id_trans_straight = menu_trans->insertItem(*transstraightenset, 
    tr("&Straighten"), this, SLOT(transStraighten()), Qt::CTRL+Qt::Key_T);

  // Help
/*  menu_help = new QMenu(this);
  menu_help->setMouseTracking(TRUE);
  menu_help->insertItem(tr("&About..."), this, SLOT(helpAbout()));
  menu_help->insertSeparator();
  menu_help->insertItem(tr("About &Qt..."), this, SLOT(helpAboutQt()));
*/
  menu_help = new QMenu(this);
  menu_help->setMouseTracking(TRUE);
  menu_help->addAction (tr("Qfsm &Manual..."), this, SLOT(helpManual()), Qt::Key_F1);
  menu_help->insertSeparator();
  menu_help->addAction (tr("&About..."), this, SLOT(helpAbout()));
  menu_help->addAction (tr("About &Qt..."), this, SLOT(helpAboutQt()));


  menubar->insertItem(tr("&File"), menu_file);
  menubar->insertItem(tr("&Edit"), menu_edit);
  menubar->insertItem(tr("&View"), menu_view);
  menubar->insertItem(tr("&Machine"), menu_machine);
  menubar->insertItem(tr("&State"), menu_state);
  menubar->insertItem(tr("&Transition"), menu_trans);
  menubar->insertItem(tr("&Help"), menu_help);
  
  // Context Menu: State
  cmenu_state = new QMenu(this);
  cmenu_state->setMouseTracking(TRUE);
  id_csundo = cmenu_state->insertItem(*undoset, tr("U&ndo"), this, 
    SLOT(editUndo()), Qt::CTRL+Qt::Key_Z);
  cmenu_state->insertSeparator();
  id_cscut = cmenu_state->insertItem(*cutset, tr("C&ut"), this, 
    SLOT(editCut()), Qt::CTRL+Qt::Key_X);
  id_cscopy = cmenu_state->insertItem(*copyset, tr("&Copy"), this, 
    SLOT(editCopy()), Qt::CTRL+Qt::Key_C);
  id_csdelete = cmenu_state->insertItem(tr("De&lete"), this, 
    SLOT(editDelete()), Qt::Key_Delete);
  cmenu_state->insertSeparator();
  id_ceditstate = cmenu_state->insertItem(tr("&Edit..."), this, SLOT(stateEdit()));
  id_csetinitial = cmenu_state->insertItem(tr("Set &Initial State"), this,
    SLOT(stateSetInitial()));
  id_csetend = cmenu_state->insertItem(tr("&Toggle Final State"), this,
    SLOT(stateSetFinal()));

  // Context Menu: Transition
  cmenu_trans = new QMenu(this);
  cmenu_trans->setMouseTracking(TRUE);
  id_ctundo = cmenu_trans->insertItem(*undoset, tr("U&ndo"), this, SLOT(editUndo()), 
    Qt::CTRL+Qt::Key_Z);
  cmenu_trans->insertSeparator();
  id_ctcut = cmenu_trans->insertItem(*cutset, tr("C&ut"), this, 
    SLOT(editCut()), Qt::CTRL+Qt::Key_X);
  id_ctcopy = cmenu_trans->insertItem(*copyset, tr("&Copy"), this, 
    SLOT(editCopy()), Qt::CTRL+Qt::Key_C);
  id_ctdelete = cmenu_trans->insertItem(tr("De&lete"), this, 
    SLOT(editDelete()), Qt::Key_Delete);
  cmenu_trans->insertSeparator();
  id_cedittrans = cmenu_trans->insertItem(tr("&Edit..."), this, SLOT(transEdit()));
  id_ctrans_straight = cmenu_trans->insertItem(*transstraightenset, 
    tr("&Straighten"), this, SLOT(transStraighten()), Qt::CTRL+Qt::Key_T);

  // Context Menu: ScrollView
  cmenu_sview = menu_edit;

  statusbar = new StatusBar(this);
  setStatusBar(statusbar);


  statemanager = new StateManager(this);
  machinemanager = new MachineManager(this);
  transmanager = new TransitionManager(this);
  fileio = new FileIO(this);
  printmanager = new PrintManager(this);

  mb_changed = new QMessageBox("qfsm", 
    tr("The file has been changed. Do you want to save it?"), 
    QMessageBox::Information, 
    QMessageBox::Yes | QMessageBox::Default,
    QMessageBox::No, 
    QMessageBox::Cancel | QMessageBox::Escape);
  mb_changed->setButtonText(QMessageBox::Yes, tr("Yes"));
  mb_changed->setButtonText(QMessageBox::No, tr("No"));
  mb_changed->setButtonText(QMessageBox::Cancel, tr("Cancel"));


  fileio->loadOptions(&doc_options);
  fileio->loadMRU(control->getMRUList());

  tabdialog = new Q3TabDialog(this, 0, TRUE);
  tabdialog->resize(400, 300);
  tabdialog->setCaption(tr("Qfsm Options"));

  opt_general = new OptGeneralDlgImpl(tabdialog);
  opt_general->init();

  opt_display = new OptDisplayDlgImpl(tabdialog);
  opt_display->init(&doc_options);

  opt_printing = new OptPrintingDlgImpl(tabdialog);
  opt_printing->init(&doc_options);

  tabdialog->addTab(opt_general, tr("&General"));
  tabdialog->addTab(opt_display, tr("&Display"));
  tabdialog->addTab(opt_printing, tr("&Printing"));
  tabdialog->setOkButton();
  tabdialog->setCancelButton();

  ahdl_export = new ExportAHDLDlgImpl(this);
  ahdl_export->init(&doc_options);
  ver_export = new ExportVerilogDlgImpl(this);
  ver_export->init(&doc_options);
  vhdl_export = new ExportVHDLDlgImpl(this);
  vhdl_export->init(&doc_options, NULL);
  statetable_export = new ExportStateTableDlgImpl(this);
  statetable_export->init(&doc_options);
  ragel_export = new ExportRagelDlgImpl(this);
  ragel_export->init(&doc_options);
  testbench_export = new ExportTestbenchDlgImpl(this);
  testbench_export->init(&doc_options,NULL);
  vvvv_export = new ExportVVVVDlgImpl(this);
  vvvv_export->init(&doc_options,NULL);

  view_io =new IOViewDlgImpl(this);
  simulator = new Simulator(this);
  ichecker = new ICheck(this);
  edit = new Edit(this);

  shift_pressed=FALSE;
  control_pressed=FALSE;
  bcut=FALSE;

  setMode(DocStatus::Select);
  updateAll(); //MenuBar();

  connect(menu_mru, SIGNAL(aboutToShow()), this, SLOT(refreshMRU()));
//  connect(cmenu_state, SIGNAL(aboutToHide()), wscroll, SLOT(contextMenuHiding()));
//  connect(cmenu_trans, SIGNAL(aboutToHide()), wscroll, SLOT(contextMenuHiding()));
//  connect(cmenu_sview, SIGNAL(aboutToHide()), wscroll, SLOT(contextMenuHiding()));
  connect(this, SIGNAL(allSelected()), wscroll->getDrawArea(), SLOT(allSelected()) );
  connect(this, SIGNAL(objectsPasted()), wscroll->getDrawArea(), SLOT(objectsPasted()) );
  connect(this, SIGNAL(quitWindow(MainWindow*)), control,SLOT(quitWindow(MainWindow*)));
  connect(this, SIGNAL(escapePressed()), wscroll->getDrawArea(), SLOT(escapePressed()) );
  connect(wscroll->getDrawArea(), SIGNAL(zoomedToPercentage(int)), statusbar, SLOT(setZoom(int)));
  connect(this, SIGNAL(updateStatusZoom(int)), wscroll->getDrawArea(), SIGNAL(zoomedToPercentage(int)) );
  connect(fileio, SIGNAL(sbMessage(QString)), this, SLOT(sbMessage(QString)));
  connect(menubar, SIGNAL(activated(int)), this, SLOT(menuItemActivated(int)));
  connect(menu_edit, SIGNAL(aboutToShow()), this, SLOT(editMenuAboutToShow()));
  connect(fileio, SIGNAL(setWaitCursor()), this, SLOT(setWaitCursor()) );
  connect(fileio, SIGNAL(setPreviousCursor()), this, SLOT(setPreviousCursor()) );
  connect(view_io,SIGNAL(closing()),this,SLOT(viewIOView()));
  connect(vvvv_export, SIGNAL(updateCode()), this, SLOT(updateVVVV()));
}


/// Destructor
MainWindow::~MainWindow()
{
  fileio->saveOptions(&doc_options);
 
  destroyToolBar();
  delete wscroll;
  delete menubar;
  delete menu_file;
  delete menu_import;
  delete menu_export;
  delete menu_edit;
  delete menu_view;
  delete menu_machine;
  delete menu_state;
  delete menu_trans;
  delete cmenu_state;
  delete cmenu_trans;
  if (project)
    delete project;
  
  delete statemanager;
  delete machinemanager;
  delete transmanager;
  delete printmanager;
  delete fileio;
  delete statusbar;
  delete tabdialog;
  delete simulator;
  delete edit;
  delete ichecker;

  delete mb_changed;

  delete ahdl_export;
  delete ver_export;
  delete vhdl_export;
  delete statetable_export;
  delete ragel_export;
  delete testbench_export;
  delete vvvv_export;
}


/// Creates the toolbar with its buttons
void MainWindow::createToolBar()
{
//  toolbar = new QToolBar("Main Toolbar", this);
  toolbar = addToolBar("Main Toolbar");
  toolbar->setMovable(true);

  pnew = new QPixmap((const char**)filenew);
  tbnew = new QToolButton(*pnew, tr("New File"), tr("Creates a new file"), 
    this, SLOT(fileNew()), toolbar);
  toolbar->addWidget(tbnew);

  popen = new QPixmap((const char**)fileopen);
  tbopen = new QToolButton(*popen, tr("Open File"), tr("Opens a file"), 
    this, SLOT(fileOpen()), toolbar);
  toolbar->addWidget(tbopen);


  QPixmap psave((const char**)filesave);
  QPixmap psaveoff((const char**)filesaveoff);
  saveset = new QIcon(psave);
  saveset->setPixmap(psaveoff, QIcon::Automatic, QIcon::Disabled);
  tbsave = new QToolButton(psave, tr("Save File"), tr("Saves this file"), 
    this, SLOT(fileSave()), toolbar);
  tbsave->setIconSet(*saveset);
  toolbar->addWidget(tbsave);
 
  QPixmap pprint((const char**)fileprint);
  QPixmap pprintoff((const char**)fileprintoff);
  printset = new QIcon(pprint);
  printset->setPixmap(pprintoff, QIcon::Automatic, QIcon::Disabled);
  tbprint = new QToolButton(pprint,tr("Print"), tr("Prints this file"), 
    this, SLOT(filePrint()), toolbar);
  tbprint->setIconSet(*printset);
  toolbar->addWidget(tbprint);
 
  QPixmap pundo((const char**)editundo);
  QPixmap pundooff((const char**)editundooff);
  undoset = new QIcon(pundo);
  undoset->setPixmap(pundooff, QIcon::Automatic, QIcon::Disabled);
  tbundo = new QToolButton(pundo,tr("Undo"), tr("Undo last action"), 
    this, SLOT(editUndo()), toolbar);
  tbundo->setIconSet(*undoset);
  toolbar->addWidget(tbundo);
 
  QPixmap pcut((const char**)editcut);
  QPixmap pcutoff((const char**)editcutoff);
  cutset = new QIcon(pcut);
  cutset->setPixmap(pcutoff, QIcon::Automatic, QIcon::Disabled);
  tbcut = new QToolButton(pcut,tr("Cut"), tr("Cuts Selection"), 
    this, SLOT(editCut()), toolbar);
  tbcut->setIconSet(*cutset);
  toolbar->addWidget(tbcut);
 
  QPixmap pcopy((const char**)editcopy);
  QPixmap pcopyoff((const char**)editcopyoff);
  copyset = new QIcon(pcopy);
  copyset->setPixmap(pcopyoff, QIcon::Automatic, QIcon::Disabled);
  tbcopy = new QToolButton(pcopy,tr("Copy"), tr("Copies Selection"), 
    this, SLOT(editCopy()), toolbar);
  tbcopy->setIconSet(*copyset);
  toolbar->addWidget(tbcopy);
 
  QPixmap ppaste((const char**)editpaste);
  QPixmap ppasteoff((const char**)editpasteoff);
  pasteset = new QIcon(ppaste);
  pasteset->setPixmap(ppasteoff, QIcon::Automatic, QIcon::Disabled);
  tbpaste = new QToolButton(ppaste,tr("Paste"), tr("Pastes the clipboard"), 
    this, SLOT(editPaste()), toolbar);
  tbpaste->setIconSet(*pasteset);
  toolbar->addWidget(tbpaste);

  toolbar->addSeparator();

  QPixmap pselect((const char**)sel);
  QPixmap pselectoff((const char**)selectoff);
  selset = new QIcon(pselect);
  selset->setPixmap(pselectoff, QIcon::Automatic, QIcon::Disabled);
  tbselect = new QToolButton(pselect,tr("Select"), tr("Select objects"), 
    this, SLOT(editSelect()), toolbar);
  tbselect->setIconSet(*selset);
  tbselect->setToggleButton(TRUE);
  toolbar->addWidget(tbselect);
 
  QPixmap ppan((const char**)pan);
  QPixmap ppanoff((const char**)panoff);
  panset = new QIcon(ppan);
  panset->setPixmap(ppanoff, QIcon::Automatic, QIcon::Disabled);
  tbpan = new QToolButton(ppan,tr("Pan"), tr("Pan view"), 
    this, SLOT(viewPan()), toolbar);
  tbpan->setIconSet(*panset);
  tbpan->setToggleButton(TRUE);
  toolbar->addWidget(tbpan);

  QPixmap pzoom((const char**)zoom);
  QPixmap pzoomoff((const char**)zoomoff);
  zoomset = new QIcon(pzoom);
  zoomset->setPixmap(pzoomoff, QIcon::Automatic, QIcon::Disabled);
  tbzoom = new QToolButton(pzoom,tr("Zoom"), tr("Switches to zoom mode"), 
    this, SLOT(viewZoom()), toolbar);
  tbzoom->setIconSet(*zoomset);
  tbzoom->setToggleButton(TRUE);
  toolbar->addWidget(tbzoom);

  QPixmap pstatenew((const char**)statenew);
  QPixmap pstatenewoff((const char**)statenewoff);
  statenewset = new QIcon(pstatenew);
  statenewset->setPixmap(pstatenewoff, QIcon::Automatic, QIcon::Disabled);
  tbstatenew = new QToolButton(pstatenew,tr("Add State"), tr("Add new states"), 
    this, SLOT(stateNew()), toolbar);
  tbstatenew->setIconSet(*statenewset);
  tbstatenew->setToggleButton(TRUE);
  toolbar->addWidget(tbstatenew);

  QPixmap ptransnew((const char**)transnew);
  QPixmap ptransnewoff((const char**)transnewoff);
  transnewset = new QIcon(ptransnew);
  transnewset->setPixmap(ptransnewoff, QIcon::Automatic, QIcon::Disabled);
  tbtransnew = new QToolButton(ptransnew,tr("Add Transition"), tr("Add new transitions"), 
    this, SLOT(transNew()), toolbar);
  tbtransnew->setIconSet(*transnewset);
  tbtransnew->setToggleButton(TRUE);
  toolbar->addWidget(tbtransnew);

  QPixmap pmachinesim((const char**)machinesim);
  QPixmap pmachinesimoff((const char**)machinesimoff);
  machinesimset = new QIcon(pmachinesim);
  machinesimset->setPixmap(pmachinesimoff, QIcon::Automatic, QIcon::Disabled);
  tbmachinesim = new QToolButton(pmachinesim,tr("Simulate"), tr("Simulates this machine"), 
    this, SLOT(machineSimulate()), toolbar);
  tbmachinesim->setIconSet(*machinesimset);
  tbmachinesim->setToggleButton(TRUE);
  toolbar->addWidget(tbmachinesim);

  toolbar->addSeparator();

  pzoomin = new QPixmap((const char**)zoomin);
  tbzoomin = new QToolButton(*pzoomin,tr("Zoom In"), tr("Zooms into the view"), 
    this, SLOT(viewZoomIn()), toolbar);
  toolbar->addWidget(tbzoomin);
 
  pzoomout = new QPixmap((const char**)zoomout);
  tbzoomout = new QToolButton(*pzoomout,tr("Zoom Out"), tr("Zoom out of the view"), 
    this, SLOT(viewZoomOut()), toolbar);
  toolbar->addWidget(tbzoomout);

  QPixmap ptransstraighten((const char**)transstraighten);
  QPixmap ptransstraightenoff((const char**)transstraightenoff);
  transstraightenset = new QIcon(ptransstraighten);
  transstraightenset->setPixmap(ptransstraightenoff, QIcon::Automatic, 
    QIcon::Disabled);
  tbtransstraighten = new QToolButton(ptransstraighten,tr("Straighten Transitions"), 
    tr("Straightens selected transitions"), 
    this, SLOT(transStraighten()), toolbar);
  tbtransstraighten->setIconSet(*transstraightenset);
  toolbar->addWidget(tbtransstraighten);


  zoomCursor = new QCursor(QPixmap((const char**)c_mag_xpm), 7, 7); 
}

/// Destroys the toolbar
void MainWindow::destroyToolBar()
{
  delete popen;
  delete pnew;
  delete pzoomin;
  delete pzoomout;
  delete saveset;
  delete printset;
  delete undoset;
  delete cutset;
  delete copyset;
  delete pasteset;
  delete selset;
  delete panset;
  delete zoomset;
  delete statenewset;
  delete transnewset;
  delete transstraightenset;
  delete machinesimset;
  delete tbnew;
  delete tbopen;
  delete tbsave;
  delete tbprint;
  delete tbundo;
  delete tbcut;
  delete tbcopy;
  delete tbpaste;
  delete tbselect;
  delete tbpan;
  delete tbzoom;
  delete tbstatenew;
  delete tbtransnew;
  delete tbmachinesim;
  delete tbzoomin;
  delete tbzoomout;
  delete tbtransstraighten;
  delete toolbar;
  delete zoomCursor;
}


/// Called when a key is pressed
void MainWindow::keyPressEvent(QKeyEvent* k)
{
  if (k->key()==Qt::Key_Shift)
    shift_pressed=TRUE;
  else if (k->key()==Qt::Key_Control)
    control_pressed=TRUE;
  else if (k->key()==Qt::Key_Escape)
  {
    emit escapePressed();
  }
}

/// Called when a key is released
void MainWindow::keyReleaseEvent(QKeyEvent* k)
{
  if (k->key()==Qt::Key_Shift)
    shift_pressed=FALSE;
  if (k->key()==Qt::Key_Control)
    control_pressed=FALSE;
}

/// Called when this window is about to close
void MainWindow::closeEvent(QCloseEvent*e )
{
//  fileQuit();
  doc_options.applyOptions(this);

  aboutToClose=TRUE;
  if (project && project->hasChanged())
  {
    switch(mb_changed->exec())
    {
      case QMessageBox::Yes:
        if (!fileSave())
        {
          aboutToClose=FALSE;
          e->ignore();
          return;
        }
        break;
      case QMessageBox::No:
        break;
      case QMessageBox::Cancel:
        e->ignore();
	aboutToClose=FALSE;
        return;
	break;
    }
  }
//  e->accept();
  emit quitWindow(this);
}

/// Called when this window receives the focus
void MainWindow::focusInEvent(QFocusEvent* e)
{
  qDebug("test");
  if (e->gotFocus())
  {
    if (e->reason()!=Qt::PopupFocusReason)
      updatePaste();
  }
}



/// Called when a drag & drop item enters the window
void MainWindow::dragEnterEvent( QDragEnterEvent*e)
{

  QString format;


  format = e->format();



  qDebug("Format: "+format);
  if (format!="text/qfsm-objects" && format!="text/uri-list" && !e->mimeData()->hasUrls())
  {

    return;
  }


  if(e->source()!=this)
    e->acceptProposedAction();
  else e->ignore();


}

/// Called when a drag & drop item is dropped
void MainWindow::dropEvent(QDropEvent*e)
{
  QString format,path,data;
  const QMimeData *mm;
  QList <QUrl> urls;
  format = e->format();



  qDebug("Format: "+format);

  if (format!="text/qfsm-objects" && format!="text/uri-list" && !e->mimeData()->hasUrls())
    return;

  e->acceptProposedAction();


  mm =e->mimeData();
  if(mm->hasUrls())
  {

    path=mm->urls().first().path();
    if(path.right(4)!=".fsm")
    {
      this->sbMessage("Invalid file type");
      return;
    }

    //workaround for windows drag&drop bugs
  #ifdef WIN32
    if(path[0]=='/')
      path=path.right(path.length()-1);
  #endif

    fileOpenRecent(path);
  }
  else {
    if(e->source()==this)
      return;
    if(!project)
      return;
    if(!project->machine)
      return;

  wscroll->getDrawArea()->getSelection()->deselectAll(project->machine);
  data=QString(mm->data("text/qfsm-objects"));

  if (edit->paste(wscroll->getDrawArea()->getSelection(), project, project->machine, data))
  {
    emit objectsPasted();
    project->setChanged();
  }

  int count = wscroll->getDrawArea()->getSelection()->count();
  if (count==1)
    statusbar->message(QString::number(count) + " " + tr("object pasted."), 2000);
  else
    statusbar->message(QString::number(count) + " " + tr("objects pasted."), 2000);

  wscroll->widget()->repaint();
  updateAll();
  }

//  data=QString(mm->data("text/qfsm-objects"));

}




/// Called when a menu item is activated
void MainWindow::menuItemActivated(int )
{
  wscroll->getDrawArea()->resetContext();
}

/// Called when the edit menu is about to show
void MainWindow::editMenuAboutToShow()
{
  wscroll->getDrawArea()->resetContext();
}



/**
 * Sets the current mode and updates the menus.
 */
void MainWindow::setMode(int m)
{
  doc_status.setMode(m);
  
  switch (m)
  {
    case DocStatus::Select:
      menu_view->setItemChecked(id_select, TRUE);
      menu_view->setItemChecked(id_pan, FALSE);
      menu_view->setItemChecked(id_newstate, FALSE);
      menu_view->setItemChecked(id_newtrans, FALSE);
      menu_view->setItemChecked(id_zoom, FALSE);
      menu_view->setItemChecked(id_machinesim, FALSE);
      tbselect->setOn(TRUE);
      tbpan->setOn(FALSE);
      tbzoom->setOn(FALSE);
      tbstatenew->setOn(FALSE);
      tbtransnew->setOn(FALSE);
      tbmachinesim->setOn(FALSE);
      break;
    case DocStatus::Pan:
      menu_view->setItemChecked(id_select, FALSE);
      menu_view->setItemChecked(id_pan, TRUE);
      menu_view->setItemChecked(id_newstate, FALSE);
      menu_view->setItemChecked(id_newtrans, FALSE);
      menu_view->setItemChecked(id_zoom, FALSE);
      menu_view->setItemChecked(id_machinesim, FALSE);
      tbselect->setOn(FALSE);
      tbpan->setOn(TRUE);
      tbzoom->setOn(FALSE);
      tbstatenew->setOn(FALSE);
      tbtransnew->setOn(FALSE);
      tbmachinesim->setOn(FALSE);
      break;
    case DocStatus::NewState:
      menu_view->setItemChecked(id_select, FALSE);
      menu_view->setItemChecked(id_pan, FALSE);
      menu_view->setItemChecked(id_newstate, TRUE);
      menu_view->setItemChecked(id_newtrans, FALSE);
      menu_view->setItemChecked(id_zoom, FALSE);
      menu_view->setItemChecked(id_machinesim, FALSE);
      tbselect->setOn(FALSE);
      tbpan->setOn(FALSE);
      tbzoom->setOn(FALSE);
      tbstatenew->setOn(TRUE);
      tbtransnew->setOn(FALSE);
      tbmachinesim->setOn(FALSE);
      break;
    case DocStatus::NewTransition:
      menu_view->setItemChecked(id_select, FALSE);
      menu_view->setItemChecked(id_pan, FALSE);
      menu_view->setItemChecked(id_newstate, FALSE);
      menu_view->setItemChecked(id_newtrans, TRUE);
      menu_view->setItemChecked(id_zoom, FALSE);
      menu_view->setItemChecked(id_machinesim, FALSE);
      tbselect->setOn(FALSE);
      tbpan->setOn(FALSE);
      tbzoom->setOn(FALSE);
      tbstatenew->setOn(FALSE);
      tbtransnew->setOn(TRUE);
      tbmachinesim->setOn(FALSE);
      break;
    case DocStatus::Zooming:
      menu_view->setItemChecked(id_select, FALSE);
      menu_view->setItemChecked(id_pan, FALSE);
      menu_view->setItemChecked(id_newstate, FALSE);
      menu_view->setItemChecked(id_newtrans, FALSE);
      menu_view->setItemChecked(id_zoom, TRUE);
      menu_view->setItemChecked(id_machinesim, FALSE);
      tbselect->setOn(FALSE);
      tbpan->setOn(FALSE);
      tbzoom->setOn(TRUE);
      tbstatenew->setOn(FALSE);
      tbtransnew->setOn(FALSE);
      tbmachinesim->setOn(FALSE);
      break;
    case DocStatus::Simulating:
      menu_view->setItemChecked(id_select, FALSE);
      menu_view->setItemChecked(id_pan, FALSE);
      menu_view->setItemChecked(id_newstate, FALSE);
      menu_view->setItemChecked(id_newtrans, FALSE);
      menu_view->setItemChecked(id_zoom, FALSE);
      menu_view->setItemChecked(id_machinesim, TRUE);
      tbselect->setOn(FALSE);
      tbpan->setOn(FALSE);
      tbzoom->setOn(FALSE);
      tbstatenew->setOn(FALSE);
      tbtransnew->setOn(FALSE);
      tbmachinesim->setOn(TRUE);
      break;
  }
  switch (m)
  {
    case DocStatus::Pan:
      wscroll->viewport()->setCursor(Qt::SizeAllCursor);
      break;
    case DocStatus::NewState:
    case DocStatus::NewTransition:
      wscroll->viewport()->setCursor(Qt::CrossCursor);
      break;
    case DocStatus::Zooming:
      wscroll->viewport()->setCursor(*zoomCursor);
      break;
    default:
      wscroll->viewport()->setCursor(Qt::ArrowCursor);
      break;
  }
      
}

/// Repaints the scroll view
void MainWindow::repaintViewport()
{
  wscroll->widget()->repaint();
}


/// Updates all menus.
void MainWindow::updateMenuBar()
{
  int numstates, numtrans;

  menu_file->setItemEnabled(id_import, TRUE);
  menu_import->setItemEnabled(id_import_graphviz, TRUE);

  if (project)
  {
    menu_file->setItemEnabled(id_save, TRUE);
    menu_file->setItemEnabled(id_saveas, TRUE);
    menu_file->setItemEnabled(id_print, TRUE);
    menu_file->setItemEnabled(id_export, TRUE);
    menu_file->setItemEnabled(id_close, TRUE);
    menu_edit->setItemEnabled(id_selectall, TRUE);
    menu_edit->setItemEnabled(id_deselectall, TRUE);
    menu_state->setItemEnabled(id_newstate, TRUE);
    menu_trans->setItemEnabled(id_newtrans, TRUE);
    if (project->machine && project->machine->getType()==Ascii)
      menu_export->setItemEnabled(id_export_ragel, TRUE);
    else
      menu_export->setItemEnabled(id_export_ragel, FALSE);
    if (project->machine && project->machine->getType()==Text)
    {
      menu_export->setItemEnabled(id_export_ahdl, FALSE);
      menu_export->setItemEnabled(id_export_vhdl, FALSE);
      menu_export->setItemEnabled(id_export_verilog, FALSE);
      menu_export->setItemEnabled(id_export_kiss, FALSE);
      menu_export->setItemEnabled(id_export_vvvv, TRUE);
      menu_export->setItemEnabled(id_export_scxml, TRUE);
      menu_export->setItemEnabled(id_export_smc, TRUE);
      menu_view->setItemEnabled(id_viewstateenc, FALSE);
      menu_view->setItemEnabled(id_viewmoore, FALSE);
      tbmachinesim->setEnabled(FALSE);
    }
    else
    {
      menu_export->setItemEnabled(id_export_ahdl, TRUE);
      menu_export->setItemEnabled(id_export_vhdl, TRUE);
      menu_export->setItemEnabled(id_export_verilog, TRUE);
      menu_export->setItemEnabled(id_export_kiss, TRUE);
      menu_export->setItemEnabled(id_export_vvvv, FALSE);
      menu_export->setItemEnabled(id_export_scxml, FALSE);
      menu_export->setItemEnabled(id_export_smc, FALSE);
      menu_view->setItemEnabled(id_viewstateenc, TRUE);
      menu_view->setItemEnabled(id_viewmoore, TRUE);
      tbmachinesim->setEnabled(TRUE);
    }
    menu_view->setItemEnabled(id_viewmealyin, TRUE);
    menu_view->setItemEnabled(id_viewmealyout, TRUE);
    menu_view->setItemEnabled(id_viewgrid, TRUE);
    menu_view->setItemEnabled(id_ioview,TRUE);
    menu_view->setItemEnabled(id_viewshadows, TRUE);
    menu_view->setItemEnabled(id_zoom, TRUE);
    menu_view->setItemEnabled(id_zoomin, TRUE);
    menu_view->setItemEnabled(id_zoomout, TRUE);
    menu_view->setItemEnabled(id_zoom100, TRUE);
    menu_edit->setItemEnabled(id_select, TRUE);
    menu_view->setItemEnabled(id_pan, TRUE);
    menu_machine->setItemEnabled(id_machineedit, TRUE);
    menu_machine->setItemEnabled(id_correctcodes, TRUE);
    menu_machine->setItemEnabled(id_machineicheck, TRUE);
    tbsave->setEnabled(TRUE);
    tbprint->setEnabled(TRUE);
    tbselect->setEnabled(TRUE);
    tbpan->setEnabled(TRUE);
    tbzoom->setEnabled(TRUE);
    tbzoomin->setEnabled(TRUE);
    tbzoomout->setEnabled(TRUE);
    tbstatenew->setEnabled(TRUE);
    tbtransnew->setEnabled(TRUE);
  }
  else
  {
    menu_file->setItemEnabled(id_save, FALSE);
    menu_file->setItemEnabled(id_saveas, FALSE);
    menu_file->setItemEnabled(id_print, FALSE);
    menu_file->setItemEnabled(id_export, FALSE);
    menu_file->setItemEnabled(id_close, FALSE);
    menu_edit->setItemEnabled(id_selectall, FALSE);
    menu_edit->setItemEnabled(id_deselectall, FALSE);
    menu_state->setItemEnabled(id_newstate, FALSE);
    menu_trans->setItemEnabled(id_newtrans, FALSE);
    menu_view->setItemEnabled(id_viewstateenc, FALSE);
    menu_view->setItemEnabled(id_viewmoore, FALSE);
    menu_view->setItemEnabled(id_viewmealyin, FALSE);
    menu_view->setItemEnabled(id_viewmealyout, FALSE);
    menu_view->setItemEnabled(id_viewgrid, FALSE);
    menu_view->setItemEnabled(id_viewshadows, FALSE);
    menu_view->setItemEnabled(id_ioview,FALSE);
    menu_view->setItemEnabled(id_zoom, FALSE);
    menu_view->setItemEnabled(id_zoomin, FALSE);
    menu_view->setItemEnabled(id_zoomout, FALSE);
    menu_view->setItemEnabled(id_zoom100, FALSE);
    menu_edit->setItemEnabled(id_select, FALSE);
    menu_view->setItemEnabled(id_pan, FALSE);
    menu_machine->setItemEnabled(id_machineedit, FALSE);
    menu_machine->setItemEnabled(id_correctcodes, FALSE);
    menu_machine->setItemEnabled(id_machineicheck, FALSE);
    tbsave->setEnabled(FALSE);
    tbprint->setEnabled(FALSE);
    tbselect->setEnabled(FALSE);
    tbpan->setEnabled(FALSE);
    tbzoom->setEnabled(FALSE);
    tbzoomin->setEnabled(FALSE);
    tbzoomout->setEnabled(FALSE);
    tbstatenew->setEnabled(FALSE);
    tbtransnew->setEnabled(FALSE);
    tbmachinesim->setEnabled(FALSE);
  }

  numtrans = wscroll->getDrawArea()->getSelection()->countTransitions();
  numstates = wscroll->getDrawArea()->getSelection()->countStates();

  if (project && project->machine && project->machine->getType()!=Text 
      && project->machine->getNumStates()>0)
  {
    menu_machine->setItemEnabled(id_machinesim, TRUE);
    tbmachinesim->setEnabled(TRUE);
  }
  else
  {
    menu_machine->setItemEnabled(id_machinesim, FALSE);
    tbmachinesim->setEnabled(FALSE);
  }

  if (numtrans)
  {
    menu_trans->setItemEnabled(id_trans_straight, TRUE);
    tbtransstraighten->setEnabled(TRUE);
    cmenu_trans->setItemEnabled(id_cedittrans, TRUE);
    cmenu_trans->setItemEnabled(id_ctrans_straight, TRUE);
  }
  else
  {
    menu_trans->setItemEnabled(id_trans_straight, FALSE);
    tbtransstraighten->setEnabled(FALSE);
    cmenu_trans->setItemEnabled(id_cedittrans, FALSE);
    cmenu_trans->setItemEnabled(id_ctrans_straight, FALSE);
  }

  if (numstates>0)
  {
    menu_state->setItemEnabled(id_setend, TRUE);
    menu_state->setItemEnabled(id_csetend, TRUE);
  }
  else
  {
    menu_state->setItemEnabled(id_setend, FALSE);
    menu_state->setItemEnabled(id_csetend, FALSE);
  }
  if (numstates==1)
  {
    menu_state->setItemEnabled(id_setinitial, TRUE);
    menu_state->setItemEnabled(id_editstate, TRUE);
  }
  else
  {
    menu_state->setItemEnabled(id_setinitial, FALSE);
    menu_state->setItemEnabled(id_editstate, FALSE);
  }

  if (numtrans==1)
  {
    menu_trans->setItemEnabled(id_edittrans, TRUE);
  }
  else
  {
    menu_trans->setItemEnabled(id_edittrans, FALSE);
  }

  if (numstates + numtrans > 0)
  {
    menu_edit->setItemEnabled(id_delete, TRUE);
    menu_edit->setItemEnabled(id_cut, TRUE);
    menu_edit->setItemEnabled(id_copy, TRUE);
    cmenu_state->setItemEnabled(id_csdelete, TRUE);
    cmenu_state->setItemEnabled(id_cscut, TRUE);
    cmenu_state->setItemEnabled(id_cscopy, TRUE);
    cmenu_trans->setItemEnabled(id_ctdelete, TRUE);
    cmenu_trans->setItemEnabled(id_ctcut, TRUE);
    cmenu_trans->setItemEnabled(id_ctcopy, TRUE);
    tbcut->setEnabled(TRUE);
    tbcopy->setEnabled(TRUE);
  }
  else
  {
    menu_edit->setItemEnabled(id_delete, FALSE);
    menu_edit->setItemEnabled(id_cut, FALSE);
    menu_edit->setItemEnabled(id_copy, FALSE);
    cmenu_state->setItemEnabled(id_csdelete, FALSE);
    cmenu_state->setItemEnabled(id_cscut, FALSE);
    cmenu_state->setItemEnabled(id_cscopy, FALSE);
    cmenu_trans->setItemEnabled(id_ctdelete, FALSE);
    cmenu_trans->setItemEnabled(id_ctcut, FALSE);
    cmenu_trans->setItemEnabled(id_ctcopy, FALSE);
    tbcut->setEnabled(FALSE);
    tbcopy->setEnabled(FALSE);
  }

//  updatePaste();

  if (doc_options.getViewStateEncoding())
    menu_view->setItemChecked(id_viewstateenc, TRUE);
  else
    menu_view->setItemChecked(id_viewstateenc, FALSE);

  if (doc_options.getViewMoore())
    menu_view->setItemChecked(id_viewmoore, TRUE);
  else
    menu_view->setItemChecked(id_viewmoore, FALSE);

  if (doc_options.getViewMealyIn())
    menu_view->setItemChecked(id_viewmealyin, TRUE);
  else
    menu_view->setItemChecked(id_viewmealyin, FALSE);
    
  if (doc_options.getViewMealyOut())
    menu_view->setItemChecked(id_viewmealyout, TRUE);
  else
    menu_view->setItemChecked(id_viewmealyout, FALSE);
    
  if (doc_options.getViewGrid())
    menu_view->setItemChecked(id_viewgrid, TRUE);
  else
    menu_view->setItemChecked(id_viewgrid, FALSE);
  
  if (doc_options.getViewIOView())
    menu_view->setItemChecked(id_ioview,TRUE);
  else 
    menu_view->setItemChecked(id_ioview,FALSE);
    
  if (doc_options.getStateShadows())
    menu_view->setItemChecked(id_viewshadows, TRUE);
  else
    menu_view->setItemChecked(id_viewshadows, FALSE);
    
  if (project && !project->getUndoBuffer()->isEmpty())
  {
    menu_edit->setItemEnabled(id_undo, TRUE);
    cmenu_state->setItemEnabled(id_csundo, TRUE);
    cmenu_trans->setItemEnabled(id_ctundo, TRUE);
    tbundo->setEnabled(TRUE);
  }
  else
  {
    menu_edit->setItemEnabled(id_undo, FALSE);
    cmenu_state->setItemEnabled(id_csundo, FALSE);
    cmenu_trans->setItemEnabled(id_ctundo, FALSE);
    tbundo->setEnabled(FALSE);
  }
    
  if (doc_status.getMode()==DocStatus::Simulating)
  {
    menu_edit->setItemEnabled(id_undo, FALSE);
    cmenu_state->setItemEnabled(id_csundo, FALSE);
    cmenu_trans->setItemEnabled(id_ctundo, FALSE);
    menu_edit->setItemEnabled(id_select, FALSE);
    menu_view->setItemEnabled(id_pan, FALSE);
    menu_edit->setItemEnabled(id_cut, FALSE);
    menu_edit->setItemEnabled(id_copy, FALSE);
    menu_edit->setItemEnabled(id_paste, FALSE);
    menu_edit->setItemEnabled(id_delete, FALSE);
    cmenu_state->setItemEnabled(id_cscut, FALSE);
    cmenu_state->setItemEnabled(id_cscopy, FALSE);
    cmenu_state->setItemEnabled(id_csdelete, FALSE);
    cmenu_trans->setItemEnabled(id_ctcut, FALSE);
    cmenu_trans->setItemEnabled(id_ctcopy, FALSE);
    cmenu_trans->setItemEnabled(id_ctdelete, FALSE);
    menu_edit->setItemEnabled(id_selectall, FALSE);
    menu_edit->setItemEnabled(id_deselectall, FALSE);
    menu_view->setItemEnabled(id_zoom, FALSE);
    menu_machine->setItemEnabled(id_machineedit, FALSE);
    menu_state->setItemEnabled(id_editstate, FALSE);
    menu_state->setItemEnabled(id_setinitial, FALSE);
    menu_state->setItemEnabled(id_ceditstate, FALSE);
    menu_state->setItemEnabled(id_csetinitial, FALSE);
    menu_state->setItemEnabled(id_setend, FALSE);
    menu_state->setItemEnabled(id_newstate, FALSE);
    menu_trans->setItemEnabled(id_newtrans, FALSE);
    menu_trans->setItemEnabled(id_edittrans, FALSE);
    menu_trans->setItemEnabled(id_trans_straight, FALSE);
    cmenu_trans->setItemEnabled(id_cedittrans, FALSE);
    cmenu_trans->setItemEnabled(id_ctrans_straight, FALSE);
    tbselect->setEnabled(FALSE);
    tbpan->setEnabled(FALSE);
    tbzoom->setEnabled(FALSE);
    tbundo->setEnabled(FALSE);
    tbcut->setEnabled(FALSE);
    tbcopy->setEnabled(FALSE);
    tbstatenew->setEnabled(FALSE);
    tbtransnew->setEnabled(FALSE);
    tbtransstraighten->setEnabled(FALSE);
  }  
}

/// Updates the paste tool button and menu item
void MainWindow::updatePaste()
{
  if (project && qApp->clipboard()->data()->provides("text/qfsm-objects"))
  {
    menu_edit->setItemEnabled(id_paste, TRUE);
    tbpaste->setEnabled(TRUE);
  }
  else
  {
    menu_edit->setItemEnabled(id_paste, FALSE);
    tbpaste->setEnabled(FALSE);
  }
}


/// Updates the title bar.
void MainWindow::updateTitleBar()
{
  QString s;
  s = "Qfsm";
  if (project)
  {
    QString f;
    f = fileio->getActFilePath();
    if (f!=QString::null)
    {
      QFileInfo fi(f);
      f = fi.fileName();
      s = "Qfsm - " + f;
      if (project->hasChanged())
        s += " " + tr("(modified)");
    }
  }
  setCaption(s);
}


/// Updates the status bar
void MainWindow::updateStatusBar()
{
  int selected;
  int scale;

  if (project)
  {
    selected = wscroll->getDrawArea()->getSelection()->count();
    scale = int(wscroll->getDrawArea()->getScale()*100+0.5);
  }
  else
  {
    selected = -1;
    scale = -1;
  }

  statusbar->setSelected(selected);
  emit updateStatusZoom(scale);
  
}


/// Updates menu, title bar and status bar
void MainWindow::updateAll()
{
//  updatePaste();
  updateMenuBar();
  updateTitleBar();
  updateStatusBar();
  if (vvvv_export->isVisible())
    updateVVVV();
}


/// Refreshes the MRU file list
void MainWindow::refreshMRU()
{
  int id, index=0;
  menu_mru->clear();
  QStringList list = control->getMRUList();

  fileio->loadMRU(list);
  QStringList::Iterator it;

  for(it = list.begin(); it != list.end(); ++it)
  {
    id = menu_mru->insertItem(*it);
    switch(index)
    {
      case 0: menu_mru->connectItem(id, this, SLOT(fileOpenRecent0())); break;
      case 1: menu_mru->connectItem(id, this, SLOT(fileOpenRecent1())); break;
      case 2: menu_mru->connectItem(id, this, SLOT(fileOpenRecent2())); break;
      case 3: menu_mru->connectItem(id, this, SLOT(fileOpenRecent3())); break;
      case 4: menu_mru->connectItem(id, this, SLOT(fileOpenRecent4())); break;
      case 5: menu_mru->connectItem(id, this, SLOT(fileOpenRecent5())); break;
      case 6: menu_mru->connectItem(id, this, SLOT(fileOpenRecent6())); break;
      case 7: menu_mru->connectItem(id, this, SLOT(fileOpenRecent7())); break;
      case 8: menu_mru->connectItem(id, this, SLOT(fileOpenRecent8())); break;
      case 9: menu_mru->connectItem(id, this, SLOT(fileOpenRecent9())); break;
    }
    index++;
  }
}


/// Shows the context menu for a state
void MainWindow::showContextState()
{
  cmenu_state->popup(QCursor::pos());
}


/// Shows the context menu for a transition 
void MainWindow::showContextTrans()
{
  cmenu_trans->popup(QCursor::pos());
}

/// Shows the context menu for the scrollview
void MainWindow::showContext()
{
  cmenu_sview->popup(QCursor::pos());
}

/// Sends a message @a s to the status bar
void MainWindow::sbMessage(QString s)
{ 
  statusbar->message(s); 
}
 
/// Sends a message @a s for time @a t to the status bar 
void MainWindow::sbMessage(QString s, int t)
{ 
  statusbar->message(s, t); 
}
 
 
 
 
 
 


/// Creates a new file
void MainWindow::fileNew()
{
  int result;
  bool sim=FALSE;

  if (doc_status.getMode()==DocStatus::Simulating)
    sim=TRUE;

  if (project && project->hasChanged())
  {
    switch(mb_changed->exec())
    {
      case QMessageBox::Yes:
        if (!fileSave())
	  return;
        break;
      case QMessageBox::No:
        break;
      case QMessageBox::Cancel:
        return;
	break;
    }
  }
  Project* p = new Project(this);

  result = machinemanager->addMachine(p);
  if (result)
  {
    if (sim)
      simulator->closeDlg();

    if (project)
    {
      delete project;
      project=NULL;
    }
    project = p;
    fileio->setActFilePath(QString::null);

    statusbar->message(project->machine->getName() + " " + tr("created."), 2000);
  }
  else
  {
    return;
  }

  setMode(DocStatus::Select);
  wscroll->getDrawArea()->reset();
  wscroll->widget()->repaint();

  updateAll();
}



/// Opens an existing file.
void MainWindow::fileOpen()
{
  Project* p;

  if (project && project->hasChanged())
  {
    switch(mb_changed->exec())
    {
      case QMessageBox::Yes:
        if (!fileSave())
	  return;
        break;
      case QMessageBox::No:
        break;
      case QMessageBox::Cancel:
        return;
	break;
    }
  }

  /*
  QCursor oldcursor1 = cursor();
  QCursor oldcursor2 = wscroll->viewport()->cursor();
  setCursor(waitCursor);
  wscroll->viewport()->setCursor(waitCursor);
  */
  //qApp->setOverrideCursor(waitCursor);


  p = fileio->openFileXML();
  if (p)
  {
    if (project)
    {
      delete project;
      project=NULL;
    }
    statusbar->message(tr("File")+" "+ fileio->getActFileName() + " " +  tr("loaded."), 2000);
    project = p;
    p->getUndoBuffer()->clear();

    updateAll();
    wscroll->updateBackground();
    wscroll->getDrawArea()->resetState();
    //wscroll->getDrawArea()->updateCanvasSize();
    wscroll->updateSize();
    if (doc_status.getMode()==DocStatus::Simulating)
    {
      if (!simulator->startSimulation(project->machine))
        setMode(DocStatus::Select);
    }
    else
      wscroll->widget()->repaint();
  
//    menu_mru->insertItem(fileio->getActFile(), -1, 0);
      control->addMRUEntry(fileio->getActFilePath());
      fileio->saveMRU(control->getMRUList());

//      statusbar->message(tr("File %1 opened").arg(fileio->getActFile()), 3000);
  }
  else if (!fileio->getActFilePath().isNull())
  {
    Error::info(tr("File %1 could not be opened").arg(fileio->getActFilePath()));
    statusbar->clear();
  }
  /*
  setCursor(oldcursor1);
  wscroll->viewport()->setCursor(oldcursor2);
  */
  //qApp->restoreOverrideCursor();
  
}


/// Opens a file from the MRU file list with the name @a fileName
void MainWindow::fileOpenRecent(QString fileName)
{
  Project* p;

  if (project && project->hasChanged())
  {
    switch(mb_changed->exec())
    {
      case QMessageBox::Yes:
        if (!fileSave())
	  return;
        break;
      case QMessageBox::No:
        break;
      case QMessageBox::Cancel:
        return;
	break;
    }
  }

  /*
  QCursor oldcursor1 = cursor();
  QCursor oldcursor2 = wscroll->viewport()->cursor();
  setCursor(waitCursor);
  wscroll->viewport()->setCursor(waitCursor);
  */

  p = fileio->openFileXML(fileName);
  if (p)
  {
    if (project)
    {
      delete project;
      project=NULL;
    }
    statusbar->message(tr("File")+" "+ fileio->getActFileName() + " " +  tr("loaded."), 2000);
    project = p;
    p->getUndoBuffer()->clear();

    updateAll();
    wscroll->updateBackground();
    wscroll->getDrawArea()->resetState();
    //wscroll->getDrawArea()->updateCanvasSize();
    wscroll->updateSize();
    if (doc_status.getMode()==DocStatus::Simulating)
    {
      if (!simulator->startSimulation(project->machine))
        setMode(DocStatus::Select);
    }
    else
      wscroll->widget()->repaint();
  
//    menu_mru->insertItem(fileio->getActFile(), -1, 0);
      control->addMRUEntry(fileio->getActFilePath());
      fileio->saveMRU(control->getMRUList());
  }
  else
  {
    Error::info(tr("File %1 could not be opened").arg(fileName));
    statusbar->clear();
    control->removeMRUEntry(fileName);
    fileio->saveMRU(control->getMRUList());
  }
  /*
  setCursor(oldcursor1);
  wscroll->viewport()->setCursor(oldcursor2);
  */
}

/// Opens the file in the MRU list entry 0
void MainWindow::fileOpenRecent0()
{
  QStringList list = control->getMRUList();
  if (list.count()>0)
    fileOpenRecent(list[0]);
}

/// Opens the file in the MRU list entry 1
void MainWindow::fileOpenRecent1()
{
  QStringList list = control->getMRUList();
  if (list.count()>1)
    fileOpenRecent(list[1]);
}

/// Opens the file in the MRU list entry 2
void MainWindow::fileOpenRecent2()
{
  QStringList list = control->getMRUList();
  if (list.count()>2)
    fileOpenRecent(list[2]);
}

/// Opens the file in the MRU list entry 3
void MainWindow::fileOpenRecent3()
{
  QStringList list = control->getMRUList();
  if (list.count()>3)
    fileOpenRecent(list[3]);
}

/// Opens the file in the MRU list entry 4
void MainWindow::fileOpenRecent4()
{
  QStringList list = control->getMRUList();
  if (list.count()>4)
    fileOpenRecent(list[4]);
}

/// Opens the file in the MRU list entry 5
void MainWindow::fileOpenRecent5()
{
  QStringList list = control->getMRUList();
  if (list.count()>5)
    fileOpenRecent(list[5]);
}

/// Opens the file in the MRU list entry 6
void MainWindow::fileOpenRecent6()
{
  QStringList list = control->getMRUList();
  if (list.count()>6)
    fileOpenRecent(list[6]);
}

/// Opens the file in the MRU list entry 7
void MainWindow::fileOpenRecent7()
{
  QStringList list = control->getMRUList();
  if (list.count()>7)
    fileOpenRecent(list[7]);
}

/// Opens the file in the MRU list entry 8
void MainWindow::fileOpenRecent8()
{
  QStringList list = control->getMRUList();
  if (list.count()>8)
    fileOpenRecent(list[8]);
}

/// Opens the file in the MRU list entry 9
void MainWindow::fileOpenRecent9()
{
  QStringList list = control->getMRUList();
  if (list.count()>9)
    fileOpenRecent(list[9]);
}

/// Saves the current file.
bool MainWindow::fileSave()
{
  if (project)
  {
    
    bool result;
    bool saveas=(fileio->getActFileName() == QString::null);
    QCursor oldcursor1 = cursor();
    QCursor oldcursor2 = wscroll->viewport()->cursor();
    setCursor(Qt::waitCursor);
    wscroll->viewport()->setCursor(Qt::waitCursor);

    result = fileio->saveFile(project);

    if (result)
    {
      statusbar->message(tr("File")+" "+ fileio->getActFileName() + " " +  tr("saved."), 2000);
      project->getUndoBuffer()->clear();
      if (saveas)
      {
	control->addMRUEntry(fileio->getActFilePath());
	fileio->saveMRU(control->getMRUList());
      }
    }

    updateAll();

    setCursor(oldcursor1);
    wscroll->viewport()->setCursor(oldcursor2);
    

    return result;
  }

  return FALSE;
}

/// Saves the current file with a new name.
bool MainWindow::fileSaveAs()
{
  if (project)
  {
    bool result;
    QCursor oldcursor1 = cursor();
    QCursor oldcursor2 = wscroll->viewport()->cursor();
    setCursor(Qt::waitCursor);
    wscroll->viewport()->setCursor(Qt::waitCursor);
    
    result =  fileio->saveFileAs(project);

    if (result)
    {
      statusbar->message(tr("File")+" "+ fileio->getActFileName() + " " +  tr("saved."), 2000);
      project->getUndoBuffer()->clear();
      control->addMRUEntry(fileio->getActFilePath());
      fileio->saveMRU(control->getMRUList());
    }

    updateAll();

    setCursor(oldcursor1);
    wscroll->viewport()->setCursor(oldcursor2);

    return result;
  }

  return FALSE;
}


/// Imports a graphviz file
void MainWindow::fileImportGraphviz()
{
  Project* p;

  if (project && project->hasChanged())
  {
    switch(mb_changed->exec())
    {
      case QMessageBox::Yes:
        if (!fileSave())
	  return;
        break;
      case QMessageBox::No:
        break;
      case QMessageBox::Cancel:
        return;
	break;
    }
  }


  ImportGraphviz* imp = new ImportGraphviz(&doc_options);
  p = fileio->importFile(imp, wscroll);
  delete imp;

  if (p)
  {
    if (project)
    {
      delete project;
      project=NULL;
    }
    statusbar->message(tr("File")+" "+ fileio->getActFileName() + " " +  tr("imported."), 2000);
    project = p;
    p->getUndoBuffer()->clear();

    updateAll();
    wscroll->updateBackground();
    wscroll->getDrawArea()->resetState();
    //wscroll->getDrawArea()->updateCanvasSize();
    if (doc_status.getMode()==DocStatus::Simulating)
    {
      if (!simulator->startSimulation(project->machine))
        setMode(DocStatus::Select);
    }
    else
    {
      //wscroll->widget()->repaint();
      //wscroll->getDrawArea()->zoomReset();
      wscroll->updateSize();

    }
  }
  else if (!fileio->getActImportFilePath().isNull())
  {
    Error::info(tr("File %1 could not be opened").arg(fileio->getActFileName()));
    statusbar->clear();
  }
}


/// Exports the current diagram to an EPS file
bool MainWindow::fileExportEPS()
{
  if (project)
  {
    bool result;

    project->machine->updateDefaultTransitions();
    
    ExportEPS* exp = new ExportEPS(&doc_options);
    result = fileio->exportFile(project, exp, wscroll);
    delete exp;

    if (result)
      statusbar->message(tr("File")+" "+ fileio->getActExportFileName() + " " +  
	  tr("exported."), 2000);

    updateAll();
    return result;
  }
  return FALSE;
}


//
/// Exports the current diagram to a SVG file
bool MainWindow::fileExportSVG()
{
  if (project)
  {
    bool result;

    project->machine->updateDefaultTransitions();
    
    ExportSVG* exp = new ExportSVG(&doc_options);
    result = fileio->exportFile(project, exp, wscroll);
    delete exp;

    if (result)
      statusbar->message(tr("File")+" "+ fileio->getActExportFileName() + " " +  
	  tr("exported."), 2000);

    updateAll();
    return result;
  }
  return FALSE;
}

/// Exports the current diagram to a PNG file
bool MainWindow::fileExportPNG()
{
  if (project)
  {
    bool result;

    project->machine->updateDefaultTransitions();

    ExportPNG* exp = new ExportPNG(&doc_options);
    result = fileio->exportFile(project, exp, wscroll);
    delete exp;

    if (result)
      statusbar->message(tr("File")+" "+ fileio->getActExportFileName() + " " +  
          tr("exported."), 2000);

    updateAll();
    return result;
  }
  return FALSE;
}

/// Exports the current file to an AHDL tdf file
bool MainWindow::fileExportAHDL()
{
  if (project)
  {
    bool result;

    switch(ahdl_export->exec())
    {
      case QDialog::Accepted:
	doc_options.applyOptions(this);
	break;
      case QDialog::Rejected:
	return TRUE;
	break;
    }

    project->machine->updateDefaultTransitions();
    ExportAHDL* exp = new ExportAHDL(&doc_options);
    result = fileio->exportFile(project, exp);
    delete exp;

    if (result)
      statusbar->message(tr("File")+" "+ fileio->getActExportFileName() + " " +  
	  tr("exported."), 2000);

    updateAll();
    return result;
  }
  return FALSE;
}

/// Exports the current file to a VHDL file
bool MainWindow::fileExportVHDL()
{
  if (project)
  {
    bool result;
	QString errorMessage;
	QStringList invalidNames;

    vhdl_export->init(&doc_options, project->machine);
    switch(vhdl_export->exec())
    {
      case QDialog::Accepted:
	doc_options.applyOptions(this);
	break;
      case QDialog::Rejected:
	return TRUE;
	break;
    }

    project->machine->updateDefaultTransitions();
    ExportVHDL* exp = new ExportVHDL(&doc_options);
	  
    result= exp->checkMachineNames(project->machine,&doc_options,&invalidNames);
	  
	  if(!result)
	  {
		  errorMessage=tr("Export of file %1 failed!").arg(fileio->getActExportFileName())+"\n\n"+
				           tr("The following identifiers do not match the VHDL syntax:")+"\n";

		  errorMessage+=invalidNames.join("\n");
		  
		  Error::warningOk(errorMessage);

		  statusbar->message(tr("Export of file")+" "+ fileio->getActExportFileName() + " " +  
				  tr("failed."), 2000);
		  delete exp;
		  return FALSE;
	  }

    if (!project || !exp)
      return FALSE;

    if (!exp->validateMachine(project->machine))
      return FALSE;


      QString path_entity=vhdl_export->getEntityPath();
      QString path_arch=vhdl_export->getArchitecturePath();

      QFile ftmp(path_entity);
      if (ftmp.exists())
      {
        if (Error::warningOkCancel(tr("File %1 exists. Do you want to overwrite it?").arg(path_entity))!=QMessageBox::Ok)
        {
          delete exp;
          return false;
        }
      }



      ofstream fout_entity(path_entity);

      if(!fout_entity)
      {
        Error::warningOk(tr("Unable to write file %1!").arg(path_entity));
        delete exp;
        return false;
      }

      if(doc_options.getVHDLSepFiles())
      {
        ftmp.setFileName(path_arch);
        if (ftmp.exists())
        {
          if (Error::warningOkCancel(tr("File %1 exists. Do you want to overwrite it?").arg(path_arch))!=QMessageBox::Ok)
          {
            delete exp;
            return false;
          }
        }

        ofstream fout_architecture(path_arch);
        if(!fout_architecture)
        {
          Error::warningOk(tr("Unable to write file %1!").arg(path_arch));
          delete exp;
          return false;
        }
        exp->init(&fout_entity,&fout_architecture,project->machine,path_entity,NULL);
        exp->doExport();
      }
      else
      {
        exp->init(&fout_entity,&fout_entity,project->machine,path_entity,NULL);
        exp->doExport();
      }



    //  result = fileio->exportFile(project, exp);
      delete exp;


    if (result)
      statusbar->message(tr("File")+" "+ fileio->getActExportFileName() + " " +  
	  tr("exported."), 2000);

    updateAll();
    return result;
  }
  return FALSE;
}


/// Exports IO Description
bool MainWindow::fileExportIODescription()
{
  bool result;
  if (project)
  {

    project->machine->updateDefaultTransitions();
    ExportIODescription* exp = new ExportIODescription(&doc_options);
    result = fileio->exportFile(project, exp);
    delete exp;

    if (result)
      statusbar->message(tr("File")+" "+ fileio->getActExportFileName() + " " +  
          tr("exported."), 2000);

    updateAll();
    return result;
  }
  return FALSE;
}

/// Exports VHDL Testbench
bool MainWindow::fileExportTestbench()
{
  if (project)
  {
    bool result;
    int dialog_result;
    QString errorMessage;
    QStringList invalidNames;
    Error err;
    QString base_dir_name,testbench_dir_name,testvector_dir_name,package_dir_name,logfile_dir_name;
    QDir testbenchDir,testvectorDir,packageDir,logfileDir;
    std::ofstream *testbench_out,*testvector_out,*package_out;

    testbench_export->init(&doc_options, project->machine);

    while(true)
    {
      dialog_result=testbench_export->exec();

      if(dialog_result==QDialog::Accepted)
      {
        doc_options.applyOptions(this);

        base_dir_name=doc_options.getTestbenchBaseDirectory();
        testbench_dir_name=doc_options.getTestbenchVHDLPath().left(doc_options.getTestbenchVHDLPath().lastIndexOf("/")+1);
        testvector_dir_name=doc_options.getTestvectorASCIIPath().left(doc_options.getTestvectorASCIIPath().lastIndexOf("/")+1);
        package_dir_name=doc_options.getTestpackageVHDLPath().left(doc_options.getTestpackageVHDLPath().lastIndexOf("/")+1);
        logfile_dir_name=doc_options.getTestbenchLogfilePath().left(doc_options.getTestbenchLogfilePath().lastIndexOf("/")+1);


        testbenchDir.setPath(base_dir_name+testbench_dir_name);
        testvectorDir.setPath(base_dir_name+testvector_dir_name);
        packageDir.setPath(base_dir_name+package_dir_name);
        logfileDir.setPath(base_dir_name+logfile_dir_name);

        if(project->machine->getNumOutputs()>0)
        {
          QMessageBox::critical(this,"qfsm",tr("The current version does not create a testbench for a Mealy-type FSM!"),QMessageBox::Ok);
          return false;
        }

        if(!testbenchDir.exists())
        {

          dialog_result=QMessageBox::question(NULL,"qfsm",tr("%1 does not exist\n\nCreate it?").arg(base_dir_name+testbench_dir_name),QMessageBox::No|QMessageBox::Yes,QMessageBox::No);

          if(dialog_result==QMessageBox::No)
            continue;

          result=testbenchDir.mkpath(base_dir_name+testbench_dir_name);

          if(!result)
          {
            QMessageBox::critical(NULL,"qfsm",tr("Error creating directory %1!").arg(base_dir_name+testbench_dir_name),QMessageBox::Ok,QMessageBox::Ok);
            continue;
          }
        }

        if(!testvectorDir.exists())
        {

          dialog_result=QMessageBox::question(NULL,"qfsm",tr("%1 does not exist\n\nCreate it?").arg(base_dir_name+testvector_dir_name),QMessageBox::No|QMessageBox::Yes,QMessageBox::No);

          if(dialog_result==QMessageBox::No)
            continue;

          result=testvectorDir.mkpath(base_dir_name+testvector_dir_name);

          if(!result)
          {
            QMessageBox::critical(NULL,"qfsm",tr("Error creating directory %1!").arg(base_dir_name+testvector_dir_name),QMessageBox::Ok,QMessageBox::Ok);
            continue;
          }
        }

        if(!packageDir.exists())
        {

          dialog_result=QMessageBox::question(NULL,"qfsm",tr("%1 does not exist\n\nCreate it?").arg(base_dir_name+package_dir_name),QMessageBox::No|QMessageBox::Yes,QMessageBox::No);

          if(dialog_result==QMessageBox::No)
            continue;

          result=packageDir.mkpath(base_dir_name+package_dir_name);

          if(!result)
          {
            QMessageBox::critical(NULL,"qfsm",tr("Error creating directory %1!").arg(base_dir_name+package_dir_name),QMessageBox::Ok,QMessageBox::Ok);
            continue;
          }
        }

        if(!logfileDir.exists())
        {

          dialog_result=QMessageBox::question(NULL,"qfsm",tr("%1 does not exist\n\nCreate it?").arg(base_dir_name+logfile_dir_name),QMessageBox::No|QMessageBox::Yes,QMessageBox::No);

          if(dialog_result==QMessageBox::No)
            continue;

          result=logfileDir.mkpath(base_dir_name+logfile_dir_name);

          if(!result)
          {
            QMessageBox::critical(NULL,"qfsm",tr("Error creating directory %1!").arg(base_dir_name+logfile_dir_name),QMessageBox::Ok,QMessageBox::Ok);
            continue;
          }
        }

        QFile ftmp(base_dir_name+doc_options.getTestbenchVHDLPath());
        if (ftmp.exists())
        {
          if (Error::warningOkCancel(tr("File %1 exists. Do you want to overwrite it?").arg(doc_options.getTestbenchVHDLPath()))!=QMessageBox::Ok)
            return false;
        }
        ftmp.setFileName(base_dir_name+doc_options.getTestvectorASCIIPath());
        if (ftmp.exists())
        {
          if (Error::warningOkCancel(tr("File %1 exists. Do you want to overwrite it?").arg(doc_options.getTestvectorASCIIPath()))!=QMessageBox::Ok)
            return false;
        }
        ftmp.setFileName(base_dir_name+doc_options.getTestpackageVHDLPath());
        if (ftmp.exists())
        {
          if (Error::warningOkCancel(tr("File %1 exists. Do you want to overwrite it?").arg(doc_options.getTestpackageVHDLPath()))!=QMessageBox::Ok)
            return false;
        }


        testbench_out = new  std::ofstream((base_dir_name+doc_options.getTestbenchVHDLPath()).toLatin1().data());
        testvector_out = new std::ofstream((base_dir_name+doc_options.getTestvectorASCIIPath()).toLatin1().data());
        package_out = new std::ofstream((base_dir_name+doc_options.getTestpackageVHDLPath()).toLatin1().data());

        if (!testbench_out)
        {
          Error::warningOk(tr("Unable to open file %1!").arg(doc_options.getTestbenchVHDLPath()));
          return false;
        }
        if (!testvector_out)
        {
          Error::warningOk(tr("Unable to open file %1!").arg(doc_options.getTestvectorASCIIPath()));
          return false;
        }
        if (!package_out)
        {
          Error::warningOk(tr("Unable to open file %1!").arg(doc_options.getTestpackageVHDLPath()));
          return false;
        }
        break;
      }
      else return TRUE;
      }


    result= ExportVHDL::checkMachineNames(project->machine,&doc_options,&invalidNames);
    if(!result)
    {
      errorMessage=tr("Export of file %1 failed!").arg(fileio->getActExportFileName())+"\n\n"+
                   tr("The following identifiers do not match the VHDL syntax:")+"\n";
      errorMessage+=invalidNames.join("\n");
      Error::warningOk(errorMessage);

      statusbar->message(tr("Export of file")+" "+ fileio->getActExportFileName() + " " +
          tr("failed."), 2000);
      delete testvector_out;
      delete testbench_out;
      delete package_out;
      return FALSE;
    }


    project->machine->updateDefaultTransitions();


    ExportTestbenchVHDL* exportTestbench = new ExportTestbenchVHDL(&doc_options);
    ExportTestvectorASCII *exportTestvector = new ExportTestvectorASCII(&doc_options);

    exportTestbench->init(testbench_out,package_out,project->machine,doc_options.getTestbenchVHDLPath(),NULL);
    exportTestvector->init(testvector_out,project->machine,doc_options.getTestvectorASCIIPath(),NULL);

    exportTestbench->doExport();
    exportTestvector->doExport();

    delete exportTestbench;
    delete exportTestvector;
    delete testvector_out;
    delete testbench_out;
    delete package_out;

    if (result)
      statusbar->message(tr("File")+" "+ fileio->getActExportFileName() + " " +
    tr("exported."), 2000);

    updateAll();
    return result;
  }
  return FALSE;
}

/// Exports the current file to a Verilog HDL file
bool MainWindow::fileExportVerilog()
{
  if (project)
  {
    bool result;

    switch(ver_export->exec())
    {
      case QDialog::Accepted:
	doc_options.applyOptions(this);
	break;
      case QDialog::Rejected:
	return TRUE;
	break;
    }

    project->machine->updateDefaultTransitions();
    ExportVerilog* exp = new ExportVerilog(&doc_options);
    result = fileio->exportFile(project, exp);
    delete exp;

    if (result)
      statusbar->message(tr("File")+" "+ fileio->getActExportFileName() + " " +  
	  tr("exported."), 2000);

    updateAll();
    return result;
  }
  return FALSE;
}


/// Exports the current file to a KISS file
bool MainWindow::fileExportKISS()
{
  if (project)
  {
    bool result;

    project->machine->updateDefaultTransitions();
    ExportKISS* exp = new ExportKISS(&doc_options);
    result = fileio->exportFile(project, exp);
    delete exp;

    if (result)
      statusbar->message(tr("File")+" "+ fileio->getActExportFileName() + " " +  
	  tr("exported."), 2000);

    updateAll();
    return result;
  }
  return FALSE;
}

/// Exports the current file to the 'vvvv Automata code' window
bool MainWindow::fileExportVVVV()
{
  if (project)
  {
    bool result=true;

    project->machine->updateDefaultTransitions();
    updateVVVV();
    vvvv_export->show();
    /*
    if (result)
      statusbar->message(tr("File")+" "+ fileio->getActExportFileName() + " " +  
	  tr("exported."), 2000);

	  */
    updateAll();
    return result;
  }
  return false;
}

/// Exports the current file to a SCXML file
bool MainWindow::fileExportSCXML()
{
  if (project)
  {
    bool result;

    project->machine->updateDefaultTransitions();
    ExportSCXML* exp = new ExportSCXML(&doc_options);
    result = fileio->exportFile(project, exp);
    delete exp;

    if (result)
      statusbar->message(tr("File")+" "+ fileio->getActExportFileName() + " " +  
	  tr("exported."), 2000);

    updateAll();
    return result;
  }
  return FALSE;
}


void MainWindow::updateVVVV()
{
  doc_options.applyOptions(this);

  ExportVVVV* exp = new ExportVVVV(&doc_options);
  //string exp_output;
  ostringstream ostr;
  //result = fileio->exportFile(project, exp);
  exp->init(&ostr ,project->machine);
  exp->doExport();
  vvvv_export->setText(ostr.str().c_str());
  //qDebug("%s" ,str.str().c_str());
  delete exp;

}


/// Exports the current file to an ASCII state table
bool MainWindow::fileExportSTASCII()
{
  if (project)
  {
    bool result;

    switch(statetable_export->exec())
    {
      case QDialog::Accepted:
	//opt_display->init(&doc_options);
	doc_options.applyOptions(this);
	break;
      case QDialog::Rejected:
	return TRUE;
	break;
    }
    QCursor oldcursor1 = cursor();
    QCursor oldcursor2 = wscroll->viewport()->cursor();
    setCursor(Qt::waitCursor);
    wscroll->viewport()->setCursor(Qt::waitCursor);

    TableBuilderASCII* tb = new TableBuilderASCII(this, project->machine, &doc_options);
    ExportStateTable* exp = new ExportStateTable(&doc_options, tb);
    result = fileio->exportFile(project, exp);
    delete exp;
    delete tb;

    if (result)
      statusbar->message(tr("File")+" "+ fileio->getActExportFileName() + " " +  
	  tr("exported."), 2000);


    setCursor(oldcursor1);
    wscroll->viewport()->setCursor(oldcursor2);

    updateAll();
    return result;
  }
  return FALSE;
}

/// Exports the current file to a Latex state table
bool MainWindow::fileExportSTLatex()
{
  if (project)
  {
    bool result;

    switch(statetable_export->exec())
    {
      case QDialog::Accepted:
	//opt_display->init(&doc_options);
	doc_options.applyOptions(this);
	break;
      case QDialog::Rejected:
	return TRUE;
	break;
    }
    QCursor oldcursor1 = cursor();
    QCursor oldcursor2 = wscroll->viewport()->cursor();
    setCursor(Qt::waitCursor);
    wscroll->viewport()->setCursor(Qt::waitCursor);

    TableBuilderLatex* tb = new TableBuilderLatex(this, project->machine, &doc_options);
    ExportStateTable* exp = new ExportStateTable(&doc_options, tb);
    result = fileio->exportFile(project, exp);
    delete exp;
    delete tb;

    if (result)
      statusbar->message(tr("File")+" "+ fileio->getActExportFileName() + " " +  
	  tr("exported."), 2000);


    setCursor(oldcursor1);
    wscroll->viewport()->setCursor(oldcursor2);

    updateAll();
    return result;
  }
  return FALSE;
}

/// Exports the current file to a HTML state table
bool MainWindow::fileExportSTHTML()
{
  if (project)
  {
    bool result;

    switch(statetable_export->exec())
    {
      case QDialog::Accepted:
	doc_options.applyOptions(this);
	break;
      case QDialog::Rejected:
	return TRUE;
	break;
    }

    QCursor oldcursor1 = cursor();
    QCursor oldcursor2 = wscroll->viewport()->cursor();
    setCursor(Qt::waitCursor);
    wscroll->viewport()->setCursor(Qt::waitCursor);

    TableBuilderHTML* tb = new TableBuilderHTML(this, project->machine, &doc_options);
    ExportStateTable* exp = new ExportStateTable(&doc_options, tb);
    result = fileio->exportFile(project, exp);
    delete exp;
    delete tb;

    if (result)
      statusbar->message(tr("File")+" "+ fileio->getActExportFileName() + " " +  
	  tr("exported."), 2000);

    setCursor(oldcursor1);
    wscroll->viewport()->setCursor(oldcursor2);

    updateAll();
    return result;
  }
  return FALSE;
}


/// Exports the current file to a Ragel file
bool MainWindow::fileExportRagel()
{

  if (project)
  {
    bool result;

    switch(ragel_export->exec())
    {
      case QDialog::Accepted:
	doc_options.applyOptions(this);
	break;
      case QDialog::Rejected:
	return TRUE;
	break;
    }

    project->machine->updateDefaultTransitions();
    ExportRagel* exp = new ExportRagel(&doc_options);
    result = fileio->exportFile(project, exp);

    if(!result)
      return FALSE;

    QFileInfo fi(fileio->getActExportFileName());
    bool create_action_file=doc_options.getRagelCreateAction();
    QString act_file = fileio->getExportDir() + "/" + fi.baseName() + "_actions.rl";
    if (create_action_file)
    {
      QFile ftmp(act_file);
      if (ftmp.exists())
      {
	if (Error::warningOkCancel(tr("File %1 exists. Do you want to overwrite it?").arg(act_file))!=QMessageBox::Ok)
	  create_action_file = FALSE;
      }
    }


    if (create_action_file)
      exp->writeActionFile(act_file, fileio->getActExportFileName());

    delete exp;

    if (result)
      statusbar->message(tr("File")+" "+ fileio->getActExportFileName() + " " +  
	  tr("exported."), 2000);

    updateAll();
    return result;
  }
  return FALSE;
}


/// Exports the current file to a SCXML file
bool MainWindow::fileExportSMC()
{
  if (project)
  {
    bool result;

    project->machine->updateDefaultTransitions();
    ExportSMC* exp = new ExportSMC(&doc_options);
    result = fileio->exportFile(project, exp);
    delete exp;

    if (result)
      statusbar->message(tr("File")+" "+ fileio->getActExportFileName() + " " +  
	  tr("exported."), 2000);

    updateAll();
    return result;
  }
  return FALSE;
}








/// Prints the current file.
void MainWindow::filePrint()
{
  QCursor oldcursor1 = cursor();
  QCursor oldcursor2 = wscroll->viewport()->cursor();
  setCursor(Qt::waitCursor);
  wscroll->viewport()->setCursor(Qt::waitCursor);

  printmanager->print();

  setCursor(oldcursor1);
  wscroll->viewport()->setCursor(oldcursor2);
}


/// Called when 'File->Quit' is clicked
void MainWindow::fileQuit()
{
  /*
  if (project && project->hasChanged())
  {
    switch(mb_changed->exec())
    {
      case QMessageBox::Yes:
        if (!fileSave())
	  return;
        break;
      case QMessageBox::No:
        break;
      case QMessageBox::Cancel:
        return;
	break;
    }
  }
  */
  close();
//  emit quitWindow(this);
}


/*
/// Opens a new window
void MainWindow::fileNewWindow()
{
//  MainWindow* wmain;

//  wmain = new MainWindow();
//  wmain->setLanguage(getLanguage());
//  wmain->resize(600, 500);
//  wmain->show();
  control->newWindow(getLanguage());
}
*/


/// Closes the current file.
bool MainWindow::fileClose()
{
  if (project)
  {
    if (project->hasChanged())
    {
      switch(mb_changed->exec())
      {
	case QMessageBox::Yes:
	  if (!fileSave())
	    return FALSE;
	  break;
	case QMessageBox::No:
	  break;
	case QMessageBox::Cancel:
	  return FALSE;
	  break;
      }
    }

    delete project;
    project = NULL;

    wscroll->getDrawArea()->resetState();
    wscroll->updateBackground();
    wscroll->getDrawArea()->getSelection()->clear();
    wscroll->getDrawArea()->repaint();

    setMode(DocStatus::Select);
    simulator->closeDlg();

    statusbar->message(tr("File")+" "+ fileio->getActFileName() + " " +  
	tr("closed."), 2000);

    updateAll();

    return TRUE;
  }
  return FALSE;
}



/// Undo the last action.
void MainWindow::editUndo()
{
  if (project)
  {
    project->getUndoBuffer()->undo();
    updateAll();
    wscroll->widget()->repaint();
  }
}

/// Cuts the selected objects from the current machine and puts it on the clipboard
void MainWindow::editCut()
{
  int count = wscroll->getDrawArea()->getSelection()->count();

  bcut=TRUE;
  editCopy();
  editDelete();
  bcut=FALSE;

  if (count==1)
    statusbar->message(QString::number(count) + " " + tr("object cut."), 2000);
  else
    statusbar->message(QString::number(count) + " " + tr("objects cut."), 2000);

  updatePaste();
}

/// Copies the selected objects to the clipboard
void MainWindow::editCopy()
{
  QString data;

  if (!project)
    return;


  if (!edit->copy(wscroll->getDrawArea()->getSelection(), project, project->machine, data))
    return;
//  qDebug(data);

  QClipboard* cb = QApplication::clipboard();

  MimeMachine* mm = new MimeMachine(data);
//  QTextDrag* td = new QTextDrag(data);
  cb->setMimeData(mm);

  if (!bcut)
  {
    int count = wscroll->getDrawArea()->getSelection()->count();
    if (count==1)
      statusbar->message(QString::number(count) + " " + tr("object copied."), 2000);
    else 
      statusbar->message(QString::number(count) + " " + tr("objects copied."), 2000);
  }

//  qDebug(cb->data()->format());
  updatePaste();
}

/// Pastes the objects on the clipboard into the current machine
void MainWindow::editPaste()
{
  if (!project)
    return;

  QString format;
//  QByteArray cbdata;
  QString data;
  MimeMachine* mm;

  QClipboard* cb = QApplication::clipboard();

  format = cb->data()->format();
  


//  qDebug(format);
  if (format!="text/qfsm-objects")
    return;

  mm =(MimeMachine*)cb->mimeData();
//  data = cb->text();

  data=QString(mm->data("text/qfsm-objects"));


//  QString data = QString(cbdata);
//  qDebug(data);
//  data = cb->text();

  if (data == QString::null || data.isEmpty())
    return;

  wscroll->getDrawArea()->getSelection()->deselectAll(project->machine);

  if (edit->paste(wscroll->getDrawArea()->getSelection(), project, project->machine, data))
  {
    emit objectsPasted();
    project->setChanged();
  }

  int count = wscroll->getDrawArea()->getSelection()->count();
  if (count==1)
    statusbar->message(QString::number(count) + " " + tr("object pasted."), 2000);
  else
    statusbar->message(QString::number(count) + " " + tr("objects pasted."), 2000);

  wscroll->widget()->repaint();
  updateAll();
}

/// Delete the selected objects.
void MainWindow::editDelete()
{
  int count = wscroll->getDrawArea()->getSelection()->count();

  edit->deleteSelection(wscroll->getDrawArea()->getSelection(), project->machine);

  if (!bcut)
  {
    if (count==1)
      statusbar->message(QString::number(count) + " " + tr("object deleted."), 2000);
    else
      statusbar->message(QString::number(count) + " " + tr("objects deleted."), 2000);
  }

  project->setChanged();
  updateAll();
  wscroll->widget()->repaint();
}

/// Set select mode.
void MainWindow::editSelect()
{
  setMode(DocStatus::Select);
}


/// Called when 'Edit->Select all' is clicked
void MainWindow::editSelectAll()
{
  DRect bound;
  if (wscroll->getDrawArea()->getSelection()->selectAll(project->machine, bound))
    emit allSelected();
  wscroll->getDrawArea()->setSelectionRect(bound);
  updateAll();
}

/// Called when 'Edit->Deselect all' is clicked
void MainWindow::editDeselectAll()
{
  wscroll->getDrawArea()->getSelection()->deselectAll(project->machine);
  wscroll->widget()->repaint();
  updateAll();
}


/// Edit options.
void MainWindow::editOptions()
{
  if (tabdialog->exec())
  {
    doc_options.applyOptions(this);
    fileio->saveOptions(&doc_options);
    wscroll->widget()->repaint();
  }
}


/// Initiate a drag operation and process the drop result
bool MainWindow::runDragOperation(bool force_copy)
{
  bool ret=false;
  QString data;


  if (edit->copy(this->wscroll->getDrawArea()->getSelection(), project, project->machine, data))
  {
  MimeMachine* mm = new MimeMachine(data);


   QDrag*drag = new QDrag(this);
   drag->setMimeData(mm);

   Qt::DropAction dropAction;
   if(force_copy)
     dropAction = drag->exec(Qt::CopyAction);
   else dropAction = drag->exec(Qt::CopyAction);


   switch(dropAction)
   {
   case Qt::IgnoreAction:
     qDebug("Drag action ignored");
     break;
   case Qt::CopyAction:
   case Qt::LinkAction:
     qDebug("Drag action finished");
     ret=true;
     break;
     case Qt::MoveAction:
     case Qt::TargetMoveAction:
       qDebug("Drag action finished, deleting data");
       ret=true;
       this->editDelete();
       break;
   }
 }
  return ret;
}

/// Toggle view state encoding
void MainWindow::viewStateEncoding()
{
  doc_options.setViewStateEncoding(!doc_options.getViewStateEncoding());
  updateAll();
  wscroll->widget()->repaint();
}

/// Toggle view moore outputs.
void MainWindow::viewMooreOutputs()
{
  doc_options.setViewMoore(!doc_options.getViewMoore());
  updateAll();
  wscroll->widget()->repaint();
}

/// Toggle view mealy outputs.
void MainWindow::viewMealyOutputs()
{
  doc_options.setViewMealyOut(!doc_options.getViewMealyOut());
  updateAll();
  wscroll->widget()->repaint();
}

/// Toggle view mealy inputs.
void MainWindow::viewMealyInputs()
{
  doc_options.setViewMealyIn(!doc_options.getViewMealyIn());
  updateAll();
  wscroll->widget()->repaint();
}

/// Toggle view grid.
void MainWindow::viewGrid()
{
  QString str;
  doc_options.setViewGrid(!doc_options.getViewGrid());
  if (doc_options.getViewGrid())
    str=tr("on");
  else
    str=tr("off");
  statusbar->message(tr("Grid is %1.").arg(str), 2000);

  updateAll();
  wscroll->widget()->repaint();
}

/// Toggle view shadows.
void MainWindow::viewShadows()
{
  doc_options.setStateShadows(!doc_options.getStateShadows());
  updateAll();
  wscroll->widget()->repaint();
}



/// Set panning mode
void MainWindow::viewPan()
{
//  QDragEnterEvent*ev=new QDragEnterEvent(QPoint(0,0),Qt::CopyAction,new QMimeData(),Qt::LeftButton,Qt::NoModifier);
//  QPaintEvent*ev=new QPaintEvent(QRect(0,0,100,100));
//  QApplication::postEvent(wscroll,ev);
  wscroll->widget()->repaint();
  bool ret;
  //QApplication::sendPostedEvents();
  if(ret)
    qDebug("events processed");
  else qDebug("events not postet");
  setMode(DocStatus::Pan);
}

/// Set zooming mode
void MainWindow::viewZoom()
{
  setMode(DocStatus::Zooming);
}

/// Zoom in the view.
void MainWindow::viewZoomIn()
{
//  QPoint middle(wscroll->visibleWidth()/2, wscroll->visibleHeight()/2);
//  QPoint offset(wscroll->contentsX(), wscroll->contentsY());
  QPoint middle(wscroll->width()/2, wscroll->height()/2);
  QPoint offset=wscroll->getDrawArea()->mapTo(wscroll,QPoint(0,0));
  middle -= offset;

  wscroll->getDrawArea()->zoomIn(middle); //zoom->zoom(wscroll, p, TRUE);
}

/// Zoom out the view.
void MainWindow::viewZoomOut()
{
//  QPoint middle(wscroll->visibleWidth()/2, wscroll->visibleHeight()/2);
//  QPoint offset(wscroll->contentsX(), wscroll->contentsY());
  QPoint middle(wscroll->width()/2, wscroll->height()/2);
  QPoint offset=wscroll->getDrawArea()->mapTo(wscroll,QPoint(0,0));
  middle -= offset;


  wscroll->getDrawArea()->zoomOut(middle); //zoom->zoom(wscroll, p, FALSE);
}

/// Set zoom to 100%
void MainWindow::viewZoom100()
{
  wscroll->getDrawArea()->zoomReset();
}


/// Toggle IO view
void MainWindow::viewIOView()
{

  doc_options.setViewIOView(!doc_options.getViewIOView());

  if(doc_options.getViewIOView() && project)
    view_io->show();
  else view_io->hide();

  updateMenuBar();
}

/// Update IOView text
void MainWindow::updateIOView(Machine*m)
{
  if(m!=NULL)
  {
    view_io->updateIOList(m);

    if(doc_options.getViewIOView())
      view_io->show();
    else view_io->hide();

    updateMenuBar();
  }

}


/// Edit the current machine.
void MainWindow::machineEdit()
{
  machinemanager->editMachine(project);
  updateAll();
  wscroll->widget()->repaint();
}

/// Automatically correct the state codes of the machine.
void MainWindow::machineCorrectCodes()
{
  project->machine->correctCodes();
  updateAll();
  wscroll->widget()->repaint();
}

/// Simulate the current machine.
void MainWindow::machineSimulate()
{
  if (getMode()!=DocStatus::Simulating)
  {
    if (simulator->startSimulation(project->machine))
    {
      setMode(DocStatus::Simulating);
      wscroll->widget()->repaint();
    }  
  }
  else
  { 
    simulator->stopSimulation();
    setMode(DocStatus::Select);
  }
  updateAll();
}

/// Called when 'Machine->Check Integrity' is clicked
void MainWindow::machineICheck()
{
  if (project && project->machine)
  {
    QCursor oldcursor1 = cursor();
    QCursor oldcursor2 = wscroll->viewport()->cursor();
    setCursor(Qt::waitCursor);
    wscroll->viewport()->setCursor(Qt::waitCursor);

    statusbar->message(tr("Checking machine..."));
    project->machine->checkIntegrity(ichecker);
    statusbar->message(tr("Check finished."), 2000);

    setCursor(oldcursor1);
    wscroll->viewport()->setCursor(oldcursor2);
  }
}


/// Add new state to current machine.
void MainWindow::stateNew()
{
  setMode(DocStatus::NewState);
}

/// Edit selected state.
void MainWindow::stateEdit()
{
  GState* s;
  int otype;
  s = (GState*)wscroll->getDrawArea()->getContextObject(otype);

  if (!s)
    s = wscroll->getDrawArea()->getSelection()->getSList().front();

  if (s && project)
    statemanager->editState(s);
}
  

/// Set selected state as initial state.
void MainWindow::stateSetInitial()
{
  GState* s;
  int otype;
  s = (GState*)wscroll->getDrawArea()->getContextObject(otype);

  if (!s)
    s = wscroll->getDrawArea()->getSelection()->getSList().front();

  if (s && project)
  {
    statemanager->setInitialState(project->machine, s);
    updateAll();
    wscroll->widget()->repaint();
  }
}

/// Set selected state as final state.
void MainWindow::stateSetFinal()
{
  GState* s;
//  int otype;
  s = NULL; //(GState*)wscroll->getContextObject(otype);
  Machine* m;
  
  if (!project)
    return;
  m = project->machine;
  if (!m)
    return;

  statemanager->setFinalStates(m, wscroll->getDrawArea()->getSelection()->getSList());

  updateAll();
  wscroll->widget()->repaint();

  /*
  if (!s)
    s = wscroll->getSelection()->getSList().getFirst();

  if (s && project)
  {
    statemanager->setEndState(project->machine, s);
    updateAll();
    wscroll->viewport()->repaint();
  }
  */
}

/// Add new transition.
void MainWindow::transNew()
{
  setMode(DocStatus::NewTransition);
}

/// Edit selected transition.
void MainWindow::transEdit()
{
  GTransition* t;
  int otype;
  t = (GTransition*)wscroll->getDrawArea()->getContextObject(otype);

  if (!t)
    t = wscroll->getDrawArea()->getSelection()->getTList().front();

  if (t && project)
    transmanager->editTransition(project->machine, t);
}
  
/// Straighten selected transitions.
void MainWindow::transStraighten()
{
  GTransition* t;
//  int otype;
  t = NULL; //(GTransition*)wscroll->getContextObject(otype);
  if (t)
  {
    project->getUndoBuffer()->changeTransition(t);
    t->straighten();
  }
  else
    transmanager->straightenSelection(&wscroll->getDrawArea()->getSelection()->getTList());

  project->setChanged();
  updateAll();
  wscroll->widget()->repaint();
}


void MainWindow::helpManual()
{
  QDir dir;
  QString qfsmpath;;
#ifdef WIN32
  QString tmppath;
  QSettings settings("HKEY_LOCAL_MACHINE\\Software\\Qfsm", QSettings::NativeFormat);
  tmppath = settings.value("Install_Dir", QVariant("-1")).toString();
  //qDebug("tmppath: %s", tmppath.latin1());
  if (tmppath=="-1")
    dir = QDir::current();
  else
    dir.cd(tmppath);
  dir.cd(QFSM_HELP_DIR);
  qfsmpath = dir.absolutePath();
#else
  qfsmpath = QFSM_HELP_DIR;
  dir = QDir(qfsmpath); 
#endif
  QFileInfo fi(dir, "qfsm.html");
  QString helpfile = fi.absoluteFilePath();
  QDesktopServices::openUrl(QUrl::fromLocalFile(helpfile));
}

/// Displays a help dialog about qfsm.
void MainWindow::helpAbout()
{
  AppInfo info(this);

  info.about();
}

/// Displays a help dialog about Qt.
void MainWindow::helpAboutQt()
{
  QMessageBox::aboutQt(this, "qfsm");
}




/// Sets the wait cursor for the main window and the scrollview
void MainWindow::setWaitCursor()
{
  previous_viewcursor = wscroll->viewport()->cursor();
  setCursor(Qt::waitCursor);
  wscroll->viewport()->setCursor(Qt::waitCursor);
}


/// Restores the previous cursor for the main window and the scrollview
void MainWindow::setPreviousCursor()
{
  setCursor(Qt::arrowCursor);
  wscroll->viewport()->setCursor(previous_viewcursor);
}

