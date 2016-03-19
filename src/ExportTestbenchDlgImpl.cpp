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
#include <QDir>

#include "ExportTestbenchDlgImpl.h"
#include "Options.h"
#include "Machine.h"

/**
 *  Constructs a ExportVHDLDlgImpl which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f' 
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
ExportTestbenchDlgImpl::ExportTestbenchDlgImpl( QWidget* parent,  const char* name, bool modal, Qt::WFlags fl )
:QDialog(parent)
{
  stdlogic=true;
  io_header=true;
  io_names=true;
  negatedreset=true;
  synchronousreset=false;
  synchronousenable=false;
  algorithm=0;
  testbench_vhdl_path="";
  testvector_ascii_path="";
  package_vhdl_path="";
  logfile_path="";
  base_directory="";
  file_dialog=new QFileDialog(this);
  file_dialog->setFileMode(QFileDialog::AnyFile);

  //load ui design for the current object
  exportTestbenchDlg.setupUi(this);


  //connects between ui elements and the current class must be done in the code
  connect(exportTestbenchDlg.cb_stdlogic, SIGNAL(clicked()), this, SLOT(useStdLogicClicked()));
  connect(exportTestbenchDlg.cb_iodesc, SIGNAL(clicked()), this, SLOT(ioHeaderClicked()));
  connect(exportTestbenchDlg.cb_ionames,SIGNAL(clicked()),this,SLOT(ioNamesClicked()));
  connect(exportTestbenchDlg.cb_syncreset, SIGNAL(clicked()), this, SLOT(synchronousResetClicked()));
  connect(exportTestbenchDlg.cb_negatedreset,SIGNAL(clicked()),this,SLOT(negatedResetClicked()));
  connect(exportTestbenchDlg.cb_synceable,SIGNAL(clicked()),this,SLOT(synchronousEnableClicked()));

  connect(exportTestbenchDlg.pb_select_basedir,SIGNAL(clicked()),this,SLOT(selectBasedirClicked()));
  connect(exportTestbenchDlg.le_basedir,SIGNAL(textChanged(QString)),this,SLOT(basedirPathChanged(QString)));

  connect(exportTestbenchDlg.pb_select_testbench,SIGNAL(clicked()),this,SLOT(selectTestbenchClicked()));
  connect(exportTestbenchDlg.pb_select_package,SIGNAL(clicked()),this,SLOT(selectPackageClicked()));
  connect(exportTestbenchDlg.pb_select_testvector,SIGNAL(clicked()),this,SLOT(selectTestvectorClicked()));
  connect(exportTestbenchDlg.pb_select_logfile,SIGNAL(clicked()),this,SLOT(selectLogfileClicked()));
  connect(exportTestbenchDlg.le_testbench,SIGNAL(textChanged(QString)),this,SLOT(testbenchPathChanged(QString)));
  connect(exportTestbenchDlg.le_testvector,SIGNAL(textChanged(QString)),this,SLOT(testvectorPathChanged(QString)));
  connect(exportTestbenchDlg.le_package,SIGNAL(textChanged(QString)),this,SLOT(packagePathChanged(QString)));
  connect(exportTestbenchDlg.le_logfile,SIGNAL(textChanged(QString)),this,SLOT(logfilePathChanged(QString)));

  connect(file_dialog,SIGNAL(directoryEntered(QString)),this,SLOT(setFileDialogDirectory(QString)));

}

/**
 *  Destroys the object and frees any allocated resources
 */
ExportTestbenchDlgImpl::~ExportTestbenchDlgImpl()
{
    // no need to delete child widgets, Qt does it all for us
}


/**
 *  Set the std logic property
 */
void ExportTestbenchDlgImpl::useStdLogicClicked()
{
  stdlogic = exportTestbenchDlg.cb_stdlogic->isChecked();
}

/**
 *  Set the io header property
 */
void ExportTestbenchDlgImpl::ioHeaderClicked()
{
  io_header = exportTestbenchDlg.cb_iodesc->isChecked();
}

/**
 *  Shows the "Open Directory"-Dialog for the base export directory and
 *  writes the file name into the base directory line edit
 */
