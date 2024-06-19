#define RGFW_NO_THREADS
#define RSGL_IMPLEMENTATION
#include "RSGL.h"

#define RPHYS_IMPLEMENTATION
#include "rphys.h"

#include "RSGL_tcc.c"

#include "objfiles.h"
/*
char** objfiles;
size_t objfiles_len;
*/

int main(int argc, char ** argv) { 
    RPhys_init();

    RSGL_window* win = RSGL_createWindow("name", (RSGL_rect){0, 0, 1000, 800}, RSGL_CENTER);

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

        i32 i;
        for (i = 0; i < objfiles_len; i++) {
            c_file file = compile_file(objfiles[i], win);
            if (file.mainFunc != NULL)
                file.mainFunc();
        }

        RPhys_run(RPhys_collideCallback);
        
        RSGL_window_clear(win, RSGL_RGB(255, 255, 255));
    }
    
    RPhys_free();

    u32 index = 0;
    for (index = 0; index < files_len; index++) {
        tcc_delete(files[index].tccState);
    }
    
    RSGL_window_close(win);
}
