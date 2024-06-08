#include <RSGL.h>

int main() { 
    static int i = 0;
    RSGL_drawRect(RSGL_RECT(40 + i, 200, 200, 200), RSGL_RGB(255, 0, 0)); 
    RSGL_drawRect(RSGL_RECT(120 + i, 450, 200, 200), RSGL_RGB(255, 0, 0)); 
    i++;
}