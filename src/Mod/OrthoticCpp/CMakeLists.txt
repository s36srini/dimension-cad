if(BUILD_GUI)
    add_subdirectory(App)
    add_subdirectory(Gui)
else(BUILD_GUI)
    add_subdirectory(App)
endif(BUILD_GUI)

INSTALL(
    FILES
        Init.py
        InitGui.py
    DESTINATION
        Mod/OrthoticCpp
)
