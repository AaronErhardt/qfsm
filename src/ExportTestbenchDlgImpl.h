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

#ifndef EXPORTTESTBENCHDLGIMPL_H
#define EXPORTTESTBENCHDLGIMPL_H
#include "ui_ExportTestbenchDlg.h"

#include <QFileDialog>

class Options;
class Machine;

class ExportTestbenchDlgImpl : public QDialog
{
    Q_OBJECT
    Ui::ExportTestbenchDlg exportTestbenchDlg;
    QFileDialog selectTestFile;

public:
    ExportTestbenchDlgImpl( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, Qt::WFlags fl = 0 );
    ~ExportTestbenchDlgImpl();

    /// Returns the 'std_logic package' flag 
    bool getStdLogic() { return stdlogic; }
    /// Sets the 'std_logic package' flag 
    void setStdLogic(bool sl) { stdlogic = sl; }
    /// Returns the 'synchronous reset' flag
    bool getSynchronousReset() { return synchronousreset; }
    /// Sets the 'synchronous reset' flag
    void setSynchronousReset(bool sr) { synchronousreset = sr; }
    /// Returns the 'synchronous enable' flag
    bool getSynchronousEnable() { return synchronousenable; }
    /// Sets the 'synchronous enable' flag
    void setSynchronousEnable(bool se) { synchronousenable = se; }
    /// Returns the 'negated reset' flag
    bool getNegatedReset() { return negatedreset; }
    /// Sets the 'negated reset' flag
    void setNegatedReset(bool nr) { negatedreset = nr; }
    /// Returns the 'io names' flag
    bool getIONames() { return io_names; }
    /// Sets the 'synchronous reset' flag
    void setIONames(bool in) { io_names = in; }
    /// Returns the 'IO header' flag 
    bool getIOheader() { return io_header; }
    /// Sets the 'IO header' flag 
    void setIOheader(bool ioh) { io_header = ioh; }
    /// Returns the selected testbench generator algorithm
    int getAlgorithm() {return algorithm;}
    /// Sets the testbench generator algorithm
    void setAlgorithm(int a) {algorithm = a;}
    /// Returns the VHDL testbench path
    QString getTestbenchVHDLPath() {return testbench_vhdl_path;}
    /// Sets the VHDL testbench path
    void setTestbenchVHDLPath(QString path) {testbench_vhdl_path=path;}
    /// Returns the ASCII testvector path
    QString getTestvectorASCIIPath() {return testvector_ascii_path;}
    /// Sets the ASCII testvector path
    void setTestvectorASCIIPath(QString path) {testvector_ascii_path=path;}
    /// Returns the logfile path
    QString getLogfilePath() {return logfile_path;}
    /// Sets the logfile path
    void setLogfilePath(QString path) {logfile_path=path;}
    /// Returns the VHDL package path
    QString getPackageVHDLPath() {return package_vhdl_path;}
    /// Returns the testbench base directory
    QString getBaseDirectory() {return base_directory;}
    /// Sets the testbench base directory
    void setBaseDirectory(QString dir) {base_directory=dir;}

    /// Sets the VHDL package path
    void setPackageVHDLPath(QString path) {testvector_ascii_path=path;}

    void init(Options* opt, Machine* m);

public slots:
    void useStdLogicClicked();
    void ioHeaderClicked();
    void selectBasedirClicked();
    void synchronousResetClicked();
    void synchronousEnableClicked();
    void negatedResetClicked();
    void ioNamesClicked();
    void basedirPathChanged(QString);
    void selectTestbenchClicked();
    void selectTestvectorClicked();
    void selectPackageClicked();
    void selectLogfileClicked();
    void testbenchPathChanged(QString);
    void packagePathChanged(QString);
    void testvectorPathChanged(QString);
    void logfilePathChanged(QString);
    void setFileDialogDirectory(QString);

private:
    /// if TRUE use std_logic_1164 package
    bool stdlogic;
    /// if TRUE export testbench with synchronous reset
    bool synchronousreset;
    /// if TRUE export testbench with synchronous enable
    bool synchronousenable;
    /// if TRUE export testbench with negated reset
    bool negatedreset;
    /// if TRUE export testbench with input and output names
    bool io_names;
    /// if TRUE write input/output description into header
    bool io_header;
    /// testbench generator algorithm: 0: Use algorithm 0 1: Use algorithm 1
    int algorithm;
    /// base name for exported files
    QString base_name;
    /// base directory for all export files
    QString base_directory;
    /// testbench export file path
    QString testbench_vhdl_path;
    /// testvector export file path
    QString testvector_ascii_path;
    /// subprogram package export file path
    QString package_vhdl_path;
    /// logfile export file path
    QString logfile_path;
    /// save file dialog for export files
    QFileDialog *file_dialog;

};

#endif // EXPORTVHDLDLGIMPL_H
