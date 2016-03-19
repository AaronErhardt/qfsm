#ifndef EXPORTVERILOGDLG_H
#define EXPORTVERILOGDLG_H

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

class Ui_ExportVerilogDlg
{
public:
    QVBoxLayout *vboxLayout;
    QHBoxLayout *hboxLayout;
    QSpacerItem *spacerItem;
    QVBoxLayout *vboxLayout1;
    QCheckBox *cb_synchreset;
    QSpacerItem *spacerItem1;
    QSpacerItem *spacerItem2;
    QHBoxLayout *hboxLayout1;
    QSpacerItem *spacerItem3;
    QPushButton *pb_export;
    QSpacerItem *spacerItem4;
    QPushButton *pb_cancel;
    QSpacerItem *spacerItem5;

    void setupUi(QDialog *ExportVerilogDlg)
    {
    if (ExportVerilogDlg->objectName().isEmpty())
        ExportVerilogDlg->setObjectName(QString::fromUtf8("ExportVerilogDlg"));
    ExportVerilogDlg->resize(336, 123);
    vboxLayout = new QVBoxLayout(ExportVerilogDlg);
    vboxLayout->setSpacing(6);
    vboxLayout->setMargin(11);
    vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
    hboxLayout = new QHBoxLayout();
    hboxLayout->setSpacing(6);
    hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
    spacerItem = new QSpacerItem(48, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    hboxLayout->addItem(spacerItem);

    vboxLayout1 = new QVBoxLayout();
    vboxLayout1->setSpacing(6);
    vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
    cb_synchreset = new QCheckBox(ExportVerilogDlg);
    cb_synchreset->setObjectName(QString::fromUtf8("cb_synchreset"));

    vboxLayout1->addWidget(cb_synchreset);


    hboxLayout->addLayout(vboxLayout1);

    spacerItem1 = new QSpacerItem(48, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    hboxLayout->addItem(spacerItem1);


    vboxLayout->addLayout(hboxLayout);

    spacerItem2 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

    vboxLayout->addItem(spacerItem2);

    hboxLayout1 = new QHBoxLayout();
    hboxLayout1->setSpacing(6);
    hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
    spacerItem3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    hboxLayout1->addItem(spacerItem3);

    pb_export = new QPushButton(ExportVerilogDlg);
    pb_export->setObjectName(QString::fromUtf8("pb_export"));
    pb_export->setDefault(true);

    hboxLayout1->addWidget(pb_export);

    spacerItem4 = new QSpacerItem(20, 16, QSizePolicy::Expanding, QSizePolicy::Minimum);

    hboxLayout1->addItem(spacerItem4);

    pb_cancel = new QPushButton(ExportVerilogDlg);
    pb_cancel->setObjectName(QString::fromUtf8("pb_cancel"));

    hboxLayout1->addWidget(pb_cancel);

    spacerItem5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    hboxLayout1->addItem(spacerItem5);


    vboxLayout->addLayout(hboxLayout1);


    retranslateUi(ExportVerilogDlg);
    QObject::connect(cb_synchreset, SIGNAL(clicked()), ExportVerilogDlg, SLOT(syncResetClicked()));
    QObject::connect(pb_export, SIGNAL(clicked()), ExportVerilogDlg, SLOT(accept()));
    QObject::connect(pb_cancel, SIGNAL(clicked()), ExportVerilogDlg, SLOT(reject()));

    QMetaObject::connectSlotsByName(ExportVerilogDlg);
    } // setupUi

    void retranslateUi(QDialog *ExportVerilogDlg)
    {
    ExportVerilogDlg->setWindowTitle(QApplication::translate("ExportVerilogDlg", "Verilog Export Options", 0, QApplication::UnicodeUTF8));
    cb_synchreset->setText(QApplication::translate("ExportVerilogDlg", "Synchronous reset", 0, QApplication::UnicodeUTF8));
    pb_export->setText(QApplication::translate("ExportVerilogDlg", "Export", 0, QApplication::UnicodeUTF8));
    pb_cancel->setText(QApplication::translate("ExportVerilogDlg", "Cancel", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(ExportVerilogDlg);
    } // retranslateUi

};

namespace Ui {
    class ExportVerilogDlg: public Ui_ExportVerilogDlg {};
} // namespace Ui

class ExportVerilogDlg : public QDialog, public Ui::ExportVerilogDlg
{
    Q_OBJECT

public:
    ExportVerilogDlg(QWidget* parent = 0, const char* name = 0, bool modal = false, Qt::WindowFlags fl = 0);
    ~ExportVerilogDlg();

public slots:
    virtual void syncResetClicked();
    virtual void registerOutClicked();

protected slots:
    virtual void languageChange();

};

#endif // EXPORTVERILOGDLG_H
