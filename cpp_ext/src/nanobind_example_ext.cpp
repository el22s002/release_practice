#include <iostream>
#include <nanobind/nanobind.h>
#include <opencv2/core.hpp>
#include <omp.h>

namespace nb = nanobind;

using namespace nb::literals;

void loop()
{
#pragma omp parallel for
    for (int i = 0; i<30; i++)
    {
        std::cout << "Loop: " << i << std::endl;
        if (i % 2 == 0)
        {
            for (int j = 0; j<10000; j++);
        }
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
