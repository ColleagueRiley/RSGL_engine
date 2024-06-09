CC = gcc

LIBS :=-lgdi32 -lm -lopengl32 -lwinmm -ggdb -lm -ltcc
EXT = .exe
STATIC =

ifeq ($(CC),x86_64-w64-mingw32-gcc)
	STATIC = --static
endif

ifneq (,$(filter $(CC),winegcc x86_64-w64-mingw32-gcc))
    detected_OS := Windows
	LIB_EXT = .dll
else
	ifeq '$(findstring ;,$(PATH))' ';'
		detected_OS := Windows
	else
		detected_OS := $(shell uname 2>/dev/null || echo Unknown)
		detected_OS := $(patsubst CYGWIN%,Cygwin,$(detected_OS))
		detected_OS := $(patsubst MSYS%,MSYS,$(detected_OS))
		detected_OS := $(patsubst MINGW%,MSYS,$(detected_OS))
	endif
endif

ifeq ($(detected_OS),Windows)
	LIBS := -ggdb -lshell32 -lwinmm -lgdi32 -lopengl32 $(STATIC)
	EXT = .exe
endif
ifeq ($(detected_OS),Darwin)        # Mac OS X
	LIBS := -lm -framework Foundation -framework AppKit -framework OpenGL -framework CoreVideo$(STATIC) -ltcc
	EXT = 
endif
ifeq ($(detected_OS),Linux)
    LIBS := -lXrandr -lX11 -lm -lGL -ldl -lpthread $(STATIC) -ltcc
	EXT =
endif

RSGL_engine: source/* include/*
	$(CC) source/main.c $(LIBS) -I./include -o $@

debug:
	$(CC) source/main.c $(LIBS) -I./include -o RSGL_engine
	./RSGL_engine test.c

release_example:
	make RSGL_engine
	mkdir -p release
	cp -r test.c RSGL.h ./RSGL_engine$(EXT) run.sh run.bat SuperEasy.ttf image.png ./release
