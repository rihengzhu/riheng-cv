from setuptools import setup,find_packages


__version__='0.0.1'

setup(
    name="xnn",
    version=__version__,
    packages=find_packages(),
    author="Ti",
    zip_safe=False,
    description="xnn qat package for tda",
    python_requires=">=3.6"
)