#ifndef _POINT_INCLUDED_
#define _POINT_INCLUDED_

#include "sprite.h"
#include "vector"

namespace simplecpp{
class Circle : public Sprite{
public:
  double radius;
  float x,y;
  int num_seg;
  Circle(Composite* owner = NULL);
  Circle(const double x, const double y, const double radius=10,
	  Composite* owner=NULL);
  double getRadius();
  void init(const double x, const double y, const double radius=10, 
	    bool repaintP=true);
  void reset(const double x, const double y, const double radius=10, 
	    bool repaintP=true);
  virtual void paint(Pose *p);
  virtual Sprite * clone();
  virtual void scale(double factor, bool repaintP=true);
};
}
#endif
