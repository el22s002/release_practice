#include <iostream>
#include <nanobind/nanobind.h>
// #include <opencv2/core.hpp>
#include <omp.h>

namespace nb = nanobind;

using namespace nb::literals;

void loop() {
    const int arraySize = 30000;
    std::vector<int> data(arraySize);
    int sum = 0;

    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < arraySize; ++i) {
        for (int j = 0; j < arraySize; j++)
        {
            for (int k = 0; k < arraySize; k++)
            {
                data[i] = k + 1;
            }
        }
        sum += data[i];
    }

    std::cout << "The sum is: " << sum << std::endl;
}

NB_MODULE(nanobind_example_ext, m) {
    m.def("add", [](int a, int b) { return a + b; }, "a"_a, "b"_a);
    m.def("loop", &loop);
    // m.def("print_vec", []() { 
    //      cv::Vec3f vec;
    //      std::cout << vec << std::endl;
    // });
}
