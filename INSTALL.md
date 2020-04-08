Installation Instructions
*************************

Binary installation
===================

Windows
-------
Currently pre-compiled binaries are available at the [GitHub repository](https://github.com/AaronErhardt/qfsm/releases). However you might still need to install QT4 and graphviz yourself. If you know how to build a Windows installer your help would be appreciated a lot.

There exists a (graphical) Windows installer for older versions however that can be downloaded from http://www.sourceforge.net/projects/qfsm. The installation should be straightforward and doesn't require any other software to be installed.


Linux
-----
Linux binaries are available from the [GitHub repository](https://github.com/AaronErhardt/qfsm/releases). Currently only raw binaries are available which means that you need to install QT4 (likely called libqt4) and graphviz (likely called libgraphviz-dev) by yourself. In the future we will try to provide packages that can be installed more easily on various Linux distributions.


Mac OS X
--------
Binary packages for Mac OS X may be provided by third-party websites, like
http://mac.softpedia.com/get/Math-Scientific/Qfms.shtml.



Installing from source code
===========================


Qfsm has to be compiled using the CMake buildsystem. 


Requirements
------------
- CMake, version 2.8 or higher (http://www.cmake.org)
- Qt SDK, version 4.8 or higher (available from https://download.qt.io/archive/qt/4.8/4.8.7/)
- graphviz, version 2.38 or higher (http://graphviz.org)


See the documentation of these tools/libraries for an explanation how to install them.



Building under GNU Linux/Unix
-----------------------------

Install the above-mentioned required software. If you install them via a package manager make sure you install the development packages (...-dev or ...-devel).

On Debian-based systems (like Ubuntu and Linux Mint) you will likely need to install the packages `libqt4-dev` and `libgraphviz-dev`.

Unpack the source code into the current directory

`unzip qfsm-0.55.0-Source.zip`

and change to that directory.

Before invoking CMake you have to make sure that the program qmake is in your global PATH environment variable. On most Linux-distributions this will work automatically but in case is doesn't work simply the following step:  
The location of qmake depends on your operating system or Linux distribution. On openSUSE for example it is under: /usr/lib/qt4/bin/
Thus, if you are using bash, you would have to type:

export PATH=/usr/lib/qt4/bin:$PATH

**Configure and compile:**

`cmake .`

Then:

`make`

Finally, install Qfsm (as root):

`make install`

This will install the executable "qfsm" to /usr/bin/ and the documentation to /usr/share/doc/qfsm/.

If CMake fails to find any of the dependencies but you know you have the
development headers/libraries installed, add -DLIBRARY_SEARCH_DIRS=<path/to/lib>
and -DINCLUDE_SEARCH_DIRS=<path/to/include> to the cmake command.

If you want to create a project file for your IDE (e.g. KDevelop), add
-GKDevelop3 to the cmake command above. This will create a .kdevelop file in
the build directory which can be opened by KDevelop.



Building under Windows
----------------------

In order to build Qfsm under Windows you have to execute the program CMakeSetup, specify input (source) and output directory and click on "Configure". 
You may choose between different development environments (e.g. Visual Studio) and CMake will create the respective project files.
You can then compile Qfsm as usual with your preferred build tool.
For more details, refer to the CMake documentation: http://www.cmake.org/HTML/Documentation.html.

Compiling with Graphviz support:
- download the binary graphviz package from http://www.graphviz.org/Download_windows.php.
- unpack and copy the contents of the release folder to something like "C:\graphviz" 
- if you copy it to another folder change the paths in graphviz_INCLUDE_DIRS and graphviz_LIBRARY_DIRS in CMakeLists.txt accordingly
- run cmake
- compile

