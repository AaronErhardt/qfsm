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

#include <qcheckbox.h>
#include <QFileDialog>

#include "ExportVHDLDlgImpl.h"
#include "Options.h"
#include "Machine.h"

/**
 *  Constructs a ExportVHDLDlgImpl which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f' 
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
ExportVHDLDlgImpl::ExportVHDLDlgImpl( QWidget* parent,  const char* name, bool modal, Qt::WFlags fl )
{
  symbolic_states=false;
  inout_names=true;
  sync_reset=false;
  sync_enable=false;
  neg_reset=true;
  stdlogic=true;
  io_header=true;
  alliance=false;
  state_code=false;

  //load ui design for the current object
  exportVHDLDlg.setupUi(this);

  //connects between ui elements and the current class must be done in the code
  connect(exportVHDLDlg.cb_symbolicstates, SIGNAL(clicked()), this, SLOT(symbolicNamesClicked()));
  connect(exportVHDLDlg.cb_inoutnames, SIGNAL(clicked()), this, SLOT(inOutNamesClicked()));
  connect(exportVHDLDlg.cb_synchreset, SIGNAL(clicked()), this, SLOT(synchronousResetClicked()));
  connect(exportVHDLDlg.cb_synchenable, SIGNAL(clicked()),this,SLOT(synchronousEnableClicked()));
  connect(exportVHDLDlg.cb_negreset, SIGNAL(clicked()), this, SLOT(negResetClicked()));
  connect(exportVHDLDlg.cb_stdlogic, SIGNAL(clicked()), this, SLOT(useStdLogicClicked()));
  connect(exportVHDLDlg.cb_iodesc, SIGNAL(clicked()), this, SLOT(ioHeaderClicked()));
  connect(exportVHDLDlg.cb_alliance, SIGNAL(clicked()), this, SLOT(allianceClicked()));
  connect(exportVHDLDlg.cb_state_code, SIGNAL(clicked()), this, SLOT(stateCodeClicked()));
  connect(exportVHDLDlg.bg_cond_notation, SIGNAL(clicked(int)), this, SLOT(condNotationClicked(int)));
  connect(exportVHDLDlg.cb_sep_files,SIGNAL(clicked()),this,SLOT(sepFilesClicked()));
  connect(exportVHDLDlg.cb_look_ahead,SIGNAL(clicked()),this,SLOT(lookAheadClicked()));
  connect(exportVHDLDlg.le_architecture_name,SIGNAL(textChanged(QString)),this,SLOT(architectureNameChanged(QString)));
  connect(exportVHDLDlg.le_architecture_file,SIGNAL(textChanged(QString)),this,SLOT(archtitecturePathChanged(QString)));
  connect(exportVHDLDlg.le_entity_file,SIGNAL(textChanged(QString)),this,SLOT(entityPathChanged(QString)));
  connect(exportVHDLDlg.pb_architecture_file,SIGNAL(clicked()),this,SLOT(selectArchitectureFileClicked()));
  connect(exportVHDLDlg.pb_entity_file,SIGNAL(clicked()),this,SLOT(selectEntityFileClicked()));
  connect(exportVHDLDlg.cb_debugstate, SIGNAL(clicked()), this, SLOT(debugStateClicked()));

}

/**
 *  Destroys the object and frees any allocated resources
 */
ExportVHDLDlgImpl::~ExportVHDLDlgImpl()
{
    // no need to delete child widgets, Qt does it all for us
}

/**
 * public slot
 */
void ExportVHDLDlgImpl::symbolicNamesClicked()
{
  symbolic_states = exportVHDLDlg.cb_symbolicstates->isChecked();
}

void ExportVHDLDlgImpl::inOutNamesClicked()
{
  inout_names = exportVHDLDlg.cb_inoutnames->isChecked();
}

/**
 * public slot
 */
void ExportVHDLDlgImpl::synchronousResetClicked()
{
  sync_reset = exportVHDLDlg.cb_synchreset->isChecked();
}

/**
 * public slot
 */
void ExportVHDLDlgImpl::synchronousEnableClicked()
{
  sync_enable = exportVHDLDlg.cb_synchenable->isChecked();
}


/**
 * public slot
 */
void ExportVHDLDlgImpl::negResetClicked()
{
  neg_reset = exportVHDLDlg.cb_negreset->isChecked();
}

/**
 * public slot
 */
