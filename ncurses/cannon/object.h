// 20220501 K.OHWADA
// original : https://www.kushiro-ct.ac.jp/yanagawa/curses/cannon/


#ifndef OBJECT_H
#define OBJECT_H

/** 
 * Moving object structure
 */
typedef struct {
  double px, py;	// posision
  double vx, vy;	// speed
  double sx, sy;	// Movement size (distance from the center) 
  int    life;		// alive / death judgment flag (0:dead / 1:alive)
} Object;

extern void InitObject(Object *obj,
  double px, double py, double vx, double vy, double sx, double sy,
  int life);
extern void MoveObject(Object *obj);
extern int ChkHit(Object *obj1, Object *obj2);

#endif

