import Part
import Surface
import FreeCAD


class My_Command_Class():
    """My new command"""

    def GetResources(self):
        return {"Pixmap"  : "Geoassembly", # the name of a svg file available in the resources
                "Accel"   : "Shift+S", # a default shortcut (optional)
                "MenuText": "My New Command",
                "ToolTip" : "What my new command does"}

    def Activated(self):
        """Do something here"""
        box = Part.makeBox(10, 10, 10)
        Part.show(box)

        # Create a surface using the Surface workbench
        wire = Part.makePolygon([FreeCAD.Base.Vector(0, 0, 0), FreeCAD.Base.Vector(10, 0, 0), FreeCAD.Base.Vector(10, 10, 0)])
        surface = Surface.makeRuledSurface(wire, wire)
        Part.show(surface)

        return

    def IsActive(self):
        """Here you can define if the command must be active or not (greyed) if certain conditions
        are met or not. This function is optional."""
        return True