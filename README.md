# VDP SPRITES 1/2 MSX ROM SDCC Library (fR3eL Project)

```
Author: mvac7 [mvac7303b@gmail.com]
Architecture: MSX
Format: C Object (SDCC .rel)
Programming language: C and Z80 assembler
```



## Description

Open Source library with functions to directly access to sprites of the TMS9918A.

Provides basic functions for initialization and display Sprites and functions for access specific parameters (positioning, color, pattern, visibility and EarlyClock).

The SPRITES 1/2 version is designed to work with TMS9918A, although it also allows using the G3 screen mode (V9938), in a simplified manner. 

The functions that assign a color, such as PUTSPRITE or SetSpriteColor, will do it in all the lines of the sprite, so it will NOT be useful to take advantage of the multicolored improvement of the sprites of the V9938.

The Early Clock functions have also been adapted for the G3 mode, since they access the color table of the sprite planes and write in all the lines.

It is complemented with the [VDP TMS9918A MSX ROM Library](https://github.com/mvac7/SDCC_VDP_TMS9918A_MSXROM_Lib), necessary for the initialization of the screen (screen and sprites mode).

It uses the functions from the MSX BIOS, so it is designed to create applications in ROM format.
  
Use them for developing MSX applications using [Small Device C Compiler (SDCC)](http://sdcc.sourceforge.net/) cross compiler.

Includes an application for test and learning purposes.


### About the Sprite libraries

I'm developing several libraries for the management of MSX Sprites, both for the creation of ROMs (using the BIOS), and MSX-DOS executables.
 
They are designed for the development of applications for the first generation of MSX but some of the variations are directed in how certain functions behave when using the G3 mode of the video processor V9938 and thus be able to take advantage of it, when it is executed in a MSX2 or higher.

The projected libraries are the following:
- [SPRITES Small](https://github.com/mvac7/SDCC_VDP_SPRITES_S_MSXROM_Lib) - Basic functions for managing Sprites. It is more compact so it takes up less space in our application.
- [SPRITES](https://github.com/mvac7/SDCC_VDP_SPRITES_MSXROM_Lib) - It includes the same functions as the Small version and adds to access specific parameters (positioning, color, pattern, visibility and EarlyClock).
- [SPRITE 1/2](https://github.com/mvac7/SDCC_VDP_SPRITES_12_MSXROM_Lib) - Same as SPRITES but in the G3 screen mode (V9938), it treats the color parameters in a simplified way. Assign the color parameters and EarlyClock to all the lines of the Sprites.
- SPRITE DUMP (In development) - Uses a buffer in RAM that has to be dumped in each interruption. Includes a Sprite Flicker, to allow viewing up to 8 sprites per line.

To optimize our development, I recommend building your library with only those functions you need.

I have yet to develop a library to work with the multi-colored Sprites of the V9938.



## History of versions

- v1.2 (22/12/2020) Removed sprite mode initialization functions.
- v1.1 (2/02/2017)
- v1.0 ?



## Requirements

* Small Device C Compiler (SDCC) v3.9 http://sdcc.sourceforge.net/
* Hex2bin v2.5 http://hex2bin.sourceforge.net/
* [VDP TMS9918A MSX ROM Library](https://github.com/mvac7/SDCC_VDP_TMS9918A_MSXROM_Lib).



## Acknowledgments
  
I want to give a special thanks to all those who freely share their knowledge with the MSX developer community.

* Avelino Herrera > [WEB](http://msx.atlantes.org/index_es.html)
* Nerlaska > [Blog](http://albertodehoyonebot.blogspot.com.es)
* Marq/Lieves!Tuore > [Marq](http://www.kameli.net/marq/) [Lieves!Tuore](http://www.kameli.net/lt/)
* [Fubukimaru](https://github.com/Fubukimaru) > [Blog](http://www.gamerachan.org/fubu/)
* Andrear > [Blog](http://andrear.altervista.org/home/msxsoftware.php)
* Ramones > [MSXblog](https://www.msxblog.es/tutoriales-de-programacion-en-ensamblador-ramones/) - [MSXbanzai](http://msxbanzai.tni.nl/dev/faq.html)
* Sapphire/Z80ST > [WEB](http://z80st.auic.es/)
* Fernando García > [youTube](https://www.youtube.com/user/bitvision)
* Eric Boez > [gitHub](https://github.com/ericb59)
* MSX Assembly Page > [WEB](http://map.grauw.nl/resources/msxbios.php)
* Portar MSX Tech Doc > [WEB](http://nocash.emubase.de/portar.htm)
* MSX Resource Center > [WEB](http://www.msx.org/)
* Karoshi MSX Community (RIP 2007-2020)
* BlueMSX emulator >> [WEB](http://www.bluemsx.com/)
* OpenMSX emulator >> [WEB](http://openmsx.sourceforge.net/)
* Meisei emulator >> ?



## Functions

* void ClearSprites() - Initialises all sprite data.
* void PUTSPRITE(char plane, char x, char y, char color, char pattern) - Displays the sprite pattern.
* void SetSpritePattern(char plane, char pattern) - Assign a pattern to a sprite plane.
* void SetSpriteColor(char plane, char color) - Assign a color to a sprite plane.
* void SetSpritePosition(char plane, char x, char y) - Assigns the position coordinates of a sprite plane.
* void SetSpriteVisible(char plane, boolean state) - Hides or shows a sprite plane.
* void SetEarlyClock(char plane) - Apply the Early Clock of a sprite plane. Move 32 points to the left the X position of the sprite.
* void UnsetEarlyClock(char plane) - Disables the Early Clock. Restore the position of a sprite plane.
