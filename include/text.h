#ifndef _TEXT_INCLUDED_
#define _TEXT_INCLUDED_

#include "sprite.h"

namespace simplecpp{

class Composite;
class Text : public Sprite{
 protected:
  string message;
  GLint ctx, myFont;
  XPoint xp;
 public:
  Text(double cx, double cy, string m, Composite* owner=NULL);
  Text(double cx, double cy, double n, Composite* owner=NULL);
  Text(Composite* owner=NULL);
  void reset(double cx, double cy, string m);
  void reset(double cx, double cy, double m);
  void setMessage(string s);
  void paint(Pose* p=NULL);
  string getMessage();
  XPoint getPos();
  Color getColor();
  bool isVisible();
  double getAngle();
  double getScale();
};
}
#endif
