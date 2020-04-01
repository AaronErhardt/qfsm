/********************************************************************************
** Form generated from reading UI file 'OptDisplayDlg.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OPTDISPLAYDLG_H
#define UI_OPTDISPLAYDLG_H

#include <Qt3Support/Q3ButtonGroup>
#include <Qt3Support/Q3GroupBox>
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
#include <QtGui/QSpinBox>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_OptDisplayDlg
{
public:
    QVBoxLayout *vboxLayout;
    Q3GroupBox *GroupBox17;
    QVBoxLayout *vboxLayout1;
    QHBoxLayout *hboxLayout;
    QPushButton *pb_gridcolor;
    QLabel *lb_gridcolor;
    QHBoxLayout *hboxLayout1;
    QLabel *TextLabel14;
    QSpinBox *sb_gridsize;
    Q3GroupBox *groupBox3;
    QHBoxLayout *hboxLayout2;
    QVBoxLayout *vboxLayout2;
    QCheckBox *cb_shadows;
    QHBoxLayout *hboxLayout3;
    QPushButton *pb_shadowcolor;
    QLabel *lb_shadowcolor;
    Q3ButtonGroup *bg_transitions;
    QVBoxLayout *vboxLayout3;
    QVBoxLayout *vboxLayout4;
    QCheckBox *cb_iomark;
    QCheckBox *cb_ionames;
    QCheckBox *cb_drawbox;
    QCheckBox *cb_tooltips;
    QSpacerItem *spacerItem;
    QGridLayout *gridLayout;
    QLineEdit *le_start;
    QLabel *textLabel2;
    QLabel *textLabel1;
    QLineEdit *le_default;
    QLabel *lb_start;
    QLineEdit *le_any;
    QLineEdit *le_inversion;
    QLabel *textLabel1_2;
    QSpacerItem *spacerItem1;

    void setupUi(QDialog *OptDisplayDlg)
    {
        if (OptDisplayDlg->objectName().isEmpty())
            OptDisplayDlg->setObjectName(QString::fromUtf8("OptDisplayDlg"));
        OptDisplayDlg->resize(426, 525);
        vboxLayout = new QVBoxLayout(OptDisplayDlg);
        vboxLayout->setSpacing(6);
        vboxLayout->setContentsMargins(11, 11, 11, 11);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        GroupBox17 = new Q3GroupBox(OptDisplayDlg);
        GroupBox17->setObjectName(QString::fromUtf8("GroupBox17"));
        GroupBox17->setColumnLayout(0, Qt::Vertical);
        GroupBox17->layout()->setSpacing(6);
        GroupBox17->layout()->setContentsMargins(11, 11, 11, 11);
        vboxLayout1 = new QVBoxLayout();
        QBoxLayout *boxlayout = qobject_cast<QBoxLayout *>(GroupBox17->layout());
        if (boxlayout)
            boxlayout->addLayout(vboxLayout1);
        vboxLayout1->setAlignment(Qt::AlignTop);
        vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
        hboxLayout = new QHBoxLayout();
        hboxLayout->setSpacing(6);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        pb_gridcolor = new QPushButton(GroupBox17);
        pb_gridcolor->setObjectName(QString::fromUtf8("pb_gridcolor"));

        hboxLayout->addWidget(pb_gridcolor);

        lb_gridcolor = new QLabel(GroupBox17);
        lb_gridcolor->setObjectName(QString::fromUtf8("lb_gridcolor"));
        lb_gridcolor->setFrameShape(QFrame::Panel);
        lb_gridcolor->setFrameShadow(QFrame::Sunken);
        lb_gridcolor->setWordWrap(false);

        hboxLayout->addWidget(lb_gridcolor);


        vboxLayout1->addLayout(hboxLayout);

        hboxLayout1 = new QHBoxLayout();
        hboxLayout1->setSpacing(6);
        hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
        TextLabel14 = new QLabel(GroupBox17);
        TextLabel14->setObjectName(QString::fromUtf8("TextLabel14"));
        TextLabel14->setWordWrap(false);

        hboxLayout1->addWidget(TextLabel14);

        sb_gridsize = new QSpinBox(GroupBox17);
        sb_gridsize->setObjectName(QString::fromUtf8("sb_gridsize"));
        sb_gridsize->setMinimum(3);

        hboxLayout1->addWidget(sb_gridsize);


        vboxLayout1->addLayout(hboxLayout1);


        vboxLayout->addWidget(GroupBox17);

        groupBox3 = new Q3GroupBox(OptDisplayDlg);
        groupBox3->setObjectName(QString::fromUtf8("groupBox3"));
        groupBox3->setColumnLayout(0, Qt::Vertical);
        groupBox3->layout()->setSpacing(6);
        groupBox3->layout()->setContentsMargins(11, 11, 11, 11);
        hboxLayout2 = new QHBoxLayout();
        QBoxLayout *boxlayout1 = qobject_cast<QBoxLayout *>(groupBox3->layout());
        if (boxlayout1)
            boxlayout1->addLayout(hboxLayout2);
        hboxLayout2->setAlignment(Qt::AlignTop);
        hboxLayout2->setObjectName(QString::fromUtf8("hboxLayout2"));
        vboxLayout2 = new QVBoxLayout();
        vboxLayout2->setSpacing(6);
        vboxLayout2->setObjectName(QString::fromUtf8("vboxLayout2"));
        cb_shadows = new QCheckBox(groupBox3);
        cb_shadows->setObjectName(QString::fromUtf8("cb_shadows"));

        vboxLayout2->addWidget(cb_shadows);

        hboxLayout3 = new QHBoxLayout();
        hboxLayout3->setSpacing(6);
        hboxLayout3->setObjectName(QString::fromUtf8("hboxLayout3"));
        pb_shadowcolor = new QPushButton(groupBox3);
        pb_shadowcolor->setObjectName(QString::fromUtf8("pb_shadowcolor"));

        hboxLayout3->addWidget(pb_shadowcolor);

        lb_shadowcolor = new QLabel(groupBox3);
        lb_shadowcolor->setObjectName(QString::fromUtf8("lb_shadowcolor"));
        lb_shadowcolor->setFrameShape(QFrame::Panel);
        lb_shadowcolor->setFrameShadow(QFrame::Sunken);
        lb_shadowcolor->setWordWrap(false);

        hboxLayout3->addWidget(lb_shadowcolor);


        vboxLayout2->addLayout(hboxLayout3);


        hboxLayout2->addLayout(vboxLayout2);


        vboxLayout->addWidget(groupBox3);

        bg_transitions = new Q3ButtonGroup(OptDisplayDlg);
        bg_transitions->setObjectName(QString::fromUtf8("bg_transitions"));
        bg_transitions->setColumnLayout(0, Qt::Vertical);
        bg_transitions->layout()->setSpacing(6);
        bg_transitions->layout()->setContentsMargins(11, 11, 11, 11);
        vboxLayout3 = new QVBoxLayout();
        QBoxLayout *boxlayout2 = qobject_cast<QBoxLayout *>(bg_transitions->layout());
        if (boxlayout2)
            boxlayout2->addLayout(vboxLayout3);
        vboxLayout3->setAlignment(Qt::AlignTop);
        vboxLayout3->setObjectName(QString::fromUtf8("vboxLayout3"));
        vboxLayout4 = new QVBoxLayout();
        vboxLayout4->setSpacing(6);
        vboxLayout4->setObjectName(QString::fromUtf8("vboxLayout4"));
        cb_iomark = new QCheckBox(bg_transitions);
        cb_iomark->setObjectName(QString::fromUtf8("cb_iomark"));

        vboxLayout4->addWidget(cb_iomark);

        cb_ionames = new QCheckBox(bg_transitions);
        cb_ionames->setObjectName(QString::fromUtf8("cb_ionames"));

        vboxLayout4->addWidget(cb_ionames);

        cb_drawbox = new QCheckBox(bg_transitions);
        cb_drawbox->setObjectName(QString::fromUtf8("cb_drawbox"));

        vboxLayout4->addWidget(cb_drawbox);


        vboxLayout3->addLayout(vboxLayout4);


        vboxLayout->addWidget(bg_transitions);

        cb_tooltips = new QCheckBox(OptDisplayDlg);
        cb_tooltips->setObjectName(QString::fromUtf8("cb_tooltips"));

        vboxLayout->addWidget(cb_tooltips);

        spacerItem = new QSpacerItem(20, 16, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vboxLayout->addItem(spacerItem);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        le_start = new QLineEdit(OptDisplayDlg);
        le_start->setObjectName(QString::fromUtf8("le_start"));

        gridLayout->addWidget(le_start, 0, 1, 1, 1);

        textLabel2 = new QLabel(OptDisplayDlg);
        textLabel2->setObjectName(QString::fromUtf8("textLabel2"));
        textLabel2->setWordWrap(false);

        gridLayout->addWidget(textLabel2, 3, 0, 1, 1);

        textLabel1 = new QLabel(OptDisplayDlg);
        textLabel1->setObjectName(QString::fromUtf8("textLabel1"));
        textLabel1->setWordWrap(false);

        gridLayout->addWidget(textLabel1, 1, 0, 1, 1);

        le_default = new QLineEdit(OptDisplayDlg);
        le_default->setObjectName(QString::fromUtf8("le_default"));

        gridLayout->addWidget(le_default, 3, 1, 1, 1);

        lb_start = new QLabel(OptDisplayDlg);
        lb_start->setObjectName(QString::fromUtf8("lb_start"));
        lb_start->setWordWrap(false);

        gridLayout->addWidget(lb_start, 0, 0, 1, 1);

        le_any = new QLineEdit(OptDisplayDlg);
        le_any->setObjectName(QString::fromUtf8("le_any"));

        gridLayout->addWidget(le_any, 2, 1, 1, 1);

        le_inversion = new QLineEdit(OptDisplayDlg);
        le_inversion->setObjectName(QString::fromUtf8("le_inversion"));

        gridLayout->addWidget(le_inversion, 1, 1, 1, 1);

        textLabel1_2 = new QLabel(OptDisplayDlg);
        textLabel1_2->setObjectName(QString::fromUtf8("textLabel1_2"));
        textLabel1_2->setWordWrap(false);

        gridLayout->addWidget(textLabel1_2, 2, 0, 1, 1);


        vboxLayout->addLayout(gridLayout);

        spacerItem1 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vboxLayout->addItem(spacerItem1);

        QWidget::setTabOrder(pb_gridcolor, sb_gridsize);
        QWidget::setTabOrder(sb_gridsize, pb_shadowcolor);
        QWidget::setTabOrder(pb_shadowcolor, cb_iomark);
        QWidget::setTabOrder(cb_iomark, cb_ionames);
        QWidget::setTabOrder(cb_ionames, cb_drawbox);
        QWidget::setTabOrder(cb_drawbox, cb_tooltips);
        QWidget::setTabOrder(cb_tooltips, le_start);
        QWidget::setTabOrder(le_start, le_inversion);
        QWidget::setTabOrder(le_inversion, le_any);
        QWidget::setTabOrder(le_any, le_default);
        QWidget::setTabOrder(le_default, cb_shadows);

        retranslateUi(OptDisplayDlg);
        QObject::connect(pb_gridcolor, SIGNAL(clicked()), OptDisplayDlg, SLOT(chooseGridColor()));
        QObject::connect(cb_tooltips, SIGNAL(clicked()), OptDisplayDlg, SLOT(tooltipsClicked()));
        QObject::connect(le_start, SIGNAL(textChanged(QString)), OptDisplayDlg, SLOT(startDescChanged()));
        QObject::connect(cb_iomark, SIGNAL(clicked()), OptDisplayDlg, SLOT(ioMarkClicked()));
        QObject::connect(cb_shadows, SIGNAL(clicked()), OptDisplayDlg, SLOT(shadowsClicked()));
        QObject::connect(pb_shadowcolor, SIGNAL(clicked()), OptDisplayDlg, SLOT(chooseShadowColor()));
        QObject::connect(cb_drawbox, SIGNAL(clicked()), OptDisplayDlg, SLOT(drawBoxClicked()));
        QObject::connect(cb_ionames, SIGNAL(clicked()), OptDisplayDlg, SLOT(ioNamesClicked()));
        QObject::connect(le_inversion, SIGNAL(textChanged(QString)), OptDisplayDlg, SLOT(inversionDescChanged()));
        QObject::connect(le_any, SIGNAL(textChanged(QString)), OptDisplayDlg, SLOT(anyInputDescChanged()));
        QObject::connect(le_default, SIGNAL(textChanged(QString)), OptDisplayDlg, SLOT(defaultDescChanged()));

        QMetaObject::connectSlotsByName(OptDisplayDlg);
    } // setupUi

    void retranslateUi(QDialog *OptDisplayDlg)
    {
        OptDisplayDlg->setWindowTitle(QApplication::translate("OptDisplayDlg", "Display", 0, QApplication::UnicodeUTF8));
        GroupBox17->setTitle(QApplication::translate("OptDisplayDlg", "Grid", 0, QApplication::UnicodeUTF8));
        pb_gridcolor->setText(QApplication::translate("OptDisplayDlg", "Color", 0, QApplication::UnicodeUTF8));
        lb_gridcolor->setText(QString());
        TextLabel14->setText(QApplication::translate("OptDisplayDlg", "Size:", 0, QApplication::UnicodeUTF8));
        groupBox3->setTitle(QApplication::translate("OptDisplayDlg", "Shadows", 0, QApplication::UnicodeUTF8));
        cb_shadows->setText(QApplication::translate("OptDisplayDlg", "Display shadows", 0, QApplication::UnicodeUTF8));
        pb_shadowcolor->setText(QApplication::translate("OptDisplayDlg", "Color", 0, QApplication::UnicodeUTF8));
        lb_shadowcolor->setText(QString());
        bg_transitions->setTitle(QApplication::translate("OptDisplayDlg", "Transitions", 0, QApplication::UnicodeUTF8));
        cb_iomark->setText(QApplication::translate("OptDisplayDlg", "Use '?' and '!' to mark inputs and outputs", 0, QApplication::UnicodeUTF8));
        cb_ionames->setText(QApplication::translate("OptDisplayDlg", "Display input/output names", 0, QApplication::UnicodeUTF8));
        cb_drawbox->setText(QApplication::translate("OptDisplayDlg", "Draw Box around inputs/outputs", 0, QApplication::UnicodeUTF8));
        cb_tooltips->setText(QApplication::translate("OptDisplayDlg", "Tooltips", 0, QApplication::UnicodeUTF8));
        textLabel2->setText(QApplication::translate("OptDisplayDlg", "Default transition descriptor:", 0, QApplication::UnicodeUTF8));
        textLabel1->setText(QApplication::translate("OptDisplayDlg", "Inversion descriptor:", 0, QApplication::UnicodeUTF8));
        lb_start->setText(QApplication::translate("OptDisplayDlg", "Initial transition descriptor:", 0, QApplication::UnicodeUTF8));
        textLabel1_2->setText(QApplication::translate("OptDisplayDlg", "\"Any input\" descriptor:", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class OptDisplayDlg: public Ui_OptDisplayDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPTDISPLAYDLG_H
