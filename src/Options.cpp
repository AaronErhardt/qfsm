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

#include <qdir.h>
#include <q3textstream.h>
#include <qregexp.h>

#include "MainWindow.h"
#include "Options.h"


/**
 * Constructor.
 * Initialises the options object with standard values.
 */
Options::Options(QObject* parent/*=NULL*/, const char* name/*=0*/)
 	:QObject(parent, name)
{
  viewStateEncoding = FALSE;
  viewMoore = TRUE;
  viewMealyIn = TRUE;
  viewMealyOut = FALSE;
  viewGrid = FALSE;
  viewIOView = FALSE;

  gridSize = 10;
  gridColor.setRgb(200, 200, 200);
  lockstates = TRUE;
  locktransitions = TRUE;

  stateShadows = TRUE;
  stateShadowColor = QColor(Qt::darkGray);

  tooltips = TRUE;
  iomark = FALSE;
  ionames = FALSE;
  bdrawbox = FALSE;

  initial_descriptor=tr("rst_n");
  inversion_descriptor=tr("NOT");
  any_input_descriptor="";//tr("any");
  default_descriptor=tr("default");

  ahdl_sync_reset = FALSE;
  ahdl_use_moore = FALSE;

  vhdl_symbolic_states = TRUE;
  vhdl_inout_names = TRUE;
  vhdl_sync_reset = FALSE;
  vhdl_sync_enable = FALSE;
  vhdl_neg_reset = TRUE;
  vhdl_stdlogic = TRUE;
  vhdl_io_header = TRUE;
  vhdl_alliance = FALSE;
  vhdl_state_code = FALSE;
  vhdl_cond_notation = 0;
  vhdl_architecture_name = "behave";
  vhdl_sep_files = FALSE;
  vhdl_sync_look_ahead = FALSE;
  vhdl_state_debug = false;

  ver_sync_reset = FALSE;

  testbench_stdlogic=TRUE;
  testbench_io_header=TRUE;
  testbench_ionames=TRUE;
  testbench_negatedreset=TRUE;
  testbench_synchronousreset=FALSE;
  testbench_synchronousenable=FALSE;
  testbench_algorithm=0;
  testbench_vhdl_path="";
  testvector_ascii_path="";
  testbench_base_directory="";
  testbench_logfile_path="";

  statetable_includeout = FALSE;
  statetable_orientation = 0;
  statetable_resolve_inverted = 0;

  ragel_create_action = FALSE;
  ragel_lang_action = 0;
  ragel_default_transitions = false;

  vvvv_reset = 0;
  vvvv_reset_event = "Reset";
  vvvv_reset_action = "DoReset";

  print_header = TRUE;
}

/**
 * Applies the options from the tab dialogs with the options.
 */
