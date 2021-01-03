#include "formatting.h"
#include "mesh.h"
#include <iostream>
#include <random>
using namespace std;

COLOR red={255,0,0,255};
COLOR blu={0,0,255,255};
Mesh *model=NULL;

void line(int x1,int y1,int x2,int y2,TGA &target,COLOR &clr){
	bool steep=false;	
	if(std::abs(x2-x1)<std::abs(y2-y1)){
		std::swap(x1,y1);
		std::swap(x2,y2);
		steep=true;
		}
	if(x1>x2){
		std::swap(x1,x2);
		std::swap(y1,y2);
		}
	
	int dx=x2-x1;
	int dy=y2-y1;
	int e=0;
	int y=y1;
	
	for(int x=x1;x<=x2;x++){
		if(steep){
			target.setPixel(y,x,clr);
		}else{
			target.setPixel(x,y,clr);
		}
		e+=dy;
		if(y1>y2){
			if((e<<1)<=-dx){//bitshift to the left once 
				e+=dx;y--;  //is the same as multiplying by 2
			}
		}else{
			if((e<<1)>=dx){
				e-=dx;y++;
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
	int width=800;int height=600;
	TGA output("Wireframe.tga",width,height);
	
	
	printf("TEST\n");//print something to make sure it works
	
	//********Draw-Wireframe*******
	for(int i=0;i<model->nfaces();i++){
		vector<int> face=model->face(i);
		for(int j=0;j<3;j++){
			vec3f v0 = model->vert(face[j]);
			vec3f v1 = model->vert(face[(j+1)%3]);
			int x0 = (v0.x+1.0)*width/2.0; 
			int y0 = (v0.y+1.0)*height/2.0; 
			int x1 = (v1.x+1.0)*width/2.0; 
			int y1 = (v1.y+1.0)*height/2.0;
	
			line(x0,y0,x1,y1,output,red);
		}	
	}
	
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
	scanf(".");
	return 0;
}