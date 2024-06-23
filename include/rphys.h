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
	#if defined(_MSC_VER) || defined(__SYMBIAN32__)
		typedef unsigned char 	u8;
		typedef signed char		i8;
		typedef unsigned short  u16;
		typedef signed short 	i16;
		typedef unsigned int 	u32;
		typedef signed int		i32;
		typedef unsigned long	u64;
		typedef signed long		i64;
	#else
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

#ifndef RPHYS_BODY_SECRET
#define RPHYS_BODY_SECRET void*
#endif

typedef struct RPhys_body {
    RPhys_shape shape; /* shape of object */
    u8 floating; /* not affected by gravity */

    vector2 velocity; /* speed of body (in px/s) */
    vector2 force; /* force on body (in newtons) */
    
    float sFrition;
    bool elastic;

    RPHYS_BODY_SECRET secret; /* secret data for the user */

    u16 index; /* index of body (in array) */
    u8 pointer; /* if it's a pointer or allocated by RPhys (don't edit by hand) */
} RPhys_body;

/* get current acceleration of an object (based on force and mass) (in px / s ^ 2 (pixels per second per second)) */
RPHYSDEF vector2 RPhys_body_getAcceleration(RPhys_body* body);

/* add new body to body array */
RPHYSDEF void RPhys_addBody(RPhys_body* body);
/* add a new body to the body array, data only, no pointer */
RPHYSDEF void RPhys_addBodyNoPtr(RPhys_body body);
/* add multiple bodies to the body array */
RPHYSDEF void RPhys_addBodies(RPhys_body* bodies, size_t count);
/* remove body from body array */
RPHYSDEF void RPhys_removeBody(RPhys_body* body);
/* get the body at a index of the body array */
RPHYSDEF RPhys_body* RPhys_getBody(size_t index);
/* get the length of the body array */
RPHYSDEF size_t RPhys_getBodyCount(void);

#ifdef RSGL_H
/* draw the bodies in the body array (guesses shape of polygon) */
RPHYSDEF void RPhys_drawBodies(void);
RPHYSDEF void RPhys_drawBodiesColors(RSGL_color* colors);
RPHYSDEF void RPhys_drawBodiesTextures(u32* textures);
RPHYSDEF void RPhys_drawBodiesPro(RSGL_color* colors, u32* textures);
#endif

#endif /* ndef RPHYS_H */

#ifdef RPHYS_IMPLEMENTATION

#include <time.h>

vector2 RPhys_gravity = {0.0f, 9.8f};
float RPhys_airDensity = 1.29f;

size_t RPhys_len, RPhys_cap;
RPhys_body** RPhys_bodies;

vector2 RPhys_addVector2(vector2 v1, vector2 v2) {
    return (vector2){v1.x + v2.x, v1.y + v2.y};
}

vector2 RPhys_subtractVector2(vector2 v1, vector2 v2) {
    return (vector2){v1.x - v2.x, v1.y - v2.y};
}

vector2 RPhys_multiplyVector2(vector2 v1, vector2 v2) {
    return (vector2){v1.x * v2.x, v1.y * v2.y};
}

vector2 RPhys_divideVector2(vector2 v1, vector2 v2) {
    return (vector2){v1.x / v2.x, v1.y / v2.y};
}

void RPhys_init(void) {
    RPhys_bodies = (RPhys_body**)RPHYS_MALLOC(sizeof(RPhys_body**) * RPHYS_BODIES_INIT);
    
    RPhys_len = 0;
    RPhys_cap = RPHYS_BODIES_INIT;
}

void RPhys_run(void (*__bodyCollideCallback)(RPhys_body*, RPhys_body*)) {
    static double startTime = 0.0;
    static double accumulator = 0.0;
    static double deltaTime = 1.0/60.0/10.0 * 1000;

    if (startTime == 0)
        startTime = RPhys_time();
    
    double time = RPhys_time();

    accumulator += (time - startTime);

    while (accumulator >= deltaTime) {
        RPhys_step(deltaTime, __bodyCollideCallback);
        accumulator -= deltaTime;
    }
    
    startTime = time;
}