void ExportTestbenchDlgImpl::selectBasedirClicked()
{
  QString testbenchName;
  QString testvectorName;
  QString packageName;
  QString logfileName;

  base_directory=QFileDialog::getExistingDirectory(this,"",base_directory);

  if(base_directory.length()>0)
  {
    exportTestbenchDlg.le_basedir->setText(base_directory);

/*
    testbenchName="src/t_"+base_name+".vhd";
    testvectorName="stimuli/"+base_name+".vec";
    packageName="src/p_"+base_name+".vhd";
    logfileName="log/result.log";

    exportTestbenchDlg.le_testbench->setText(testbenchName);
    exportTestbenchDlg.le_package->setText(packageName);
    exportTestbenchDlg.le_testvector->setText(testvectorName);
    exportTestbenchDlg.le_logfile->setText(logfileName);*/

  }
}

/**
 *  Updates the base directory name when the name has changed
 */
void ExportTestbenchDlgImpl::basedirPathChanged(QString)
{
  QDir dir;

  base_directory=exportTestbenchDlg.le_basedir->text();

    if(base_directory[base_directory.length()-1]!='/')
      base_directory.append('/');

  if(dir.exists(base_directory))
  {
    exportTestbenchDlg.le_testbench->setEnabled(true);
    exportTestbenchDlg.le_testvector->setEnabled(true);
    exportTestbenchDlg.le_package->setEnabled(true);
    exportTestbenchDlg.le_logfile->setEnabled(true);
    exportTestbenchDlg.pb_select_package->setEnabled(true);
    exportTestbenchDlg.pb_select_testbench->setEnabled(true);
    exportTestbenchDlg.pb_select_testvector->setEnabled(true);
    exportTestbenchDlg.pb_select_logfile->setEnabled(true);
  }
  else {
    exportTestbenchDlg.le_testbench->setEnabled(false);
    exportTestbenchDlg.le_testvector->setEnabled(false);
    exportTestbenchDlg.le_package->setEnabled(false);
    exportTestbenchDlg.le_logfile->setEnabled(false);
    exportTestbenchDlg.pb_select_package->setEnabled(false);
    exportTestbenchDlg.pb_select_testbench->setEnabled(false);
    exportTestbenchDlg.pb_select_testvector->setEnabled(false);
    exportTestbenchDlg.pb_select_logfile->setEnabled(false);
  }

}


/**
 *  Shows the "Save File"-Dialog for the testbench file name and
 *  writes the file name into the testbench line edit
 */
void ExportTestbenchDlgImpl::selectTestbenchClicked()
{

  //  testbench_vhdl_path=QFileDialog::getSaveFileName(this,"","","VHDL Files (*.vhd *.vhdl);;All Files (*.*)");
  file_dialog->setNameFilter(tr("VHDL Files (*.vhd *.vhdl);;All Files (*.*)"));
  QStringList fileNames;
  if (file_dialog->exec())
     fileNames = file_dialog->selectedFiles();
  else return;

  testbench_vhdl_path=fileNames.at(0).right(fileNames.at(0).length()-base_directory.length());


  if(testbench_vhdl_path.right(testbench_vhdl_path.length()-testbench_vhdl_path.lastIndexOf("/")-1).find(".")<0)
    testbench_vhdl_path.append(".vhd");

  if(testbench_vhdl_path.length()>0)
    exportTestbenchDlg.le_testbench->setText(testbench_vhdl_path);


}

/**
 *  Sets the 'synchronous reset' property
 */
void ExportTestbenchDlgImpl::synchronousResetClicked()
{
  synchronousreset=exportTestbenchDlg.cb_syncreset->isChecked();

}


/**
 *  Sets the 'synchronous enable' property
 */
void ExportTestbenchDlgImpl::synchronousEnableClicked()
{
  synchronousenable=exportTestbenchDlg.cb_synceable->isChecked();
}


/**
 *  Sets the 'negated reset' property
 */
void ExportTestbenchDlgImpl::negatedResetClicked()
{
  negatedreset=exportTestbenchDlg.cb_negatedreset->isChecked();

}


/**
 *  Sets the 'synchronous reset' property
 */
void ExportTestbenchDlgImpl::ioNamesClicked()
{
  io_names=exportTestbenchDlg.cb_ionames->isChecked();

}


/**
 *  Updates the testvector file name when the testbench file name has changed
 */
void ExportTestbenchDlgImpl::testbenchPathChanged(QString)
{
  testbench_vhdl_path=exportTestbenchDlg.le_testbench->text();
}

/**
 *  Updates the testvector file name when the testbench file name has changed
 */
