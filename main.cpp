#include <iostream>
#include <random>
#include "formatting.h"
#include "mesh.h"
#include "TGAGraphics.h"

using namespace std;


Mesh *model=NULL;
const int width=800;const int height=800;


void rasterize(TGA& tga,float *zbuffer,Mesh *model,vec3f light){		
	for(triangle pts:model->tris){
		vec3f normal=(pts[2]-pts[0])^(pts[1]-pts[0]);
		normal.normalize();
		float intensity=normal*light;
		COLOR clr(intensity*255,intensity*255,intensity*255,255);
		//change to screen coords
		pts[0]=vec3f(int( (pts[0].x+1.0)*width/2.0) ,int( (pts[0].y+1.0)*height/2.0) , pts[0].z);
		pts[1]=vec3f(int( (pts[1].x+1.0)*width/2.0) ,int( (pts[1].y+1.0)*height/2.0) , pts[1].z);
		pts[2]=vec3f(int( (pts[2].x+1.0)*width/2.0) ,int( (pts[2].y+1.0)*height/2.0) , pts[2].z);
		///////////////////////////
		vec3f t0=pts[0];
		vec3f t1=pts[1];
		vec3f t2=pts[2];
		
		if(t0.y>t1.y){swap(t0,t1);};
		if(t0.y>t2.y){swap(t0,t2);};
		if(t1.y>t2.y){swap(t1,t2);};

		
		for(int y=t0.y;y<t2.y;y++){
			int x0=t0.x+(y-t0.y)*((float)(t2.x-t0.x)/(t2.y-t0.y));  			//interpolating for the long side
			int x1=(y<t1.y)?(int)t0.x+(y-t0.y)*((float)(t1.x-t0.x)/(t1.y-t0.y))://interpolating for the first segment
							(int)t1.x+(y-t1.y)*((float)(t2.x-t1.x)/(t2.y-t1.y));//interpolate fro the remaining segment
			if(x0>x1){swap(x0,x1);}
			for(int x=x0;x<=x1;x++){
				
				vec3f bc_screen = pts.Barycentric(vec2f(x,y));
				float z=0;
				for(int i=0;i<3;i++){z+=pts[i][2]*bc_screen[i];}
				int idx=x+y*height;
				if(zbuffer[idx]<z){
					zbuffer[idx]=z;
					tga.setPixel(x,y,clr);
				}
			}
		}
	}
}

