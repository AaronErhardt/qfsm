/********************************************************************************
** Form generated from reading UI file 'ICheckDlg.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ICHECKDLG_H
#define UI_ICHECKDLG_H

#include <Qt3Support/Q3ButtonGroup>
#include <Qt3Support/Q3GroupBox>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTextBrowser>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ICheckDlg
{
public:
    QVBoxLayout *vboxLayout;
    Q3ButtonGroup *ButtonGroup11;
    QHBoxLayout *hboxLayout;
    QGridLayout *gridLayout;
    QLabel *lb_transconnected_val;
    QLabel *lb_completeness_val;
    QLabel *lb_transconnected;
    QLabel *lb_statesreachable_val;
    QLabel *lb_deadlocks;
    QLabel *lb_statesreachable;
    QLabel *lb_completeness;
    QLabel *lb_unambcond;
    QLabel *pm_unambcond;
    QLabel *lb_startstate;
    QLabel *lb_endstatesreachable;
    QLabel *pm_endstate;
    QLabel *lb_endstatesreachable_val;
    QLabel *pm_startstate;
    QLabel *lb_endstate;
    QLabel *pm_deadlocks;
    QLabel *pm_statecodes;
    QLabel *lb_statecodes;
    QGroupBox *groupBox;
    QHBoxLayout *hboxLayout1;
    QTextBrowser *tb_protocol;
    QHBoxLayout *hboxLayout2;
    QSpacerItem *spacerItem;
    QPushButton *pb_ok;
    QSpacerItem *spacerItem1;

    void setupUi(QDialog *ICheckDlg)
    {
        if (ICheckDlg->objectName().isEmpty())
            ICheckDlg->setObjectName(QString::fromUtf8("ICheckDlg"));
        ICheckDlg->resize(374, 500);
        vboxLayout = new QVBoxLayout(ICheckDlg);
        vboxLayout->setSpacing(6);
        vboxLayout->setContentsMargins(11, 11, 11, 11);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        ButtonGroup11 = new Q3ButtonGroup(ICheckDlg);
        ButtonGroup11->setObjectName(QString::fromUtf8("ButtonGroup11"));
        ButtonGroup11->setMinimumSize(QSize(20, 20));
        ButtonGroup11->setColumnLayout(0, Qt::Vertical);
        ButtonGroup11->layout()->setSpacing(6);
        ButtonGroup11->layout()->setContentsMargins(11, 11, 11, 11);
        hboxLayout = new QHBoxLayout();
        QBoxLayout *boxlayout = qobject_cast<QBoxLayout *>(ButtonGroup11->layout());
        if (boxlayout)
            boxlayout->addLayout(hboxLayout);
        hboxLayout->setAlignment(Qt::AlignTop);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        lb_transconnected_val = new QLabel(ButtonGroup11);
        lb_transconnected_val->setObjectName(QString::fromUtf8("lb_transconnected_val"));
        lb_transconnected_val->setFrameShape(QFrame::Panel);
        lb_transconnected_val->setFrameShadow(QFrame::Sunken);
        lb_transconnected_val->setWordWrap(false);

        gridLayout->addWidget(lb_transconnected_val, 9, 0, 1, 1);

        lb_completeness_val = new QLabel(ButtonGroup11);
        lb_completeness_val->setObjectName(QString::fromUtf8("lb_completeness_val"));
        lb_completeness_val->setFrameShape(QFrame::Panel);
        lb_completeness_val->setFrameShadow(QFrame::Sunken);
        lb_completeness_val->setWordWrap(false);

        gridLayout->addWidget(lb_completeness_val, 6, 0, 1, 1);

        lb_transconnected = new QLabel(ButtonGroup11);
        lb_transconnected->setObjectName(QString::fromUtf8("lb_transconnected"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lb_transconnected->sizePolicy().hasHeightForWidth());
        lb_transconnected->setSizePolicy(sizePolicy);
        lb_transconnected->setWordWrap(false);

        gridLayout->addWidget(lb_transconnected, 9, 1, 1, 1);

        lb_statesreachable_val = new QLabel(ButtonGroup11);
        lb_statesreachable_val->setObjectName(QString::fromUtf8("lb_statesreachable_val"));
        lb_statesreachable_val->setFrameShape(QFrame::Panel);
        lb_statesreachable_val->setFrameShadow(QFrame::Sunken);
        lb_statesreachable_val->setWordWrap(false);

        gridLayout->addWidget(lb_statesreachable_val, 7, 0, 1, 1);

        lb_deadlocks = new QLabel(ButtonGroup11);
        lb_deadlocks->setObjectName(QString::fromUtf8("lb_deadlocks"));
        sizePolicy.setHeightForWidth(lb_deadlocks->sizePolicy().hasHeightForWidth());
        lb_deadlocks->setSizePolicy(sizePolicy);
        lb_deadlocks->setWordWrap(false);

        gridLayout->addWidget(lb_deadlocks, 3, 1, 1, 1);

        lb_statesreachable = new QLabel(ButtonGroup11);
        lb_statesreachable->setObjectName(QString::fromUtf8("lb_statesreachable"));
        sizePolicy.setHeightForWidth(lb_statesreachable->sizePolicy().hasHeightForWidth());
        lb_statesreachable->setSizePolicy(sizePolicy);
        lb_statesreachable->setWordWrap(false);

        gridLayout->addWidget(lb_statesreachable, 7, 1, 1, 1);

        lb_completeness = new QLabel(ButtonGroup11);
        lb_completeness->setObjectName(QString::fromUtf8("lb_completeness"));
        lb_completeness->setWordWrap(false);

        gridLayout->addWidget(lb_completeness, 6, 1, 1, 1);

        lb_unambcond = new QLabel(ButtonGroup11);
        lb_unambcond->setObjectName(QString::fromUtf8("lb_unambcond"));
        sizePolicy.setHeightForWidth(lb_unambcond->sizePolicy().hasHeightForWidth());
        lb_unambcond->setSizePolicy(sizePolicy);
        lb_unambcond->setWordWrap(false);

        gridLayout->addWidget(lb_unambcond, 0, 1, 1, 1);

        pm_unambcond = new QLabel(ButtonGroup11);
        pm_unambcond->setObjectName(QString::fromUtf8("pm_unambcond"));
        QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pm_unambcond->sizePolicy().hasHeightForWidth());
        pm_unambcond->setSizePolicy(sizePolicy1);
        pm_unambcond->setMinimumSize(QSize(20, 20));
        pm_unambcond->setMaximumSize(QSize(50, 50));
        pm_unambcond->setScaledContents(false);
        pm_unambcond->setAlignment(Qt::AlignCenter);
        pm_unambcond->setWordWrap(false);

        gridLayout->addWidget(pm_unambcond, 0, 0, 1, 1);

        lb_startstate = new QLabel(ButtonGroup11);
        lb_startstate->setObjectName(QString::fromUtf8("lb_startstate"));
        sizePolicy.setHeightForWidth(lb_startstate->sizePolicy().hasHeightForWidth());
        lb_startstate->setSizePolicy(sizePolicy);
        lb_startstate->setWordWrap(false);

        gridLayout->addWidget(lb_startstate, 1, 1, 1, 1);

        lb_endstatesreachable = new QLabel(ButtonGroup11);
        lb_endstatesreachable->setObjectName(QString::fromUtf8("lb_endstatesreachable"));
        sizePolicy.setHeightForWidth(lb_endstatesreachable->sizePolicy().hasHeightForWidth());
        lb_endstatesreachable->setSizePolicy(sizePolicy);
        lb_endstatesreachable->setWordWrap(false);

        gridLayout->addWidget(lb_endstatesreachable, 8, 1, 1, 1);

        pm_endstate = new QLabel(ButtonGroup11);
        pm_endstate->setObjectName(QString::fromUtf8("pm_endstate"));
        sizePolicy1.setHeightForWidth(pm_endstate->sizePolicy().hasHeightForWidth());
        pm_endstate->setSizePolicy(sizePolicy1);
        pm_endstate->setMinimumSize(QSize(20, 20));
        pm_endstate->setMaximumSize(QSize(50, 50));
        pm_endstate->setScaledContents(false);
        pm_endstate->setAlignment(Qt::AlignCenter);
        pm_endstate->setWordWrap(false);

        gridLayout->addWidget(pm_endstate, 2, 0, 1, 1);

        lb_endstatesreachable_val = new QLabel(ButtonGroup11);
        lb_endstatesreachable_val->setObjectName(QString::fromUtf8("lb_endstatesreachable_val"));
        lb_endstatesreachable_val->setFrameShape(QFrame::Panel);
        lb_endstatesreachable_val->setFrameShadow(QFrame::Sunken);
        lb_endstatesreachable_val->setWordWrap(false);

        gridLayout->addWidget(lb_endstatesreachable_val, 8, 0, 1, 1);

        pm_startstate = new QLabel(ButtonGroup11);
        pm_startstate->setObjectName(QString::fromUtf8("pm_startstate"));
        sizePolicy1.setHeightForWidth(pm_startstate->sizePolicy().hasHeightForWidth());
        pm_startstate->setSizePolicy(sizePolicy1);
        pm_startstate->setMinimumSize(QSize(20, 20));
        pm_startstate->setMaximumSize(QSize(50, 50));
        pm_startstate->setScaledContents(false);
        pm_startstate->setAlignment(Qt::AlignCenter);
        pm_startstate->setWordWrap(false);

        gridLayout->addWidget(pm_startstate, 1, 0, 1, 1);

        lb_endstate = new QLabel(ButtonGroup11);
        lb_endstate->setObjectName(QString::fromUtf8("lb_endstate"));
        sizePolicy.setHeightForWidth(lb_endstate->sizePolicy().hasHeightForWidth());
        lb_endstate->setSizePolicy(sizePolicy);
        lb_endstate->setWordWrap(false);

        gridLayout->addWidget(lb_endstate, 2, 1, 1, 1);

        pm_deadlocks = new QLabel(ButtonGroup11);
        pm_deadlocks->setObjectName(QString::fromUtf8("pm_deadlocks"));
        sizePolicy1.setHeightForWidth(pm_deadlocks->sizePolicy().hasHeightForWidth());
        pm_deadlocks->setSizePolicy(sizePolicy1);
        pm_deadlocks->setMinimumSize(QSize(20, 20));
        pm_deadlocks->setMaximumSize(QSize(50, 50));
        pm_deadlocks->setScaledContents(false);
        pm_deadlocks->setAlignment(Qt::AlignCenter);
        pm_deadlocks->setWordWrap(false);

        gridLayout->addWidget(pm_deadlocks, 3, 0, 1, 1);

        pm_statecodes = new QLabel(ButtonGroup11);
        pm_statecodes->setObjectName(QString::fromUtf8("pm_statecodes"));
        pm_statecodes->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(pm_statecodes, 4, 0, 1, 1);

        lb_statecodes = new QLabel(ButtonGroup11);
        lb_statecodes->setObjectName(QString::fromUtf8("lb_statecodes"));

        gridLayout->addWidget(lb_statecodes, 4, 1, 1, 1);


        hboxLayout->addLayout(gridLayout);


        vboxLayout->addWidget(ButtonGroup11);

        groupBox = new QGroupBox(ICheckDlg);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy2);
        hboxLayout1 = new QHBoxLayout(groupBox);
        hboxLayout1->setSpacing(6);
        hboxLayout1->setContentsMargins(11, 11, 11, 11);
        hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
        tb_protocol = new QTextBrowser(groupBox);
        tb_protocol->setObjectName(QString::fromUtf8("tb_protocol"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(tb_protocol->sizePolicy().hasHeightForWidth());
        tb_protocol->setSizePolicy(sizePolicy3);

        hboxLayout1->addWidget(tb_protocol);


        vboxLayout->addWidget(groupBox);

        hboxLayout2 = new QHBoxLayout();
        hboxLayout2->setSpacing(6);
        hboxLayout2->setContentsMargins(0, 0, 0, 0);
        hboxLayout2->setObjectName(QString::fromUtf8("hboxLayout2"));
        spacerItem = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout2->addItem(spacerItem);

        pb_ok = new QPushButton(ICheckDlg);
        pb_ok->setObjectName(QString::fromUtf8("pb_ok"));
        pb_ok->setDefault(true);

        hboxLayout2->addWidget(pb_ok);

        spacerItem1 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout2->addItem(spacerItem1);


        vboxLayout->addLayout(hboxLayout2);


        retranslateUi(ICheckDlg);
        QObject::connect(pb_ok, SIGNAL(clicked()), ICheckDlg, SLOT(accept()));

        QMetaObject::connectSlotsByName(ICheckDlg);
    } // setupUi

    void retranslateUi(QDialog *ICheckDlg)
    {
        ICheckDlg->setWindowTitle(QApplication::translate("ICheckDlg", "Integrity Check", 0, QApplication::UnicodeUTF8));
        ButtonGroup11->setTitle(QApplication::translate("ICheckDlg", "Result", 0, QApplication::UnicodeUTF8));
        lb_transconnected_val->setText(QApplication::translate("ICheckDlg", "100%", 0, QApplication::UnicodeUTF8));
        lb_completeness_val->setText(QApplication::translate("ICheckDlg", "100%", 0, QApplication::UnicodeUTF8));
        lb_transconnected->setText(QApplication::translate("ICheckDlg", "Transitions connected", 0, QApplication::UnicodeUTF8));
        lb_statesreachable_val->setText(QApplication::translate("ICheckDlg", "100%", 0, QApplication::UnicodeUTF8));
        lb_deadlocks->setText(QApplication::translate("ICheckDlg", "No dead locks", 0, QApplication::UnicodeUTF8));
        lb_statesreachable->setText(QApplication::translate("ICheckDlg", "States reachable", 0, QApplication::UnicodeUTF8));
        lb_completeness->setText(QApplication::translate("ICheckDlg", "Completeness", 0, QApplication::UnicodeUTF8));
        lb_unambcond->setText(QApplication::translate("ICheckDlg", "Unambiguous Conditions", 0, QApplication::UnicodeUTF8));
        lb_startstate->setText(QApplication::translate("ICheckDlg", "Initial state", 0, QApplication::UnicodeUTF8));
        lb_endstatesreachable->setText(QApplication::translate("ICheckDlg", "Final states reachable", 0, QApplication::UnicodeUTF8));
        lb_endstatesreachable_val->setText(QApplication::translate("ICheckDlg", "100%", 0, QApplication::UnicodeUTF8));
        lb_endstate->setText(QApplication::translate("ICheckDlg", "Final state", 0, QApplication::UnicodeUTF8));
        pm_statecodes->setText(QString());
        lb_statecodes->setText(QApplication::translate("ICheckDlg", "Unambiguous state codes", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("ICheckDlg", "Protocol", 0, QApplication::UnicodeUTF8));
        pb_ok->setText(QApplication::translate("ICheckDlg", "OK", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ICheckDlg: public Ui_ICheckDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ICHECKDLG_H
