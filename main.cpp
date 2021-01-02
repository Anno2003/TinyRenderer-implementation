#include "formatting.h"
#include <iostream>
#include <random>

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
			if((e<<1)<=-dx){//bitshifting e to the left by 1  
				e+=dx;y--;  //is the same as multiplying e by 2
			}
		}else{
			if((e<<1)>=dx){
				e-=dx;y++;
			}
		}
	}
}

int main(){
	TGA output("Line.tga",100,100);
	COLOR white={255,255,255,255};
	COLOR black={0,0,0,255};
	COLOR red={255,0,0,255};
	COLOR blu={0,0,255,255};
	
	
	printf("TEST");//print something to make sure it works
	
	
	//******LINE-TESTING********
	line(0 ,0 ,20,20,output,red);
	line(20,0 ,0 ,20,output,red);
	////vertical & horizontal
	line(10,0 ,10,20,output,red);//v
	line(0 ,10,20,10,output,red);//h
	////steep lines
	line(20,0 ,40,40,output,red);
	line(20,40,40,0 ,output,red);
	////swap starting coordinate
	line(20,20,0 ,0 ,output,blu);
	line(0 ,20,20,0 ,output,blu);
	line(10,20,10,0 ,output,blu);//v
	line(20,10,0 ,10,output,blu);//h
	line(40,40,20,0 ,output,blu);
	line(40,0 ,20,40,output,blu);
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