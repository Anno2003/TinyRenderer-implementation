#ifndef TYPE_H
#define TYPE_H
//sorry  this place is messy, i think i kinda overengineered it a bit
//i'll clean it up in the future
#include <cassert>

template<class t> struct vec2;
template<class t> struct vec3;
template<class t> struct mat3;

template<class t> struct vec2{
	union {
		struct {t u, v;};
		struct {t x, y;};
		t raw[2];
	};
	vec2() : u(0), v(0) {}
	vec2(t _u, t _v) : u(_u),v(_v) {}
	inline vec2<t> operator +(const vec2<t> &V) const { return vec2<t>(u+V.u, v+V.v); }
	inline vec2<t> operator -(const vec2<t> &V) const { return vec2<t>(u-V.u, v-V.v); }
	inline vec2<t> operator *(float          f) const { return vec2<t>(u*f, v*f); }
};

template<class t> struct vec3{
	union{
		struct{t x,y,z;};
		struct{t a,b,c;};
		t raw[3];
	};
	vec3() : x(0), y(0), z(0) {}
	vec3(t _x, t _y,t _z) : x(_x),y(_y),z(_z) {}
	inline vec3<t> operator ^(const vec3<t> &v) const{return vec3<t>(y*v.z-z*v.y,z*v.x-x*v.z,x*v.y-y*v.x);}
	inline vec3<t> operator +(const vec3<t> &v) const{return vec3<t>(x+v.x,y+v.y,z+v.z);}
	inline vec3<t> operator -(const vec3<t> &v) const{return vec3<t>(x-v.x,y-v.y,z-v.z);}
	inline vec3<t> operator *(float          f) const{return vec3<t>(x*f,y*f,z*f);}
	inline t       operator *(const vec3<t> &v) const{return         x*v.x+y*v.y+z*v.z;}
	
		  t& operator [](const size_t i)      {assert(i<3);return raw[i];}
	const t& operator [](const size_t i)const {assert(i<3);return raw[i];}
	
	float norm () const {return sqrt(x*x+y*y+z*z);}
	vec3<t> &normalize(t l=1){*this=(*this)*(1/norm());return *this;}
};

template<class t> struct mat3{
	union{
		struct{vec3<t> a,b,c;};
		vec3<t> p[3];
	};

		  vec3<t>& operator[](const size_t i)     {assert(i<3);return p[i];}
	const vec3<t>& operator[](const size_t i)const{assert(i<3);return p[i];}
	
	inline vec3<t> Barycentric(vec2<t> vec) const{
		vec3<t> lambda;
		
		t det    = 1/((b.y - c.y)*(a.x - c.x)+(c.x - b.x)*(a.y - c.y));
		lambda.x = ((b.y - c.y)*(vec.x - c.x)+(c.x - b.x)*(vec.y - c.y)) * det;
		lambda.y = ((c.y - a.y)*(vec.x - c.x)+(a.x - c.x)*(vec.y - c.y)) * det;
		lambda.z = 1 - lambda.x - lambda.y;
		
		return lambda;
	}

};


typedef vec2<float> vec2f;
typedef vec2<int>   vec2i;
typedef vec3<float> vec3f;
typedef vec3<int>   vec3i;
typedef mat3<float> triangle;



#endif
