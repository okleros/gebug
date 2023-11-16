#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

#ifndef GEBUG_H
#define GEBUG_H

#define GEBUG_RED      0xFF0000FF
#define GEBUG_GREEN    0x00FF00FF
#define GEBUG_BLUE     0x0000FFFF
#define GEBUG_CYAN     0x00FFFFFF
#define GEBUG_MAGENTA  0xFF00FFFF
#define GEBUG_YELLOW   0xFFFF00FF
#define GEBUG_BLACK    0x000000FF
#define GEBUG_WHITE    0xFFFFFFFF
#define GEBUG_GREY     0x181818FF

typedef struct {
    uint32_t *pixels;
    size_t width;
    size_t height;
} gebug_canvas;

typedef uint32_t gebug_color;

gebug_canvas gebug_create_canvas(uint32_t *pixels, size_t width, size_t height);

void gebug_rectangle(gebug_canvas gc,
		     size_t x1, size_t y1,
		     size_t x2, size_t y2,
		     gebug_color color);

void gebug_fill(gebug_canvas gc, gebug_color color);

void gebug_circle(gebug_canvas gc, size_t cx, size_t cy, gebug_color color);

void gebug_triangle(gebug_canvas gc,
		    size_t x1, size_t y1,
		    size_t x2, size_t y2,
		    size_t x3, size_t y3,
		    gebug_color color);

bool gebug_save_ppm(gebug_canvas gc, const char *file_path);

#endif // GEBUG_H

#ifdef GEBUG_IMPLEMENTATION

#define GEBUG_PIXEL(gc, x, y) (gc).pixels[(y) * (gc).width + (x)]

gebug_canvas gebug_create_canvas(uint32_t *pixels, size_t width, size_t height)
{
    gebug_canvas gc = {
	.pixels = pixels,
	.width = width,
	.height = height
    };

    return gc;
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

void gebug_circle(gebug_canvas gc, size_t cx, size_t cy, gebug_color color)
{
    // TODO
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

    return 1;
}

#endif // GEBUG_IMPLEMENTATION
