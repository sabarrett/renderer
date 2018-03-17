#include "vec.h"
#include "mat4.h"

struct transform_t {
	vec3 position;
	vec3 rotation;
	vec3 scale;
};

vec3 Transform(struct transform_t transform, vec3 point);
vec3 InverseTransform(struct transform_t transform, vec3 point);
vec3 Transform_Forward(struct transform_t transform);
vec3 Transform_Right(struct transform_t transform);
struct mat4 Transform_GetMatrix(struct transform_t transform);
struct mat4 Transform_GetInvMatrix(struct transform_t transform);
struct mat4 Transform_Translate(struct transform_t transform, vec3 movement);
