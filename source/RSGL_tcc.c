#include <stdio.h>
#include <stdlib.h>
#include <libtcc.h>

#include <sys/stat.h>


typedef struct c_file {
    TCCState* tccState;
    char* fileName;
    void (*mainFunc)();
    void (*eventFunc)(RGFW_Event);
    void (*collideFunc)(RPhys_body*, RPhys_body*);
    void (*messageFunc)(i32, void*);
    struct stat lastFileStat;
    bool inited;
} c_file;

c_file files[200];
size_t files_len = 0;

void RSGL_sendMessage(i32 msg, void* data) {
    u32 i;
    for (i = 0; i < files_len; i++) {
        if (files[i].messageFunc != NULL)
            files[i].messageFunc(msg, data);
    }
}

void error_func(void * user, const char * msg) {
    printf("TCC Error: %s\n", msg);
}

void add_RSGL_symbols(TCCState* s) {
    tcc_add_symbol(s, "RSGL_legacy", RSGL_legacy);
    tcc_add_symbol(s, "RSGL_createWindow", RSGL_createWindow);
    tcc_add_symbol(s, "RSGL_window_checkEvent", RSGL_window_checkEvent);
    tcc_add_symbol(s, "RSGL_window_close", RSGL_window_close);
    tcc_add_symbol(s, "RSGL_window_setIconImage", RSGL_window_setIconImage);
    tcc_add_symbol(s, "RSGL_window_makeCurrent", RSGL_window_makeCurrent);
    tcc_add_symbol(s, "RSGL_window_clear", RSGL_window_clear);
    tcc_add_symbol(s, "RSGL_window_setMouseStandard", RSGL_window_setMouseStandard);
    tcc_add_symbol(s, "RGFW_isPressedI", RGFW_isPressedI);
    tcc_add_symbol(s, "RSGL_isPressedI", RSGL_isPressedI);
    tcc_add_symbol(s, "RSGL_wasPressedI", RSGL_wasPressedI);
    tcc_add_symbol(s, "RSGL_isHeldI", RSGL_isHeldI);
    tcc_add_symbol(s, "RSGL_isReleasedI", RSGL_isReleasedI);
    tcc_add_symbol(s, "RSGL_rotate", RSGL_rotate);
    tcc_add_symbol(s, "RSGL_setTexture", RSGL_setTexture);
    tcc_add_symbol(s, "RSGL_setProgram", RSGL_setProgram);
    tcc_add_symbol(s, "RSGL_setGradient", RSGL_setGradient);
    tcc_add_symbol(s, "RSGL_fill", RSGL_fill);
    tcc_add_symbol(s, "RSGL_center", RSGL_center);
    tcc_add_symbol(s, "RSGL_setClearArgs", RSGL_setClearArgs);
    tcc_add_symbol(s, "RSGL_clearArgs", RSGL_clearArgs);
    tcc_add_symbol(s, "RSGL_alignRect", RSGL_alignRect);
    tcc_add_symbol(s, "RSGL_alignRectF", RSGL_alignRectF);
    tcc_add_symbol(s, "RSGL_basicDraw", RSGL_basicDraw);
    tcc_add_symbol(s, "RSGL_renderCreateTexture", RSGL_renderCreateTexture);
    tcc_add_symbol(s, "RSGL_renderUpdateTexture", RSGL_renderUpdateTexture);
    tcc_add_symbol(s, "RSGL_renderDeleteTexture", RSGL_renderDeleteTexture);
    tcc_add_symbol(s, "RSGL_renderCreateProgram", RSGL_renderCreateProgram);
    tcc_add_symbol(s, "RSGL_renderDeleteProgram", RSGL_renderDeleteProgram);
    tcc_add_symbol(s, "RSGL_renderSetShaderValue", RSGL_renderSetShaderValue);
    tcc_add_symbol(s, "RSGL_drawPoint", RSGL_drawPoint);
    tcc_add_symbol(s, "RSGL_drawPointF", RSGL_drawPointF);
    tcc_add_symbol(s, "RSGL_plotLines", RSGL_plotLines);
    tcc_add_symbol(s, "RSGL_drawTriangle", RSGL_drawTriangle);
    tcc_add_symbol(s, "RSGL_drawTriangleF", RSGL_drawTriangleF);
    tcc_add_symbol(s, "RSGL_drawTriangleHyp", RSGL_drawTriangleHyp);
    tcc_add_symbol(s, "RSGL_drawRect", RSGL_drawRect);
    tcc_add_symbol(s, "RSGL_drawRectF", RSGL_drawRectF);
    tcc_add_symbol(s, "RSGL_drawRoundRect", RSGL_drawRoundRect);
    tcc_add_symbol(s, "RSGL_drawRoundRectF", RSGL_drawRoundRectF);
    tcc_add_symbol(s, "RSGL_drawPolygon", RSGL_drawPolygon);
    tcc_add_symbol(s, "RSGL_drawPolygonF", RSGL_drawPolygonF);
    tcc_add_symbol(s, "RSGL_drawArc", RSGL_drawArc);
    tcc_add_symbol(s, "RSGL_drawArcF", RSGL_drawArcF);
    tcc_add_symbol(s, "RSGL_drawCircle", RSGL_drawCircle);
    tcc_add_symbol(s, "RSGL_drawCircleF", RSGL_drawCircleF);
    tcc_add_symbol(s, "RSGL_drawOval", RSGL_drawOval);
    tcc_add_symbol(s, "RSGL_drawOvalF", RSGL_drawOvalF);
    tcc_add_symbol(s, "RSGL_drawLine", RSGL_drawLine);
    tcc_add_symbol(s, "RSGL_drawLineF", RSGL_drawLineF);
    tcc_add_symbol(s, "RSGL_drawTriangleOutline", RSGL_drawTriangleOutline);
    tcc_add_symbol(s, "RSGL_drawTriangleFOutline", RSGL_drawTriangleFOutline);
    tcc_add_symbol(s, "RSGL_drawRectOutline", RSGL_drawRectOutline);
    tcc_add_symbol(s, "RSGL_drawRectFOutline", RSGL_drawRectFOutline);
    tcc_add_symbol(s, "RSGL_drawRoundRectOutline", RSGL_drawRoundRectOutline);
    tcc_add_symbol(s, "RSGL_drawRoundRectFOutline", RSGL_drawRoundRectFOutline);
    tcc_add_symbol(s, "RSGL_drawPolygonOutline", RSGL_drawPolygonOutline);
    tcc_add_symbol(s, "RSGL_drawPolygonFOutline", RSGL_drawPolygonFOutline);
    tcc_add_symbol(s, "RSGL_drawArcOutline", RSGL_drawArcOutline);
    tcc_add_symbol(s, "RSGL_drawArcFOutline", RSGL_drawArcFOutline);
    tcc_add_symbol(s, "RSGL_drawCircleOutline", RSGL_drawCircleOutline);
    tcc_add_symbol(s, "RSGL_drawCircleFOutline", RSGL_drawCircleFOutline);
    tcc_add_symbol(s, "RSGL_drawOvalOutline", RSGL_drawOvalOutline);
    tcc_add_symbol(s, "RSGL_drawOvalFOutline", RSGL_drawOvalFOutline);
    tcc_add_symbol(s, "RFont_fmt", RFont_fmt);
    tcc_add_symbol(s, "RSGL_loadFont", RSGL_loadFont);
    tcc_add_symbol(s, "RSGL_setFont", RSGL_setFont);
    tcc_add_symbol(s, "RSGL_setRFont", RSGL_setRFont);
    tcc_add_symbol(s, "RSGL_drawFPS", RSGL_drawFPS);
    tcc_add_symbol(s, "RSGL_drawText_len", RSGL_drawText_len);
    tcc_add_symbol(s, "RSGL_drawText", RSGL_drawText);
    tcc_add_symbol(s, "RSGL_alignText", RSGL_alignText);
    tcc_add_symbol(s, "RSGL_alignText_len", RSGL_alignText_len);
    tcc_add_symbol(s, "RSGL_textArea", RSGL_textArea);
    tcc_add_symbol(s, "RSGL_textLineArea", RSGL_textLineArea);
    tcc_add_symbol(s, "RSGL_drawImage", RSGL_drawImage);
    tcc_add_symbol(s, "RSGL_expandableRect_update", RSGL_expandableRect_update);
    tcc_add_symbol(s, "RSGL_expandableRectF_update", RSGL_expandableRectF_update);
    tcc_add_symbol(s, "RSGL_initButton", RSGL_initButton);
    tcc_add_symbol(s, "RSGL_copyButton", RSGL_copyButton);
    tcc_add_symbol(s, "RSGL_button_setStyle", RSGL_button_setStyle);
    tcc_add_symbol(s, "RSGL_button_setRect", RSGL_button_setRect);
    tcc_add_symbol(s, "RSGL_button_setRectF", RSGL_button_setRectF);
    tcc_add_symbol(s, "RSGL_button_setRounding", RSGL_button_setRounding);
    tcc_add_symbol(s, "RSGL_button_setPolygon", RSGL_button_setPolygon);
    tcc_add_symbol(s, "RSGL_button_setPolygonF", RSGL_button_setPolygonF);
    tcc_add_symbol(s, "RSGL_button_setText", RSGL_button_setText);
    tcc_add_symbol(s, "RSGL_button_alignText", RSGL_button_alignText);
    tcc_add_symbol(s, "RSGL_button_setTexture", RSGL_button_setTexture);
    tcc_add_symbol(s, "RSGL_button_setColor", RSGL_button_setColor);
    tcc_add_symbol(s, "RSGL_button_setOutline", RSGL_button_setOutline);
    tcc_add_symbol(s, "RSGL_button_setWindow", RSGL_button_setWindow);
    tcc_add_symbol(s, "RSGL_button_setKeybind", RSGL_button_setKeybind);
    tcc_add_symbol(s, "RSGL_button_setCombo", RSGL_button_setCombo);
    tcc_add_symbol(s, "RSGL_button_setDrawArgs", RSGL_button_setDrawArgs);
    tcc_add_symbol(s, "RSGL_button_setDrawArgsData", RSGL_button_setDrawArgsData);
    tcc_add_symbol(s, "RSGL_button_setOnIdle", RSGL_button_setOnIdle);
    tcc_add_symbol(s, "RSGL_button_setOnHover", RSGL_button_setOnHover);
    tcc_add_symbol(s, "RSGL_button_setOnPress", RSGL_button_setOnPress);
    tcc_add_symbol(s, "RSGL_drawButton", RSGL_drawButton);
    tcc_add_symbol(s, "RSGL_slider_update", RSGL_slider_update);
    tcc_add_symbol(s, "RSGL_nullButton", RSGL_nullButton);
    tcc_add_symbol(s, "RSGL_label", RSGL_label);
    tcc_add_symbol(s, "RSGL_initContainer", RSGL_initContainer);
    tcc_add_symbol(s, "RSGL_freeContainer", RSGL_freeContainer);
    tcc_add_symbol(s, "RSGL_drawContainer", RSGL_drawContainer);
    tcc_add_symbol(s, "RSGL_container_setStyle", RSGL_container_setStyle);
    tcc_add_symbol(s, "RSGL_container_setPos", RSGL_container_setPos);
    tcc_add_symbol(s, "RSGL_container_update", RSGL_container_update);
    tcc_add_symbol(s, "RSGL_initTextbox", RSGL_initTextbox);
    tcc_add_symbol(s, "RSGL_textbox_free", RSGL_textbox_free);
    tcc_add_symbol(s, "RSGL_textbox_draw", RSGL_textbox_draw);
    tcc_add_symbol(s, "RSGL_textbox_getString", RSGL_textbox_getString);
    tcc_add_symbol(s, "RSGL_textbox_update", RSGL_textbox_update);
    tcc_add_symbol(s, "RSGL_textbox_setTextInfo", RSGL_textbox_setTextInfo);
    tcc_add_symbol(s, "RSGL_textbox_alignText", RSGL_textbox_alignText);
    tcc_add_symbol(s, "RSGL_textbox_setColor", RSGL_textbox_setColor);
    tcc_add_symbol(s, "RSGL_textbox_setOutline", RSGL_textbox_setOutline);
    tcc_add_symbol(s, "RSGL_textbox_setStyle", RSGL_textbox_setStyle);
    tcc_add_symbol(s, "RSGL_textbox_setRect", RSGL_textbox_setRect);
    tcc_add_symbol(s, "RSGL_textbox_setRectF", RSGL_textbox_setRectF);
    tcc_add_symbol(s, "RSGL_textbox_setWindow", RSGL_textbox_setWindow);
    tcc_add_symbol(s, "RSGL_wait", RSGL_wait);
    tcc_add_symbol(s, "RSGL_wait_frames", RSGL_wait_frames);
    tcc_add_symbol(s, "RSGL_circleCollidePoint", RSGL_circleCollidePoint);
    tcc_add_symbol(s, "RSGL_circleCollideRect", RSGL_circleCollideRect);
    tcc_add_symbol(s, "RSGL_circleCollide", RSGL_circleCollide);
    tcc_add_symbol(s, "RSGL_rectCollidePoint", RSGL_rectCollidePoint);
    tcc_add_symbol(s, "RSGL_rectCollide", RSGL_rectCollide);
    tcc_add_symbol(s, "RSGL_pointCollide", RSGL_pointCollide);
    tcc_add_symbol(s, "RSGL_circleCollidePointF", RSGL_circleCollidePointF);
    tcc_add_symbol(s, "RSGL_circleCollideRectF", RSGL_circleCollideRectF);
    tcc_add_symbol(s, "RSGL_circleCollideF", RSGL_circleCollideF);
    tcc_add_symbol(s, "RSGL_rectCollidePointF", RSGL_rectCollidePointF);
    tcc_add_symbol(s, "RSGL_rectCollideF", RSGL_rectCollideF);
    tcc_add_symbol(s, "RSGL_pointCollideF", RSGL_pointCollideF);
    tcc_add_symbol(s, "RGFW_createWindow", RGFW_createWindow);
    tcc_add_symbol(s, "RGFW_getScreenSize", RGFW_getScreenSize);
    tcc_add_symbol(s, "RGFW_window_checkEvent", RGFW_window_checkEvent);
    tcc_add_symbol(s, "RGFW_window_close", RGFW_window_close);
    tcc_add_symbol(s, "RGFW_window_move", RGFW_window_move);
    tcc_add_symbol(s, "RGFW_window_moveToMonitor", RGFW_window_moveToMonitor);
    tcc_add_symbol(s, "RGFW_window_resize", RGFW_window_resize);
    tcc_add_symbol(s, "RGFW_window_setMinSize", RGFW_window_setMinSize);
    tcc_add_symbol(s, "RGFW_window_setMaxSize", RGFW_window_setMaxSize);
    tcc_add_symbol(s, "RGFW_window_maximize", RGFW_window_maximize);
    tcc_add_symbol(s, "RGFW_window_minimize", RGFW_window_minimize);
    tcc_add_symbol(s, "RGFW_window_restore", RGFW_window_restore);
    tcc_add_symbol(s, "RGFW_window_setName", RGFW_window_setName);
    tcc_add_symbol(s, "RGFW_window_setIcon", RGFW_window_setIcon);
    tcc_add_symbol(s, "RGFW_window_setMouse", RGFW_window_setMouse);
    tcc_add_symbol(s, "RGFW_window_setMouseStandard", RGFW_window_setMouseStandard);
    tcc_add_symbol(s, "RGFW_window_setMouseDefault", RGFW_window_setMouseDefault);
    tcc_add_symbol(s, "RGFW_window_mouseHold", RGFW_window_mouseHold);
    tcc_add_symbol(s, "RGFW_window_mouseUnhold", RGFW_window_mouseUnhold);
    tcc_add_symbol(s, "RGFW_window_hide", RGFW_window_hide);
    tcc_add_symbol(s, "RGFW_window_show", RGFW_window_show);
    tcc_add_symbol(s, "RGFW_window_setShouldClose", RGFW_window_setShouldClose);
    tcc_add_symbol(s, "RGFW_getGlobalMousePoint", RGFW_getGlobalMousePoint);
    tcc_add_symbol(s, "RGFW_window_showMouse", RGFW_window_showMouse);
    tcc_add_symbol(s, "RGFW_window_moveMouse", RGFW_window_moveMouse);
    tcc_add_symbol(s, "RGFW_window_shouldClose", RGFW_window_shouldClose);
    tcc_add_symbol(s, "RGFW_window_isFullscreen", RGFW_window_isFullscreen);
    tcc_add_symbol(s, "RGFW_window_isHidden", RGFW_window_isHidden);
    tcc_add_symbol(s, "RGFW_window_isMinimized", RGFW_window_isMinimized);
    tcc_add_symbol(s, "RGFW_window_isMaximized", RGFW_window_isMaximized);
    tcc_add_symbol(s, "RGFW_window_scaleToMonitor", RGFW_window_scaleToMonitor);
    tcc_add_symbol(s, "RGFW_window_getMonitor", RGFW_window_getMonitor);
    tcc_add_symbol(s, "RGFW_window_makeCurrent", RGFW_window_makeCurrent);
    tcc_add_symbol(s, "RGFW_isPressedI", RGFW_isPressedI);
    tcc_add_symbol(s, "RGFW_wasPressedI", RGFW_wasPressedI);
    tcc_add_symbol(s, "RGFW_isHeldI", RGFW_isHeldI);
    tcc_add_symbol(s, "RGFW_isReleasedI", RGFW_isReleasedI);
    tcc_add_symbol(s, "RGFW_keyCodeTokeyStr", RGFW_keyCodeTokeyStr);
    tcc_add_symbol(s, "RGFW_keyStrToKeyCode", RGFW_keyStrToKeyCode);
    tcc_add_symbol(s, "RGFW_readClipboard", RGFW_readClipboard);
    tcc_add_symbol(s, "RGFW_writeClipboard", RGFW_writeClipboard);
    tcc_add_symbol(s, "RGFW_keystrToChar", RGFW_keystrToChar);
    tcc_add_symbol(s, "RGFW_registerJoystick", RGFW_registerJoystick);
    tcc_add_symbol(s, "RGFW_registerJoystickF", RGFW_registerJoystickF);
    tcc_add_symbol(s, "RGFW_isPressedJS", RGFW_isPressedJS);
    tcc_add_symbol(s, "RGFW_window_swapBuffers", RGFW_window_swapBuffers);
    tcc_add_symbol(s, "RGFW_window_swapInterval", RGFW_window_swapInterval);
    tcc_add_symbol(s, "RGFW_window_setGPURender", RGFW_window_setGPURender);
    tcc_add_symbol(s, "RGFW_getTime", RGFW_getTime);
    tcc_add_symbol(s, "RGFW_getTimeNS", RGFW_getTimeNS);
    tcc_add_symbol(s, "RGFW_sleep", RGFW_sleep);
    tcc_add_symbol(s, "RPhys_addVector2", RPhys_addVector2);
    tcc_add_symbol(s, "RPhys_subtractVector2", RPhys_subtractVector2);
    tcc_add_symbol(s, "RPhys_multiplyVector2", RPhys_multiplyVector2);
    tcc_add_symbol(s, "RPhys_divideVector2", RPhys_divideVector2);
    tcc_add_symbol(s, "RPhys_init", RPhys_init);
    tcc_add_symbol(s, "RPhys_run", RPhys_run);
    tcc_add_symbol(s, "RPhys_step", RPhys_step);
    tcc_add_symbol(s, "RPhys_free", RPhys_free);
    tcc_add_symbol(s, "RPhys_setGravity", RPhys_setGravity);
    tcc_add_symbol(s, "RPhys_setAirDensity", RPhys_setAirDensity);
    tcc_add_symbol(s, "RPhys_angledForce", RPhys_angledForce);
    tcc_add_symbol(s, "RPhys_time", RPhys_time);
    tcc_add_symbol(s, "RPhys_circleCollideRect", RPhys_circleCollideRect);
    tcc_add_symbol(s, "RPhys_circleCollide", RPhys_circleCollide);
    tcc_add_symbol(s, "RPhys_rectCollide", RPhys_rectCollide);
    tcc_add_symbol(s, "RPhys_shapeCollide", RPhys_shapeCollide);
    tcc_add_symbol(s, "RPhys_triangleToRect", RPhys_triangleToRect);
    tcc_add_symbol(s, "RPhys_shapeRect", RPhys_shapeRect);
    tcc_add_symbol(s, "RPhys_MuTable", RPhys_MuTable);
    tcc_add_symbol(s, "RPhys_shape_loadRect", RPhys_shape_loadRect);
    tcc_add_symbol(s, "RPhys_shape_loadPolygon", RPhys_shape_loadPolygon);
    tcc_add_symbol(s, "RPhys_shape_loadCircle", RPhys_shape_loadCircle);
    tcc_add_symbol(s, "RPhys_shape_loadTriangle", RPhys_shape_loadTriangle);
    tcc_add_symbol(s, "RPhys_shape_loadPoint", RPhys_shape_loadPoint);
    tcc_add_symbol(s, "RPhys_shape_getRect", RPhys_shape_getRect);
    tcc_add_symbol(s, "RPhys_shape_getPolyRect", RPhys_shape_getPolyRect);
    tcc_add_symbol(s, "RPhys_shape_getCircle", RPhys_shape_getCircle);
    tcc_add_symbol(s, "RPhys_shape_getTriangle", RPhys_shape_getTriangle);
    tcc_add_symbol(s, "RPhys_shape_getPoint", RPhys_shape_getPoint);
    tcc_add_symbol(s, "RPhys_body_getAcceleration", RPhys_body_getAcceleration);
    tcc_add_symbol(s, "RPhys_addBody", RPhys_addBody);
    tcc_add_symbol(s, "RPhys_addBodies", RPhys_addBodies);
    tcc_add_symbol(s, "RPhys_removeBody", RPhys_removeBody);
    tcc_add_symbol(s, "RPhys_drawBodies", RPhys_drawBodies);
    tcc_add_symbol(s, "RPhys_drawBodiesColors", RPhys_drawBodiesColors);
    tcc_add_symbol(s, "RPhys_drawBodiesTextures", RPhys_drawBodiesTextures);
    tcc_add_symbol(s, "RPhys_drawBodiesPro", RPhys_drawBodiesPro);
    tcc_add_symbol(s, "RSGL_sendMessage", RSGL_sendMessage);
}