int main(int argc, char** argv){
	if(argc==2){
		model=new Mesh(argv[1]);
	}
	else{
		model=new Mesh("african_head.obj");
	}
	
	TGA output("z-buffer.tga",width,height);
	
	
	printf("RENDERING\n");//print something to make sure it works
	
	//******Flat-Shading-Render*****
	//with some illumination
	float *zbuffer=new float[width*height];
	
	for(int i=width*height;i--;zbuffer[i]=-numeric_limits<float>::max());
	
	vec3f light_dir(0,0,-1);
	
	rasterize(output,zbuffer,model,light_dir);
	//TODO:move this whole commented tests into a header file and use preprocessor to access tests
	//for(triangle pts:model->tris){
	//	COLOR clr(rand()%255,rand()%255,rand()%255,255);
	//	//change to screen coords
	//	pts[0]=vec3f(int( (pts[0].x+1.0)*width/2.0+5.0) ,int( (pts[0].y+1.0)*height/2.0+5.0) , pts[0].z);
	//	pts[1]=vec3f(int( (pts[1].x+1.0)*width/2.0+5.0) ,int( (pts[1].y+1.0)*height/2.0+5.0) , pts[1].z);
	//	pts[2]=vec3f(int( (pts[2].x+1.0)*width/2.0+5.0) ,int( (pts[2].y+1.0)*height/2.0+5.0) , pts[2].z);
	//	///////////////////////////
	//	vec3f t0=pts[0];
	//	vec3f t1=pts[1];
	//	vec3f t2=pts[2];
	//	
	//	if(t0.y>t1.y){swap(t0,t1);};
	//	if(t0.y>t2.y){swap(t0,t2);};
	//	if(t1.y>t2.y){swap(t1,t2);};
	//	
	//	
	//	for(int y=t0.y;y<t2.y;y++){
	//		int x0=t0.x+(y-t0.y)*((float)(t2.x-t0.x)/(t2.y-t0.y));  			//interpolating for the long side
	//		int x1=(y<t1.y)?(int)t0.x+(y-t0.y)*((float)(t1.x-t0.x)/(t1.y-t0.y))://interpolating for the first segment
	//						(int)t1.x+(y-t1.y)*((float)(t2.x-t1.x)/(t2.y-t1.y));//interpolate fro the remaining segment
	//		if(x0>x1){swap(x0,x1);}
	//		for(int x=x0;x<x1;x++){
	//			vec3f bc_screen = pts.Barycentric(vec2f(x,y));
	//			
	//			output.setPixel(x,y,clr);
	//
	//		}
	//	}
	//}
	
	//for(int i=0;i<model->nfaces();i++){
	//	vector<int> face=model->face(i);
	//	vec2i screen_coords[3];
	//	vec3f world_coords[3];
	//	for(int j=0;j<3;j++){
	//		vec3f v=model->vert(face[j]);//get coords from index
	//		screen_coords[j]=vec2i((v.x+1.0)*width/2.0,(v.y+1.0)*height/2.0);
	//		world_coords[j] =v;
	//	}
	//	vec3f normal=(world_coords[2]-world_coords[0])^(world_coords[1]-world_coords[0]);
	//	normal.normalize();
	//	float intensity=normal*light_dir;
	//	if (intensity>0){
	//		COLOR clr(intensity*255,intensity*255,intensity*255,255);
	//		filledTriangle(screen_coords[0],screen_coords[1],screen_coords[2],output,clr);
	//	}
	//	
	//}
	//rainbow colored
	//for(int i=0;i<model->nfaces();i++){
	//	vector<int> face=model->face(i);
	//	vec2i screen_coords[3];
	//	for(int j=0;j<3;j++){
	//		vec3f world_coords=model->vert(face[j]);
	//		screen_coords[j]=vec2i((world_coords.x+1.0)*width/2.0,(world_coords.y+1.0)*height/2.0);
	//	}
	//	COLOR clr={rand()%255,rand()%255,rand()%255,255};
	//	filledTriangle(screen_coords[0],screen_coords[1],screen_coords[2],output,clr);
	//}
	
	//******Draw-FilledTriangle*****
	//vec2i t0[3] = {{100,150 }, {200, 150},  {200, 250}}; 
	//vec2i t1[3] = {{100,150 }, {200, 150},  {100,  50}}; 
	//vec2i t2[3] = {{200,  50}, {200, 150},  {100,  50}};
	//vec2i t3[3] = {{150,  50}, {150, 100},  {200, 100}};
	
	//vec2i t0[3] ={vec2i(10, 70),   vec2i(50, 160),  vec2i(70, 80)}; 
	//vec2i t1[3] ={vec2i(180, 50),  vec2i(150, 1),   vec2i(70, 180)}; 
	//vec2i t2[3] ={vec2i(180, 150), vec2i(120, 160), vec2i(130, 180)};
	//vec2i t3[3] ={vec2i(180, 150), vec2i(120, 160), vec2i(130, 180)};
	
	//filledTriangle(t0[0], t0[1], t0[2],output,red);
	//filledTriangle(t1[0], t1[1], t1[2],output,black);
	//filledTriangle(t2[0], t2[1], t2[2],output,red);
	//filledTriangle(t3[0], t3[1], t3[2],output,black);
	//
	//triangle(t0[0], t0[1], t0[2],output,blu); 
	//triangle(t1[0], t1[1], t1[2],output,blu); 
	//triangle(t2[0], t2[1], t2[2],output,blu);
	//triangle(t3[0], t3[1], t3[2],output,blu);
	
	
	//********Draw-Wireframe*******
	//int *zbuffer=new int[width*height];
	//for(int i=0;i<model->nfaces();i++){
	//	vector<int> face=model->face(i);
	//	for(int j=0;j<3;j++){
	//		vec3f v0 = model->vert(face[j]);
	//		vec3f v1 = model->vert(face[(j+1)%3]);
	//		
	//		int x0 = (v0.x+1.0)*width/2.0; 
	//		int y0 = (v0.y+1.0)*height/2.0; 
	//		int x1 = (v1.x+1.0)*width/2.0; 
	//		int y1 = (v1.y+1.0)*height/2.0;
	//
	//		line(x0, y0, x1, y1, output, red);
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
