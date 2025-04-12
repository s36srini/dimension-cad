#include "PreCompiled.h"

#include <Base/Console.h>
#include <Base/Interpreter.h>
#include <Base/PyObjectBase.h>

#include <App/Application.h>

namespace OrthoticCpp {
extern PyObject* initModule();
}

/* Python entry */
PyMOD_INIT_FUNC(OrthoticCpp)
{
    // load dependent modules
    try {
        Base::Interpreter().loadModule("Part");
    }
    catch(const Base::Exception& e) {
        PyErr_SetString(PyExc_ImportError, e.what());
        PyMOD_Return(nullptr);
    }

    PyObject* mod = OrthoticCpp::initModule();
    Base::Console().Log("Loading OrthoticCpp module... done\n");
    PyMOD_Return(mod);
}
