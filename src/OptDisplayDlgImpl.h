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

#ifndef OPTDISPLAYDLGIMPL_H
#define OPTDISPLAYDLGIMPL_H

#include <qspinbox.h>
#include "ui_OptDisplayDlg.h"

class Options;

/**
 * @class OptDisplayDlgImpl
 * @brief Tab dialog for the display options.
 */
class OptDisplayDlgImpl : public QDialog
{
  Ui::OptDisplayDlg optDisplayDlg;
    Q_OBJECT

public:
    OptDisplayDlgImpl( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, Qt::WFlags fl = 0 );
    ~OptDisplayDlgImpl();

    /// Returns the color used to draw the grid
    QColor getGridColor() { return gridcolor; };
    /// Sets the grid color
    void setGridColor(QColor c) { gridcolor=c; };
    /// Returns the distance between the grid points
    int getGridSize() { return optDisplayDlg.sb_gridsize->value(); };
    /// Sets the distance between the grid points
    void setGridSize(int s) { optDisplayDlg.sb_gridsize->setValue(s); };
    /// Returns TRUE if shadows shall be displayed, otherwise FALSE
    bool getShadows() { return bshadows; };
    /// Sets/clears the 'display shadows' flag
    void setShadows(bool s) { bshadows = s; };
    /// Returns the color used to draw the shadows
    QColor getShadowColor() { return shadowcolor; };
    /// Sets the shadow color
    void setShadowColor(QColor c) { shadowcolor=c; };
    
    /// Returns TRUE if tooltips shall be shown, otherwise FALSE
    bool getToolTips() { return btooltips; };
    /// Sets/clears the 'show tooltips' flag
    void setToolTips(bool t) { btooltips = t; };
    /// Returns TRUE if ?/! shall be shown, otherwise FALSE
    bool getIOMark() { return iomark; };
    /// Sets/clears the 'show ?/!' flag
    void setIOMark(bool m) { iomark = m; };
    /// Returns TRUE if I/O names shall be shown over the transitions, otherwise FALSE
    bool getDisplayIONames() { return ionames; };
    /// Sets/clears the 'Display I/O names' flag
    void setDisplayIONames(bool dio) { ionames = dio; };
    /// Returns TRUE if a box around the I/O shall be drawn, otherwise FALSE
    bool getDrawBox() { return bdrawbox; };
    /// Sets/clears the 'Draw box' flag
    void setDrawBox(bool db) { bdrawbox = db; };

    /// Returns the initial transition descriptor
    QString getInitialDescriptor() { return initial_descriptor; };
    /// Sets the initial transition decsriptor to @a sd
    void setInitialDescriptor(QString sd) { initial_descriptor = sd; };
    /// Returns the inversion descriptor
    QString getInversionDescriptor() { return inversion_descriptor; };
    /// Sets the inversion decsriptor to @a id
    void setInversionDescriptor(QString id) { inversion_descriptor = id; };
    /// Returns the "any input" descriptor
    QString getAnyInputDescriptor() { return any_input_descriptor; };
    /// Sets the "any input" decsriptor to @a ad
    void setAnyInputDescriptor(QString ad) { any_input_descriptor = ad; };
    /// Returns the default transition descriptor
    QString getDefaultDescriptor() { return default_descriptor; };
    /// Sets the default transition decsriptor to @a ad
    void setDefaultDesriptor(QString dd) { default_descriptor = dd; };

    void init(Options* );

public slots:
    void chooseGridColor();
    void tooltipsClicked();
    void ioMarkClicked();
    void startDescChanged();
    void inversionDescChanged();
    void anyInputDescChanged();
    void defaultDescChanged();
    void shadowsClicked();
    void chooseShadowColor();
    void ioNamesClicked();
    void drawBoxClicked();
 
private:
    /// Initial transition descriptor
    QString initial_descriptor;
    /// Inversion descriptor
    QString inversion_descriptor;
    /// "Any input" descriptor
    QString any_input_descriptor;
    /// Default transition descriptor
    QString default_descriptor;
    /// Grid color
    QColor gridcolor;
    /// If TRUE, tooltips are shown
    bool btooltips;
    /// Shadow color
    QColor shadowcolor;
    /// If TRUE, shadows are displayed
    bool bshadows;
    /// If TRUE, ? and ! are shown
    bool iomark;
    /// If TRUE, the input/output names are displayed over the transitions
    bool ionames;
    /// If TRUE a box is drawn around the inputs/outputs over a transition
    bool bdrawbox;
};

#endif // OPTDISPLAYDLGIMPL_H
