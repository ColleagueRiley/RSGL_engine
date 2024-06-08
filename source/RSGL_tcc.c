#include <stdio.h>
#include <stdlib.h>
#include <libtcc.h>

#include <sys/stat.h>


TCCState* tccState = NULL;

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
}

void* compile_file(char* fileName) {
    static void* lastFunc = NULL;
    static struct stat lastFileStat;
    struct stat fileStat;
    time_t mtime;

    if (stat(fileName, &fileStat) < 0) {
        perror(fileName);
        return NULL;
    }
    
    if (fileStat.st_mtime == lastFileStat.st_mtime && lastFunc != NULL) {
        return lastFunc;
    }
     
    if (tccState != NULL)
        tcc_delete(tccState);

    tccState = tcc_new();

    tcc_set_output_type(tccState, TCC_OUTPUT_MEMORY);
    tcc_set_error_func(tccState, 0, error_func);

    FILE* file = fopen(fileName, "r");
    fseek(file, 0, SEEK_END);
    size_t len = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* file_ptr = malloc(len + 1);
    fread(file_ptr, 1, len, file);
    fclose(file);
    file_ptr[len] = '\0';

    tcc_add_include_path(tccState, "./include");
    tcc_add_include_path(tccState, "./");

    tcc_compile_string(tccState, file_ptr);

    add_RSGL_symbols(tccState);    

    tcc_run(tccState, 0, NULL);

    free(file_ptr);

    lastFunc = tcc_get_symbol(tccState, "main");

    lastFileStat = fileStat;

    return lastFunc;
}