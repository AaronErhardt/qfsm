#pragma once
#include "qdialog.h"
#include "QtWidgets/QTabWidget.h"
#include "QtWidgets/QDialogButtonBox.h"
class TabDialog :
	public QDialog
{
	Q_OBJECT

public:
	explicit TabDialog(const QString &fileName, QWidget *parent = 0);
	virtual ~TabDialog();

private:
	QTabWidget *tabWidget;
	QDialogButtonBox *buttonBox;

};

