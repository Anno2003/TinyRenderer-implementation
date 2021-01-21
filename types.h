#ifndef TYPE_H
#define TYPE_H

#include <cassert>

template<class t> struct vec2;
template<class t> struct vec3;
template<class t> struct vec4;
template<class t> struct mat3;
template<class t> struct mat4;

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
	inline vec3<t> operator *(const mat4<t> &v) const{return vec3<t>(x*v[0][0] + y*v[1][0] + z*v[2][0] + v[3][0],
																	 x*v[0][1] + y*v[1][1] + z*v[2][1] + v[3][1],
																	 x*v[0][2] + y*v[1][2] + z*v[2][2] + v[3][2]);}
	
		  t& operator [](const size_t i)      {assert(i<3);return raw[i];}
	const t& operator [](const size_t i)const {assert(i<3);return raw[i];}
	
	float norm () const {return sqrt(x*x+y*y+z*z);}
	vec3<t> &normalize(t l=1){*this=(*this)*(1/norm());return *this;}
};

template<class t> struct vec4{
	union{
		struct{t red,green,blue,alpha;};
		t raw[4];
	};
	vec4():red(0),green(0),blue(0),alpha(0){}
	vec4(t _r,t _g,t _b,t _a):red(_r),green(_g),blue(_b),alpha(_a){}
	
		  t& operator [](const size_t i)      {assert(i<4);return raw[i];}
	const t& operator [](const size_t i)const {assert(i<4);return raw[i];}
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

template<class t> struct mat4{
	vec4<t> p[4];
		  vec4<t>& operator[](const size_t i)     {assert(i<4);return p[i];}
	const vec4<t>& operator[](const size_t i)const{assert(i<4);return p[i];}
	
	
};


typedef vec2<float> vec2f;
typedef vec2<int>   vec2i;
typedef vec3<float> vec3f;
typedef vec3<int>   vec3i;
typedef vec4<unsigned char> COLOR;
typedef mat3<float> triangle;



#endif