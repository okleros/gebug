#define GEBUG_IMPLEMENTATION
#include "../gebug.h"

#define IMG_WIDTH 400
#define IMG_HEIGHT 400

uint32_t pixels[IMG_WIDTH*IMG_HEIGHT];

int main(void)
{
    gebug_canvas gc = gebug_create_canvas(pixels, IMG_WIDTH, IMG_HEIGHT);

    gebug_fill(gc, GEBUG_GREY);

    gebug_rectangle(gc, 0, 0, gc.width/3*2, gc.height/4*3, GEBUG_RED);
    gebug_rectangle(gc, gc.width/3, gc.height/4, gc.width-1, gc.height-1, GEBUG_BLUE);
    gebug_rectangle(gc, gc.width/5, gc.height/5, gc.width/5*4, gc.height/5*4, GEBUG_YELLOW);

    gebug_save_ppm(gc, "rectangle.ppm");
    
    return 0;
}
