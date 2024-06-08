CC = gcc

LIBS := -lopengl32 -lgdi32 -lWinmm -ltcc -lm
EXT = exe

ifneq (,$(filter $(CC),winegcc x86_64-w64-mingw32-gcc))
    detected_OS := Windows
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

ifeq '$(findstring ;,$(PATH))' ';'
    detected_OS := Windows
else
    detected_OS := $(shell uname 2>/dev/null || echo Unknown)c
    detected_OS := $(patsubst CYGWIN%,Cygwin,$(detected_OS))
    detected_OS := $(patsubst MSYS%,MSYS,$(detected_OS))
    detected_OS := $(patsubst MINGW%,MSYS,$(detected_OS))
endif

ifeq ($(detected_OS),Windows)
	LIBS := -lopengl32 -lgdi32 -lWinmm -ltcc -lm
	EXT = .exe
endif
ifeq ($(detected_OS),Darwin)        # Mac OS X
	LIBS := -framework Foundation -framework AppKit -framework OpenGL -framework CoreVideo -ltcc -lm -w
	EXT = 
endif
ifeq ($(detected_OS),Linux)
    LIBS := -lX11 -lGL -lXrandr -ltcc -lm
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
	cp -r test.c include/* ./RSGL_engine$(EXT) run.sh run.bat ./release