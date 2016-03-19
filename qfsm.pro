TEMPLATE = app
LANGUAGE = C++
VERSION = 0.51
CONFIG += qt debug
INCLUDEPATH += . \
    src
HEADERS += src/AppInfo.h \
    src/Const.h \
    src/Convert.h \
    src/DocStatus.h \
    src/Draw.h \
    src/DrawArea.h \
    src/DRect.h \
    src/Edit.h \
    src/Error.h \
    src/Export.h \
    src/ExportAHDL.h \
    src/ExportAHDLDlg.ui.h \
    src/ExportAHDLDlgImpl.h \
    src/ExportKISS.h \
    src/ExportRagel.h \
    src/ExportRagelDlgImpl.h \
    src/ExportStateTable.h \
    src/ExportStateTableDlg.ui.h \
    src/ExportStateTableDlgImpl.h \
    src/ExportVerilog.h \
    src/ExportVerilogDlg.ui.h \
    src/ExportVerilogDlgImpl.h \
    src/ExportVHDL.h \
    src/ExportIODescription.h \
    src/ExportVHDLDlg.ui.h \
    src/ExportVHDLDlgImpl.h \
    src/ExportEPS.h \
    src/ExportPNG.h \
    src/ExportSVG.h \
    src/ExportTestvectorASCII.h \
    src/ExportTestbenchVHDL.h \
    src/ExportTestbenchDlgImpl.h \
    src/ExportVVVV.h \
    src/ExportVVVVDlgImpl.h \
    src/ExportSCXML.h \
    src/TestvectorGenerator.h \
    src/FileIO.h \
    src/GITransition.h \
    src/GObject.h \
    src/Grid.h \
    src/GState.h \
    src/GTransition.h \
    src/ICheck.h \
    src/ICheckDlg.ui.h \
    src/ICheckDlgImpl.h \
    src/IOInfo.h \
    src/IOInfoASCII.h \
    src/IOInfoBin.h \
    src/IOInfoList.h \
    src/IOInfoText.h \
    src/IOViewDlgImpl.h \
    src/ListBoxItems.h \
    src/Machine.h \
    src/MachineManager.h \
    src/MachinePropertiesDlg.ui.h \
    src/MachinePropertiesDlgImpl.h \
    src/MainControl.h \
    src/MainWindow.h \
    src/MimeMachine.h \
    src/OptDisplayDlg.ui.h \
    src/OptDisplayDlgImpl.h \
    src/OptGeneral.h \
    src/OptGeneralDlg.ui.h \
    src/OptGeneralDlgImpl.h \
    src/Options.h \
    src/OptPrintingDlgImpl.h \
    src/PrintManager.h \
    src/Project.h \
    src/ScrollView.h \
    src/Selection.h \
    src/Simulator.h \
    src/SimulatorDlg.ui.h \
    src/SimulatorDlgImpl.h \
    src/State.h \
    src/StateManager.h \
    src/StatePropertiesDlg.ui.h \
    src/StatePropertiesDlgImpl.h \
    src/StatusBar.h \
    src/TableBuilder.h \
    src/TableBuilderASCII.h \
    src/TableBuilderHTML.h \
    src/TableBuilderLatex.h \
    src/ToolTipSV.h \
    src/Transition.h \
    src/TransitionInfo.h \
    src/TransitionInfoASCII.h \
    src/TransitionInfoBin.h \
    src/TransitionInfoText.h \
    src/TransitionManager.h \
    src/TransitionPropertiesDlg.ui.h \
    src/TransitionPropertiesDlgImpl.h \
    src/Undo.h \
    src/UndoBuffer.h \
    src/Utils.h \
    src/WSpinBox.h \
    src/XMLHandler.h \
    src/Zoom.h \
    src/TestvectorGenerator.h \
    src/ExportTestbenchVHDL.h \
    src/ExportTestvectorASCII.h \
    src/ImportGraphviz.h \
    src/Import.h
