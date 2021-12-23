# -*- coding: utf-8 -*-
"""
generate and compile cython code
"""

from distutils.core import setup
from Cython.Build import cythonize
from distutils.extension import Extension
from Cython.Distutils import build_ext
import numpy
import os

cpp_part_path = "./CplusplusPart/src/"

sources_cpp = os.listdir(cpp_part_path)

sources = ["lib.pyx", ]

for file in sources_cpp:
    file_name, ext = os.path.splitext(file)
    if ext == ".cpp":
        sources.append(cpp_part_path + file)

ext_modules=[
    Extension("lib",
              sources = sources, # ["lib.pyx", "./CplusplusPart/src/x_inf_and_tau_functions.cpp"],
              language="c++", 
              libraries=["m"],
              extra_compile_args = ["-std=c++11", "-O3", "-ffast-math", "-march=native", "-fopenmp" ],
              extra_link_args=['-fopenmp'],
              include_dirs=[numpy.get_include(), "./CplusplusPart/src/", "./CplusplusPart/include/", ]
              ) 
]

setup( 
    name = "lib",
    cmdclass = {"build_ext": build_ext},
    ext_modules = ext_modules,
    include_dirs=[numpy.get_include()],

)



