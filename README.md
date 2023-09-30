# DOS-retrolib
### [Wiki](https://github.com/ifknot/DOS-retrolib/wiki)
DOS 16 bit Real Mode Graphics and Physics Library written in C++98 &amp; 8086 Assembly

![small logo](https://cldup.com/MWyAWo2qLY.png) 

Written using [Microsoft Visual Studio Community Edition](https://visualstudio.microsoft.com/vs/community/)

Built using [Open Watcom V2 Fork](https://open-watcom.github.io/)

Tested using [DOSBOX](https://www.dosbox.com/) and my IBM XT

## Project Progress (*aka the great re-write of 2023*)

TODO DOS

move DOS into retrolib

FIX:
+ [ ] give option to include stream operators if desired but inc in dos.h 
+ [ ] dos_types_stream_operators.h (inc types reduce types header burden)
+ [ ] dos_types_stream_operators.cpp 
+ [ ] add to dos.h
+ [x] dos_services.h is long - close up the empty lines
+ [x] dos_services.cpp
+ [ ] replace int86 use asm
+ [ ] extend test.h

TODO BIOS
+ [x] bios_types_stream_operators.h
+ [x] bios_types_stream_operators.cpp
+ [ ] seperate test for each service
    + [x] keyboard
    + [x] clock 
    + [x] config
    + [ ] bios data area 
    + [ ] memory
    + [ ] video
+ [ ] combined into test bios header

FIX
+ [ ] not depend in dos.h int86

TODO MEM
+ [ ] mem arena

TODO GFX
+ [ ] rectangle_t & functions
+ [ ] bitblt memory -> vram
    + [ ] HGA
    + [ ] CGA
+ [ ] make gfx primitives using arena
+ [ ] use swap buffers paradigm
    + [ ] HGA
    + [ ] CGA
+ [ ] draw(...) primitives

## Why DOS 16 bit?

Having recently aquired a couple of IBM XT 5160 machines I was looking into the best way to create and cross-compile software for this wonderful old machine and its kind.

## Usage

Clone it, compile it, play with it...

## What is this repository for?

My steep learning curve.

## How do I get setup?

Option 1: Run the executable files in DOSBOX - or on your own old iron hardware!

OPtion 2: Download and Install:

+ [Open Watcom V2 Fork](https://open-watcom.github.io/)
+ [Microsoft Visual Studio Community Edition](https://visualstudio.microsoft.com/vs/community/)
+ [DOSBOX](https://www.dosbox.com/)

## Contribution guidelines

Fork it, do your thing and pull request

## Who do I talk to?

Me :)
