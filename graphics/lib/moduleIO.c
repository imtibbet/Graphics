// These functions read and write text files defining modules for graphics heirarchies
// Ian Tibbetts and Astrid Moore
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graphics.h"

// read in rgb values from the ppm file output by cqcam
int genModule(char *infilename, char *outfilename) {
	FILE *infile, *outfile;
	char buf[1000];
	char *codeline, *firstword;
	int i, moduleID = 0;

	// open input file for reading
	infile =fopen(infilename,"r");
	if (!infile){
		printf("%s did not open for reading properly\n",infilename);
		return 0;
	}

	// open ouput file for writing
	outfile =fopen(outfilename,"w");
	if (!outfile){
		printf("%s did not open for writing properly\n",outfilename);
		fclose(infile);
		return 0;
	}

	fprintf(outfile, "%s", 	"#include 'graphics.h'\n"
							"int main(int argc, char *argv[]) {\n"
							"\tLine l;\n"
							"\tPoint pt;\n"
							"\tPolyline *pl = polyline_create();\n"
							"\tPolygon *pg = polygon_create();\n"
							"\tMatrix m;\n\n");

	// loop until EOF is reached
	while (fgets(buf,1000, infile)!=NULL){
		printf("%s\n", buf);
		firstword = strtok (buf,"()");
		if(strcmp(buf, "begin module") == 0){
			sprintf(codeline, "Module *mod%d = module_create();", moduleID++);
		} else if(strcmp(firstword, "line2D") == 0){
			firstword = strtok (NULL, "()");
			sprintf(codeline, "line_set2D(&l, %s);\nmodule_line(mod%d, &l);", firstword, moduleID);
		} else {
			printf("%s isn't a recognized line for genModule\n", buf);
			codeline = "NOT RECOGNIZED"
		}
		fprintf(outfile, "%s\n", codeline);
	}
	for(i=0;i<moduleID;i++){
		sprintf(codeline, "mod%d = module_clear()", moduleID);
	}

	fclose(infile);
	fclose(outfile);
	return 1;
}
