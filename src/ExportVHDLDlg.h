#ifndef EXPORTVHDLDLG_H
#define EXPORTVHDLDLG_H

#include <qvariant.h>


#include <Qt3Support/Q3MimeSourceFactory>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

class Ui_ExportVHDLDlg
{
public:
    QVBoxLayout *vboxLayout;
    QHBoxLayout *hboxLayout;
    QSpacerItem *spacerItem;
    QVBoxLayout *vboxLayout1;
    QCheckBox *cb_symbolicstates;
    QCheckBox *cb_synchreset;
    QCheckBox *cb_stdlogic;
    QSpacerItem *spacerItem1;
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
    ExportVHDLDlg->resize(301, 165);
    vboxLayout = new QVBoxLayout(ExportVHDLDlg);
    vboxLayout->setSpacing(6);
    vboxLayout->setMargin(11);
    vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
    hboxLayout = new QHBoxLayout();
    hboxLayout->setSpacing(6);
    hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
    spacerItem = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    hboxLayout->addItem(spacerItem);

    vboxLayout1 = new QVBoxLayout();
    vboxLayout1->setSpacing(6);
    vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
    cb_symbolicstates = new QCheckBox(ExportVHDLDlg);
    cb_symbolicstates->setObjectName(QString::fromUtf8("cb_symbolicstates"));

    vboxLayout1->addWidget(cb_symbolicstates);

    cb_synchreset = new QCheckBox(ExportVHDLDlg);
    cb_synchreset->setObjectName(QString::fromUtf8("cb_synchreset"));

    vboxLayout1->addWidget(cb_synchreset);

    cb_stdlogic = new QCheckBox(ExportVHDLDlg);
    cb_stdlogic->setObjectName(QString::fromUtf8("cb_stdlogic"));

    vboxLayout1->addWidget(cb_stdlogic);


    hboxLayout->addLayout(vboxLayout1);

    spacerItem1 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    hboxLayout->addItem(spacerItem1);


    vboxLayout->addLayout(hboxLayout);

    spacerItem2 = new QSpacerItem(20, 16, QSizePolicy::Minimum, QSizePolicy::Expanding);

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


    retranslateUi(ExportVHDLDlg);
    QObject::connect(cb_symbolicstates, SIGNAL(clicked()), ExportVHDLDlg, SLOT(symbolicNamesClicked()));
    QObject::connect(cb_synchreset, SIGNAL(clicked()), ExportVHDLDlg, SLOT(synchronousResetClicked()));
    QObject::connect(cb_stdlogic, SIGNAL(clicked()), ExportVHDLDlg, SLOT(useStdLogicClicked()));
    QObject::connect(pb_export, SIGNAL(clicked()), ExportVHDLDlg, SLOT(accept()));
    QObject::connect(pb_cancel, SIGNAL(clicked()), ExportVHDLDlg, SLOT(reject()));

    QMetaObject::connectSlotsByName(ExportVHDLDlg);
    } // setupUi

    void retranslateUi(QDialog *ExportVHDLDlg)
    {
    ExportVHDLDlg->setWindowTitle(QApplication::translate("ExportVHDLDlg", "VHDL Export Options", 0, QApplication::UnicodeUTF8));
    cb_symbolicstates->setText(QApplication::translate("ExportVHDLDlg", "Use symbolic names for states", 0, QApplication::UnicodeUTF8));
    cb_synchreset->setText(QApplication::translate("ExportVHDLDlg", "Synchronous reset", 0, QApplication::UnicodeUTF8));
    cb_stdlogic->setText(QApplication::translate("ExportVHDLDlg", "Use std_logic_1164 package ", 0, QApplication::UnicodeUTF8));
    pb_export->setText(QApplication::translate("ExportVHDLDlg", "Export", 0, QApplication::UnicodeUTF8));
    pb_cancel->setText(QApplication::translate("ExportVHDLDlg", "Cancel", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(ExportVHDLDlg);
    } // retranslateUi

};

namespace Ui {
    class ExportVHDLDlg: public Ui_ExportVHDLDlg {};
} // namespace Ui

class ExportVHDLDlg : public QDialog, public Ui::ExportVHDLDlg
{
    Q_OBJECT

public:
    ExportVHDLDlg(QWidget* parent = 0, const char* name = 0, bool modal = false, Qt::WindowFlags fl = 0);
    ~ExportVHDLDlg();

public slots:
    virtual void symbolicNamesClicked();
    virtual void synchronousResetClicked();
    virtual void useStdLogicClicked();

protected slots:
    virtual void languageChange();

};

#endif // EXPORTVHDLDLG_H
