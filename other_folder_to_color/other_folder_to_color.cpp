//
//  main.cpp
//  byte_to_wav
//
//  Created by Zeno  Loesch on 15/11/22.
//

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
#include "../lodepng/lodepng.h"
int counter = 0;

int main(int argc, const char * argv[]) {

    unsigned char r, g, b;
    std::filesystem::path path {}; //input path
    
    for (auto const &dir_entry : std::filesystem::recursive_directory_iterator{path})
    {
        std::string path_string = dir_entry.path().string();
        std::ifstream in(path_string, std::ifstream::binary);
    
    uint32_t fsize = in.tellg();
    in.seekg(0, std::ios::end);
    fsize = (uint32_t)in.tellg() - fsize;
    in.seekg(0, std::ios::beg);
    char * rbuffer = new char  [262144];
    char * gbuffer = new char  [262144];
    char * bbuffer = new char  [262144];
    in.read(rbuffer, 262144);
    in.read(gbuffer, 262144);
    in.read(bbuffer, 262144);
    printf("file size: %u\n", fsize); // length of file
        
    counter += 1;
    const int width = 512;
    const int height = 512;
    std::vector<uint8_t> image;
    image.resize(width * height * 4);
          
    // Fill the image data
    for (int i = 0; i < height * width * 4; i += 4) {
            image[i + 0] = rbuffer[i / 4];
            image[i + 1] = gbuffer[i / 4];
            image[i + 2] = bbuffer[i / 4];
            image[i + 3] = 255;
          }
    in.close();
    free(rbuffer);
    free(gbuffer);
    free(bbuffer);
    // Encode and save the PNG file
    const std::string file_name = "path" + std::to_string(counter) + ".png";
    const auto error = lodepng::encode(file_name, image, width, height);
    if (error) {
        std::cerr << "Encoding error: " << lodepng_error_text(error) << std::endl;
        return 1;
        }
    }
    return 0;
}

