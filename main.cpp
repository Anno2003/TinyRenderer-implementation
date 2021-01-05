#include <iostream>
#include <random>
#include "formatting.h"
#include "mesh.h"
#include "TGAGraphics.h"

using namespace std;

Mesh *model=NULL;


int main(int argc, char** argv){
	if(argc==2){
		model=new Mesh(argv[1]);
	}
	else{
		model=new Mesh("african_head.obj");
	}
	int width=800;int height=600;
	TGA output("Flat-Shaded.tga",width,height);
	
	
	printf("TEST\n");//print something to make sure it works
	
	//******Flat-Shading-Render*****
	for(int i=0;i<model->nfaces();i++){
		vector<int> face=model->face(i);
		vec2i screen_coords[3];
		for(int j=0;j<3;j++){
			vec3f world_coords=model->vert(face[j]);
			screen_coords[j]=vec2i((world_coords.x+1.0)*width/2.0,(world_coords.y+1.0)*height/2.0);
		}
		COLOR clr={rand()%255,rand()%255,rand()%255,255};
		filledTriangle(screen_coords[0],screen_coords[1],screen_coords[2],output,clr);
	}
	
	//******Draw-FilledTriangle*****
	//vec2i t0[3] = {{100,150 }, {200, 150},  {200, 250}}; 
	//vec2i t1[3] = {{100,150 }, {200, 150},  {100,  50}}; 
	//vec2i t2[3] = {{200,  50}, {200, 150},  {100,  50}};
	//vec2i t3[3] = {{150,  50}, {150, 100},  {200, 100}};
	//
	//filledTriangle(t0[0], t0[1], t0[2],output,red);
	//filledTriangle(t1[0], t1[1], t1[2],output,red);
	//filledTriangle(t2[0], t2[1], t2[2],output,red);
	//filledTriangle(t3[0], t3[1], t3[2],output,red);
	//
	//triangle(t0[0], t0[1], t0[2],output,blu); 
	//triangle(t1[0], t1[1], t1[2],output,blu); 
	//triangle(t2[0], t2[1], t2[2],output,blu);
	//triangle(t3[0], t3[1], t3[2],output,blu);
	
	
	//********Draw-Wireframe*******
	//for(int i=0;i<model->nfaces();i++){
	//	vector<int> face=model->face(i);
	//	for(int j=0;j<3;j++){
	//		vec3f v0 = model->vert(face[j]);
	//		vec3f v1 = model->vert(face[(j+1)%3]);
	//		int x0 = (v0.x+1.0)*width/2.0; 
	//		int y0 = (v0.y+1.0)*height/2.0; 
	//		int x1 = (v1.x+1.0)*width/2.0; 
	//		int y1 = (v1.y+1.0)*height/2.0;
	//
	//		line(x0,y0,x1,y1,output,red);
	//	}	
	//}
	
	//******LINE-TESTING********
	//line(0 ,0 ,20,20,output,red);
	//line(20,0 ,0 ,20,output,red);
	////vertical & horizontal
	//line(10,0 ,10,20,output,red);//v
	//line(0 ,10,20,10,output,red);//h
	////steep lines
	//line(20,0 ,40,40,output,red);
	//line(20,40,40,0 ,output,red);
	////swap starting coordinate
	//line(20,20,0 ,0 ,output,blu);
	//line(0 ,20,20,0 ,output,blu);
	//line(10,20,10,0 ,output,blu);//v
	//line(20,10,0 ,10,output,blu);//h
	//line(40,40,20,0 ,output,blu);
	//line(40,0 ,20,40,output,blu);
	////if everything is correct all lines should be blue
	
	//******INITIAL-TESTING*****
	//for(int i=0;i<100;i++){
	//	output.setPixel(rand()%100,rand()%100,red);
	//}
	//**************************
	output.writeFile();
	printf("done!...\n");//print something to make sure it's done
	scanf(".");
	return 0;
}