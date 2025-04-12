#include "PreCompiled.h"

#include "Command.h"
#include "RigidInsoleTaskPanel.h"
#include <Base/Console.h>
#include <App/Document.h>
#include <Gui/Application.h>
#include <Gui/Selection.h>
#include <Gui/Control.h>
#include <Mod/Part/App/PartFeature.h>

using namespace OrthoticCppGui;

// Create rigid insole command
CreateRigidInsoleCommand::CreateRigidInsoleCommand()
  : Command("OrthoticCpp_CreateRigidInsole")
{
    sAppModule      = "OrthoticCpp";
    sGroup          = "Orthotic Design";
    sMenuText       = "Create Rigid Insole";
    sToolTipText    = "Create a rigid insole from a foot scan";
    sWhatsThis      = "OrthoticCpp_CreateRigidInsole";
    sStatusTip      = sToolTipText;
    sPixmap         = "OrthoticCpp_CreateRigidInsole";
}

CreateRigidInsoleCommand::~CreateRigidInsoleCommand()
{
}

void CreateRigidInsoleCommand::activated(int iMsg)
{
    // Get the active document
    App::Document* doc = App::GetApplication().getActiveDocument();
    if (!doc) {
        Base::Console().Warning("No active document available\n");
        return;
    }

    // Create and show the task panel
    Gui::TaskView::TaskDialog* dlg = new Gui::TaskView::TaskDialog();
    dlg->setButtonPosition(Gui::TaskView::TaskDialog::South);
    Gui::TaskView::TaskPanel* panel = new RigidInsoleTaskPanel();
    dlg->addTaskPanel(panel);
    Gui::Control().showDialog(dlg);
}

bool CreateRigidInsoleCommand::isActive(void)
{
    // Command is active if there is an active document and a selection
    return (App::GetApplication().getActiveDocument() && 
            !Gui::Selection().getSelection().empty());
}
