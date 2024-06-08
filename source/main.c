#define RSGL_IMPLEMENTATION
#include "RSGL.h"

#include "RSGL_tcc.c"

int main(int argc, char ** argv) { 
    if (argc < 2) {
        perror("No input files\n");
        return -1;
    }

    RSGL_window* win = RSGL_createWindow("name", (RSGL_rect){0, 0, 1000, 800}, RSGL_CENTER);    

    for (;;) {
        RSGL_window_checkEvent(win);

        if (win->event.type == RSGL_quit)
            break;

        u32 i;
        for (i = 1; i < argc; i++) {
            void* func = compile_file(argv[i]);
            if (func != NULL)
                ((void(*)())func)();
        }

        RSGL_window_clear(win, RSGL_RGB(255, 255, 255));
    }
        
    tcc_delete(tccState);
    RSGL_window_close(win);
}
