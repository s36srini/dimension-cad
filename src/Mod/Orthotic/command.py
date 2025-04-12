# In command.py
from Gui.RigidInsole import RigidInsole

class RigidInsoleCommand:
    def GetResources(self):
        return {'Pixmap': 'Mesh',
                'MenuText': 'Create Rigid Insole',
                'ToolTip': 'Creates a rigid insole from a foot mesh with 2mm offset depth'}

    def Activated(self):
        RigidInsole().Activated()

    def IsActive(self):
        return True  # or add your own logic to check if the command should be enabled