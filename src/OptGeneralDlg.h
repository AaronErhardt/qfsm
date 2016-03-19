#ifndef OPTGENERALDLG_H
#define OPTGENERALDLG_H

#include <qvariant.h>


#include <Qt3Support/Q3MimeSourceFactory>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

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
    vboxLayout->setMargin(0);
    vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
    vboxLayout->setContentsMargins(0, 0, 0, 0);
    hboxLayout = new QHBoxLayout();
    hboxLayout->setSpacing(6);
    hboxLayout->setMargin(0);
    hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
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
    Q_UNUSED(OptGeneralDlg);
    } // retranslateUi

};

namespace Ui {
    class OptGeneralDlg: public Ui_OptGeneralDlg {};
} // namespace Ui

class OptGeneralDlg : public QDialog, public Ui::OptGeneralDlg
{
    Q_OBJECT

public:
    OptGeneralDlg(QWidget* parent = 0, const char* name = 0, bool modal = false, Qt::WindowFlags fl = 0);
    ~OptGeneralDlg();

protected slots:
    virtual void languageChange();

};

#endif // OPTGENERALDLG_H
