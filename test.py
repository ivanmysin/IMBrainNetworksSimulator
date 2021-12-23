import numpy as np
import matplotlib.pyplot as plt
import lib

main_params = np.array([-65.0, 0.5, 0.01, 1.0])

channels = {
    "leak" : {
        'gmax' : 0.1,
        'Erev' : -65.0,
    },

    'na' : {
        'gmax' : 55.0,
        'Erev' : 50.0,
        'is_Ca_' :  False,
        'get_x_tau' : ['m_tau', 'h_tau'],
        'get_x_inf' : ['m_inf', 'h_inf'],
        'gates_degrees' : np.asarray([3, 1]),
    },

    'kdr': {
        'gmax': 8.0,
        'Erev': -90.0,
        'is_Ca_': False,
        'get_x_tau': ['n_tau', ],
        'get_x_inf': ['n_inf', ],
        'gates_degrees': np.asarray([4,]),
    },


}

compartment = lib.PyCompartment(main_params, channels)
compartment.integrate(0.1, 3000)

print("Hello")

