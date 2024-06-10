CC = gcc

LIBS :=-lgdi32 -lm -lopengl32 -lwinmm -ggdb -lm
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
	LIBS := -lm -framework Foundation -framework AppKit -framework OpenGL -framework CoreVideo$(STATIC)
	EXT = 
endif
ifeq ($(detected_OS),Linux)
    LIBS := -lXrandr -lX11 -lm -lGL -ldl -lpthread $(STATIC)
	EXT =
endif

tinycc:
	git clone https://repo.or.cz/tinycc.git

tinycc/libtcc.a:
	make tinycc
	cd tinycc && ./configure && make

RSGL_engine: source/* includ	e/*
	make tinycc/libtcc.a
	$(CC) source/main.c $(LIBS) -	I./include -I./tinycc tinycc/libtcc.a -o $@

debug:
	make tinycc/libtcc.a
	$(CC) source/main.c $(LIBS) -I./include -I./tinycc tinycc/libtcc.a -o RSGL_engine
	./RSGL_engine test.c

release_example:
	make RSGL_engine
	mkdir -p release
	mkdir -p release/tinycc
	cp -r tinycc/include tinycc/runmain.o tinycc/libtcc1.a ./release/tinycc
	cp -r test.c RSGL.h ./RSGL_engine$(EXT) run.sh run.bat SuperEasy.ttf image.png ./release

test:
	@for header in $(HEADER_FILES); do \
		while IFS= read -r line; do \
			if echo $$line | grep -q '^#ifdef [A-Z0-9_]*_IMPLEMENTATION'; then \
				break; \
			fi; \
			echo $$line >> $(OUTPUT_HEADER); \
		done < $$header; \
		echo "" >> $(OUTPUT_HEADER); \
	done