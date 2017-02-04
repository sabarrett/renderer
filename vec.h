struct vec2 {
	float x;
	float y;
};

struct vec3 {
	float x;
	float y;
	float z;
};

struct point2 {
	int x;
	int y;
};

extern struct vec3 vec3forward;
extern struct vec3 vec3right;
extern struct vec3 vec3up;

struct vec2 vec2mul(struct vec2 v, float scalar);
struct vec3 vec3mul(struct vec3 v, float scalar);
float dot(struct vec3 u, struct vec3 v);
struct vec3 proj(struct vec3 u, struct vec3 v);
struct vec3 projectOnPlane(struct vec3 u, struct vec3 n);
struct vec3 subtract(struct vec3 u, struct vec3 v);
struct vec3 uToV(struct vec3 u, struct vec3 v);
float magnitude(struct vec3 u);
int max(int a, int b);
int min(int a, int b);
