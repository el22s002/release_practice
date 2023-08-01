#include <iostream>
#include <nanobind/nanobind.h>
#include <opencv2/core.hpp>

namespace nb = nanobind;

using namespace nb::literals;

NB_MODULE(nanobind_example_ext, m) {
    m.def("add", [](int a, int b) { return a + b; }, "a"_a, "b"_a);
    m.def("print_vec", []() { 
        cv::Vec3f vec;
        std::cout << vec << std::endl;
    });
}