void ExportTestbenchDlgImpl::selectPackageClicked()
{

  package_vhdl_path=QFileDialog::getSaveFileName(this,"","","VHDL Files (*.vhd *.vhdl);;All Files (*.*)");

  if(package_vhdl_path.right(package_vhdl_path.length()-package_vhdl_path.lastIndexOf("/")-1).find(".")<0)
    package_vhdl_path.append(".vhd");

}

/**
 *  Updates the vhdl package file name
 */
void ExportTestbenchDlgImpl::packagePathChanged(QString)
{
  package_vhdl_path=exportTestbenchDlg.le_package->text();
}




/**
 *  Updates the testvector file name when the testbench file name has changed
 */
void ExportTestbenchDlgImpl::selectTestvectorClicked()
{

//  testvector_ascii_path=QFileDialog::getSaveFileName(this,"","","VHDL Files (*.vhd *.vhdl);;All Files (*.*)");

    file_dialog->setNameFilter(tr("Testvector Files (*.vec);;All Files (*.*)"));
  QStringList fileNames;
  if (file_dialog->exec())
     fileNames = file_dialog->selectedFiles();
  else return;


  if(testvector_ascii_path.right(testvector_ascii_path.length()-testvector_ascii_path.lastIndexOf("/")-1).find(".")<0)
    testvector_ascii_path.append(".vec");
;
}

/**
 *  Updates the testvector file name
 */
void ExportTestbenchDlgImpl::testvectorPathChanged(QString)
{
  testvector_ascii_path=exportTestbenchDlg.le_testvector->text();
}

/**
 *  Updates the logfile name when the logfile name has changed
 */
void ExportTestbenchDlgImpl::selectLogfileClicked()
{
  file_dialog->setNameFilter(tr("Logfiles (*.log);;All Files (*.*)"));
  QStringList fileNames;
  if (file_dialog->exec())
     fileNames = file_dialog->selectedFiles();
  else return;

  if(logfile_path.right(logfile_path.length()-logfile_path.lastIndexOf("/")-1).find(".")<0)
    logfile_path.append(".vec");
}


/**
 *  Updates the logfile name
 */
void ExportTestbenchDlgImpl::logfilePathChanged(QString)
{
  logfile_path=exportTestbenchDlg.le_logfile->text();
}


/**
 *  Force file dialog to stay in working directory
 */
void ExportTestbenchDlgImpl::setFileDialogDirectory(QString dir)
{

  if(dir.indexOf(base_directory)!=0)
    file_dialog->setDirectory(base_directory);


}



/**
 * Initialises the dialog according to the current options @a opt.
 */
void ExportTestbenchDlgImpl::init(Options* opt, Machine* m)
{
    stdlogic=opt->getTestbenchStdLogic();
    io_header=opt->getTestbenchIOHeader();
    io_names=opt->getTestbenchIONames();
    synchronousenable=opt->getTestbenchSynchronousEnable();
    synchronousreset=opt->getTestbenchSynchronousReset();
    negatedreset=opt->getTestbenchNegatedReset();
//    testbench_vhdl_path=opt->getTestbenchVHDLPath();
//    testvector_ascii_path=opt->getTestvectorASCIIPath();
//    logfile_path=opt->getTestbenchLogfilePath();
//    package_vhdl_path=opt->getTestpackageVHDLPath();
    if(m!=NULL)
      base_name = m->getName();
    else base_name="";

    exportTestbenchDlg.cb_stdlogic->setChecked(stdlogic);
    exportTestbenchDlg.cb_iodesc->setChecked(io_header);
    exportTestbenchDlg.cb_ionames->setChecked(io_names);
    exportTestbenchDlg.cb_negatedreset->setChecked(negatedreset);
    exportTestbenchDlg.cb_synceable->setChecked(synchronousenable);
    exportTestbenchDlg.cb_syncreset->setChecked(synchronousreset);
//    exportTestbenchDlg.le_testbench->setText(testbench_vhdl_path);
//    exportTestbenchDlg.le_testvector->setText(testvector_ascii_path);
//    exportTestbenchDlg.le_package->setText(package_vhdl_path);
//    exportTestbenchDlg.le_logfile->setText(logfile_path);

    exportTestbenchDlg.le_testbench->setText("src/t_"+base_name+".vhd");
    exportTestbenchDlg.le_testvector->setText("stimuli/"+base_name+"_stimuli.vec");
    exportTestbenchDlg.le_package->setText("src/p_"+base_name+".vhd");
    exportTestbenchDlg.le_logfile->setText("log/"+base_name+"_result.log");


}



