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

#ifndef IMAGEELEMENT_HPP
#define IMAGEELEMENT_HPP

#include <vector>
#include <string>

class ImageElement{
public:
    ImageElement(std::string path);
    ImageElement();
    ImageElement(const ImageElement &obj, std::string);
    ~ImageElement();
    std::string basename();
    std::string dirname();
    std::string name;
    std::string extension;
    std::string getFilePath();
    std::string evalAtFrame(int frame);
    std::vector<std::string> getPaths();
    bool operator== (ImageElement &other);
    static bool validateFile(std::string path);
    void merge(ImageElement &other);
    std::vector<int> getFrames();
    void setFrames(std::vector<int> frames);

private:
    std::string filePath;
    std::string buildName();
    std::string framePadding;
    std::string tokenizeName(std::string filename);
    void parseName(std::string filename);
    bool upToDate = true;
    std::vector<int> frames;
};

#endif //IMAGEELEMENT_HPP
