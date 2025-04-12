# FreeCAD init GUI script for the OrthoticCpp module

# Import the module
import FreeCAD
import FreeCADGui

# Import the module
try:
    import OrthoticCppGui
except ImportError:
    # If the GUI module is not available, we're in console mode
    msg = "Error importing OrthoticCppGui"
    FreeCAD.Console.PrintError(msg)
