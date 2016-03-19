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

Qt 3 iterators replaced by Qt 4 iterators

changed constructors of QFileDialog to Qt 4 format
replaced setSelection() by selectFile()
*/

#ifndef FILEIO_H
#define FILEIO_H

#include <qobject.h>
#include <qdir.h>
#include <qmap.h>
#include <QMessageBox>

class QFileDialog;
class QWidget;
class Project;
class MainWindow;
class Options;
class Import;
class Export;
class ScrollView;

/**
 * @class FileIO
 * @brief This class is responsible for all file input and output.
 *
 * It can load and save 'fsm'-files and the application options and stores the
 * file name of the actual file..
 */
class FileIO : public QObject
{
  Q_OBJECT
  public:
    FileIO(QWidget* );
    ~FileIO();

    //Project* openFile(QString mrufile=QString::null);  // deprecated
    Project* openFileXML(QString mrufile=QString::null);
    bool saveFile(Project* );
    bool saveFileAs(Project* );
    Project* importFile(Import* , ScrollView* sv=NULL );
    bool exportFile(Project* ,Export* , ScrollView* sv=NULL );
    int saveOptions(Options* );
    int loadOptions(Options* );
    bool loadMRU(QStringList& );
    bool saveMRU(QStringList );

    void setActFilePath(QString file) /// Sets actual file name.
      { act_file = file; }
    QString getActFilePath() /// Gets actual file name.
      { return act_file; }
    /// Returns the current file name
    QString getActFileName() { QFileInfo fi(act_file); return fi.fileName(); }
    /// Gets actual import file name.
    QString getActImportFilePath() { return act_importfile; }
    /// Returns the current import file name
    QString getActImportFileName() { QFileInfo fi(act_importfile); return fi.fileName(); }
    /// Returns the current import directory
    QString getImportDir() { return act_import_dir; }
    /// Returns the current export file name
    QString getActExportFileName() { QFileInfo fi(act_exportfile); return fi.fileName(); }
    /// Returns the current export directory
    QString getExportDir() { return act_export_dir; }
    /// Returns the string that represents an empty field (null value) in the options file
    QString getEmptyFieldString() { return "<none>"; }

  signals:
    /// Sets a statusbar message
    void sbMessage(QString);
    /// Sets the hourglass cursor
    void setWaitCursor();
    /// Resets the cursor to the previous one
    void setPreviousCursor();

  private:
    /// Creates the .qfsm directory
    QDir createQfsmDir();
    
    /// Pointer to the main window
    MainWindow* main;
    /// Messagebox that is opend when the user wants to save a file with abiguous state codes
    QMessageBox* mb_statecode;
    /// Current directory
    QDir act_dir;
    /// Current import directory
    QString act_import_dir;
    /// Current export directory
    QString act_export_dir;
    /// Current file name
    QString act_file;
    /// Current import file name
    QString act_importfile;
    /// Current export file name
    QString act_exportfile;
    /// File dialog
    QFileDialog* filedlg;
    /// File dialog (import)
    QFileDialog* importdlg;
    /// File dialog (export)
    QFileDialog* exportdlg;

    bool doSave(Project* );
    bool doSaveXML(Project* );
    void setOptions(QMap<QString, QString>* map, Options* opt);

};


#endif
