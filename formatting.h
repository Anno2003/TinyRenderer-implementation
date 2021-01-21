#ifndef FORMATTING_H
#define FORMATTING_H

#include <fstream>
#include <string>
#include "types.h"
#include "mesh.h"
using namespace std;


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
		
		void rasterize(float *zbuffer,Mesh* model){		
			for(triangle pts:model->tris){
				COLOR clr(rand()%255,rand()%255,rand()%255,255);
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
						int idx=x+y*height;//printf("[%d,%d]%d\n",x,y,idx);//apparently the index is out of bounds of array
						if(zbuffer[idx]<z){//TODO accessing zbuffer crashes program
							zbuffer[idx]=z;
							this->setPixel(x,y,clr);
						}
					}
				}
			}
		}
};

#endif