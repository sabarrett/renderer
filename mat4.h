#ifndef MAT4_H
#define MAT4_H

#include "vec.h"

struct mat4 {
	float cells[4][4];
};

extern struct mat4 mat4_identity;

struct mat4 mat4mul(struct mat4 A, struct mat4 B);
vec4 mat4_transform(struct mat4 A, vec4 x);
struct mat4 mat4_SetCell(struct mat4 A, int row, int col, float value);
float mat4_GetCell(struct mat4 A, int row, int col);
struct vec4 RowVec4(struct mat4 A, int row);
struct vec4 ColVec4(struct mat4 A, int row);
int mat4_equal(struct mat4 A, struct mat4 B);
struct mat4 mat4_Transpose(struct mat4 A);

#endif
