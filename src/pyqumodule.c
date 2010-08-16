#include "pyqumodule.h"


static PyMethodDef PyquMethods[] = {
  {"H", pyqu_H, METH_VARARGS,
   "Applies hadamard operator"},
  {"Cnot", pyqu_Cnot, METH_VARARGS,
   "Applies Cnot operator"},
  {"QFT", pyqu_QFT, METH_VARARGS,
   "Applies QFT (Quantum Fourier Transform) operator"},
  {"UexpModN", pyqu_UexpModN, METH_VARARGS,
   "Applies the operator that computes f(x)=a^x mod N"},
  {"X", pyqu_X, METH_VARARGS,
   "Applies X Pauli operator (same as NOT)"},
  {"Y", pyqu_Y, METH_VARARGS,
   "Applies Y Pauli operator"},
  {"Z", pyqu_Z, METH_VARARGS,
   "Applies Z Pauli operator"},
  {"measure", pyqu_measure, METH_VARARGS,
   "Measures the whole register and collapses to outcome state"},
  {"shor", pyqu_shor, METH_VARARGS,
   "Measures the whole register and collapses to outcome state"},
  {NULL, NULL, 0, NULL}
};

static struct PyModuleDef pyqumodule = {
  PyModuleDef_HEAD_INIT,
  "pyqu",
  NULL,
  -1,
  PyquMethods
};

static PyMethodDef Qureg_methods[] = {
    {"__getitem__", (PyCFunction) QuregMap_Subscript, METH_O|METH_COEXIST,
     "Returns a 'subregister' of the actual register"
    },
    {"size", (PyCFunction)Qureg_size, METH_NOARGS,
     "Returns the number of non-zero vectors"
    },
    {"width", (PyCFunction)Qureg_width, METH_NOARGS,
     "Returns the number qubits"
    },
    {"coef", (PyCFunction)Qureg_coef, METH_NOARGS,
     "Returns the coeficients of the vectors of the computational basis"
    },
    {"prob", (PyCFunction)Qureg_prob, METH_NOARGS,
     "Returns the probabilities of the vectors of the computational basis"
    },
    {"reverse", (PyCFunction)Qureg_reverse, METH_NOARGS,
     "Reverses the weight of the bits of the register"
    },
    {NULL}  /* Sentinel */
};

static PyNumberMethods QuregNumber_methods = {
     (binaryfunc) 0,    // nb_add
     (binaryfunc) 0, // nb_subtract;
     (binaryfunc) 0, // nb_multiply;
     (binaryfunc) 0, // nb_remainder;
     (binaryfunc) 0, // nb_divmod;
     (ternaryfunc) QuregNumber_Power, // nb_power;
     (unaryfunc) 0, // nb_negative;
     (unaryfunc) 0, // nb_positive;
     (unaryfunc) 0, // nb_absolute;
     (inquiry) 0, // nb_bool;
     (unaryfunc) 0, // nb_invert;
     (binaryfunc) 0, // nb_lshift;
     (binaryfunc) 0, // nb_rshift;
     (binaryfunc) 0, // nb_and;
     (binaryfunc) 0, // nb_xor;
     (binaryfunc) 0, // nb_or;
     (unaryfunc) 0, // nb_int;
     0, //void *nb_reserved;
     (unaryfunc) 0, // nb_float;

     (binaryfunc) 0, // nb_inplace_add;
     (binaryfunc) 0, // nb_inplace_subtract;
     (binaryfunc) 0, // nb_inplace_multiply;
     (binaryfunc) 0, // nb_inplace_divide;
     (binaryfunc) 0, // nb_inplace_remainder;
     (ternaryfunc) 0, // nb_inplace_power;
     (binaryfunc) 0, // nb_inplace_lshift;
     (binaryfunc) 0, // nb_inplace_rshift;
     (binaryfunc) 0, // nb_inplace_and;
     (binaryfunc) 0, // nb_inplace_xor;
     (binaryfunc) 0, // nb_inplace_or;

     (binaryfunc) 0, // nb_floor_divide;
     (binaryfunc) 0, // nb_true_divide;
     (binaryfunc) 0, // nb_inplace_floor_divide;
     (binaryfunc) 0, // nb_inplace_true_divide;

     (unaryfunc)0 // nb_index;
};


