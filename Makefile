CC = gcc
TCC = tinycc/tcc

LIBS := -static -lgdi32 -lm -lopengl32 -lwinmm -lm
WINTCC = -I./tinycc/win32/include -I./tinycc/win32/lib
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
	LIBS := -static -lshell32 -lwinmm -lgdi32 -lopengl32 
	EXT = .exe
	WINTCC = -I./tinycc/win32/include -I./tinycc/win32/lib
	EXT_TCC = .dll
endif
ifeq ($(detected_OS),Darwin)        # Mac OS X
	LIBS := -lm -framework Foundation -framework AppKit -framework OpenGL -framework CoreVideo
	EXT = 
	WINTCC = 
	EXT_TCC = .a
endif
ifeq ($(detected_OS),Linux)
    LIBS := -lXrandr -lX11 -lm -lGL -ldl -lpthread
	WINTCC =
	EXT =
	EXT_TCC = .a
endif

RSGL_engine: source/* include/*
	make tinycc/libtcc$(EXT_TCC)
	$(CC) source/main.c $(LIBS) -I./include -I./tinycc tinycc/libtcc$(EXT_TCC) -o $@

debug:
	make tinycc/libtcc$(EXT_TCC)
	$(CC) source/main.c $(LIBS) -I./include -I./tinycc tinycc/libtcc$(EXT_TCC) -o RSGL_engine
	./RSGL_engine$(EXT) test.c test2.c

tinycc:
	git clone https://repo.or.cz/tinycc.git

tinycc/libtcc$(EXT_TCC):
	make tinycc
	cd tinycc && ./configure && make

release_example:
	make RSGL_engine

	echo "char* objfiles[] = {\"test.o\", \"test2.o\"}; size_t objfiles_len = 2;" > ./include/objfiles.h
	$(TCC) -c -I./tinycc/include $(WINTCC) test.c 
	$(TCC) -c -I./tinycc/include $(WINTCC) test2.c 

	$(CC) source/release.c $(LIBS) -I./include -I./source -I./tinycc tinycc/libtcc$(EXT_TCC) -o test-release
	rm ./include/objfiles.h 

	mkdir -p release
	mkdir -p release/tinycc
	cp -r tinycc/include tinycc/runmain.o tinycc/libtcc1.a ./release/tinycc
	cp -r RSGL.h image.png ./release
	mv test-release test.o test2.o ./release

ifeq ($(EXT),.exe)
	cp tinycc/libtcc.dll ./release/
endif

RSGL.h:
	python create_header.py