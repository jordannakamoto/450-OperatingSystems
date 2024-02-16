#include <fstream>
#include <iostream>

class FileReader {
    public:
        FileReader() {};
        std::vector<std::string> fileItems = {};
    void readFile(const std::string& fileName) {
        std::ifstream file(fileName);
        if (!file.is_open()) {
            std::cout << "Error: could not open file '" << fileName << "'" << std::endl;
            return;
        }
        std::string line;
        while (std::getline(file, line)) {
            fileItems.push_back(line);
        }
        file.close();
    };
    void printFile(){
        for(auto item: fileItems){
            std::cout << item << std::endl;
        }
    }
    void clearItems(){
        fileItems.clear();
    }
};