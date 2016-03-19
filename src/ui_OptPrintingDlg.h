/********************************************************************************
** Form generated from reading UI file 'OptPrintingDlg.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OPTPRINTINGDLG_H
#define UI_OPTPRINTINGDLG_H

#include <Qt3Support/Q3MimeSourceFactory>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_OptPrintingDlg
{
public:
    QHBoxLayout *hboxLayout;
    QCheckBox *cb_print_header;

    void setupUi(QDialog *OptPrintingDlg)
    {
        if (OptPrintingDlg->objectName().isEmpty())
            OptPrintingDlg->setObjectName(QString::fromUtf8("OptPrintingDlg"));
        OptPrintingDlg->resize(405, 282);
        hboxLayout = new QHBoxLayout(OptPrintingDlg);
        hboxLayout->setSpacing(6);
        hboxLayout->setContentsMargins(11, 11, 11, 11);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        cb_print_header = new QCheckBox(OptPrintingDlg);
        cb_print_header->setObjectName(QString::fromUtf8("cb_print_header"));

        hboxLayout->addWidget(cb_print_header);


        retranslateUi(OptPrintingDlg);
        QObject::connect(cb_print_header, SIGNAL(clicked()), OptPrintingDlg, SLOT(printHeaderClicked()));

        QMetaObject::connectSlotsByName(OptPrintingDlg);
    } // setupUi

    void retranslateUi(QDialog *OptPrintingDlg)
    {
        OptPrintingDlg->setWindowTitle(QApplication::translate("OptPrintingDlg", "Printing", 0, QApplication::UnicodeUTF8));
        cb_print_header->setText(QApplication::translate("OptPrintingDlg", "Print header", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class OptPrintingDlg: public Ui_OptPrintingDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPTPRINTINGDLG_H
