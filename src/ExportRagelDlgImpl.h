
/*
Qt 4 Port by Rainer Strobel

*/


#ifndef EXPORTRAGELDLGIMPL_H
#define EXPORTRAGELDLGIMPL_H
#include "ui_ExportRagelDlg.h"

class Options;

class ExportRagelDlgImpl : public QDialog
{
    Q_OBJECT

        Ui::ExportRagelDlg exportRagelDlg;


public:
    ExportRagelDlgImpl( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, Qt::WFlags fl = 0 );
    ~ExportRagelDlgImpl();

    /// Returns the 'create action file' flag 
    bool getCreateAction() { return create_action; };
    /// Sets the 'create action file' flag 
    void setCreateAction(bool ca) { create_action = ca; };
    /// Returns the language of the action file to export
    int getLangAction() { return lang_action; };
    /// Sets the language of the action file to export
    void setLangAction(int la) { lang_action = la; };
    /// Returns the 'add default transitions' flag
    int getAddDefaultTransitions() { return add_default_transitions; };
    /// Sets the 'add default transitions' flag
    void setAddDefaultTransitions(int dt) { add_default_transitions = dt; };

    void init(Options* opt);

public slots:
    void createActionClicked();
    void langCClicked();
    void langJavaClicked();
    void langRubyClicked();
    void addDefaultTransClicked();

private:
    /// If TRUE create action file
    bool create_action;
    /// Language of action file. 0: C/C++   1: Java   2: Ruby
    int lang_action;
    /// If TRUE, temporarily adds a default transition to every state for exporting
    bool add_default_transitions;
};

#endif // EXPORTRAGELDLGIMPL_H
