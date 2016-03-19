#ifndef STATEPROPERTIESDLG_H
#define STATEPROPERTIESDLG_H

#include <qvariant.h>


#include <Qt3Support/Q3MimeSourceFactory>
#include <Qt3Support/Q3TextEdit>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>

class Ui_StatePropertiesDlg
{
public:
    QVBoxLayout *vboxLayout;
    QVBoxLayout *vboxLayout1;
    QGridLayout *gridLayout;
    QLineEdit *le_linewidth;
    QLineEdit *le_name;
    QLineEdit *le_code;
    QLabel *lb_colorpreview;
    QLabel *TextLabel3;
    QLabel *TextLabel2;
    QPushButton *PushButton1;
    QLabel *TextLabel1;
    QLineEdit *le_radius;
    QLabel *textLabel1;
    QLineEdit *le_mooreoutputs;
    QLabel *TextLabel4;
    QLabel *TextLabel1_2;
    Q3TextEdit *te_description;
    QHBoxLayout *hboxLayout;
    QPushButton *PushButton2;
    QPushButton *PushButton3;

    void setupUi(QDialog *StatePropertiesDlg)
    {
    if (StatePropertiesDlg->objectName().isEmpty())
        StatePropertiesDlg->setObjectName(QString::fromUtf8("StatePropertiesDlg"));
    StatePropertiesDlg->resize(314, 410);
    vboxLayout = new QVBoxLayout(StatePropertiesDlg);
    vboxLayout->setSpacing(6);
    vboxLayout->setMargin(11);
    vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
    vboxLayout1 = new QVBoxLayout();
    vboxLayout1->setSpacing(6);
    vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
    gridLayout = new QGridLayout();
    gridLayout->setSpacing(6);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    le_linewidth = new QLineEdit(StatePropertiesDlg);
    le_linewidth->setObjectName(QString::fromUtf8("le_linewidth"));

    gridLayout->addWidget(le_linewidth, 4, 1, 1, 1);

    le_name = new QLineEdit(StatePropertiesDlg);
    le_name->setObjectName(QString::fromUtf8("le_name"));

    gridLayout->addWidget(le_name, 0, 1, 1, 1);

    le_code = new QLineEdit(StatePropertiesDlg);
    le_code->setObjectName(QString::fromUtf8("le_code"));

    gridLayout->addWidget(le_code, 1, 1, 1, 1);

    lb_colorpreview = new QLabel(StatePropertiesDlg);
    lb_colorpreview->setObjectName(QString::fromUtf8("lb_colorpreview"));
    lb_colorpreview->setFrameShape(QFrame::Panel);
    lb_colorpreview->setFrameShadow(QFrame::Sunken);
    lb_colorpreview->setWordWrap(false);

    gridLayout->addWidget(lb_colorpreview, 5, 1, 1, 1);

    TextLabel3 = new QLabel(StatePropertiesDlg);
    TextLabel3->setObjectName(QString::fromUtf8("TextLabel3"));
    TextLabel3->setWordWrap(false);

    gridLayout->addWidget(TextLabel3, 3, 0, 1, 1);

    TextLabel2 = new QLabel(StatePropertiesDlg);
    TextLabel2->setObjectName(QString::fromUtf8("TextLabel2"));
    TextLabel2->setWordWrap(false);

    gridLayout->addWidget(TextLabel2, 1, 0, 1, 1);

    PushButton1 = new QPushButton(StatePropertiesDlg);
    PushButton1->setObjectName(QString::fromUtf8("PushButton1"));

    gridLayout->addWidget(PushButton1, 5, 0, 1, 1);

    TextLabel1 = new QLabel(StatePropertiesDlg);
    TextLabel1->setObjectName(QString::fromUtf8("TextLabel1"));
    TextLabel1->setWordWrap(false);

    gridLayout->addWidget(TextLabel1, 0, 0, 1, 1);

    le_radius = new QLineEdit(StatePropertiesDlg);
    le_radius->setObjectName(QString::fromUtf8("le_radius"));

    gridLayout->addWidget(le_radius, 3, 1, 1, 1);

    textLabel1 = new QLabel(StatePropertiesDlg);
    textLabel1->setObjectName(QString::fromUtf8("textLabel1"));
    textLabel1->setWordWrap(false);

    gridLayout->addWidget(textLabel1, 2, 0, 1, 1);

    le_mooreoutputs = new QLineEdit(StatePropertiesDlg);
    le_mooreoutputs->setObjectName(QString::fromUtf8("le_mooreoutputs"));

    gridLayout->addWidget(le_mooreoutputs, 2, 1, 1, 1);

    TextLabel4 = new QLabel(StatePropertiesDlg);
    TextLabel4->setObjectName(QString::fromUtf8("TextLabel4"));
    TextLabel4->setWordWrap(false);

    gridLayout->addWidget(TextLabel4, 4, 0, 1, 1);


    vboxLayout1->addLayout(gridLayout);

    TextLabel1_2 = new QLabel(StatePropertiesDlg);
    TextLabel1_2->setObjectName(QString::fromUtf8("TextLabel1_2"));
    TextLabel1_2->setWordWrap(false);

    vboxLayout1->addWidget(TextLabel1_2);

    te_description = new Q3TextEdit(StatePropertiesDlg);
    te_description->setObjectName(QString::fromUtf8("te_description"));
    te_description->setHScrollBarMode(Q3ScrollView::AlwaysOff);

    vboxLayout1->addWidget(te_description);

    hboxLayout = new QHBoxLayout();
    hboxLayout->setSpacing(6);
    hboxLayout->setMargin(0);
    hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
    PushButton2 = new QPushButton(StatePropertiesDlg);
    PushButton2->setObjectName(QString::fromUtf8("PushButton2"));
    PushButton2->setDefault(true);

    hboxLayout->addWidget(PushButton2);

    PushButton3 = new QPushButton(StatePropertiesDlg);
    PushButton3->setObjectName(QString::fromUtf8("PushButton3"));

    hboxLayout->addWidget(PushButton3);


    vboxLayout1->addLayout(hboxLayout);


    vboxLayout->addLayout(vboxLayout1);

    QWidget::setTabOrder(le_name, le_code);
    QWidget::setTabOrder(le_code, le_mooreoutputs);
    QWidget::setTabOrder(le_mooreoutputs, le_radius);
    QWidget::setTabOrder(le_radius, le_linewidth);
    QWidget::setTabOrder(le_linewidth, PushButton1);
    QWidget::setTabOrder(PushButton1, te_description);
    QWidget::setTabOrder(te_description, PushButton2);
    QWidget::setTabOrder(PushButton2, PushButton3);

    retranslateUi(StatePropertiesDlg);
    QObject::connect(PushButton3, SIGNAL(clicked()), StatePropertiesDlg, SLOT(reject()));
    QObject::connect(PushButton2, SIGNAL(clicked()), StatePropertiesDlg, SLOT(validate()));
    QObject::connect(PushButton1, SIGNAL(clicked()), StatePropertiesDlg, SLOT(chooseFGColor()));

    QMetaObject::connectSlotsByName(StatePropertiesDlg);
    } // setupUi