void RPhys_collideCallback(RPhys_body* body1, RPhys_body* body2) {
    u32 i;
    for (i = 0; i < files_len; i++) {
        if (files[i].collideFunc != NULL)
            files[i].collideFunc(body1, body2);
    }
}

c_file compile_file(char* fileName, RSGL_window* win) {
    u32 i;
    for (i = 0; i < files_len; i++) {
        if (strcmp(files[i].fileName, fileName) == 0)
            break;
    }

    if (files_len == i) {
        files[i].fileName = fileName;
        files[i].tccState = NULL;
        files[i].mainFunc = NULL;
        files[i].eventFunc = NULL;
        files[i].collideFunc = NULL;
        files[i].messageFunc = NULL;
        files[i].inited = false;
        files_len++;
    }

    struct stat fileStat;
    time_t mtime;

    if (stat(fileName, &fileStat) < 0) {
        perror(fileName);
        return files[i];
    }
    
    if (fileStat.st_mtime == files[i].lastFileStat.st_mtime && files[i].inited != false) {
        return files[i];
    }
     
    if (files[i].tccState != NULL)
        tcc_delete(files[i].tccState);
    
    files[i].tccState = tcc_new();

    tcc_set_output_type(files[i].tccState, TCC_OUTPUT_MEMORY);
    tcc_set_error_func(files[i].tccState, 0, error_func);

    tcc_add_include_path(files[i].tccState, "./");
    tcc_add_include_path(files[i].tccState, "./include");
    tcc_add_include_path(files[i].tccState, "tinycc/include");
    tcc_add_library_path(files[i].tccState, "tinycc");

    if (tcc_add_file(files[i].tccState, fileName) == -1) {
        files[i].mainFunc = NULL;
        files[i].eventFunc = NULL;
        files[i].collideFunc = NULL;
        files[i].messageFunc = NULL;
        
        return files[i];
    }

    add_RSGL_symbols(files[i].tccState);    
    
    tcc_run(files[i].tccState, 0, NULL);

    void* initFunc = tcc_get_symbol(files[i].tccState, "init");
    if (initFunc != NULL)
        ((void (*)()) initFunc)(win);
    files[i].eventFunc = tcc_get_symbol(files[i].tccState, "eventLoop");
    files[i].collideFunc = tcc_get_symbol(files[i].tccState, "collideEvent");
    files[i].messageFunc = tcc_get_symbol(files[i].tccState, "getMessage");
    files[i].mainFunc = tcc_get_symbol(files[i].tccState, "main");

    files[i].lastFileStat = fileStat;

    files[i].inited = true;

    return files[i];
}