#include "RSGL.h"
#include <stdio.h>

RSGL_color color = RSGL_RGB(255, 0, 0);

void getMessage(int message, void* data) {
    switch (message) {
        case 0:
            color = *(RSGL_color*)data;
            break;
            
        default:
            break;
    }
}

RSGL_image image;

RPhys_body body;

void init(RGFW_window* win) {
    RGFW_window_resize(win, RGFW_AREA(800, 800));
    RGFW_window_setName(win, "my game");
    RSGL_window_setIconImage(win, "image.png");
    image = RSGL_loadImage("image.png");

    body = (RPhys_body){RPhys_shape_loadRect(RSGL_RECTF(120, 450, 200, 200), 0.90f, CONCRETE_DRY), false};
    RPhys_addBody(&body);
}

u8 b = 0;

void eventLoop(RGFW_Event event) {
    if (event.type == RGFW_keyReleased) {
        b += 5;
    }
}


int main() { 
    static u8 i = 0;
    
    RSGL_setTexture(image.tex);
    RSGL_drawRectF(RPhys_shape_getRect(body.shape), color);
    
    body.velocity.x = i * (pow(10, -3));
    body.velocity.y = b * (pow(10, -3));
    i++;

    if (i == 0 || body.shape.r.v.x > 800  || body.shape.r.v.x < -body.shape.r.w - 5)
        body.shape.r.v.x = 120;
    if (b == 0 || body.shape.r.v.y > 800 || body.shape.r.v.y < -body.shape.r.h - 5)
        body.shape.r.v.y = 450;
}   