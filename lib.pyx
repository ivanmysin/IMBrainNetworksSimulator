from libc.math cimport exp, cos
from libcpp.map cimport map
from libcpp.pair cimport pair
from libcpp.string cimport string
from libcpp.vector cimport vector
from libcpp cimport bool
from cython.operator cimport dereference, preincrement
import numpy as np
cimport numpy as np
from libcpp.queue cimport queue
from cython.parallel cimport parallel, prange
cimport cython

cdef extern from "./CplusplusPart/include/Compartment.h":
    cdef cppclass Compartment:
        Compartment() except +
        Compartment(vector [double], vector [BaseChannel *]) except +
        void integrate(double dt, double duration) except +
        void init_to_inf() except +

cdef extern from "./CplusplusPart/include/BaseChannel.h":
    cdef cppclass BaseChannel:
        BaseChannel() except +
        BaseChannel(double, double, bool, vector [double (*)(double)], vector [double (*)(double)], vector [double]) except +
        BaseChannel(double, double) except +


cdef extern from "./CplusplusPart/include/x_inf_and_tau_functions.h" namespace "fs_neuron":
    cdef double m_inf(double)
    cdef double m_tau(double)
    cdef double h_inf(double)
    cdef double h_tau(double)
    cdef double n_inf(double)
    cdef double n_tau(double)

cdef class PyCompartment:
    cdef Compartment *thisptr

    def __cinit__(self, main_params, channels_params):
        cdef vector[double] params
        for i in range(4):
            params.push_back(main_params[i])

        cdef vector [BaseChannel *] channels #  = new vector[BaseChannel *]()

        for key in channels_params:
            ch_vals = channels_params[key]
            gmax = ch_vals['gmax']
            Erev = ch_vals['Erev']
            is_Ca = False
            if 'is_Ca' in ch_vals.keys():
                is_Ca = ch_vals['is_Ca']

            #cdef vector[double] gates_degrees
#            for val in ch_vals['gates_degrees']:
#                gates_degrees.push_back(val)

            ch = new BaseChannel(gmax, Erev)
            channels.push_back(ch)

        self.thisptr = new Compartment(params, channels)

    def __dealloc__(self):
        del self.thisptr

    def integrate(self, dt, duration):
        self.thisptr.integrate(dt, duration)
