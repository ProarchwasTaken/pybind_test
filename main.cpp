#include <iostream>
#include <pybind11/pybind11.h>


void sayHello() {
  std::cout << "Hello World!\n"; 
}


PYBIND11_MODULE(test_module, m) {
  m.doc() = "This is momumental!";
  m.def("sayHello", &sayHello, "Function that prints Hello World");
}
