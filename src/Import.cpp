/*
Copyright (C) 2000,2001 Stefan Duffner 

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/


#include <iostream>
#include <qapplication.h>
#include "Import.h"
#include "Project.h"
#include "AppInfo.h"
#include "MainWindow.h"


//using namespace std;

/// Standard constructor.
Import::Import(Options* opt) : QObject()
{
  options = opt;
  in = &std::cin;
  project=NULL;
  scrollview=NULL;
}

/// Destructor
Import::~Import() 
{
}


/**
 * Initializes the import object.
 * @a i is a pointer to the input stream opened with the standard fstream methods.
 */
void Import::init(std::istream* i, MainWindow* main, QString fn/*=QString::null*/, ScrollView* sv/*=NULL*/)
{
  in = i;
  fileName = fn;
  scrollview = sv;
  project = new Project(main);
}

