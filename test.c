#include <assert.h>
#include "vec.h"
#include "mat4.h"

void test_projectOnPlane()
{
	struct vec3 u = {
		.x = 1,
		.y = 1,
		.z = 0
	};
	struct vec3 onXZ = projectOnPlane(u, vec3right);
	assert(onXZ.x == 0 && onXZ.y == 1 && onXZ.z == 0);
}

void test_mat4mul()
{
	assert(mat4_equal(mat4mul(mat4_identity, mat4_identity), mat4_identity));
}
