/*
 * Author: Ian Tibbetts and Astrid Moore
 * Date: 10/17/14
 *
 * The heirarchical model
 */

#include "graphics.h"

// 2D and Generic Module Function

/*
 * Allocate and return an initialized but empty Element.
 */
Element *element_create(){
	Element *e = malloc(sizeof(Element));
	if(!e){
		printf("malloc failed in element_create\n");
	}
	return e;
}

/*
 * Allocate an Element and store a duplicate of the data pointed to by 
 * obj in the Element. Modules do not get duplicated. The function needs
 * to handle each type of object separately in a case statement.
 */
Element *element_init(ObjectType type, void *obj){
	Element *e = malloc(sizeof(Element));
	if(!e){
		printf("malloc failed in element_init\n");
	}
	e->type = type;
	switch (type) {
		case ObjNone:
			printf("ObjNone not implemented in element_init\n");
			break;
		case ObjLine:
			line_copy(&(e->obj.line), (Line*)obj);
			break;
		case ObjPoint:
			point_copy(&(e->obj.point), (Point*)obj);
			break;
		case ObjPolyline:
			polyline_copy(&(e->obj.polyline), (Polyline*)obj);
			break;
		case ObjPolygon:
			polygon_copy(&(e->obj.polygon), (Polygon*)obj);
			break;
		case ObjIdentity:
		case ObjMatrix:
			matrix_copy(&(e->obj.matrix), (Matrix*)obj);
			break;
		case ObjColor:
		case ObjBodyColor:
		case ObjSurfaceColor:
			color_copy(&(e->obj.color), (Color*)obj);
			break;
		case ObjSurfaceCoeff:
			e->obj.coeff = *(float*)obj;
			break;
		case ObjLight:
			printf("ObjLight not implemented in element_init\n");
			break;
		case ObjModule:
			e->obj.module = obj;
			break;
		default:
			printf("ObjectType type is not handled in element_init\n");
	}
	return e;
}

/*
 * free the element and the object it contains, as appropriate.
 */
void element_delete(Element *e){

}

/*
 * Allocate an empty module.
 */
Module *module_create(){

	return NULL;
}

/*
 * clear the module’s list of Elements, freeing memory as appropriate.
 */
void module_clear(Module *md){

}

/*
 * Free all of the memory associated with a module, 
 * including the memory pointed to by md.
 */
void module_delete(Module *md){

}

/*
 * Generic insert of an element into the module at the tail of the list.
 */
void module_insert(Module *md, Element *e){

}

/*
 * Adds a pointer to the Module sub to the tail of the module’s list.
 */
void module_module(Module *md, Module *sub){

}

/*
 * Adds p to the tail of the module’s list.
 */
void module_point(Module *md, Point *p){

}

/*
 * Adds p to the tail of the module’s list.
 */
void module_line(Module *md, Line *p){

}

/*
 * Adds p to the tail of the module’s list.
 */
void module_polyline(Module *md, Polyline *p){

}

/*
 * Adds p to the tail of the module’s list.
 */
void module_polygon(Module *md, Polygon *p){

}

/*
 * Object that sets the current transform to the identity, 
 * placed at the tail of the module’s list.
 */
void module_identity(Module *md){

}

/*
 * Matrix operand to add a translation matrix to the tail of the module’s list.
 */
void module_translate2D(Module *md, double tx, double ty){

}

/*
 * Matrix operand to add a scale matrix to the tail of the module’s list.
 */
void module_scale2D(Module *md, double sx, double sy){

}

/*
 * Matrix operand to add a rotation about the Z axis to the tail of the module’s list
 */
void module_rotateZ(Module *md, double cth, double sth){

}

/*
 * Matrix operand to add a 2D shear matrix to the tail of the module’s lisT
 */
void module_shear2D(Module *md, double shx, double shY){

}

/*
 * Draw the module into the image using the given view transformation matrix [VTM], 
 * Lighting and DrawState by traversing the list of Elements. 
 * (For now, Lighting can be an empty structure.)
 */
void module_draw(Module *md, Matrix *VTM, Matrix *GTM, DrawState *ds, 
				Lighting *lighting, Image *src){

}

// 3D Module functions

/*
 * Matrix operand to add a 3D translation to the Module.
 */
void module_translate(Module *md, double tx, double ty, double tz){

}

/*
 * Matrix operand to add a 3D scale to the Module.
 */
void module_scale(Module *md, double sx, double sy, double sz){

}

/*
 * Matrix operand to add a rotation about the X-axis to the Module.
 */
void module_rotateX(Module *md, double cth, double sth){

}

/*
 * Matrix operand to add a rotation about the Y-axis to the Module.
 */
void module_rotateY(Module *md, double cth, double sth){

}

/*
 * Matrix operand to add a rotation that orients to the orthonormal axes u,v,w
 */
void module_rotateXYZ(Module *md, Vector *u, Vector *v, Vector *w){

}


/*
 * Adds a unit cube, axis-aligned and centered on zero to the Module. 
 * If solid is zero, add only lines. If solid is non-zero, use polygons. 
 * Make sure each polygon has surface normals defined for it.
 */
void module_cube(Module *md, int solid){

}

// Shading/Color Module Functions

/*
 * Adds the foreground color value to the tail of the module’s list
 */
void module_color(Module *md, Color *c){

}

// Draw State

/*
 * create a new DrawState structure and initialize the fields.
 */
void drawstate_create( void ){

}

/*
 * set the color field to c.
 */
void drawstate_setColor( DrawState *s, Color c ){

}

/*
 * set the body field to c.
 */
void drawstate_setBody( DrawState *s, Color c ){

}

/*
 * set the surface field to c.
 */
void drawstate_setSurface( DrawState *s, Color c ){

}

/*
 * set the surfaceCoeff field to f.
 */
void drawstate_setSurfaceCoeff( DrawState *s, float f ){

}

/*
 * copy the DrawState data.
 */
void drawstate_copy( DrawState *to, DrawState *from ){

}
