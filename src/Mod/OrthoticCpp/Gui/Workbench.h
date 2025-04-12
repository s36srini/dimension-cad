#ifndef ORTHOTIC_GUI_WORKBENCH_H
#define ORTHOTIC_GUI_WORKBENCH_H

#include <Gui/Workbench.h>

namespace OrthoticCppGui {

/**
 * @brief The Workbench class
 * This class implements a workbench for the Orthotic module.
 */
class OrthoticWorkbench : public Gui::Workbench
{
    TYPESYSTEM_HEADER();

public:
    OrthoticWorkbench();
    virtual ~OrthoticWorkbench();

    /** Initialization of the workbench. */
    virtual void setupContextMenu(const char* recipient, Gui::MenuItem*) const;
    virtual Gui::ToolBarItem* setupToolBars() const;
    virtual Gui::MenuItem* setupMenuBar() const;
};

} // namespace OrthoticCppGui

#endif // ORTHOTIC_GUI_WORKBENCH_H
