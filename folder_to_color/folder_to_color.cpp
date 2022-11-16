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

int counter = 0;

int main(int argc, const char * argv[]) {

    unsigned char r, g, b;
    const std::__fs::filesystem::path path {""}; //input path
    
    for (auto const &dir_entry : std::__fs::filesystem::recursive_directory_iterator{path})
    {
        std::string path_string = dir_entry.path();
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
        
    std::ofstream out("" + std::to_string(counter) + ".png" , std::ios::binary | std::ios::out); // write raw data
        counter += 1;
    out << "P6\n" << 512 << " " << 512 << "\n255\n";
    for (int i = 0; i < 262144; ++i) {
        r = static_cast<unsigned char>(rbuffer[i]);
        g = static_cast<unsigned char>(gbuffer[i]);
        b = static_cast<unsigned char>(bbuffer[i]);
                out << r << g << b;
    }
    
    out.close();
    in.close();
    free(rbuffer);
    free(gbuffer);
    free(bbuffer);
    }
    return 0;
}