void ExportVHDLDlgImpl::useStdLogicClicked()
{
  stdlogic = exportVHDLDlg.cb_stdlogic->isChecked();
}

/**
 * public slot
 */
void ExportVHDLDlgImpl::ioHeaderClicked()
{
  io_header = exportVHDLDlg.cb_iodesc->isChecked();
}

/**
 * public slot
 */
void ExportVHDLDlgImpl::stateCodeClicked()
{
  state_code = exportVHDLDlg.cb_state_code->isChecked();
}

/**
 * public slot
 */
void ExportVHDLDlgImpl::allianceClicked()
{
  alliance = exportVHDLDlg.cb_alliance->isChecked();
  if (alliance)
  {
    exportVHDLDlg.cb_symbolicstates->setEnabled(false);
    exportVHDLDlg.cb_inoutnames->setEnabled(false);
    exportVHDLDlg.cb_synchreset->setEnabled(false);
    exportVHDLDlg.bg_cond_notation->setEnabled(false);
  }
  else
  {
    exportVHDLDlg.cb_symbolicstates->setEnabled(true);
    exportVHDLDlg.cb_inoutnames->setEnabled(true);
    exportVHDLDlg.cb_synchreset->setEnabled(true);
    exportVHDLDlg.bg_cond_notation->setEnabled(true);
  }
}

/**
 * Initialises the dialog according to the current options @a opt.
 */
void ExportVHDLDlgImpl::init(Options* opt, Machine* m)
{
  symbolic_states = opt->getVHDLSymbolicStates();
  exportVHDLDlg.cb_symbolicstates->setChecked(symbolic_states);
  inout_names = opt->getVHDLInOutNames();
  exportVHDLDlg.cb_inoutnames->setChecked(inout_names);
  sync_reset = opt->getVHDLSyncReset();
  exportVHDLDlg.cb_synchreset->setChecked(sync_reset);
  sync_enable = opt->getVHDLSyncEnable();
  exportVHDLDlg.cb_synchenable->setChecked(sync_enable);
  neg_reset = opt->getVHDLNegReset();
  exportVHDLDlg.cb_negreset->setChecked(neg_reset);
  stdlogic = opt->getVHDLStdLogic();
  exportVHDLDlg.cb_stdlogic->setChecked(stdlogic);
  io_header = opt->getVHDLIOheader();
  exportVHDLDlg.cb_iodesc->setChecked(io_header);
  alliance = opt->getVHDLAlliance();
  exportVHDLDlg.cb_alliance->setChecked(alliance);
  cond_notation = opt->getVHDLCondNotation();
  state_code = opt->getVHDLStateCode();
  sep_files = opt->getVHDLSepFiles();
  path_entity = opt->getVHDLEntityPath();
  path_architecture = opt->getVHDLArchitecturePath();

  exportVHDLDlg.cb_sep_files->setChecked(sep_files);
  sync_look_ahead = opt->getVHDLSyncLookAhead();
  exportVHDLDlg.cb_look_ahead->setChecked(sync_look_ahead);
  architecture_name = opt->getVHDLArchitectureName();
  exportVHDLDlg.le_architecture_name->setText(architecture_name);
  exportVHDLDlg.cb_state_code->setChecked(state_code);
  exportVHDLDlg.bg_cond_notation->setButton(cond_notation);
  setSepFiles(sep_files);

  if(m==NULL)
    machine_name="";
  else machine_name=m->getName();
  if(path_entity.length()>0)
  {
    if(sep_files)
    {
      path_entity=path_entity.left(path_entity.lastIndexOf("/")+1)+"e_"+machine_name+".vhd";
      path_architecture=path_architecture.left(path_architecture.lastIndexOf("/")+1)+"a_"+machine_name+"_"+architecture_name+".vhd";
    }
    else path_entity=path_entity.left(path_entity.lastIndexOf("/")+1)+machine_name+".vhd";
    exportVHDLDlg.le_entity_file->setText(path_entity);
    exportVHDLDlg.le_architecture_file->setText(path_architecture);
  }
  else exportVHDLDlg.pb_export->setEnabled(false);



  if (m && m->getType()==0) // Binary machine
  {
    exportVHDLDlg.cb_alliance->setEnabled(true);
    exportVHDLDlg.cb_inoutnames->setEnabled(true);
  }
  else
  {
    exportVHDLDlg.cb_alliance->setEnabled(false);
    exportVHDLDlg.cb_inoutnames->setEnabled(false);
  }

  if (alliance && m && m->getType()==0)
  {
    exportVHDLDlg.cb_symbolicstates->setEnabled(false);
    exportVHDLDlg.cb_inoutnames->setEnabled(false);
    exportVHDLDlg.cb_synchreset->setEnabled(false);
    exportVHDLDlg.bg_cond_notation->setEnabled(false);
  }
  else 
  {
    exportVHDLDlg.cb_symbolicstates->setEnabled(true);
    //exportVHDLDlg.cb_inoutnames->setEnabled(true);
    exportVHDLDlg.cb_synchreset->setEnabled(true);
    exportVHDLDlg.bg_cond_notation->setEnabled(true);
  }
}

