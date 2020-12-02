PROJECT(qfsm)

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

#SET( CMAKE_BUILD_TYPE Debug )
SET( CMAKE_BUILD_TYPE Release )

#INCLUDE(FindGraphviz.cmake)

#INCLUDE_DIRECTORIES(/usr/include/Qt
#/usr/include/ActiveQt
#/usr/include/Qt3Support
#/usr/include/QtAssistant
#/usr/include/QtCore
#/usr/include/QtDesigner
#/usr/include/QtGui
#/usr/include/QtTest
#/usr/include/QtUiTools
#/usr/include/QtXml
#/usr/include/QtNetwork
#/usr/include/QtSql
#/usr/include/QtSvg
#/usr/include/QtOpenGL
#/usr/include/QtDBus
#/usr/include
#src/
#.)

INCLUDE(mycmake.cmake)


INCLUDE_DIRECTORIES ( ${QT_INCLUDE_DIR} ${QT_QT3SUPPORT_INCLUDE_DIR} ${QT_QTGUI_INCLUDE_DIR} ${QT_QTCORE_INCLUDE_DIR} src .)

SET(CMAKE_MODULE_PATH "${qfsm_SOURCE_DIR}")

IF ( WIN32 )
  SET(graphviz_INCLUDE_DIRS "C:\\Program Files\\Graphviz2.38\\include\\graphviz")
  SET(graphviz_LIBRARY_DIRS "C:\\Program Files\\Graphviz2.38\\lib\\release\\lib")
  SET(CMAKE_PREFIX_PATH "C:\\Program Files\\Graphviz2.38")
ENDIF ( WIN32 )


FIND_PACKAGE(GraphViz)
IF(graphviz_FOUND)
  MESSAGE("Graphviz library found")
  #ADD_DEFINITIONS(-DGRAPHVIZ_FOUND -DHAVE_STRING_H -DWITH_CGRAPH)
  ADD_DEFINITIONS(-DGRAPHVIZ_FOUND -DHAVE_STRING_H)
  INCLUDE_DIRECTORIES( ${graphviz_INCLUDE_DIRECTORIES} )
#  MESSAGE( ${graphviz_INCLUDE_DIRECTORIES} )
#  MESSAGE( ${graphviz_LIBRARIES} )
ELSE(graphviz_FOUND)
  MESSAGE("WARNING: Graphviz library not found")
ENDIF(graphviz_FOUND)

FIND_PACKAGE(Qt4 REQUIRED)

ADD_DEFINITIONS(-DQT3_SUPPORT -DSVG)

SET( QT_USE_QT3SUPPORT TRUE )
SET( QT_USE_QTXML TRUE )
SET( QT_USE_QTSVG TRUE )
SET( QT_USE_QTGUI TRUE )


INCLUDE(${QT_USE_FILE})

SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "A graphical tool for designing finite state machines")
SET(CPACK_PACKAGE_VENDOR "")
SET(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/README.md")
SET(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/COPYRIGHT")
SET(CPACK_PACKAGE_VERSION_MAJOR "0")
SET(CPACK_PACKAGE_VERSION_MINOR "56")
SET(CPACK_PACKAGE_VERSION_PATCH "0")
#SET(CPACK_PACKAGE_INSTALL_DIRECTORY "Qfsm_${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}")
SET(CPACK_PACKAGE_INSTALL_DIRECTORY "Qfsm")
IF(WIN32 AND NOT UNIX)
    # There is a bug in NSI that does not handle full unix paths properly. Make
    # sure there is at least one set of four (4) backlasshes.
#  SET(CPACK_PACKAGE_ICON "${CMake_SOURCE_DIR}/desktop/64x64/apps/qfsm.png")
  SET(CPACK_PACKAGE_ICON "${PROJECT_SOURCE_DIR}/desktop/64x64/apps\\\\qfsm.png")
  SET(CPACK_NSIS_INSTALLED_ICON_NAME "bin\\\\qfsm.exe")
  SET(CPACK_NSIS_DISPLAY_NAME "${CPACK_PACKAGE_INSTALL_DIRECTORY}")
  SET(CPACK_NSIS_HELP_LINK "http://www.sourceforge.net/projects/qfsm")
  SET(CPACK_NSIS_URL_INFO_ABOUT "http://qfsm.sourceforge.net")
  SET(CPACK_NSIS_CONTACT "qfsm@duffner-net.de")
  SET(CPACK_NSIS_MODIFY_PATH ON)
ELSE(WIN32 AND NOT UNIX)
  SET(CPACK_STRIP_FILES "bin/qfsm")
  SET(CPACK_SOURCE_STRIP_FILES "")
ENDIF(WIN32 AND NOT UNIX)
SET(CPACK_PACKAGE_EXECUTABLES "qfsm;qfsm")
SET(CPACK_GENERATOR "")
SET(CPACK_SOURCE_GENERATOR "TBZ2")
SET(CPACK_SOURCE_IGNORE_FILES "^${PROJECT_SOURCE_DIR}/src/ui_*;/CVSROOT/;install_manifest.txt;cmake_install.cmake;^${PROJECT_SOURCE_DIR}/src/qfsm$;^${PROJECT_SOURCE_DIR}/qfsm$;^${PROJECT_SOURCE_DIR}/qfsm.pro;/tmp/;patches;test_machines;qfsm_tmp;old;CPack.*;CMakeCache.txt;/CMakeFiles/;\\\\.o$;moc_.*;/CVS/;/\\\\.svn/;\\\\.swp$;\\\\.#;/#;.*~;cscope.*")

SET(CMAKE_MODULE_PATH ".")
INCLUDE(CPack)
#INCLUDE(UseRPMTools)
#IF(RPMTools_FOUND)
#RPMTools_ADD_RPM_TARGETS(qfsm)
#ENDIF(RPMTools_FOUND)


SET(moc_h 	src/AppInfo.h 	src/Const.h 	src/Convert.h 	src/DocStatus.h 	src/Draw.h 
	src/DrawArea.h
	src/DRect.h 
	src/Edit.h 
	src/Error.h 
	src/Export.h 
	src/ExportAHDL.h  
    src/ExportAHDLDlgImpl.h 
	src/ExportKISS.h 
	src/ExportRagel.h 
	src/ExportRagelDlgImpl.h 
	src/ExportStateTable.h 
	src/ExportStateTableDlgImpl.h  
    src/ExportVerilogDlgImpl.h 
	src/ExportVHDL.h 
	src/ExportPNG.h 
	src/ExportIODescription.h
        src/ExportVHDLDlgImpl.h 
        src/ExportTestbenchVHDL.h
        src/ExportTestbenchDlgImpl.h
        src/ExportTestvectorASCII.h
        src/ExportVVVVDlgImpl.h	
        src/TestvectorGenerator.h
	src/ExportSVG.h 
	src/ExportEPS.h 
	src/ExportVVVV.h
	src/ExportSCXML.h
	src/FileIO.h 
	src/GITransition.h 
	src/GObject.h 
	src/Grid.h 
	src/GState.h 
	src/GTransition.h 
    src/ICheckDlgImpl.h 
	src/Import.h 
	src/ImportGraphviz.h 
	src/IOInfo.h 
	src/IOInfoASCII.h 
	src/IOInfoBin.h 
	src/IOInfoList.h 
	src/IOInfoText.h 
  src/IOViewDlgImpl.h
	src/ListBoxItems.h 
	src/Machine.h 
	src/MachineManager.h 
    src/MachinePropertiesDlgImpl.h 
	src/MainControl.h 
	src/MainWindow.h 
	src/MimeMachine.h  
    src/OptDisplayDlgImpl.h 
	src/OptGeneral.h 
    src/OptGeneralDlgImpl.h 
	src/Options.h 
    src/OptPrintingDlgImpl.h 
	src/PrintManager.h 
	src/Project.h 
	src/ScrollView.h 
	src/Selection.h 
	src/Simulator.h 
    src/SimulatorDlgImpl.h 
	src/StateManager.h 
    src/StatePropertiesDlgImpl.h 
	src/StatusBar.h 
	src/TableBuilder.h 
	src/TableBuilderASCII.h 
	src/TableBuilderHTML.h 
	src/TableBuilderLatex.h 
	src/ToolTipSV.h 
	src/Transition.h 
	src/TransitionInfo.h 
	src/TransitionInfoASCII.h 
	src/TransitionInfoBin.h 
	src/TransitionInfoText.h 
	src/TransitionManager.h 
    src/TransitionPropertiesDlgImpl.h 
	src/Undo.h 
	src/UndoBuffer.h 
	src/Utils.h 
	src/WSpinBox.h 
	src/XMLHandler.h 
	src/Zoom.h)
	
SET(src_h src/AppInfo.h 
	src/Const.h 
	src/Convert.h 
	src/DocStatus.h 
	src/Draw.h 
	src/DrawArea.h
	src/DRect.h 
	src/Edit.h 
	src/Error.h 
	src/Export.h 
	src/ExportAHDL.h 
    src/ExportAHDLDlgImpl.h 
	src/ExportKISS.h 
	src/ExportRagel.h 
	src/ExportRagelDlgImpl.h 
	src/ExportStateTable.h 
	src/ExportStateTableDlgImpl.h 
	src/ExportVerilog.h 
    src/ExportVerilogDlgImpl.h 
	src/ExportVHDL.h
	src/ExportPNG.h 
	src/ExportIODescription.h
    src/ExportVHDLDlgImpl.h 
        src/ExportTestbenchVHDL.h
        src/ExportTestbenchDlgImpl.h
        src/ExportTestvectorASCII.h
    src/ExportVVVVDlgImpl.h 
        src/TestvectorGenerator.h
	src/ExportSVG.h 
	src/ExportEPS.h 
	src/ExportVVVV.h
	src/ExportSCXML.h
	src/ExportSMC.h
	src/FileIO.h 
	src/GITransition.h 
	src/GObject.h 
	src/Grid.h 
	src/GState.h 
	src/GTransition.h 
	src/ICheck.h 
    src/ICheckDlgImpl.h 
    src/Import.h
	src/ImportGraphviz.h 
	src/IOInfo.h 
	src/IOInfoASCII.h 
	src/IOInfoBin.h 
	src/IOInfoList.h 
	src/IOInfoText.h 
  src/IOViewDlgImpl.h 
	src/ListBoxItems.h 
	src/Machine.h 
	src/MachineManager.h 
    src/MachinePropertiesDlgImpl.h 
	src/MainControl.h 
	src/MainWindow.h 
	src/MimeMachine.h 
    src/OptDisplayDlgImpl.h 
	src/OptGeneral.h 
    src/OptGeneralDlgImpl.h 
	src/Options.h 
    src/OptPrintingDlgImpl.h 
	src/PrintManager.h 
	src/Project.h 
	src/ScrollView.h 
	src/Selection.h 
	src/Simulator.h 
    src/SimulatorDlgImpl.h 
	src/State.h 
	src/StateManager.h 
    src/StatePropertiesDlgImpl.h 
	src/StatusBar.h 
	src/TableBuilder.h 
	src/TableBuilderASCII.h 
	src/TableBuilderHTML.h 
	src/TableBuilderLatex.h 
	src/ToolTipSV.h 
	src/Transition.h 
	src/TransitionInfo.h 
	src/TransitionInfoASCII.h 
	src/TransitionInfoBin.h 
	src/TransitionInfoText.h 
	src/TransitionManager.h 
    src/TransitionPropertiesDlgImpl.h 
	src/Undo.h 
	src/UndoBuffer.h 
	src/Utils.h 
	src/WSpinBox.h 
	src/XMLHandler.h 
	src/Zoom.h

)
	
SET(src_cxx src/AppInfo.cpp 
	src/Convert.cpp 
	src/DocStatus.cpp 
	src/Draw.cpp
	src/DrawArea.cpp
	src/DRect.cpp 
	src/Edit.cpp 
	src/Error.cpp 
	src/Export.cpp 
	src/ExportAHDL.cpp 
	src/ExportAHDLDlgImpl.cpp 
	src/ExportKISS.cpp 
	src/ExportRagel.cpp 
	src/ExportRagelDlgImpl.cpp   
	src/ExportStateTable.cpp 
	src/ExportStateTableDlgImpl.cpp 
	src/ExportVerilog.cpp 
    src/ExportVerilogDlgImpl.cpp 
	src/ExportVHDL.cpp
	src/ExportPNG.cpp 
	src/ExportIODescription.cpp
    src/ExportVHDLDlgImpl.cpp 
        src/ExportTestbenchVHDL.cpp
        src/ExportTestbenchDlgImpl.cpp
        src/ExportTestvectorASCII.cpp
	src/ExportVVVVDlgImpl.cpp 
	src/ExportVVVV.cpp
	src/ExportSCXML.cpp
	src/ExportSMC.cpp
        src/TestvectorGenerator.cpp
	src/FileIO.cpp 
	src/ExportSVG.cpp 
	src/ExportEPS.cpp 
	src/GITransition.cpp 
	src/GObject.cpp 
	src/Grid.cpp 
	src/GState.cpp 
	src/GTransition.cpp 
	src/ICheck.cpp 
    src/ICheckDlgImpl.cpp 
    src/Import.cpp 
	src/ImportGraphviz.cpp 
	src/IOInfo.cpp 
	src/IOInfoASCII.cpp 
	src/IOInfoBin.cpp 
	src/IOInfoList.cpp 
	src/IOInfoText.cpp 
  src/IOViewDlgImpl.cpp 
	src/ListBoxItems.cpp 
	src/Machine.cpp 
	src/MachineManager.cpp 
    src/MachinePropertiesDlgImpl.cpp 
	src/main.cpp 
	src/MainControl.cpp 
	src/MainWindow.cpp 
	src/MimeMachine.cpp 
    src/OptDisplayDlgImpl.cpp 
	src/OptGeneral.cpp 
    src/OptGeneralDlgImpl.cpp 
	src/Options.cpp 
    src/OptPrintingDlgImpl.cpp 
	src/PrintManager.cpp 
	src/Project.cpp 
	src/ScrollView.cpp 
	src/Selection.cpp 
	src/Simulator.cpp 
    src/SimulatorDlgImpl.cpp 
	src/State.cpp 
	src/StateManager.cpp 
    src/StatePropertiesDlgImpl.cpp 
	src/StatusBar.cpp 
	src/TableBuilder.cpp 
	src/TableBuilderASCII.cpp 
	src/TableBuilderHTML.cpp 
	src/TableBuilderLatex.cpp 
	src/ToolTipSV.cpp 
	src/Transition.cpp 
	src/TransitionInfo.cpp 
	src/TransitionInfoASCII.cpp 
	src/TransitionInfoBin.cpp 
	src/TransitionInfoText.cpp 
	src/TransitionManager.cpp 
    src/TransitionPropertiesDlgImpl.cpp 
	src/Undo.cpp 
	src/UndoBuffer.cpp 
	src/Utils.cpp 
	src/WSpinBox.cpp 
	src/XMLHandler.cpp 
	src/Zoom.cpp
)

SET(src_ui 
        src/ExportAHDLDlg.ui
        src/ExportAHDLDlg.ui
	src/ExportRagelDlg.ui
	src/ExportStateTableDlg.ui
	src/ExportTestbenchDlg.ui
	src/ExportVerilogDlg.ui
	src/ExportVHDLDlg.ui
	src/ExportVVVVDlg.ui
	src/ICheckDlg.ui
  	src/IOViewDlg.ui 
	src/MachinePropertiesDlg.ui
	src/OptDisplayDlg.ui
	src/OptGeneralDlg.ui
	src/OptPrintingDlg.ui
	src/SimulatorDlg.ui
	src/StatePropertiesDlg.ui
	src/TransitionPropertiesDlg.ui
)

IF(WIN32)
   SET(src_cxx 
                ${src_cxx}
                desktop/qfsm.rc
      )
   SET(src_h 
                ${src_h}
                desktop/resource.h
      )
ENDIF(WIN32)




QT4_WRAP_CPP(moc_cxx ${moc_h})

#QT4_WRAP_UI(ui_h ${src_ui})
MY_QT4_WRAP_UI(ui_h ${src_ui})
#QT4_WRAP_UI(GUI_HEADERS ${GUI})
include_directories(${CMAKE_CURRENT_BINARY_DIR})


#ADD_EXECUTABLE(qfsm WIN32 ${src_cxx} ${src_h} ${moc_cxx} ${moc_ui_cxx} ${src_ui_cxx} ${GUI_HEADERS})
ADD_EXECUTABLE(qfsm WIN32 ${src_cxx} ${src_h} ${moc_cxx} ${moc_ui_cxx} ${src_ui_cxx} ${src_ui})

#TARGET_LINK_LIBRARIES(qfsm ${QT_LIBRARIES} ${graphviz_GVC_LIBRARY} ${graphviz_GRAPH_LIBRARY} ${graphviz_CDT_LIBRARY} ${graphviz_PATHPLAN_LIBRARY})
TARGET_LINK_LIBRARIES(qfsm ${QT_LIBRARIES} ${graphviz_LIBRARIES})



IF(UNIX AND NOT WIN32)
  SET(CMAKE_INSTALL_PREFIX "/usr")
ENDIF(UNIX AND NOT WIN32)

IF(UNIX AND NOT WIN32)
  ADD_DEFINITIONS(-DQFSM_LANGUAGE_DIR="${CMAKE_INSTALL_PREFIX}/share/qfsm/")
  ADD_DEFINITIONS(-DQFSM_HELP_DIR="${CMAKE_INSTALL_PREFIX}/share/doc/qfsm/")
ELSE(UNIX AND NOT WIN32)
  ADD_DEFINITIONS(-DQFSM_LANGUAGE_DIR=\"po\")
  ADD_DEFINITIONS(-DQFSM_HELP_DIR=\"doc\\\\user\")
ENDIF(UNIX AND NOT WIN32)


IF(UNIX AND NOT WIN32)
  INSTALL(TARGETS qfsm RUNTIME DESTINATION bin
      PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ
		  GROUP_EXECUTE GROUP_READ
		  WORLD_EXECUTE WORLD_READ)
  INSTALL(DIRECTORY doc/user/ DESTINATION share/doc/qfsm
      PATTERN "CVS" EXCLUDE
      PERMISSIONS OWNER_WRITE OWNER_READ GROUP_READ WORLD_READ)
  INSTALL(FILES desktop/qfsm.desktop DESTINATION share/applications
      PERMISSIONS OWNER_WRITE OWNER_READ GROUP_READ WORLD_READ)
  INSTALL(FILES desktop/x-qfsm.desktop DESTINATION share/mimelnk/application
      PERMISSIONS OWNER_WRITE OWNER_READ GROUP_READ WORLD_READ)
  INSTALL(DIRECTORY desktop/32x32 DESTINATION share/icons/hicolor
      PATTERN "CVS" EXCLUDE
      PERMISSIONS OWNER_WRITE OWNER_READ GROUP_READ WORLD_READ)
  INSTALL(DIRECTORY desktop/48x48 DESTINATION share/icons/hicolor
      PATTERN "CVS" EXCLUDE
      PERMISSIONS OWNER_WRITE OWNER_READ GROUP_READ WORLD_READ)
  INSTALL(DIRECTORY desktop/64x64 DESTINATION share/icons/hicolor
      PATTERN "CVS" EXCLUDE
      PERMISSIONS OWNER_WRITE OWNER_READ GROUP_READ WORLD_READ)
  INSTALL(FILES po/English.qm po/French.qm po/German.qm po/Russian.qm DESTINATION share/qfsm
      PERMISSIONS OWNER_WRITE OWNER_READ GROUP_READ WORLD_READ)
  INSTALL(DIRECTORY examples DESTINATION share/qfsm
      PATTERN "CVS" EXCLUDE
      PERMISSIONS OWNER_WRITE OWNER_READ GROUP_READ WORLD_READ)
ELSE(UNIX AND NOT WIN32)
  INSTALL(TARGETS qfsm RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}
#  INSTALL(TARGETS qfsm RUNTIME DESTINATION ${DESTDIR}
      PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ
		  GROUP_EXECUTE GROUP_READ
		  WORLD_EXECUTE WORLD_READ)
  INSTALL(DIRECTORY doc/user DESTINATION doc
      PATTERN "CVS" EXCLUDE
      PERMISSIONS OWNER_WRITE OWNER_READ GROUP_READ WORLD_READ)
  INSTALL(FILES po/English.qm po/French.qm po/German.qm po/Russian.qm DESTINATION po
      PERMISSIONS OWNER_WRITE OWNER_READ GROUP_READ WORLD_READ)
  INSTALL(DIRECTORY examples DESTINATION ${CMAKE_INSTALL_PREFIX}
      PATTERN "CVS" EXCLUDE
      PERMISSIONS OWNER_WRITE OWNER_READ GROUP_READ WORLD_READ)
  INSTALL(FILES
        "${QT_LIBRARY_DIR}/QtCore${QT_VERSION_MAJOR}.dll"
        "${QT_LIBRARY_DIR}/QtXml${QT_VERSION_MAJOR}.dll"
        "${QT_LIBRARY_DIR}/QtTest${QT_VERSION_MAJOR}.dll"
        "${QT_LIBRARY_DIR}/QtWebKit${QT_VERSION_MAJOR}.dll"
        "${QT_LIBRARY_DIR}/QtGui${QT_VERSION_MAJOR}.dll"
        "${QT_LIBRARY_DIR}/QtNetwork${QT_VERSION_MAJOR}.dll"
        "${QT_LIBRARY_DIR}/Qt3Support${QT_VERSION_MAJOR}.dll"
        "${QT_LIBRARY_DIR}/QtSql${QT_VERSION_MAJOR}.dll"
        "${QT_LIBRARY_DIR}/QtSvg${QT_VERSION_MAJOR}.dll"
        DESTINATION ${CMAKE_INSTALL_PREFIX}
    )

ENDIF(UNIX AND NOT WIN32)


