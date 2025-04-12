
import FreeCAD
import Mesh
import MeshPart
import Part
import FreeCADGui as Gui
from FreeCAD import Base

from PySide import QtGui

def snake_to_camel(snake_str):
    components = snake_str.split('_')  # Split the string at underscores
    # Capitalize the first letter of each component except the first one
    return components[0] + ''.join(x.title() for x in components[1:])

class RigidInsole:
    def __init__(self):
        self.foot_mesh = None
        self.selected_points = {
            "heel": None,
            "first_metatarsal": None,
            "fifth_metatarsal": None
        }
        self.offset_depth = 2.0  # 2mm offset depth

    def Activated(self):
        # Get the selected mesh
        sel = Gui.Selection.getSelection()
        if not sel:
            FreeCAD.Console.PrintError("Please select a mesh object first\n")
            return
            
        obj = sel[0]
        if not hasattr(obj, "Mesh"):
            FreeCAD.Console.PrintError("Selected object is not a mesh\n")
            return
            
        self.foot_mesh = obj.Mesh
        self.create_boundary_selection_task()

    def create_boundary_selection_task(self):
        # Create a task panel for selecting boundary points
        task = RigidInsoleTaskPanel(self)
        Gui.Control.showDialog(task)

    def create_insole(self):
        if not all(self.selected_points.values()):
            FreeCAD.Console.PrintError("Please select all boundary points first\n")
            return

        # Create a new document object for the insole
        doc = FreeCAD.ActiveDocument
        insole = doc.addObject("Mesh::Feature", "RigidInsole")
        
        # Create boundary loop using selected points
        boundary = self.create_boundary_loop()
        
        FreeCAD.Console.PrintError("Boundary: ", boundary)
        #insole.Mesh = boundary

        # # Create surface from boundary
        # surface = self.create_surface_from_boundary(boundary)

        # FreeCAD.Console.PrintError("Surface: ", surface)
        
        # # Apply offset to create the insole
        # self.apply_offset(surface, insole)
        
        doc.recompute()

    def create_boundary_loop(self):
        """Create a boundary loop that follows the foot mesh contour"""
        if not all(self.selected_points.values()):
            FreeCAD.Console.PrintError("Please select all boundary points first\n")
            return None

        # Get the selected points
        heel = self.selected_points["heel"]
        first_met = self.selected_points["first_metatarsal"]
        fifth_met = self.selected_points["fifth_metatarsal"]

        # Create a wire that follows the mesh surface
        edges = []
        
        # Create edge between first metatarsal and fifth metatarsal
        edge1 = self.create_mesh_edge(first_met, fifth_met)
        if edge1:
            edges.append(edge1)
        
        # Create edge between fifth metatarsal and heel
        edge2 = self.create_mesh_edge(fifth_met, heel)
        if edge2:
            edges.append(edge2)
        
        # Create edge between heel and first metatarsal
        edge3 = self.create_mesh_edge(heel, first_met)
        if edge3:
            edges.append(edge3)

        edges.append(edge1)

        if not edges:
            FreeCAD.Console.PrintError("Failed to create any edges\n")
            return None

        FreeCAD.Console.PrintError("Edges: ")

        # Create wire from edges
        wire = Part.Wire(edges)
    
        doc = FreeCAD.ActiveDocument
        wire_feature = doc.addObject("Part::Feature", "BoundaryWire")
        wire_feature.Shape = wire
        doc.recompute()
        
        return wire

    def create_mesh_edge(self, start_point, end_point):
        """Create an edge that follows the mesh surface between two points"""
        try:
            # Get the mesh object and its kernel
            mesh_obj = self.foot_mesh

            import pdb; pdb.set_trace()
            mesh_kernel = mesh_obj.Mesh.getKernel()
            
            # Create a mesh projection
            mesh_projection = Mesh.MeshProjection()
            
            # Convert points to Vector3f
            start_vec = Base.Vector3f(start_point[0], start_point[1], start_point[2])
            end_vec = Base.Vector3f(end_point[0], end_point[1], end_point[2])
            
            # Create a list to store the projected points
            polyline = []
            
            # Project the line on mesh
            if mesh_projection.projectLineOnMesh(mesh_kernel, start_vec, end_vec, polyline):
                if len(polyline) > 1:
                    # Create a spline through the projected points
                    points = [Base.Vector(p.x, p.y, p.z) for p in polyline]
                    spline = Part.BSplineCurve()
                    spline.interpolate(points)
                    
                    # Create an edge from the spline
                    edge = Part.Edge(spline.toShape())
                    return edge
                    
            FreeCAD.Console.PrintError("Failed to project line on mesh\n")
            return None
        except Exception as e:
            FreeCAD.Console.PrintError(f"Failed to create edge: {str(e)}\n")
            return None

    def create_surface_from_boundary(self, boundary):
        """Create a curved surface that follows the foot mesh"""
        if not boundary:
            return None

        # Get the points from the boundary
        points = []
        for vertex in boundary.Vertexes:
            points.append(vertex.Point)

        # Create a surface that follows the foot mesh
        # We'll use a ruled surface between the boundary and a slightly offset version
        offset_points = []
        for point in points:
            # Find the normal at this point on the mesh
            # normal = self.foot_mesh.getNormalAtPoint(point)
            # Offset slightly in the normal direction
            # offset_point = point + normal * 2.0  # 2mm offset
            offset_points.append(points)

        # Create splines for both curves
        curve1 = Part.BSplineCurve()
        curve1.interpolate(points)
        
        curve2 = Part.BSplineCurve()
        curve2.interpolate(offset_points)

        # Create a ruled surface between the two curves
        surface = Part.makeRuledSurface(curve1.toShape(), curve2.toShape())
        return surface

    def apply_offset(self, surface, insole):
        # Apply the 2mm offset to create the insole
        MeshPart.offset(surface, self.offset_depth)
        insole.Mesh = surface

    def GetResources(self):
        return {'Pixmap': 'Mesh',
                'MenuText': 'Create Rigid Insole',
                'ToolTip': 'Creates a rigid insole from a foot mesh with 2mm offset depth'}

