#define GEBUG_IMPLEMENTATION
#define GEBUG_CLEAR_COLOR 0x515151FF

#include "./../../gebug.h"

#define IMG_WIDTH  400
#define IMG_HEIGHT 400

uint32_t pixels[IMG_WIDTH*IMG_HEIGHT];

int main(void)
{
    gebug_canvas gc = gebug_create_canvas(pixels, IMG_WIDTH, IMG_HEIGHT);

    gebug_clear(gc);

    gebug_circle(gc,  gc.width/2,  gc.height/2, 100, GEBUG_MAGENTA);
    gebug_circle(gc,          20,           20,  50,     GEBUG_RED);
    gebug_circle(gc,           0,  gc.height-1,  60,   GEBUG_GREEN);
    gebug_circle(gc,  gc.width-1,           20,  70,    GEBUG_BLUE);
    gebug_circle(gc, gc.width-30, gc.height-30,  80,    GEBUG_CYAN);

    gebug_save_ppm(gc, "circle.ppm");
    
    return 0;
}
