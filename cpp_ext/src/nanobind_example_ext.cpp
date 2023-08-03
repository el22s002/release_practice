#include <iostream>
#include <nanobind/nanobind.h>
// #include <opencv2/core.hpp>
#include <omp.h>

namespace nb = nanobind;

using namespace nb::literals;

void loop()
{
    int sum = 0;
    #pragma omp parallel for
    for (int i = 0; i<1234567890; i++)
    {
        sum += 1;
        if (i % 3 == 0)
        {
            for (int j = 0; j<100000; j++);
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