void RPhys_step(double deltaTime, void (*__bodyCollideCallback)(RPhys_body*, RPhys_body*) ) {
    /*vector2 timeVector = {deltaTime / 2.0f, deltaTime / 2.0f};*/

    u32 index = 0;
    for (index = 0; index < RPhys_len; index++) {
        RPhys_body* body = RPhys_bodies[index];
        
        switch (body->shape.s) {
            case RPHYS_RECT: case RPHYS_RECT_POLYGON:
                body->shape.r.v = RPhys_addVector2(body->shape.c.v, body->velocity);
                break;
            case RPHYS_POLYGON:
                size_t v;
                for (v = 0; v < body->shape.vertexCount; v++)
                    body->shape.vertices[v] = RPhys_addVector2(body->shape.vertices[v], body->velocity);
                break;
            case RPHYS_CIRCLE:
                body->shape.c.v = RPhys_addVector2(body->shape.c.v, body->velocity);
                break;
            default: break;
        }
        
        vector2 correction = {0, 0};

        size_t i; 
        for (i = 0; i < RPhys_len; i++) {
            RPhys_body* body2 = RPhys_bodies[i];

            if (body->index == body2->index || body->floating || RPhys_shapeCollide(body->shape, body2->shape) == false || 
                (body->velocity.x == 0 && body->velocity.y == 0 && body->force.x == 0 && body->force.y == 0)
            )
                continue;
            
            RPhys_rect r1 = RPhys_shapeRect(body2->shape);
            
            const RPhys_rect rect = RPhys_shapeRect(body->shape);
            RPhys_rect r = (RPhys_rect){(vector2){rect.v.x + 2, rect.v.y + rect.h}, rect.w - 3, 1};

            if (__bodyCollideCallback != NULL)
                __bodyCollideCallback(body, body2);

            /* if the object is coliding with something from the bottom */
            if (RPhys_rectCollide(r1, r) && (body->velocity.y != 0 || body->force.y != 0)) {
                for (r.v.y -= rect.h; r.h < rect.h && !(r1.v.y + r1.h >= r.v.y && r1.v.y <= r.v.y + r.h); r.h++);
                
                vector2 norm = RPhys_multiplyVector2(RPhys_gravity, (vector2){0, -(100 + (body2->shape.mass * 100))});


                float Mu = RPhys_MuTable(body->shape.material, body2->shape.material);
                float frictionForceX = (Mu* (RPhys_gravity.y * body->shape.mass));
                
                if (body->velocity.x && body->velocity.x > body->sFrition) {
                    body->sFrition = 0;
                    
                    if (body->velocity.x > 0.0f)
                        frictionForceX = -frictionForceX;
                    
                    body->velocity.x += frictionForceX * (deltaTime / (1000 / 2.0)); 
                }

                else
                    /* the static friction Mu, in this, will just be the kenetic friction Mu * 2*/
                    body->sFrition = ((Mu * 2) * (RPhys_gravity.y * body->shape.mass));
                
                body->force = RPhys_addVector2(body->force, norm);

                correction = (vector2){0.0f, r.h - rect.h};
            
                if ((body2->shape.mass * (body2->velocity.y + 1)) < (body->shape.mass * (body->velocity.y + 1))) {
                    body2->force = RPhys_addVector2(body2->force, RPhys_gravity);

                    if (body->elastic)
                        body2->force = RPhys_multiplyVector2(
                            (vector2){body2->force.x, -body2->force.y},
                            RPhys_gravity
                        );
                }
            } else if (body->velocity.y != 0 || body->force.y != 0) {
                r = (RPhys_rect){(vector2){rect.v.x + 2, rect.v.y}, rect.w - 2, 1};
                /* if the object is coliding with something from the top */
                if (RPhys_rectCollide(r1, r)) {
                    for (; r.h < rect.h && !(r1.v.y + r1.h >= r.v.y && r1.v.y <= r.v.y + r.h); r.h++);
                    correction = (vector2){0.0f, r.h - 0.45};
                    
                    if ((body2->shape.mass * (body2->velocity.y + 1)) < (body->shape.mass * (body->velocity.y + 1)))
                        body2->velocity.y = (1.0f / RPhys_airDensity) * (body->velocity.y + 1) * (deltaTime / (1000 / 2.0));

                    if (body->elastic)
                        body2->force = RPhys_multiplyVector2(
                            (vector2){body2->force.x, -body2->force.y},
                            RPhys_gravity
                        );
                }
            }
            
            if (body->velocity.x == 0 && body->force.x == 0)
                continue;
            
            /* if the object is coliding with something from the left-side */
            r = (RPhys_rect){(vector2){rect.v.x, rect.v.y + 5}, 1, rect.h - 6};
            if (RPhys_rectCollide(r1, r)) {
                body->velocity.x = body2->velocity.x * (deltaTime / (1000 / 2.0));
            
                if ((body2->shape.mass * (body2->velocity.x + 1)) < (body->shape.mass * (body->velocity.x + 1)))
                    body2->velocity.x = body->velocity.x * (deltaTime / (1000 / 2.0));
                
                if (body->elastic)
                    body->velocity.x = body->velocity.x * (deltaTime / (1000 / 2.0));

                continue;
            }
            
            r = (RPhys_rect){(vector2){rect.v.x + rect.w, rect.v.y + 3}, 1, rect.h - 6};
            if (RPhys_rectCollide(r1, r)) {
                body->velocity.x = body2->velocity.x * (deltaTime / (1000 / 2.0));
                
                /* momentum  (p = m * v) */
                if ((body2->shape.mass * (body2->velocity.x + 1)) < (body->shape.mass * (body->velocity.x + 1)))
                    body2->velocity.x = -body->velocity.x * (deltaTime / (1000 / 2.0));
                
                                
                if (body->elastic)
                    body->velocity.x = body->velocity.x * (deltaTime / (1000 / 2.0));
            }
        }

        float inverseMass = ((body->shape.mass != 0.0f) ? 1.0f / body->shape.mass : 0.0f);

        body->velocity = RPhys_addVector2(body->velocity, (vector2){
                                                            (body->force.x * inverseMass) * (deltaTime / 2.0), 
                                                            (body->force.y * inverseMass) * (deltaTime / 2.0)
                                                        });
        
        if (body->floating == 0)  {
            body->velocity.x += RPhys_gravity.x * (deltaTime / (1000 / 2.0));
            body->velocity.y += RPhys_gravity.y * (deltaTime / (1000 / 2.0));
            
            body->velocity.x = RPhys_gravity.x ? ((RPhys_airDensity * body->shape.mass) / (body->velocity.x)) * (deltaTime / (1000 / 2.0)) : body->velocity.x;
            body->velocity.y = RPhys_gravity.y ? ((RPhys_airDensity * body->shape.mass) / (body->velocity.y)) * (deltaTime / (1000 / 2.0)) : body->velocity.y; 
        }
        body->velocity = RPhys_addVector2(body->velocity, correction);

        body->force = (vector2){0, 0};
    }
}

