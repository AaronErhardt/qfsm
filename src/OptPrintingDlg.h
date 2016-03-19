#ifndef OPTPRINTINGDLG_H
#define OPTPRINTINGDLG_H

#include <qvariant.h>


#include <Qt3Support/Q3MimeSourceFactory>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>

class Ui_OptPrintingDlg
{
public:
    QHBoxLayout *hboxLayout;
    QCheckBox *cb_print_header;

    void setupUi(QDialog *OptPrintingDlg)
    {
    if (OptPrintingDlg->objectName().isEmpty())
        OptPrintingDlg->setObjectName(QString::fromUtf8("OptPrintingDlg"));
    OptPrintingDlg->resize(405, 282);
    hboxLayout = new QHBoxLayout(OptPrintingDlg);
    hboxLayout->setSpacing(6);
    hboxLayout->setMargin(11);
    hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
    cb_print_header = new QCheckBox(OptPrintingDlg);
    cb_print_header->setObjectName(QString::fromUtf8("cb_print_header"));

    hboxLayout->addWidget(cb_print_header);


    retranslateUi(OptPrintingDlg);
    QObject::connect(cb_print_header, SIGNAL(clicked()), OptPrintingDlg, SLOT(printHeaderClicked()));

    QMetaObject::connectSlotsByName(OptPrintingDlg);
    } // setupUi

    void retranslateUi(QDialog *OptPrintingDlg)
    {
    OptPrintingDlg->setWindowTitle(QApplication::translate("OptPrintingDlg", "Printing", 0, QApplication::UnicodeUTF8));
    cb_print_header->setText(QApplication::translate("OptPrintingDlg", "Print header", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(OptPrintingDlg);
    } // retranslateUi

};

namespace Ui {
    class OptPrintingDlg: public Ui_OptPrintingDlg {};
} // namespace Ui

class OptPrintingDlg : public QDialog, public Ui::OptPrintingDlg
{
    Q_OBJECT

public:
    OptPrintingDlg(QWidget* parent = 0, const char* name = 0, bool modal = false, Qt::WindowFlags fl = 0);
    ~OptPrintingDlg();

public slots:
    virtual void printHeaderClicked();

protected slots:
    virtual void languageChange();

};

#endif // OPTPRINTINGDLG_H
