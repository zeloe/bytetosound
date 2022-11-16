//
//  save_image.h
//  byte_to_wav
//
//  Created by Zeno  Loesch on 15/11/22.
//
#include <fstream>
#include <string>
#include <cmath>
#include <cstdint>
#ifndef save_image_h
#define save_image_h


void save_image(const std::string name, char*  imgvals[][512], int size)
{
   using ::std::string;
   using ::std::ios;
   using ::std::ofstream;
   typedef unsigned char pixval_t;
   
   auto as_pgm = [](const string &name) -> string {
      if (! ((name.length() >= 4)
             && (name.substr(name.length() - 4, 4) == ".pgm")))
      {
         return name + ".pgm";
      } else {
         return name;
      }
   };

   ofstream out(as_pgm(name), ios::binary | ios::out | ios::trunc);

   out << "P5\n512 512\n255\n";
   for (int x = 0; x < size; ++x) {
      for (int y = 0; y < size; ++y) {
        char*  outpy = imgvals[x][y];
         out.write(outpy, 1);
      }
   }
    out.close();
    
}


#endif /* save_image_h */
