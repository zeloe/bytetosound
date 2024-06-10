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
#include "WaveFile.h"
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
    for (auto const& dir_entry : std::filesystem::recursive_directory_iterator{ path })
    {
        std::string path_string = dir_entry.path().string();
        std::ifstream in(path_string, std::ifstream::binary);

        uint32_t fsize = in.tellg();
        in.seekg(0, std::ios::end);
        fsize = (uint32_t)in.tellg() - fsize;
        in.seekg(0, std::ios::beg);

        //printf("file size: %u\n", fsize); // length of file
        wav_hdr wav;
        wav.ChunkSize = fsize + sizeof(wav_hdr) - 8;
        wav.Subchunk2Size = fsize + sizeof(wav_hdr) - 44;
        // temporary load data
        char* buffer = new char[fsize];

        in.read(buffer, fsize);
        // path to file output
        std::ofstream out(outputDir + std::to_string(counter) + ".wav", std::ios::binary); //output path
        counter += 1;
        // write wav data
        out.write(reinterpret_cast<const char*>(&wav), sizeof(wav));
        for (int i = 0; i < fsize; ++i) {

            out.write(reinterpret_cast<char*>(&buffer[i]), sizeof(int16_t));
        }
        out.close();
        in.close();
        free(buffer);
    }
    return 0;
    }
}

