void RSGL_sendMessage(int msg, void* data);
/*
* Copyright (c) 2021-24 ColleagueRiley ColleagueRiley@gmail.com
*
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
*
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following r estrictions:
*
* 1. The origin of this software must not be misrepresented; you must not
* claim that you wrote the original software. If you use this software
* in a product, an acknowledgment in the product documentation would be
* appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
* misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
*
*
*/

/*
    define args
    (MAKE SURE RSGL_IMPLEMENTATION is in exactly one header or you use -DRSGL_IMPLEMENTATION)
	#define RSGL_IMPLEMENTATION - makes it so source code is included with header
    
    #define RSGL_NO_RGFW - no RSGL_window, RSGL_graphics is used instead [this is for using a differnt window manager other than RGFW ]
    #define RSGL_NO_TEXT - do not include text rendering functions
    #define RSGL_NO_WIDGETS - do not include widgets
    #define RSGL_NO_SAVE_IMAGE - do not save/load images (don't use RSGL_drawImage if you use this), 
                                    RSGL_drawImage saves the file name + texture so it can load it
                                    when you ask for it later. This disables that 
    #define RSGL_INIT_FONTS [number of fonts] - set hFow much room should be pre-allocated for fonts by fontstash
                                                this avoids performance issues related to RSGL_REALLOC
                                                RSGL_INIT_FONTS = 4 by default
    #define RSGL_INIT_IMAGES [number of fonts] - set how much room should be pre-allocated for images by RSGL
                                                this avoids performance issues related to RSGL_REALLOC
                                                RSGL_INIT_IMAGES = 20 by default
    #define RSGL_NEW_IMAGES [number of fonts] - set how much room should be RSGL_REALLOCated at a time for images by RSGL
                                                this avoids performance issues related to RSGL_REALLOC
                                                RSGL_NEW_IMAGES 10 by default

    #define RSGL_MAX_BATCHES [number of batches] - set max number of batches to be allocated
    #define RSGL_MAX_VERTS [number of verts] - set max number of verts to be allocated (global, not per batch)

    #define RSGL_RENDER_LEGACY - use legacy rendering (ex. opengl) functions
    
    #define RSGL_NO_STB_IMAGE - do not include stb_image.h (& don't define image loading funcs)
    #define RSGL_NO_STB_IMAGE_IMP - declare stb funcs but don't define
    #define RSGL_NO_DEPS_FOLDER - Do not use '/deps' for the deps includes, use "./"

    RGFW (more RGFW documentation in RGFW.h):
    
	#define RGFW_PRINT_ERRORS - (optional) makes it so RGFW prints errors when they're found
	#define RGFW_OSMESA - (optional) use OSmesa as backend (instead of system's opengl api + regular opengl)
	#define RGFW_BUFFER - (optional) just draw directly to (RGFW) window pixel buffer that is drawn to screen (the buffer is in the BGRA format)
	#define RGFW_EGL - (optional) use EGL for loading an OpenGL context (instead of the system's opengl api)
	#define RGFW_OPENGL_ES - (optional) use EGL to load and use Opengl ES for backend rendering (instead of the system's opengl api)
	#define VULKAN - (optional) use vulkan for the rendering backend (rather than opengl)

	#define RGFW_LINK_EGL (optional) (windows only) if EGL is being used, if EGL functions should be defined dymanically (using GetProcAddress)
	#define RGFW_LINK_OSMESA (optional) (windows only) if EGL is being used, if OS Mesa functions should be defined dymanically  (using GetProcAddress)

	#define RGFW_X11 (optional) (unix only) if X11 should be used. This option is turned on by default by unix systems except for MacOS
	#define RGFW_WGL_LOAD (optional) (windows only) if WGL should be loaded dynamically during runtime
*/ 
#ifndef RSGL_INIT_FONTS
#define RSGL_INIT_FONTS 4
#endif
#ifndef RSGL_NEW_FONTS
#define RSGL_NEW_FONTS 2
#endif
#ifndef RSGL_INIT_IMAGES
#define RSGL_INIT_IMAGES 20
#endif
#ifndef RSGL_NEW_IMAGES
#define RSGL_NEW_IMAGES 10
#endif
#ifndef RSGL_MAX_BATCHES
#define RSGL_MAX_BATCHES 2028
#endif
#ifndef RSGL_MAX_VERTS
#define RSGL_MAX_VERTS 8192
#endif

#ifndef RSGL_MALLOC
#define RSGL_MALLOC malloc
#define RSGL_REALLOC realloc
#define RSGL_FREE free
#endif

#ifndef RSGL_UNUSED
#define RSGL_UNUSED(x) if (x){}
#endif

/*! Optional arguments for making a windows */
#define RSGL_TRANSPARENT_WINDOW		(1L<<9) /*!< the window is transparent */
#define RSGL_NO_BORDER		(1L<<3) /*!< the window doesn't have border */
#define RSGL_NO_RESIZE		(1L<<4) /*!< the window cannot be resized  by the user */
#define RSGL_ALLOW_DND     (1L<<5) /*!< the window supports drag and drop*/
#define RSGL_HIDE_MOUSE (1L<<6) /*! the window should hide the mouse or not (can be toggled later on) using `RGFW_window_mouseShow*/
#define RSGL_FULLSCREEN (1L<<8) /* the window is fullscreen by default or not */
#define RSGL_CENTER (1L<<10) /*! center the window on the screen */
#define RSGL_OPENGL_SOFTWARE (1L<<11) /*! use OpenGL software rendering */

/*! event codes */
#define RSGL_keyPressed 2 /* a key has been pressed */
#define RSGL_keyReleased 3 /*!< a key has been released*/
/*! key event note
	the code of the key pressed is stored in
	RGFW_Event.keyCode
	!!Keycodes defined at the bottom of the header file!!
	
	while a string version is stored in
	RGFW_Event.KeyString

	RGFW_Event.lockState holds the current lockState
	this means if CapsLock, NumLock are active or not
*/
#define RSGL_mouseButtonPressed 4 /*!< a mouse button has been pressed (left,middle,right)*/
#define RSGL_mouseButtonReleased 5 /*!< a mouse button has been released (left,middle,right)*/
#define RSGL_mousePosChanged 6 /*!< the position of the mouse has been changed*/
/*! mouse event note
	The x and y coords of the mouse are stored as RSGL_point in RGFW_Event.point
	
	RGFW_Event.button holds which mouse button was pressed
*/
#define RSGL_jsButtonPressed 7 /*!< a joystick button was pressed */
#define RSGL_jsButtonReleased 8 /*!< a joystick button was released */
#define RSGL_jsAxisMove 9 /*!< an axis of a joystick was moved*/
/*! joystick event note
	RGFW_Event.joystick holds which joystick was altered, if any
	RGFW_Event.button holds which joystick button was pressed

	RGFW_Event.axis holds the data of all the axis
	RGFW_Event.axisCount says how many axis there are
*/
#define RSGL_windowAttribsChange 10 /*!< the window was moved or resized (by the user) */
/* attribs change event note
	The event data is sent straight to the window structure
	with win->r.x, win->r.y, win->r.w and win->r.h
*/
#define RSGL_quit 33 /*!< the user clicked the quit button*/ 
#define RSGL_dnd 34 /*!< a file has been dropped into the window*/
#define RSGL_dnd_init 35 /*!< the start of a dnd event, when the place where the file drop is known */
/* dnd data note
	The x and y coords of the drop are stored as RSGL_point in RGFW_Event.point

	RGFW_Event.droppedFilesCount holds how many files were dropped
	
	This is also the size of the array which stores all the dropped file string,
	RGFW_Event.droppedFiles
*/

/*! mouse button codes (RGFW_Event.button) */
#define RSGL_mouseLeft  1 /*!< left mouse button is pressed*/
#define RSGL_mouseMiddle  2 /*!< mouse-wheel-button is pressed*/
#define RSGL_mouseRight  3 /*!< right mouse button is pressed*/
#define RSGL_mouseScrollUp  4 /*!< mouse wheel is scrolling up*/
#define RSGL_mouseScrollDown  5 /*!< mouse wheel is scrolling down*/

/* for RGFW_Event.lockstate */
#define RSGL_CAPSLOCK (1L << 1)
#define RSGL_NUMLOCK (1L << 2)

#define RSGL_JS_A RGFW_JS_A /* or PS X button */
#define RSGL_JS_B RGFW_JS_B /* or PS circle button */
#define RSGL_JS_Y RGFW_JS_Y /* or PS triangle button */
#define RSGL_JS_X RGFW_JS_X /* or PS square button */
#define RSGL_JS_START RGFW_JS_START /* start button */
#define RSGL_JS_SELECT RGFW_JS_SELECT /* select button */
#define RSGL_JS_HOME RGFW_JS_HOME /* home button */
#define RSGL_JS_UP RGFW_JS_UP /* dpad up */
#define RSGL_JS_DOWN RGFW_JS_DOWN /* dpad down*/
#define RSGL_JS_LEFT RGFW_JS_LEFT /* dpad left */
#define RSGL_JS_RIGHT RGFW_JS_RIGHT /* dpad right */
#define RSGL_JS_L1 RGFW_JS_L1 /* left bump */
#define RSGL_JS_L2 RGFW_JS_L2 /* left trigger*/
#define RSGL_JS_R1 RGFW_JS_R1 /* right bumper */
#define RSGL_JS_R2 RGFW_JS_R2 /* right trigger */

/* 
RSGL basicDraw types
*/

#ifndef RSGL_QUADS
#define RSGL_POINTS                               0x0000
#define RSGL_LINES                                0x0001      
#define RSGL_LINE_LOOP                            0x0002
#define RSGL_LINE_STRIP                           0x0003
#define RSGL_TRIANGLES                            0x0004      
#define RSGL_TRIANGLE_STRIP                       0x0005
#define RSGL_TRIANGLE_FAN                         0x0006      
#define RSGL_QUADS                                 0x0007

/* these are to ensure GL_DEPTH_TEST is disabled when they're being rendered */
#define RSGL_POINTS_2D                               0x0010
#define RSGL_LINES_2D                                0x0011    
#define RSGL_LINE_LOOP_2D                            0x0012
#define RSGL_LINE_STRIP_2D                           0x0013
#define RSGL_TRIANGLES_2D                            0x0014     
#define RSGL_TRIANGLE_STRIP_2D                       0x0015
#define RSGL_TRIANGLE_FAN_2D                         0x0016

#define RSGL_TRIANGLES_2D_BLEND     0x0114
#endif

/* 
keys = 
RGFW_{key} 

keys will not be reincluded into RSGL
*/

#ifndef RSGL_H
#define RSGL_H

#ifndef RSGLDEF
#ifdef __APPLE__
#define RSGLDEF extern inline
#else
#define RSGLDEF inline
#endif
#endif

#define RGFWDEF RSGLDEF

#if !defined(u8)
    #include <stdint.h>

    typedef uint8_t     u8;
	typedef int8_t      i8;
	typedef uint16_t   u16;
	typedef int16_t    i16;
	typedef uint32_t   u32;
	typedef int32_t    i32;
	typedef uint64_t   u64;
	typedef int64_t    i64;
#endif

#define RSGL_between(x, lower, upper) (((lower) <= (x)) && ((x) <= (upper)))
#define RSGL_ENUM(type, name) type name; enum

/* 
*******
RSGL_[shape]
*******
*/

typedef struct RSGL_rect {
    i32 x, y, w, h;
} RSGL_rect;
#define RSGL_RECT(x, y, w, h) (RSGL_rect){x, y, w, h}

typedef struct RSGL_rectF { float x, y, w, h; } RSGL_rectF;
#define RSGL_RECTF(x, y, w, h) (RSGL_rectF){x, y, w, h}

typedef struct RSGL_point {
    i32 x, y;
} RSGL_point;
#define RSGL_POINT(x, y) (RSGL_point){x, y}

typedef struct RSGL_area {
    u32 w, h;
} RSGL_area;
#define RSGL_AREA(w, h) (RSGL_area){w, h}

/*  include RGFW here  */

#ifndef RSGL_NO_RGFW
/* so we're only using one kind of shape data */
#define RGFW_rect RSGL_rect
#define RGFW_vector RSGL_point
#define RGFW_area RSGL_area
#define GL_SILENCE_DEPRECATION
#ifndef RSGL_NO_DEPS_FOLDER
/*
* Copyright (C) 2023-24 ColleagueRiley
*
* libpng license
*
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
*
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
*
* 1. The origin of this software must not be misrepresented; you must not
*    claim that you wrote the original software. If you use this software
*    in a product, an acknowledgment in the product documentation would be
*    appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
*    misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
*
*
*/

/*
	(MAKE SURE RGFW_IMPLEMENTATION is in exactly one header or you use -D RGFW_IMPLEMENTATION)
	#define RGFW_IMPLEMENTATION - makes it so source code is included with header
*/

