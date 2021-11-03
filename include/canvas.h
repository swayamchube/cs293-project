#ifndef _CANVAS_INCLUDED
#define _CANVAS_INCLUDED

#include "simplecpp"

namespace simplecpp{
	struct XMotionEvent{
		int x, y;
	};
	struct XButtonEvent{
		int x,y;
		unsigned int button; 
	};
	struct XKeyEvent{
		int x, y;
	};
	struct XEvent{
		int type;
		XKeyEvent xkey;
		XButtonEvent xbutton;
		XMotionEvent xmotion;
    char key;
	};


  void screenshot(char *filename);	
  double randuv(double u, double v); 
  //  void srand(unsigned int);
  void wait(float duration);
  void abort();

  void initCanvas(const char window_title[]="Simplecpp Canvas",
		 int w=500, int h=500);
  // creates the graphics window

  void closeCanvas();
  extern void Initialize();
  void resizeCanvas(int w, int h);
  int canvas_width();  // return the width of the canvas
  int canvas_height();
  int textWidth(string text);
  int textWidth(char op);
  int textHeight();
  int textDescent();
  void addText(Text *t);
  void addSprite(Sprite *t);  // adds *t into the list of active sprites
                              // does not repaint immediately?
   
  void removeSprite(Sprite *t);

  Color COLOR(const char *color_string);  // creates a colour.
  Color COLOR(unsigned int red, unsigned int green, unsigned int blue);

  void imprintLine(short x1, short y1, short x2, short y2, Color line_color=COLOR(0,0,0), unsigned int line_width=2);

	void drawLine(XPoint start, XPoint end, Color line_color,unsigned int line_width=0);

	void drawCircle(XPoint center, float r_new, int num_seg,Color fill_color, bool fill=true, unsigned int line_width=2, int line_style=1, int cap_style=1, int join_style=1, int function=1);
	void drawEllipse(XPoint center, float r_new, float y_new, int num_seg,Color fill_color, bool fill=true, unsigned int line_width=2, int line_style=1, int cap_style=1, int join_style=1, int function=1);


	void drawPolygon(XPoint *points, int npoints, Color fill_color, bool fill=true, unsigned int line_width=2, int line_style=1, int cap_style=1, int join_style=1, int fill_rule=1, int function=1);
	void drawText();
  void c_imprint(Sprite* s);  // paints *s into the background
  void repaint();  // paint the current screen into new buffer, then transfer.
  void beginFrame();  // suspend painting.  set flag appropriately.
  void endFrame();    // resume painting.  reset flag.

void nextEvent(XEvent &event);  // wait for an event: mouseclick, keypress.
char charFromEvent(XEvent &event);
bool mouseButtonPressEvent(XEvent &event); 
bool checkEvent(XEvent &event); 
bool keyPressEvent(XEvent &event);
int BGImage(char * path,int _x_=0,int _y_=0,int _xx_=canvas_width(),int _yy_=canvas_height());
//void deleteBG(int texture);
 bool mouseDragEvent(XEvent &event);  // true if event is drag
  
 
  bool mouseButtonReleaseEvent(XEvent &event);
  void echoKey(XEvent &event, Color clr = Color("blue"));  // print value on screen
  void spriteStatus();
  
  int getClick();  // wait for a click, and return xclickpos*65536+yclickpos.
}

#endif
