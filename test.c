#include "RSGL.h"
#include <stdio.h>


RSGL_image image;

RPhys_body body;

void init(RGFW_window* win) {
    RGFW_window_resize(win, RGFW_AREA(800, 800));
    RGFW_window_setName(win, "my game");
    RSGL_window_setIconImage(win, "image.png");
    image = RSGL_loadImage("image.png");
    
    body = (RPhys_body){RPhys_shape_loadPolygon(RSGL_RECTF(200, 20, 200, 200), 8, 0.90f, CONCRETE_DRY), true};
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
    RSGL_drawPolygonF(RPhys_shape_getRect(body.shape), body.shape.vertexCount, RSGL_RGB(255, 0, 0));
    RSGL_drawRect(RSGL_RECT(120 + i, 450 + b, 200, 200), RSGL_RGB(255, 0, 0)); 
    i++;
    
    if (RSGL_isPressedI(NULL, RGFW_Up))
        body.velocity.y = -0.5;
    else if (RSGL_isPressedI(NULL, RGFW_Down))
        body.velocity.y = 0.5;
    else
        body.velocity.y = 0;
    
    if (RSGL_isPressedI(NULL, RGFW_Left))
        body.velocity.x = -0.5;    
    else if (RSGL_isPressedI(NULL, RGFW_Right))
        body.velocity.x = 0.5;
    else
        body.velocity.x = 0;
}   