static PyMappingMethods QuregMapping_methods = {
    (lenfunc) QuregMap_Length,
    (binaryfunc) QuregMap_Subscript,
    (objobjargproc) 0
};

static PyTypeObject QuregType = {
    PyObject_HEAD_INIT(NULL)
    "pyqu.Qureg",             /* tp_name */
    sizeof(Qureg),             /* tp_basicsize */
    0,                         /* tp_itemsize */
    (destructor)Qureg_dealloc, /* tp_dealloc */
    0,                         /* tp_print */
    0,                         /* tp_getattr */
    0,                         /* tp_setattr */
    0,                         /* tp_reserved */
    0,                         /* tp_repr */
    &QuregNumber_methods,      /* tp_as_number */
    0,                         /* tp_as_sequence */
    &QuregMapping_methods,     /* tp_as_mapping */
    0,                         /* tp_hash  */
    0,                         /* tp_call */
    0,                         /* tp_str */
    0,                         /* tp_getattro */
    0,                         /* tp_setattro */
    0,                         /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT |
        Py_TPFLAGS_BASETYPE,   /* tp_flags */
    "Quantum register",        /* tp_doc */
    0,                         /* tp_traverse */
    0,                         /* tp_clear */
    0,                         /* tp_richcompare */
    0,                         /* tp_weaklistoffset */
    0,                         /* tp_iter */
    0,                         /* tp_iternext */
    Qureg_methods,             /* tp_methods */
    0,                         /* tp_members */
    0,                         /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    (initproc)Qureg_init,      /* tp_init */
    0,                         /* tp_alloc */
    Qureg_new,                 /* tp_new */
};

static PyTypeObject PyQuantumRegType = {
    PyObject_HEAD_INIT(NULL)
    "pyqu.PyQuantumReg",       /* tp_name */
    sizeof(PyQuantumReg),      /* tp_basicsize */
    0,                         /* tp_itemsize */
    0,                         /* tp_dealloc */
    0,                         /* tp_print */
    0,                         /* tp_getattr */
    0,                         /* tp_setattr */
    0,                         /* tp_reserved */
    0,                         /* tp_repr */
    0,                         /* tp_as_number */
    0,                         /* tp_as_sequence */
    0,                         /* tp_as_mapping */
    0,                         /* tp_hash  */
    0,                         /* tp_call */
    0,                         /* tp_str */
    0,                         /* tp_getattro */
    0,                         /* tp_setattro */
    0,                         /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT,
};

static void
Qureg_dealloc(Qureg* self)
{
    if(self->pyqr->refcount <= 1)
    {
        quantum_delete_qureg(&self->pyqr->qr);
        PyObject_Del(self->pyqr);
    }
    Py_TYPE(self)->tp_free((PyObject*)self);
}

static PyObject *
Qureg_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    int width = 1;
    unsigned int initVal = 0;
    
    if(!PyArg_ParseTuple(args, "|iI", &width, &initVal))
        return NULL;
    
    Qureg *self;
    
    self = (Qureg *)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->pyqr = (PyQuantumReg*) _PyObject_New(&PyQuantumRegType);
        self->pyqr->qr = quantum_new_qureg(initVal, width);
        self->pyqr->refcount = 1;
        self->first = 0;
        self->last = width - 1;
        self->reverse = 0;
    }
    return (PyObject *)self;
}

static int
Qureg_init(Qureg *self, PyObject *args, PyObject *kwds)
{
    return 0;
}

static PyObject *
Qureg_size(Qureg* self)
{
    //TODO:I want this function to return the number of basis whose coefficient > 0
    unsigned long long size = 1 << (self->last - self->first + 1);
    PyObject *ret = Py_BuildValue("K", size);
    
    return ret;
}

static PyObject *
Qureg_width(Qureg* self)
{
    PyObject *ret = Py_BuildValue("i", self->last - self->first + 1);
    
    return ret;
}

