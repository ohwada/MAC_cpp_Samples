// 2022-05-01 K.OHWADA
// original : https://www.kushiro-ct.ac.jp/yanagawa/curses/cannon/
 
 // chnge log
// 2022-05-01
// separated Sound definitions into sound.h


// linux
// gcc  main.c  object.c  gameutil.c -o cannon  -lm -lncurses

// mac
// gcc  main.c  object.c  gameutil.c -o cannon  `pkg-config --cflags --libs ncurses` 


/*
 * Canon game Ver.8
 * by yanagawa@kushiro-ct.ac.jp
 */

//#include <ncursesw/ncurses.h>
#include <ncurses.h>
#include <locale.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <sys/stat.h>
#include "object.h"
#include "gameutil.h"
#include "sound.h"

#define INTERVAL 20	// (milliseconds)
#define GRAVITY  0.01	// Gravitational acceleration
#define N_TYPE    4	// Type of enemy aircraft，don't change
#define N_ENEMY  10	// Maximum number of enemy aircrafts

#define N_BULLET 20	// Maximum number of bullets
#define READYINT 10	// Fire time interval (number of loops)
#define BOOMDUR  15	// Explosion duration (number of loops)



/**
 * Object shape structure
 */
typedef struct {
  double sx, sy;			// size
  void   (*draw)(double x, double y);	// Drawing function pointer
} Shape;


/**
 * Enemy aircraft structure
 */
typedef struct {
  Object obj;
  Shape  shape;
} Enemy;


/* Initialization of enemy aircraft */
void InitEnemy(Enemy *enemy,
  double px, double py, double vx, double vy, int life, Shape shape)
{
  InitObject(&(enemy->obj), px, py, vx, vy, shape.sx, shape.sy, life);
  enemy->shape = shape;
}


/**
 * InitEnemies
 */
void InitEnemies(Enemy enemy[], int n,
  double px, double py, double vx, double vy, int life, Shape shape[])
{
  int  i;

  for (i = 0; i < n; i++) {
    InitEnemy(&enemy[i], px, py, vx, vy, life, shape[Rand(N_TYPE)]);
  }
}


/* Initialization of Bullets */
void InitBullet(Object *bullet,
  double px, double py, double vx, double vy, int life)
{
  InitObject(bullet, px, py, vx, vy, 0.0, 0.0, life);
}

void InitBullets(Object bullet[], int n,
  double px, double py, double vx, double vy, int life)
{
  int  i;

  for (i = 0; i < n; i++) {
    InitBullet(&bullet[i], px, py, vx, vy, life);
  }
}


/* Missile movement */
void MoveMissile(Object *obj)
{
  int w, h;

  getmaxyx(stdscr, h, w);
  MoveObject(obj);

  if ((int)(obj->px) < 0)  obj->life = 0;
  else if ((int)(obj->px) >= w) obj->life = 0;
  else if ((int)(obj->py) < 0)  obj->life = 0;
  else if ((int)(obj->py) >= h) obj->life = 0;
}

/* Bullet movement */
void MoveBullet(Object *obj)
{
  int w, h;

  getmaxyx(stdscr, h, w);
  obj->vy += GRAVITY;
  MoveObject(obj);

  if ((int)(obj->px) < 0)  obj->life = 0;
  else if ((int)(obj->px) >= w) obj->life = 0;
  else if ((int)(obj->py) >= h) obj->life = 0;
}

void MoveBullets(Object bullet[], int n)
{
  int  i;

  for (i = 0; i < N_BULLET; i++) {
    switch (bullet[i].life) {
    case 1 : MoveBullet(&bullet[i]); break;
    case 2 : MoveMissile(&bullet[i]); break;
    default : break;
    }
  }
}


/* Enemy movement */
void MoveEnemy(Enemy *enemy)
{
  int w, h;

  getmaxyx(stdscr, h, w);
  MoveObject(&(enemy->obj));

  if (enemy->obj.life < 0) enemy->obj.life++;	// 爆発中

  if ((int)(enemy->obj.px) < -10) enemy->obj.life = 0;
  if ((int)(enemy->obj.py) < 0)   enemy->obj.life = 0;
  if ((int)(enemy->obj.py) >= h)  enemy->obj.life = 0;
}


/**
 * draw Missile 
 */
void DrawMissile(Object *obj)
{
  UseColor(6);
  DrawBlocks((int)(obj->py), (int)(obj->px), "#");
  UseColor(7);
  DrawBlocks((int)(obj->py-obj->vy), (int)(obj->px-obj->vx), ".");
  DrawBlocks((int)(obj->py-2*obj->vy), (int)(obj->px-2*obj->vx), "&");
}


/**
 * draw Bullet 
 */
void DrawBullet(Object *bullet)
{
  UseColor(3);
  mvaddch((int)(bullet->py), (int)(bullet->px), '*');
}

void DrawBullets(Object bullet[], int n)
{
  int  i;

  for (i = 0; i < n; i++) {
    switch (bullet[i].life) {
    case 1 : DrawBullet(&bullet[i]); break;
    case 2 : DrawMissile(&bullet[i]); break;
    default : break;
    }
  }
}


