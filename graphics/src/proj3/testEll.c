/*
  Bruce A. Maxwell
  Fall 2014

  Test function 1 for the graphics primitives assignment
  Enterpoop
 */

// edit the include files as necessary
#include "graphics.h"

// draw a box
static int box( Image *src, Color color, int x, int y, int dx, int dy );
static int box( Image *src, Color color, int x, int y, int dx, int dy ) {
  Line l;
  
  line_set2D( &l, x, y, x, y+dy );
  line_draw( &l, src, color );

  line_set2D( &l, x, y+dy, x + dx, y+dy );
  line_draw( &l, src, color );

  line_set2D( &l, x+dx, y+dy, x+dx, y );
  line_draw( &l, src, color );

  line_set2D( &l, x+dx, y, x, y );
  line_draw( &l, src, color );
  printf("box drawn\n");
  return(0);
}

// draw a few boxes, a circle, and some lines.
int main(int argc, char *argv[]) {
  Image *src;
  Color White;
  Color Red;
  Point p;
  Ellipse e;
  Line line;

  color_set( &White, 1.0, 1.0, 1.0 );
  color_set( &Red, 0.9, 0.05, 0.05 );

  src = image_create( 400, 600 );

  box( src, White, 100, 100, 100, 20 );
  box( src, White, 100, 200, 100, 20 );
  box( src, White, 150, 140, 70, 40 );
  box( src, White, 160, 120, 10, 20 );
  box( src, White, 160, 180, 10, 20 );

  point_set2D( &p, 260, 160 );
  ellipse_set( &e, p, 60, 30 );
  ellipse_draw( &e, src, White );

  line_set2D( &line, 290, 210, 470, 300);
  line_draw( &line, src, Red );

  line_set2D( &line, 295, 205, 475, 280);
  line_draw( &line, src, Red );
  
  image_write( src, "testEll.ppm" );

  image_free( src );

  return(0);
}
