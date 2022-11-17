# bytetosound
 Reads raw data and outputs it as a wave file or image.
## How to use

### edit in .cpp files path to input and output 
Just edit empty strings.

## How to build
> g++ -std=c++17 -o outputfile  input.cpp 

Example

>  g++ -std=c++17 -o wavefilecreator folder_to_wav.cpp

## "Best results" for getting glitches in audio 

<img width="511" alt="1" src="https://user-images.githubusercontent.com/54742442/202549477-edb661c8-b818-4548-8e01-14e6c0f45ec9.png">
<img width="510" alt="2" src="https://user-images.githubusercontent.com/54742442/202549488-6dc3e371-bbd2-4203-93e7-24e401ff0b08.png">
<img width="513" alt="3" src="https://user-images.githubusercontent.com/54742442/202549489-43f29493-aa3d-45c9-8584-371f1ecde228.png">


You can set bit rate in Wavefile.h to 1 and it is more likley to get this kind of image. \
Remember to put it like to 8 that your DAW can import it. 


## Wavefile encoding
The code how to write a 
[WaveFile](https://gist.github.com/csukuangfj/c1d1d769606260d436f8674c30662450) .

## More about pixels
[Pixelcode](https://www.scratchapixel.com/lessons/digital-imaging/simple-image-manipulations/reading-writing-images)

## The image i used
![kandinsky](https://user-images.githubusercontent.com/54742442/201990514-70c5f03b-bdf3-43c7-b27b-dcebbffe8c26.jpg)
