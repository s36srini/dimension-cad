# FreeCAD init script for the OrthoticCpp module

# Import the standard library modules
import os

# Add the FreeCAD modules path to the Python path
FreeCADModulePath = os.path.dirname(os.path.realpath(__file__))
FreeCADPath = os.path.dirname(FreeCADModulePath)
FreeCADBasePath = os.path.dirname(FreeCADPath)
FreeCADRootPath = os.path.dirname(FreeCADBasePath)
FreeCADLibPath = os.path.join(FreeCADRootPath, "lib")

# Add the module to the path
if FreeCADLibPath not in os.sys.path:
    os.sys.path.append(FreeCADLibPath)

# Import the module
import OrthoticCpp
