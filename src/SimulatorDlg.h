/********************************************************************************
** Form generated from reading UI file 'SimulatorDlg.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef SIMULATORDLG_H
#define SIMULATORDLG_H

#include <Qt3Support/Q3ButtonGroup>
#include <Qt3Support/Q3GroupBox>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include "WSpinBox.h"

QT_BEGIN_NAMESPACE

class Ui_SimulatorDlg
{
public:
    QVBoxLayout *vboxLayout;
    Q3GroupBox *GroupBox3;
    QVBoxLayout *vboxLayout1;
    QLineEdit *le_inputs;
    Q3ButtonGroup *ButtonGroup1;
    QHBoxLayout *hboxLayout;
    QHBoxLayout *hboxLayout1;
    QRadioButton *rb_ibin;
    QRadioButton *rb_ihex;
    QRadioButton *rb_iascii;
    QHBoxLayout *hboxLayout2;
    QPushButton *pb_bin15;
    QPushButton *pb_bin14;
    QPushButton *pb_bin13;
    QPushButton *pb_bin12;
    QPushButton *pb_bin11;
    QPushButton *pb_bin10;
    QPushButton *pb_bin9;
    QPushButton *pb_bin8;
    QPushButton *pb_bin7;
    QPushButton *pb_bin6;
    QPushButton *pb_bin5;
    QPushButton *pb_bin4;
    QPushButton *pb_bin3;
    QPushButton *pb_bin2;
    QPushButton *pb_bin1;
    QPushButton *pb_bin0;
    Q3GroupBox *GroupBox4;
    QVBoxLayout *vboxLayout2;
    QLabel *lb_outputs;
    Q3ButtonGroup *ButtonGroup2;
    QHBoxLayout *hboxLayout3;
    QHBoxLayout *hboxLayout4;
    QRadioButton *rb_obin;
    QRadioButton *rb_ohex;
    QRadioButton *rb_oascii;
    QHBoxLayout *hboxLayout5;
    QLabel *TextLabel1;
    QLabel *lb_sname;
    QLabel *pm_end;
    QHBoxLayout *hboxLayout6;
    QLabel *TextLabel3;
    QLabel *lb_scode;
    QHBoxLayout *hboxLayout7;
    QPushButton *pb_clock;
    QSpacerItem *spacerItem;
    QLabel *lb_frequency;
    WSpinBox *frequency;
    QHBoxLayout *hboxLayout8;
    QPushButton *pb_send;
    QSpacerItem *spacerItem1;
    QPushButton *pb_reset;
    QPushButton *pb_cancel;

    void setupUi(QDialog *SimulatorDlg)
    {
        if (SimulatorDlg->objectName().isEmpty())
            SimulatorDlg->setObjectName(QString::fromUtf8("SimulatorDlg"));
        SimulatorDlg->resize(427, 380);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(SimulatorDlg->sizePolicy().hasHeightForWidth());
        SimulatorDlg->setSizePolicy(sizePolicy);
        SimulatorDlg->setMinimumSize(QSize(250, 0));
        SimulatorDlg->setMaximumSize(QSize(800, 500));
        SimulatorDlg->setSizeGripEnabled(false);
        vboxLayout = new QVBoxLayout(SimulatorDlg);
        vboxLayout->setSpacing(6);
        vboxLayout->setContentsMargins(11, 11, 11, 11);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        GroupBox3 = new Q3GroupBox(SimulatorDlg);
        GroupBox3->setObjectName(QString::fromUtf8("GroupBox3"));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(GroupBox3->sizePolicy().hasHeightForWidth());
        GroupBox3->setSizePolicy(sizePolicy1);
        GroupBox3->setColumnLayout(0, Qt::Vertical);
        GroupBox3->layout()->setSpacing(6);
        GroupBox3->layout()->setContentsMargins(8, 8, 8, 8);
        vboxLayout1 = new QVBoxLayout();
        QBoxLayout *boxlayout = qobject_cast<QBoxLayout *>(GroupBox3->layout());
        if (boxlayout)
            boxlayout->addLayout(vboxLayout1);
        vboxLayout1->setAlignment(Qt::AlignTop);
        vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
        le_inputs = new QLineEdit(GroupBox3);
        le_inputs->setObjectName(QString::fromUtf8("le_inputs"));

        vboxLayout1->addWidget(le_inputs);

        ButtonGroup1 = new Q3ButtonGroup(GroupBox3);
        ButtonGroup1->setObjectName(QString::fromUtf8("ButtonGroup1"));
        ButtonGroup1->setMaximumSize(QSize(32767, 35));
        ButtonGroup1->setFrameShape(Q3GroupBox::NoFrame);
        ButtonGroup1->setColumnLayout(0, Qt::Vertical);
        ButtonGroup1->layout()->setSpacing(6);
        ButtonGroup1->layout()->setContentsMargins(0, 0, 0, 0);
        hboxLayout = new QHBoxLayout();
        QBoxLayout *boxlayout1 = qobject_cast<QBoxLayout *>(ButtonGroup1->layout());
        if (boxlayout1)
            boxlayout1->addLayout(hboxLayout);
        hboxLayout->setAlignment(Qt::AlignTop);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        hboxLayout1 = new QHBoxLayout();
        hboxLayout1->setSpacing(6);
        hboxLayout1->setContentsMargins(0, 0, 0, 0);
        hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
        rb_ibin = new QRadioButton(ButtonGroup1);
        rb_ibin->setObjectName(QString::fromUtf8("rb_ibin"));

        hboxLayout1->addWidget(rb_ibin);

        rb_ihex = new QRadioButton(ButtonGroup1);
        rb_ihex->setObjectName(QString::fromUtf8("rb_ihex"));

        hboxLayout1->addWidget(rb_ihex);

        rb_iascii = new QRadioButton(ButtonGroup1);
        rb_iascii->setObjectName(QString::fromUtf8("rb_iascii"));

        hboxLayout1->addWidget(rb_iascii);


        hboxLayout->addLayout(hboxLayout1);


        vboxLayout1->addWidget(ButtonGroup1);

        hboxLayout2 = new QHBoxLayout();
        hboxLayout2->setSpacing(2);
        hboxLayout2->setContentsMargins(0, 0, 0, 0);
        hboxLayout2->setObjectName(QString::fromUtf8("hboxLayout2"));
        pb_bin15 = new QPushButton(GroupBox3);
        pb_bin15->setObjectName(QString::fromUtf8("pb_bin15"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(pb_bin15->sizePolicy().hasHeightForWidth());
        pb_bin15->setSizePolicy(sizePolicy2);
        pb_bin15->setCheckable(true);

        hboxLayout2->addWidget(pb_bin15);

        pb_bin14 = new QPushButton(GroupBox3);
        pb_bin14->setObjectName(QString::fromUtf8("pb_bin14"));
        sizePolicy2.setHeightForWidth(pb_bin14->sizePolicy().hasHeightForWidth());
        pb_bin14->setSizePolicy(sizePolicy2);
        pb_bin14->setCheckable(true);

        hboxLayout2->addWidget(pb_bin14);

        pb_bin13 = new QPushButton(GroupBox3);
        pb_bin13->setObjectName(QString::fromUtf8("pb_bin13"));
        sizePolicy2.setHeightForWidth(pb_bin13->sizePolicy().hasHeightForWidth());
        pb_bin13->setSizePolicy(sizePolicy2);
        pb_bin13->setCheckable(true);

        hboxLayout2->addWidget(pb_bin13);

        pb_bin12 = new QPushButton(GroupBox3);
        pb_bin12->setObjectName(QString::fromUtf8("pb_bin12"));
        sizePolicy2.setHeightForWidth(pb_bin12->sizePolicy().hasHeightForWidth());
        pb_bin12->setSizePolicy(sizePolicy2);
        pb_bin12->setCheckable(true);

        hboxLayout2->addWidget(pb_bin12);

        pb_bin11 = new QPushButton(GroupBox3);
        pb_bin11->setObjectName(QString::fromUtf8("pb_bin11"));
        sizePolicy2.setHeightForWidth(pb_bin11->sizePolicy().hasHeightForWidth());
        pb_bin11->setSizePolicy(sizePolicy2);
        pb_bin11->setCheckable(true);

        hboxLayout2->addWidget(pb_bin11);

        pb_bin10 = new QPushButton(GroupBox3);
        pb_bin10->setObjectName(QString::fromUtf8("pb_bin10"));
        sizePolicy2.setHeightForWidth(pb_bin10->sizePolicy().hasHeightForWidth());
        pb_bin10->setSizePolicy(sizePolicy2);
        pb_bin10->setCheckable(true);

        hboxLayout2->addWidget(pb_bin10);

        pb_bin9 = new QPushButton(GroupBox3);
        pb_bin9->setObjectName(QString::fromUtf8("pb_bin9"));
        sizePolicy2.setHeightForWidth(pb_bin9->sizePolicy().hasHeightForWidth());
        pb_bin9->setSizePolicy(sizePolicy2);
        pb_bin9->setCheckable(true);

        hboxLayout2->addWidget(pb_bin9);

        pb_bin8 = new QPushButton(GroupBox3);
        pb_bin8->setObjectName(QString::fromUtf8("pb_bin8"));
        sizePolicy2.setHeightForWidth(pb_bin8->sizePolicy().hasHeightForWidth());
        pb_bin8->setSizePolicy(sizePolicy2);
        pb_bin8->setCheckable(true);

        hboxLayout2->addWidget(pb_bin8);

        pb_bin7 = new QPushButton(GroupBox3);
        pb_bin7->setObjectName(QString::fromUtf8("pb_bin7"));
        sizePolicy2.setHeightForWidth(pb_bin7->sizePolicy().hasHeightForWidth());
        pb_bin7->setSizePolicy(sizePolicy2);
        pb_bin7->setCheckable(true);

        hboxLayout2->addWidget(pb_bin7);

        pb_bin6 = new QPushButton(GroupBox3);
        pb_bin6->setObjectName(QString::fromUtf8("pb_bin6"));
        sizePolicy2.setHeightForWidth(pb_bin6->sizePolicy().hasHeightForWidth());
        pb_bin6->setSizePolicy(sizePolicy2);
        pb_bin6->setCheckable(true);

        hboxLayout2->addWidget(pb_bin6);

        pb_bin5 = new QPushButton(GroupBox3);
        pb_bin5->setObjectName(QString::fromUtf8("pb_bin5"));
        sizePolicy2.setHeightForWidth(pb_bin5->sizePolicy().hasHeightForWidth());
        pb_bin5->setSizePolicy(sizePolicy2);
        pb_bin5->setCheckable(true);

        hboxLayout2->addWidget(pb_bin5);

        pb_bin4 = new QPushButton(GroupBox3);
        pb_bin4->setObjectName(QString::fromUtf8("pb_bin4"));
        sizePolicy2.setHeightForWidth(pb_bin4->sizePolicy().hasHeightForWidth());
        pb_bin4->setSizePolicy(sizePolicy2);
        pb_bin4->setCheckable(true);

        hboxLayout2->addWidget(pb_bin4);

        pb_bin3 = new QPushButton(GroupBox3);
        pb_bin3->setObjectName(QString::fromUtf8("pb_bin3"));
        sizePolicy2.setHeightForWidth(pb_bin3->sizePolicy().hasHeightForWidth());
        pb_bin3->setSizePolicy(sizePolicy2);
        pb_bin3->setCheckable(true);

        hboxLayout2->addWidget(pb_bin3);

        pb_bin2 = new QPushButton(GroupBox3);
        pb_bin2->setObjectName(QString::fromUtf8("pb_bin2"));
        sizePolicy2.setHeightForWidth(pb_bin2->sizePolicy().hasHeightForWidth());
        pb_bin2->setSizePolicy(sizePolicy2);
        pb_bin2->setCheckable(true);

        hboxLayout2->addWidget(pb_bin2);

        pb_bin1 = new QPushButton(GroupBox3);
        pb_bin1->setObjectName(QString::fromUtf8("pb_bin1"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(pb_bin1->sizePolicy().hasHeightForWidth());
        pb_bin1->setSizePolicy(sizePolicy3);
        pb_bin1->setCheckable(true);

        hboxLayout2->addWidget(pb_bin1);

        pb_bin0 = new QPushButton(GroupBox3);
        pb_bin0->setObjectName(QString::fromUtf8("pb_bin0"));
        sizePolicy3.setHeightForWidth(pb_bin0->sizePolicy().hasHeightForWidth());
        pb_bin0->setSizePolicy(sizePolicy3);
        pb_bin0->setCheckable(true);

        hboxLayout2->addWidget(pb_bin0);


        vboxLayout1->addLayout(hboxLayout2);


        vboxLayout->addWidget(GroupBox3);

        GroupBox4 = new Q3GroupBox(SimulatorDlg);
        GroupBox4->setObjectName(QString::fromUtf8("GroupBox4"));
        GroupBox4->setColumnLayout(0, Qt::Vertical);
        GroupBox4->layout()->setSpacing(6);
        GroupBox4->layout()->setContentsMargins(8, 8, 8, 8);
        vboxLayout2 = new QVBoxLayout();
        QBoxLayout *boxlayout2 = qobject_cast<QBoxLayout *>(GroupBox4->layout());
        if (boxlayout2)
            boxlayout2->addLayout(vboxLayout2);
        vboxLayout2->setAlignment(Qt::AlignTop);
        vboxLayout2->setObjectName(QString::fromUtf8("vboxLayout2"));
        lb_outputs = new QLabel(GroupBox4);
        lb_outputs->setObjectName(QString::fromUtf8("lb_outputs"));
        lb_outputs->setFrameShape(QFrame::Panel);
        lb_outputs->setFrameShadow(QFrame::Sunken);
        lb_outputs->setWordWrap(false);

        vboxLayout2->addWidget(lb_outputs);

        ButtonGroup2 = new Q3ButtonGroup(GroupBox4);
        ButtonGroup2->setObjectName(QString::fromUtf8("ButtonGroup2"));
        QSizePolicy sizePolicy4(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(ButtonGroup2->sizePolicy().hasHeightForWidth());
        ButtonGroup2->setSizePolicy(sizePolicy4);
        ButtonGroup2->setMinimumSize(QSize(0, 0));
        ButtonGroup2->setMaximumSize(QSize(32767, 32767));
        ButtonGroup2->setFrameShape(Q3GroupBox::NoFrame);
        ButtonGroup2->setColumnLayout(0, Qt::Vertical);
        ButtonGroup2->layout()->setSpacing(6);
        ButtonGroup2->layout()->setContentsMargins(0, 0, 0, 0);
        hboxLayout3 = new QHBoxLayout();
        QBoxLayout *boxlayout3 = qobject_cast<QBoxLayout *>(ButtonGroup2->layout());
        if (boxlayout3)
            boxlayout3->addLayout(hboxLayout3);
        hboxLayout3->setAlignment(Qt::AlignTop);
        hboxLayout3->setObjectName(QString::fromUtf8("hboxLayout3"));
        hboxLayout4 = new QHBoxLayout();
        hboxLayout4->setSpacing(6);
        hboxLayout4->setContentsMargins(0, 0, 0, 0);
        hboxLayout4->setObjectName(QString::fromUtf8("hboxLayout4"));
        rb_obin = new QRadioButton(ButtonGroup2);
        rb_obin->setObjectName(QString::fromUtf8("rb_obin"));

        hboxLayout4->addWidget(rb_obin);

        rb_ohex = new QRadioButton(ButtonGroup2);
        rb_ohex->setObjectName(QString::fromUtf8("rb_ohex"));

        hboxLayout4->addWidget(rb_ohex);

        rb_oascii = new QRadioButton(ButtonGroup2);
        rb_oascii->setObjectName(QString::fromUtf8("rb_oascii"));

        hboxLayout4->addWidget(rb_oascii);


        hboxLayout3->addLayout(hboxLayout4);


        vboxLayout2->addWidget(ButtonGroup2);


        vboxLayout->addWidget(GroupBox4);

        hboxLayout5 = new QHBoxLayout();
        hboxLayout5->setSpacing(6);
        hboxLayout5->setContentsMargins(0, 0, 0, 0);
        hboxLayout5->setObjectName(QString::fromUtf8("hboxLayout5"));
        TextLabel1 = new QLabel(SimulatorDlg);
        TextLabel1->setObjectName(QString::fromUtf8("TextLabel1"));
        sizePolicy2.setHeightForWidth(TextLabel1->sizePolicy().hasHeightForWidth());
        TextLabel1->setSizePolicy(sizePolicy2);
        TextLabel1->setWordWrap(false);

        hboxLayout5->addWidget(TextLabel1);

        lb_sname = new QLabel(SimulatorDlg);
        lb_sname->setObjectName(QString::fromUtf8("lb_sname"));
        sizePolicy3.setHeightForWidth(lb_sname->sizePolicy().hasHeightForWidth());
        lb_sname->setSizePolicy(sizePolicy3);
        lb_sname->setMinimumSize(QSize(20, 20));
        lb_sname->setFrameShape(QFrame::Panel);
        lb_sname->setFrameShadow(QFrame::Sunken);
        lb_sname->setWordWrap(false);

        hboxLayout5->addWidget(lb_sname);

        pm_end = new QLabel(SimulatorDlg);
        pm_end->setObjectName(QString::fromUtf8("pm_end"));
        QSizePolicy sizePolicy5(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(pm_end->sizePolicy().hasHeightForWidth());
        pm_end->setSizePolicy(sizePolicy5);
        pm_end->setMinimumSize(QSize(20, 20));
        pm_end->setMaximumSize(QSize(32767, 32767));
        pm_end->setScaledContents(false);
        pm_end->setAlignment(Qt::AlignCenter);
        pm_end->setWordWrap(false);
        pm_end->setIndent(-1);

        hboxLayout5->addWidget(pm_end);


        vboxLayout->addLayout(hboxLayout5);

        hboxLayout6 = new QHBoxLayout();
        hboxLayout6->setSpacing(6);
        hboxLayout6->setContentsMargins(0, 0, 0, 0);
        hboxLayout6->setObjectName(QString::fromUtf8("hboxLayout6"));
        TextLabel3 = new QLabel(SimulatorDlg);
        TextLabel3->setObjectName(QString::fromUtf8("TextLabel3"));
        TextLabel3->setWordWrap(false);

        hboxLayout6->addWidget(TextLabel3);

        lb_scode = new QLabel(SimulatorDlg);
        lb_scode->setObjectName(QString::fromUtf8("lb_scode"));
        sizePolicy3.setHeightForWidth(lb_scode->sizePolicy().hasHeightForWidth());
        lb_scode->setSizePolicy(sizePolicy3);
        lb_scode->setFrameShape(QFrame::Panel);
        lb_scode->setFrameShadow(QFrame::Sunken);
        lb_scode->setWordWrap(false);

        hboxLayout6->addWidget(lb_scode);


        vboxLayout->addLayout(hboxLayout6);

        hboxLayout7 = new QHBoxLayout();
        hboxLayout7->setSpacing(6);
        hboxLayout7->setContentsMargins(0, 0, 0, 0);
        hboxLayout7->setObjectName(QString::fromUtf8("hboxLayout7"));
        pb_clock = new QPushButton(SimulatorDlg);
        pb_clock->setObjectName(QString::fromUtf8("pb_clock"));
        sizePolicy.setHeightForWidth(pb_clock->sizePolicy().hasHeightForWidth());
        pb_clock->setSizePolicy(sizePolicy);
        pb_clock->setCheckable(true);

        hboxLayout7->addWidget(pb_clock);

        spacerItem = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout7->addItem(spacerItem);

        lb_frequency = new QLabel(SimulatorDlg);
        lb_frequency->setObjectName(QString::fromUtf8("lb_frequency"));
        lb_frequency->setWordWrap(false);

        hboxLayout7->addWidget(lb_frequency);

        frequency = new WSpinBox(SimulatorDlg);
        frequency->setObjectName(QString::fromUtf8("frequency"));
        QSizePolicy sizePolicy6(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(frequency->sizePolicy().hasHeightForWidth());
        frequency->setSizePolicy(sizePolicy6);

        hboxLayout7->addWidget(frequency);


        vboxLayout->addLayout(hboxLayout7);

        hboxLayout8 = new QHBoxLayout();
        hboxLayout8->setSpacing(5);
        hboxLayout8->setContentsMargins(0, 0, 0, 0);
        hboxLayout8->setObjectName(QString::fromUtf8("hboxLayout8"));
        pb_send = new QPushButton(SimulatorDlg);
        pb_send->setObjectName(QString::fromUtf8("pb_send"));
        sizePolicy3.setHeightForWidth(pb_send->sizePolicy().hasHeightForWidth());
        pb_send->setSizePolicy(sizePolicy3);
        pb_send->setDefault(true);

        hboxLayout8->addWidget(pb_send);

        spacerItem1 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout8->addItem(spacerItem1);

        pb_reset = new QPushButton(SimulatorDlg);
        pb_reset->setObjectName(QString::fromUtf8("pb_reset"));
        sizePolicy2.setHeightForWidth(pb_reset->sizePolicy().hasHeightForWidth());
        pb_reset->setSizePolicy(sizePolicy2);

        hboxLayout8->addWidget(pb_reset);

        pb_cancel = new QPushButton(SimulatorDlg);
        pb_cancel->setObjectName(QString::fromUtf8("pb_cancel"));
        sizePolicy2.setHeightForWidth(pb_cancel->sizePolicy().hasHeightForWidth());
        pb_cancel->setSizePolicy(sizePolicy2);

        hboxLayout8->addWidget(pb_cancel);


        vboxLayout->addLayout(hboxLayout8);

#ifndef QT_NO_SHORTCUT
        TextLabel1->setBuddy(lb_sname);
        TextLabel3->setBuddy(lb_scode);
#endif // QT_NO_SHORTCUT
        QWidget::setTabOrder(le_inputs, rb_ibin);
        QWidget::setTabOrder(rb_ibin, rb_ihex);
        QWidget::setTabOrder(rb_ihex, rb_iascii);
        QWidget::setTabOrder(rb_iascii, pb_bin15);
        QWidget::setTabOrder(pb_bin15, pb_bin14);
        QWidget::setTabOrder(pb_bin14, pb_bin13);
        QWidget::setTabOrder(pb_bin13, pb_bin12);
        QWidget::setTabOrder(pb_bin12, pb_bin11);
        QWidget::setTabOrder(pb_bin11, pb_bin10);
        QWidget::setTabOrder(pb_bin10, pb_bin9);
        QWidget::setTabOrder(pb_bin9, pb_bin8);
        QWidget::setTabOrder(pb_bin8, pb_bin7);
        QWidget::setTabOrder(pb_bin7, pb_bin6);
        QWidget::setTabOrder(pb_bin6, pb_bin5);
        QWidget::setTabOrder(pb_bin5, pb_bin4);
        QWidget::setTabOrder(pb_bin4, pb_bin3);
        QWidget::setTabOrder(pb_bin3, pb_bin2);
        QWidget::setTabOrder(pb_bin2, pb_bin1);
        QWidget::setTabOrder(pb_bin1, pb_bin0);
        QWidget::setTabOrder(pb_bin0, pb_send);
        QWidget::setTabOrder(pb_send, pb_reset);
        QWidget::setTabOrder(pb_reset, pb_cancel);

        retranslateUi(SimulatorDlg);
        QObject::connect(pb_clock, SIGNAL(pressed()), SimulatorDlg, SLOT(clockPressed()));
        QObject::connect(le_inputs, SIGNAL(textChanged(QString)), SimulatorDlg, SLOT(inputsChanged(QString)));
        QObject::connect(rb_ibin, SIGNAL(pressed()), SimulatorDlg, SLOT(iBinPressed()));
        QObject::connect(rb_ihex, SIGNAL(pressed()), SimulatorDlg, SLOT(iHexPressed()));
        QObject::connect(rb_iascii, SIGNAL(pressed()), SimulatorDlg, SLOT(iASCIIPressed()));
        QObject::connect(rb_obin, SIGNAL(pressed()), SimulatorDlg, SLOT(oBinPressed()));
        QObject::connect(rb_ohex, SIGNAL(pressed()), SimulatorDlg, SLOT(oHexPressed()));
        QObject::connect(rb_oascii, SIGNAL(pressed()), SimulatorDlg, SLOT(oASCIIPressed()));
        QObject::connect(pb_send, SIGNAL(pressed()), SimulatorDlg, SLOT(send()));
        QObject::connect(pb_reset, SIGNAL(pressed()), SimulatorDlg, SLOT(reset()));
        QObject::connect(pb_cancel, SIGNAL(pressed()), SimulatorDlg, SLOT(closeSim()));
        QObject::connect(pb_bin0, SIGNAL(released()), SimulatorDlg, SLOT(button0Pressed()));
        QObject::connect(pb_bin1, SIGNAL(released()), SimulatorDlg, SLOT(button1Pressed()));
        QObject::connect(pb_bin10, SIGNAL(released()), SimulatorDlg, SLOT(button10Pressed()));
        QObject::connect(pb_bin11, SIGNAL(released()), SimulatorDlg, SLOT(button11Pressed()));
        QObject::connect(pb_bin12, SIGNAL(released()), SimulatorDlg, SLOT(button12Pressed()));
        QObject::connect(pb_bin13, SIGNAL(released()), SimulatorDlg, SLOT(button13Pressed()));
        QObject::connect(pb_bin14, SIGNAL(released()), SimulatorDlg, SLOT(button14Pressed()));
        QObject::connect(pb_bin15, SIGNAL(released()), SimulatorDlg, SLOT(button15Pressed()));
        QObject::connect(pb_bin2, SIGNAL(released()), SimulatorDlg, SLOT(button2Pressed()));
        QObject::connect(pb_bin3, SIGNAL(released()), SimulatorDlg, SLOT(button3Pressed()));
        QObject::connect(pb_bin4, SIGNAL(released()), SimulatorDlg, SLOT(button4Pressed()));
        QObject::connect(pb_bin5, SIGNAL(released()), SimulatorDlg, SLOT(button5Pressed()));
        QObject::connect(pb_bin6, SIGNAL(released()), SimulatorDlg, SLOT(button6Pressed()));
        QObject::connect(pb_bin7, SIGNAL(released()), SimulatorDlg, SLOT(button7Pressed()));
        QObject::connect(pb_bin8, SIGNAL(released()), SimulatorDlg, SLOT(button8Pressed()));
        QObject::connect(pb_bin9, SIGNAL(released()), SimulatorDlg, SLOT(button9Pressed()));
        QObject::connect(le_inputs, SIGNAL(returnPressed()), SimulatorDlg, SLOT(returnPressedInputs()));

        QMetaObject::connectSlotsByName(SimulatorDlg);
    } // setupUi

    void retranslateUi(QDialog *SimulatorDlg)
    {
        SimulatorDlg->setWindowTitle(QApplication::translate("SimulatorDlg", "Simulator", 0, QApplication::UnicodeUTF8));
        GroupBox3->setTitle(QApplication::translate("SimulatorDlg", "Inputs", 0, QApplication::UnicodeUTF8));
        ButtonGroup1->setTitle(QString());
        rb_ibin->setText(QApplication::translate("SimulatorDlg", "Binary", 0, QApplication::UnicodeUTF8));
        rb_ihex->setText(QApplication::translate("SimulatorDlg", "Hexadecimal", 0, QApplication::UnicodeUTF8));
        rb_iascii->setText(QApplication::translate("SimulatorDlg", "ASCII", 0, QApplication::UnicodeUTF8));
        pb_bin15->setText(QApplication::translate("SimulatorDlg", "15", 0, QApplication::UnicodeUTF8));
        pb_bin14->setText(QApplication::translate("SimulatorDlg", "14", 0, QApplication::UnicodeUTF8));
        pb_bin13->setText(QApplication::translate("SimulatorDlg", "13", 0, QApplication::UnicodeUTF8));
        pb_bin12->setText(QApplication::translate("SimulatorDlg", "12", 0, QApplication::UnicodeUTF8));
        pb_bin11->setText(QApplication::translate("SimulatorDlg", "11", 0, QApplication::UnicodeUTF8));
        pb_bin10->setText(QApplication::translate("SimulatorDlg", "10", 0, QApplication::UnicodeUTF8));
        pb_bin9->setText(QApplication::translate("SimulatorDlg", "9", 0, QApplication::UnicodeUTF8));
        pb_bin8->setText(QApplication::translate("SimulatorDlg", "8", 0, QApplication::UnicodeUTF8));
        pb_bin7->setText(QApplication::translate("SimulatorDlg", "7", 0, QApplication::UnicodeUTF8));
        pb_bin6->setText(QApplication::translate("SimulatorDlg", "6", 0, QApplication::UnicodeUTF8));
        pb_bin5->setText(QApplication::translate("SimulatorDlg", "5", 0, QApplication::UnicodeUTF8));
        pb_bin4->setText(QApplication::translate("SimulatorDlg", "4", 0, QApplication::UnicodeUTF8));
        pb_bin3->setText(QApplication::translate("SimulatorDlg", "3", 0, QApplication::UnicodeUTF8));
        pb_bin2->setText(QApplication::translate("SimulatorDlg", "2", 0, QApplication::UnicodeUTF8));
        pb_bin1->setText(QApplication::translate("SimulatorDlg", "1", 0, QApplication::UnicodeUTF8));
        pb_bin0->setText(QApplication::translate("SimulatorDlg", "0", 0, QApplication::UnicodeUTF8));
        GroupBox4->setTitle(QApplication::translate("SimulatorDlg", "Outputs", 0, QApplication::UnicodeUTF8));
        lb_outputs->setText(QString());
        ButtonGroup2->setTitle(QString());
        rb_obin->setText(QApplication::translate("SimulatorDlg", "Binary", 0, QApplication::UnicodeUTF8));
        rb_ohex->setText(QApplication::translate("SimulatorDlg", "Hexadecimal", 0, QApplication::UnicodeUTF8));
        rb_oascii->setText(QApplication::translate("SimulatorDlg", "ASCII", 0, QApplication::UnicodeUTF8));
        TextLabel1->setText(QApplication::translate("SimulatorDlg", "State Name:", 0, QApplication::UnicodeUTF8));
        lb_sname->setText(QString());
        TextLabel3->setText(QApplication::translate("SimulatorDlg", "State Code:", 0, QApplication::UnicodeUTF8));
        lb_scode->setText(QString());
        pb_clock->setText(QApplication::translate("SimulatorDlg", "Clock", 0, QApplication::UnicodeUTF8));
        lb_frequency->setText(QApplication::translate("SimulatorDlg", "Frequency:", 0, QApplication::UnicodeUTF8));
        pb_send->setText(QApplication::translate("SimulatorDlg", "Send", 0, QApplication::UnicodeUTF8));
        pb_reset->setText(QApplication::translate("SimulatorDlg", "Reset", 0, QApplication::UnicodeUTF8));
        pb_cancel->setText(QApplication::translate("SimulatorDlg", "Cancel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SimulatorDlg: public Ui_SimulatorDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // SIMULATORDLG_H
