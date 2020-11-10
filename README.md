Qfsm 0.56
=========

About
-----
Qfsm is a graphical tool for designing finite state machine.
It is written in C++ using the Qt library.
Features include:

- Drawing, Editing and Printing of states diagrams
- Binary, ASCII or "free text" condition codes
- Integrity check
- Interactive simulation
- HDL export in the file formats: AHDL, VHDL, Verilog HDL, KISS
- Creation of VHDL test code
- Diagram export in the formats: EPS, SVG and PNG
- State table export in Latex, HTML or plain text format
- Ragel file export (used for C/C++, Java or Ruby code generation)
- State Machine Compiler (SMC) export (supporting code generation in many programming languages)
- Other export formats: SCXML, vvvv Automata code
- Import of DOT files (Graphviz) and automatic creation of state diagrams from textual descriptions


Download
--------
AppImage packages, pre-compiled binaries of Qfsm and the source code of the latest releases are available at: https://github.com/AaronErhardt/qfsm/releases.


Requirements
------------

> The AppImage version has all dependencies included so you don't need to install anything by yourself.

- Qt 4.8 (available from https://download.qt.io/archive/qt/4.8/4.8.7/)

Optional:

- graphviz  (to import graphviz (.gv) files)

Installation
------------
Follow the standard installation procedure as explained in the file [INSTALL.md](https://github.com/AaronErhardt/qfsm/blob/master/INSTALL.md).


Running
-------
If installed correctly you can simply start Qfsm from your application launcher.

If you want to run Qfsm from the console however, type:

`qfsm [file ... ]`

As parameters you can specify an arbitrary number of files that
shall be opened on startup.


Manual
------
The user manual can be found at this url: [https://aaronerhardt.github.io/qfsm/manual](https://aaronerhardt.github.io/qfsm/manual/).


Docs for developers
-------------------
The documentation of Qfsm can be found at this url: [https://aaronerhardt.github.io/qfsm/docs](https://aaronerhardt.github.io/qfsm/docs/).


Older Versions
--------------
Older versions of Qfsm are available from [Sourceforge](https://sourceforge.net/projects/qfsm/). The older Versions include a Windows installer, rpm packages and the source code. But keep in mind that several bug fixes aren't included in older releases.


Bugs
----
Please report bugs through the [issue tracker on GitHub](https://github.com/AaronErhardt/qfsm)


Contribution
-------
Simply fork this repository, create your own branch, apply changes and open a pull request. This allows us to review your code easily and merge into the code base.


Contact
-------
If you have questions, suggestions, comments or want to contribute, please contact us by e-mail:

qfsm (at) duffner (dash) net (dot) de
