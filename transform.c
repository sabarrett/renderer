#include "transform.h"

#include <math.h>
#include <assert.h>

static struct mat4 translationMat(vec3 movement)
{
	struct mat4 out = mat4_identity;

	out = mat4_SetCell(out, 0, 3, movement.x);
	out = mat4_SetCell(out, 1, 3, movement.y);
	out = mat4_SetCell(out, 2, 3, movement.z);

	return out;
}

static struct mat4 rotationMat(vec3 rotation)
{
	struct mat4 out = mat4_identity;
	float x = rotation.x,
		  y = rotation.y,
		  z = rotation.z;

	// Set X
	{
		out = mat4_SetCell(out, 1, 1, cos(x));
		out = mat4_SetCell(out, 1, 2, sin(x));
		out = mat4_SetCell(out, 2, 1, -sin(x));
		out = mat4_SetCell(out, 2, 2, cos(x));
	}

	// Set Y
	{
		out = mat4_SetCell(out, 0, 0, cos(y));
		out = mat4_SetCell(out, 0, 2, -sin(y));
		out = mat4_SetCell(out, 2, 0, sin(y));
		out = mat4_SetCell(out, 2, 2, cos(y));
	}

	// Set Z
	{
		out = mat4_SetCell(out, 0, 0, cos(z));
		out = mat4_SetCell(out, 0, 1, sin(z));
		out = mat4_SetCell(out, 1, 0, -sin(z));
		out = mat4_SetCell(out, 1, 1, cos(z));
	}

	return out;
}

static struct mat4 scaleMat(vec3 scale)
{
	struct mat4 out = mat4_identity;

	out = mat4_SetCell(out, 0, 0, scale.x);
	out = mat4_SetCell(out, 1, 1, scale.y);
	out = mat4_SetCell(out, 2, 2, scale.z);

	return out;
}

vec3 Transform(struct transform_t transform, vec3 point)
{
	// Stub
	struct mat4 transformMat = Transform_GetMatrix(transform);
	vec4 tempPoint = {
		.x = point.x,
        .y = point.y,
        .z = point.z,
		.w = 1
	};
	vec4 transformed = mat4_transform(transformMat, tempPoint);
	vec3 out = {
		.x = transformed.x,
		.y = transformed.y,
		.z = transformed.z
	};

	assert(transformed.w == 1);

	return out;
}

vec3 InverseTransform(struct transform_t transform, vec3 point)
{
	// Stub
	return vec3up;
}

struct mat4 Transform_GetMatrix(struct transform_t transform)
{
	return mat4mul(mat4mul(mat4mul(mat4_identity, translationMat(transform.position)), rotationMat(transform.rotation)), scaleMat(transform.scale));
}
