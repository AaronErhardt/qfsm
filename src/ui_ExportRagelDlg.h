/********************************************************************************
** Form generated from reading UI file 'ExportRagelDlg.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EXPORTRAGELDLG_H
#define UI_EXPORTRAGELDLG_H

#include <Qt3Support/Q3ButtonGroup>
#include <Qt3Support/Q3GroupBox>
#include <Qt3Support/Q3MimeSourceFactory>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ExportRagelDlg
{
public:
    QVBoxLayout *vboxLayout;
    QHBoxLayout *hboxLayout;
    QSpacerItem *spacerItem;
    QCheckBox *cb_actionfile;
    QSpacerItem *spacerItem1;
    Q3ButtonGroup *bg_lang;
    QHBoxLayout *hboxLayout1;
    QSpacerItem *spacerItem2;
    QVBoxLayout *vboxLayout1;
    QRadioButton *rb_C;
    QRadioButton *rb_java;
    QRadioButton *rb_ruby;
    QSpacerItem *spacerItem3;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QCheckBox *cb_adddefault;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *hboxLayout2;
    QSpacerItem *spacerItem4;
    QPushButton *pb_export;
    QSpacerItem *spacerItem5;
    QPushButton *pb_cancel;
    QSpacerItem *spacerItem6;

    void setupUi(QDialog *ExportRagelDlg)
    {
        if (ExportRagelDlg->objectName().isEmpty())
            ExportRagelDlg->setObjectName(QString::fromUtf8("ExportRagelDlg"));
        ExportRagelDlg->resize(337, 241);
        vboxLayout = new QVBoxLayout(ExportRagelDlg);
        vboxLayout->setSpacing(6);
        vboxLayout->setContentsMargins(11, 11, 11, 11);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        hboxLayout = new QHBoxLayout();
        hboxLayout->setSpacing(6);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        spacerItem = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem);

        cb_actionfile = new QCheckBox(ExportRagelDlg);
        cb_actionfile->setObjectName(QString::fromUtf8("cb_actionfile"));

        hboxLayout->addWidget(cb_actionfile);

        spacerItem1 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem1);


        vboxLayout->addLayout(hboxLayout);

        bg_lang = new Q3ButtonGroup(ExportRagelDlg);
        bg_lang->setObjectName(QString::fromUtf8("bg_lang"));
        bg_lang->setColumnLayout(0, Qt::Vertical);
        bg_lang->layout()->setSpacing(6);
        bg_lang->layout()->setContentsMargins(11, 11, 11, 11);
        hboxLayout1 = new QHBoxLayout();
        QBoxLayout *boxlayout = qobject_cast<QBoxLayout *>(bg_lang->layout());
        if (boxlayout)
            boxlayout->addLayout(hboxLayout1);
        hboxLayout1->setAlignment(Qt::AlignTop);
        hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
        spacerItem2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout1->addItem(spacerItem2);

        vboxLayout1 = new QVBoxLayout();
        vboxLayout1->setSpacing(6);
        vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
        rb_C = new QRadioButton(bg_lang);
        rb_C->setObjectName(QString::fromUtf8("rb_C"));
        rb_C->setChecked(true);

        vboxLayout1->addWidget(rb_C);

        rb_java = new QRadioButton(bg_lang);
        rb_java->setObjectName(QString::fromUtf8("rb_java"));

        vboxLayout1->addWidget(rb_java);

        rb_ruby = new QRadioButton(bg_lang);
        rb_ruby->setObjectName(QString::fromUtf8("rb_ruby"));

        vboxLayout1->addWidget(rb_ruby);


        hboxLayout1->addLayout(vboxLayout1);

        spacerItem3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout1->addItem(spacerItem3);


        vboxLayout->addWidget(bg_lang);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        cb_adddefault = new QCheckBox(ExportRagelDlg);
        cb_adddefault->setObjectName(QString::fromUtf8("cb_adddefault"));

        horizontalLayout->addWidget(cb_adddefault);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        vboxLayout->addLayout(horizontalLayout);

        hboxLayout2 = new QHBoxLayout();
        hboxLayout2->setSpacing(6);
        hboxLayout2->setObjectName(QString::fromUtf8("hboxLayout2"));
        spacerItem4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout2->addItem(spacerItem4);

        pb_export = new QPushButton(ExportRagelDlg);
        pb_export->setObjectName(QString::fromUtf8("pb_export"));
        pb_export->setDefault(true);

        hboxLayout2->addWidget(pb_export);

        spacerItem5 = new QSpacerItem(20, 16, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout2->addItem(spacerItem5);

        pb_cancel = new QPushButton(ExportRagelDlg);
        pb_cancel->setObjectName(QString::fromUtf8("pb_cancel"));

        hboxLayout2->addWidget(pb_cancel);

        spacerItem6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout2->addItem(spacerItem6);


        vboxLayout->addLayout(hboxLayout2);


        retranslateUi(ExportRagelDlg);
        QObject::connect(cb_actionfile, SIGNAL(clicked()), ExportRagelDlg, SLOT(createActionClicked()));
        QObject::connect(rb_C, SIGNAL(clicked()), ExportRagelDlg, SLOT(langCClicked()));
        QObject::connect(rb_java, SIGNAL(clicked()), ExportRagelDlg, SLOT(langJavaClicked()));
        QObject::connect(rb_ruby, SIGNAL(clicked()), ExportRagelDlg, SLOT(langRubyClicked()));
        QObject::connect(pb_export, SIGNAL(clicked()), ExportRagelDlg, SLOT(accept()));
        QObject::connect(pb_cancel, SIGNAL(clicked()), ExportRagelDlg, SLOT(reject()));
        QObject::connect(cb_adddefault, SIGNAL(clicked()), ExportRagelDlg, SLOT(addDefaultTransClicked()));

        QMetaObject::connectSlotsByName(ExportRagelDlg);
    } // setupUi

    void retranslateUi(QDialog *ExportRagelDlg)
    {
        ExportRagelDlg->setWindowTitle(QApplication::translate("ExportRagelDlg", "Ragel Export", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_WHATSTHIS
        cb_actionfile->setWhatsThis(QApplication::translate("ExportRagelDlg", "Creates a separate file containing a framework for actions/functions that are executed during or after the processing of the FSM.\n"
"This file is necessary to create code that can be compiled.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        cb_actionfile->setText(QApplication::translate("ExportRagelDlg", "Create action file", 0, QApplication::UnicodeUTF8));
        bg_lang->setTitle(QApplication::translate("ExportRagelDlg", "Language", 0, QApplication::UnicodeUTF8));
        rb_C->setText(QApplication::translate("ExportRagelDlg", "C / C++ / objective C", 0, QApplication::UnicodeUTF8));
        rb_java->setText(QApplication::translate("ExportRagelDlg", "Java", 0, QApplication::UnicodeUTF8));
        rb_ruby->setText(QApplication::translate("ExportRagelDlg", "Ruby", 0, QApplication::UnicodeUTF8));
        cb_adddefault->setText(QApplication::translate("ExportRagelDlg", "Add default transition loop to every state", 0, QApplication::UnicodeUTF8));
        pb_export->setText(QApplication::translate("ExportRagelDlg", "Export", 0, QApplication::UnicodeUTF8));
        pb_cancel->setText(QApplication::translate("ExportRagelDlg", "Cancel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ExportRagelDlg: public Ui_ExportRagelDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EXPORTRAGELDLG_H