void RPhys_free(void) {
    size_t i;
    for (i = 0; i < RPhys_len; i++) {
        if (RPhys_bodies[i]->pointer)
            continue;
        
        free(RPhys_bodies[i]);
    }

    RPHYS_FREE(RPhys_bodies);
}

void RPhys_setGravity(vector2 gravity) {
    RPhys_gravity = gravity;
}

void RPhys_setAirDensity(float density) {
    RPhys_airDensity = density;
}

vector2 RPhys_angledForce(float force, float angle) {
    return (vector2) {
        cos(angle) * force,
        sin(angle) * force 
    };
}

double RPhys_time(void) {
    static u64 baseTime = 0; 
    static u64 frequency = 0; 

    if (frequency == 0) {
        #if defined(_WIN32)
            QueryPerformanceFrequency((unsigned long long int *) &frequency);
        #endif

        #if defined(__linux__)
            struct timespec now;
            if (clock_gettime(1, &now) == 0)
                frequency = 1000000000;
        #endif

        #if defined(__APPLE__)
            mach_timebase_info_data_t timebase;
            mach_timebase_info(&timebase);
            frequency = (timebase.denom * 1e9)/timebase.numer;
        #endif
    }

    u64 time = 0;

    #if defined(_WIN32)
        QueryPerformanceCounter((unsigned long long int *) &time);
    #endif

    #if defined(__linux__)
        struct timespec now;
        clock_gettime(1, &now);
        time = (u64)now.tv_sec*(u64)1000000000 + (u64)now.tv_nsec;
    #endif

    #if defined(__APPLE__)
        time = mach_absolute_time();
    #endif

    if (baseTime == 0)
        baseTime = time;

    return (double)(time - baseTime)/frequency*1000;
}

u8 RPhys_circleCollide(RPhys_circle cir, RPhys_circle cir2) {
    float distanceBetweenCircles = (float) sqrtf(
        (cir2.v.x - cir.v.x) * (cir2.v.x - cir.v.x) + 
        (cir2.v.y - cir.v.y) * (cir2.v.y - cir.v.y)
    );

    return !(distanceBetweenCircles > (cir.d/2) + (cir2.d/2)); /* check if there is a collide */
}

