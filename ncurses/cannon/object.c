// 20220501 K.OHWADA
// original : https://www.kushiro-ct.ac.jp/yanagawa/curses/cannon/


// object.c
// Processing of moving objects

#include <math.h>
#include "object.h"


/* 
 * Object initialization
 */
void InitObject(Object *obj,
  double px, double py, double vx, double vy, double sx, double sy,
  int life)
{
  obj->px = px; obj->py = py;
  obj->vx = vx; obj->vy = vy;
  obj->sx = sx; obj->sy = sy;
  obj->life = life;
}


/* 
 * Motion of an object
 */
void MoveObject(Object *obj)
{
  obj->px += obj->vx;
  obj->py += obj->vy;
}


/* 
 * Collision judgment
 */
int ChkHit(Object *obj1, Object *obj2)
{
  if (fabs(obj1->px - obj2->px) > (obj1->sx + obj2->sx)) return (0);
  if (fabs(obj1->py - obj2->py) > (obj1->sy + obj2->sy)) return (0);
  return (1);
}

