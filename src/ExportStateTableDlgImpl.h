/*
Qt 4 Port by Rainer Strobel

in method init:
removed setButton() call for QButtonGroup.
It does no longer exist in Qt 4
*/


#ifndef EXPORTSTATETABLEDLGIMPL_H
#define EXPORTSTATETABLEDLGIMPL_H
#include "ui_ExportStateTableDlg.h"

class Options;




class ExportStateTableDlgImpl : public QDialog
{
    Q_OBJECT
        
        
        Ui::ExportStateTableDlg exportStateTableDlg;


public:
    ExportStateTableDlgImpl( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, Qt::WFlags fl = 0 );
    ~ExportStateTableDlgImpl();

    bool getIncludeOutputs() { return includeout; };
    void setIncludeOutputs(bool io) { includeout = io; };
    bool getResolveInverted() { return resolve_inverted; };
    void setResolveInverted(bool ri) { resolve_inverted = ri; };
    int getOrientation() { return orientation; };
    void setOrientation(bool orient) { orientation = orient; };

    void init(Options* opt);

public slots:
    void includeOutputsClicked();
    void resolveInvertedClicked();
    void orientationClicked(int);


private:
    bool includeout;
    bool resolve_inverted;
    int orientation;
};

#endif // EXPORTSTATETABLEDLGIMPL_H
