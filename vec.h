#ifndef VEC_H
#define VEC_H

struct vec2 {
	float x;
	float y;
};

typedef struct vec3 {
	float x;
	float y;
	float z;
} vec3;

typedef struct vec4 {
	float x;
	float y;
	float z;
	float w;
} vec4;

struct point2 {
	int x;
	int y;
};

extern struct vec3 vec3_forward;
extern struct vec3 vec3_right;
extern struct vec3 vec3_up;
extern struct vec3 vec3_zero;
extern struct vec3 vec3_one;

struct vec2 vec2_mul(struct vec2 v, float scalar);

int vec3_equal(struct vec3 u, struct vec3 v);
struct vec3 vec3_add(struct vec3 u, struct vec3 v);
struct vec3 vec3_mul(struct vec3 v, float scalar);
float dot3(struct vec3 u, struct vec3 v);
float vec3_angle(struct vec3 u, struct vec3 v);
struct vec3 vec3_normalized(struct vec3 u);
struct vec3 proj(struct vec3 u, struct vec3 v);
struct vec3 projectOnPlane(struct vec3 u, struct vec3 n);
struct vec3 vec3_minus(struct vec3 u, struct vec3 v);
struct vec3 vec3_uToV(struct vec3 u, struct vec3 v);
float vec3_magnitude(struct vec3 u);

float dot4(struct vec4 u, struct vec4 v);

int max(int a, int b);
int min(int a, int b);

#endif
