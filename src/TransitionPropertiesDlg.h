#ifndef TRANSITIONPROPERTIESDLG_H
#define TRANSITIONPROPERTIESDLG_H

#include <qvariant.h>


#include <Qt3Support/Q3ButtonGroup>
#include <Qt3Support/Q3MimeSourceFactory>
#include <Qt3Support/Q3TextEdit>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QVBoxLayout>

class Ui_TransitionPropertiesDlg
{
public:
    QVBoxLayout *vboxLayout;
    Q3ButtonGroup *bg_type;
    QHBoxLayout *hboxLayout;
    QRadioButton *rb_bin;
    QRadioButton *rb_ascii;
    QRadioButton *rb_text;
    QGridLayout *gridLayout;
    QLabel *TextLabel7;
    QCheckBox *cb_invert;
    QLineEdit *le_input;
    QCheckBox *cb_default;
    QCheckBox *cb_any;
    QLineEdit *le_output;
    QLabel *TextLabel6;
    QLabel *TextLabel3;
    Q3TextEdit *te_description;
    QHBoxLayout *hboxLayout1;
    QPushButton *PushButton19;
    QPushButton *PushButton20;

    void setupUi(QDialog *TransitionPropertiesDlg)
    {
    if (TransitionPropertiesDlg->objectName().isEmpty())
        TransitionPropertiesDlg->setObjectName(QString::fromUtf8("TransitionPropertiesDlg"));
    TransitionPropertiesDlg->resize(323, 479);
    vboxLayout = new QVBoxLayout(TransitionPropertiesDlg);
    vboxLayout->setSpacing(6);
    vboxLayout->setMargin(11);
    vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
    bg_type = new Q3ButtonGroup(TransitionPropertiesDlg);
    bg_type->setObjectName(QString::fromUtf8("bg_type"));
    bg_type->setColumnLayout(0, Qt::Vertical);
    bg_type->layout()->setSpacing(6);
    bg_type->layout()->setMargin(11);
    hboxLayout = new QHBoxLayout();
    QBoxLayout *boxlayout = qobject_cast<QBoxLayout *>(bg_type->layout());
    if (boxlayout)
        boxlayout->addLayout(hboxLayout);
    hboxLayout->setAlignment(Qt::AlignTop);
    hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
    rb_bin = new QRadioButton(bg_type);
    rb_bin->setObjectName(QString::fromUtf8("rb_bin"));

    hboxLayout->addWidget(rb_bin);

    rb_ascii = new QRadioButton(bg_type);
    rb_ascii->setObjectName(QString::fromUtf8("rb_ascii"));

    hboxLayout->addWidget(rb_ascii);

    rb_text = new QRadioButton(bg_type);
    rb_text->setObjectName(QString::fromUtf8("rb_text"));

    hboxLayout->addWidget(rb_text);


    vboxLayout->addWidget(bg_type);

    gridLayout = new QGridLayout();
    gridLayout->setSpacing(6);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    TextLabel7 = new QLabel(TransitionPropertiesDlg);
    TextLabel7->setObjectName(QString::fromUtf8("TextLabel7"));
    TextLabel7->setWordWrap(false);

    gridLayout->addWidget(TextLabel7, 4, 0, 1, 1);

    cb_invert = new QCheckBox(TransitionPropertiesDlg);
    cb_invert->setObjectName(QString::fromUtf8("cb_invert"));

    gridLayout->addWidget(cb_invert, 2, 1, 1, 1);

    le_input = new QLineEdit(TransitionPropertiesDlg);
    le_input->setObjectName(QString::fromUtf8("le_input"));

    gridLayout->addWidget(le_input, 0, 1, 1, 1);

    cb_default = new QCheckBox(TransitionPropertiesDlg);
    cb_default->setObjectName(QString::fromUtf8("cb_default"));

    gridLayout->addWidget(cb_default, 3, 1, 1, 1);

    cb_any = new QCheckBox(TransitionPropertiesDlg);
    cb_any->setObjectName(QString::fromUtf8("cb_any"));

    gridLayout->addWidget(cb_any, 1, 1, 1, 1);

    le_output = new QLineEdit(TransitionPropertiesDlg);
    le_output->setObjectName(QString::fromUtf8("le_output"));

    gridLayout->addWidget(le_output, 4, 1, 1, 1);

    TextLabel6 = new QLabel(TransitionPropertiesDlg);
    TextLabel6->setObjectName(QString::fromUtf8("TextLabel6"));
    TextLabel6->setWordWrap(false);

    gridLayout->addWidget(TextLabel6, 0, 0, 1, 1);


    vboxLayout->addLayout(gridLayout);

    TextLabel3 = new QLabel(TransitionPropertiesDlg);
    TextLabel3->setObjectName(QString::fromUtf8("TextLabel3"));
    TextLabel3->setWordWrap(false);

    vboxLayout->addWidget(TextLabel3);

    te_description = new Q3TextEdit(TransitionPropertiesDlg);
    te_description->setObjectName(QString::fromUtf8("te_description"));

    vboxLayout->addWidget(te_description);

    hboxLayout1 = new QHBoxLayout();
    hboxLayout1->setSpacing(6);
    hboxLayout1->setMargin(0);
    hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
    PushButton19 = new QPushButton(TransitionPropertiesDlg);
    PushButton19->setObjectName(QString::fromUtf8("PushButton19"));
    PushButton19->setDefault(true);

    hboxLayout1->addWidget(PushButton19);

    PushButton20 = new QPushButton(TransitionPropertiesDlg);
    PushButton20->setObjectName(QString::fromUtf8("PushButton20"));

    hboxLayout1->addWidget(PushButton20);


    vboxLayout->addLayout(hboxLayout1);

    QWidget::setTabOrder(le_input, le_output);
    QWidget::setTabOrder(le_output, rb_bin);
    QWidget::setTabOrder(rb_bin, rb_ascii);
    QWidget::setTabOrder(rb_ascii, PushButton19);
    QWidget::setTabOrder(PushButton19, PushButton20);

    retranslateUi(TransitionPropertiesDlg);
    QObject::connect(PushButton19, SIGNAL(clicked()), TransitionPropertiesDlg, SLOT(validate()));
    QObject::connect(PushButton20, SIGNAL(clicked()), TransitionPropertiesDlg, SLOT(reject()));
    QObject::connect(rb_bin, SIGNAL(clicked()), TransitionPropertiesDlg, SLOT(binaryClicked()));
    QObject::connect(rb_ascii, SIGNAL(clicked()), TransitionPropertiesDlg, SLOT(asciiClicked()));
    QObject::connect(cb_any, SIGNAL(clicked()), TransitionPropertiesDlg, SLOT(anyClicked()));
    QObject::connect(cb_default, SIGNAL(clicked()), TransitionPropertiesDlg, SLOT(defaultClicked()));
    QObject::connect(cb_invert, SIGNAL(clicked()), TransitionPropertiesDlg, SLOT(invertClicked()));
    QObject::connect(rb_text, SIGNAL(clicked()), TransitionPropertiesDlg, SLOT(freeTextClicked()));

    QMetaObject::connectSlotsByName(TransitionPropertiesDlg);
    } // setupUi