u8 RPhys_rectCollide(RPhys_rect r, RPhys_rect r2) { 
    return (r.v.x + r.w >= r2.v.x && r.v.x <= r2.v.x + r2.w && r.v.y + r.h >= r2.v.y && r.v.y <= r2.v.y + r2.h); 
}

u8 RPhys_circleCollideRect(RPhys_circle c, RPhys_rect r) {
    /* test cords */
    float testX = c.v.x; 
    float testY = c.v.y;

    /* fill cords based on x/ys of the shapes */
    if (c.v.x < r.v.x)
      testX = r.v.x;

    else if (c.v.x > r.v.x + r.w) 
      testX = r.v.x - r.w;

    if (c.v.y < r.v.x)  
      testY = r.v.x;  

    else if (c.v.y > r.v.y + r.h)
      testY = r.v.y + r.h; 
    
    /* check */
    return ( sqrtf( ( (c.v.x - testX) * (c.v.x - testX) ) + ( (c.v.y - testY) * (c.v.y - testY) ) )  <= (c.d/2) );
}

RPhys_rect RPhys_triangleToRect(vector2* triangle) {
    RPhys_rect rect = {{-10.1f, -10.1f}, 0.0f, 0.0f};
    
    u8 i;
    for (i = 0; i < 3; i++) {
        if (triangle[i].x < rect.v.x)
            rect.v.x = triangle[i].x;
        if (triangle[i].y < rect.v.y)
            rect.v.y = triangle[i].y;
        if (triangle[i].x > rect.w)
            rect.w = triangle[i].x;
        if (triangle[i].y > rect.h)
            rect.h = triangle[i].y;
    }

    return rect;
}

RPhys_rect RPhys_shapeRect(RPhys_shape s) {
    if (s.vertexCount == 3)
        return RPhys_triangleToRect(s.vertices);
    
    if (s.s == RPHYS_RECT || s.s == RPHYS_RECT_POLYGON)
        return s.r;
    if (s.s == RPHYS_CIRCLE)
       return (RPhys_rect){(vector2){s.c.v.x, s.c.v.y}, s.c.d, s.c.d};

    return (RPhys_rect){(vector2){0.0f, 0.0f}, 0.0f, 0.0f};
}

/* 
typedef enum RPhys_material_option {
    RUBBER,
    CONCRETE_DRY,
    ICE,
    SNOW,
    COPPER,
    STEEL
} RPhys_material_option;

*/

float RPhys_MuTable(RPhys_material_option mat1, RPhys_material_option mat2) {
    static float MuTable[] = {
        0.0115, 0.0100, 0.0089, 0.0003, 0.0039, 0.0005, 
        0.0100, 0.0080, 0.0004, 0.0065, 0.0070, 0.0067,
        0.0089, 0.0004, 0.0002, 0.0003, 0.0005, 0.0014,
        0.0003, 0.0065, 0.0003, 0.0003, 0.0057, 0.0008,
        0.0039, 0.0070, 0.0005, 0.0057, 0.0002, 0.0053,
        0.0005, 0.0067, 0.0014, 0.0008, 0.0053, 0.0015,
    };
    
    return MuTable[(mat1 * 6) + mat2];
}

u8 RPhys_shapeCollide(RPhys_shape s, RPhys_shape s2) {
    if (s.vertexCount == 3) {
        RPhys_rect r1 = RPhys_triangleToRect(s.vertices);

        if (s2.vertexCount == 3)
            return RPhys_rectCollide(r1, RPhys_triangleToRect(s2.vertices));

        if (s2.s == RPHYS_CIRCLE)
            return RPhys_circleCollideRect(s2.c, r1);
    
        if (s2.s == RPHYS_RECT || s2.s == RPHYS_RECT_POLYGON)
            return RPhys_rectCollide(r1, s2.r);
    }

    if ((s.s == RPHYS_RECT || s.s == RPHYS_RECT_POLYGON) && 
        (s2.s == RPHYS_RECT || s2.s == RPHYS_RECT_POLYGON))
            return RPhys_rectCollide(s.r, s2.r);
    if ((s.s == RPHYS_RECT || s.s == RPHYS_RECT_POLYGON) && s2.s == RPHYS_CIRCLE)
        return RPhys_circleCollideRect(s2.c, s.r);
    if ((s2.s == RPHYS_RECT || s2.s == RPHYS_RECT_POLYGON) && s.s == RPHYS_CIRCLE)
       return RPhys_circleCollideRect(s.c, s2.r);
    if (s.s == RPHYS_CIRCLE && s2.s == RPHYS_CIRCLE)
        return RPhys_circleCollide(s.c, s2.c);

    return false;
}

