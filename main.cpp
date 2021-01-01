#include "formatting.h"
#include <iostream>
#include <random>
int main(){
	TGA output("test1.tga",100,100);
	COLOR red={255,0,0,255};
	
	printf("TEST");//print something to make sure it works
	for(int i=0;i<100;i++){
		output.setPixel(rand()%100,rand()%100,red);
	}
	output.writeFile();
	scanf(".");
	return 0;
}