#include "PreCompiled.h"

#include <Base/Console.h>
#include <Base/Interpreter.h>
#include <Base/PyObjectBase.h>
#include <Gui/Application.h>
#include <Gui/BitmapFactory.h>
#include <Gui/WidgetFactory.h>
#include <Gui/Language/Translator.h>

#include "Workbench.h"
#include "Command.h"

// use a different name to CreateCommand()
void CreateOrthoticCommands(void);

namespace OrthoticCppGui {
extern PyObject* initModule();
}

/* Python entry */
PyMOD_INIT_FUNC(OrthoticCppGui)
{
    if (!Gui::Application::Instance) {
        PyErr_SetString(PyExc_ImportError, "Cannot load Gui module in console application.");
        PyMOD_Return(nullptr);
    }

    // load dependent modules
    try {
        Base::Interpreter().loadModule("OrthoticCpp");
    }
    catch(const Base::Exception& e) {
        PyErr_SetString(PyExc_ImportError, e.what());
        PyMOD_Return(nullptr);
    }

    PyObject* mod = OrthoticCppGui::initModule();
    Base::Console().Log("Loading OrthoticCppGui module... done\n");

    // instantiate the workbench
    (void)new OrthoticCppGui::OrthoticWorkbench();
    Gui::Application::Instance->addWorkbench(new OrthoticCppGui::OrthoticWorkbench());

    // register commands
    CreateOrthoticCommands();

    PyMOD_Return(mod);
}

void CreateOrthoticCommands(void)
{
    Gui::CommandManager &rcCmdMgr = Gui::Application::Instance->commandManager();
    rcCmdMgr.addCommand(new OrthoticCppGui::CreateRigidInsoleCommand());
}
