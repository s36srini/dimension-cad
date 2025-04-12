#include "PreCompiled.h"

#include "Workbench.h"
#include <Gui/MenuManager.h>
#include <Gui/ToolBarManager.h>

using namespace OrthoticCppGui;

TYPESYSTEM_SOURCE(OrthoticCppGui::OrthoticWorkbench, Gui::Workbench)

OrthoticWorkbench::OrthoticWorkbench()
{
}

OrthoticWorkbench::~OrthoticWorkbench()
{
}

void OrthoticWorkbench::setupContextMenu(const char* recipient, Gui::MenuItem* item) const
{
    Gui::Workbench::setupContextMenu(recipient, item);
    *item << "Orthotic Design";
}

Gui::ToolBarItem* OrthoticWorkbench::setupToolBars() const
{
    Gui::ToolBarItem* root = Gui::Workbench::setupToolBars();
    Gui::ToolBarItem* orthotic = new Gui::ToolBarItem(root);
    orthotic->setCommand("Orthotic Design");
    *orthotic << "OrthoticCpp_CreateRigidInsole";

    return root;
}

Gui::MenuItem* OrthoticWorkbench::setupMenuBar() const
{
    Gui::MenuItem* root = Gui::Workbench::setupMenuBar();
    Gui::MenuItem* orthotic = new Gui::MenuItem;
    root->insertItem(orthotic);
    orthotic->setCommand("Orthotic Design");
    *orthotic << "OrthoticCpp_CreateRigidInsole";

    return root;
}
