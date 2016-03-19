/********************************************************************************
** Form generated from reading UI file 'MachinePropertiesDlg.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MACHINEPROPERTIESDLG_H
#define UI_MACHINEPROPERTIESDLG_H

#include <Qt3Support/Q3ButtonGroup>
#include <Qt3Support/Q3Frame>
#include <Qt3Support/Q3GroupBox>
#include <Qt3Support/Q3ListBox>
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
#include <QtGui/QRadioButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QTextEdit>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_MachinePropertiesDlg
{
public:
    QVBoxLayout *vboxLayout;
    QHBoxLayout *hboxLayout;
    QLabel *TextLabel1;
    QLineEdit *le_name;
    QHBoxLayout *hboxLayout1;
    QLabel *TextLabel2_2;
    QLineEdit *le_version;
    QHBoxLayout *hboxLayout2;
    QLabel *label;
    QLineEdit *le_author;
    Q3ButtonGroup *bg_type;
    QHBoxLayout *hboxLayout3;
    QRadioButton *rb_binary;
    QRadioButton *rb_ascii;
    QRadioButton *rb_text;
    Q3GroupBox *bg_moore;
    QHBoxLayout *hboxLayout4;
    QLabel *TextLabel2;
    QSpinBox *sb_mealyin;
    QLabel *TextLabel5;
    QLineEdit *le_mealyin;
    Q3GroupBox *bg_mealy;
    QGridLayout *gridLayout;
    QLabel *TextLabel6;
    QSpinBox *sb_mealyout;
    QLabel *TextLabel3;
    QLineEdit *le_mealyout;
    QLabel *TextLabel4;
    QSpinBox *sb_mooreout;
    QLabel *TextLabel7;
    QLineEdit *le_mooreout;
    QHBoxLayout *hboxLayout5;
    QPushButton *pb_statefont;
    QLabel *lb_statefont;
    QHBoxLayout *hboxLayout6;
    QPushButton *pb_transfont;
    QLabel *lb_transfont;
    QHBoxLayout *hboxLayout7;
    QLabel *TextLabel11;
    Q3ListBox *lbox_arrowtype;
    QCheckBox *cb_inittrans;
    QLabel *label_2;
    QTextEdit *te_description;
    QHBoxLayout *hboxLayout8;
    QSpacerItem *spacerItem;
    QPushButton *pb_ok;
    QPushButton *pb_cancel;

    void setupUi(QDialog *MachinePropertiesDlg)
    {
        if (MachinePropertiesDlg->objectName().isEmpty())
            MachinePropertiesDlg->setObjectName(QString::fromUtf8("MachinePropertiesDlg"));
        MachinePropertiesDlg->resize(337, 706);
        vboxLayout = new QVBoxLayout(MachinePropertiesDlg);
        vboxLayout->setSpacing(6);
        vboxLayout->setContentsMargins(11, 11, 11, 11);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        hboxLayout = new QHBoxLayout();
        hboxLayout->setSpacing(6);
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        TextLabel1 = new QLabel(MachinePropertiesDlg);
        TextLabel1->setObjectName(QString::fromUtf8("TextLabel1"));
        TextLabel1->setFrameShape(QFrame::NoFrame);
        TextLabel1->setFrameShadow(QFrame::Plain);
        TextLabel1->setWordWrap(false);

        hboxLayout->addWidget(TextLabel1);

        le_name = new QLineEdit(MachinePropertiesDlg);
        le_name->setObjectName(QString::fromUtf8("le_name"));

        hboxLayout->addWidget(le_name);


        vboxLayout->addLayout(hboxLayout);

        hboxLayout1 = new QHBoxLayout();
        hboxLayout1->setSpacing(6);
        hboxLayout1->setContentsMargins(0, 0, 0, 0);
        hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
        TextLabel2_2 = new QLabel(MachinePropertiesDlg);
        TextLabel2_2->setObjectName(QString::fromUtf8("TextLabel2_2"));
        TextLabel2_2->setWordWrap(false);

        hboxLayout1->addWidget(TextLabel2_2);

        le_version = new QLineEdit(MachinePropertiesDlg);
        le_version->setObjectName(QString::fromUtf8("le_version"));

        hboxLayout1->addWidget(le_version);


        vboxLayout->addLayout(hboxLayout1);

        hboxLayout2 = new QHBoxLayout();
        hboxLayout2->setSpacing(6);
        hboxLayout2->setObjectName(QString::fromUtf8("hboxLayout2"));
        label = new QLabel(MachinePropertiesDlg);
        label->setObjectName(QString::fromUtf8("label"));

        hboxLayout2->addWidget(label);

        le_author = new QLineEdit(MachinePropertiesDlg);
        le_author->setObjectName(QString::fromUtf8("le_author"));

        hboxLayout2->addWidget(le_author);


        vboxLayout->addLayout(hboxLayout2);

        bg_type = new Q3ButtonGroup(MachinePropertiesDlg);
        bg_type->setObjectName(QString::fromUtf8("bg_type"));
        bg_type->setColumnLayout(0, Qt::Vertical);
        bg_type->layout()->setSpacing(6);
        bg_type->layout()->setContentsMargins(11, 11, 11, 11);
        hboxLayout3 = new QHBoxLayout();
        QBoxLayout *boxlayout = qobject_cast<QBoxLayout *>(bg_type->layout());
        if (boxlayout)
            boxlayout->addLayout(hboxLayout3);
        hboxLayout3->setAlignment(Qt::AlignTop);
        hboxLayout3->setObjectName(QString::fromUtf8("hboxLayout3"));
        rb_binary = new QRadioButton(bg_type);
        rb_binary->setObjectName(QString::fromUtf8("rb_binary"));

        hboxLayout3->addWidget(rb_binary);

        rb_ascii = new QRadioButton(bg_type);
        rb_ascii->setObjectName(QString::fromUtf8("rb_ascii"));

        hboxLayout3->addWidget(rb_ascii);

        rb_text = new QRadioButton(bg_type);
        rb_text->setObjectName(QString::fromUtf8("rb_text"));

        hboxLayout3->addWidget(rb_text);


        vboxLayout->addWidget(bg_type);

        bg_moore = new Q3GroupBox(MachinePropertiesDlg);
        bg_moore->setObjectName(QString::fromUtf8("bg_moore"));
        bg_moore->setColumnLayout(0, Qt::Vertical);
        bg_moore->layout()->setSpacing(6);
        bg_moore->layout()->setContentsMargins(11, 11, 11, 11);
        hboxLayout4 = new QHBoxLayout();
        QBoxLayout *boxlayout1 = qobject_cast<QBoxLayout *>(bg_moore->layout());
        if (boxlayout1)
            boxlayout1->addLayout(hboxLayout4);
        hboxLayout4->setAlignment(Qt::AlignTop);
        hboxLayout4->setObjectName(QString::fromUtf8("hboxLayout4"));
        TextLabel2 = new QLabel(bg_moore);
        TextLabel2->setObjectName(QString::fromUtf8("TextLabel2"));
        TextLabel2->setWordWrap(false);

        hboxLayout4->addWidget(TextLabel2);

        sb_mealyin = new QSpinBox(bg_moore);
        sb_mealyin->setObjectName(QString::fromUtf8("sb_mealyin"));
        sb_mealyin->setMinimum(0);
        sb_mealyin->setValue(1);

        hboxLayout4->addWidget(sb_mealyin);

        TextLabel5 = new QLabel(bg_moore);
        TextLabel5->setObjectName(QString::fromUtf8("TextLabel5"));
        TextLabel5->setWordWrap(false);

        hboxLayout4->addWidget(TextLabel5);

        le_mealyin = new QLineEdit(bg_moore);
        le_mealyin->setObjectName(QString::fromUtf8("le_mealyin"));

        hboxLayout4->addWidget(le_mealyin);


        vboxLayout->addWidget(bg_moore);

        bg_mealy = new Q3GroupBox(MachinePropertiesDlg);
        bg_mealy->setObjectName(QString::fromUtf8("bg_mealy"));
        bg_mealy->setColumnLayout(0, Qt::Vertical);
        bg_mealy->layout()->setSpacing(6);
        bg_mealy->layout()->setContentsMargins(11, 11, 11, 11);
        gridLayout = new QGridLayout();
        QBoxLayout *boxlayout2 = qobject_cast<QBoxLayout *>(bg_mealy->layout());
        if (boxlayout2)
            boxlayout2->addLayout(gridLayout);
        gridLayout->setAlignment(Qt::AlignTop);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        TextLabel6 = new QLabel(bg_mealy);
        TextLabel6->setObjectName(QString::fromUtf8("TextLabel6"));
        TextLabel6->setWordWrap(false);

        gridLayout->addWidget(TextLabel6, 1, 2, 1, 1);

        sb_mealyout = new QSpinBox(bg_mealy);
        sb_mealyout->setObjectName(QString::fromUtf8("sb_mealyout"));
        sb_mealyout->setButtonSymbols(QAbstractSpinBox::UpDownArrows);
        sb_mealyout->setMinimum(0);
        sb_mealyout->setValue(0);

        gridLayout->addWidget(sb_mealyout, 1, 1, 1, 1);

        TextLabel3 = new QLabel(bg_mealy);
        TextLabel3->setObjectName(QString::fromUtf8("TextLabel3"));
        TextLabel3->setWordWrap(false);

        gridLayout->addWidget(TextLabel3, 1, 0, 1, 1);

        le_mealyout = new QLineEdit(bg_mealy);
        le_mealyout->setObjectName(QString::fromUtf8("le_mealyout"));

        gridLayout->addWidget(le_mealyout, 1, 3, 1, 1);

        TextLabel4 = new QLabel(bg_mealy);
        TextLabel4->setObjectName(QString::fromUtf8("TextLabel4"));
        TextLabel4->setWordWrap(false);

        gridLayout->addWidget(TextLabel4, 0, 0, 1, 1);

        sb_mooreout = new QSpinBox(bg_mealy);
        sb_mooreout->setObjectName(QString::fromUtf8("sb_mooreout"));

        gridLayout->addWidget(sb_mooreout, 0, 1, 1, 1);

        TextLabel7 = new QLabel(bg_mealy);
        TextLabel7->setObjectName(QString::fromUtf8("TextLabel7"));
        TextLabel7->setWordWrap(false);

        gridLayout->addWidget(TextLabel7, 0, 2, 1, 1);

        le_mooreout = new QLineEdit(bg_mealy);
        le_mooreout->setObjectName(QString::fromUtf8("le_mooreout"));

        gridLayout->addWidget(le_mooreout, 0, 3, 1, 1);


        vboxLayout->addWidget(bg_mealy);

        hboxLayout5 = new QHBoxLayout();
        hboxLayout5->setSpacing(6);
        hboxLayout5->setObjectName(QString::fromUtf8("hboxLayout5"));
        pb_statefont = new QPushButton(MachinePropertiesDlg);
        pb_statefont->setObjectName(QString::fromUtf8("pb_statefont"));

        hboxLayout5->addWidget(pb_statefont);

        lb_statefont = new QLabel(MachinePropertiesDlg);
        lb_statefont->setObjectName(QString::fromUtf8("lb_statefont"));
        lb_statefont->setFrameShape(QFrame::Panel);
        lb_statefont->setFrameShadow(QFrame::Sunken);
        lb_statefont->setWordWrap(false);

        hboxLayout5->addWidget(lb_statefont);


        vboxLayout->addLayout(hboxLayout5);

        hboxLayout6 = new QHBoxLayout();
        hboxLayout6->setSpacing(6);
        hboxLayout6->setObjectName(QString::fromUtf8("hboxLayout6"));
        pb_transfont = new QPushButton(MachinePropertiesDlg);
        pb_transfont->setObjectName(QString::fromUtf8("pb_transfont"));

        hboxLayout6->addWidget(pb_transfont);

        lb_transfont = new QLabel(MachinePropertiesDlg);
        lb_transfont->setObjectName(QString::fromUtf8("lb_transfont"));
        lb_transfont->setFrameShape(QFrame::Panel);
        lb_transfont->setFrameShadow(QFrame::Sunken);
        lb_transfont->setWordWrap(false);

        hboxLayout6->addWidget(lb_transfont);


        vboxLayout->addLayout(hboxLayout6);

        hboxLayout7 = new QHBoxLayout();
        hboxLayout7->setSpacing(6);
        hboxLayout7->setObjectName(QString::fromUtf8("hboxLayout7"));
        TextLabel11 = new QLabel(MachinePropertiesDlg);
        TextLabel11->setObjectName(QString::fromUtf8("TextLabel11"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(TextLabel11->sizePolicy().hasHeightForWidth());
        TextLabel11->setSizePolicy(sizePolicy);
        TextLabel11->setWordWrap(false);

        hboxLayout7->addWidget(TextLabel11);

        lbox_arrowtype = new Q3ListBox(MachinePropertiesDlg);
        lbox_arrowtype->setObjectName(QString::fromUtf8("lbox_arrowtype"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lbox_arrowtype->sizePolicy().hasHeightForWidth());
        lbox_arrowtype->setSizePolicy(sizePolicy1);
        lbox_arrowtype->setMinimumSize(QSize(0, 0));

        hboxLayout7->addWidget(lbox_arrowtype);


        vboxLayout->addLayout(hboxLayout7);

        cb_inittrans = new QCheckBox(MachinePropertiesDlg);
        cb_inittrans->setObjectName(QString::fromUtf8("cb_inittrans"));

        vboxLayout->addWidget(cb_inittrans);

        label_2 = new QLabel(MachinePropertiesDlg);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        vboxLayout->addWidget(label_2);

        te_description = new QTextEdit(MachinePropertiesDlg);
        te_description->setObjectName(QString::fromUtf8("te_description"));
        sizePolicy1.setHeightForWidth(te_description->sizePolicy().hasHeightForWidth());
        te_description->setSizePolicy(sizePolicy1);

        vboxLayout->addWidget(te_description);

        hboxLayout8 = new QHBoxLayout();
        hboxLayout8->setSpacing(6);
        hboxLayout8->setContentsMargins(0, 0, 0, 0);
        hboxLayout8->setObjectName(QString::fromUtf8("hboxLayout8"));
        spacerItem = new QSpacerItem(20, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout8->addItem(spacerItem);

        pb_ok = new QPushButton(MachinePropertiesDlg);
        pb_ok->setObjectName(QString::fromUtf8("pb_ok"));
        pb_ok->setDefault(true);

        hboxLayout8->addWidget(pb_ok);

        pb_cancel = new QPushButton(MachinePropertiesDlg);
        pb_cancel->setObjectName(QString::fromUtf8("pb_cancel"));

        hboxLayout8->addWidget(pb_cancel);


        vboxLayout->addLayout(hboxLayout8);


        retranslateUi(MachinePropertiesDlg);
        QObject::connect(pb_ok, SIGNAL(clicked()), MachinePropertiesDlg, SLOT(accept()));
        QObject::connect(pb_cancel, SIGNAL(clicked()), MachinePropertiesDlg, SLOT(reject()));
        QObject::connect(pb_statefont, SIGNAL(clicked()), MachinePropertiesDlg, SLOT(chooseSFont()));
        QObject::connect(pb_transfont, SIGNAL(clicked()), MachinePropertiesDlg, SLOT(chooseTFont()));
        QObject::connect(rb_binary, SIGNAL(clicked()), MachinePropertiesDlg, SLOT(binaryClicked()));
        QObject::connect(rb_ascii, SIGNAL(clicked()), MachinePropertiesDlg, SLOT(asciiClicked()));
        QObject::connect(rb_text, SIGNAL(clicked()), MachinePropertiesDlg, SLOT(freeTextClicked()));
        QObject::connect(cb_inittrans, SIGNAL(clicked()), MachinePropertiesDlg, SLOT(drawITransClicked()));

        QMetaObject::connectSlotsByName(MachinePropertiesDlg);
    } // setupUi

    void retranslateUi(QDialog *MachinePropertiesDlg)
    {
        MachinePropertiesDlg->setWindowTitle(QApplication::translate("MachinePropertiesDlg", "Machine Properties", 0, QApplication::UnicodeUTF8));
        TextLabel1->setText(QApplication::translate("MachinePropertiesDlg", "Name:", 0, QApplication::UnicodeUTF8));
        TextLabel2_2->setText(QApplication::translate("MachinePropertiesDlg", "Version:", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MachinePropertiesDlg", "Author:", 0, QApplication::UnicodeUTF8));
        bg_type->setTitle(QApplication::translate("MachinePropertiesDlg", "Type", 0, QApplication::UnicodeUTF8));
        rb_binary->setText(QApplication::translate("MachinePropertiesDlg", "Binary", 0, QApplication::UnicodeUTF8));
        rb_ascii->setText(QApplication::translate("MachinePropertiesDlg", "ASCII", 0, QApplication::UnicodeUTF8));
        rb_text->setText(QApplication::translate("MachinePropertiesDlg", "Free Text", 0, QApplication::UnicodeUTF8));
        bg_moore->setTitle(QApplication::translate("MachinePropertiesDlg", "Inputs", 0, QApplication::UnicodeUTF8));
        TextLabel2->setText(QApplication::translate("MachinePropertiesDlg", "Inputs:", 0, QApplication::UnicodeUTF8));
        TextLabel5->setText(QApplication::translate("MachinePropertiesDlg", "Names:", 0, QApplication::UnicodeUTF8));
        bg_mealy->setTitle(QApplication::translate("MachinePropertiesDlg", "Outputs", 0, QApplication::UnicodeUTF8));
        TextLabel6->setText(QApplication::translate("MachinePropertiesDlg", "Names:", 0, QApplication::UnicodeUTF8));
        TextLabel3->setText(QApplication::translate("MachinePropertiesDlg", "Mealy:", 0, QApplication::UnicodeUTF8));
        TextLabel4->setText(QApplication::translate("MachinePropertiesDlg", "Moore:", 0, QApplication::UnicodeUTF8));
        TextLabel7->setText(QApplication::translate("MachinePropertiesDlg", "Names:", 0, QApplication::UnicodeUTF8));
        pb_statefont->setText(QApplication::translate("MachinePropertiesDlg", "State Font", 0, QApplication::UnicodeUTF8));
        lb_statefont->setText(QString());
        pb_transfont->setText(QApplication::translate("MachinePropertiesDlg", "Transition Font", 0, QApplication::UnicodeUTF8));
        lb_transfont->setText(QString());
        TextLabel11->setText(QApplication::translate("MachinePropertiesDlg", "Arrow Type:", 0, QApplication::UnicodeUTF8));
        cb_inittrans->setText(QApplication::translate("MachinePropertiesDlg", "Draw initial transition", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MachinePropertiesDlg", "Description:", 0, QApplication::UnicodeUTF8));
        pb_ok->setText(QApplication::translate("MachinePropertiesDlg", "OK", 0, QApplication::UnicodeUTF8));
        pb_cancel->setText(QApplication::translate("MachinePropertiesDlg", "Cancel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MachinePropertiesDlg: public Ui_MachinePropertiesDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MACHINEPROPERTIESDLG_H
