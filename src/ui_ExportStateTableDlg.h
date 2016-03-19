/********************************************************************************
** Form generated from reading UI file 'ExportStateTableDlg.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EXPORTSTATETABLEDLG_H
#define UI_EXPORTSTATETABLEDLG_H

#include <Qt3Support/Q3ButtonGroup>
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

class Ui_ExportStateTableDlg
{
public:
    QVBoxLayout *vboxLayout;
    QVBoxLayout *vboxLayout1;
    QHBoxLayout *hboxLayout;
    QSpacerItem *spacerItem;
    QVBoxLayout *vboxLayout2;
    QCheckBox *cb_includeout;
    QCheckBox *cb_resolve_invert;
    Q3ButtonGroup *bg_orientation;
    QVBoxLayout *vboxLayout3;
    QRadioButton *rb_orientation0;
    QRadioButton *rb_orientation1;
    QSpacerItem *spacerItem1;
    QSpacerItem *spacerItem2;
    QHBoxLayout *hboxLayout1;
    QSpacerItem *spacerItem3;
    QPushButton *pb_export;
    QSpacerItem *spacerItem4;
    QPushButton *pb_cancel;
    QSpacerItem *spacerItem5;

    void setupUi(QDialog *ExportStateTableDlg)
    {
        if (ExportStateTableDlg->objectName().isEmpty())
            ExportStateTableDlg->setObjectName(QString::fromUtf8("ExportStateTableDlg"));
        ExportStateTableDlg->resize(291, 203);
        vboxLayout = new QVBoxLayout(ExportStateTableDlg);
        vboxLayout->setSpacing(6);
        vboxLayout->setContentsMargins(11, 11, 11, 11);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        vboxLayout1 = new QVBoxLayout();
        vboxLayout1->setSpacing(6);
        vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
        hboxLayout = new QHBoxLayout();
        hboxLayout->setSpacing(6);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        spacerItem = new QSpacerItem(16, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem);

        vboxLayout2 = new QVBoxLayout();
        vboxLayout2->setSpacing(6);
        vboxLayout2->setObjectName(QString::fromUtf8("vboxLayout2"));
        cb_includeout = new QCheckBox(ExportStateTableDlg);
        cb_includeout->setObjectName(QString::fromUtf8("cb_includeout"));

        vboxLayout2->addWidget(cb_includeout);

        cb_resolve_invert = new QCheckBox(ExportStateTableDlg);
        cb_resolve_invert->setObjectName(QString::fromUtf8("cb_resolve_invert"));

        vboxLayout2->addWidget(cb_resolve_invert);

        bg_orientation = new Q3ButtonGroup(ExportStateTableDlg);
        bg_orientation->setObjectName(QString::fromUtf8("bg_orientation"));
        bg_orientation->setColumnLayout(0, Qt::Vertical);
        bg_orientation->layout()->setSpacing(6);
        bg_orientation->layout()->setContentsMargins(11, 11, 11, 11);
        vboxLayout3 = new QVBoxLayout();
        QBoxLayout *boxlayout = qobject_cast<QBoxLayout *>(bg_orientation->layout());
        if (boxlayout)
            boxlayout->addLayout(vboxLayout3);
        vboxLayout3->setAlignment(Qt::AlignTop);
        vboxLayout3->setObjectName(QString::fromUtf8("vboxLayout3"));
        rb_orientation0 = new QRadioButton(bg_orientation);
        rb_orientation0->setObjectName(QString::fromUtf8("rb_orientation0"));
        rb_orientation0->setChecked(true);

        vboxLayout3->addWidget(rb_orientation0);

        rb_orientation1 = new QRadioButton(bg_orientation);
        rb_orientation1->setObjectName(QString::fromUtf8("rb_orientation1"));

        vboxLayout3->addWidget(rb_orientation1);


        vboxLayout2->addWidget(bg_orientation);


        hboxLayout->addLayout(vboxLayout2);

        spacerItem1 = new QSpacerItem(44, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem1);


        vboxLayout1->addLayout(hboxLayout);

        spacerItem2 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vboxLayout1->addItem(spacerItem2);

        hboxLayout1 = new QHBoxLayout();
        hboxLayout1->setSpacing(6);
        hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
        spacerItem3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout1->addItem(spacerItem3);

        pb_export = new QPushButton(ExportStateTableDlg);
        pb_export->setObjectName(QString::fromUtf8("pb_export"));
        pb_export->setDefault(true);

        hboxLayout1->addWidget(pb_export);

        spacerItem4 = new QSpacerItem(20, 16, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout1->addItem(spacerItem4);

        pb_cancel = new QPushButton(ExportStateTableDlg);
        pb_cancel->setObjectName(QString::fromUtf8("pb_cancel"));

        hboxLayout1->addWidget(pb_cancel);

        spacerItem5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout1->addItem(spacerItem5);


        vboxLayout1->addLayout(hboxLayout1);


        vboxLayout->addLayout(vboxLayout1);

        QWidget::setTabOrder(cb_includeout, rb_orientation0);
        QWidget::setTabOrder(rb_orientation0, rb_orientation1);
        QWidget::setTabOrder(rb_orientation1, pb_export);
        QWidget::setTabOrder(pb_export, pb_cancel);

        retranslateUi(ExportStateTableDlg);
        QObject::connect(cb_includeout, SIGNAL(clicked()), ExportStateTableDlg, SLOT(includeOutputsClicked()));
        QObject::connect(pb_export, SIGNAL(clicked()), ExportStateTableDlg, SLOT(accept()));
        QObject::connect(pb_cancel, SIGNAL(clicked()), ExportStateTableDlg, SLOT(reject()));
        QObject::connect(bg_orientation, SIGNAL(clicked(int)), ExportStateTableDlg, SLOT(orientationClicked(int)));
        QObject::connect(cb_resolve_invert, SIGNAL(clicked()), ExportStateTableDlg, SLOT(resolveInvertedClicked()));

        QMetaObject::connectSlotsByName(ExportStateTableDlg);
    } // setupUi

    void retranslateUi(QDialog *ExportStateTableDlg)
    {
        ExportStateTableDlg->setWindowTitle(QApplication::translate("ExportStateTableDlg", "State Table Export Options", 0, QApplication::UnicodeUTF8));
        cb_includeout->setText(QApplication::translate("ExportStateTableDlg", "Include asyncronous output", 0, QApplication::UnicodeUTF8));
        cb_resolve_invert->setText(QApplication::translate("ExportStateTableDlg", "Resolve inverted conditions", 0, QApplication::UnicodeUTF8));
        bg_orientation->setTitle(QApplication::translate("ExportStateTableDlg", "Orientation", 0, QApplication::UnicodeUTF8));
        rb_orientation0->setText(QApplication::translate("ExportStateTableDlg", "Rows: States / Columns: Events", 0, QApplication::UnicodeUTF8));
        rb_orientation1->setText(QApplication::translate("ExportStateTableDlg", "Rows: Events / Columns: States", 0, QApplication::UnicodeUTF8));
        pb_export->setText(QApplication::translate("ExportStateTableDlg", "Export", 0, QApplication::UnicodeUTF8));
        pb_cancel->setText(QApplication::translate("ExportStateTableDlg", "Cancel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ExportStateTableDlg: public Ui_ExportStateTableDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EXPORTSTATETABLEDLG_H
