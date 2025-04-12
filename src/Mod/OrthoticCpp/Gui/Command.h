#ifndef ORTHOTIC_GUI_COMMAND_H
#define ORTHOTIC_GUI_COMMAND_H

#include <Gui/Command.h>

namespace OrthoticCppGui {

/**
 * @brief Create Rigid Insole command
 */
class CreateRigidInsoleCommand : public Gui::Command
{
public:
    CreateRigidInsoleCommand();
    virtual ~CreateRigidInsoleCommand();
    virtual const char* className() const { return "OrthoticCppGui::CreateRigidInsoleCommand"; }
    virtual void activated(int iMsg);
    virtual bool isActive(void);
};

} // namespace OrthoticCppGui

#endif // ORTHOTIC_GUI_COMMAND_H