    void retranslateUi(QDialog *TransitionPropertiesDlg)
    {
    TransitionPropertiesDlg->setWindowTitle(QApplication::translate("TransitionPropertiesDlg", "Transition Properties", 0, QApplication::UnicodeUTF8));
    bg_type->setTitle(QApplication::translate("TransitionPropertiesDlg", "Condition Type", 0, QApplication::UnicodeUTF8));
    rb_bin->setText(QApplication::translate("TransitionPropertiesDlg", "Binary", 0, QApplication::UnicodeUTF8));
    rb_ascii->setText(QApplication::translate("TransitionPropertiesDlg", "ASCII", 0, QApplication::UnicodeUTF8));
    rb_text->setText(QApplication::translate("TransitionPropertiesDlg", "Free Text", 0, QApplication::UnicodeUTF8));
    TextLabel7->setText(QApplication::translate("TransitionPropertiesDlg", "Output:", 0, QApplication::UnicodeUTF8));
    cb_invert->setText(QApplication::translate("TransitionPropertiesDlg", "Invert condition", 0, QApplication::UnicodeUTF8));
    cb_default->setText(QApplication::translate("TransitionPropertiesDlg", "Default transition", 0, QApplication::UnicodeUTF8));
    cb_any->setText(QApplication::translate("TransitionPropertiesDlg", "Any input", 0, QApplication::UnicodeUTF8));
    TextLabel6->setText(QApplication::translate("TransitionPropertiesDlg", "Input:", 0, QApplication::UnicodeUTF8));
    TextLabel3->setText(QApplication::translate("TransitionPropertiesDlg", "Description:", 0, QApplication::UnicodeUTF8));
    PushButton19->setText(QApplication::translate("TransitionPropertiesDlg", "OK", 0, QApplication::UnicodeUTF8));
    PushButton20->setText(QApplication::translate("TransitionPropertiesDlg", "Cancel", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(TransitionPropertiesDlg);
    } // retranslateUi

};

namespace Ui {
    class TransitionPropertiesDlg: public Ui_TransitionPropertiesDlg {};
} // namespace Ui

class TransitionPropertiesDlg : public QDialog, public Ui::TransitionPropertiesDlg
{
    Q_OBJECT

public:
    TransitionPropertiesDlg(QWidget* parent = 0, const char* name = 0, bool modal = false, Qt::WindowFlags fl = 0);
    ~TransitionPropertiesDlg();

public slots:
    virtual void asciiClicked();
    virtual void binaryClicked();
    virtual void validate();
    virtual void anyClicked();
    virtual void defaultClicked();
    virtual void invertClicked();
    virtual void freeTextClicked();

protected slots:
    virtual void languageChange();

};

#endif // TRANSITIONPROPERTIESDLG_H