#ifdef RSGL_H
RPhys_shape RPhys_shape_loadRect(RSGL_rectF r, float mass, RPhys_material_option m) {
    RPhys_shape s = {RPHYS_RECT, mass, m, {}, 0};
    s.r = (RPhys_rect){(vector2){(float)r.x, (float)r.y}, (float)r.w, (float)r.h};

    return s;
}

RPhys_shape RPhys_shape_loadPolygon(RSGL_rectF r, u32 sides, float mass, RPhys_material_option m) {
    RPhys_shape s = {RPHYS_RECT_POLYGON, mass, m, {}, sides};
    s.r = (RPhys_rect){(vector2){r.x, r.y}, r.w, r.h};

    return s;
}

RPhys_shape RPhys_shape_loadCircle(RSGL_circle c, float mass, RPhys_material_option m) {
    RPhys_shape s = {RPHYS_CIRCLE, mass, m, {}, 0};
    s.c = (RPhys_circle){(vector2){c.x, c.y}, c.d};

    return s;
}

RPhys_shape RPhys_shape_loadTriangle(RSGL_triangle t, float mass, RPhys_material_option m) {
    RPhys_shape s = {RPHYS_POLYGON, mass, m, {}, 3};
    s.vertices[0] = (vector2){t.p1.x, t.p1.y};
    s.vertices[1] = (vector2){t.p2.x, t.p2.y};
    s.vertices[2] = (vector2){t.p3.x, t.p3.y};

    return s;
}

RPhys_shape RPhys_shape_loadPoint(RSGL_point p, float mass, RPhys_material_option m) {
    RPhys_shape s = {RPHYS_RECT, mass, m, {}, 1};
    s.r = (RPhys_rect){(vector2){p.x, p.y}, 1, 1};

    return s;
}

RSGL_rectF RPhys_shape_getRect(RPhys_shape shape) {
    if (shape.s == RPHYS_CIRCLE)
        return (RSGL_rectF){shape.c.v.x, shape.c.v.y, shape.c.d, shape.c.d};
    if (shape.s == RPHYS_RECT || shape.s == RPHYS_RECT_POLYGON)
        return (RSGL_rectF){shape.r.v.x, shape.r.v.y, shape.r.w, shape.r.h};
    if (shape.vertexCount < 4)
        return (RSGL_rectF){0, 0, 0, 0};

    RSGL_point p = RPhys_shape_getPoint(shape);
    return RSGL_RECTF(   p.x, p.y, 
                        (shape.vertices[2].x - p.x), 
                        (shape.vertices[2].y - p.y)
                    );
}

RSGL_rectF RPhys_shape_getPolyRect(RPhys_shape shape) {
    if (shape.s == RPHYS_CIRCLE)
        return (RSGL_rectF){shape.c.v.x, shape.c.v.y, shape.c.d, shape.c.d};
    if (shape.s == RPHYS_RECT_POLYGON)
        return (RSGL_rectF){shape.r.v.x, shape.r.v.y, shape.r.w, shape.r.h};
    
    RSGL_point p = {-500, -500};
    RSGL_area a = {0, 0};

    size_t i;
    for (i = 0; i < shape.vertexCount; i++) {
        if ((shape.vertices[i].x) < p.x || p.x == -500)
            p.x = (shape.vertices[i].x);
        
        if ((shape.vertices[i].y) < p.y || p.y == -500)
            p.y = shape.vertices[i].y;

        if ((shape.vertices[i].x) > a.w)
            a.w = shape.vertices[i].x;
        
        if ((shape.vertices[i].y) > a.h)
            a.h = shape.vertices[i].y;
    }

    return (RSGL_rectF){p.x, p.y, a.w - p.x, a.h - p.x};
}

RSGL_circle RPhys_shape_getCircle(RPhys_shape shape) {
    if (shape.s == RPHYS_RECT)
        return RSGL_CIRCLE(shape.r.v.x, shape.r.v.y, shape.r.w);
    if (shape.s != RPHYS_CIRCLE)
        return RSGL_CIRCLE(0, 0, 0);
    return RSGL_CIRCLE(shape.c.v.x, shape.c.v.y, shape.c.d);
}

