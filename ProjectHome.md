PyQu is an extension module for Python 3 whose main goal is to provide a complete set of data types and functions for simulating quantum computation with a neat syntax.
PyQu is written in C and makes extensive use of libquantum-1.0.0 library by Björn Butscher and Hendrik Weimer. However, PyQu intends not to be just a wrapper of libquantum to Python, but rather a new high-level language (in Python style of course) for quantum programming.

## Important notes ##
  * PyQu is under developement and contains bugs (see list of known bugs below) and many features to be finished, use it under your responsability.
  * I'll be more than happy if you report any bug you may encounter at ericmarcosp@gmail.com. Any comments, suggestions, questions are welcome too.
  * If you are interested in participating developing PyQu don't hesitate to contact me!

## Installation ##
### Pre-requisites ###
  * Python 3.X with dev tools:
```
sudo apt-get install python3.2
sudo apt-get install python3.2-dev
```
  * libquantum 1.0.0 (which is included in this repo)
```
cd $libquantum_dir$
./configure
make
sudo make install
```
### Install pyqu ###
  * Let python find libquantum: add these lines to your .bashrc and source it
```
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib
export LD_LIBRARY_PATH
```
  * Install as a global module
```
cd $pyqu_dir$
sudo python3.2 setup.py install
```
  * Install in a virtualenv
```
mkdir myproject && cd myproject
virtualenv . -p /usr/bin/python3.2
source bin/activate
python $pyqu_dir$/setup.py install
```

## Quick start ##
  * Run Python interpreter: `$>python`
  * Import the pyqu module:
```
>>> from pyqu import *
```
  * Now let's create some quantum registers, which is the main object of the pyqu module:
```
>>> a = Qureg()
>>> b = Qureg(8)
>>> c = Qureg(8,63)
```
  * Now a is a single qubit in the state |0>, b is a quantum register of 8 qubits in the state |0>, and c is a quantum register of 8 qubits in the state |00111111>.<br />Note that a, b and c are completely independent, so changes in any register don't affect the others.
  * We can check the width (number of qubits), size (number of basis states with coefficients different from 0 <sup>1</sup>), the coefficients and the probabilities of the basis states:
```
>>> b.width()
8
>>> c.size()
1
>>> a.coef()
[(1+0j),0j]
>>> a.prob()
[1.0,0]
```
  * Next, we can create new registers from the ones we already have. Use  in order to "join" two registers (performing a Kronecker product). The single `*` returns the inner product of the two registers (they must have the same width):
```
>>> d = a**b
>>> d.width()
9
>>> a.width()
1
>>> b.width()
8
>>> b*c
0
```
  * Here we have created a register d which is the Kronecker product of a and b. It's important to note that these three registers are not independent now, they reference qubits of the same register (you can think of a and b being _subregisters_ of d). It's also possible to create subregisters with the [.md](.md) operator:
```
>>> e = d[2]
>>> f = d[1:6]
```

## Features ##

## Known Bugs ##

## Author ##