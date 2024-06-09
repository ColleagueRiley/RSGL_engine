SET mypath=%~dp0
cd %mypath:~0,-1%
RSGL_engine.exe test.c --release