RSGL_triangle RPhys_shape_getTriangle(RPhys_shape shape) {
    if (shape.s == RPHYS_CIRCLE || shape.vertexCount < 3)
        return (RSGL_triangle){};
    return (RSGL_triangle){
                            (RSGL_point){shape.vertices[0].x, shape.vertices[0].y},
                            (RSGL_point){shape.vertices[1].x, shape.vertices[1].y},
                            (RSGL_point){shape.vertices[2].x, shape.vertices[2].y}
                          };
}

RSGL_point RPhys_shape_getPoint(RPhys_shape shape) {
    if (shape.s == RPHYS_CIRCLE)
        return (RSGL_point){shape.c.v.x, shape.c.v.y};
    
    if (shape.vertexCount < 1)
        return (RSGL_point){0, 0};
    
    return (RSGL_point){shape.vertices[0].x, shape.vertices[0].y};
}
#endif

vector2 RPhys_body_getAcceleration(RPhys_body* body) {
    /* a = (fnet / mass) */
    return (vector2){(body->force.x / body->shape.mass), (body->force.y / body->shape.mass)};
}

void RPhys_addBody(RPhys_body* body) {
    if (RPhys_len >= RPhys_cap) {
        RPhys_bodies = (RPhys_body**)RPHYS_REALLOC(RPhys_bodies, sizeof(RPhys_body**) * (RPHYS_BODIES_NEW + RPhys_len));
        RPhys_len += RPHYS_BODIES_NEW;
    }

    body->index = RPhys_len;

    body->velocity = (vector2){0, 0};
    body->force = (vector2){0, 0};
    body->sFrition = 0.0f;
    body->shape.angle = 0.0f;
    body->pointer = true;

    RPhys_bodies[body->index] = body;

    RPhys_len += 1; 
}

void RPhys_addBodyNoPtr(RPhys_body newBody) {
    RPhys_body* body = (RPhys_body*)malloc(sizeof(RPhys_body));

    body->shape = newBody.shape;
    body->floating = newBody.floating;
    body->elastic = newBody.elastic;
    body->secret = newBody.secret;

    RPhys_addBody(body);
    body->pointer = false;
}

void RPhys_addBodies(RPhys_body* bodies, size_t count) {
    size_t i;
    for (i = 0; i < count; i++)
        RPhys_addBody(&bodies[i]);
}

void RPhys_removeBody(RPhys_body* body) {
    RPhys_len -= 1;
    memcpy(RPhys_bodies + body->index, RPhys_bodies + body->index + 1, (RPhys_len - body->index) * sizeof(RPhys_body**));
}

RPhys_body* RPhys_getBody(size_t index) {
    return RPhys_bodies[index];
}

size_t RPhys_getBodyCount(void) { return RPhys_len; }

#ifdef RSGL_H
void RPhys_drawBodies(void) { RPhys_drawBodiesPro(NULL, NULL); }

void RPhys_drawBodiesColors(RSGL_color* colors) { RPhys_drawBodiesPro(colors, (u32*)NULL);  }

void RPhys_drawBodiesTextures(u32* texs){ RPhys_drawBodiesPro((RSGL_color*)NULL, texs); }

void RPhys_drawBodiesPro(RSGL_color* colors, u32* texs) {
    size_t i;
    for (i = 0; i < RPhys_len; i++) {
        RPhys_shape shape = RPhys_bodies[i]->shape;
        
        RSGL_color c = RSGL_RGB(255, 0, 0);
        if (colors != NULL)
            c = colors[i];

        if (texs != NULL && texs[i])
            RSGL_setTexture(texs[i]);

        RSGL_rotate(RSGL_POINT3D(0, 0, shape.angle));

        if (shape.s == RPHYS_CIRCLE) {
            RSGL_drawCircle(RPhys_shape_getCircle(shape), c);
            continue;
        }


        if (shape.vertexCount == 4 || shape.s == RPHYS_RECT) {
            RSGL_drawRectF(RPhys_shape_getRect(shape), c);
            continue;         
        }

        if (shape.vertexCount == 1) {
            RSGL_drawPoint(RPhys_shape_getPoint(shape), c);
            continue;
        }

        if (shape.vertexCount == 3) {
            RSGL_drawTriangle(RPhys_shape_getTriangle(shape), c);
            continue;         
        }

        RSGL_rectF r = RPhys_shape_getPolyRect(shape);
        RSGL_drawPolygonF(r, (shape.s == RPHYS_RECT_POLYGON) ? shape.vertexCount :shape.vertexCount / 3, c);
    }
}
#endif

#endif /* RPHYS_IMPLEMENTATION */