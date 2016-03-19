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

changed drawPrimitive calls for Qt 4 QStyle class
replaced p->moveTo and p->lineTo drawing commands by p->drawLine

*/

#ifndef LISTBOXITEMS_H
#define LISTBOXITEMS_H

class QListbox;

/**
 * @class LBArrowLine
 * @brief Listbox item for the machine properties dialog.
 *
 * Listbox item which paints the unfilled arrowhead for a transition.
 */
class LBArrowLine : public Q3ListBoxItem
{
  public:
    LBArrowLine(Q3ListBox*);

    int height(const Q3ListBox*) const;
    int width(const Q3ListBox*) const;
    void paint(QPainter*);

  private:
    /// Height of the item
    int h;
    /// Width of the item
    int w;
};

/**
 * @class LBArrowFilled
 * ListBox item for the machine properties dialog.
 * Listbox item which paints the filled arrowhead for a transition.
 */
class LBArrowFilled : public Q3ListBoxItem
{
  public:
    LBArrowFilled(Q3ListBox*);

    int height(const Q3ListBox*) const;
    int width(const Q3ListBox*) const;
    void paint(QPainter*);

  private:
    /// Height of the item
    int h;
    /// Width of the item
    int w;
};


/**
 * @class LBArrowWhite
 * ListBox item for the machine properties dialog.
 * Listbox item which paints the white arrowhead for a transition.
 */
class LBArrowWhite : public Q3ListBoxItem
{
  public:
    LBArrowWhite(Q3ListBox*);

    int height(const Q3ListBox*) const;
    int width(const Q3ListBox*) const;
    void paint(QPainter*);

  private:
    /// Height of the item
    int h;
    /// Width of the item
    int w;
};


/**
 * @class LBArrowFilledPointed
 * ListBox item for the machine properties dialog.
 * Listbox item which paints the filled pointed arrowhead for a transition.
 */
class LBArrowFilledPointed : public Q3ListBoxItem
{
  public:
    LBArrowFilledPointed(Q3ListBox*);

    int height(const Q3ListBox*) const;
    int width(const Q3ListBox*) const;
    void paint(QPainter*);

  private:
    /// Height of the item
    int h;
    /// Width of the item
    int w;
};

/**
 * @class LBArrowWhitePointed
 * ListBox item for the machine properties dialog.
 * Listbox item which paints the white pointed arrowhead for a transition.
 */
class LBArrowWhitePointed : public Q3ListBoxItem
{
  public:
    LBArrowWhitePointed(Q3ListBox*);

    int height(const Q3ListBox*) const;
    int width(const Q3ListBox*) const;
    void paint(QPainter*);

  private:
    /// Height of the item
    int h;
    /// Width of the item
    int w;
};


#endif
