# CPP extension

![workflow status](https://github.com/el22s002/release_practice/actions/workflows/wheels.yml/badge.svg)

## Installation

### From wheel

You can install the prebuilt wheels with pip. Download the wheel (`.whl`) from `dist` folder for your platform and python version. For example, for python 3.11 on MacOS (Apple Silicon), you would download `*-cp311-cp311-macosx_11_0_arm64.whl`.

```bash
pip install <path-to-wheel>
```

### From source

You can also install from source.

```bash
git clone 
cd cpp_ext
pip install .
```

We use [nanobind]() to implement the C++ extension. You should read nanobind documentation for more details about a build system.
