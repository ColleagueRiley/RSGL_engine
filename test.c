#include <RSGL.h>
#include <stdio.h>


RSGL_image image;

void init(RGFW_window* win) {
    RGFW_window_resize(win, RGFW_AREA(800, 800));
    RGFW_window_setName(win, "my game");
    RSGL_window_setIconImage(win, "image.png");
    image = RSGL_loadImage("image.png");
}

u8 b = 0;

void eventLoop(RGFW_Event event) {
    if (event.type == RGFW_keyReleased) {
        b += 5;
    }
}

int main() { 
    static u8 i = 0;
    static RSGL_rect rect = RSGL_RECT(20, 200, 200, 200);
    RSGL_setTexture(image.tex);
    RSGL_drawPolygon(rect, 11, RSGL_RGB(255, 0, 0)); 
    RSGL_drawRect(RSGL_RECT(120 + i, 450 + b, 200, 200), RSGL_RGB(255, 0, 0)); 
    i++;

    if (RSGL_isPressedI(NULL, RGFW_Up))
        rect.y -= 5;
    if (RSGL_isPressedI(NULL, RGFW_Down))
        rect.y += 5;
    if (RSGL_isPressedI(NULL, RGFW_Left))
        rect.x -= 5;    
    if (RSGL_isPressedI(NULL, RGFW_Right))
        rect.x += 5;
}   