/*
	#define RGFW_IMPLEMENTATION - (required) makes it so the source code is included
	#define RGFW_PRINT_ERRORS - (optional) makes it so RGFW prints errors when they're found
	#define RGFW_OSMESA - (optional) use OSmesa as backend (instead of system's opengl api + regular opengl)
	#define RGFW_BUFFER - (optional) just draw directly to (RGFW) window pixel buffer that is drawn to screen (the buffer is in the RGBA format)
	#define RGFW_EGL - (optional) use EGL for loading an OpenGL context (instead of the system's opengl api)
	#define RGFW_OPENGL_ES1 - (optional) use EGL to load and use Opengl ES (version 1) for backend rendering (instead of the system's opengl api)
									This version doesn't work for desktops (I'm pretty sure)
	#define RGFW_OPENGL_ES2 - (optional) use OpenGL ES (version 2)
	#define RGFW_OPENGL_ES3 - (optional) use OpenGL ES (version 3)
	#define RGFW_VULKAN - (optional) use vulkan for the rendering backend (rather than opengl)
	#define RGFW_DIRECTX - (optional) use directX for the rendering backend (rather than opengl) (windows only, defaults to opengl for unix)
	#define RGFW_NO_API - (optional) don't use any rendering API (no opengl, no vulkan, no directX)

	#define RGFW_LINK_EGL (optional) (windows only) if EGL is being used, if EGL functions should be defined dymanically (using GetProcAddress)
	#define RGFW_LINK_OSMESA (optional) (windows only) if EGL is being used, if OS Mesa functions should be defined dymanically  (using GetProcAddress)

	#define RGFW_X11 (optional) (unix only) if X11 should be used. This option is turned on by default by unix systems except for MacOS
	#define RGFW_WGL_LOAD (optional) (windows only) if WGL should be loaded dynamically during runtime
	#define RGFW_NO_X11_CURSOR (optional) (unix only) don't use XCursor
	#define RGFW_NO_X11_CURSOR_PRELOAD (optional) (unix only) Use XCursor, but don't link it in code, (you'll have to link it with -lXcursor)

	#define RGFW_NO_DPI - Do not include calculate DPI (no XRM nor libShcore included)

	#define RGFW_ALLOC_DROPFILES (optional) if room should be allocating for drop files (by default it's global data)
	#define RGFW_MALLOC x - choose what function to use to allocate, by default the standard malloc is used
	#define RGFW_CALLOC x - choose what function to use to allocate (calloc), by default the standard calloc is used
	#define RGFW_FREE x - choose what function to use to allocated memory, by default the standard free is used
*/

/*
	Credits :
		EimaMei/Sacode : Much of the code for creating windows using winapi, Wrote the Silicon library, helped with MacOS Support

		stb - This project is heavily inspired by the stb single header files

		GLFW:
			certain parts of winapi and X11 are very poorly documented,
			GLFW's source code was referenced and used throughout the project (used code is marked in some way),
			this mainly includes, code for drag and drops, code for setting the icon to a bitmap and the code for managing the clipboard for X11 (as these parts are not documented very well)

			GLFW Copyright, https::/github.com/GLFW/GLFW

			Copyright (c) 2002-2006 Marcus Geelnard
			Copyright (c) 2006-2019 Camilla Löwy
*/

#ifndef RGFW_MALLOC
#include <stdlib.h>
#include <time.h>
#define RGFW_MALLOC malloc
#define RGFW_CALLOC calloc
#define RGFW_FREE free
#endif

#if !_MSC_VER
#ifndef inline
#ifndef __APPLE__
#define inline __inline
#endif
#endif
#endif

#ifndef RGFWDEF
#ifdef __APPLE__
#define RGFWDEF static inline
#else
#define RGFWDEF inline
#endif
#endif

#ifndef RGFW_UNUSED
#define RGFW_UNUSED(x) if (x){}
#endif