class RigidInsoleTaskPanel:
    def __init__(self, insole_creator):
        ui = FreeCAD.getHomePath() + "src/Mod/Orthotic/Resources/ui/RigidInsole.ui"
        self.form = Gui.PySideUic.loadUi(ui)
        self.insole_creator = insole_creator
        self.setup_ui()
        
        # Track point selections
        self.selected_points = {
            "heel": None,
            "first_metatarsal": None,
            "fifth_metatarsal": None
        }

        # Initialize current selection
        self.current_selection = None
        self.view3d = Gui.ActiveDocument.ActiveView
        
        # Add observer at initialization
        Gui.Selection.addObserver(self)
    
    def setup_ui(self):
        self.form.selectHeel.clicked.connect(lambda: self.set_selection_mode("heel"))
        self.form.selectFirstMetatarsal.clicked.connect(lambda: self.set_selection_mode("first_metatarsal"))
        self.form.selectFifthMetatarsal.clicked.connect(lambda: self.set_selection_mode("fifth_metatarsal"))
        
        # Connect button box
        self.form.buttonBox.accepted.connect(self.on_ok_clicked)
        self.form.buttonBox.rejected.connect(self.on_cancel_clicked)


    def set_selection_mode(self, point_type):
        """Set the current selection mode"""
        self.current_selection = point_type

    def addSelection(self, doc, obj, sub, pnt):
        """Handle selection when user clicks on the screen"""
        # Get the view that was clicked
        view = Gui.ActiveDocument.ActiveView
        
        # Only process if we clicked in the 3D view and not the task panel
        if view != self.view3d:
            return
            

        if not self.current_selection:
            # Reset selection mode
            self.set_selection_mode(None)
            return

        # Try to get the actual object from the document
        if isinstance(obj, str):
            try:
                obj = FreeCAD.ActiveDocument.getObject(obj)
            except:
                FreeCAD.Console.PrintError("Could not get object from document\n")
                return

        # Get the actual mesh object
        mesh_obj = None
        if hasattr(obj, "Mesh"):
            mesh_obj = obj
        # elif hasattr(obj, "Parent"):
        #     parent = obj.Parent
        #     if hasattr(parent, "Mesh"):
        #         mesh_obj = parent

        if not mesh_obj:
            FreeCAD.Console.PrintError("No mesh object found\n")
            return
            
        # Get the first subobject (vertex) from the selection
        point = pnt
        
        # Store the point
        self.selected_points[self.current_selection] = point
        
        # Update the status label
        status_label = getattr(self.form, snake_to_camel(f"status_{self.current_selection}"))
        status_label.setText(f"{self.current_selection.replace('_', ' ').title()}: Selected")
        
        # If all points are selected, enable the OK button
        if all(self.selected_points.values()):
            self.form.buttonBox.button(QtGui.QDialogButtonBox.Ok).setEnabled(True)
        else:
            self.form.buttonBox.button(QtGui.QDialogButtonBox.Ok).setEnabled(False)
            
        # Reset selection mode
        self.set_selection_mode(None)

    def on_ok_clicked(self):
        # Only create insole if all points are selected
        if all(self.selected_points.values()):
            self.insole_creator.selected_points = self.selected_points
            self.insole_creator.create_insole()
        
        Gui.Selection.removeObserver(self)
        Gui.Control.closeDialog()

    def on_cancel_clicked(self):
        self.selected_points = {
            "heel": None,
            "first_metatarsal": None,
            "fifth_metatarsal": None
        }
        self.current_selection = None
        Gui.Selection.removeObserver(self)
        Gui.Control.closeDialog()
