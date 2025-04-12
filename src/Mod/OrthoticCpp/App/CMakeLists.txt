include_directories(
    ${CMAKE_BINARY_DIR}
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_CURRENT_BINARY_DIR}
    ${Boost_INCLUDE_DIRS}
    ${OCC_INCLUDE_DIR}
    ${PYTHON_INCLUDE_DIRS}
    ${XercesC_INCLUDE_DIRS}
)

set(OrthoticCpp_LIBS
    FreeCADApp
    Part
)

set(OrthoticCpp_SRCS
    AppOrthotic.cpp
    OrthoticModule.cpp
    PreCompiled.cpp
    PreCompiled.h
)

add_library(OrthoticCpp SHARED ${OrthoticCpp_SRCS})
target_link_libraries(OrthoticCpp ${OrthoticCpp_LIBS})

fc_target_copy_resource(OrthoticCpp 
    ${CMAKE_SOURCE_DIR}/src/Mod/OrthoticCpp
    ${CMAKE_BINARY_DIR}/Mod/OrthoticCpp
    Init.py)

SET_BIN_DIR(OrthoticCpp OrthoticCpp /Mod/OrthoticCpp)
SET_PYTHON_PREFIX_SUFFIX(OrthoticCpp)

INSTALL(TARGETS OrthoticCpp DESTINATION ${CMAKE_INSTALL_LIBDIR})
