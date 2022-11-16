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
#include "WaveFile.h"
int seconds = 44100 * 10;
int counter = 0;
int main(int argc, const char * argv[]) {

    // path to file to read
    const std::__fs::filesystem::path path {"/Volumes/Backup/Glichart/colors"};  //path to image
    
    for (auto const &dir_entry : std::__fs::filesystem::recursive_directory_iterator{path})
    {
        std::string path_string = dir_entry.path();
        std::ifstream in(path_string, std::ifstream::binary);
    
        uint32_t fsize = in.tellg();
        in.seekg(0, std::ios::end);
        fsize = (uint32_t)in.tellg() - fsize;
        in.seekg(0, std::ios::beg);

        printf("file size: %u\n", fsize); // length of file
        wav_hdr wav;
        wav.ChunkSize = fsize + sizeof(wav_hdr) - 8;
        wav.Subchunk2Size = fsize + sizeof(wav_hdr) - 44;
        // temporary load data
        char * buffer = new char [fsize];
        
        in.read(buffer, fsize);
        // path to file output
        
        std::ofstream out("/Volumes/Backup/Glichart/waves_2/" + std::to_string(counter) + ".wav", std::ios::binary); //output path
        counter += 1;
        // write wav data
    out.write(reinterpret_cast<const char *>(&wav), sizeof(wav));
    for (int i = 0; i < fsize; ++i) {
        out.write(reinterpret_cast<char *>(& buffer[i]), sizeof(int16_t));
      }
        out.close();
        in.close();
    }
    return 0;
}

