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
#include "save_image.h"
#include "WaveFile.h"
// two channels = 2 * sampling rate = 1 second
int seconds = 44100 * 10;
int counter = 0;
int y = 0;
int count2 = 0;
int main(int argc, const char * argv[]) {

    // path to file to read
    std::filesystem::path path {""}; //input path
    
    for (auto const &dir_entry : std::filesystem::recursive_directory_iterator{path})
    {
        std::string path_string = dir_entry.path().string();
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
        char * buffer = new char [1024];
        char * buffer2 = new char [512];
        char * buffer3 = new char [512];
        char * buffer4 [512][512];
        in.read(buffer, 512);
        in.read(buffer2, 512);
        
        for(int i = 0; i < 512; i++)
        {
            buffer2[i] = buffer[i];
        }
        
        for(int i = 512; i < 1024; i++)
        {
            count2 += 1;
            buffer3[count2] = buffer[i];
        }
        
        for (int x = 0; x < 512; x++)
        {
            buffer4[x][y] = &buffer2[x];
            for ( y = 0; y < 512; y++)
            {
                buffer4[x][y] = &buffer3[y];
            }
        }
        // path to file output
        
     std::string outname =  "" + std::to_string(counter); //output path
        counter += 1;
        // write raw data
        save_image(outname,buffer4,512);
        free(buffer);
        free(buffer2);
        free(buffer3);
        in.close();
    }
    return 0;
}

