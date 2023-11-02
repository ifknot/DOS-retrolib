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
+ [x] 25  Set interrupt vector
+ [x] 35  Get interrupt vector
+ [x] 36  Get disk free space
+ [ ] 37  Get/set switch character (undocumented)
+ [ ] 38  Get/set country dependent information
+ [ ] 39  Create subdirectory (mkdir)
+ [ ] 3A  Remove subdirectory (rmdir)
+ [ ] 3B  Change current subdirectory (chdir) 
+ [x] 3C  Create file using handle
+ [x] 3D  Open file using handle
+ [x] 3E  Close file using handle
+ [x] 3F  Read file or device using handle
+ [x] 40  Write file or device using handle
+ [x] 41  Delete file
+ [x] 42  Move file pointer using handle
+ [x] 43  Change file mode
+ [ ] 44  I/O control for devices (IOCTL)
+ [ ] 45  Duplicate file handle
+ [ ] 46  Force duplicate file handle
+ [ ] 47  Get current directory
+ [x] 48  Allocate memory blocks
+ [x] 49  Free allocated memory blocks
+ [ ] 4A  Modify allocated memory blocks

TODO MEM
+ [ ] v0.1
+ [x] mem::dump(ostream, ...)
+ [x] mem::save(cstring, ...)
+ [ ] mem::load(cstring, ...)
+ [x] mem::save(istream, ...)
+ [ ] arena_t
    + [ ] arena::functions(...)
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
