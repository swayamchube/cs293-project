#ifndef _ELLIPSE_INCLUDED_
#define _ELLIPSE_INCLUDED_

#include "sprite.h"
#include <vector>

namespace simplecpp{
class Ellipse : public Sprite{
public:
  double radius_x, radius_y;
  float x,y;
  int num_seg;
  Ellipse(Composite* owner = NULL);
  Ellipse(const double x, const double y, const double radius_x=10, const double radius_y=10,
	  Composite* owner=NULL);
  double getRadius();
  void init(const double x, const double y, const double radius_x=10, const double radius_y=10,
	    bool repaintP=true);
  void reset(const double x, const double y, const double radius_x=10, const double radius_y=10,
	    bool repaintP=true);
  virtual void paint(Pose *p);
  virtual Sprite * clone();
  virtual void scale(double factor, bool repaintP=true);
};
}
#endif
