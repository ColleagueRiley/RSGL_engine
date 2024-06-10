#include "RSGL.h"
#include <stdio.h>


RSGL_image image;

RPhys_body body;
RPhys_body bigBody;


void init(RGFW_window* win) {
    RGFW_window_resize(win, RGFW_AREA(800, 800));
    RGFW_window_setName(win, "my game");
    RSGL_window_setIconImage(win, "image.png");
    image = RSGL_loadImage("image.png");
    
    body = (RPhys_body){RPhys_shape_loadRect(RSGL_RECTF(200, 20, 200, 200), 0.90f, CONCRETE_DRY), false};
    RPhys_addBody(&body);

    bigBody = (RPhys_body){RPhys_shape_loadRect(RSGL_RECTF(120, 450, 200, 200), 0.90f, CONCRETE_DRY), false};
    RPhys_addBody(&bigBody);

    RPhys_setGravity((vector2){0, 0});
}

void collideEvent(RPhys_body* body1, RPhys_body* body2) {
    if (body1->index != body.index && body2->index != body.index && 
        body1->index != bigBody.index && body2->index != bigBody.index
    )    
        return;
    
    printf("body %i collided with body %i\n", body1->index, body2->index);
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
    RSGL_drawPolygonF(RPhys_shape_getRect(body.shape), 8, RSGL_RGB(255, 0, 0));
    RSGL_drawRectF(RPhys_shape_getRect(bigBody.shape), RSGL_RGB(255, 0, 0));
    
    bigBody.velocity.x = i * (pow(10, -3));
    bigBody.velocity.y = b * (pow(10, -3));
    i++;

    if (i == 0)
        bigBody.shape.r.v.x = 120;
    if (b == 0)
        bigBody.shape.r.v.y = 450;
    
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