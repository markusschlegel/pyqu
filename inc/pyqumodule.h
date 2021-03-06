#include <Python.h>
#include <quantum.h>
#include "structmember.h"
 
typedef struct {
    PyObject_HEAD
    quantum_reg qr;
    int refcount;
} PyQuantumReg;
 
typedef struct {
    PyObject_HEAD
    PyQuantumReg *pyqr;
    unsigned int first;
    unsigned int last;
    char reverse;  //Boolean
} Qureg;
 
static PyObject *pyqu_H(PyObject *self, PyObject *args);
static PyObject *pyqu_Cnot(PyObject *self, PyObject *args);
static PyObject *pyqu_X(PyObject *self, PyObject *args);
static PyObject *pyqu_Y(PyObject *self, PyObject *args);
static PyObject *pyqu_Z(PyObject *self, PyObject *args);
static PyObject *pyqu_QFT(PyObject *self, PyObject *args);
static PyObject *pyqu_QFTi(PyObject *self, PyObject *args);
static PyObject *pyqu_UexpModN(PyObject *self, PyObject *args);
static PyObject *pyqu_measure(PyObject *self, PyObject *args);
static PyObject *pyqu_shor(PyObject *self, PyObject *args);
 
static void Qureg_dealloc(Qureg* self);
static PyObject *Qureg_new(PyTypeObject *type, PyObject *args, PyObject *kwds);
static int Qureg_init(Qureg *self, PyObject *args, PyObject *kwds);
static PyObject *Qureg_size(Qureg* self);
static PyObject *Qureg_width(Qureg* self);
static PyObject *Qureg_coef(Qureg *self);
static PyObject *Qureg_prob(Qureg *self);
static PyObject *Qureg_reverse(Qureg *self);
static PyObject *QuregNumber_Power(PyObject *o1, PyObject *o2, PyObject *o3);
static Py_ssize_t QuregMap_Length(Qureg *reg);
static PyObject *QuregMap_Subscript(Qureg* self, PyObject* item);