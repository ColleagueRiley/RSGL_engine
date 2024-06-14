#define RGFW_NO_THREADS
#define RSGL_IMPLEMENTATION
#include "RSGL.h"

#define RPHYS_IMPLEMENTATION
#include "rphys.h"

#include "RSGL_tcc.c"

typedef struct sprite {
    RSGL_point initPoint;
    bool pressed;
} sprite;

int main(int argc, char ** argv) { 
    if (argc < 2) {
        perror("No input files\n");
        return -1;
    }

    bool rElEaSeMoDe = false; /* in rElEaSe MoDe */
    bool phys_pause = false;
  
    RPhys_init();

    RSGL_window* win = RSGL_createWindow("name", (RSGL_rect){0, 0, 1000, 800}, RSGL_CENTER);    

    RSGL_setFont(RSGL_loadFont("SuperEasy.ttf"));

    sprite* sprites = (sprite*)RPHYS_MALLOC(sizeof(sprite) * RPHYS_BODIES_INIT);
    
     
    while (RGFW_window_shouldClose(win) == false) {
        while (RSGL_window_checkEvent(win)) {
            if (win->event.type == RGFW_quit)
                break;
            
            u32 i;
            for (i = 0; i < files_len; i++) {
                if (files[i].eventFunc != NULL)
                    files[i].eventFunc(win->event);
            }

            switch (win->event.type) {
                case RGFW_keyReleased:
                    if (win->event.keyCode == RGFW_d && RSGL_isPressedI(win, RGFW_ControlL))
                        phys_pause = !phys_pause;
                    break;
                
                case RGFW_mouseButtonPressed:  
                    if (RSGL_isPressedI(win, RGFW_ControlL) && !rElEaSeMoDe) {
                        u32 index = 0;
                        for (index = 0; index < RPhys_len; index++) {
                            RPhys_body* body = RPhys_bodies[index];
                            sprite* sprite = &sprites[index]; 

                            sprite->pressed = RSGL_rectCollidePointF(RPhys_shape_getRect(body->shape), RSGL_POINTF(win->event.point.x, win->event.point.y));
                            sprite->initPoint = win->event.point;
                        }
                    } 

                    break;
                
                case RGFW_mousePosChanged: {
                    u32 index = 0;
                    for (index = 0; index < RPhys_len; index++) {
                        RPhys_body* body = RPhys_bodies[index];
                        sprite* sprite = &sprites[index]; 
                        
                        if (sprite->pressed == false) 
                            continue;
                        
                        body->shape.r.v = RSGL_POINTF(body->shape.r.v.x + (float)(win->event.point.x - sprite->initPoint.x),
                                                            body->shape.r.v.y + (float)(win->event.point.y - sprite->initPoint.y));

                        sprite->initPoint = win->event.point;   
                    }

                    break;
                }

                case RGFW_mouseButtonReleased: {
                    u32 index = 0;
                    for (index = 0; index < RPhys_len; index++) {
                        RPhys_body* body = RPhys_bodies[index];
                        sprite* sprite = &sprites[index]; 

                        sprite->pressed = false;
                    }
                    
                    break;
                }
            }
        }

        if (win->event.type == RSGL_quit)
            break;

        i32 i;
        for (i = 1; i < argc; i++) {
            if (argv[i][0] == '-') {
                if (rElEaSeMoDe == false && strcmp(argv[i], "--release") == 0)
                    rElEaSeMoDe = true;
                continue;
            }

            c_file file = compile_file(argv[i], win);
            if (file.mainFunc != NULL)
                file.mainFunc();
        }
        
        RSGL_setTexture(0);
    
        if (RSGL_isPressedI(win, RGFW_ControlL) && !rElEaSeMoDe) {
            char* str = (char*)RSGL_strFmt("%i, %i", win->event.point.x, win->event.point.y);
            RSGL_drawRect(RSGL_RECT(win->event.point.x, win->event.point.y, 100, 20), RSGL_RGBA(80, 80, 80, 100));
            RSGL_drawText(str, RSGL_CIRCLE(20 + win->event.point.x, win->event.point.y, 20), RSGL_RGB(0, 0, 0));
        
            u32 index = 0;
            for (index = 0; index < RPhys_len; index++) {
                RSGL_rectF rect = RPhys_shape_getRect(RPhys_bodies[index]->shape);
                char* str = (char*)RSGL_strFmt("%i, %i", (u32)rect.x, (u32)rect.y);
                RSGL_drawRect(RSGL_RECT(rect.x + ((rect.w - 100) / 2), rect.y + (rect.h / 2), 100, 20), RSGL_RGBA(80, 80, 80, 100));
                RSGL_drawText(str, RSGL_CIRCLE(rect.x + ((rect.w - 50) / 2), rect.y + (rect.h / 2), 20), RSGL_RGB(0, 0, 0));
            }
        }

        if (phys_pause == false)
            RPhys_run(RPhys_collideCallback);
        
        RSGL_window_clear(win, RSGL_RGB(255, 255, 255));
    }
    
    free(sprites);
    RPhys_free();

    u32 index = 0;
    for (index = 0; index < files_len; index++) {
        tcc_delete(files[index].tccState);
    }
    
    RSGL_window_close(win);
}
