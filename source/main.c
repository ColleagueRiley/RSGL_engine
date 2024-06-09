#define RSGL_IMPLEMENTATION
#include "RSGL.h"

#include "RSGL_tcc.c"

int main(int argc, char ** argv) { 
    if (argc < 2) {
        perror("No input files\n");
        return -1;
    }

    RSGL_window* win = RSGL_createWindow("name", (RSGL_rect){0, 0, 1000, 800}, RSGL_CENTER);    

    RSGL_setFont(RSGL_loadFont("SuperEasy.ttf"));

    while (RGFW_window_shouldClose(win) == false) {
        while (RSGL_window_checkEvent(win)) {
            if (win->event.type == RGFW_quit)
                break;
            
            u32 i;
            for (i = 0; i < files_len; i++) {
                if (files[i].eventFunc != NULL)
                    files[i].eventFunc(win->event);
            }
        }

        if (win->event.type == RSGL_quit)
            break;

        u32 i;
        for (i = 1; i < argc; i++) {
            c_file file = compile_file(argv[i], win);
            if (file.mainFunc != NULL)
                file.mainFunc();
        }

        RSGL_setTexture(0);
    
        if (RSGL_isPressedI(win, RGFW_ShiftR)) {
            char* str = RSGL_strFmt("%i, %i", win->event.point.x, win->event.point.y);
            RSGL_drawRect(RSGL_RECT(win->event.point.x, win->event.point.y, 100, 20), RSGL_RGBA(80, 80, 80, 100));
            RSGL_drawText(str, RSGL_CIRCLE(20 + win->event.point.x, win->event.point.y, 20), RSGL_RGB(0, 0, 0));
        }

        RSGL_window_clear(win, RSGL_RGB(255, 255, 255));
    }
        
    tcc_delete(tccState);
    RSGL_window_close(win);
}
