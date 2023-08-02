cmake_minimum_required(VERSION 3.12)

project(nanobind_example LANGUAGES CXX)

if (NOT SKBUILD)
  message(WARNING "\
  This CMake file is meant to be executed using 'scikit-build'. Running
  it directly will almost certainly not produce the desired result. If
  you are a user trying to install this package, please use the command
  below, which will install all necessary build dependencies, compile
  the package in an isolated environment, and then install it.
  =====================================================================
   $ pip install .
  =====================================================================
  If you are a software developer, and this is your own package, then
  it is usually much more efficient to install the build dependencies
  in your environment once and use the following command that avoids
  a costly creation of a new virtual environment at every compilation:
  =====================================================================
   $ pip install nanobind scikit-build-core[pyproject]
   $ pip install --no-build-isolation -ve .
  =====================================================================
  You may optionally add -Ceditable.rebuild=true to auto-rebuild when
  the package is imported. Otherwise, you need to re-run the above
  after editing C++ files.")
endif()

# Try to import all Python components potentially needed by nanobind
find_package(Python 3.8
  REQUIRED COMPONENTS Interpreter Development.Module
  OPTIONAL_COMPONENTS Development.SABIModule)

# Import nanobind through CMake's find_package mechanism
find_package(nanobind CONFIG REQUIRED)

# We are now ready to compile the actual extension module
nanobind_add_module(
  # Name of the extension
  nanobind_example_ext

  # Target the stable ABI for Python 3.12+, which reduces
  # the number of binary wheels that must be built. This
  # does nothing on older Python versions
  STABLE_ABI

  # Build libnanobind statically and merge it into the
  # extension (which itself remains a shared library)
  #
  # If your project builds multiple extensions, you can
  # replace this flag by NB_SHARED to conserve space by
  # reusing a shared libnanobind across libraries
  NB_STATIC

  # Source code goes here
  src/nanobind_example_ext.cpp
)

# Install directive for scikit-build-core
install(TARGETS nanobind_example_ext LIBRARY DESTINATION nanobind_example)

# OpenCV
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

# OpenMP
if(APPLE)
  # Find the library paths and include paths using brew command
  execute_process(
    COMMAND brew --prefix libomp
    OUTPUT_VARIABLE BREW_PREFIX
    OUTPUT_STRIP_TRAILING_WHITESPACE
  )

  # Append the appropriate paths to the library and include directories
  set(LIBOMP_LIB_DIR "${BREW_PREFIX}/lib")
  set(LIBOMP_INCLUDE_DIR "${BREW_PREFIX}/include")

  # Link the target to the library directories
  target_link_directories(nanobind_example_ext PRIVATE ${LIBOMP_LIB_DIR})
  
  # Add the include directories to your target
  target_include_directories(nanobind_example_ext PRIVATE ${LIBOMP_INCLUDE_DIR})

  set(OpenMP_CXX_FLAGS "-Xpreprocessor -fopenmp -lomp")

  # Add the flags to the target
  set_target_properties(nanobind_example_ext PROPERTIES
    COMPILE_FLAGS ${OpenMP_CXX_FLAGS}
    LINK_FLAGS ${OpenMP_CXX_FLAGS}
  )

  # Link the target to the OpenMP library
  target_link_libraries(nanobind_example_ext PRIVATE ${OpenMP_CXX_FLAGS})
else()
  find_package(OpenMP REQUIRED)
  target_link_libraries(nanobind_example_ext PRIVATE OpenMP::OpenMP_CXX)
endif()
