/********************************************************************************
** Form generated from reading UI file 'OptGeneralDlg.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OPTGENERALDLG_H
#define UI_OPTGENERALDLG_H

#include <Qt3Support/Q3MimeSourceFactory>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OptGeneralDlg
{
public:
    QWidget *Layout3;
    QVBoxLayout *vboxLayout;
    QHBoxLayout *hboxLayout;
    QLabel *TextLabel12;
    QComboBox *cmb_language;
    QSpacerItem *spacerItem;
    QLabel *TextLabel1;

    void setupUi(QDialog *OptGeneralDlg)
    {
        if (OptGeneralDlg->objectName().isEmpty())
            OptGeneralDlg->setObjectName(QString::fromUtf8("OptGeneralDlg"));
        OptGeneralDlg->resize(336, 234);
        Layout3 = new QWidget(OptGeneralDlg);
        Layout3->setObjectName(QString::fromUtf8("Layout3"));
        Layout3->setGeometry(QRect(10, 70, 306, 130));
        vboxLayout = new QVBoxLayout(Layout3);
        vboxLayout->setSpacing(6);
        vboxLayout->setContentsMargins(11, 11, 11, 11);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        vboxLayout->setContentsMargins(0, 0, 0, 0);
        hboxLayout = new QHBoxLayout();
        hboxLayout->setSpacing(6);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        TextLabel12 = new QLabel(Layout3);
        TextLabel12->setObjectName(QString::fromUtf8("TextLabel12"));
        TextLabel12->setWordWrap(false);

        hboxLayout->addWidget(TextLabel12);

        cmb_language = new QComboBox(Layout3);
        cmb_language->setObjectName(QString::fromUtf8("cmb_language"));

        hboxLayout->addWidget(cmb_language);


        vboxLayout->addLayout(hboxLayout);

        spacerItem = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vboxLayout->addItem(spacerItem);

        TextLabel1 = new QLabel(Layout3);
        TextLabel1->setObjectName(QString::fromUtf8("TextLabel1"));
        TextLabel1->setAlignment(Qt::AlignVCenter);
        TextLabel1->setWordWrap(true);

        vboxLayout->addWidget(TextLabel1);


        retranslateUi(OptGeneralDlg);

        QMetaObject::connectSlotsByName(OptGeneralDlg);
    } // setupUi

    void retranslateUi(QDialog *OptGeneralDlg)
    {
        OptGeneralDlg->setWindowTitle(QApplication::translate("OptGeneralDlg", "General", 0, QApplication::UnicodeUTF8));
        TextLabel12->setText(QApplication::translate("OptGeneralDlg", "Language:", 0, QApplication::UnicodeUTF8));
        TextLabel1->setText(QApplication::translate("OptGeneralDlg", "Language settings go into effect the next time you start Qfsm.", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class OptGeneralDlg: public Ui_OptGeneralDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPTGENERALDLG_H
