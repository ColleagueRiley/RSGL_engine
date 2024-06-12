# RSGL_engine
Basic 'engine' for RSGL. Supports C scripting via libtcc.

more features will probably be added in the future

# requirements / dependencies
- libtcc (included)

# features
    - scripting with C 
    - move sprites (when control is pressed)
    - see x, y of mouse (when control is pressed)
    - physics library
    - init, collideEvent and eventLoop functions
    - pause physics sim (with control + d)
    - get libtcc to be properly statically linked (windows)

# features todo
    - draw outline when physics object is hovered, moved or pressed
    - show physics object x, y if it's pressed

    - get sprite distance to pointer 
    - broadcast / get message (functional call)

    to RGFW
    -> window_getMouse (x, y)
    -> RGFW_isMousePressed() (mouse)