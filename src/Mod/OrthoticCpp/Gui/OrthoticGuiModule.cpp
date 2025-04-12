#include "PreCompiled.h"

#include <Base/Console.h>
#include <Base/PyObjectBase.h>

namespace OrthoticCppGui {

PyObject* initModule()
{
    // initialize the Python interpreter
    PyObject* orthoticGuiModule = PyImport_AddModule("OrthoticCppGui");
    Base::Console().Log("Initializing OrthoticCppGui module...\n");

    // here you must register all your Python types
    Base::Console().Log("OrthoticCppGui module initialized\n");
    return orthoticGuiModule;
}

} // namespace OrthoticCppGui