SOURCES += src/AppInfo.cpp \
    src/Convert.cpp \
    src/DocStatus.cpp \
    src/Draw.cpp \
    src/DrawArea.cpp \
    src/DRect.cpp \
    src/Edit.cpp \
    src/Error.cpp \
    src/Export.cpp \
    src/ExportAHDL.cpp \
    src/ExportAHDLDlgImpl.cpp \
    src/ExportKISS.cpp \
    src/ExportRagel.cpp \
    src/ExportRagelDlgImpl.cpp \
    src/ExportStateTable.cpp \
    src/ExportStateTableDlgImpl.cpp \
    src/ExportVerilog.cpp \
    src/ExportVerilogDlgImpl.cpp \
    src/ExportVHDL.cpp \
    src/ExportIODescription.cpp \
    src/ExportVHDLDlgImpl.cpp \
    src/FileIO.cpp \
    src/ExportEPS.cpp \
    src/ExportPNG.cpp \
    src/ExportSVG.cpp \
    src/ExportTestvectorASCII.cpp \
    src/ExportTestbenchVHDL.cpp \
    src/ExportTestbenchDlgImpl.cpp \
    src/ExportVVVV.cpp \
    src/ExportVVVVDlgImpl.cpp \
    src/ExportSCXML.cpp \
    src/TestvectorGenerator.cpp \
    src/GITransition.cpp \
    src/GObject.cpp \
    src/Grid.cpp \
    src/GState.cpp \
    src/GTransition.cpp \
    src/ICheck.cpp \
    src/ICheckDlgImpl.cpp \
    src/IOInfo.cpp \
    src/IOInfoASCII.cpp \
    src/IOInfoBin.cpp \
    src/IOInfoList.cpp \
    src/IOInfoText.cpp \
    src/IOViewDlgImpl.cpp \
    src/ListBoxItems.cpp \
    src/Machine.cpp \
    src/MachineManager.cpp \
    src/MachinePropertiesDlgImpl.cpp \
    src/main.cpp \
    src/MainControl.cpp \
    src/MainWindow.cpp \
    src/MimeMachine.cpp \
    src/OptDisplayDlgImpl.cpp \
    src/OptGeneral.cpp \
    src/OptGeneralDlgImpl.cpp \
    src/Options.cpp \
    src/OptPrintingDlgImpl.cpp \
    src/PrintManager.cpp \
    src/Project.cpp \
    src/ScrollView.cpp \
    src/Selection.cpp \
    src/Simulator.cpp \
    src/SimulatorDlgImpl.cpp \
    src/State.cpp \
    src/StateManager.cpp \
    src/StatePropertiesDlgImpl.cpp \
    src/StatusBar.cpp \
    src/TableBuilder.cpp \
    src/TableBuilderASCII.cpp \
    src/TableBuilderHTML.cpp \
    src/TableBuilderLatex.cpp \
    src/ToolTipSV.cpp \
    src/Transition.cpp \
    src/TransitionInfo.cpp \
    src/TransitionInfoASCII.cpp \
    src/TransitionInfoBin.cpp \
    src/TransitionInfoText.cpp \
    src/TransitionManager.cpp \
    src/TransitionPropertiesDlgImpl.cpp \
    src/Undo.cpp \
    src/UndoBuffer.cpp \
    src/Utils.cpp \
    src/WSpinBox.cpp \
    src/XMLHandler.cpp \
    src/Zoom.cpp \
    src/ImportGraphviz.cpp \
    src/Import.cpp

FORMS = src/ExportVHDLDlg.ui \
    src/ExportAHDLDlg.ui \
    src/ExportRagelDlg.ui \
    src/ExportStateTableDlg.ui \
    src/ExportTestbenchDlg.ui \
    src/ExportVerilogDlg.ui \
    src/ExportVVVVDlg.ui \
    src/ICheckDlg.ui \
    src/IOViewDlg.ui \
    src/MachinePropertiesDlg.ui \
    src/OptDisplayDlg.ui \
    src/OptGeneralDlg.ui \
    src/OptPrintingDlg.ui \
    src/SimulatorDlg.ui \
    src/StatePropertiesDlg.ui \
    src/TransitionPropertiesDlg.ui
win32 { 
    RC_FILE = desktop/qfsm.rc
    HEADERS += desktop/resource.h
}
win32 {
INSTDIR = "C:\Qfsm"
}
else {
INSTDIR = /usr
}
DEPENDPATH += po \
    src
TARGET = qfsm
OBJECTS_DIR = objs
MOC_DIR = mocs
win32 { 
    DEFINES += QFSM_LANGUAGE_DIR=\\\"po\\\"
    DEFINES += QFSM_HELP_DIR=\\\"doc\\user\\\"
}
else { 
    DEFINES += QFSM_LANGUAGE_DIR=\\\"$${INSTDIR}/share/qfsm\\\"
    DEFINES += QFSM_HELP_DIR=\\\"${INSTDIR}/share/doc/qfsm\\\"
}

