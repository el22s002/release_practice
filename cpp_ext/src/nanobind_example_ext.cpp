#include <iostream>
#include <nanobind/nanobind.h>
// #include <opencv2/core.hpp>
#include <omp.h>

namespace nb = nanobind;

using namespace nb::literals;

void loop()
{
    long int sum = 0;
#pragma omp parallel for
    for (long int i = 0; i<123456789000; i++)
    {
        if (sum == i)
        {
            sum += 1;
        }
    }

    std::cout << sum << std::endl;
}

NB_MODULE(nanobind_example_ext, m) {
    m.def("add", [](int a, int b) { return a + b; }, "a"_a, "b"_a);
    m.def("loop", &loop);
    // m.def("print_vec", []() { 
    //      cv::Vec3f vec;
    //      std::cout << vec << std::endl;
    // });
}
