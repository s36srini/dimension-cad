include_directories(
    ${CMAKE_BINARY_DIR}
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_CURRENT_BINARY_DIR}
    ${Boost_INCLUDE_DIRS}
    ${COIN3D_INCLUDE_DIRS}
    ${ZLIB_INCLUDE_DIR}
    ${OCC_INCLUDE_DIR}
    ${PYTHON_INCLUDE_DIRS}
    ${XercesC_INCLUDE_DIRS}
    ${QT_INCLUDE_DIR}
)

set(OrthoticCppGui_LIBS
    OrthoticCpp
    FreeCADGui
    PartGui
)

qt_add_resources(OrthoticCppGui_QRC_SRCS Resources/OrthoticCpp.qrc)

set(OrthoticCppGui_UIC_SRCS
    ../Resources/ui/RigidInsole.ui
)

qt_wrap_ui(OrthoticCppGui_UIC_HDRS ${OrthoticCppGui_UIC_SRCS})

set(OrthoticCppGui_SRCS
    ${OrthoticCppGui_QRC_SRCS}
    ${OrthoticCppGui_UIC_HDRS}
    AppOrthoticGui.cpp
    Command.cpp
    Command.h
    RigidInsoleTaskPanel.cpp
    RigidInsoleTaskPanel.h
    OrthoticGuiModule.cpp
    PreCompiled.cpp
    PreCompiled.h
    Workbench.cpp
    Workbench.h
)

add_library(OrthoticCppGui SHARED ${OrthoticCppGui_SRCS})
target_link_libraries(OrthoticCppGui ${OrthoticCppGui_LIBS})

fc_target_copy_resource(OrthoticCppGui 
    ${CMAKE_SOURCE_DIR}/src/Mod/OrthoticCpp
    ${CMAKE_BINARY_DIR}/Mod/OrthoticCpp
    InitGui.py)

SET_BIN_DIR(OrthoticCppGui OrthoticCppGui /Mod/OrthoticCpp)
SET_PYTHON_PREFIX_SUFFIX(OrthoticCppGui)

INSTALL(TARGETS OrthoticCppGui DESTINATION ${CMAKE_INSTALL_LIBDIR})
