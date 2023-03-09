import platform
import os
from pybind11.setup_helpers import  Pybind11Extension,build_ext
from setuptools import setup
from typing import NamedTuple


def check_env_flag(name: str, default: str = "") -> bool:
    return os.getenv(name, default).upper() in ["ON", "1", "YES", "TRUE", "Y"]
class Package(NamedTuple):
    package: str
    name: str
    url: str
    include_flag: str
    lib_flag: str
    syspath_var_name: str



# def get_llvm_package_info():
#     # download if nothing is installed
#     system = platform.system()
#     if system == "Darwin":
#         system_suffix = "apple-darwin"
#     elif system == "Linux":
#         vglibc = tuple(map(int, platform.libc_ver()[1].split('.')))
#         vglibc = vglibc[0] * 100 + vglibc[1]
#         linux_suffix = 'ubuntu-18.04' if vglibc > 217 else 'centos-7'
#         system_suffix = f"linux-gnu-{linux_suffix}"
#     else:
#         return Package("llvm", "LLVM-C.lib", "", "LLVM_INCLUDE_DIRS", "LLVM_LIBRARY_DIR", "LLVM_SYSPATH")
#     use_assert_enabled_llvm = check_env_flag("TRITON_USE_ASSERT_ENABLED_LLVM", "False")
#     release_suffix = "assert" if use_assert_enabled_llvm else "release"
#     name = f'llvm+mlir-17.0.0-x86_64-{system_suffix}-{release_suffix}'
#     version = "llvm-17.0.0-8e5a41e8271f"
#     url = f"https://github.com/ptillet/triton-llvm-releases/releases/download/{version}/{name}.tar.xz"
#     return Package("llvm", name, url, "LLVM_INCLUDE_DIRS", "LLVM_LIBRARY_DIR", "LLVM_SYSPATH")



__version__='0.0.1'
ext_modules=[
    Pybind11Extension("preprocess",
                      ["src/preprocess_pybind11.cpp","src/cvtformat.cpp"],
                      include_dirs=["inc"],
                      define_macros=[("VERSION_INFO",__version__)],
                      language='c++',
                      extra_compile_args=['-std=c++11']),
]

setup(
    name="preprocess",
    version=__version__,
    description="image preprocess",
    author="riheng",
    ext_modules=ext_modules,
    cmdclass={"build_ext":build_ext},
    zip_safe=False,
    python_requires=">=3.6"
)