void Options::applyOptions(MainWindow* pMain)
{
  // General
  QString lang;
  QString path;
  QDir dir = QDir::home();
  path = dir.absPath()+"/.qfsm/language";

  QFile file(path);
  Q3TextStream fout(&file);

  if (!file.open(QIODevice::WriteOnly))
  {
    qDebug("language could not be saved");
    return;
  }

  OptGeneralDlgImpl* optgen;
  optgen = pMain->getOptGeneral();
  lang = optgen->getLanguage();
  fout << lang << endl;

  file.close();

  // Display
  gridSize = pMain->getOptDisplay()->getGridSize();
  gridColor = pMain->getOptDisplay()->getGridColor();

  stateShadows = pMain->getOptDisplay()->getShadows();
  stateShadowColor = pMain->getOptDisplay()->getShadowColor();

  tooltips = pMain->getOptDisplay()->getToolTips();
  iomark = pMain->getOptDisplay()->getIOMark();
  ionames = pMain->getOptDisplay()->getDisplayIONames();
  bdrawbox = pMain->getOptDisplay()->getDrawBox();

  initial_descriptor = pMain->getOptDisplay()->getInitialDescriptor();
  initial_descriptor = initial_descriptor.replace(QRegExp("\\s"), "_");
  inversion_descriptor = pMain->getOptDisplay()->getInversionDescriptor();
  inversion_descriptor = inversion_descriptor.replace(QRegExp("\\s"), "_");
  any_input_descriptor = pMain->getOptDisplay()->getAnyInputDescriptor();
  any_input_descriptor = any_input_descriptor.replace(QRegExp("\\s"), "_");
  default_descriptor = pMain->getOptDisplay()->getDefaultDescriptor();
  default_descriptor = default_descriptor.replace(QRegExp("\\s"), "_");

  // AHDL
  ahdl_sync_reset = pMain->getExportAHDL()->getSyncReset();
  ahdl_use_moore = pMain->getExportAHDL()->getUseMoore();

  // VHDL
  vhdl_symbolic_states = pMain->getExportVHDL()->getSymbolicStates();
  vhdl_inout_names  = pMain->getExportVHDL()->getInOutNames();
  vhdl_sync_reset = pMain->getExportVHDL()->getSyncReset();
  vhdl_sync_enable = pMain->getExportVHDL()->getSyncEnable();
  vhdl_neg_reset = pMain->getExportVHDL()->getNegReset();
  vhdl_stdlogic = pMain->getExportVHDL()->getStdLogic();
  vhdl_io_header = pMain->getExportVHDL()->getIOheader();
  vhdl_alliance = pMain->getExportVHDL()->getAlliance();
  vhdl_cond_notation = pMain->getExportVHDL()->getCondNotation();
  vhdl_state_code = pMain->getExportVHDL()->getStateCode();
  vhdl_architecture_name = pMain->getExportVHDL()->getArchitectureName();
  vhdl_sep_files = pMain->getExportVHDL()->getSepFiles();
  vhdl_sync_look_ahead = pMain->getExportVHDL()->getLookAhead();
  vhdl_architecture_path = pMain->getExportVHDL()->getArchitecturePath();
  vhdl_entity_path = pMain->getExportVHDL()->getEntityPath();
  vhdl_state_debug = pMain->getExportVHDL()->getDebugState();


  // Testbench
  testbench_stdlogic=pMain->getExportTestbench()->getStdLogic();
  testbench_synchronousreset=pMain->getExportTestbench()->getSynchronousReset();
  testbench_synchronousenable=pMain->getExportTestbench()->getSynchronousEnable();
  testbench_negatedreset=pMain->getExportTestbench()->getNegatedReset();
  testbench_io_header=pMain->getExportTestbench()->getIOheader();
  testbench_ionames=pMain->getExportTestbench()->getIONames();
  testbench_algorithm=pMain->getExportTestbench()->getAlgorithm();
  testbench_vhdl_path=pMain->getExportTestbench()->getTestbenchVHDLPath();
  testvector_ascii_path=pMain->getExportTestbench()->getTestvectorASCIIPath();
  testpackage_vhdl_path=pMain->getExportTestbench()->getPackageVHDLPath();
  testbench_logfile_path=pMain->getExportTestbench()->getLogfilePath();
  testbench_base_directory=pMain->getExportTestbench()->getBaseDirectory();

  // Verilog
  ver_sync_reset = pMain->getExportVerilog()->getSyncReset();
  //ver_register_out = pMain->getExportVerilog()->getRegisterOut();

  // State Table
  statetable_includeout = pMain->getExportStateTable()->getIncludeOutputs();
  statetable_resolve_inverted = pMain->getExportStateTable()->getResolveInverted();
  statetable_orientation = pMain->getExportStateTable()->getOrientation();

  // Ragel
  ragel_create_action = pMain->getExportRagel()->getCreateAction();
  ragel_lang_action = pMain->getExportRagel()->getLangAction();
  ragel_default_transitions = pMain->getExportRagel()->getAddDefaultTransitions();

  // VVVV
  vvvv_reset = pMain->getExportVVVV()->getVVVVReset();
  vvvv_reset_event = pMain->getExportVVVV()->getVVVVResetEvent();
  vvvv_reset_action = pMain->getExportVVVV()->getVVVVResetAction();

  // Printing
  print_header = pMain->getOptPrinting()->getPrintHeader();

  pMain->updateMenuBar();
}