static PyObject *
Qureg_coef(Qureg *self)
{
    //TODO:I'm returning the coefficients of the whole register,
    // I want to return just the coefficients of the basis of the subspace specified by qr[first,last] --> It makes no sense with entangled states!
    int i,j,b = 0;
    PyObject *a;
    unsigned long long int size =  1 << self->pyqr->qr.width;
    PyObject *coefList = PyList_New(size);
    
    for(i = 0; i < size; i++)
    {
        b = 0;
        for(j = 0; j < self->pyqr->qr.size && !b; j++)
        {
            if(self->pyqr->qr.node[j].state == i)
            {
                float *p = (float *) &self->pyqr->qr.node[j].amplitude;
                a = PyComplex_FromDoubles(p[0], p[1]);
                b = 1;
            }
        }
        if(!b)
            a = PyComplex_FromDoubles(.0, .0);
        
        PyList_SET_ITEM(coefList, i, a);
    }
    
    return coefList;
}

static PyObject *
Qureg_prob(Qureg *self)
{
    int i,j = 0;
    PyObject *a,*b;
    //int size =  1 << self->pyqr->qr.width;
    unsigned long long int size = 1 << (self->last - self->first + 1);
    PyObject *probList = PyList_New(size);
    
    for(i = 0; i < size; i++)
        PyList_SET_ITEM(probList, i, PyFloat_FromDouble(.0));

    for(j = 0; j < self->pyqr->qr.size; j++)
    {
        b = PyList_GET_ITEM(probList, (self->pyqr->qr.node[j].state >> self->first) & (size - 1));
        float *p = (float *) &self->pyqr->qr.node[j].amplitude;
        a = PyFloat_FromDouble(p[0]*p[0]+p[1]*p[1] + PyFloat_AS_DOUBLE(b));
        PyList_SET_ITEM(probList, (self->pyqr->qr.node[j].state >> self->first) & (size - 1), a);
    }
    
    return probList;
}

static PyObject *
Qureg_reverse(Qureg *self)
{
    self->reverse = !self->reverse;
    
    Py_RETURN_NONE;
}

static PyObject *QuregNumber_Power(PyObject *o1, PyObject *o2, PyObject *o3)
{
    //No es poden concatenar si son subregistres
    //int size = o1->
    printf("hola!");
    Py_RETURN_NONE;
}

static Py_ssize_t QuregMap_Length(Qureg *reg)
{
    return reg->last - reg->first + 1;
}

static PyObject *QuregMap_Subscript(Qureg* self, PyObject* item)
{
    if (PyIndex_Check(item))
    {
        Py_ssize_t i;
        i = PyNumber_AsSsize_t(item, PyExc_IndexError);
        if (i == -1 && PyErr_Occurred())
            return NULL;
        while (i < 0)
            i += QuregMap_Length(self);
            
        PyTypeObject *type = &QuregType;
        Qureg *subreg;
        subreg = (Qureg *)type->tp_alloc(type, 0);
        if (subreg != NULL)
        {
            subreg->pyqr = self->pyqr;
            subreg->first = i;
            subreg->last = i;
            self->pyqr->refcount++;
        }
        return (PyObject *)subreg;
    }
    else if (PySlice_Check(item)) 
    {
        Py_ssize_t start, stop, step, slicelength;

        if (PySlice_GetIndicesEx((PySliceObject*)item, self->last - self->first + 1,
                &start, &stop, &step, &slicelength) < 0)
            return NULL;
        
        if (slicelength <= 0)
        {
            Py_RETURN_NONE;
        }
        
        PyTypeObject *type = &QuregType;
        Qureg *subreg;
        subreg = (Qureg *)type->tp_alloc(type, 0);
        if (subreg != NULL)
        {
            subreg->pyqr = self->pyqr;
            subreg->first = start;
            subreg->last = stop - 1;
            self->pyqr->refcount++;
        }
        return (PyObject *)subreg;
    }
    else
    {
        PyErr_Format(PyExc_TypeError,
                    "list indices must be integers, not %.200s",
                    item->ob_type->tp_name);
        return NULL;
    }
}


static PyObject *pyqu_H(PyObject *self, PyObject *args)
{
    int i;
    Qureg *reg;
    
    if(!PyArg_ParseTuple(args, "O!", &QuregType, &reg))
        return NULL;
    
    for(i = reg->first; i <= reg->last; i++)
        quantum_hadamard(i, &reg->pyqr->qr);
    
    Py_RETURN_NONE;
}