#ifdef __cplusplus
extern "C" {
#endif

	/* makes sure the header file part is only defined once by default */
#ifndef RGFW_HEADER

#define RGFW_HEADER

#if !defined(u8)
	#include <stdint.h>

	typedef uint8_t     u8;
	typedef int8_t      i8;
	typedef uint16_t   u16;
	typedef int16_t    i16;
	typedef uint32_t   u32;
	typedef int32_t    i32;
	typedef uint64_t   u64;
	typedef int64_t    i64;
#endif

#if defined(RGFW_X11) && defined(__APPLE__)
#define RGFW_MACOS_X11
#undef __APPLE__
#endif

#if defined(_WIN32) && !defined(RGFW_X11) /* (if you're using X11 on windows some how) */

	/* this name looks better */
	/* plus it helps with cross-compiling because RGFW_X11 won't be accidently defined */
	
#define RGFW_WINDOWS

#if defined(_WIN32) && !defined(WIN32)
#define WIN32
#endif

#if defined(_WIN64)

#ifndef WIN64
#define WIN64
#endif

#define _AMD64_
#undef _X86_
#else
#undef _AMD64_
#define _X86_
#endif

#include <windef.h>

#else 
#if defined(__unix__) || defined(RGFW_MACOS_X11) || defined(RGFW_X11)
#define RGFW_MACOS_X11
#define RGFW_X11
#include <X11/Xlib.h>
#endif
#endif 	

#if defined(__APPLE__) && !defined(RGFW_MACOS_X11) && !defined(RGFW_X11)
#define RGFW_MACOS
#endif

#if (defined(RGFW_OPENGL_ES1) || defined(RGFW_OPENGL_ES2) || defined(RGFW_OPENGL_ES3)) && !defined(RGFW_EGL)
#define RGFW_EGL
#endif
#if defined(RGFW_EGL) && defined(__APPLE__)
	#warning  EGL is not supported for Cocoa, switching back to the native opengl api
#undef RGFW_EGL
#endif

#if !defined(RGFW_OSMESA) && !defined(RGFW_EGL) && !defined(RGFW_OPENGL) && !defined (RGFW_VULKAN) && !defined(RGFW_DIRECTX) && !defined(RGFW_BUFFER) && !defined(RGFW_NO_API)
#define RGFW_OPENGL
#endif

#ifdef RGFW_VULKAN
#ifndef RGFW_MAX_FRAMES_IN_FLIGHT
#define RGFW_MAX_FRAMES_IN_FLIGHT 2
#endif

#ifdef RGFW_X11
#define VK_USE_PLATFORM_XLIB_KHR
#endif
#ifdef RGFW_WINDOWS
#define VK_USE_PLATFORM_WIN32_KHR
#endif
#ifdef RGFW_MACOS
#define VK_USE_PLATFORM_MACOS_MVK
#endif

#include <vulkan/vulkan.h>
#endif

#if defined(RGFW_X11) && (defined(RGFW_OPENGL))
#ifndef GLX_MESA_swap_control
#define  GLX_MESA_swap_control
#endif
#include <GL/glx.h> /* GLX defs, xlib.h, gl.h */
#endif

#ifdef RGFW_EGL
#include <EGL/egl.h>
#endif

#ifdef RGFW_OSMESA
#ifndef __APPLE__
#include <GL/osmesa.h>
#else
#include <OpenGL/osmesa.h>
#endif
#endif

#if defined(RGFW_DIRECTX) && defined(RGFW_WINDOWS)
#include <d3d11.h>
#include <dxgi.h>
#include <dxgi.h>
#include <d3dcompiler.h>

#ifndef __cplusplus
#define __uuidof(T) IID_##T
#endif
#endif

		/*! Optional arguments for making a windows */
#define RGFW_TRANSPARENT_WINDOW		(1L<<9) /*!< the window is transparent */
#define RGFW_NO_BORDER		(1L<<3) /*!< the window doesn't have border */
#define RGFW_NO_RESIZE		(1L<<4) /*!< the window cannot be resized  by the user */
#define RGFW_ALLOW_DND     (1L<<5) /*!< the window supports drag and drop*/
#define RGFW_HIDE_MOUSE (1L<<6) /*! the window should hide the mouse or not (can be toggled later on) using `RGFW_window_mouseShow*/
#define RGFW_FULLSCREEN (1L<<8) /* the window is fullscreen by default or not */
#define RGFW_CENTER (1L<<10) /*! center the window on the screen */
#define RGFW_OPENGL_SOFTWARE (1L<<11) /*! use OpenGL software rendering */
#define RGFW_COCOA_MOVE_TO_RESOURCE_DIR (1L << 12) /* (cocoa only), move to resource folder */
#define RGFW_SCALE_TO_MONITOR (1L << 13) /* scale the window to the screen */

#define RGFW_NO_GPU_RENDER (1L<<14) /* don't render (using the GPU based API)*/
#define RGFW_NO_CPU_RENDER (1L<<15) /* don't render (using the CPU based buffer rendering)*/


/*! event codes */
#define RGFW_keyPressed 2 /* a key has been pressed */
#define RGFW_keyReleased 3 /*!< a key has been released*/
/*! key event note
	the code of the key pressed is stored in
	RGFW_Event.keyCode
	!!Keycodes defined at the bottom of the header file!!

	while a string version is stored in
	RGFW_Event.KeyString

	RGFW_Event.lockState holds the current lockState
	this means if CapsLock, NumLock are active or not
*/
#define RGFW_mouseButtonPressed 4 /*!< a mouse button has been pressed (left,middle,right)*/
#define RGFW_mouseButtonReleased 5 /*!< a mouse button has been released (left,middle,right)*/
#define RGFW_mousePosChanged 6 /*!< the position of the mouse has been changed*/
/*! mouse event note
	the x and y of the mouse can be found in the vector, RGFW_Event.point

	RGFW_Event.button holds which mouse button was pressed
*/
#define RGFW_jsButtonPressed 7 /*!< a joystick button was pressed */
#define RGFW_jsButtonReleased 8 /*!< a joystick button was released */
#define RGFW_jsAxisMove 9 /*!< an axis of a joystick was moved*/
/*! joystick event note
	RGFW_Event.joystick holds which joystick was altered, if any
	RGFW_Event.button holds which joystick button was pressed

	RGFW_Event.axis holds the data of all the axis
	RGFW_Event.axisCount says how many axis there are
*/
#define RGFW_windowAttribsChange 10 /*!< the window was moved or resized (by the user) */
/* attribs change event note
	The event data is sent straight to the window structure
	with win->r.x, win->r.y, win->r.w and win->r.h
*/
#define RGFW_quit 33 /*!< the user clicked the quit button*/ 
#define RGFW_dnd 34 /*!< a file has been dropped into the window*/
#define RGFW_dnd_init 35 /*!< the start of a dnd event, when the place where the file drop is known */
/* dnd data note
	The x and y coords of the drop are stored in the vector RGFW_Event.point

	RGFW_Event.droppedFilesCount holds how many files were dropped

	This is also the size of the array which stores all the dropped file string,
	RGFW_Event.droppedFiles
*/

/*! mouse button codes (RGFW_Event.button) */
#define RGFW_mouseLeft  1 /*!< left mouse button is pressed*/
#define RGFW_mouseMiddle  2 /*!< mouse-wheel-button is pressed*/
#define RGFW_mouseRight  3 /*!< right mouse button is pressed*/
#define RGFW_mouseScrollUp  4 /*!< mouse wheel is scrolling up*/
#define RGFW_mouseScrollDown  5 /*!< mouse wheel is scrolling down*/

#ifndef RGFW_MAX_PATH
#define RGFW_MAX_PATH 260 /* max length of a path (for dnd) */
#endif
#ifndef RGFW_MAX_DROPS
#define RGFW_MAX_DROPS 260 /* max items you can drop at once */
#endif


/* for RGFW_Event.lockstate */
#define RGFW_CAPSLOCK (1L << 1)
#define RGFW_NUMLOCK (1L << 2)

/*! joystick button codes (based on xbox/playstation), you may need to change these values per controller */
#ifndef RGFW_JS_A

#define RGFW_JS_A 0 /* or PS X button */
#define RGFW_JS_B 1 /* or PS circle button */
#define RGFW_JS_Y 2 /* or PS triangle button */
#define RGFW_JS_X 3 /* or PS square button */
#define RGFW_JS_START 9 /* start button */
#define RGFW_JS_SELECT 8 /* select button */
#define RGFW_JS_HOME 10 /* home button */
#define RGFW_JS_UP 13 /* dpad up */
#define RGFW_JS_DOWN 14 /* dpad down*/
#define RGFW_JS_LEFT 15 /* dpad left */
#define RGFW_JS_RIGHT 16 /* dpad right */
#define RGFW_JS_L1 4 /* left bump */
#define RGFW_JS_L2 5 /* left trigger*/
#define RGFW_JS_R1 6 /* right bumper */
#define RGFW_JS_R2 7 /* right trigger */

#endif

/* basic vector type, if there's not already a point/vector type of choice */
#ifndef RGFW_vector
typedef struct { i32 x, y; } RGFW_vector;
#endif

	/* basic rect type, if there's not already a rect type of choice */
#ifndef RGFW_rect
	typedef struct { i32 x, y, w, h; } RGFW_rect;
#endif

	/* basic area type, if there's not already a area type of choice */
#ifndef RGFW_area
	typedef struct { u32 w, h; } RGFW_area;
#endif

#define RGFW_VECTOR(x, y) (RGFW_vector){x, y}
#define RGFW_RECT(x, y, w, h) (RGFW_rect){x, y, w, h}
#define RGFW_AREA(w, h) (RGFW_area){w, h}

	typedef struct RGFW_monitor {
		char name[128];  /* monitor name */
		RGFW_rect rect; /* monitor Workarea */
		float scaleX, scaleY; /* monitor content scale*/
		float physW, physH; /* monitor physical size */
	} RGFW_monitor;

	/*
	NOTE : Monitor functions should be ran only as many times as needed (not in a loop)
	*/

	/* get an array of all the monitors (max 6) */
	RGFWDEF RGFW_monitor* RGFW_getMonitors(void);
	/* get the primary monitor */
	RGFWDEF RGFW_monitor RGFW_getPrimaryMonitor(void);

	/* NOTE: some parts of the data can represent different things based on the event (read comments in RGFW_Event struct) */
	typedef struct RGFW_Event {
#ifdef RGFW_WINDOWS
		char keyName[16]; /* key name of event*/
#else
		char* keyName; /*!< key name of event */
#endif

		/*! drag and drop data */
		/* 260 max paths with a max length of 260 */
#ifdef RGFW_ALLOC_DROPFILES
		char** droppedFiles;
#else
		char droppedFiles[RGFW_MAX_DROPS][RGFW_MAX_PATH]; /*!< dropped files*/
#endif
		u32 droppedFilesCount; /*!< house many files were dropped */

		u32 type; /*!< which event has been sent?*/
		RGFW_vector point; /*!< mouse x, y of event (or drop point) */
		u32 keyCode; /*!< keycode of event 	!!Keycodes defined at the bottom of the header file!! */

		u32 fps; /*the current fps of the window [the fps is checked when events are checked]*/
		u64 frameTime, frameTime2; /* this is used for counting the fps */

		u8 inFocus;  /*if the window is in focus or not*/

		u8 lockState;

		u16 joystick; /* which joystick this event applies to (if applicable to any) */

		u8 button; /*!< which mouse button has been clicked (0) left (1) middle (2) right OR which joystick button was pressed*/
		double scroll; /* the raw mouse scroll value */

		u8 axisesCount; /* number of axises */
		RGFW_vector axis[2]; /* x, y of axises (-100 to 100) */
	} RGFW_Event; /*!< Event structure for checking/getting events */

	/* source data for the window (used by the APIs) */
	typedef struct RGFW_window_src {
#ifdef RGFW_WINDOWS
		HWND window; /*!< source window */
		HDC hdc; /*!< source HDC */
		u32 hOffset; /*!< height offset for window */
#endif
#ifdef RGFW_X11
		Display* display; /*!< source display */
		Window window; /*!< source window */
		Cursor cursor;
#endif
#ifdef RGFW_MACOS
		u32 display;
		void* displayLink;
		void* window;
		u8 dndPassed;
#endif

#if (defined(RGFW_OPENGL)) && !defined(RGFW_OSMESA)
#ifdef RGFW_MACOS
		void* rSurf; /*!< source graphics context */
#endif
#ifdef RGFW_WINDOWS
		HGLRC rSurf; /*!< source graphics context */
#endif
#ifdef RGFW_X11
		GLXContext rSurf; /*!< source graphics context */
#endif
#else
#ifdef RGFW_VULKAN
		VkSurfaceKHR rSurf; /*!< source graphics context */

		/* vulkan data */
		VkSwapchainKHR swapchain;
		u32 image_count;
		VkImage* swapchain_images;
		VkImageView* swapchain_image_views;
#endif

#ifdef RGFW_OSMESA
		OSMesaContext rSurf;
#endif
#endif

#ifdef RGFW_WINDOWS
		RGFW_area maxSize, minSize;
#if defined(RGFW_DIRECTX)
		IDXGISwapChain* swapchain;
		ID3D11RenderTargetView* renderTargetView;
		ID3D11DepthStencilView* pDepthStencilView;
#endif
#endif

#if defined(RGFW_MACOS) && !defined(RGFW_MACOS_X11)
		void* view; /*apple viewpoint thingy*/
#endif

#ifdef RGFW_EGL
		EGLSurface EGL_surface;
		EGLDisplay EGL_display;
		EGLContext EGL_context;
#endif

#if defined(RGFW_OSMESA) || defined(RGFW_BUFFER) 
#ifdef RGFW_WINDOWS
		HBITMAP bitmap;
#endif
#ifdef RGFW_X11
		XImage* bitmap;
#endif
#ifdef RGFW_MACOS
		void* bitmap; /* API's bitmap for storing or managing */
		void* image;
#endif
#if defined(RGFW_BUFFER) && defined(RGFW_WINDOWS)
		HDC hdcMem; /* window stored in memory that winapi needs to render buffers */
#endif
#endif

		u8 jsPressed[4][16]; /* if a key is currently pressed or not (per joystick) */

		i32 joysticks[4]; /* limit of 4 joysticks at a time */
		u16 joystickCount; /* the actual amount of joysticks */

		RGFW_area scale; /* window scaling */

#ifdef RGFW_MACOS
		u8 cursorChanged; /* for steve jobs */
#endif

		u32 winArgs; /* windows args (for RGFW to check) */
		/*
			!< if dnd is enabled or on (based on window creating args)
			cursorChanged
		*/
	} RGFW_window_src;

	typedef struct RGFW_window {
		RGFW_window_src src;

#if defined(RGFW_OSMESA) || defined(RGFW_BUFFER) 
		u8* buffer; /* buffer for non-GPU systems (OSMesa, basic software rendering) */
		/* when rendering using RGFW_BUFFER, the buffer is in the RGBA format */
#endif

		RGFW_Event event; /*!< current event */

		RGFW_rect r; /* the x, y, w and h of the struct */

		u32 fpsCap; /*!< the fps cap of the window should run at (change this var to change the fps cap, 0 = no limit)*/
		/*[the fps is capped when events are checked]*/
	} RGFW_window; /*!< Window structure for managing the window */

#if defined(RGFW_X11) || defined(RGFW_MACOS)
	typedef u64 RGFW_thread; /* thread type unix */
#else
	typedef void* RGFW_thread; /* thread type for window */
#endif

	RGFW_window* RGFW_createWindow(
		const char* name, /* name of the window */
		RGFW_rect rect, /* rect of window */
		u16 args /* extra arguments (NULL / (u16)0 means no args used)*/
	); /*!< function to create a window struct */

	/* get the size of the screen to an area struct */
	RGFWDEF RGFW_area RGFW_getScreenSize(void);

	/*
		this function checks an *individual* event (and updates window structure attributes)
		this means, using this function without a while loop may cause event lag

		ex.

		while (RGFW_window_checkEvent(win) != NULL) [this keeps checking events until it reaches the last one]
	*/

	RGFW_Event* RGFW_window_checkEvent(RGFW_window* win); /*!< check events (returns a pointer to win->event or NULL if there is no event)*/

	/*! window managment functions*/
	RGFWDEF void RGFW_window_close(RGFW_window* win); /*!< close the window and free leftover data */

	RGFWDEF void RGFW_window_move(RGFW_window* win,
		RGFW_vector v/* new pos*/
	);

	/* move to a specific monitor */
	RGFWDEF void RGFW_window_moveToMonitor(RGFW_window* win, RGFW_monitor m);

	RGFWDEF void RGFW_window_resize(RGFW_window* win,
		RGFW_area a/* new size*/
	);

	/* set the minimum size a user can shrink a window */
	RGFWDEF void RGFW_window_setMinSize(RGFW_window* win, RGFW_area a);
	/* set the minimum size a user can extend a window */
	RGFWDEF void RGFW_window_setMaxSize(RGFW_window* win, RGFW_area a);

	RGFWDEF void RGFW_window_maximize(RGFW_window* win); /* maximize the window size */
	RGFWDEF void RGFW_window_minimize(RGFW_window* win); /* minimize the window (in taskbar (per OS))*/
	RGFWDEF void RGFW_window_restore(RGFW_window* win); /* restore the window from minimized (per OS)*/

	RGFWDEF void RGFW_window_setName(RGFW_window* win,
		char* name
	);

	void RGFW_window_setIcon(RGFW_window* win, /*!< source window */
		u8* icon /*!< icon bitmap */,
		RGFW_area a /*!< width and height of the bitmap*/,
		i32 channels /*!< how many channels the bitmap has (rgb : 3, rgba : 4) */
	); /*!< image resized by default */

	/*!< sets mouse to bitmap (very simular to RGFW_window_setIcon), image NOT resized by default*/
	RGFWDEF void RGFW_window_setMouse(RGFW_window* win, u8* image, RGFW_area a, i32 channels);

	/*!< sets the mouse to a standard API cursor (based on RGFW_MOUSE, as seen at the end of the file) */
#ifdef RGFW_MACOS
	RGFWDEF void RGFW_window_setMouseStandard(RGFW_window* win, void* mouse);
#else
	RGFWDEF	void RGFW_window_setMouseStandard(RGFW_window* win, i32 mouse);
#endif

	RGFWDEF void RGFW_window_setMouseDefault(RGFW_window* win); /* sets the mouse to1` the default mouse image */
	/*
		holds the mouse in place by moving the mouse back each time it moves
		you can still use win->event.point to see how much it moved before it was put back in place

		this is useful for a 3D camera
	*/
	RGFWDEF void RGFW_window_mouseHold(RGFW_window* win);
	/* undo hold */
	RGFWDEF void RGFW_window_mouseUnhold(RGFW_window* win);

	/* hide the window */
	RGFWDEF void RGFW_window_hide(RGFW_window* win);
	/* show the window */
	RGFWDEF void RGFW_window_show(RGFW_window* win);

	/*
		makes it so `RGFW_window_shouldClose` returns true
		by setting the window event.type to RGFW_quit
	*/
	RGFWDEF void RGFW_window_setShouldClose(RGFW_window* win);

	/* where the mouse is on the screen */
	RGFWDEF RGFW_vector RGFW_getGlobalMousePoint(void);

	/* where the mouse is on the window */
	RGFWDEF RGFW_vector RGFW_window_getMousePoint(RGFW_window* win);

	/* show the mouse or hide the mouse*/
	RGFWDEF void RGFW_window_showMouse(RGFW_window* win, i8 show);
	/* move the mouse to a set x, y pos*/
	RGFWDEF void RGFW_window_moveMouse(RGFW_window* win, RGFW_vector v);

	/* if the window should close (RGFW_close was sent or escape was pressed) */
	RGFWDEF u8 RGFW_window_shouldClose(RGFW_window* win);
	/* if window is fullscreen'd */
	RGFWDEF u8 RGFW_window_isFullscreen(RGFW_window* win);
	/* if window is hidden */
	RGFWDEF u8 RGFW_window_isHidden(RGFW_window* win);
	/* if window is minimized */
	RGFWDEF u8 RGFW_window_isMinimized(RGFW_window* win);
	/* if window is maximized */
	RGFWDEF u8 RGFW_window_isMaximized(RGFW_window* win);

	/*
	scale the window to the monitor,
	this is run by default if the user uses the arg `RGFW_SCALE_TO_MONITOR` during window creation
	*/
	RGFWDEF void RGFW_window_scaleToMonitor(RGFW_window* win);
	/* get the struct of the window's monitor  */
	RGFWDEF RGFW_monitor RGFW_window_getMonitor(RGFW_window* win);

	/*!< make the window the current opengl drawing context */
	RGFWDEF void RGFW_window_makeCurrent(RGFW_window* win);

	/*error handling*/
	RGFWDEF u8 RGFW_Error(void); /* returns true if an error has occurred (doesn't print errors itself) */

	/*!< if window == NULL, it checks if the key is pressed globally. Otherwise, it checks only if the key is pressed while the window in focus.*/
	RGFWDEF u8 RGFW_isPressedI(RGFW_window* win, u32 key); /*!< if key is pressed (key code)*/

	RGFWDEF u8 RGFW_wasPressedI(RGFW_window* win, u32 key); /*!< if key was pressed (checks prev keymap only) (key code)*/

	RGFWDEF u8 RGFW_isHeldI(RGFW_window* win, u32 key); /*!< if key is held (key code)*/
	RGFWDEF u8 RGFW_isReleasedI(RGFW_window* win, u32 key); /*!< if key is released (key code)*/

	RGFWDEF u8 RGFW_isMousePressed(RGFW_window* win, u8 button);
	RGFWDEF u8 RGFW_isMouseHeld(RGFW_window* win, u8 button);
	RGFWDEF u8 RGFW_isMouseReleased(RGFW_window* win, u8 button);
	RGFWDEF u8 RGFW_wasMousePressed(RGFW_window* win, u8 button);

	/*
		!!Keycodes defined at the bottom of the header file!!
	*/
	/*!< converts a key code to it's key string */
	RGFWDEF char* RGFW_keyCodeTokeyStr(u64 key);
	/*!< converts a string of a key to it's key code */
	RGFWDEF u32 RGFW_keyStrToKeyCode(char* key);
	/*!< if key is pressed (key string) */
#define RGFW_isPressedS(win, key) RGFW_isPressedI(win, RGFW_keyStrToKeyCode(key))

/*! clipboard functions*/
	RGFWDEF char* RGFW_readClipboard(size_t* size); /*!< read clipboard data */
#define RGFW_clipboardFree free /* the string returned from RGFW_readClipboard must be freed */

	RGFWDEF void RGFW_writeClipboard(const char* text, u32 textLen); /*!< write text to the clipboard */

	/*
		convert a keyString to a char version
	*/
	RGFWDEF char RGFW_keystrToChar(const char*);
	/*
		ex.
		"parenleft" -> '('
		"A" -> 'A',
		"Return" -> "\n"
	*/

#ifndef RGFW_NO_THREADS
	/*! threading functions*/

	/*! NOTE! (for X11/linux) : if you define a window in a thread, it must be run after the original thread's window is created or else there will be a memory error */
	/*
		I'd suggest you use sili's threading functions instead
		if you're going to use sili
		which is a good idea generally
	*/

	#if defined(__unix__) || defined(__APPLE__) 
	typedef void* (* RGFW_threadFunc_ptr)(void*);
	#else
	typedef DWORD (* RGFW_threadFunc_ptr)(void*);
	#endif

	RGFWDEF RGFW_thread RGFW_createThread(RGFW_threadFunc_ptr ptr, void* args); /*!< create a thread*/
	RGFWDEF void RGFW_cancelThread(RGFW_thread thread); /*!< cancels a thread*/
	RGFWDEF void RGFW_joinThread(RGFW_thread thread); /*!< join thread to current thread */
	RGFWDEF void RGFW_setThreadPriority(RGFW_thread thread, u8 priority); /*!< sets the priority priority  */
#endif

	/*! gamepad/joystick functions (linux-only currently) */

	/*! joystick count starts at 0*/
	/*!< register joystick to window based on a number (the number is based on when it was connected eg. /dev/js0)*/
	RGFWDEF u16 RGFW_registerJoystick(RGFW_window* win, i32 jsNumber);
	RGFWDEF u16 RGFW_registerJoystickF(RGFW_window* win, char* file);

	RGFWDEF u32 RGFW_isPressedJS(RGFW_window* win, u16 controller, u8 button);

	/*! native opengl functions */
#ifdef RGFW_OPENGL
/*! Get max OpenGL version */
	RGFWDEF u8* RGFW_getMaxGLVersion(void);
	/* OpenGL init hints */
	RGFWDEF void RGFW_setGLStencil(i32 stencil); /* set stencil buffer bit size (8 by default) */
	RGFWDEF void RGFW_setGLSamples(i32 samples); /* set number of sampiling buffers (4 by default) */
	RGFWDEF void RGFW_setGLStereo(i32 stereo); /* use GL_STEREO (GL_FALSE by default) */
	RGFWDEF void RGFW_setGLAuxBuffers(i32 auxBuffers); /* number of aux buffers (0 by default) */

	/*! Set OpenGL version hint */
	RGFWDEF void RGFW_setGLVersion(i32 major, i32 minor);
	RGFWDEF void* RGFW_getProcAddress(const char* procname); /* get native opengl proc address */
#endif
	/* supports openGL, directX, OSMesa, EGL and software rendering */
	RGFWDEF void RGFW_window_swapBuffers(RGFW_window* win); /* swap the rendering buffer */
	RGFWDEF void RGFW_window_swapInterval(RGFW_window* win, i32 swapInterval);

	RGFWDEF void RGFW_window_setGPURender(RGFW_window* win, i8 set);

#ifdef RGFW_VULKAN
	typedef struct {
		VkInstance instance;
		VkPhysicalDevice physical_device;
		VkDevice device;

		VkDebugUtilsMessengerEXT debugMessenger;

		VkQueue graphics_queue;
		VkQueue present_queue;

		VkFramebuffer* framebuffers;

		VkRenderPass render_pass;
		VkPipelineLayout pipeline_layout;
		VkPipeline graphics_pipeline;

		VkCommandPool command_pool;
		VkCommandBuffer* command_buffers;

		VkSemaphore* available_semaphores;
		VkSemaphore* finished_semaphore;
		VkFence* in_flight_fences;
		VkFence* image_in_flight;
		size_t current_frame;
	} RGFW_vulkanInfo;

	/*! initializes a vulkan rendering context for the RGFW window,
		this outputs the vulkan surface into wwin->src.rSurf
		other vulkan data is stored in the global instance of the RGFW_vulkanInfo structure which is returned
		by the initVulkan() function
		RGFW_VULKAN must be defined for this function to be defined

	*/
	RGFWDEF RGFW_vulkanInfo* RGFW_initVulkan(RGFW_window* win);
	RGFWDEF void RGFW_freeVulkan(void);

	RGFWDEF RGFW_vulkanInfo* RGFW_getVulkanInfo(void);

	RGFWDEF int RGFW_initData(RGFW_window* win);
	RGFWDEF void RGFW_createSurface(VkInstance instance, RGFW_window* win);
	int RGFW_deviceInitialization(RGFW_window* win);
	int RGFW_createSwapchain(RGFW_window* win);
	RGFWDEF int RGFW_createRenderPass(void);
	int RGFW_createCommandPool(void);
	int RGFW_createCommandBuffers(RGFW_window* win);
	int RGFW_createSyncObjects(RGFW_window* win);
	RGFWDEF int RGFW_createFramebuffers(RGFW_window* win);
#endif

#ifdef RGFW_DIRECTX
	typedef struct {
		IDXGIFactory* pFactory;
		IDXGIAdapter* pAdapter;
		ID3D11Device* pDevice;
		ID3D11DeviceContext* pDeviceContext;
	} RGFW_directXinfo;

	/*
		RGFW stores a global instance of RGFW_directXinfo,
		you can use this function to get a pointer the instance
	*/
	RGFWDEF RGFW_directXinfo* RGFW_getDirectXInfo(void);
#endif

	/*! Supporting functions */
	RGFWDEF void RGFW_window_checkFPS(RGFW_window* win); /*!< updates fps / sets fps to cap (ran by RGFW_window_checkEvent)*/
	RGFWDEF u64 RGFW_getTime(void); /* get time in seconds */
	RGFWDEF u64 RGFW_getTimeNS(void); /* get time in nanoseconds */
	RGFWDEF void RGFW_sleep(u64 microsecond); /* sleep for a set time */
#endif /* RGFW_HEADER */

	/*
	Example to get you started :

	linux : gcc main.c -lX11 -lXcursor -lGL
	windows : gcc main.c -lopengl32 -lshell32 -lgdi32
	macos : gcc main.c -framework Foundation -framework AppKit -framework OpenGL -framework CoreVideo

	#define RGFW_IMPLEMENTATION
	#include "RGFW.h"

	u8 icon[4 * 3 * 3] = {0xFF, 0x00, 0x00, 0xFF,    0xFF, 0x00, 0x00, 0xFF,     0xFF, 0x00, 0x00, 0xFF,   0xFF, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0xFF,     0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF};

	int main() {
		RGFW_window* win = RGFW_createWindow("name", RGFW_RECT(500, 500, 500, 500), (u64)0);

		RGFW_window_setIcon(win, icon, RGFW_AREA(3, 3), 4);

		for (;;) {
			RGFW_window_checkEvent(win); // NOTE: checking events outside of a while loop may cause input lag
			if (win->event.type == RGFW_quit || RGFW_isPressedI(win, RGFW_Escape))
				break;

			RGFW_window_swapBuffers(win);

			glClearColor(0xFF, 0XFF, 0xFF, 0xFF);
			glClear(GL_COLOR_BUFFER_BIT);
		}

		RGFW_window_close(win);
	}

		compiling :

		if you wish to compile the library all you have to do is create a new file with this in it

		rgfw.c
		#define RGFW_IMPLEMENTATION
		#include "RGFW.h"

		then you can use gcc (or whatever compile you wish to use) to compile the library into object file

		ex. gcc -c RGFW.c -fPIC

		after you compile the library into an object file, you can also turn the object file into an static or shared library

		(commands ar and gcc can be replaced with whatever equivalent your system uses)
		static : ar rcs RGFW.a RGFW.o
		shared :
			windows:
				gcc -shared RGFW.o -lopengl32 -lshell32 -lgdi32 -o RGFW.dll
			linux:
				gcc -shared RGFW.o -lX11 -lXcursor -lGL -o RGFW.so
			macos:
				gcc -shared RGFW.o -framework Foundation -framework AppKit -framework OpenGL -framework CoreVideo
	*/

#ifdef RGFW_X11
#define RGFW_OS_BASED_VALUE(l, w, m) l
#endif
#ifdef RGFW_WINDOWS
#define RGFW_OS_BASED_VALUE(l, w, m) w
#endif
#ifdef RGFW_MACOS
#define RGFW_OS_BASED_VALUE(l, w, m) m
#endif

#define RGFW_Escape RGFW_OS_BASED_VALUE(0xff1b, 0x1B, 53)
#define RGFW_F1 RGFW_OS_BASED_VALUE(0xffbe, 0x70, 127)
#define RGFW_F2 RGFW_OS_BASED_VALUE(0xffbf, 0x71, 121)
#define RGFW_F3 RGFW_OS_BASED_VALUE(0xffc0, 0x72, 100)
#define RGFW_F4 RGFW_OS_BASED_VALUE(0xffc1, 0x73, 119)
#define RGFW_F5 RGFW_OS_BASED_VALUE(0xffc2, 0x74, 97)
#define RGFW_F6 RGFW_OS_BASED_VALUE(0xffc3, 0x75, 98)
#define RGFW_F7 RGFW_OS_BASED_VALUE(0xffc4, 0x76, 99)
#define RGFW_F8 RGFW_OS_BASED_VALUE(0xffc5, 0x77, 101)
#define RGFW_F9 RGFW_OS_BASED_VALUE(0xffc6, 0x78, 102)
#define RGFW_F10 RGFW_OS_BASED_VALUE(0xffc7, 0x79, 110)
#define RGFW_F11 RGFW_OS_BASED_VALUE(0xffc8, 0x7A, 104)
#define RGFW_F12 RGFW_OS_BASED_VALUE(0xffc9, 0x7B, 112)
#define RGFW_F13 RGFW_OS_BASED_VALUE(0xffca, 0x7C, 106)
#define RGFW_F14 RGFW_OS_BASED_VALUE(0xffcb, 0x7D, 108)
#define RGFW_F15 RGFW_OS_BASED_VALUE(0xffcc, 0x7E, 114)

#define RGFW_Backtick RGFW_OS_BASED_VALUE(96 , 192, 50)

#define RGFW_0 RGFW_OS_BASED_VALUE(0x0030, 0x30, 29)
#define RGFW_1 RGFW_OS_BASED_VALUE(0x0031, 0x31, 18)
#define RGFW_2 RGFW_OS_BASED_VALUE(0x0032, 0x32, 19)
#define RGFW_3 RGFW_OS_BASED_VALUE(0x0033, 0x33, 20)
#define RGFW_4 RGFW_OS_BASED_VALUE(0x0034, 0x34, 21)
#define RGFW_5 RGFW_OS_BASED_VALUE(0x0035, 0x35, 23)
#define RGFW_6 RGFW_OS_BASED_VALUE(0x0036, 0x36, 22)
#define RGFW_7 RGFW_OS_BASED_VALUE(0x0037, 0x37, 26)
#define RGFW_8 RGFW_OS_BASED_VALUE(0x0038, 0x38, 28)
#define RGFW_9 RGFW_OS_BASED_VALUE(0x0039, 0x39, 25)

#define RGFW_Minus RGFW_OS_BASED_VALUE(0x002d, 189, 27)
#define RGFW_Equals RGFW_OS_BASED_VALUE(0x003d, 187, 24)
#define RGFW_BackSpace RGFW_OS_BASED_VALUE(0xff08, 8, 51)
#define RGFW_Tab RGFW_OS_BASED_VALUE(0xff89, 0x09, 48)
#define RGFW_CapsLock RGFW_OS_BASED_VALUE(0xffe5, 20, 57)
#define RGFW_ShiftL RGFW_OS_BASED_VALUE(0xffe1, 0xA0, 56)
#define RGFW_ControlL RGFW_OS_BASED_VALUE(0xffe3, 0x11, 59)
#define RGFW_AltL RGFW_OS_BASED_VALUE(0xffe9, 164, 58)
#define RGFW_SuperL RGFW_OS_BASED_VALUE(0xffeb, 0x5B, 55) 
#define RGFW_ShiftR RGFW_OS_BASED_VALUE(0xffe2, 0x5C, 56)
#define RGFW_ControlR RGFW_OS_BASED_VALUE(0xffe4, 0x11, 59)
#define RGFW_AltR RGFW_OS_BASED_VALUE(0xffea, 165, 58)
#define RGFW_SuperR RGFW_OS_BASED_VALUE(0xffec, 0xA4, 55)
#define RGFW_Space RGFW_OS_BASED_VALUE(0x0020,  0x20, 49)

#define RGFW_A RGFW_OS_BASED_VALUE(0x0041, 0x41, 0)
#define RGFW_B RGFW_OS_BASED_VALUE(0x0042, 0x42, 11)
#define RGFW_C RGFW_OS_BASED_VALUE(0x0043, 0x43, 8)
#define RGFW_D RGFW_OS_BASED_VALUE(0x0044, 0x44, 2)
#define RGFW_E RGFW_OS_BASED_VALUE(0x0045, 0x45, 14)
#define RGFW_F RGFW_OS_BASED_VALUE(0x0046, 0x46, 3)
#define RGFW_G RGFW_OS_BASED_VALUE(0x0047, 0x47, 5)
#define RGFW_H RGFW_OS_BASED_VALUE(0x0048, 0x48, 4) 
#define RGFW_I RGFW_OS_BASED_VALUE(0x0049, 0x49, 34)
#define RGFW_J RGFW_OS_BASED_VALUE(0x004a, 0x4A, 38)
#define RGFW_K RGFW_OS_BASED_VALUE(0x004b, 0x4B, 40)
#define RGFW_L RGFW_OS_BASED_VALUE(0x004c, 0x4C, 37)
#define RGFW_M RGFW_OS_BASED_VALUE(0x004d, 0x4D, 46)
#define RGFW_N RGFW_OS_BASED_VALUE(0x004e, 0x4E, 45)
#define RGFW_O RGFW_OS_BASED_VALUE(0x004f, 0x4F, 31)
#define RGFW_P RGFW_OS_BASED_VALUE(0x0050, 0x50, 35)
#define RGFW_Q RGFW_OS_BASED_VALUE(0x0051, 0x51, 12)
#define RGFW_R RGFW_OS_BASED_VALUE(0x0052, 0x52, 15)
#define RGFW_S RGFW_OS_BASED_VALUE(0x0053, 0x53, 1)
#define RGFW_T RGFW_OS_BASED_VALUE(0x0054, 0x54, 17)
#define RGFW_U RGFW_OS_BASED_VALUE(0x0055, 0x55, 32)
#define RGFW_V RGFW_OS_BASED_VALUE(0x0056, 0x56, 9)
#define RGFW_W RGFW_OS_BASED_VALUE(0x0057, 0x57, 13)
#define RGFW_X RGFW_OS_BASED_VALUE(0x0058, 0x58, 7)
#define RGFW_Y RGFW_OS_BASED_VALUE(0x0059, 0x59, 16)
#define RGFW_Z RGFW_OS_BASED_VALUE(0x005a, 0x5A, 6)

#define RGFW_a RGFW_OS_BASED_VALUE(0x0061, 0x41, 0)
#define RGFW_b RGFW_OS_BASED_VALUE(0x0062, 0x42, 11)
#define RGFW_c RGFW_OS_BASED_VALUE(0x0063, 0x43, 8)
#define RGFW_d RGFW_OS_BASED_VALUE(0x0064, 0x44, 2)
#define RGFW_e RGFW_OS_BASED_VALUE(0x0065, 0x45, 14)
#define RGFW_f RGFW_OS_BASED_VALUE(0x0066, 0x46, 3)
#define RGFW_g RGFW_OS_BASED_VALUE(0x0067, 0x47, 5)
#define RGFW_h RGFW_OS_BASED_VALUE(0x0068, 0x48, 4)
#define RGFW_i RGFW_OS_BASED_VALUE(0x0069, 0x49, 34)
#define RGFW_j RGFW_OS_BASED_VALUE(0x006a, 0x4a, 38)
#define RGFW_k RGFW_OS_BASED_VALUE(0x006b, 0x4b, 40)
#define RGFW_l RGFW_OS_BASED_VALUE(0x006c, 0x4c, 37)
#define RGFW_m RGFW_OS_BASED_VALUE(0x006d, 0x4d, 46)
#define RGFW_n RGFW_OS_BASED_VALUE(0x006e, 0x4e, 45)
#define RGFW_o RGFW_OS_BASED_VALUE(0x006f, 0x4f, 31)
#define RGFW_p RGFW_OS_BASED_VALUE(0x0070, 0x50, 35)
#define RGFW_q RGFW_OS_BASED_VALUE(0x0071, 0x51, 12)
#define RGFW_r RGFW_OS_BASED_VALUE(0x0072, 0x52, 15)
#define RGFW_s RGFW_OS_BASED_VALUE(0x0073, 0x53, 1)
#define RGFW_t RGFW_OS_BASED_VALUE(0x0074, 0x54, 17)
#define RGFW_u RGFW_OS_BASED_VALUE(0x0075, 0x55, 32)
#define RGFW_v RGFW_OS_BASED_VALUE(0x0076, 0x56, 9)
#define RGFW_w RGFW_OS_BASED_VALUE(0x0077, 0x57, 13)
#define RGFW_x RGFW_OS_BASED_VALUE(0x0078, 0x58, 7) 
#define RGFW_y RGFW_OS_BASED_VALUE(0x0079, 0x59, 16)
#define RGFW_z RGFW_OS_BASED_VALUE(0x007a, 0x5A, 6)

#define RGFW_Period RGFW_OS_BASED_VALUE(0x002e, 190, 47)
#define RGFW_Comma RGFW_OS_BASED_VALUE(0x002c, 188, 43)
#define RGFW_Slash RGFW_OS_BASED_VALUE(0x002f, 191, 44)
#define RGFW_Bracket RGFW_OS_BASED_VALUE(0x005b, 219, 33)
#define RGFW_CloseBracket RGFW_OS_BASED_VALUE(0x005d, 221, 30) 
#define RGFW_Semicolon RGFW_OS_BASED_VALUE(0x003b, 186, 41)
#define RGFW_Return RGFW_OS_BASED_VALUE(0xff0d, 0x0D, 36) 
#define RGFW_Quote RGFW_OS_BASED_VALUE(0x0022, 222, 39)
#define RGFW_BackSlash RGFW_OS_BASED_VALUE(0x005c, 322, 42)

#define RGFW_Up RGFW_OS_BASED_VALUE(0xff52, 0x26, 126)
#define RGFW_Down RGFW_OS_BASED_VALUE(0xff54, 0x28, 125)
#define RGFW_Left RGFW_OS_BASED_VALUE(0xff51, 0x25, 123)
#define RGFW_Right RGFW_OS_BASED_VALUE(0xff53, 0x27, 124)

#define RGFW_Delete RGFW_OS_BASED_VALUE(0xffff, 0x2E, 118)
#define RGFW_Insert RGFW_OS_BASED_VALUE(0xff63, 0x2D, 115)
#define RGFW_End RGFW_OS_BASED_VALUE(0xff57, 0x23, 120)
#define RGFW_Home RGFW_OS_BASED_VALUE(0xff50, 0x24, 116) 
#define RGFW_PageUp RGFW_OS_BASED_VALUE(0xff55, 336, 117)
#define RGFW_PageDown RGFW_OS_BASED_VALUE(0xff56, 325, 122)

#define RGFW_Numlock RGFW_OS_BASED_VALUE(0xff7f, 0x90, 72)
#define RGFW_KP_Slash RGFW_OS_BASED_VALUE(0xffaf, 0x6F, 82)
#define RGFW_Multiply RGFW_OS_BASED_VALUE(0xffaa, 0x6A, 76)
#define RGFW_KP_Minus RGFW_OS_BASED_VALUE(0xffad, 0x6D, 67)
#define RGFW_KP_1 RGFW_OS_BASED_VALUE(0xffb1, 0x61, 84)
#define RGFW_KP_2 RGFW_OS_BASED_VALUE(0xffb2, 0x62, 85)
#define RGFW_KP_3 RGFW_OS_BASED_VALUE(0xffb3, 0x63, 86)
#define RGFW_KP_4 RGFW_OS_BASED_VALUE(0xffb4, 0x64, 87)
#define RGFW_KP_5 RGFW_OS_BASED_VALUE(0xffb5, 0x65, 88)
#define RGFW_KP_6 RGFW_OS_BASED_VALUE(0xffb6, 0x66, 89)
#define RGFW_KP_7 RGFW_OS_BASED_VALUE(0xffb7, 0x67, 90)
#define RGFW_KP_8 RGFW_OS_BASED_VALUE(0xffb8, 0x68, 92)
#define RGFW_KP_9 RGFW_OS_BASED_VALUE(0xffb9, 0x619, 93)
#define RGFW_KP_0 RGFW_OS_BASED_VALUE(0xffb0, 0x60, 83)
#define RGFW_KP_Period RGFW_OS_BASED_VALUE(0xffae, 0x6E, 65)
#define RGFW_KP_Return RGFW_OS_BASED_VALUE(0xff8d, 0x92, 77)

#ifdef __APPLE__
	void* NSCursor_arrowStr(char* str);
	void NSCursor_performSelector(void* cursor, void* selector);
#endif

	/* mouse icons */
#define RGFW_MOUSE_ARROW 				RGFW_OS_BASED_VALUE(68,   32512, NSCursor_arrowStr("arrowCursor"))
#define RGFW_MOUSE_IBEAM 				RGFW_OS_BASED_VALUE(152,  32513, NSCursor_arrowStr("IBeamCursor"))
#define RGFW_MOUSE_CROSSHAIR		 	RGFW_OS_BASED_VALUE(34,   32515, NSCursor_arrowStr("crosshairCursor"))
#define RGFW_MOUSE_POINTING_HAND 		RGFW_OS_BASED_VALUE(60,   32649, NSCursor_arrowStr("pointingHandCursor"))
#define RGFW_MOUSE_RESIZE_EW 			RGFW_OS_BASED_VALUE(108,  32644, NSCursor_arrowStr("resizeLeftRightCursor"))
#define RGFW_MOUSE_RESIZE_NS  			RGFW_OS_BASED_VALUE(116,  32645, NSCursor_arrowStr("resizeUpDownCursor"))
#define RGFW_MOUSE_RESIZE_ALL 			RGFW_OS_BASED_VALUE(52,   32646, NSCursor_arrowStr("closedHandCursor"))
#define RGFW_MOUSE_RESIZE_NWSE 			RGFW_OS_BASED_VALUE(12,   32642, NSCursor_performSelector(selector("_windowResizeNorthWestSouthEastCursor")))
#define RGFW_MOUSE_RESIZE_NESW 			RGFW_OS_BASED_VALUE(14,   32643, NSCursor_performSelector(selector("_windowResizeNorthEastSouthWestCursor")))
#define RGFW_MOUSE_NOT_ALLOWED 			RGFW_OS_BASED_VALUE(0,    32648, NSCursor_arrowStr("operationNotAllowedCursor"))
#else
#include "RGFW.h"
#endif
#else
typedef struct {
    u32 type;  /* event type */
    RSGL_point point; /* cursor point */
    u8 button; /*!< which mouse button has been clicked (0) left (1) middle (2) right OR which joystick button was pressed*/
    double scroll; /* the raw mouse scroll value */
    u32 keyCode; /* code of key pressed */
    char keyName[16]; /* string of key */
} RGFW_Event;
#endif

#include <stdbool.h>
#include <stddef.h>

/* 
******* 
RSGL_[shape]
*******
*/

typedef struct RSGL_pointF { float x, y; } RSGL_pointF;
#define RSGL_POINTF(x, y) (RSGL_pointF){x, y}

typedef struct RSGL_point3D {
    i32 x, y, z;
} RSGL_point3D;

typedef struct RSGL_point3DF { float x, y, z; } RSGL_point3DF;

#define RSGL_POINT3D(x, y, z) (RSGL_point3D){x, y, z}
#define RSGL_POINT3DF(x, y, z) (RSGL_point3DF){x, y, z}

typedef struct RSGL_areaF { float w, h;} RSGL_areaF;
#define RSGL_AREAF(w, h) (RSGL_areaF){w, h}

typedef struct RSGL_circle {
    i32 x, y, d;
} RSGL_circle;
#define RSGL_CIRCLE(x, y, d) (RSGL_circle){x, y, d}

typedef struct RSGL_circleF { float x, y, d; } RSGL_circleF;
#define RSGL_CIRCLEF(x, y, d) (RSGL_circleF){x, y, d}

typedef struct RSGL_triangle {
    RSGL_point p1, p2, p3;
} RSGL_triangle;
#define RSGL_TRIANGLE(p1, p2, p3) (RSGL_triangle){p1, p2, p3}

typedef struct RSGL_triangleF { RSGL_pointF p1, p2, p3; } RSGL_triangleF;
#define RSGL_TRIANGLEF(p1, p2, p3) (RSGL_triangleF){p1, p2, p3}

#define RSGL_createTriangle(x1, y1, x2, y2, x3, y3) (RSGL_triangle){{x1, y1}, {x2, y2}, {x3, y3}}
#define RSGL_createTriangleF(x1, y1, x2, y2, x3, y3) (RSGL_triangleF){{x1, y1}, {x2, y2}, {x3, y3}}

typedef struct RSGL_cube {
    i32 x, y, z, w, h, l;
} RSGL_cube;
#define RSGL_CUBE(x, y, z, w, h, l) (RSGL_cube){x, y, z, w, h, l}

typedef struct RSGL_cubeF { float x, y, z, w, h, l; } RSGL_cubeF;
#define RSGL_CUBEF(x, y, z, w, h, l) (RSGL_cubeF){x, y, z, w, h, l}

/* 
the color stucture is in 
ABGR by default for performance reasons 
(converting color to hex for example)
*/
typedef struct RSGL_color {
    u8 a, b, g, r;
} RSGL_color;

#define RSGL_RGBA(r, g, b, a) ((RSGL_color){(a), (b), (g), (r)})
#define RSGL_RGB(r, g, b) ((RSGL_color){255, (b), (g), (r)})

#define RSGL_COLOR_TO_HEX(color) ((u32)(color) & 0xFFFFFF00)
#define RSGL_RGB_TO_HEX(r, g, b, a) (RSGL_COLOR_TO_HEX(RSGL_RGBA(r, g, b, a)))
#define RSGL_RGBA_TO_HEX(r, g, b) (RSGL_COLOR_TO_HEX(RSGL_RGB(r, g, b, a)))

/* toggle the use of legacy OpenGL, on by default unless it fails to load */
RSGLDEF void RSGL_legacy(i32 legacy);

/* 
*******
RSGL_window
*******
*/

#ifndef RSGL_NO_RGFW

#define RSGL_Up RGFW_Up
#define RSGL_Down RGFW_Down
#define RSGL_Left RGFW_Left
#define RSGL_Right RGFW_Right
#define RSGL_Tab RGFW_Tab
#define RSGL_BackSpace RGFW_BackSpace

/* relevent RGFW defines. For documentation, this isn't meant to be used. */
#if defined(RELEVENT_RGFW_STRUCTS) && !defined(RELEVENT_RGFW_STRUCTS)
/* NOTE: some parts of the data can represent different things based on the event (read comments in RGFW_Event struct) */
typedef struct RGFW_Event {
	#ifdef RGFW_WINDOWS
	char keyName[16]; /* key name of event*/
	#else
	char* keyName; /*!< key name of event */
	#endif
	
	/*! drag and drop data */
	/* 260 max paths with a max length of 260 */
	#ifdef RGFW_ALLOC_DROPFILES
    char** droppedFiles;
	#else
	char droppedFiles[RGFW_MAX_DROPS][RGFW_MAX_PATH]; /*!< dropped files*/
	#endif
	u32 droppedFilesCount; /*!< house many files were dropped */

	u32 type; /*!< which event has been sent?*/
	RGFW_vector point; /*!< mouse x, y of event (or drop point) */
    u32 keyCode; /*!< keycode of event 	!!Keycodes defined at the bottom of the header file!! */

	u32 inFocus;  /*if the window is in focus or not*/
	
	u32 fps; /*the current fps of the window [the fps is checked when events are checked]*/
	u32 current_ticks, frames;
	
	u8 lockState;

	u16 joystick; /* which joystick this event applies to (if applicable to any) */

    u8 button; /*!< which mouse button has been clicked (0) left (1) middle (2) right OR which joystick button was pressed*/
  	
	u8 axisesCount; /* number of axises */
	RGFW_vector axis[2]; /* x, y of axises (-100 to 100) */
} RGFW_Event; /*!< Event structure for checking/getting events */

typedef struct RGFW_window {
	RGFW_window_src src;

	#if defined(RGFW_OSMESA) || defined(RGFW_BUFFER) 
	u8* buffer; /* buffer for non-GPU systems (OSMesa, basic software rendering) */
				/* when rendering using RGFW_BUFFER, the buffer is in the BGRA format */
	#endif

	RGFW_Event event; /*!< current event */

	RGFW_rect r; /* the x, y, w and h of the struct */

	u8 fpsCap; /*!< the fps cap of the window should run at (change this var to change the fps cap, 0 = no limit)*/
		/*[the fps is capped when events are checked]*/
} RGFW_window; /*!< Window structure for managing the window */
#endif

typedef RGFW_window RSGL_window;
/* 
    create RSGL window, an RGFW window and init stuff for RSGL 
    u64 args -> custom args (can be found earlier in this file)
*/
RSGLDEF RSGL_window* RSGL_createWindow(const char* name, RSGL_rect rect, u64 args);

/*
******
RGFW_FUNCTION_DEFINES
******
*/

/* 
	this function checks an *individual* event (and updates window structure attributes)
	this means, using this function without a while loop may cause event lag

	ex. 
	
	while (RSGL_window_checkEvent(win) != NULL) [this keeps checking events until it reaches the last one]
*/

RGFW_Event* RSGL_window_checkEvent(RSGL_window* win); /*!< check events (returns a pointer to win->event or NULL if there is no event)*/

/*! window managment functions*/
RSGLDEF void RSGL_window_close(RSGL_window* win); /*!< close the window and free leftover data */

RSGLDEF void RSGL_window_setIconImage(RGFW_window* win, const char* image);
RSGLDEF void RSGL_window_makeCurrent(RSGL_window* win);
RSGLDEF void RSGL_window_clear(RSGL_window* win, RSGL_color color);

RSGLDEF void RSGL_window_setMouseStandard(RSGL_window* win, u32 cursorIcon);

/*!< if window == NULL, it checks if the key is pressed globally. Otherwise, it checks only if the key is pressed while the window in focus.*/
RSGLDEF u8 RSGL_isPressedI(RSGL_window* win, u32 key); /*!< if key is pressed (key code)*/

RSGLDEF u8 RSGL_wasPressedI(RSGL_window* win, u32 key); /*!< if key was pressed (checks prev keymap only) (key code)*/

RSGLDEF u8 RSGL_isHeldI(RSGL_window* win, u32 key); /*!< if key is held (key code)*/
RSGLDEF u8 RSGL_isReleasedI(RSGL_window* win, u32 key); /*!< if key is released (key code)*/
#else /* RSGL_NO_RGFW */

/* 
*********************
RSGL_GRAPHICS_CONTEXT
*********************

this is for standalone RSGL graphics, no windowing / RGFW
AN example of this can be found in examples/glfw.c
*/

/* 
You need to define these if you want to use `RSGL_textbox_update`

#define RSGL_Up 
#define RSGL_Down 
#define RSGL_Left 
#define RSGL_Right 
#define RSGL_Tab 
#define RSGL_BackSpace 
*/

RSGLDEF void RSGL_initGraphics(
                            RSGL_area r, /* graphics context size */
                            void* loader /* opengl prozc address ex. wglProcAddress */
                            ); 
RSGLDEF void RSGL_graphics_updateSize(RSGL_area r);
RSGLDEF void RSGL_graphics_clear(RSGL_color c);
RSGLDEF void RSGL_graphics_free(void);


/* YOU define this version (if you need it) */
/*!< if window == NULL, it checks if the key is pressed globally. Otherwise, it checks only if the key is pressed while the window in focus.*/
RSGLDEF u8 RSGL_isPressedI(void* win, u32 key); /*!< if key is pressed (key code)*/

#ifndef RSGL_MOUSE_ARROW
#define RSGL_MOUSE_ARROW    1
#define RSGL_MOUSE_IBEAM  2
#define RSGL_MOUSE_POINTING_HAND 3
#endif

RSGLDEF void RSGL_window_setMouseStandard(void* win, u32 cursorIcon);

#endif /* RSGL_GRAPHICS_CONTEXT / !RSGL_NO_RGFW */

/* 
*******
RSGL_draw
*******
*/


/* 
    RSGL_draw args 

    RSGL has internal args which control how RSGL draws certain things
    by default these args clear after each RSGL_draw<whatever> call 

    but you can run RSGL_setClearArgs to enable or disable this behavior
    you can also run RSGL_clearArgs to clear the args by hand
*/
/* RSGL_args */
typedef struct RSGL_drawArgs {
    float* gradient; /* does not allocate any memory */
    
    u32 texture;
    u32 gradient_len;

    RSGL_rect currentRect; /* size of current window */
    RSGL_point3D rotate; 

    bool fill;
    RSGL_point3DF center;
    float lineWidth;
    i32 legacy;
    u32 program;
} RSGL_drawArgs;

RSGLDEF void RSGL_rotate(RSGL_point3D rotate); /* apply rotation to drawing */
RSGLDEF void RSGL_setTexture(u32 texture); /* apply texture to drawing */
RSGLDEF void RSGL_setProgram(u32 program); /* use shader program for drawing */
RSGLDEF void RSGL_setGradient(
                                float* gradient, /* array of gradients */
                                size_t len /* length of array */
                            ); /* apply gradient to drawing, based on color list*/
RSGLDEF void RSGL_fill(bool fill); /* toggle filling, if fill is false it runs RSGL_draw<whatever>_outline instead */
RSGLDEF void RSGL_center(RSGL_point3DF center); /* the center of the drawing (or shape), this is used for rotation */

/* args clear after a draw function by default, this toggles that */
RSGLDEF void RSGL_setClearArgs(bool clearArgs); /* toggles if args are cleared by default or not */
RSGLDEF void RSGL_clearArgs(void); /* clears the args */

/* calculate the align a smaller rect with larger rect */
typedef RSGL_ENUM(u8, RSGL_alignment) {
    RSGL_ALIGN_NONE = (1 << 0),
    /* horizontal */
    RSGL_ALIGN_LEFT = (1 << 1),
    RSGL_ALIGN_CENTER = (1 << 2),
    RSGL_ALIGN_RIGHT = (1 << 3),
    
    /* vertical */
    RSGL_ALIGN_UP = (1 << 4),
    RSGL_ALIGN_MIDDLE = (1 << 5),
    RSGL_ALIGN_DOWN = (1 << 6),

    RSGL_ALIGN_HORIZONTAL = RSGL_ALIGN_LEFT | RSGL_ALIGN_CENTER | RSGL_ALIGN_RIGHT,
    RSGL_ALIGN_VERTICAL = RSGL_ALIGN_UP | RSGL_ALIGN_MIDDLE | RSGL_ALIGN_DOWN,
/* ex : alignment = (RSGL_ALIGN_LEFT | RSGL_ALIGN_MIDDLE) */
};

/* align smaller rect onto larger rect based on a given alignment */
RSGLDEF RSGL_rect RSGL_alignRect(RSGL_rect larger, RSGL_rect smaller, u16 alignment);
RSGLDEF RSGL_rectF RSGL_alignRectF(RSGL_rectF larger, RSGL_rectF smaller, u16 alignment);

#define RSGL_GET_WORLD_X(x) (float)(2.0f * (x) / RSGL_args.currentRect.w - 1.0f)
#define RSGL_GET_WORLD_Y(y) (float)(1.0f + -2.0f * (y) / RSGL_args.currentRect.h)
#define RSGL_GET_WORLD_Z(z) (float)(z)

#define RSGL_GET_MATRIX_X(x, y, z) (matrix.m[0] * x + matrix.m[4] * y + matrix.m[8] * z + matrix.m[12])
#define RSGL_GET_MATRIX_Y(x, y, z) (matrix.m[1] * x + matrix.m[5] * y + matrix.m[9] * z + matrix.m[13])
#define RSGL_GET_MATRIX_Z(x, y, z) (matrix.m[2] * x + matrix.m[6] * y + matrix.m[10] * z + matrix.m[14])

#define RSGL_GET_MATRIX_POINT(x, y, z) RSGL_GET_MATRIX_X(x, y, z), RSGL_GET_MATRIX_Y(x, y, z), RSGL_GET_MATRIX_Z(x, y, z)
#define RSGL_GET_WORLD_POINT(x, y, z) RSGL_GET_WORLD_X((x)), RSGL_GET_WORLD_Y((y)), RSGL_GET_WORLD_Z((z))

#define RSGL_GET_FINAL_POINT(x, y, z) RSGL_GET_MATRIX_POINT(RSGL_GET_WORLD_X((x)), RSGL_GET_WORLD_Y((y)), RSGL_GET_WORLD_Z((z)))

typedef struct RSGL_MATRIX {
    float m[16];
} RSGL_MATRIX;

RSGLDEF RSGL_MATRIX RSGL_initDrawMatrix(RSGL_point3DF center);

/* 
RSGL_basicDraw is a function used internally by RSGL, but you can use it yourself
RSGL_basicDraw batches a given set of points based on the data to be rendered
*/
RSGLDEF void RSGL_basicDraw(
                u32 TYPE, /* type of shape, RSGL_QUADS, RSGL_TRIANGLES, RSGL_LINES, RSGL_QUADS_2D */
                float* points, /* array of 3D points */
                float* texPoints, /* array of 2D texture points (must be same length as points)*/
                RSGL_color c, /* the color to draw the shape */
                size_t len /* the length of the points array */
            );

typedef struct RSGL_BATCH {
    size_t start, len; /* when batch starts and it's length */
    u32 type, tex;
    float lineWidth;
} RSGL_BATCH; /* batch data type for rendering */

typedef struct RSGL_RENDER_INFO {
    RSGL_BATCH* batches;

    float* verts;
    float* texCoords;
    float* colors;

    size_t len; /* number of batches*/
    size_t vert_len; /* number of verts */
} RSGL_RENDER_INFO; /* render data */

/* 
    All of these functions are to be defined by the external render backend
*/

/* renders the current batches */
RSGLDEF void RSGL_renderBatch(RSGL_RENDER_INFO* info);
RSGLDEF void RSGL_renderInit(void* proc, RSGL_RENDER_INFO* info); /* init render backend */
RSGLDEF void RSGL_renderFree(void); /* free render backend */
RSGLDEF void RSGL_renderClear(float r, float g, float b, float a);
RSGLDEF void RSGL_renderViewport(i32 x, i32 y, i32 w, i32 h);
/* create a texture based on a given bitmap, this must be freed later using RSGL_deleteTexture or opengl*/
RSGLDEF u32 RSGL_renderCreateTexture(u8* bitmap, RSGL_area memsize,  u8 channels);
/* updates an existing texture wiht a new bitmap */
RSGLDEF void RSGL_renderUpdateTexture(u32 texture, u8* bitmap, RSGL_area memsize, u8 channels);
/* delete a texture */
RSGLDEF void RSGL_renderDeleteTexture(u32 tex);

/* custom shader program */
typedef struct RSGL_programInfo {
    u32 vShader, fShader, program;
} RSGL_programInfo;

RSGLDEF RSGL_programInfo RSGL_renderCreateProgram(const char* VShaderCode, const char* FShaderCode, char* posName, char* texName, char* colorName);
RSGLDEF void RSGL_renderDeleteProgram(RSGL_programInfo program);
RSGLDEF void RSGL_renderSetShaderValue(u32 program, char* var, float value[], u8 len);

/* these are RFont functions that also must be defined by the renderer

32 RFont_create_atlas(u32 atlasWidth, u32 atlasHeight);
void RFont_bitmap_to_atlas(u32 atlas, u8* bitmap, float x, float y, float w, float h);

*/

/* RSGL translation */
RSGLDEF RSGL_MATRIX RSGL_matrixMultiply(float left[16], float right[16]);
RSGLDEF RSGL_MATRIX RSGL_rotatef(RSGL_MATRIX* matrix, float angle, float x, float y, float z); 
RSGLDEF RSGL_MATRIX RSGL_translatef(RSGL_MATRIX* matrix, float x, float y, float z);
/* 2D shape drawing */
/* in the function names, F means float */

RSGLDEF void RSGL_drawPoint(RSGL_point p, RSGL_color c);
RSGLDEF void RSGL_drawPointF(RSGL_pointF p, RSGL_color c);
RSGLDEF void RSGL_plotLines(RSGL_pointF* lines, size_t points_count, u32 thickness, RSGL_color c);

RSGLDEF void RSGL_drawTriangle(RSGL_triangle t, RSGL_color c);
RSGLDEF void RSGL_drawTriangleF(RSGL_triangleF t, RSGL_color c);

RSGLDEF void RSGL_drawTriangleHyp(RSGL_pointF p, size_t angle, float hypotenuse, RSGL_color color);

RSGLDEF void RSGL_drawRect(RSGL_rect r, RSGL_color c);
RSGLDEF void RSGL_drawRectF(RSGL_rectF r, RSGL_color c);


RSGLDEF void RSGL_drawRoundRect(RSGL_rect r, RSGL_point rounding, RSGL_color c);
RSGLDEF void RSGL_drawRoundRectF(RSGL_rectF r, RSGL_point rounding, RSGL_color c);

RSGLDEF void RSGL_drawPolygon(RSGL_rect r, u32 sides, RSGL_color c);
RSGLDEF void RSGL_drawPolygonF(RSGL_rectF r, u32 sides, RSGL_color c);

RSGLDEF void RSGL_drawArc(RSGL_rect o, RSGL_point arc, RSGL_color color);
RSGLDEF void RSGL_drawArcF(RSGL_rectF o, RSGL_pointF arc, RSGL_color color);

RSGLDEF void RSGL_drawCircle(RSGL_circle c, RSGL_color color);
RSGLDEF void RSGL_drawCircleF(RSGL_circleF c, RSGL_color color);

RSGLDEF void RSGL_drawOval(RSGL_rect o, RSGL_color c);
RSGLDEF void RSGL_drawOvalF(RSGL_rectF o, RSGL_color c);

RSGLDEF void RSGL_drawLine(RSGL_point p1, RSGL_point p2, u32 thickness, RSGL_color c);
RSGLDEF void RSGL_drawLineF(RSGL_pointF p1, RSGL_pointF p2, u32 thickness, RSGL_color c);

/* 2D outlines */

/* thickness means the thickness of the line */

RSGLDEF void RSGL_drawTriangleOutline(RSGL_triangle t, u32 thickness, RSGL_color c);
RSGLDEF void RSGL_drawTriangleFOutline(RSGL_triangleF t, u32 thickness, RSGL_color c);

RSGLDEF void RSGL_drawRectOutline(RSGL_rect r, u32 thickness, RSGL_color c);
RSGLDEF void RSGL_drawRectFOutline(RSGL_rectF r, u32 thickness, RSGL_color c);

RSGLDEF void RSGL_drawRoundRectOutline(RSGL_rect r, RSGL_point rounding, u32 thickness, RSGL_color c);
RSGLDEF void RSGL_drawRoundRectFOutline(RSGL_rectF r, RSGL_point rounding, u32 thickness, RSGL_color c);

RSGLDEF void RSGL_drawPolygonOutline(RSGL_rect r, u32 sides, u32 thickness, RSGL_color c);
RSGLDEF void RSGL_drawPolygonFOutline(RSGL_rectF r, u32 sides, u32 thickness, RSGL_color c);

RSGLDEF void RSGL_drawArcOutline(RSGL_rect o, RSGL_point arc, u32 thickness, RSGL_color color);
RSGLDEF void RSGL_drawArcFOutline(RSGL_rectF o, RSGL_pointF arc, u32 thickness, RSGL_color color);

RSGLDEF void RSGL_drawCircleOutline(RSGL_circle c, u32 thickness, RSGL_color color);
RSGLDEF void RSGL_drawCircleFOutline(RSGL_circleF c, u32 thickness, RSGL_color color);

RSGLDEF void RSGL_drawOvalFOutline(RSGL_rectF o, u32 thickness, RSGL_color c);
RSGLDEF void RSGL_drawOvalOutline(RSGL_rect o, u32 thickness, RSGL_color c);

/* format a string */
#ifndef RSGL_NO_TEXT
RSGLDEF const char* RFont_fmt(const char* string, ...);
#define RSGL_strFmt RFont_fmt

/* loads a font into RSGL, returns it's index into the RSGL_fonts array, this is used as an id in later functions */
RSGLDEF i32 RSGL_loadFont(const char* font);
/* sets font as the current font in use based on index in RSGL_font, given when it was loaded */
RSGLDEF void RSGL_setFont(i32 font);

typedef struct RFont_font RFont_font;
/* sets source RFont font as the current font, given when it was loaded */
RSGLDEF void RSGL_setRFont(RFont_font* font);

/* draws the current fps on the screen */
#ifndef RSGL_NO_RGFW
RSGLDEF void RSGL_drawFPS(RGFW_window* win, RSGL_circle c, RSGL_color color);
#endif

RSGLDEF void RSGL_drawText_len(const char* text, size_t len, RSGL_circle c, RSGL_color color);
RSGLDEF void RSGL_drawText(const char* text, RSGL_circle c, RSGL_color color);
#define RSGL_drawTextF(text, font, c, color) \
    RSGL_setFont(font);\
    RSGL_drawText(text, c, color);

/* align text onto larger rect based on a given alignment */
RSGLDEF RSGL_circle RSGL_alignText(char* str, RSGL_circle c, RSGL_rectF larger, u8 alignment);
/* align text based on a length */
RSGLDEF RSGL_circle RSGL_alignText_len(char* str, size_t str_len, RSGL_circle c, RSGL_rectF larger, u8 alignment);

/* 
    returns the width of a text when rendered with the set font with the size of `fontSize
    stops at `textEnd` or when it reaches '\0'
*/
RSGLDEF RSGL_area RSGL_textArea(const char* text, u32 fontSize, size_t textEnd);
RSGLDEF RSGL_area RSGL_textLineArea(const char* text, u32 fontSize, size_t textEnd, size_t line);
#define RSGL_textAreaF(text, fontSize, textEnd) \
    RSGL_setFont(font);\
    RSGL_textAreaF(text, fontSize, textEnd);
#endif /* RSGL_NO_TEXT */

/* 
    this creates a texture based on a given image, draws it on a rectangle and then returns the loaded texture 
    
    if the rectangle's width and height are 0 it doesn't draw the image
    the texture is loaded into RSGL_image, this means it doesn't need to be freed
    but you can still free it early
*/

typedef struct RSGL_image { u32 tex; RSGL_area srcSize; char file[255]; } RSGL_image;
RSGLDEF RSGL_image RSGL_drawImage(const char* image, RSGL_rect r);

#define RSGL_loadImage(image) ((RSGL_image) RSGL_drawImage(image, (RSGL_rect){0, 0, 0, 0}))

/* 
    these two functions can be used before RSGL_renderCreateTexture in order to create 
    an swizzle'd texutre or atlas
*/

/* 
*******
RSGL_widgets
*******
*/

#ifndef RSGL_NO_WIDGETS

/* style of a widget */
typedef RSGL_ENUM(u32, RSGL_widgetStyle) {
    RSGL_STYLE_NONE = (1L << 0),

    RSGL_STYLE_DARK = (1L << 1), /* dark mode*/
    RSGL_STYLE_LIGHT = (1L << 2), /* light mode*/
    RSGL_STYLE_MODE  = RSGL_STYLE_LIGHT | RSGL_STYLE_DARK,

    RSGL_STYLE_ROUNDED = (1L << 3), /* use rounded rect */
    
    RSGL_STYLE_SLIDER_HORIZONTAL = (1L << 4),
    RSGL_STYLE_SLIDER_VERTICAL = (1L << 5),
    /* rectangle by default */
    RSGL_STYLE_SLIDER_CIRCLE = (1L << 6), 
    RSGL_STYLE_SLIDER = RSGL_STYLE_SLIDER_VERTICAL | RSGL_STYLE_SLIDER_HORIZONTAL, 
    
    RSGL_STYLE_TOGGLE = (1L << 7),
    RSGL_STYLE_RADIO = (1L << 8),
    RSGL_STYLE_CHECKBOX = (1 << 9),
    RSGL_STYLE_COMBOBOX = (1 << 10),
    RSGL_STYLE_CONTAINER = (1 << 11),
    RSGL_STYLE_TEXTBOX = (1 << 12),
    RSGL_STYLE_NO_TAB = (1 << 13),
    RSGL_STYLE_TYPE = RSGL_STYLE_SLIDER | RSGL_STYLE_TOGGLE | RSGL_STYLE_RADIO | RSGL_STYLE_CHECKBOX | RSGL_STYLE_COMBOBOX,

    RSGL_SHAPE_NULL = (1L << 0),
    RSGL_SHAPE_RECT = (1L << 14),
    RSGL_SHAPE_POLYGON = (1L << 15),

    RSGL_SHAPE_POLYGONF = (1L << 16),
    RSGL_SHAPE_RECTF = (1L << 17),

    RSGL_STYLE_RED = (1 << 18),
    RSGL_STYLE_BLUE = (1 << 19),
    RSGL_STYLE_GREEN = (1 << 20),
    RSGL_STYLE_YELLOW = (1 << 21),
    RSGL_STYLE_TEAL = (1 << 22),
    RSGL_STYLE_PURPLE = (1 << 23),
    RSGL_STYLE_COLOR = RSGL_STYLE_RED | RSGL_STYLE_BLUE | RSGL_STYLE_GREEN | RSGL_STYLE_YELLOW | RSGL_STYLE_TEAL | RSGL_STYLE_PURPLE,

    RSGL_STYLE_SHAPE = RSGL_SHAPE_RECT | RSGL_SHAPE_POLYGON | RSGL_SHAPE_POLYGONF | RSGL_SHAPE_RECTF,
};


/* expandable rect, returns true if a change has been made */
bool RSGL_expandableRect_update(RSGL_rect* rect, RGFW_Event e);
bool RSGL_expandableRectF_update(RSGL_rectF* rect, RGFW_Event e);

typedef RSGL_ENUM(u8, RSGL_buttonStatus) {
    RSGL_none = 0,
    RSGL_hovered,
    RSGL_pressed,
};

typedef struct RSGL_button_src {
    /* source data */
    struct {
        char* str;
        size_t text_len;
        size_t text_cap;
        RSGL_circle c;
        RSGL_color color;
        u8 alignment;
    } text;

    char** combo;

    u32 tex;
    RSGL_color color, outlineColor;
    RSGL_point rounding;
    RSGL_drawArgs drawArgs; 
    
    union {    
        size_t array_count; /* used for the combobox and radio buttons array size */
        size_t slider_pos; /* the pos of a slider for x or y */
        u32 cursorIndex; /* current cursor index (for textbox) */
    };

    u32* keys;
    size_t keys_len;

    void* window;

    RSGL_widgetStyle style;   
} RSGL_button_src; /* src data for a button*/

typedef struct RSGL_button {
    RSGL_button_src loaded_states[3]; /* based on RSGL_buttonStatus*/
    RSGL_buttonStatus status;
    
    union {
        size_t radio_select; /* which ratio button the status applies to (the rest are idle)*/
        size_t line_count; /* number of lines (for a textbox) */
    };

    bool toggle; /* for toggle buttons */

    RSGL_rectF rect;
    u32 points; /* for a polygon */
    u32 outline;

    RSGL_button_src src;
} RSGL_button;


typedef struct RSGL_select {
    u32 selectStart;
    u32 selectEnd;
    bool selected;
} RSGL_select;

/* button managing functions */
/* 
    inits the button 
    zeros out the data by default
*/
RSGLDEF RSGL_button RSGL_initButton(void); 

/* creates a new button from another button, does not copy over states */
RSGLDEF RSGL_button RSGL_copyButton(RSGL_button button); 

/* 
    load a default style into the button 
    the rect and any text you want should 
    be loaded before this function is used
*/
RSGLDEF void RSGL_button_setStyle(RSGL_button* button, RSGL_widgetStyle buttonStyle);

RSGLDEF void RSGL_button_setRect(RSGL_button* button, RSGL_rect rect);
RSGLDEF void RSGL_button_setRectF(RSGL_button* button, RSGL_rectF rect);

/* set rounding (for rectangles) */
RSGLDEF void RSGL_button_setRounding(RSGL_button* button, RSGL_point rounding);

RSGLDEF void RSGL_button_setPolygon(RSGL_button* button, RSGL_rect rect, u32 points);
RSGLDEF void RSGL_button_setPolygonF(RSGL_button* button, RSGL_rectF rect, u32 points);

/* add text to the button */
RSGLDEF void RSGL_button_setText(RSGL_button* button, char* text, size_t text_len, RSGL_circle c, RSGL_color color);
/* align the set text to the button */
RSGLDEF void RSGL_button_alignText(RSGL_button* button, u8 alignment);

RSGLDEF void RSGL_button_setTexture(RSGL_button* button, u32 tex);

RSGLDEF void RSGL_button_setColor(RSGL_button* button, RSGL_color color);
RSGLDEF void RSGL_button_setOutline(RSGL_button* button, u32 size, RSGL_color color);

/* set the window for the button (this is used for RGFW_isPressed and changing the cursor icon), NULL by default */
RSGLDEF void RSGL_button_setWindow(RSGL_button* button, void* window);

/* set keybinding for the button, if these keys are pressed the button is marked as pressed */
RSGLDEF void RSGL_button_setKeybind(RSGL_button* button, u32* keys, size_t keys_len);

/* set button combos for a combo box */
RSGLDEF void RSGL_button_setCombo(RSGL_button* button, char** combo, size_t combo_count);

/* 
    by default drawArgs is reset before drawing the button 
    it is then backed up later on
*/

/* draws the button using the current draw data */
RSGLDEF void RSGL_button_setDrawArgs(RSGL_button* button);
/* uses given draw arg data to draw the button */
RSGLDEF void RSGL_button_setDrawArgsData(RSGL_button* button, RSGL_drawArgs args);

/* button states (change button based on current state) */
RSGLDEF void RSGL_button_setOnIdle(RSGL_button* button, RSGL_button_src idle);
RSGLDEF void RSGL_button_setOnHover(RSGL_button* button, RSGL_button_src hover);
RSGLDEF void RSGL_button_setOnPress(RSGL_button* button, RSGL_button_src press);

/* draw the button */
RSGLDEF void RSGL_drawButton(RSGL_button button);

/* these functions should be run in an event loop */
RSGLDEF void RSGL_button_update(
    RSGL_button* b, /* button pointer */
    RGFW_Event e /* current event */
);

RSGLDEF float RSGL_slider_update(
    RSGL_button* b, /* button pointer */
    RGFW_Event e /* the current event, used for checking for a mouse event */
);

typedef struct  {
    RSGL_button** buttons;
    size_t buttons_len;

    RSGL_button title;
    bool held;
    RSGL_point initPoint;
} RSGL_container_src;

typedef RSGL_button RSGL_container;

RSGLDEF RSGL_button RSGL_nullButton(void);
RSGLDEF RSGL_button RSGL_label(char* text, size_t text_len, size_t textSize);

RSGLDEF RSGL_container* RSGL_initContainer(RSGL_rect r, RSGL_button** buttons, size_t len);
RSGLDEF void RSGL_freeContainer(RSGL_container* container);

RSGLDEF void RSGL_drawContainer(RSGL_container* container);
RSGLDEF void RSGL_container_setStyle(RSGL_container* button, u16 buttonStyle);

RSGLDEF void RSGL_container_setPos(RSGL_container* container, RSGL_point p);

RSGLDEF i32 RSGL_container_update(RSGL_container* container, RGFW_Event event);
#ifndef RSGL_NO_TEXT

typedef RSGL_button RSGL_textbox;

RSGLDEF RSGL_textbox* RSGL_initTextbox(size_t defaultSize);
RSGLDEF void RSGL_textbox_free(RSGL_textbox* tb); 

RSGLDEF void RSGL_textbox_draw(RSGL_textbox* tb);
RSGLDEF char* RSGL_textbox_getString(RSGL_textbox* tb, size_t* len);
RSGLDEF RSGL_select RSGL_textbox_update(RSGL_textbox* tb, RGFW_Event event);
RSGLDEF void RSGL_textbox_setTextInfo(RSGL_textbox* tb, RSGL_circle c, RSGL_color color);

/* these wrap around the same RSGL_button functions */
RSGLDEF void RSGL_textbox_alignText(RSGL_textbox* tb, u8 alignment);
RSGLDEF void RSGL_textbox_setColor(RSGL_textbox* button, RSGL_color color);
RSGLDEF void RSGL_textbox_setOutline(RSGL_textbox* button, u32 size, RSGL_color color);

RSGLDEF void RSGL_textbox_setStyle(RSGL_textbox* button, RSGL_widgetStyle buttonStyle);
RSGLDEF void RSGL_textbox_setRect(RSGL_textbox* button, RSGL_rect rect);
RSGLDEF void RSGL_textbox_setRectF(RSGL_textbox* button, RSGL_rectF rect);

RSGLDEF void RSGL_textbox_setWindow(RSGL_textbox* button, void* win);
#endif /* RSGL_NO_TEXT */

#endif /* RSGL_NO_WIDGETS */

/* 
*******
extra
*******
*/

/* wait functions */
RSGLDEF bool RSGL_wait(u32 miliseconds);
RSGLDEF bool RSGL_wait_frames(u32 frames);

/* ** collision functions ** */
RSGLDEF bool RSGL_circleCollidePoint(RSGL_circle c, RSGL_point p);
RSGLDEF bool RSGL_circleCollideRect(RSGL_circle c, RSGL_rect r);
RSGLDEF bool RSGL_circleCollide(RSGL_circle cir1, RSGL_circle cir2);
RSGLDEF bool RSGL_rectCollidePoint(RSGL_rect r, RSGL_point p);
RSGLDEF bool RSGL_rectCollide(RSGL_rect r, RSGL_rect r2);
RSGLDEF bool RSGL_pointCollide(RSGL_point p, RSGL_point p2);

RSGLDEF bool RSGL_circleCollidePointF(RSGL_circleF c, RSGL_pointF p);
RSGLDEF bool RSGL_circleCollideRectF(RSGL_circleF c, RSGL_rectF r);
RSGLDEF bool RSGL_circleCollideF(RSGL_circleF cir1, RSGL_circleF cir2);
RSGLDEF bool RSGL_rectCollidePointF(RSGL_rectF r, RSGL_pointF p);
RSGLDEF bool RSGL_rectCollideF(RSGL_rectF r, RSGL_rectF r2);
RSGLDEF bool RSGL_pointCollideF(RSGL_pointF p, RSGL_pointF p2);

#endif /* ndef RSGL_H */

/*
(Notes on how to manage Silicon (macos) included)

Example to get you started :

linux : gcc main.c -lX11 -lXcursor -lGL
windows : gcc main.c -lopengl32 -lshell32 -lgdi32
macos:
	<Silicon> can be replaced to where you have the Silicon headers stored
	<libSilicon.a> can be replaced to wherever you have libSilicon.a
	clang main.c -I<Silicon> <libSilicon.a> -framework Foundation -framework AppKit -framework OpenGL -framework CoreVideo

	NOTE(EimaMei): If you want the MacOS experience to be fully single header, then I'd be best to install Silicon (after compiling)
	by going to the `Silicon` folder and running `make install`. After this you can easily include Silicon via `#include <Silicon/silicon.h>'
	and link it by doing `-lSilicon`

#define RSGL_IMPLEMENTATION
#include "RSGL.h"

int main() {
    RSGL_window* win = RSGL_createWindow("name", (RSGL_rect){500, 500, 500, 500}, RSGL_CENTER);


    for (;;) {
        RSGL_window_checkEvent(win); // NOTE: checking events outside of a while loop may cause input lag 

        if (win->event.type == RSGL_quit)
            break;

        RSGL_drawRect((RSGL_rect){200, 200, 200, 200}, RSGL_RGB(255, 0, 0));
        RSGL_window_clear(win, RSGL_RGB(255, 255, 255));
    }

    RSGL_window_close(win);
}

	compiling :

	if you wish to compile the library all you have to do is create a new file with this in it

	RSGL.c
	#define RSGL_IMPLEMENTATION
	#include "RSGL.h"

	then you can use gcc (or whatever compile you wish to use) to compile the library into object file

	ex. gcc -c RSGL.c -fPIC

	after you compile the library into an object file, you can also turn the object file into an static or shared library

	(commands ar and gcc can be replaced with whatever equivalent your system uses)
	static : ar rcs RSGL.a RSGL.o
	shared :
		windows:
			gcc -shared RSGL.o  -lshell32 -lgdi32 -o RSGL.dll
		linux:
			gcc -shared RSGL.o -lX11 -lXcursor -o RSGL.so
		macos:
			<Silicon/include> can be replaced to where you have the Silicon headers stored
			<libSilicon.a> can be replaced to wherever you have libSilicon.a
			gcc -shared RSGL.o -framework Foundation <libSilicon.a> -framework AppKit -framework CoreVideo -I<Silicon/include>

	installing/building silicon (macos)

	Silicon does not need to be installde per se.
	I personally recommended that you use the Silicon included using RGFW

	to build this version of Silicon simplly run

	cd Silicon && make

	you can then use Silicon/include and libSilicon.a for building RGFW projects

    Alternatively, you also can find pre-built binaries for Silicon at
    https://github.com/ColleagueRiley/Silicon/tree/binaries

	ex.
	gcc main.c -framework Foundation -lSilicon -framework AppKit -framework CoreVideo -ISilicon/include

	I also suggest you compile Silicon (and RGFW if applicable)
	per each time you compile your application so you know that everything is compiled for the same architecture.
*/

/*
* Copyright (c) 2021-23 ColleagueRiley ColleagueRiley@gmail.com
*
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
*
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following r estrictions:
*
* 1. The origin of this software must not be misrepresented; you must not
* claim that you wrote the original software. If you use this software
* in a product, an acknowledgment in the product documentation would be
* appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
* misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
*
*
*

    define args
    (MAKE SURE RPHYS_IMPLEMENTATION is in at least one header or you use -DRSGL_IMPLEMENTATION)
	#define RPHYS_IMPLEMENTATION - makes it so source code is include
*/

#ifndef RPHYS_H
#define RPHYS_H

#ifndef RPHYSDEF
#ifdef __APPLE__
#define RPHYSDEF extern inline
#else
#define RPHYSDEF inline
#endif
#endif

#ifndef RPHYS_BODIES_INIT
#define RPHYS_BODIES_INIT 64
#endif

#ifndef RPHYS_BODIES_NEW
#define RPHYS_BODIES_NEW 5
#endif

#ifndef RPHYS_MAX_VERTICES
#define RPHYS_MAX_VERTICES 24
#endif

#ifndef RPHYS_MALLOC
#include <memory.h> /* use c standard memory handling by default */

#define RPHYS_MALLOC malloc
#define RPHYS_REALLOC realloc
#define RPHYS_FREE free
#endif

#ifdef RSGL_H
/* for loading polygons */
#include <math.h>

#ifndef PI
    #define PI 3.14159265358979323846f
#endif

#ifndef DEG2RAD
    #define DEG2RAD (PI/180.0f)
#endif
#endif

#ifdef RSGL_H
typedef RSGL_pointF vector2;
#else

#if !defined(u8)
    #include <stdint.h>

    typedef uint8_t     u8;
	typedef int8_t      i8;
	typedef uint16_t   u16;
	typedef int16_t    i16;
	typedef uint32_t   u32;
	typedef int32_t    i32;
	typedef uint64_t   u64;
	typedef int64_t    i64;
#endif

#ifndef RPHS_VECTOR_DEFINED
typedef struct vector2 {float x, y;} vector2;
#endif
#endif

/*
************************
***** RPhys_vector2 ******
************************
*/

/* add two 2D vectors */
RPHYSDEF vector2 RPhys_addVector2(vector2 v1, vector2 v2);
/* subtract two 2D vectors */
RPHYSDEF vector2 RPhys_subtractVector2(vector2 v1, vector2 v2);
/* multiply two 2D vectors */
RPHYSDEF vector2 RPhys_multiplyVector2(vector2 v1, vector2 v2);
/* divide two 2D vectors */
RPHYSDEF vector2 RPhys_divideVector2(vector2 v1, vector2 v2);

/*
************************
***** RPhys general ****
************************
*/

typedef struct RPhys_body RPhys_body; 

/* init RPhys (allocations, ect)*/
RPHYSDEF void RPhys_init(void);
/* do physics processing for all the bodies */
RPHYSDEF void RPhys_run(void (*__bodyCollideCallback)(RPhys_body*, RPhys_body*));
/* do a step in the physics processing (run by RPhys_run) */
void RPhys_step(double deltaTime, void (*)(RPhys_body*, RPhys_body*));
/* free and deinit RPhys data (for you're done using it) */
RPHYSDEF void RPhys_free(void);
/* set current gravity (9.8 m/s^2 by default)*/
RPHYSDEF void RPhys_setGravity(vector2 gravity);
/* set current air density (1.29 kg m−3 default) */
RPHYSDEF void RPhys_setAirDensity(float density);
/* 
  get vector of angled force (force = length of hypotenuse ) 

  |\ (force)
  | \
  |-(\ (<- angle)
*/
RPHYSDEF vector2 RPhys_angledForce(float force, float angle);
/* get current time */
RPHYSDEF double RPhys_time(void);

/*
************************
***** RPhys_shape ******
************************
*/

typedef enum RPhys_material_option {
    RUBBER = 0,
    CONCRETE_DRY,
    ICE,
    SNOW,
    COPPER,
    STEEL
} RPhys_material_option;

typedef struct RPhys_circle {vector2 v; float d;} RPhys_circle;
typedef struct RPhys_rect {vector2 v; float w, h;} RPhys_rect;

typedef enum RPhys_shape_option {
    RPHYS_CIRCLE, /* so we don't have to handle all 360 points */
    RPHYS_RECT, /* rectangle shape */
    RPHYS_RECT_POLYGON, /* polygon with rectangle data */
    RPHYS_POLYGON /* everything else that's not a circle or have a rectangle shape */
} RPhys_shape_option;

typedef struct RPhys_shape {
    RPhys_shape_option s; /* actual shape */
    float mass; /* mass of the body / shape (in kilograms) */
    RPhys_material_option material; /* material of the object*/

    union { /* shape data */
        RPhys_circle c;
        RPhys_rect r;
        vector2 vertices[RPHYS_MAX_VERTICES];
    };

    size_t vertexCount; /* how many vertices are in the vertices array (if the shape is a polygon) */
    float angle;
} RPhys_shape;

/* if a circle is colliding with a rect */
RPHYSDEF u8 RPhys_circleCollideRect(RPhys_circle c, RPhys_rect rect);
/* if two circles are colliding */
RPHYSDEF u8 RPhys_circleCollide(RPhys_circle cir1, RPhys_circle cir2);
/* if two rectangles are colliding */
RPHYSDEF u8 RPhys_rectCollide(RPhys_rect rect, RPhys_rect rect2);
/* if two shapes are colliding (any shape) */
RPHYSDEF u8 RPhys_shapeCollide(RPhys_shape s, RPhys_shape s2);

/* convert triangle cords to a rectangle struct */
RPHYSDEF RPhys_rect RPhys_triangleToRect(vector2* triangle);
/* convert any shape struct data to a rectangle struct */
RPHYSDEF RPhys_rect RPhys_shapeRect(RPhys_shape s) ;

/* get the µ value of two materials */
RPHYSDEF float RPhys_MuTable(RPhys_material_option mat1, RPhys_material_option mat2);

#ifdef RSGL_H
/* creates an RPhys_shape from an RSGL_rectF structure and mass in kg */
RPHYSDEF RPhys_shape RPhys_shape_loadRect(RSGL_rectF r, float mass, RPhys_material_option m);
/* creates an polygon RPhys_shape using an RSGL_rectF structure and a given number of sides and mass in kg */
RPHYSDEF RPhys_shape RPhys_shape_loadPolygon(RSGL_rectF r, u32 sides, float mass, RPhys_material_option m);
/* creates an RPhys_shape from an RSGL_circle structure and mass in kg */
RPHYSDEF RPhys_shape RPhys_shape_loadCircle(RSGL_circle c, float mass, RPhys_material_option m);
/* creates an RPhys_shape from an RSGL_triangle structure and mass in kg */
RPHYSDEF RPhys_shape RPhys_shape_loadTriangle(RSGL_triangle t, float mass, RPhys_material_option m);
/* creates an RPhys_shape from an RSGL_point structure and mass in kg */
RPHYSDEF RPhys_shape RPhys_shape_loadPoint(RSGL_point p, float mass, RPhys_material_option m);

/* creates an RSGL_rectF from rectangular polygon data of a RPhys_shape */
RPHYSDEF RSGL_rectF RPhys_shape_getRect(RPhys_shape shape);
/* 
    creates an RSGL_rectF from the polygon data of a RPhys_shape 
    (this assumes any type of polygon so this will be slower than using `RPhys_shape_getRect`)
*/
RPHYSDEF RSGL_rectF RPhys_shape_getPolyRect(RPhys_shape shape);
/* creates an RSGL_circle from the RPhys_circle structure of a RPhys_shape */
RPHYSDEF RSGL_circle RPhys_shape_getCircle(RPhys_shape shape);
/* creates an RSGL_triangle from triangular polygon data of a RPhys_shape */
RPHYSDEF RSGL_triangle RPhys_shape_getTriangle(RPhys_shape shape);
/* creates an RSGL_point from a single point of the data from RPhys_shape */
RPHYSDEF RSGL_point RPhys_shape_getPoint(RPhys_shape shape);
#endif

typedef struct RPhys_body {
    RPhys_shape shape; /* shape of object */
    u8 floating; /* not affected by gravity */

    vector2 velocity; /* speed of body (in px/s) */
    vector2 force; /* force on body (in newtons) */
    
    float sFrition;
    bool elastic;

    u16 index; /* index of body (in array) */
} RPhys_body;

/* get current acceleration of an object (based on force and mass) (in px / s ^ 2 (pixels per second per second)) */
RPHYSDEF vector2 RPhys_body_getAcceleration(RPhys_body* body);

/* add new body to body array */
RPHYSDEF void RPhys_addBody(RPhys_body* body);
/* add multiple bodies to the body array */
RPHYSDEF void RPhys_addBodies(RPhys_body* bodies, size_t count);
/* remove body from body array */
RPHYSDEF void RPhys_removeBody(RPhys_body* body);

#ifdef RSGL_H
/* draw the bodies in the body array (guesses shape of polygon) */
RPHYSDEF void RPhys_drawBodies(void);
RPHYSDEF void RPhys_drawBodiesColors(RSGL_color* colors);
RPHYSDEF void RPhys_drawBodiesTextures(u32* textures);
RPHYSDEF void RPhys_drawBodiesPro(RSGL_color* colors, u32* textures);
#endif

#endif /* ndef RPHYS_H */

