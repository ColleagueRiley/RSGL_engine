# RSGL_engine
Basic 'engine' for RSGL. Supports C scripting via libtcc.

more features will probably be added in the future

# features
- scripting with C 
- move sprites (when control is pressed)
- see x, y of mouse and sprites (when control is pressed)
- physics library
- init, collideEvent and eventLoop functions
- pause physics sim (with control + d)
- get libtcc to be properly statically linked (windows)
- broadcast / get message (functional call)

# dependencies
All dependencies are internally included and/or cloned in by the Makefile
- libtcc (included via `git clone`)
- RSGL (included locally)
- rphys (included locally)