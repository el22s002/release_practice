#include <iostream>
#include <cstdlib>
#include <nanobind/nanobind.h>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <omp.h>

namespace nb = nanobind;

using namespace nb::literals;

void loop() {
    const int arraySize = 50000;
    int sum = 0;

    #pragma omp parallel for
    for (int i = 0; i < arraySize; ++i) {
        for (int j = 0; j < arraySize; ++j) {
            int rand_val = std::rand();
            if (rand_val % 2 == 0)
            {
                sum += 1;
            }
            else
            {
                sum -= 1;
            }
        }
    }

    std::cout << "The sum is: " << sum << std::endl;
}

NB_MODULE(nanobind_example_ext, m) {
    m.def("add", [](int a, int b) { return a + b; }, "a"_a, "b"_a);
    m.def("loop", &loop);
    m.def("print_vec", []() { 
         cv::Vec3f vec;
         std::cout << vec << std::endl;
    });
    // m.def("get_mat", [](int width, int height) {
    //     cv::Mat1f img(height, width);
    //     return img;
    // });
}
}