static PyObject *pyqu_Cnot(PyObject *self, PyObject *args)
{
    Qureg *controlReg;
    Qureg *targetReg;
    
    if(!PyArg_ParseTuple(args, "O!O!", &QuregType, &controlReg, &QuregType, &targetReg))
        return NULL;
    
    if(controlReg->pyqr != targetReg->pyqr)
    {
        //error: The control and the target registers must belong to the same quantum system
        return NULL;
    }
    
    if((controlReg->first < targetReg->first && controlReg->last < targetReg->first)
        || (controlReg->first < targetReg->last && controlReg->last > targetReg->last))
    {
        //error: The control and the target registers can't overlap
        //TODO:in future versions I want to allow qr.last < qr.first for the same
        //register qr. This will change the condition of this 'if'
        return NULL;
    }
    
    //TODO: implement CNOT with multiple control qubits and multiple target qubits
    quantum_cnot(controlReg->first, targetReg->first, &targetReg->pyqr->qr);
    
    Py_RETURN_NONE;
}

static PyObject *pyqu_QFT(PyObject *self, PyObject *args)
{
    int i,j;
    Qureg *reg;
    
    if(!PyArg_ParseTuple(args, "O!", &QuregType, &reg))
        return NULL;
    
    int first = reg->first;
    int last = reg->last;
    for(i=first; i <= last; i++)
    {
        quantum_hadamard(i, &reg->pyqr->qr);
        for(j=i+1; j<=last; j++)
            quantum_cond_phase(j, i, &reg->pyqr->qr);

    }
    
    Py_RETURN_NONE;
}

static PyObject *pyqu_UexpModN(PyObject *self, PyObject *args)
{
    int N,x,i,inWidth,outWidth;
    Qureg *inputReg,*outputReg;
    
    if(!PyArg_ParseTuple(args, "O!O!ii", &QuregType, &inputReg, &QuregType, &outputReg, &x, &N))
        return NULL;
        
    if(inputReg->pyqr != outputReg->pyqr)
    {
        //error: The control and the target registers must belong to the same quantum system
        return NULL;
    }
    
   /* if((controlReg->first < targetReg->first && controlReg->last < targetReg->first)
        || (controlReg->first < targetReg->last && controlReg->last > targetReg->last))
    {
        //error: The control and the target registers can't overlap
        //TODO:in future versions I want to allow qr.last < qr.first for the same
        //register qr. This will change the condition of this 'if'
        return NULL;
    }*/
    inWidth = inputReg->last - inputReg->first + 1;
    outWidth = outputReg->last - outputReg->first + 1;
    
    quantum_addscratch(2*outWidth+2, &outputReg->pyqr->qr);
    quantum_exp_mod_n(N, x, inWidth, outWidth, &outputReg->pyqr->qr);
    for(i=0;i<2*outWidth+2;i++)
    {
      quantum_bmeasure(0, &outputReg->pyqr->qr);
    }
    
    Py_RETURN_NONE;
}

static PyObject *pyqu_X(PyObject *self, PyObject *args)
{
    int i;
    Qureg *reg;
    
    if(!PyArg_ParseTuple(args, "O!", &QuregType, &reg))
        return NULL;
    
    for(i = reg->first; i <= reg->last; i++)
        quantum_sigma_x(i, &reg->pyqr->qr);
    
    Py_RETURN_NONE;
}

static PyObject *pyqu_Y(PyObject *self, PyObject *args)
{
    int i;
    Qureg *reg;
    
    if(!PyArg_ParseTuple(args, "O!", &QuregType, &reg))
        return NULL;
    
    for(i = reg->first; i <= reg->last; i++)
        quantum_sigma_y(i, &reg->pyqr->qr);
    
    Py_RETURN_NONE;
}

static PyObject *pyqu_Z(PyObject *self, PyObject *args)
{
    int i;
    Qureg *reg;
    
    if(!PyArg_ParseTuple(args, "O!", &QuregType, &reg))
        return NULL;
    
    for(i = reg->first; i <= reg->last; i++)
        quantum_sigma_z(i, &reg->pyqr->qr);
    
    Py_RETURN_NONE;
}