/**
 * draw angle
 */
void DrawAngle(int y, int x, int angle)
{
  UseColor(7);
  mvprintw(y, x, "angle : %d deg", angle);
}


/**
 * DrawEnemy0
 *  drawing function of Enemy aircraft 
 */
void DrawEnemy0(double px, double py)
{
  int x, y;
  UseColor(2);
  x = (int)px - 3;
  y = (int)py;
  DrawBlocks(y-1, x, " *||   ");
  DrawBlocks(y  , x, "<=====P");
  DrawBlocks(y+1, x, "  *\\\\  ");
};


/**
 * DrawEnemy1
 */
void DrawEnemy1(double px, double py)
{
  int x, y;
  UseColor(4);
  x = (int)px - 4;
  y = (int)py;
  DrawBlocks(y-1, x, "   -//| /");
  DrawBlocks(y  , x, "-=======/");
  DrawBlocks(y+1, x, "    -\\\\| ");
};


/**
 * DrawEnemy2
 */
void DrawEnemy2(double px, double py)
{
  int x, y;
  UseColor(6);
  x = (int)px - 6;
  y = (int)py;
  DrawBlocks(y-2, x, "     /#|     ");
  DrawBlocks(y-1, x, "    *|#|   /|");
  DrawBlocks(y  , x, "<###########=");
  DrawBlocks(y+1, x, "     *\\#\\     ");
  DrawBlocks(y+2, x, "       \\#\\    ");
};


/**
 * DrawEnemy3
 */
void DrawEnemy3(double px, double py)
{
  int x, y;
  UseColor(2);
  x = (int)px - 2;
  y = (int)py;
  DrawBlocks(y-1, x, "--## ");
  DrawBlocks(y  , x, "@@@@@");
};


/**
 * DrawBoom
 */
void DrawBoom(double px, double py, int size)
{
  int x, y;
  UseColor(1);
  size = size*10/BOOMDUR;
  if (size < 4) {
    x = (int)px - 1;
    y = (int)py;
    DrawBlocks(y  , x, "( )");
  } else if (size < 7) {
    x = (int)px - 3;
    y = (int)py;
    DrawBlocks(y-1, x, "  &&&  ");
    DrawBlocks(y  , x, " &   & ");
    DrawBlocks(y+1, x, "  &&&  ");
  } else {
    x = (int)px - 5;
    y = (int)py;
    DrawBlocks(y-2, x, "   &&&&&   ");
    DrawBlocks(y-1, x, " &&&   &&& ");
    DrawBlocks(y  , x, "&&       &&");
    DrawBlocks(y+1, x, " &&&   &&& ");
    DrawBlocks(y+2, x, "   &&&&&   ");
  }
}


/**
 * Draw Enemy aircraft
 */

void DrawEnemy(Enemy *enemy)
{
  if (enemy->obj.life == 1) {		// 機体
    enemy->shape.draw(enemy->obj.px, enemy->obj.py);
  } else {				// 爆発
    DrawBoom(enemy->obj.px, enemy->obj.py, -enemy->obj.life);
  }
}


/**
 * DrawEnemies
 */
void DrawEnemies(Enemy enemy[], int n)
{
  int  i;

  for (i = 0; i < n; i++) {
    if (enemy[i].obj.life != 0) DrawEnemy(&enemy[i]);
  }
}


/**
 *  mainroutine of the game
 */
