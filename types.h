#ifndef TYPE_H
#define TYPE_H

template<class t> struct vec2{
	union {
		struct {t u, v;};
		struct {t x, y;};
		t raw[2];
	};
	inline vec2<t> operator +(const vec2<t> &V) const { return vec2<t>(u+V.u, v+V.v); }
	inline vec2<t> operator -(const vec2<t> &V) const { return vec2<t>(u-V.u, v-V.v); }
	inline vec2<t> operator *(float          f) const { return vec2<t>(u*f, v*f); }
};

template<class t> struct vec3{
	union{
		struct{t x,y,z;};
		t raw[3];
	};
	inline vec3<t> operator +(const vec3<t> &v) const{return vec3<t>(x+v.x,y+v.y,z+v.z);}
	inline vec3<t> operator -(const vec3<t> &v) const{return vec3<t>(x-v.x,y-v.y,z-v.z);}
	inline vec3<t> operator *(float          f) const{return vec3<t>(x*f,y*f,z*f);}
	inline t       operator *(const vec3<t> &v) const{return vec3<t>(x*v.x,y*v.y,z*v.z);}
};

template<class t> struct vec4{
	union{
		struct{t red,green,blue,alpha;};
		t raw[4];
	};
};

typedef vec2<float> vec2f;
typedef vec2<int>   vec2i;
typedef vec3<float> vec3f;
typedef vec3<int>   vec3i;
typedef vec4<unsigned char> COLOR;

struct triangle{vec3f p[3];};


#endif