# XPMS = $$system( find pics -type f -name "*.xpm" | grep -v CVS )
# QMS = $$system( find po -type f -name "*.[qt][ms]" | grep -v CVS )
# ICONS = $$system( find desktop -type f -name "*.png" | grep -v CVS )
# DOC = $$system( find doc/user -type f | grep -v CVS )
XPMS = pics/editcutoff.xpm \
    pics/panoff.xpm \
    pics/machinesimulate_old.xpm \
    pics/zoomoff.xpm \
    pics/greylight.xpm \
    pics/scissors.xpm \
    pics/fileprintoff.xpm \
    pics/greenlight.xpm \
    pics/machinesimoff.xpm \
    pics/editundo.xpm \
    pics/zoomout.xpm \
    pics/zoom.xpm \
    pics/editcut.xpm \
    pics/filenew.xpm \
    pics/c_mag.xpm \
    pics/statenew.xpm \
    pics/filesave.xpm \
    pics/select.xpm \
    pics/cross.xpm \
    pics/editundooff.xpm \
    pics/editcopy_old.xpm \
    pics/qfsm_64.xpm \
    pics/editcopyoff.xpm \
    pics/select_old.xpm \
    pics/filesaveoff.xpm \
    pics/editpasteoff.xpm \
    pics/magnifier.xpm \
    pics/arrow.xpm \
    pics/transnewoff.xpm \
    pics/zoominoff.xpm \
    pics/tick.xpm \
    pics/pan.xpm \
    pics/editcopy.xpm \
    pics/fileprint.xpm \
    pics/zoomoutoff.xpm \
    pics/machinesim.xpm \
    pics/editcut_old.xpm \
    pics/editpaste.xpm \
    pics/redlight.xpm \
    pics/machinesimulate.xpm \
    pics/fileopen.xpm \
    pics/zoomin.xpm \
    pics/transstraighten.xpm \
    pics/selectoff.xpm \
    pics/selectoff_old.xpm \
    pics/transnew.xpm \
    pics/statenewoff.xpm \
    pics/transstraightenoff.xpm
QMS = po/French.qm \
    po/German.qm \
    po/English.qm
TRANS = $$QMS \
    po/French.ts \
    po/German.ts \
    po/English.ts
ICONS = desktop/32x32/apps/qfsm.png \
    desktop/32x32/mimetypes/x-qfsm.png \
    desktop/48x48/apps/qfsm.png \
    desktop/48x48/mimetypes/x-qfsm.png \
    desktop/64x64/apps/qfsm.png \
    desktop/64x64/mimetypes/x-qfsm.png \
    desktop/qfsm.ico \
    desktop/x-qfsm.ico
DOC = doc/user/addtrans.png \
    doc/user/undo.png \
    doc/user/machine_properties.png \
    doc/user/.qfsm.docbook.swp \
    doc/user/toolbar.png \
    doc/user/cut.png \
    doc/user/LICENSE \
    doc/user/toolbar2.png \
    doc/user/toolbar3.png \
    doc/user/save.png \
    doc/user/paste.png \
    doc/user/zoomout.png \
    doc/user/zoom.png \
    doc/user/select.png \
    doc/user/simulate.png \
    doc/user/integrity_check.png \
    doc/user/new.png \
    doc/user/copy.png \
    doc/user/straighten.png \
    doc/user/working_area2.png \
    doc/user/qfsm.html \
    doc/user/simulation.png \
    doc/user/open.png \
    doc/user/doc_Makefile \
    doc/user/qfsm.pdf \
    doc/user/qfsm.rtf \
    doc/user/addstate.png \
    doc/user/state_properties.png \
    doc/user/pan.png \
    doc/user/zoomin.png \
    doc/user/qfsm.docbook \
    doc/user/working_area.png \
    doc/user/working_area.xcf \
    doc/user/transition_properties.png \
    doc/user/qfsm.fo \
    doc/user/print.png
TEST_MACHINES = examples/ascii_example3.fsm \
    examples/bin_example2.fsm \
    examples/text_example.fsm \
    examples/float.fsm \
    examples/integer.fsm \
    examples/datum.fsm
DISTFILES += $$XPMS \
    $$TRANS \
    $$TEST_MACHINES \
    $$ICONS \
    $$DOC \
    desktop/qfsm.desktop \
    desktop/x-qfsm.desktop
UI_HEADERS_DIR = src
UI_SOURCES_DIR = src
win32 { 
    target.path = $${INSTDIR}
    doc.path = $${INSTDIR}
    doc.files = $$DOC
    trans.path = $${INSTDIR}
    trans.files = $$QMS
    INSTALLS += target \
        doc \
        trans
}
else { 
    target.path = $${INSTDIR}/bin
    doc.path = $${INSTDIR}/share/doc/qfsm
    doc.files = $$DOC
    desktop.path = $${INSTDIR}/share/applications
    desktop.files = desktop/qfsm.desktop
    mime.path = $${INSTDIR}/share/mimelnk/application
    mime.files = desktop/x-qfsm.desktop
    icons.path = $${INSTDIR}/share/icons/hicolor
    icons.files = desktop/32x32 \
        desktop/48x48 \
        desktop/64x64
    trans.path = $${INSTDIR}/share/qfsm
    trans.files = $$QMS
    INSTALLS += target \
        doc \
        trans \
        desktop \
        mime \
        icons
}

# Input
TRANSLATIONS += po/English.ts \
    po/French.ts \
    po/German.ts
QT += xml \
    svg \
    qt3support
