#include "PreCompiled.h"

#include <Base/Console.h>
#include <Base/PyObjectBase.h>

namespace OrthoticCpp {

PyObject* initModule()
{
    // initialize the Python interpreter
    PyObject* orthoticModule = PyImport_AddModule("OrthoticCpp");
    Base::Console().Log("Initializing OrthoticCpp module...\n");

    // here you must register all your Python types
    Base::Console().Log("OrthoticCpp module initialized\n");
    return orthoticModule;
}

} // namespace OrthoticCpp
