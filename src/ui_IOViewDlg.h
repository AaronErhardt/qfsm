/********************************************************************************
** Form generated from reading UI file 'IOViewDlg.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IOVIEWDLG_H
#define UI_IOVIEWDLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QTextBrowser>
#include <QtGui/QVBoxLayout>
#include "WSpinBox.h"

QT_BEGIN_NAMESPACE

class Ui_IOViewDlg
{
public:
    QVBoxLayout *vboxLayout;
    QTextBrowser *textBrowser;

    void setupUi(QDialog *IOViewDlg)
    {
        if (IOViewDlg->objectName().isEmpty())
            IOViewDlg->setObjectName(QString::fromUtf8("IOViewDlg"));
        IOViewDlg->setWindowModality(Qt::NonModal);
        IOViewDlg->resize(210, 152);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(1);
        sizePolicy.setHeightForWidth(IOViewDlg->sizePolicy().hasHeightForWidth());
        IOViewDlg->setSizePolicy(sizePolicy);
        IOViewDlg->setMinimumSize(QSize(0, 0));
        IOViewDlg->setMaximumSize(QSize(800, 600));
        IOViewDlg->setSizeGripEnabled(false);
        vboxLayout = new QVBoxLayout(IOViewDlg);
        vboxLayout->setSpacing(6);
        vboxLayout->setContentsMargins(11, 11, 11, 11);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        textBrowser = new QTextBrowser(IOViewDlg);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        sizePolicy.setHeightForWidth(textBrowser->sizePolicy().hasHeightForWidth());
        textBrowser->setSizePolicy(sizePolicy);
        textBrowser->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        textBrowser->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        textBrowser->setLineWrapMode(QTextEdit::NoWrap);

        vboxLayout->addWidget(textBrowser);


        retranslateUi(IOViewDlg);

        QMetaObject::connectSlotsByName(IOViewDlg);
    } // setupUi

    void retranslateUi(QDialog *IOViewDlg)
    {
        IOViewDlg->setWindowTitle(QApplication::translate("IOViewDlg", "IOView", 0, QApplication::UnicodeUTF8));
        textBrowser->setHtml(QApplication::translate("IOViewDlg", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans Serif'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'DejaVu Sans'; font-weight:600;\">Inputs:</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'DejaVu Sans'; font-weight:600;\">Moore Outputs:</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'DejaVu Sans'; font-weight:600;\">Mealy Outputs:</span></p></body></html>", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class IOViewDlg: public Ui_IOViewDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IOVIEWDLG_H
