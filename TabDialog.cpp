#include "TabDialog.h"
#include "QFileInfo.h"
#include "GeneralTab.h"
#include "PermissionsTab.h"
#include "ApplicationsTab.h"
#include "QtWidgets/QVBoxLayout.h"



TabDialog::TabDialog(const QString &fileName, QWidget *parent)
	: QDialog(parent)
{
	QFileInfo fileInfo(fileName);

	tabWidget = new QTabWidget;
	tabWidget->addTab(new GeneralTab(fileInfo), tr("General"));
	tabWidget->addTab(new PermissionsTab(fileInfo), tr("Permissions"));
	tabWidget->addTab(new ApplicationsTab(fileInfo), tr("Applications"));

	buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
		| QDialogButtonBox::Cancel);

	connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
	connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addWidget(tabWidget);
	mainLayout->addWidget(buttonBox);
	setLayout(mainLayout);

	setWindowTitle(tr("Tab Dialog"));
}

TabDialog::~TabDialog()
{
}