void Game(int mode)
{
  Object  bullet[N_BULLET];
  Enemy   enemy[N_ENEMY];
  int     t;

  int     h, w;
  int     key, fire, ready, angle;
  int     i, j;
  char    autokey[10] = "z- - - k j";

  Shape shape[] = {
    {3.0, 1.0, DrawEnemy0},
    {4.0, 1.0, DrawEnemy1},
    {5.0, 1.0, DrawEnemy2},
    {2.0, 1.0, DrawEnemy3}
  };

  PlaySnd(START_SND);

  InitRand();
  InitBullets(bullet, N_BULLET, 0.0, 0.0, 0.0, 0.0, 0);
  InitEnemies(enemy, N_ENEMY, 0.0, 0.0, 0.0, 0.0, 0, shape);
  angle = 45;
  ready = 0;

  timeout(0);
  while (1) {
    InitWait();

    erase();
    getmaxyx(stdscr, h, w);

    DrawBullets(bullet, N_BULLET);
    DrawEnemies(enemy, N_ENEMY);
    DrawAngle(0, 0, angle);
    refresh();
  
    fire = 0;
    key = getch();
    if ((key == EOF) && (mode == 'd')) key = autokey[Rand(10)];

    switch (key) {
    case 'h' :
    case 'k' :
    case KEY_LEFT :
    case KEY_UP :   angle += 5; break;	// angle up
    case 'l' :
    case 'j' :
    case KEY_RIGHT :
    case KEY_DOWN : angle -= 5; break;	// angle down
    case ' ' : fire = 1; break;		// fire Bullet
    case 'z' : fire = 2; break;		// fire Missile
    case 'q' : return;			// Game canceled
    }
    if (angle < 0) angle = 0;
    if (angle > 90) angle = 90;

// fire bullet
    if (ready <= 0) {
      if (fire != 0) {
        for (i = 0; i < N_BULLET; i++) {
          if (bullet[i].life) continue;

          switch (fire) {
          case 1: PlaySnd(SHOT_SND); break;
          case 2: PlaySnd(JET_SND); break;
          default: break;
          }
          InitBullet(&bullet[i], 0.0, (double)(h-1),
            cos(angle*M_PI/180.0)*(1+fire)/2, -sin(angle*M_PI/180.0)*(1+fire)/2, fire);
          ready = READYINT;
          break;
        }
      }
    } else {
      ready--;
    }

// Shoot down
    for (i = 0; i < N_BULLET; i++) {
      if (bullet[i].life == 0) continue;

      for (j = 0; j < N_ENEMY; j++) {
        if (enemy[j].obj.life > 0) {
          if (ChkHit(&bullet[i], &enemy[j].obj) != 0) {
            PlaySnd(BOOM_SND);
            enemy[j].obj.life = -BOOMDUR;		// 爆発
            bullet[i].life = 0;
            break;
          }
        }
      }
    }


    // Bullet movement
    MoveBullets(bullet, N_BULLET);

    // Enemy aircraft movement
    for (j = 0; j < N_ENEMY; j++) {
      if (enemy[j].obj.life != 0) {
        MoveEnemy(&enemy[j]);
      } else {
  t = Rand(N_TYPE);
  if (t >= 3) {		// land type
    InitEnemy(&enemy[j], (double)(w+Rand(10)+5), (double)(h-1),
      -(Rand(7)+3)*0.01 , 0.0, 1, shape[t]);
  } else {		// Aviation type
    InitEnemy(&enemy[j], (double)(w+Rand(10)+5), (double)Rand(h/2),
      -(Rand(7)+3)*0.1 , 0.0, 1, shape[t]);
  }

      }
    }

    Wait(INTERVAL);	// Operating speed
                                    // Standard sleep()

  }
}


/**
 * title screen
 */
int Title()
{
  int  h, w, key;

  getmaxyx(stdscr, h, w);

  erase();
  attrset(0);
  UseColor(11);
  DrawBlocks(h/2-9, (w-42)/2, "###  #  #  # #  # ### #  # ##   #  #   #  ");
  DrawBlocks(h/2-8, (w-42)/2, "#   ### #  # #  # # # #  # # # ### #   #  ");
  DrawBlocks(h/2-7, (w-42)/2, "#   # # ## # ## # # # ## # ##  # # #   #  ");
  DrawBlocks(h/2-6, (w-42)/2, "#   ### # ## # ## # # # ## # # ### #   #  ");
  DrawBlocks(h/2-5, (w-42)/2, "### # # #  # #  # ### #  # ##  # # ### ###");

  attrset(A_BOLD);
  UseColor(1);
  CenterStr(h/2-4, w/2, "Cannon Game");
  UseColor(2);
  CenterStr(h/2-2, w/2, "Push [Space] to start game");
  CenterStr(h/2-1, w/2, "Push [S] to start in silent mode");
  CenterStr(h/2,   w/2, "Push [D] to start demo");
  CenterStr(h/2+1, w/2, "Push [Q] to quit");
  UseColor(3);
  CenterStr(h/2+3, w/2, "[Space]  [z]  [↑] [↓]");
  CenterStr(h/2+4, w/2, "bullet missile up  down");
  move(0, 0);

  timeout(-1);
  key = getch();

  return (key);
}


/**
 * existsFile
 */
bool existsFile(char *path) 
{
    struct stat   sb;   
    int ret = stat(path, &sb);
    bool res = ( ret == 0 )? true: false;
    return res;
}

/**
 * main
 */
int main()
{
  int  key;

  setlocale(LC_ALL, "");

if( ! existsFile(PLAY_CMD) ) {
    printf( "not found PLAY_CMD: %s \n", PLAY_CMD );
     return 1;
}

if( ! existsFile(START_SND) ) {
    printf( "not found START_SND : %s \n", START_SND );
     return 1;
}


if( ! existsFile(SHOT_SND) ) {
    printf("not found SHOT_SND: %s \n", SHOT_SND );
     return 1;
}

if( ! existsFile( JET_SND) ) {
    printf( "not found JET_SND: %s \n",  JET_SND );
     return 1;
}

if( ! existsFile(BOOM_SND) ) {
    printf( "not found BOOM_SND : %s \n", BOOM_SND );
     return 1;
}


  initscr();
  noecho();
  cbreak();
  curs_set(0);
  keypad(stdscr, TRUE);
  InitColor(COLOR_BLACK);
  attrset(A_BOLD);

// Audio playback command settings
  SetPlay(PLAY_CMD);	

  while (1) {
    key = Title();
    if (key == 'q') break;
    if ((key == 's') || (key == 'd')) {
      SetSnd(0);
    } else {
      SetSnd(1);
    }
    Game(key);
  }

  endwin();
  return (0);
}

