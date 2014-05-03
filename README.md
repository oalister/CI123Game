# Starship Fontana #

This is project is based on a game written in C++ using the SDL library. The original game is available at https://github.com/AidanDelaney/StarshipFontana.

The features I have added are:
*Static walls that other objects colide with. The player and projectiles cannot pass through 	walls.
*A Score that is increased by collecting coins.
*End game that occurs when the player collides with an enemy or when all the enemies are dead
*Collectable coins that dissapear after they have been collected.
*Player has a persistent direction so that the player doesn't have to keep mashing the arrow keys.


## Story ##
Aliens are preparing to invade earth and you are the planets last hope!
Fy past the alien's defences and shoot your lasers to blow them up and save earth.
Collect coins to gain points.

## Installation ##
Requirements: SDL development libraries installed on your system.  

The easiest way to compile is to use a command-line

"$g++ -c src/*.cpp -std=c++0x -I/usr/include/sigc++-2.0/  \-I/lib64/sigc++-2.0/include/"

`$ g++ -o starship src/Main.o -lSDL -lSDL_image`

to run the game enter:

`$ ./starship`
 
from the top-level directory.  The game will expect to find the
`assets` directory under its current working directory.

## Credits ##
The sprites in this game come directly from 
[SpriteLib](http://www.widgetworx.com/widgetworx/portfolio/spritelib.html) and are used
under the terms of the [CPL 1.0](http://opensource.org/licenses/cpl1.0.php).


The event system is based on [Libsigc++](http://libsigc.sourceforge.net/)
and is used under the [LGPL](http://www.gnu.org/copyleft/lgpl.html).
