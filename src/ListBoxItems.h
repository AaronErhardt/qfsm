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

#pragma once

class QListbox;

class ListBoxItem : public QListWidgetItem {
  public:
    ListBoxItem(QListWidget*);
    QPixmap *icon_to_be_shown;
  private:
    QListWidget* list;
};
/**
 * @class LBArrowLine
 * @brief Listbox item for the machine properties dialog.
 *
 * Listbox item which paints the unfilled arrowhead for a transition.
 */
class LBArrowLine : public ListBoxItem {
  public:
    LBArrowLine(QListWidget*);

    int height(const QListWidget*) const;
    int width(const QListWidget*) const;
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
class LBArrowFilled : public ListBoxItem {
  public:
    LBArrowFilled(QListWidget*);

    int height(const QListWidget*) const;
    int width(const QListWidget*) const;
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
class LBArrowWhite : public ListBoxItem {
  public:
    LBArrowWhite(QListWidget*);

    int height(const QListWidget*) const;
    int width(const QListWidget*) const;
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
class LBArrowFilledPointed : public ListBoxItem {
  public:
    LBArrowFilledPointed(QListWidget*);

    int height(const QListWidget*) const;
    int width(const QListWidget*) const;
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
class LBArrowWhitePointed : public ListBoxItem {
  public:
    LBArrowWhitePointed(QListWidget*);

    int height(const QListWidget*) const;
    int width(const QListWidget*) const;
    void paint(QPainter*);

  private:
    /// Height of the item
    int h;
    /// Width of the item
    int w;
};