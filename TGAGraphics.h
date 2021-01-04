#ifndef TGAGRAPHIC_H
#define TGAGRAPHIC_H
#include "types.h"

COLOR red={255,0,0,255};
COLOR blu={0,0,255,255};
COLOR black={0,0,0,255};

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

void triangle(vec2i t0,vec2i t1,vec2i t2,TGA &target,COLOR &clr){
	if(t0.y>t1.y){swap(t0,t1);};
	if(t0.y>t2.y){swap(t0,t2);};
	if(t1.y>t2.y){swap(t1,t2);};
	
	line(t0.x,t0.y,t1.x,t1.y,target,black);
	line(t1.x,t1.y,t2.x,t2.y,target,black);
	line(t2.x,t2.y,t0.x,t0.y,target,blu);
}


void filledTriangle(vec2i t0,vec2i t1,vec2i t2,TGA &target,COLOR &clr){
	if(t0.y>t1.y){swap(t0,t1);};
	if(t0.y>t2.y){swap(t0,t2);};
	if(t1.y>t2.y){swap(t1,t2);};
	
	if(t0.y==t2.y){return;}//triangle has no area
	
	vec2i middle={t0.x+((t1.y-t0.y)/(t2.y-t0.y))*(t2.x-t0.x),t1.y};
	float m1=(t1.x-t0.x)/(t1.y-t0.y);
	float m2=(middle.x-t0.x)/(middle.y-t0.y);
	
	int x0=t0.x;
	int x1=t0.x;	
	for(int y=t0.y;y<=middle.y;y++){
		//int x0=t0.x+((y-t0.y)/(t2.y-t0.y))*(t2.x-t0.x); //interpolating from small to end
		//
		//int x1=(y<=t1.y)?t0.x+((t1.x-t0.x)/(t1.y-t0.y))*(y-t0.y): //interpolating from small to middle
		//				    t1.x+((t2.x-t1.x)/(t2.y-t1.y))*(y-t1.y);//interpolating for middle to bottom	
		line(x0,y,x1,y,target,clr);
		x0+=m2;
		x1+=m1;
	}
	
}

#endif