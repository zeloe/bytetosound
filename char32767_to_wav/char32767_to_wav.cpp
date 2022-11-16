//
//  main.cpp
//  byte_to_wav
//
//  Created by Zeno  Loesch on 15/11/22.
//

#include <iostream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdint>
#include <vector>
#include "WaveFile.h"
// two channels = 2 * sampling rate = 1 second
int seconds = 44100 * 10;
int main(int argc, const char * argv[]) {

    // path to file to read
    
    std::string in_name = ""; // raw  data
    std::ifstream in(in_name, std::ifstream::binary);
    
    uint32_t fsize = in.tellg();
    in.seekg(0, std::ios::end);
    fsize = (uint32_t)in.tellg() - fsize;
    in.seekg(0, std::ios::beg);

    printf("file size: %u\n", fsize); // length of file
    wav_hdr wav;
    wav.ChunkSize = seconds + sizeof(wav_hdr) - 8;
    wav.Subchunk2Size = seconds + sizeof(wav_hdr) - 44;
    // temporary load data
    char * buffer = new char [seconds];
    int * intbuffer = new int [seconds];
    in.read(buffer, seconds);
    for(int i = 0;i < seconds; i++)
    {
        intbuffer[i] = buffer[i] * 32767;
    }
    // path to file output
    std::ofstream out("", std::ios::binary); // write raw data
    out.write(reinterpret_cast<const char *>(&wav), sizeof(wav));
    for (int i = 0; i < seconds; ++i) {
        char data = intbuffer[i];
        out.write(reinterpret_cast<char *>(&data), sizeof(int16_t));
      }
    out.close();
    in.close();
    return 0;
}

