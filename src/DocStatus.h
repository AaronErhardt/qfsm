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

#ifndef DOCSTATUS_H
#define DOCSTATUS_H


/**
 * @class DocStatus
 * @brief Stores the current status of the document.
 *
 * The current status of the document includes the mode in which the document
 * is in. This determines e.g. what happens if the user presses a mouse button
 * inside the view.
 */



class DocStatus
{
  public:
    DocStatus();
    ~DocStatus();

    /**
     * Document modes.
     * These are the modes a document can be in. The default one is @a Select.
     */
    enum Mode {
      Select, 		///< Select 
      Pan,		///< Pan view
      NewState, 	///< Add new states
      NewTransition, 	///< Add new transitions
      Zooming, 		///< Zoom in/out
      Simulating	///< Simultate the machine
    };

    int getMode() /// Gets the current mode of the document. 
      { return mode; };
    void setMode(int m) /// Sets the current mode @a m of the document. 
      { mode = m; };

  private:
    /// Mode 
    int mode;
};




#endif
