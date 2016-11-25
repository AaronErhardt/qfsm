#pragma once
#include "qwidget.h"
class GeneralTab :
	public QWidget
{
	Q_OBJECT

public:
	explicit GeneralTab(const QFileInfo &fileInfo, QWidget *parent = 0);
};

