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
/*
Qt 4 Port by Rainer Strobel

replaced Qt 3 iterators by Qt 4 iterators
*/

#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <qobject.h>

class MainWindow;
class Machine;
class GState;
class IOInfo;
class SimulatorDlgImpl;

/**
 * @class Simulator
 * @brief Class responsible for all simulation matters.
 */
class Simulator : public QObject {
  Q_OBJECT

public:
  Simulator(MainWindow *);
  ~Simulator();

  bool startSimulation(Machine *);
  void enableButtons();

private:
  /// Pointer to the main windows
  MainWindow *main;
  /// Simulator dialog
  SimulatorDlgImpl *simdlg;
  /// Pointer to the machine to simulate
  Machine *machine;

  /// Current state (during simulation)
  GState *current_state;

  GState *next(IOInfo *, QString &);
  void setCurrentState(GState *);

public slots:
  void reset();
  void next();
  void stopSimulation();
  void closeDlg();
};

#endif
