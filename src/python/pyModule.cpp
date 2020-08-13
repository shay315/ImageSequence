// Copyright (C) 2020  Max Wiklund
//
// Licensed under the Apache License, Version 2.0 (the “License”);
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an “AS IS” BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "libImageSequence/imageElement.hpp"
#include "libImageSequence/scanDir.hpp"

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

bool type_check(ImageElement &lhs, pybind11::object &rhs) {
    ImageElement other = pybind11::cast<ImageElement>(rhs);
    return lhs == other;
}


PYBIND11_MODULE(pyImageSequence, module) {
    // ImageElement class.
    pybind11::class_<ImageElement>(module, "ImageElement")
            .def_property("frames",
                pybind11::cpp_function(&ImageElement::getFrames, pybind11::return_value_policy::copy),
                pybind11::cpp_function(&ImageElement::setFrames)
                )
            .def(pybind11::init<const std::string &>(), pybind11::arg("path"))
            .def(pybind11::init<ImageElement const&, std::string>(), pybind11::return_value_policy::copy)
            .def("basename", &ImageElement::basename)
            .def("dirname", &ImageElement::dirname)
            .def_readwrite("name", &ImageElement::name)
            .def_readwrite("ext", &ImageElement::extension)
            .def("getFilePath", &ImageElement::getFilePath, "Return serialized file path.")
            .def("getPaths", &ImageElement::getPaths, "Get all sequence file paths for this object.")
            .def("evalAtFrame", &ImageElement::evalAtFrame, pybind11::arg("frame"))
            .def("__repr__", [](ImageElement &self){
                return "ImageElement(path=\"" + self.getFilePath() + "\")";
            })

            // This is a hacky way of solving it copy until I have had time to investigate a proper solution.
            .def("copy", [](ImageElement &self){
                ImageElement copy = self;
                return copy;
            })

            .def("__eq__", [](ImageElement &self, pybind11::object &other) {
               return type_check(self, other);
            });

    module.def("scandir", &scandir,  "Scan directory for images.", pybind11::arg("path"));

}
