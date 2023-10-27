# DOS-retrolib
### [Wiki](https://github.com/ifknot/DOS-retrolib/wiki)
DOS 16 bit Real Mode Graphics and Physics Library written in C++98 &amp; 8086 Assembly

![small logo](https://cldup.com/MWyAWo2qLY.png) 

Written using [Microsoft Visual Studio Community Edition](https://visualstudio.microsoft.com/vs/community/)

Built using [Open Watcom V2 Fork](https://open-watcom.github.io/)

Tested using [DOSBOX](https://www.dosbox.com/) and my IBM XT


## Project Progress

### TODO:

dumps -> files -> arena_t -> bitmap_t -> blits

TODO BIOS
+ [...] v0.3 complete on an **as needed basis**

TODO DOS
+ [...] v0.3  complete on an **as needed basis**
    + [ ] block file load

TODO MEM
+ [ ] v0.1
+ [ ] mem::dump(ostream, ...)
+ [ ] mem::file_dump(cstring, ...)
+ [ ] mem::file_load(cstring, ...)
+ [ ] mem::load(istream, ...)
+ [ ] arena_t
    + [ ] arena::functions(...)
+ [ ] mcb_t 
+ [ ] mcb stream operators
+ [ ] get_available_low_memory

TODO GFX
+ [ ] v0.5
+ [ ] bitmap_t (universal)
    + [ ] bmp::functions(...)
+ [ ] HGA
    + [ ] hga::blits(...) universal bmp -> specialised vram

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
