#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include <math.h>

#ifndef GEBUG_H
#define GEBUG_H

typedef uint32_t gebug_color;

#define GEBUG_RED      0xFF0000FF
#define GEBUG_GREEN    0x00FF00FF
#define GEBUG_BLUE     0x0000FFFF
#define GEBUG_CYAN     0x00FFFFFF
#define GEBUG_MAGENTA  0xFF00FFFF
#define GEBUG_YELLOW   0xFFFF00FF
#define GEBUG_BLACK    0x000000FF
#define GEBUG_WHITE    0xFFFFFFFF
#define GEBUG_GREY     0x181818FF

#ifndef GEBUG_CLEAR_COLOR
#define GEBUG_CLEAR_COLOR GEBUG_GREY
#endif // GEBUG_CLEAR_COLOR

typedef struct {
    uint32_t *pixels;
    size_t width;
    size_t height;
} gebug_canvas;

gebug_canvas gebug_create_canvas(uint32_t *pixels, size_t width, size_t height);

void gebug_clear(gebug_canvas gc);

void gebug_rectangle(gebug_canvas gc,
		     size_t x1, size_t y1,
		     size_t x2, size_t y2,
		     gebug_color color);

void gebug_fill(gebug_canvas gc, gebug_color color);

void gebug_circle(gebug_canvas gc, int cx, int cy, size_t r, gebug_color color);

void gebug_triangle(gebug_canvas gc,
		    size_t x1, size_t y1,
		    size_t x2, size_t y2,
		    size_t x3, size_t y3,
		    gebug_color color);

bool gebug_save_ppm(gebug_canvas gc, const char *file_path);

#endif // GEBUG_H

#ifdef GEBUG_IMPLEMENTATION

#define GEBUG_PIXEL(gc, x, y) (gc).pixels[(y) * (gc).width + (x)]
#define GEBUG_DISTANCE(x1, y1, x2, y2) sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1))

gebug_canvas gebug_create_canvas(uint32_t *pixels, size_t width, size_t height)
{
    gebug_canvas gc = {
	.pixels = pixels,
	.width = width,
	.height = height
    };

    return gc;
}

void gebug_clear(gebug_canvas gc)
{
    for (size_t x = 0; x < gc.width; ++x) {
	for (size_t y = 0; y < gc.height; ++y) {
	    GEBUG_PIXEL(gc, x, y) = GEBUG_CLEAR_COLOR;
	}
    }    
}

void gebug_rectangle(gebug_canvas gc, size_t x1, size_t y1, size_t x2, size_t y2, gebug_color color)
{
    assert(x1 < x2);
    assert(y1 < y2);
    
    assert(x1 < gc.width);
    assert(x2 < gc.width);

    assert(y1 < gc.height);
    assert(y2 < gc.height);
    
    for (size_t x = x1; x <= x2; ++x) {
	for (size_t y = y1; y <= y2; ++y) {
	    GEBUG_PIXEL(gc, x, y) = color;
	}
    }
}

void gebug_fill(gebug_canvas gc, gebug_color color)
{
    for (size_t x = 0; x < gc.width; ++x) {
	for (size_t y = 0; y < gc.height; ++y) {
	    GEBUG_PIXEL(gc, x, y) = color;
	}
    }
}

void gebug_circle(gebug_canvas gc, int cx, int cy, size_t r, gebug_color color)
{
    // This creates a square bounding box around the
    // circle so you don't have to iterate through
    // the whole pixel array 
    size_t bbx1 = fmax(cx-r, 0);
    size_t bby1 = fmax(cy-r, 0);
    size_t bbx2 = fmin(cx+r, gc.width);
    size_t bby2 = fmin(cy+r, gc.height);

    for (size_t x = bbx1; x < bbx2; ++x) {
	for (size_t y = bby1; y < bby2; ++y) {
	    if (GEBUG_DISTANCE(cx, cy, x, y) <= r)
		GEBUG_PIXEL(gc, x, y) = color;
	}
    }
}

void gebug_triangle(gebug_canvas gc, size_t x1, size_t y1, size_t x2, size_t y2, size_t x3, size_t y3, gebug_color color)
{
    // TODO
}

bool gebug_save_ppm(gebug_canvas gc, const char *file_path)
{
    FILE *f = fopen(file_path, "wb");

    if (!f) return 0;
    
    fprintf(f, "P6\n%zu\n%zu\n255\n", gc.width, gc.height);
    
    for (size_t x = 0; x < gc.width; ++x) {
		for (size_t y = 0; y < gc.height; ++y) {
		    gebug_color cor = GEBUG_PIXEL(gc, x, y);
		    fputc((cor >> 24 & 0xFF), f);
		    fputc((cor >> 16 & 0xFF), f);
		    fputc((cor >>  8 & 0xFF), f);
		}
    }

    fclose(f);
    
    return 1;
}

#endif // GEBUG_IMPLEMENTATION
