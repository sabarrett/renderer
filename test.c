#include <assert.h>
#include "vec.h"

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
