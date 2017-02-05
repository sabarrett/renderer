#define _BSD_SOURCE
#include <stdio.h>
#include <assert.h>
#include <X11/Xlib.h>
#include <unistd.h>
#include <X11/keysymdef.h>
#include <X11/Xutil.h>
#include <math.h>
#include "vec.h"
#include "test.h"
#include "transform.h"

int blackColor, whiteColor;
XImage* img;
Display* dsp;
Window wnd;
GC gc;
struct transform_t cameraTransform;
int width = 640,
	height = 480;

static int x_at_y(int x1, int y1, int x2, int y2, int y);
void graphics_prog();

struct triangle_t {
	struct vec3 p0;
	struct vec3 p1;
	struct vec3 p2;
};

struct triangle_t map_triangle_to_camera_space(struct triangle_t tri);
struct triangle_t screenspace_to_pixels(struct triangle_t tri);
struct point2 vec3_to_point2(struct vec3 vector);

int main(int argc, char* argv[])
{
	test_inv_transform();
	test_transform();
	test_mat4mul();
	test_transpose();
	cameraTransform.position = vec3mul(vec3up, 0.2);
	cameraTransform.rotation = vec3mul(vec3right, 30);
	cameraTransform.scale = vec3one;
	graphics_prog();
	return 0;
}

int x_at_y(int x1, int y1, int x2, int y2, int y)
{
	if (y1 == y2)
		return -1;
	if (x1 == x2)
		return x1;

	float m = (float)(y2 - y1) / (x2 - x1);
	float b = y1 - m * x1;
	float minv = 1/m;
	return (int)round(minv * (y - b));
}

void draw_triangle(struct point2 p1, struct point2 p2, struct point2 p3)
{
	struct point2* topPoint = &p1;
	struct point2* bottomPoint = &p1;
	struct point2* m;
	struct point2* n;

	if (p2.y < topPoint->y)
		topPoint = &p2;
	if (p3.y < topPoint->y)
		topPoint = &p3;

	if (p2.y > bottomPoint->y)
		bottomPoint = &p2;
	if (p3.y > bottomPoint->y)
		bottomPoint = &p3;

	if (&p1 == topPoint)
	{
		m = &p2;
		n = &p3;
	}
	else if (&p2 == topPoint)
	{
		m = &p1;
		n = &p3;
	}
	else if (&p3 == topPoint)
	{
		m = &p1;
		n = &p2;
	}

	int flippedN = 0;
	int flippedM = 0;

	for (int i = topPoint->y; i <= bottomPoint->y; ++i)
	{
		if (i == m->y)
		{
			flippedM = 1;
		}
		else if (i == n->y)
		{
			flippedN = 1;
		}

		int x1;
		if (flippedM)
			x1 = x_at_y(m->x, m->y, n->x, n->y, i);
		else
			x1 = x_at_y(topPoint->x, topPoint->y, m->x, m->y, i);
		int x2;
		if (flippedN)
			x2 = x_at_y(m->x, m->y, n->x, n->y, i);
		else
			x2 = x_at_y(topPoint->x, topPoint->y, n->x, n->y, i);	

		if (x1 == -1)
			x1 = m->x;
		if (x2 == -1)
			x2 = n->x;

		int maxx = max(x1, x2);
		int minx = min(x1, x2);

		for (int j = minx; j <= maxx; ++j)
		{
			XPutPixel(img, j, i, whiteColor);
		}
	}
}

void graphics_prog()
{
	int x1 = 10,
		x2 = 180;

	dsp = XOpenDisplay(NULL);
	assert(dsp);

	blackColor = BlackPixel(dsp, DefaultScreen(dsp));
	whiteColor = WhitePixel(dsp, DefaultScreen(dsp));

	wnd = XCreateSimpleWindow(dsp, DefaultRootWindow(dsp), 0, 0,
			width, height, 0, blackColor, blackColor);

	XSelectInput(dsp, wnd, StructureNotifyMask);

	XMapWindow(dsp, wnd);

	gc = XCreateGC(dsp, wnd, 0, (0));

	XSetForeground(dsp, gc, whiteColor);

	for (;;) {
		XEvent e;
		int exit = 0;
		XNextEvent(dsp, &e);

		switch (e.type)
		{
			case MapNotify:
				exit = 1;
				break;
		}

		if (exit)
			break;
	}

	{
		img = XGetImage(dsp, wnd, 0, 0, width, height, 0xFFFFFFFF, ZPixmap);
		assert(img);
		{
			struct triangle_t triangle = {
				.p0 = {0, 0.3, 1},
				.p1 = {0.5, 0.3, 1},
				.p2 = {0, 0.6, 1}
			};
			struct triangle_t cameraSpaceTriangle =
				map_triangle_to_camera_space(triangle);
			struct triangle_t pixelPositionsTriangle =
				screenspace_to_pixels(cameraSpaceTriangle);
			struct point2 p0 = vec3_to_point2(pixelPositionsTriangle.p0);
			struct point2 p1 = vec3_to_point2(pixelPositionsTriangle.p1);
			struct point2 p2 = vec3_to_point2(pixelPositionsTriangle.p2);
			draw_triangle(p0, p1, p2);
		}

		/*
		{
			struct point2 p1 = {10, 10},
						  p2 = {100, 100},
						  p3 = {15, 80};
			draw_triangle(p1, p2, p3);
			struct point2 p4 = {70, 12};
			struct point2 p5 = {70, 220};
			struct point2 p6 = {14, 80};
			draw_triangle(p5, p6, p4);
			XPutPixel(img, p4.x, p4.y, 0xFFFF0000);
			XPutPixel(img, p5.x, p5.y, 0xFFFF0000);
			XPutPixel(img, p6.x, p6.y, 0xFFFF0000);
		}
		*/

		XPutImage(dsp, wnd, gc, img, 0, 0, 0, 0, width, height);
	}

	sleep(3);

	/* Not sure this stuff does anything. I put it in just in case,
	 * but I still get an error message about unreleased windows or something.
	 */
	XDestroyWindow(dsp, wnd);

	XCloseDisplay(dsp);
}

struct triangle_t map_triangle_to_camera_space(struct triangle_t tri)
{
	// World space to camera space
	struct triangle_t out;

	out.p0 = InverseTransform(cameraTransform, tri.p0);
	out.p1 = InverseTransform(cameraTransform, tri.p1);
	out.p2 = InverseTransform(cameraTransform, tri.p2);

	return out;
}

struct triangle_t screenspace_to_pixels(struct triangle_t tri)
{
	// Camera space to 2D normalized screen space
	struct triangle_t out;

	out.p0.x = (int)(width * tri.p0.x + (width / 2));
	out.p0.y = (int)(height * tri.p0.y + (height / 2));
	out.p1.x = (int)(width * tri.p1.x + (width / 2));
	out.p1.y = (int)(height * tri.p1.y + (height / 2));
	out.p2.x = (int)(width * tri.p2.x + (width / 2));
	out.p2.y = (int)(height * tri.p2.y + (height / 2));

	return out;
}

struct point2 vec3_to_point2(struct vec3 vector)
{
	struct point2 out;

	out.x = vector.x;
	out.y = vector.y;

	return out;
}
