CC = gcc

LIBS := -Bstatic -no-pthread -lgdi32 -lm -lopengl32 -lwinmm -ggdb -lm
EXT = .exe
EXT_TCC = .dll

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
	LIBS := -Bstatic -no-pthread -ggdb -lshell32 -lwinmm -lgdi32 -lopengl32 
	EXT = .exe
	EXT_TCC = .dll
endif
ifeq ($(detected_OS),Darwin)        # Mac OS X
	LIBS := -lm -framework Foundation -framework AppKit -framework OpenGL -framework CoreVideo
	EXT = 
	EXT_TCC = .a
endif
ifeq ($(detected_OS),Linux)
    LIBS := -lXrandr -lX11 -lm -lGL -ldl -lpthread
	EXT =
	EXT_TCC = .a
endif

tinycc:
	git clone https://repo.or.cz/tinycc.git

tinycc/libtcc$(EXT_TCC):
	make tinycc
	cd tinycc && ./configure && make

RSGL_engine: source/* include/*
	make tinycc/libtcc$(EXT_TCC)
	$(CC) source/main.c $(LIBS) -I./include -I./tinycc tinycc/libtcc$(EXT_TCC) -o $@

debug:
	make tinycc/libtcc$(EXT_TCC)
	$(CC) source/main.c $(LIBS) -I./include -I./tinycc tinycc/libtcc$(EXT_TCC) -o RSGL_engine
	./RSGL_engine test.c

release_example:
	make RSGL_engine
	mkdir -p release
	mkdir -p release/tinycc
	cp -r tinycc/include tinycc/runmain.o tinycc/libtcc1.a ./release/tinycc
	cp -r test.c RSGL.h ./RSGL_engine$(EXT) run.sh run.bat SuperEasy.ttf image.png ./release
ifeq ($(detected_OS),Windows)
	cp tinycc/libtcc.dll ./release/tinycc
endif

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