import sys
from pybind11 import get_cmake_dir
from pybind11.setup_helpers import  Pybind11Extension,build_ext
from setuptools import setup

__version__='0.0.1'
ext_modules=[
    Pybind11Extension("preprocess",
                      ["src/preprocess_pybind11.cpp","src/cvtformat.c"],
                      include_dirs=["inc"],
                      define_macros=[("VERSION_INFO",__version__)]),
]

setup(
    name="preprocess",
    version=__version__,
    description="image preprocess",
    author="riheng",
    ext_modules=ext_modules,
    cmdclass={"build_ext":build_ext},
    zip_false=False,
    python_requores=">=3.6"
)