/*
 * This file is part of RFM69LIB by Bits Working
 *
 * Copyright
 *
 *     Copyright (C) 2013 Bits Working <chris.hager@bitsworking.com>
 *
 */
#include "Python.h"
#include "rfm69.h"

// All these will get exposed via the Python module
static PyObject *WrongDirectionException;
static PyObject *version;

// bcm_to_board() returns the pin for the supplied bcm_gpio_id or -1
// if not a valid gpio-id. P5 pins are returned with | HEADER_P5, so
// you can know the header with (retval >> 8) (either 0 or 5) and the
// exact pin number with (retval & 255).
static int
test()
{
    return 1;
}

// module_setup is run on import of the GPIO module and calls the setup() method in c_gpio.c
static int
module_setup(void)
{
    // int result;
    // // printf("Setup module (mmap)\n");

    // // Set all gpios to input in internal direction (not the system)
    // int i=0;
    // for (i=0; i<54; i++)
    //     gpio_direction[i] = -1;

    // result = setup();
    // if (result == SETUP_DEVMEM_FAIL) {
    //     PyErr_SetString(PyExc_RuntimeError, "No access to /dev/mem. Try running as root!");
    //     return SETUP_DEVMEM_FAIL;
    // } else if (result == SETUP_MALLOC_FAIL) {
    //     PyErr_NoMemory();
    //     return SETUP_MALLOC_FAIL;
    // } else if (result == SETUP_MMAP_FAIL) {
    //     PyErr_SetString(PyExc_RuntimeError, "Mmap failed on module import");
    //     return SETUP_MALLOC_FAIL;
    // } else {
    //     // result == SETUP_OK
    //     return SETUP_OK;
    // }
    return 1;
}

// python function output(channel, value)
static PyObject*
py_test(PyObject *self, PyObject *args)
{
    // if (!PyArg_ParseTuple(args, "ii", &channel, &value))
    //     return NULL;

    Py_INCREF(Py_None);
    return Py_None;
}



PyMethodDef rpi_gpio_methods[] = {
    {"test", py_test, METH_VARARGS, "Test shit"},
    {NULL, NULL, 0, NULL}
};

PyMODINIT_FUNC initRFM69(void)
{
    PyObject *module = NULL;

    if ((module = Py_InitModule("RFM69", rpi_gpio_methods)) == NULL)
        goto exit;

    WrongDirectionException = PyErr_NewException("RPIO.Exceptions.WrongDirectionException", NULL, NULL);
    PyModule_AddObject(module, "WrongDirectionException", WrongDirectionException);

    version = Py_BuildValue("s", "0.10.1/0.4.2a");
    PyModule_AddObject(module, "VERSION_GPIO", version);

exit:
    return;
}
