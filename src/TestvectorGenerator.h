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

#ifndef TESTVECTORGENERATOR_H
#define TESTVECTORGENERATOR_H
#include <qstring.h>
#include <qobject.h>
#include <QList>



class Machine;
class GState;
class IOInfo;

/**
 * @class TestvectorGengerator
 * @brief Base class for testvector generator classes.
 *
 */

class TestvectorGenerator : public QObject
{
  Q_OBJECT

  public:
    TestvectorGenerator();
    virtual ~TestvectorGenerator();

    void init(Machine*,bool,bool,bool);

    void generateTestvector();


    QList<IOInfo*> getControlSignalVector() {return control_signal_vector;}

    QList<IOInfo*> getInputVector() {return input_vector;}

    QList<IOInfo*> getMooreOutputVector() {return moore_output_vector;}

    QList<IOInfo*> getMealyOutputVector() {return mealy_output_vector;}

    QList<GState*> getPathRec(QList<GState*> path);

    QList<GState*> getResetPathRec(QList<GState*> path);

    /// Returns the length of the testvector or -1 when
    int getTestvectorLength() {return testvector_length;}

  protected:
    /// Pointer to the machine for testvector generation
    Machine* machine;

    /// Input data vector
    QList<IOInfo*>input_vector;

    /// Control signal vector (synchronous reset, synchronous enable)
    QList<IOInfo*>control_signal_vector;

    /// Expected data of mealy outputs
    QList<IOInfo*>mealy_output_vector;

    /// Expected data of moore outputs
    QList<IOInfo*>moore_output_vector;

    /// Number of enteries in the test vector
    int testvector_length;

    /// If TRUE, the testvector will contain a synchronous reset signal
    bool synchronous_reset;

    /// If TRUE, the testvector will contain a synchronous enable signal
    bool synchronous_enable;

    /// If TRUE, a low-active reset signal is used
    bool negated_reset;

};
#endif // TESTVECTORGENERATOR_H
