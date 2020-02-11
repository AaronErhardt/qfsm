/********************************************************************************
** Form generated from reading UI file 'ExportTestbenchDlg.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EXPORTTESTBENCHDLG_H
#define UI_EXPORTTESTBENCHDLG_H

#include <Qt3Support/Q3MimeSourceFactory>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ExportTestbenchDlg
{
public:
    QVBoxLayout *vboxLayout;
    QHBoxLayout *hboxLayout;
    QSpacerItem *spacerItem;
    QVBoxLayout *vboxLayout1;
    QCheckBox *cb_stdlogic;
    QCheckBox *cb_iodesc;
    QCheckBox *cb_syncreset;
    QCheckBox *cb_synceable;
    QCheckBox *cb_negatedreset;
    QCheckBox *cb_ionames;
    QSpacerItem *spacerItem1;
    QGridLayout *gridLayout;
    QLabel *l_testbench;
    QLabel *l_testvector;
    QLineEdit *le_testbench;
    QLineEdit *le_testvector;
    QPushButton *pb_select_testbench;
    QLabel *l_package;
    QLineEdit *le_package;
    QPushButton *pb_select_testvector;
    QPushButton *pb_select_package;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *horizontalSpacer_5;
    QSpacerItem *horizontalSpacer_6;
    QSpacerItem *horizontalSpacer_7;
    QSpacerItem *horizontalSpacer_8;
    QSpacerItem *horizontalSpacer_9;
    QPushButton *pb_select_basedir;
    QLineEdit *le_basedir;
    QLabel *l_basedir;
    QLineEdit *le_logfile;
    QLabel *l_logfile;
    QPushButton *pb_select_logfile;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *hboxLayout1;
    QSpacerItem *spacerItem2;
    QPushButton *pb_export;
    QSpacerItem *spacerItem3;
    QPushButton *pb_cancel;
    QSpacerItem *spacerItem4;

    void setupUi(QDialog *ExportTestbenchDlg)
    {
        if (ExportTestbenchDlg->objectName().isEmpty())
            ExportTestbenchDlg->setObjectName(QString::fromUtf8("ExportTestbenchDlg"));
        ExportTestbenchDlg->resize(442, 510);
        vboxLayout = new QVBoxLayout(ExportTestbenchDlg);
        vboxLayout->setSpacing(6);
        vboxLayout->setContentsMargins(11, 11, 11, 11);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        hboxLayout = new QHBoxLayout();
        hboxLayout->setSpacing(6);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        spacerItem = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem);

        vboxLayout1 = new QVBoxLayout();
        vboxLayout1->setSpacing(6);
        vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
        cb_stdlogic = new QCheckBox(ExportTestbenchDlg);
        cb_stdlogic->setObjectName(QString::fromUtf8("cb_stdlogic"));
        cb_stdlogic->setEnabled(true);

        vboxLayout1->addWidget(cb_stdlogic);

        cb_iodesc = new QCheckBox(ExportTestbenchDlg);
        cb_iodesc->setObjectName(QString::fromUtf8("cb_iodesc"));

        vboxLayout1->addWidget(cb_iodesc);

        cb_syncreset = new QCheckBox(ExportTestbenchDlg);
        cb_syncreset->setObjectName(QString::fromUtf8("cb_syncreset"));

        vboxLayout1->addWidget(cb_syncreset);

        cb_synceable = new QCheckBox(ExportTestbenchDlg);
        cb_synceable->setObjectName(QString::fromUtf8("cb_synceable"));

        vboxLayout1->addWidget(cb_synceable);

        cb_negatedreset = new QCheckBox(ExportTestbenchDlg);
        cb_negatedreset->setObjectName(QString::fromUtf8("cb_negatedreset"));

        vboxLayout1->addWidget(cb_negatedreset);

        cb_ionames = new QCheckBox(ExportTestbenchDlg);
        cb_ionames->setObjectName(QString::fromUtf8("cb_ionames"));

        vboxLayout1->addWidget(cb_ionames);


        hboxLayout->addLayout(vboxLayout1);

        spacerItem1 = new QSpacerItem(31, 115, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem1);


        vboxLayout->addLayout(hboxLayout);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        l_testbench = new QLabel(ExportTestbenchDlg);
        l_testbench->setObjectName(QString::fromUtf8("l_testbench"));

        gridLayout->addWidget(l_testbench, 2, 1, 1, 1);

        l_testvector = new QLabel(ExportTestbenchDlg);
        l_testvector->setObjectName(QString::fromUtf8("l_testvector"));

        gridLayout->addWidget(l_testvector, 4, 1, 1, 1);

        le_testbench = new QLineEdit(ExportTestbenchDlg);
        le_testbench->setObjectName(QString::fromUtf8("le_testbench"));
        le_testbench->setEnabled(false);

        gridLayout->addWidget(le_testbench, 3, 1, 1, 1);

        le_testvector = new QLineEdit(ExportTestbenchDlg);
        le_testvector->setObjectName(QString::fromUtf8("le_testvector"));
        le_testvector->setEnabled(false);
        le_testvector->setReadOnly(false);

        gridLayout->addWidget(le_testvector, 5, 1, 1, 1);

        pb_select_testbench = new QPushButton(ExportTestbenchDlg);
        pb_select_testbench->setObjectName(QString::fromUtf8("pb_select_testbench"));
        pb_select_testbench->setEnabled(false);

        gridLayout->addWidget(pb_select_testbench, 3, 2, 1, 1);

        l_package = new QLabel(ExportTestbenchDlg);
        l_package->setObjectName(QString::fromUtf8("l_package"));

        gridLayout->addWidget(l_package, 6, 1, 1, 1);

        le_package = new QLineEdit(ExportTestbenchDlg);
        le_package->setObjectName(QString::fromUtf8("le_package"));
        le_package->setEnabled(false);

        gridLayout->addWidget(le_package, 7, 1, 1, 1);

        pb_select_testvector = new QPushButton(ExportTestbenchDlg);
        pb_select_testvector->setObjectName(QString::fromUtf8("pb_select_testvector"));
        pb_select_testvector->setEnabled(false);

        gridLayout->addWidget(pb_select_testvector, 5, 2, 1, 1);

        pb_select_package = new QPushButton(ExportTestbenchDlg);
        pb_select_package->setObjectName(QString::fromUtf8("pb_select_package"));
        pb_select_package->setEnabled(false);

        gridLayout->addWidget(pb_select_package, 7, 2, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_4, 7, 0, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_5, 6, 0, 1, 1);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_6, 5, 0, 1, 1);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_7, 4, 0, 1, 1);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_8, 3, 0, 1, 1);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_9, 2, 0, 1, 1);

        pb_select_basedir = new QPushButton(ExportTestbenchDlg);
        pb_select_basedir->setObjectName(QString::fromUtf8("pb_select_basedir"));

        gridLayout->addWidget(pb_select_basedir, 1, 2, 1, 1);

        le_basedir = new QLineEdit(ExportTestbenchDlg);
        le_basedir->setObjectName(QString::fromUtf8("le_basedir"));

        gridLayout->addWidget(le_basedir, 1, 0, 1, 2);

        l_basedir = new QLabel(ExportTestbenchDlg);
        l_basedir->setObjectName(QString::fromUtf8("l_basedir"));

        gridLayout->addWidget(l_basedir, 0, 0, 1, 2);

        le_logfile = new QLineEdit(ExportTestbenchDlg);
        le_logfile->setObjectName(QString::fromUtf8("le_logfile"));
        le_logfile->setEnabled(false);

        gridLayout->addWidget(le_logfile, 9, 1, 1, 1);

        l_logfile = new QLabel(ExportTestbenchDlg);
        l_logfile->setObjectName(QString::fromUtf8("l_logfile"));

        gridLayout->addWidget(l_logfile, 8, 1, 1, 1);

        pb_select_logfile = new QPushButton(ExportTestbenchDlg);
        pb_select_logfile->setObjectName(QString::fromUtf8("pb_select_logfile"));
        pb_select_logfile->setEnabled(false);

        gridLayout->addWidget(pb_select_logfile, 9, 2, 1, 1);

        gridLayout->setColumnStretch(0, 1);

        vboxLayout->addLayout(gridLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vboxLayout->addItem(verticalSpacer);

        hboxLayout1 = new QHBoxLayout();
        hboxLayout1->setSpacing(6);
        hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
        spacerItem2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout1->addItem(spacerItem2);

        pb_export = new QPushButton(ExportTestbenchDlg);
        pb_export->setObjectName(QString::fromUtf8("pb_export"));
        pb_export->setDefault(true);

        hboxLayout1->addWidget(pb_export);

        spacerItem3 = new QSpacerItem(20, 16, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout1->addItem(spacerItem3);

        pb_cancel = new QPushButton(ExportTestbenchDlg);
        pb_cancel->setObjectName(QString::fromUtf8("pb_cancel"));

        hboxLayout1->addWidget(pb_cancel);

        spacerItem4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout1->addItem(spacerItem4);


        vboxLayout->addLayout(hboxLayout1);

        QWidget::setTabOrder(cb_stdlogic, cb_iodesc);
        QWidget::setTabOrder(cb_iodesc, pb_export);
        QWidget::setTabOrder(pb_export, pb_cancel);

        retranslateUi(ExportTestbenchDlg);
        QObject::connect(pb_export, SIGNAL(clicked()), ExportTestbenchDlg, SLOT(accept()));
        QObject::connect(pb_cancel, SIGNAL(clicked()), ExportTestbenchDlg, SLOT(reject()));

        QMetaObject::connectSlotsByName(ExportTestbenchDlg);
    } // setupUi

    void retranslateUi(QDialog *ExportTestbenchDlg)
    {
        ExportTestbenchDlg->setWindowTitle(QApplication::translate("ExportTestbenchDlg", "Testbench Export Options", 0, QApplication::UnicodeUTF8));
        cb_stdlogic->setText(QApplication::translate("ExportTestbenchDlg", "Use std_logic_1164 package ", 0, QApplication::UnicodeUTF8));
        cb_iodesc->setText(QApplication::translate("ExportTestbenchDlg", "Write I/O description into header", 0, QApplication::UnicodeUTF8));
        cb_syncreset->setText(QApplication::translate("ExportTestbenchDlg", "Synchronous reset", 0, QApplication::UnicodeUTF8));
        cb_synceable->setText(QApplication::translate("ExportTestbenchDlg", "Synchronous enable", 0, QApplication::UnicodeUTF8));
        cb_negatedreset->setText(QApplication::translate("ExportTestbenchDlg", "Negated reset", 0, QApplication::UnicodeUTF8));
        cb_ionames->setText(QApplication::translate("ExportTestbenchDlg", "Use input/output names", 0, QApplication::UnicodeUTF8));
        l_testbench->setText(QApplication::translate("ExportTestbenchDlg", "VHDL testbench file name", 0, QApplication::UnicodeUTF8));
        l_testvector->setText(QApplication::translate("ExportTestbenchDlg", "Testvector file name", 0, QApplication::UnicodeUTF8));
        pb_select_testbench->setText(QApplication::translate("ExportTestbenchDlg", "Select", 0, QApplication::UnicodeUTF8));
        l_package->setText(QApplication::translate("ExportTestbenchDlg", "VHDL subprogram package file name", 0, QApplication::UnicodeUTF8));
        pb_select_testvector->setText(QApplication::translate("ExportTestbenchDlg", "Select", 0, QApplication::UnicodeUTF8));
        pb_select_package->setText(QApplication::translate("ExportTestbenchDlg", "Select", 0, QApplication::UnicodeUTF8));
        pb_select_basedir->setText(QApplication::translate("ExportTestbenchDlg", "Select", 0, QApplication::UnicodeUTF8));
        l_basedir->setText(QApplication::translate("ExportTestbenchDlg", "Base directory", 0, QApplication::UnicodeUTF8));
        l_logfile->setText(QApplication::translate("ExportTestbenchDlg", "Log file directory", 0, QApplication::UnicodeUTF8));
        pb_select_logfile->setText(QApplication::translate("ExportTestbenchDlg", "Select", 0, QApplication::UnicodeUTF8));
        pb_export->setText(QApplication::translate("ExportTestbenchDlg", "Export", 0, QApplication::UnicodeUTF8));
        pb_cancel->setText(QApplication::translate("ExportTestbenchDlg", "Cancel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ExportTestbenchDlg: public Ui_ExportTestbenchDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EXPORTTESTBENCHDLG_H
