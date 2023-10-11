# DOS-retrolib
### [Wiki](https://github.com/ifknot/DOS-retrolib/wiki)
DOS 16 bit Real Mode Graphics and Physics Library written in C++98 &amp; 8086 Assembly

![small logo](https://cldup.com/MWyAWo2qLY.png) 

Written using [Microsoft Visual Studio Community Edition](https://visualstudio.microsoft.com/vs/community/)

Built using [Open Watcom V2 Fork](https://open-watcom.github.io/)

Tested using [DOSBOX](https://www.dosbox.com/) and my IBM XT


## Project Progress

### TODO:

TODO BIOS
+ [ ] v0.2

TODO DOS
+ [ ] v0.2


TODO SYS
+ [ ] v0.1
+ [ ] test_sys.h
+ [ ] global bios consts for the likes of int 15h

TODO MEM
+ [ ] v0.1
+ [ ] mem arena

TODO GFX
+ [ ] v0.5
+ [ ] rectangle_t & functions
+ [ ] bitblt memory->vram
+ [ ] HGA
+ [ ] CGA
+ [ ] make gfx primitives using arena
+ [ ] use swap buffers paradigm
+ [ ] HGA
+ [ ] CGA
+ [ ] draw(...) primitives

### DOING

DOING BIOS

+ [x] seperate test for each service
+ [x] keyboard
+ [x] clock
+ [x] config
+ [x] bios data area
+ [x] memory
+ [ ] video
+ [ ] video debug streams
+ [x] combined into test bios header

DOING DOS

+ [ ] 25  Set interrupt vector
+ [x] 35  Get interrupt vector
+ [x] 49  Free allocated memory blocks
+ [x] 48  Allocate memory blocks
+ [x] 59  Get extended error information (3.x+)

DOING SYS
+ [x] SYS folder
+ [ ] test_sys.h
+ [x] read/write memloc T
+ [x] move mem consts into lower mem consts
+ [ ] global bios consts for the likes of int 15h

### TEST

TEST BIOS

+ [ ] seperate test for each service
	+ [x] keyboard
	+ [x] clock
	+ [x] config
	+ [x] bios data area
	+ [x] memory
	+ [ ] video
	+ [ ] combined into test bios header

TEST DOS

+ [ ] seperate test for each service
 + [ ] 25  Set interrupt vector
 + [ ] 35  Get interrupt vector
 + [ ] 49  Free allocated memory blocks
 + [ ] 48  Allocate memory blocks
 + [ ] 59  Get extended error information (3.x+)

### DONE

DONE BIOS

DONE DOS

+ [x] replace int86 use asm
+ [x] dos_services.h is long - close up the empty lines
+ [x] dos_services.cpp

DONE SYS

DONE MEM

+ [x] inline debug streams
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
