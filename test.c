#include <assert.h>
#include "vec.h"
#include "mat4.h"
#include "transform.h"
# define M_PI		3.14159265358979323846	/* pi */
# define M_PI_2		1.57079632679489661923	/* pi/2 */
# define M_PI_4		0.78539816339744830962	/* pi/4 */

void test_projectOnPlane()
{
	assert(vec3_equal(projectOnPlane(vec3_add(vec3_right, vec3_up), vec3_right), vec3_right));
}

void test_mat4mul()
{
	assert(mat4_equal(mat4mul(mat4_identity, mat4_identity), mat4_identity));
}

void test_transpose()
{
	assert(mat4_equal(mat4_Transpose(mat4_identity), mat4_identity));
}

void test_transform()
{
	{
		struct transform_t t;

		t.position = vec3_forward;
		t.rotation = vec3_zero;
		t.scale = vec3_one;

		assert(vec3_equal(Transform(t, vec3_zero), vec3_forward));
	}

	{
		struct transform_t t;

		t.position = vec3_zero;
		t.rotation = vec3_zero;
		t.scale = vec3_mul(vec3_one, 2);

		assert(vec3_equal(Transform(t, vec3_forward), vec3_mul(vec3_forward, 2)));
	}

	{
		struct transform_t t;

		t.position = vec3_zero;
		t.rotation = vec3_mul(vec3_forward, 90);
		t.scale = vec3_one;

		assert(vec3_angle(Transform(t, vec3_up), vec3_right) < 0.1f);
	}
}

void test_inv_transform()
{
	{
		struct transform_t t;

		t.position = vec3_forward;
		t.rotation = vec3_zero;
		t.scale = vec3_one;

		assert(vec3_equal(InverseTransform(t, vec3_forward), vec3_zero));
	}

	{
		struct transform_t t;

		t.position = vec3_zero;
		t.rotation = vec3_zero;
		t.scale = vec3_mul(vec3_one, 2);

		assert(vec3_equal(InverseTransform(t, vec3_mul(vec3_forward, 2)), vec3_forward));
	}

	{
		struct transform_t t;

		t.position = vec3_zero;
		t.rotation = vec3_mul(vec3_forward, 90);
		t.scale = vec3_one;

		assert(vec3_angle(InverseTransform(t, vec3_right), vec3_up) < 0.1f);
	}
}
