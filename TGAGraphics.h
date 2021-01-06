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
	if(t0.y>t1.y){swap(t0,t1);};//sort based on y axis 
	if(t0.y>t2.y){swap(t0,t2);};//so that t0 is always the smallest
	if(t1.y>t2.y){swap(t1,t2);};
	
	line(t0.x,t0.y,t1.x,t1.y,target,clr);
	line(t1.x,t1.y,t2.x,t2.y,target,clr);
	line(t2.x,t2.y,t0.x,t0.y,target,clr);
}


void filledTriangle(vec2i t0,vec2i t1,vec2i t2,TGA &target,COLOR &clr){
	if(t0.y>t1.y){swap(t0,t1);};//sort based on y axis 
	if(t0.y>t2.y){swap(t0,t2);};//so that t0 is always the smallest
	if(t1.y>t2.y){swap(t1,t2);};
	
	if(t0.y==t2.y){return;}//return because triangle has no area
	//somehow it wouldn't work(the swap would be so slow) if you loop until y<=t2.y
	for(int y=t0.y;y<t2.y;y++){
		
		int x0=t0.x+(y-t0.y)*((float)(t2.x-t0.x)/(t2.y-t0.y));  			//interpolating for the long side
		int x1=(y<t1.y)?(int)t0.x+(y-t0.y)*((float)(t1.x-t0.x)/(t1.y-t0.y))://interpolating for the first segment
					    (int)t1.x+(y-t1.y)*((float)(t2.x-t1.x)/(t2.y-t1.y));//interpolate fro the remaining segment
		
		if(x0>x1){swap(x0,x1);}
		//make sure x0 is smaller than x1 so this loop works
		for(int x=x0;x<x1;x++){
			target.setPixel(x,y,clr);
		}
		
	}
}



#endif