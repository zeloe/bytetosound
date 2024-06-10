#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <filesystem>
#include <algorithm>
#include <fstream>
#include <string>
#include <cmath>
#include <cstdint>
#include "lodepng.h"
int counter = 0;

int main(int argc, const char * argv[]) {

    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <input_directory> <output_directory>" << std::endl;
        return 1;
    }

    std::string inputDir = argv[1];
    std::string outputDir = argv[2];
    outputDir += "/";
    unsigned char r, g, b;
    std::filesystem::path path { inputDir }; //input path
    
    for (auto const &dir_entry : std::filesystem::recursive_directory_iterator{path})
    {
        std::string path_string = dir_entry.path().string();
        std::ifstream in(path_string, std::ifstream::binary);
        std::cout << path_string << std::endl;
    uint32_t fsize = in.tellg();
    in.seekg(0, std::ios::end);
    fsize = (uint32_t)in.tellg() - fsize;
    in.seekg(0, std::ios::beg);
    uint32_t fsize_3 = fsize / 3;
    char * rbuffer = new char  [fsize_3];
    char * gbuffer = new char  [fsize_3];
    char * bbuffer = new char  [fsize_3];
    in.read(rbuffer, fsize_3);
    in.read(gbuffer, fsize_3);
    in.read(bbuffer, fsize_3);
    printf("file size: %u\n", fsize); // length of file
        
    counter += 1;
    const int width = 512;
    const int height = 512;
    std::vector<uint8_t> image;
    image.resize(width * height * 4);
          
    // Fill the image data
    for (int i = 0; i < height * width * 4; i += 4) {
            
        if (i > fsize) break;
        image[i + 0] = static_cast<uint8_t>(rbuffer[i / 4]);
        image[i + 1] = static_cast<uint8_t>(gbuffer[i / 4]);
        image[i + 2] = static_cast<uint8_t>(bbuffer[i / 4]);
        image[i + 3] = 255;

    }
    in.close();
    free(rbuffer);
    free(gbuffer);
    free(bbuffer);
    // Encode and save the PNG file
    const std::string file_name = outputDir + std::to_string(counter) + ".png";
    std::cout << file_name;
    const auto error = lodepng::encode(file_name, image, width, height);
    if (error) {
        std::cerr << "Encoding error: " << lodepng_error_text(error) << std::endl;
        return 1;
        }
    }
    return 0;
}

