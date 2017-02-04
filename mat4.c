#include "mat4.h"
#include "vec.h"

#include <assert.h>

struct mat4 mat4_identity = {
	.cells = {{1, 0, 0, 0},
			  {0, 1, 0, 0},
			  {0, 0, 1, 0},
			  {0, 0, 0, 1}}
};

struct mat4 mat4mul(struct mat4 A, struct mat4 B)
{
	struct mat4 out;

	for (int r = 0; r < 4; ++r)
		for (int c = 0; c < 4; ++c)
			mat4_SetCell(&out, r, c, dot4(RowVec4(A, r), ColVec4(B, c)));

	return out;
}

float mat4_GetCell(struct mat4 A, int row, int col)
{
	return A.cells[row][col];
}

float mat4_SetCell(struct mat4* A, int row, int col, float value)
{
	return A->cells[row][col] = value;
}

struct vec4 RowVec4(struct mat4 A, int row)
{
	struct vec4 out;
	assert(row >= 0 && row <= 3);

	out.x = mat4_GetCell(A, row, 0);
	out.y = mat4_GetCell(A, row, 1);
	out.z = mat4_GetCell(A, row, 2);
	out.w = mat4_GetCell(A, row, 3);

	return out;
}

struct vec4 ColVec4(struct mat4 A, int col)
{
	struct vec4 out;
	assert(col >= 0 && col <= 3);

	out.x = mat4_GetCell(A, 0, col);
	out.y = mat4_GetCell(A, 1, col);
	out.z = mat4_GetCell(A, 2, col);
	out.w = mat4_GetCell(A, 3, col);

	return out;
}

int mat4_equal(struct mat4 A, struct mat4 B)
{
	for (int r = 0; r < 4; ++r)
		for (int c = 0; c < 4; ++c)
			if (mat4_GetCell(A, r, c) != mat4_GetCell(B, r, c))
				return 0;
	return 1;
}
