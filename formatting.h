#ifndef FORMATTING_H
#define FORMATTING_H

#include <fstream>
#include <string>
using namespace std;

typedef struct{
	unsigned char red,green,blue,alpha;
}COLOR;

class TGA{
	private:
	const char *filename;
	int width,height;
	unsigned char header[18]={0};
	COLOR *data;
	public:
		TGA(const char *fname,unsigned w,unsigned h):width(w),height(h){
			filename=fname;
			
			header[2 ]=2;               //image type
			header[12]=w  & 0x00FF;     //width low order byte
			header[13]=(w & 0xFF00)/256;//width high order byte
			header[14]=h  & 0x00FF;     //height low order byte
			header[15]=(h & 0xFF00)/256;//height high order byte
			header[16]=32;              //bits per pixel
			
			data=new COLOR[w*h];
			for(int i=0;i<width*height;i++){
				data[i].red=0;
				data[i].green=0;
				data[i].blue=0;
				data[i].alpha=0;
			}
		}
		~TGA(){
			delete[] data;
		}
		void writeFile(){
			ofstream f(filename,ios::binary);
			f.write((const char*)&header,18);
			for(int i=0;i<width*height;i++){
				f.put(data[i].blue);
				f.put(data[i].green);
				f.put(data[i].red);
				f.put(data[i].alpha);
			}
			
			f.close();
		}
		void setPixel(int x,int y,COLOR clr){
			if(x<0||y<0||x>=width||y>=height){return;}
			
			else{
				data[(y * width) + x]=clr;
			}
		}
		void loadFile();
};

#endif