    void retranslateUi(QDialog *StatePropertiesDlg)
    {
    StatePropertiesDlg->setWindowTitle(QApplication::translate("StatePropertiesDlg", "State Properties", 0, QApplication::UnicodeUTF8));
    le_linewidth->setText(QApplication::translate("StatePropertiesDlg", "1", 0, QApplication::UnicodeUTF8));
    lb_colorpreview->setText(QString());
    TextLabel3->setText(QApplication::translate("StatePropertiesDlg", "Radius:", 0, QApplication::UnicodeUTF8));
    TextLabel2->setText(QApplication::translate("StatePropertiesDlg", "Code:", 0, QApplication::UnicodeUTF8));
    PushButton1->setText(QApplication::translate("StatePropertiesDlg", "Color", 0, QApplication::UnicodeUTF8));
    TextLabel1->setText(QApplication::translate("StatePropertiesDlg", "Name:", 0, QApplication::UnicodeUTF8));
    le_radius->setText(QApplication::translate("StatePropertiesDlg", "40", 0, QApplication::UnicodeUTF8));
    textLabel1->setText(QApplication::translate("StatePropertiesDlg", "Moore Outputs:", 0, QApplication::UnicodeUTF8));
    TextLabel4->setText(QApplication::translate("StatePropertiesDlg", "Line width:", 0, QApplication::UnicodeUTF8));
    TextLabel1_2->setText(QApplication::translate("StatePropertiesDlg", "Description:", 0, QApplication::UnicodeUTF8));
    PushButton2->setText(QApplication::translate("StatePropertiesDlg", "OK", 0, QApplication::UnicodeUTF8));
    PushButton3->setText(QApplication::translate("StatePropertiesDlg", "Cancel", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(StatePropertiesDlg);
    } // retranslateUi

};

namespace Ui {
    class StatePropertiesDlg: public Ui_StatePropertiesDlg {};
} // namespace Ui

class StatePropertiesDlg : public QDialog, public Ui::StatePropertiesDlg
{
    Q_OBJECT

public:
    StatePropertiesDlg(QWidget* parent = 0, const char* name = 0, bool modal = false, Qt::WindowFlags fl = 0);
    ~StatePropertiesDlg();

public slots:
    virtual void chooseFGColor();
    virtual void validate();

protected slots:
    virtual void languageChange();

};

#endif // STATEPROPERTIESDLG_H
