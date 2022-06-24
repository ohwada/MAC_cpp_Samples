README.txt

3D Pong v.0.5

by Bill Kendrick
bill@newbreedsoftware.com

New Breed Software
http://www.newbreedsoftware.com/

December 10, 1997 - April 28, 2004


WHAT IS 3D PONG?

  3D Pong is an X-Window game for 1 or 2 players.  It's a 3D game based
  on the first arcade game, "Pong."  Like "Pong," it's a game played with
  a ball and paddles.  The object is to hit the ball and get it in the
  other player's goal.  Use your paddle to deflect the ball and keep it
  from getting in your goal.

  3D Pong has three game modes:

    1. Two player - requires two X-Window display servers
    2. One player - against a computer player
    3. Handball - one player against gravity and a wall


INSTALLING

  To compile and install 3D Pong, see "INSTALL.txt".


RUNNING THE GAME

  To run the game, type "3dpong" with a pair of arguments that depend on the
  game mode you wish to play:

  Two player game:

    player 1's display server
    player 2's display server

    Example:  3dpong $DISPLAY desktop.domain.com:0.0
              3dpong desktop.domain.com:0.0 machine.domain.com:0.0

  One player game:

    player's display
    the word "computer" or "--computer"

    Example:  3dpong $DISPLAY --computer
              3dpong machine.domain.com:0.0 computer

  Handball game:

    player's display server
    [no second display argument!]

    Example:  3dpong $DISPLAY
              3dpong desktop.domain.com:0.0


  You can also specify the "gravity" to be used in the game.  In the
  one- and two-player ping-pong games, this defines gravity towards the
  "floor" of the game.  (The floor is marked with a divider in the middle
  between the two players's sides.)  You CAN have negative gravity (where
  the ball flies towards the ceiling)!

  In the handball game, gravity is defined towards your goal/paddle.
  The minimum gravity is 0.1; negative gravity is not allowed.  If you
  enter a negative gravity, it's absolute value will be taken.  If the
  gravity is less than 0.1, 0.1 will be used.

  To specify gravity, append "--gravity value" or "-g value" to the
  command line.

    Example:  3dpong $DISPLAY --gravity 0.5
              3dpong desktop.domain.com:0.0 machine.domain.com:0.0 -g 0.5

  To play a game with a net (not available in "handball" mode), append
  "--net value" or "-n value" to the command line.  The net appears in the
  middle of the game arena, where the marker normally is.  If the ball hits
  the net, it bounces back with full force.  You can specify a net height up
  to 0.75 (one third the height of the game arena).  Values under 0.0 get
  taken as their absolute value.  Values over 0.75 are taken as 0.75.

  The "--net" switch must appear after the "--gravity" switch, if you used one.

    Example:  3dpong $DISPLAY --computer --net 0.5
              3dpong $DISPLAY other.domain.com:0.0 --gravity 0.2 -n 0.75

  To play a game with sound, append "--sound" or "-s" to the command
  line.  (It must appear after the "--net" switch, if you used one.)

    Example:  3dpong $DISPLAY --sound
              3dpong $DISPLAY computer -g 0.5 --sound

  The sound will be played on the machine on which the game is
  executing.  (The program simply sends ".au" audio files to the
  "/dev/audio" device.  The sounds were "stolen" from the game
  "xboing"; thanks guy(s)!)

  To control the paddle in the game without holding the mouse button down,
  add "--noclick1" for player one, and "--noclick2" for player two.
  They must be after any of the previously mentioned options, and player
  one's "--noclick1", if any, should come first.

  Two extremely simple scripts have been created to start a one-player
  3dpong session:

    3dpong-vs-computer.sh - Play against the computer on your
                            default $DISPLAY with a 0.5-high net

    3dpong-handball.sh    - Play handball on your default $DISPLAY


  So, in summary, you have the following switches available to you, in this
  order:

    3dpong display1 [display2 | --computer] [--gravity value]
           [--net value] [--sound] [--nockick1] [--noclick2]


ON THE SCREEN:

  The game is viewed in 3D.  Depending on your viewing mode, you see the
  game from a different angle.  (See "3D PONG CONTROLS" below.)

  One- And Two-Player Ping Pong Mode:

    * There is a white divider line in the middle of the court to show
      you where the "floor" is.
    * Player one's paddle is a red square.  Player two's is blue.
    * Score is displayed at the upper left.  Player one's score is red.
      Player two's score is blue.

  Handball Mode:

    * Your paddle is a red square.
    * Score and high score are displayed at the upper left.

  Both Modes:

    * The ball is a green diamond shape.
    * Dark green markers appear on two walls of the court, showing you
      relative positions of the ball.


3D PONG CONTROLS:

  Moving the paddle:

    Left-Click in your window and drag (holding the left mouse button,
    unless you've specified "noclick" mode; see above) to move the paddle
    around.

  Serving:

    In a one- or two-player ping-pong game, when it's your turn to serve,
    or to start a game in handball mode:

    * Position your paddle where you wish the ball to start
    * Right-Click to launch the ball

  Changing views:

    Press the [V] key to change your viewing perspective.  There are six
    modes it cycles through:

      1. Normal   - First person perspective from behind your paddle.
      2. Bleacher - From the side of the game.  (Your paddle on the left.)
      3. Above    - From above the game.  (Your paddle on the top.)
      4. FreeView - Choose any angle. (Use Middle-Click and drag to change
                    angles.  Careful not to get confused!)
      5. Follow the Ball - The perspective moves and zooms depending on the
                           position of the ball.
      6. From the Paddle - The perspective is similar to "Normal" mode,
                           but keeps your paddle in the center.

    Press the [3] keyto toggle 3D glasses (red/blue) mode.
    When using 3D glasses, you must use red/blue glasses with the red
    lense on your left eye.  For best 3D results, get very close to the
    screen.  (Careful of health risks though!!!)  Your milage may vary.

  Changing controls:

    To toggle whether your paddle is controlled while mouse button one
    is down (normal) or not ("--noclick..."), press [C].

  So, in summary, you have the following keyboard controls:

    [V] - Change view
    [3] - Toggle 3D glasses mode
    [C] - Toggle "noclick" mode
    [Q] - Quit


GAME RULES:

  One and two-player ping-pong games:

    * The game is played until the player(s) decide to quit.
    * The ball moves faster and faster until someone scores, at which point
      it slows down again.
    * Score is accumulated during the game when the ball goes past a
      player's paddle and into their goal.
    * When a player scores (the ball goes into their opponent's goal),
      they get to serve.

  Handball game:

    * Multiple games are played until the player decides to quit.
    * Score is accumulated during the game when the ball bounces off the
      player's paddle.
    * The score is zeroed and the game starts over when
      the ball goes past the player's paddle and into their goal.
    * A high score is kept for the session.


