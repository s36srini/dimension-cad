
class OrthoticWorkbench (Workbench):

    MenuText = "Orthotic Workbench"
    ToolTip = "Orthotic stuff"
    Icon = None

    def Initialize(self):
        """This function is executed when the workbench is first activated.
        It is executed once in a FreeCAD session followed by the Activated function.
        """
        import command

        Gui.addCommand('CreateRigidInsole', command.RigidInsoleCommand())

        self.commandList = ['CreateRigidInsole']

        # creates a new toolbar with your commands
        self.appendToolbar("Orthotic Design", self.commandList)

        # creates a new menu
        self.appendMenu("Orthotic Design", self.commandList)

    def Activated(self):
        """This function is executed whenever the workbench is activated"""
        return

    def Deactivated(self):
        """This function is executed whenever the workbench is deactivated"""
        return

    def ContextMenu(self, recipient):
        """This function is executed whenever the user right-clicks on screen"""
        # "recipient" will be either "view" or "tree"
        self.appendContextMenu("Orthotic Design Menu", self.commandList) # add commands to the context menu

    def GetClassName(self): 
        # This function is mandatory if this is a full Python workbench
        # This is not a template, the returned string should be exactly "Gui::PythonWorkbench"
        return "Gui::PythonWorkbench"
       
Gui.addWorkbench(OrthoticWorkbench())