/**
 * public slot
 */
void ExportVHDLDlgImpl::condNotationClicked(int cn)
{
  cond_notation = cn;
}

void ExportVHDLDlgImpl::debugStateClicked()
{
  debug_state = exportVHDLDlg.cb_debugstate->isChecked();
}


void ExportVHDLDlgImpl::sepFilesClicked()
{
  sep_files=exportVHDLDlg.cb_sep_files->isChecked();
  setSepFiles(sep_files);

}

void ExportVHDLDlgImpl::lookAheadClicked()
{
  sync_look_ahead=exportVHDLDlg.cb_look_ahead->isChecked();
}

/**
 * public slot
 */
void ExportVHDLDlgImpl::architectureNameChanged(QString)
{
  architecture_name=exportVHDLDlg.le_architecture_name->text();
  qDebug("architecture name chaned: "+architecture_name);
}

/**
 * public slot
 * Show file dialog to get entity file name
 */
void ExportVHDLDlgImpl::selectArchitectureFileClicked()
{

  if(path_architecture.length()==0)
    path_architecture="a_"+machine_name+"_"+architecture_name+".vhd";


  QString path_architecture_temp=QFileDialog::getSaveFileName(this,"",path_architecture,"VHDL (*.vhd *.vhdl);;All Files (*)",0,QFileDialog::DontConfirmOverwrite);

  if(path_architecture_temp.length()>0)
  {
    exportVHDLDlg.le_architecture_file->setText(path_architecture_temp);
    path_architecture=path_architecture_temp;

  }

}


/**
 * Public slot;
 * Show file dialog to get entity file name
 */
void ExportVHDLDlgImpl::selectEntityFileClicked()
{
  if(path_entity.length()<=0)
  {
    if(sep_files)
      path_entity="e_"+machine_name+".vhd";
    else path_entity=machine_name+".vhd";
  }

  QString path_entity_temp=QFileDialog::getSaveFileName(this,"",path_entity,"VHDL (*.vhd *.vhdl);;All Files (*)",0,QFileDialog::DontConfirmOverwrite);

  if(path_entity_temp.length()>0)
  {
    exportVHDLDlg.le_entity_file->setText(path_entity_temp);
    path_entity=path_entity_temp;

  }
}

/**
 * Public slot to update the entity export path
 */
void ExportVHDLDlgImpl::entityPathChanged(QString new_path)
{
  path_entity=new_path;
  if(path_entity.length()>0)
    exportVHDLDlg.pb_export->setEnabled(true);
  else exportVHDLDlg.pb_export->setEnabled(false);
}

/**
 * Public slot to update the architecture export path
 */
void ExportVHDLDlgImpl::archtitecturePathChanged(QString new_path)
{
  path_architecture=new_path;
}

/// Set the flag for exporting the state machine in two files (architecture and entity)
void ExportVHDLDlgImpl::setSepFiles(bool sep) {
  sep_files=sep;
  if(sep_files)
  {
    exportVHDLDlg.l_entity_file->setText(tr("Entity File Name"));
    exportVHDLDlg.le_architecture_file->setEnabled(true);
    exportVHDLDlg.pb_architecture_file->setEnabled(true);
    exportVHDLDlg.l_architecture_file->setEnabled(true);
  }
  else {
    exportVHDLDlg.l_entity_file->setText(tr("Export File Name"));
    exportVHDLDlg.le_architecture_file->setEnabled(false);
    exportVHDLDlg.pb_architecture_file->setEnabled(false);
    exportVHDLDlg.l_architecture_file->setEnabled(false);
  }
}

