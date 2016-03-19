/********************************************************************************
** Form generated from reading UI file 'ExportVHDLDlg.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EXPORTVHDLDLG_H
#define UI_EXPORTVHDLDLG_H

#include <Qt3Support/Q3ButtonGroup>
#include <Qt3Support/Q3GroupBox>
#include <Qt3Support/Q3MimeSourceFactory>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTabWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ExportVHDLDlg
{
public:
    QVBoxLayout *vboxLayout;
    QTabWidget *tabWidget;
    QWidget *tab;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *spacerItem;
    QVBoxLayout *_2;
    QCheckBox *cb_inoutnames;
    QCheckBox *cb_synchreset;
    QCheckBox *cb_synchenable;
    QCheckBox *cb_stdlogic;
    QCheckBox *cb_negreset;
    QFrame *line;
    QLabel *l_entity_file;
    QHBoxLayout *horizontalLayout_5;
    QLineEdit *le_entity_file;
    QPushButton *pb_entity_file;
    QLabel *l_architecture_file;
    QHBoxLayout *horizontalLayout_4;
    QLineEdit *le_architecture_file;
    QPushButton *pb_architecture_file;
    QSpacerItem *verticalSpacer;
    QSpacerItem *spacerItem1;
    QWidget *tab_2;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QVBoxLayout *verticalLayout;
    QCheckBox *cb_symbolicstates;
    QCheckBox *cb_debugstate;
    QCheckBox *cb_iodesc;
    QCheckBox *cb_state_code;
    QCheckBox *cb_alliance;
    QCheckBox *cb_sep_files;
    QCheckBox *cb_look_ahead;
    QHBoxLayout *horizontalLayout_3;
    QLabel *l_architecture_name;
    QLineEdit *le_architecture_name;
    Q3ButtonGroup *bg_cond_notation;
    QVBoxLayout *verticalLayout_2;
    QRadioButton *rb_ifthen;
    QRadioButton *rb_casewhen;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *hboxLayout;
    QSpacerItem *spacerItem2;
    QHBoxLayout *hboxLayout1;
    QSpacerItem *spacerItem3;
    QPushButton *pb_export;
    QSpacerItem *spacerItem4;
    QPushButton *pb_cancel;
    QSpacerItem *spacerItem5;

    void setupUi(QDialog *ExportVHDLDlg)
    {
        if (ExportVHDLDlg->objectName().isEmpty())
            ExportVHDLDlg->setObjectName(QString::fromUtf8("ExportVHDLDlg"));
        ExportVHDLDlg->resize(397, 412);
        vboxLayout = new QVBoxLayout(ExportVHDLDlg);
        vboxLayout->setSpacing(6);
        vboxLayout->setContentsMargins(11, 11, 11, 11);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        tabWidget = new QTabWidget(ExportVHDLDlg);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        horizontalLayout = new QHBoxLayout(tab);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        spacerItem = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(spacerItem);

        _2 = new QVBoxLayout();
        _2->setSpacing(6);
        _2->setObjectName(QString::fromUtf8("_2"));
        cb_inoutnames = new QCheckBox(tab);
        cb_inoutnames->setObjectName(QString::fromUtf8("cb_inoutnames"));
        cb_inoutnames->setEnabled(true);

        _2->addWidget(cb_inoutnames);

        cb_synchreset = new QCheckBox(tab);
        cb_synchreset->setObjectName(QString::fromUtf8("cb_synchreset"));

        _2->addWidget(cb_synchreset);

        cb_synchenable = new QCheckBox(tab);
        cb_synchenable->setObjectName(QString::fromUtf8("cb_synchenable"));

        _2->addWidget(cb_synchenable);

        cb_stdlogic = new QCheckBox(tab);
        cb_stdlogic->setObjectName(QString::fromUtf8("cb_stdlogic"));
        cb_stdlogic->setEnabled(true);

        _2->addWidget(cb_stdlogic);

        cb_negreset = new QCheckBox(tab);
        cb_negreset->setObjectName(QString::fromUtf8("cb_negreset"));

        _2->addWidget(cb_negreset);

        line = new QFrame(tab);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        _2->addWidget(line);

        l_entity_file = new QLabel(tab);
        l_entity_file->setObjectName(QString::fromUtf8("l_entity_file"));

        _2->addWidget(l_entity_file);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        le_entity_file = new QLineEdit(tab);
        le_entity_file->setObjectName(QString::fromUtf8("le_entity_file"));

        horizontalLayout_5->addWidget(le_entity_file);

        pb_entity_file = new QPushButton(tab);
        pb_entity_file->setObjectName(QString::fromUtf8("pb_entity_file"));

        horizontalLayout_5->addWidget(pb_entity_file);


        _2->addLayout(horizontalLayout_5);

        l_architecture_file = new QLabel(tab);
        l_architecture_file->setObjectName(QString::fromUtf8("l_architecture_file"));

        _2->addWidget(l_architecture_file);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        le_architecture_file = new QLineEdit(tab);
        le_architecture_file->setObjectName(QString::fromUtf8("le_architecture_file"));

        horizontalLayout_4->addWidget(le_architecture_file);

        pb_architecture_file = new QPushButton(tab);
        pb_architecture_file->setObjectName(QString::fromUtf8("pb_architecture_file"));

        horizontalLayout_4->addWidget(pb_architecture_file);


        _2->addLayout(horizontalLayout_4);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        _2->addItem(verticalSpacer);


        horizontalLayout->addLayout(_2);

        spacerItem1 = new QSpacerItem(31, 115, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(spacerItem1);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        horizontalLayout_2 = new QHBoxLayout(tab_2);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        cb_symbolicstates = new QCheckBox(tab_2);
        cb_symbolicstates->setObjectName(QString::fromUtf8("cb_symbolicstates"));
        cb_symbolicstates->setEnabled(true);

        verticalLayout->addWidget(cb_symbolicstates);

        cb_debugstate = new QCheckBox(tab_2);
        cb_debugstate->setObjectName(QString::fromUtf8("cb_debugstate"));

        verticalLayout->addWidget(cb_debugstate);

        cb_iodesc = new QCheckBox(tab_2);
        cb_iodesc->setObjectName(QString::fromUtf8("cb_iodesc"));

        verticalLayout->addWidget(cb_iodesc);

        cb_state_code = new QCheckBox(tab_2);
        cb_state_code->setObjectName(QString::fromUtf8("cb_state_code"));

        verticalLayout->addWidget(cb_state_code);

        cb_alliance = new QCheckBox(tab_2);
        cb_alliance->setObjectName(QString::fromUtf8("cb_alliance"));

        verticalLayout->addWidget(cb_alliance);

        cb_sep_files = new QCheckBox(tab_2);
        cb_sep_files->setObjectName(QString::fromUtf8("cb_sep_files"));

        verticalLayout->addWidget(cb_sep_files);

        cb_look_ahead = new QCheckBox(tab_2);
        cb_look_ahead->setObjectName(QString::fromUtf8("cb_look_ahead"));

        verticalLayout->addWidget(cb_look_ahead);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        l_architecture_name = new QLabel(tab_2);
        l_architecture_name->setObjectName(QString::fromUtf8("l_architecture_name"));

        horizontalLayout_3->addWidget(l_architecture_name);

        le_architecture_name = new QLineEdit(tab_2);
        le_architecture_name->setObjectName(QString::fromUtf8("le_architecture_name"));

        horizontalLayout_3->addWidget(le_architecture_name);


        verticalLayout->addLayout(horizontalLayout_3);

        bg_cond_notation = new Q3ButtonGroup(tab_2);
        bg_cond_notation->setObjectName(QString::fromUtf8("bg_cond_notation"));
        bg_cond_notation->setColumnLayout(0, Qt::Vertical);
        bg_cond_notation->layout()->setSpacing(6);
        bg_cond_notation->layout()->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2 = new QVBoxLayout();
        QBoxLayout *boxlayout = qobject_cast<QBoxLayout *>(bg_cond_notation->layout());
        if (boxlayout)
            boxlayout->addLayout(verticalLayout_2);
        verticalLayout_2->setAlignment(Qt::AlignTop);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        rb_ifthen = new QRadioButton(bg_cond_notation);
        rb_ifthen->setObjectName(QString::fromUtf8("rb_ifthen"));
        rb_ifthen->setChecked(true);

        verticalLayout_2->addWidget(rb_ifthen);

        rb_casewhen = new QRadioButton(bg_cond_notation);
        rb_casewhen->setObjectName(QString::fromUtf8("rb_casewhen"));

        verticalLayout_2->addWidget(rb_casewhen);


        verticalLayout->addWidget(bg_cond_notation);


        horizontalLayout_2->addLayout(verticalLayout);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        tabWidget->addTab(tab_2, QString());

        vboxLayout->addWidget(tabWidget);

        hboxLayout = new QHBoxLayout();
        hboxLayout->setSpacing(6);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));

        vboxLayout->addLayout(hboxLayout);

        spacerItem2 = new QSpacerItem(346, 16, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vboxLayout->addItem(spacerItem2);

        hboxLayout1 = new QHBoxLayout();
        hboxLayout1->setSpacing(6);
        hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
        spacerItem3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout1->addItem(spacerItem3);

        pb_export = new QPushButton(ExportVHDLDlg);
        pb_export->setObjectName(QString::fromUtf8("pb_export"));
        pb_export->setDefault(true);

        hboxLayout1->addWidget(pb_export);

        spacerItem4 = new QSpacerItem(20, 16, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout1->addItem(spacerItem4);

        pb_cancel = new QPushButton(ExportVHDLDlg);
        pb_cancel->setObjectName(QString::fromUtf8("pb_cancel"));

        hboxLayout1->addWidget(pb_cancel);

        spacerItem5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout1->addItem(spacerItem5);


        vboxLayout->addLayout(hboxLayout1);

        QWidget::setTabOrder(pb_export, pb_cancel);

        retranslateUi(ExportVHDLDlg);
        QObject::connect(pb_export, SIGNAL(clicked()), ExportVHDLDlg, SLOT(accept()));
        QObject::connect(pb_cancel, SIGNAL(clicked()), ExportVHDLDlg, SLOT(reject()));

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(ExportVHDLDlg);
    } // setupUi

    void retranslateUi(QDialog *ExportVHDLDlg)
    {
        ExportVHDLDlg->setWindowTitle(QApplication::translate("ExportVHDLDlg", "VHDL Export Options", 0, QApplication::UnicodeUTF8));
        cb_inoutnames->setText(QApplication::translate("ExportVHDLDlg", "Use input/output names", 0, QApplication::UnicodeUTF8));
        cb_synchreset->setText(QApplication::translate("ExportVHDLDlg", "Synchronous reset", 0, QApplication::UnicodeUTF8));
        cb_synchenable->setText(QApplication::translate("ExportVHDLDlg", "Synchronous enable", 0, QApplication::UnicodeUTF8));
        cb_stdlogic->setText(QApplication::translate("ExportVHDLDlg", "Use std_logic_1164 package ", 0, QApplication::UnicodeUTF8));
        cb_negreset->setText(QApplication::translate("ExportVHDLDlg", "Negated reset", 0, QApplication::UnicodeUTF8));
        l_entity_file->setText(QApplication::translate("ExportVHDLDlg", "Export File Name", 0, QApplication::UnicodeUTF8));
        pb_entity_file->setText(QApplication::translate("ExportVHDLDlg", "Select", 0, QApplication::UnicodeUTF8));
        l_architecture_file->setText(QApplication::translate("ExportVHDLDlg", "Architecture File Name", 0, QApplication::UnicodeUTF8));
        pb_architecture_file->setText(QApplication::translate("ExportVHDLDlg", "Select", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("ExportVHDLDlg", "Basic", 0, QApplication::UnicodeUTF8));
        cb_symbolicstates->setText(QApplication::translate("ExportVHDLDlg", "Use symbolic names for states", 0, QApplication::UnicodeUTF8));
        cb_debugstate->setText(QApplication::translate("ExportVHDLDlg", "Add debug output state", 0, QApplication::UnicodeUTF8));
        cb_iodesc->setText(QApplication::translate("ExportVHDLDlg", "Write I/O description into header", 0, QApplication::UnicodeUTF8));
        cb_state_code->setText(QApplication::translate("ExportVHDLDlg", "Export state codes", 0, QApplication::UnicodeUTF8));
        cb_alliance->setText(QApplication::translate("ExportVHDLDlg", "Produce Alliance compliant code", 0, QApplication::UnicodeUTF8));
        cb_sep_files->setText(QApplication::translate("ExportVHDLDlg", "Separate files for Architecture and Entity", 0, QApplication::UnicodeUTF8));
        cb_look_ahead->setText(QApplication::translate("ExportVHDLDlg", "Synchronous look-ahead buffer", 0, QApplication::UnicodeUTF8));
        l_architecture_name->setText(QApplication::translate("ExportVHDLDlg", "Architecture name:", 0, QApplication::UnicodeUTF8));
        le_architecture_name->setText(QApplication::translate("ExportVHDLDlg", "behave", 0, QApplication::UnicodeUTF8));
        bg_cond_notation->setTitle(QApplication::translate("ExportVHDLDlg", "Transiton Conditions", 0, QApplication::UnicodeUTF8));
        rb_ifthen->setText(QApplication::translate("ExportVHDLDlg", "IF-THEN notation", 0, QApplication::UnicodeUTF8));
        rb_casewhen->setText(QApplication::translate("ExportVHDLDlg", "CASE-WHEN notation", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("ExportVHDLDlg", "Advanced", 0, QApplication::UnicodeUTF8));
        pb_export->setText(QApplication::translate("ExportVHDLDlg", "Export", 0, QApplication::UnicodeUTF8));
        pb_cancel->setText(QApplication::translate("ExportVHDLDlg", "Cancel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ExportVHDLDlg: public Ui_ExportVHDLDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EXPORTVHDLDLG_H
