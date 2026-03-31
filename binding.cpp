#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <vector>
#include <cstdint>

// твоя функция
std::vector<uint8_t> img2eink();

namespace py = pybind11;

PYBIND11_MODULE(eink, m)
{
    m.doc() = "E-ink image converter";

    m.def("img2eink", &img2eink);
}