static PyObject *pyqu_measure(PyObject *self, PyObject *args)
{
    int i,r;
    unsigned int m = 0;
    Qureg *reg;
    
    if(!PyArg_ParseTuple(args, "O!", &QuregType, &reg))
        return NULL;
    
    if(!reg->reverse)
    {
        for(i = reg->first; i <= reg->last; i++)
        {
            r = quantum_bmeasure_bitpreserve(i, &reg->pyqr->qr);
            m = m | (r << (i - reg->first));
        }
    } else {
        for(i = reg->first; i <= reg->last; i++)
        {
            r = quantum_bmeasure_bitpreserve(i, &reg->pyqr->qr);
            m = m | (r << (reg->last - i));
        }
    }
    
    return Py_BuildValue("I", m);
}

static PyObject * pyqu_shor(PyObject *self, PyObject *args)
{
  quantum_reg qr;
  int i;
  int width, swidth;
  int x = 0;
  int N;
  int c,q,a,b, factor;

  if(!PyArg_ParseTuple(args, "i", &N))
    return NULL;

  if(N<15)
    {
      //printf("Invalid number\n\n");
      return NULL;
    }

  width=quantum_getwidth(N*N);
  swidth=quantum_getwidth(N);

  printf("N = %i, %i qubits required, x=%i, y=%i\n", N, width+3*swidth+2, width, swidth);

  while((quantum_gcd(N, x) > 1) || (x < 2))
    {
      x = rand() % N;
    } 

  printf("Random seed: %i\n", x);

  qr=quantum_new_qureg(0, width);

  for(i=0;i<width;i++)
    quantum_hadamard(i, &qr);

  quantum_addscratch(3*swidth+2, &qr);

  quantum_exp_mod_n(N, x, width, swidth, &qr);

  for(i=0;i<3*swidth+2;i++)
    {
      quantum_bmeasure(0, &qr);
    }

  quantum_qft(width, &qr); 
  
  for(i=0; i<width/2; i++)
    {
      quantum_cnot(i, width-i-1, &qr);
      quantum_cnot(width-i-1, i, &qr);
      quantum_cnot(i, width-i-1, &qr);
    }
  
  c=quantum_measure(qr);

  if(c==-1)
    {
      //printf("Impossible Measurement!\n");
      return NULL;
    }

  if(c==0)
    {
      //printf("Measured zero, try again.\n");
      return NULL;
    }

  q = 1<<(width);

  printf("Measured %i (%f), ", c, (float)c/q);

  quantum_frac_approx(&c, &q, width);

  printf("fractional approximation is %i/%i.\n", c, q);

  if((q % 2 == 1) && (2*q<(1<<width)))
    {
      printf("Odd denominator, trying to expand by 2.\n");
      q *= 2;
    }
    
  if(q % 2 == 1)
    {
      printf("Odd period, try again.\n");
      return NULL;
    }

  printf("Possible period is %i.\n", q);
  
  a = quantum_ipow(x, q/2) + 1 % N;
  b = quantum_ipow(x, q/2) - 1 % N;
  
  a = quantum_gcd(N, a);
  b = quantum_gcd(N, b);
  
  if(a>b)
    factor=a;
  else
    factor=b;
  char result[50] = "Factors: ";
  if((factor < N) && (factor > 1))
    {
      sprintf(result + strlen(result), "%d, %d", factor, N/factor);
      //result = "Yes";
      
      //printf("%i = %i * %i\n", N, factor, N/factor);
    }
  else
    {
      //result = "No";
      //printf("Unable to determine factors, try again.\n");
      //return 2;
    }
    
  quantum_delete_qureg(&qr);

  //  printf("Memory leak: %i bytes\n", (int) quantum_memman(0));

  return Py_BuildValue("s", result);
}


PyMODINIT_FUNC PyInit_pyqu(void)
{
    PyObject* m;
    
    if (PyType_Ready(&QuregType) < 0)
        return NULL;

    m = PyModule_Create(&pyqumodule);
    if (m == NULL)
        return NULL;
        
    Py_INCREF(&QuregType);
    PyModule_AddObject(m, "Qureg", (PyObject *)&QuregType);
    srand(time(0));
    
    return m; 
}
