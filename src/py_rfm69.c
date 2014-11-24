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

// python function output(channel, value)
static PyObject*
py_test(PyObject *self, PyObject *args)
{
    // if (!PyArg_ParseTuple(args, "ii", &channel, &value))
    //     return NULL;

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject*
py_initialize(PyObject *self, PyObject *args)
{
    int frequency, nodeid, networkid;

    if (!PyArg_ParseTuple(args, "iii", &frequency, &nodeid, &networkid))
        return NULL;

    rfm69_initialize(frequency, nodeid, networkid);

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject*
py_encrypt(PyObject *self, PyObject *args)
{
    char *s;

    if (!PyArg_ParseTuple(args, "s", &s))
        return NULL;

    rfm69_encrypt(s);

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject*
py_setPowerLevel(PyObject *self, PyObject *args)
{
    int level;

    if (!PyArg_ParseTuple(args, "i", &level))
        return NULL;

    rfm69_setPowerLevel(level);

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject*
py_receive(PyObject *self, PyObject *args)
{
    rfm69_receive();

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject*
py_getDataLen(PyObject *self, PyObject *args)
{
    PyObject *func;
    func = Py_BuildValue("i", rfm69_getDataLen());
    return func;
}

static PyObject*
py_getRssi(PyObject *self, PyObject *args)
{
    PyObject *func;
    func = Py_BuildValue("i", rfm69_getRssi());
    return func;
}

static PyObject*
py_getSenderId(PyObject *self, PyObject *args)
{
    PyObject *func;
    func = Py_BuildValue("i", rfm69_getSenderId());
    return func;
}

static PyObject*
py_getData(PyObject *self, PyObject *args)
{
    PyObject *func;
    char received[63];
    rfm69_getData(received);

    func = Py_BuildValue("s", received);
    return func;
}

static PyObject*
py_send(PyObject *self, PyObject *args)
{
    int senderId;
    char *s;
    int len;

    if (!PyArg_ParseTuple(args, "isi", &senderId, &s, &len))
        return NULL;

    rfm69_send(senderId, (const void*) s, len, 0);
}

PyMethodDef rpi_gpio_methods[] = {
    {"test", py_test, METH_VARARGS, "Test shit n stuff"},
    {"initialize", py_initialize, METH_VARARGS, "Initialize RFM module with Frequency, NodeID and NetworkID"},
    {"encrypt", py_encrypt, METH_VARARGS, "Set encryption key"},
    {"setPowerLevel", py_setPowerLevel, METH_VARARGS, "Set power level (0..31)"},

    {"receive", py_receive, METH_VARARGS, "Receive Data until timeout or valid data"},
    {"getDataLen", py_getDataLen, METH_VARARGS, "Returns number of bytes ready to be read"},
    {"getRssi", py_getRssi, METH_VARARGS, "Returns RSSI"},
    {"getSenderId", py_getSenderId, METH_VARARGS, "Returns Sender ID"},

    {"getData", py_getData, METH_VARARGS, "Get data"},

    {"send", py_send, METH_VARARGS, "Send data"},

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
