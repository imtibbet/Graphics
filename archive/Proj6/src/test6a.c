/*
  Bruce Maxwell
  Fall 2014

  A simple test function for Module_draw that creates 3 X-wing fighters as line drawings

  Requires the following functions to be defined

  element_create
  element_init
  element_delete

  module_create
  module_add
  module_delete
  module_translate2D
  module_scale2D
  module_point
  module_line
  module_module
  module_draw

  drawstate_create
  drawstate_setColor
  drawstate_copy

  vector_set

  point_set2D
  point_copy

  line_set2D
  line_set
  line_copy

  matrix_setView2D
 */
#include <stdio.h>
#include <stdlib.h>
#include "graphics.h"

int main(int argc, char *argv[]) {
  View2D view;
  Matrix vtm;
  Matrix gtm;
  Module *scene;
  Module *wing;
  Module *engine;
  Module *body;
  Module *xwing;
  Module *formation;
  int i;
  Point p[8];
  Line l;
  DrawState *ds;
  Image *src;

	srand48(42);

  // setup gtm
  matrix_identity( &gtm );

  // setup vtm
  point_set2D( &(view.vrp), 0, 0 );
  vector_set( &(view.x), 1, 0, 0 );
  view.dx = 2;
  view.screenx = 640;
  view.screeny = 360;
  matrix_setView2D( &vtm, &view );
  printf("set up vtm\n");

  // create a body
  body = module_create();

  point_set2D(&p[0], 0, 0);
  point_set2D(&p[1], 2, .1);
  point_set2D(&p[2], 2.2, 0.25 );
  point_set2D(&p[3], 2, 0.4 );
  point_set2D(&p[4], 0, .5 );
  printf("set up points\n");

  for(i=0;i<5;i++) {
    int a = i;
    int b = (i+1) % 5;
    
    line_set( &l, p[a], p[b] );
    module_line( body, &l );
  }
  line_set2D( &l, 0.6, 0.05, 0.6, 0.45 );
  module_line( body, &l );
  line_set2D( &l, 1.1, 0.08, 1.1, 0.42 );
  module_line( body, &l );
  printf("created a body\n");

  // create an engine
  engine = module_create();
  
  point_set2D( &p[0], 0, 0 );
  point_set2D( &p[1], .6, 0 );
  point_set2D( &p[2], .6, .2 );
  point_set2D( &p[3], 0, .2 );

  for(i=0;i<4;i++) {
    int a = i;
    int b = (i+1) % 4;
    
    line_set( &l, p[a], p[b] );
    module_line( engine, &l );
  }
  printf("created an engine\n");

  // make a wing
  wing = module_create();

  point_set2D(&p[0], 0.5, 0);
  point_set2D(&p[1], 0.3, 1.5);
  point_set2D(&p[2], 0.7, 1.5 );
  point_set2D(&p[3], 0, 1.5 );
  point_set2D(&p[4], 0, 0 );

  for(i=0;i<5;i++) {
    int a = i;
    int b = (i+1) % 5;
    
    line_set( &l, p[a], p[b] );
    module_line( wing, &l );
  }
  module_scale2D( wing, 1.5, 1.0 );
  module_translate2D( wing, -0.05, 0.05 );
  module_module( wing, engine );
  printf("created a wing\n");

  // make an x-wing
  xwing = module_create();

  module_module(xwing, body );
  module_translate2D( xwing, 0, .5 );
  module_module( xwing, wing);
  module_identity(xwing);
  module_scale2D( xwing, 1, -1 );
  module_translate2D( xwing, 0, 0 );
  module_module( xwing, wing );
  printf("made an x-wing\n");

  // make a formation
  formation = module_create();

  module_module(formation, xwing );
  module_translate2D(formation, -4, 3 );
  module_module( formation, xwing );
  module_translate2D(formation, 0, -5 );
  module_module( formation, xwing );
  printf("made a formation\n");

  // make a scene
  scene = module_create();
  module_scale2D( scene, 0.1, 0.1 );
  module_translate2D( scene, 0.2, 0 );
  module_module( scene, formation );
  printf("made a scene\n");
  
	// draw stars into the scene
  module_identity(scene);
  for(i=0;i<30;i++) {
    point_set2D( &(p[0]), drand48()*2 - 1, drand48()*1 - 0.5 );
    module_point( scene, &(p[0]) );
  }
  printf("drew stars into scene\n");


	// create the image and draw the module
  src = image_create( view.screeny, view.screenx );
  ds = drawstate_create(); // default color is white
  module_draw( scene, &vtm, &gtm, ds, NULL, src );
  printf("created the image and drew the module\n");

	// write out the image
  image_write( src, "xwings.ppm" );
  printf("wrote out the image\n");

	// free modules
  module_delete( scene );
  printf("freed scene\n");
  module_delete( formation );
  printf("freed formation\n");
  module_delete( xwing );
  printf("freed xwing\n");
  module_delete( body );
  printf("freed body\n");
  module_delete( wing );
  printf("freed wing\n");

	// free drawstate
  free( ds );

	// free image
  image_free( src );

  return(0);
}
