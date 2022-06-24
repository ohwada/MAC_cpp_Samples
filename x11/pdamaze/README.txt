README.txt for PDA Maze

by Bill Kendrick
bill@newbreedsoftware.com
http://www.newbreedsoftware.com/pdamaze/

May 22, 2001 - September 4, 2001


About:
------
  "PDA Maze" is a simple maze game.  A random two-dimensional maze is
  generated, and you must navigate it using a three-dimensional,
  first-person view.

  The game is written using Xlib (X-Window), and should run on any
  compatible system (eg, Unix, Linux, BSD, MacOSX, etc.).  However, it
  was specifically created to run on the Linux-based "Agenda" PDA.


Features:
---------
  * High quality graphics
  * Simple sound effects
  * Numerous game options
    * Count-up or count-down timer
    * Three maze sizes
    * Three mapping modes:  show all, show-as-you-go, hide


Installing:
-----------
  * Run "make"

    The Makefile will attempt to build a version playable on your
    development environment (your desktop).  This is "pdamaze.host".

    If you have the MIPS compiler toolchain installed, it should also
    build a MIPS version for Agendas using the SNOW kernel/romdisk.
    This is "pdamaze.snow".

    If you're using the older, SVR4-based (non-SNOW) Agenda system,
    you can ask "make" to create a binary for that.  Just run
    "make mips-svr4"

  * Copy to your PDA

    Copy the "pdamaze.snow" program to your PDA.  For example, you could
    "rsync" it to the "/flash/local/bin/" directory.

    On the Agenda, you can create a menu-item entry under "Games" by
    creating a symbolic link.

      vr$  cd ~/.wmx/
      vr$  cd Games/
      vr$  ln -s /flash/local/bin/pdamaze.snow PDAMaze

    You can also upload the "pdamaze.xpm" icon to your PDA, for use
    in a graphical loader (eg, Agenda's "Launchpad").  For example,
    you could "rsync" it to "/flash/local/pixmaps/".  Then add the icon
    to the launcher.

    On the Agenda, you can do this:

      vr$  cat >> ~/.wmx/.icons
      Games/PDAMaze;/flash/local/pixmaps/pdamaze.xpm   [ Enter ]
      [ Control-D ]

    Then quit and re-start the Launchpad program.


Screen Layout:
--------------
  The top part of the screen contains the view in front of you.
  You can see the walls and passageways a few steps in front of you.
  In the distance, you can see mountains and hills.  Pay attention,
  because they can help you determine what direction you're facing.

  The bottom part of the screen is split into three:

  * Compass
    This shows you the direction you're currently facing.
    North, East, South or West.

  * Map of the Maze
    A small map of the maze, from a bird's eye view.
    Your current position is marked with a box.

  * Timer
    This shows you how long you've been playing.


Controls:
---------
  You can control the game with the buttons on the Agenda or a keyboard:

    * Left
      Rotate counter clockwise (North -> West -> South -> East -> North)

    * Right
      Rotate clockwise (North -> East -> South -> West -> North)

    * PageUp or Up
      Move forward

    * PageDown or Down
      Move backwards

    * Escape
      Quit


  You can also control the game with the stylus or a mouse.

  The display at the top of the screen is divided into four triangular zones:

      \  /
       \/
       /\
      /  \

    * Left zone
      Rotate counter clockwise

    * Right zone
      Rotate clockwise

    * Top zone
      Move forward

    * Bottom zone
      Move backwards


  There are also some buttons at the very bottom of the screen:

    * "Done"
      Quit


Credits:
--------
  Graphics and programming by Bill Kendrick
  bill@newbreedsoftware.com

  Maze generation code based on "Hidden Maze" for Atari BASIC.
  Published by Compute! magazine.

  Skyline photograph source URLs:
    East:  babs.com.au/hillcrest/
    North: 128.2.242.152/afs/cs.cmu.edu/user/har/Web/usr0/summer97.html
    South: www.geocities.com/jaybop42/cincinnati.htm
    West:  cfa-www.harvard.edu/space_geodesy/BARGEN/station_info/images/dyer/
