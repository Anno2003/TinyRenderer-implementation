#ifndef MESH_H
#define MESH_H
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "types.h"

using namespace std;

class Mesh{
	private:
	vector<vec3f>       verts;//vertices coordinates
	vector<vector<int>>  fidx;//index of vertices 
	
	vector<vec3f>    textures;//texture coordinates
	vector<vector<int>>  tidx;//index of  texture 
	vector<vec3f>     normals;//normals coordinates
	vector<vector<int>>  nidx;//index of  normals
	
	public:
	vector<triangle>     tris;//triangle faces
	Mesh(string Fname){
		ifstream f(Fname);	
		string line;
		while (!f.eof()){
			getline(f,line);
			istringstream iss(line.c_str());
			char junk;
			if(!line.compare(0, 2, "v ")){//extract vertices coordinates 
				vec3f v;
				iss>>junk>>v.x>>v.y>>v.z;
				verts.push_back(v);
			}
			if(!line.compare(0, 2, "f ")){//extract indexes
				vector<int> a;vector<int> b;vector <int> c;
				int v,vt,vn;
				iss>>junk;
				while(iss>>v>>junk>>vt>>junk>>vn){
					v--;vt--;vn--;
					a.push_back(v);b.push_back(vt);c.push_back(vn);
				}
				fidx.push_back(a);tidx.push_back(b);nidx.push_back(c);
				tris.push_back({verts[a[0]],verts[a[1]],verts[a[2]]});
			}
		}
	}
	int nfaces(){return (int)tris.size();}
	int nverts(){return (int)verts.size();}
	
	vec3f vert(int i){return verts[i];}
	vector<int> face(int i){return fidx[i];}

};


#endif