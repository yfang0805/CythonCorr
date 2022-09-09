from Cython.Build import cythonize
from distutils.core import setup, Extension
import numpy as np

ext_modules = Extension('utils',sources=["utils.pyx", "stats.cpp", "function1.cpp", "function2.cpp"],language='c++')
setup(
    ext_modules=cythonize(ext_modules,compiler_directives={'language_level': 3}),
    include_dirs=[np.get_include()]
)
