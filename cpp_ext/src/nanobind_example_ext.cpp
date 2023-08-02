#include <iostream>
#include <nanobind/nanobind.h>
#include <opencv2/core.hpp>
#include <omp.h>

namespace nb = nanobind;

using namespace nb::literals;

void loop()
{
    for (int i = 0; i<30; i++)
    {
        std::cout << i << std::endl;
    }
}

NB_MODULE(nanobind_example_ext, m) {
    m.def("add", [](int a, int b) { return a + b; }, "a"_a, "b"_a);
    m.def("loop", &loop);
    m.def("print_vec", []() { 
         cv::Vec3f vec;
         std::cout << vec << std::endl;
    });
}
