#include <math.h>
#include "vec.h"

struct vec3 vec3forward  = {
	.x = 0,
	.y = 0,
	.z = 1
};

struct vec3 vec3right = {
	.x = 1,
	.y = 0,
	.z = 0
};

struct vec3 vec3up = {
	.x = 0,
	.y = 1,
	.z = 0
};

struct vec2 vec2mul(struct vec2 v, float scalar)
{
	struct vec2 out;
	out.x = v.x * scalar;
	out.y = v.y * scalar;
	return out;
}

float dot(struct vec3 u, struct vec3 v)
{
	return u.x * v.x + u.y * v.y + u.z * v.z;
}

float magnitude(struct vec3 u)
{
	return sqrt(pow(u.x, 2) + pow(u.y, 2) + pow(u.z, 2));
}

struct vec3 vec3mul(struct vec3 v, float scalar)
{
	struct vec3 out;
	out.x = v.x * scalar;
	out.y = v.y * scalar;
	out.z = v.z * scalar;

	return out;
}

struct vec3 subtract(struct vec3 u, struct vec3 v)
{
	struct vec3 out;

	out.x = u.x - v.x;
	out.y = u.y - v.y;
	out.z = u.z - v.z;

	return out;
}

struct vec3 uToV(struct vec3 u, struct vec3 v)
{
	return subtract(v, u);
}

struct vec3 projectOnPlane(struct vec3 u, struct vec3 n)
{
	return subtract(u, proj(u, n));
}

struct vec3 proj(struct vec3 u, struct vec3 v)
{
	return vec3mul(v, dot(u, v) / dot(v, v));
}

int max(int a, int b)
{
	return a > b ? a : b;
}

int min(int a, int b)
{
	return a < b ? a : b;
}
