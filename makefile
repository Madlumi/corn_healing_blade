outname=corn_healing_blade
outdir=out/
webdir=web/
port=8808

rl=/home/madi/proj/c/raylib/
rlw=/home/madi/proj/c/raylibw/

run: linux
	./$(outdir)$(outname)
linux:
	-mkdir $(outdir)
	gcc src/main.c  -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -lm -o $(outdir)$(outname)
windows:
	-mkdir $(outdir)
	x86_64-w64-mingw32-gcc src/main.c -o $(outdir)$(outname).exe -L$(rl)src/ -I$(rl)src -lm  -lraylib
	cp $(rl)src/raylib.dll $(outdir)
	tar cf $(outdir)$(outname)_win.tar $(outdir)$(outname).exe $(outdir)raylib.dll
wasm:
	-mkdir $(outdir)
	-mkdir $(webdir)
	emcc src/main.c -sASYNCIFY -s USE_GLFW=3 -o web/corn_healing_blade.html -I/home/madi/proj/c/raylibw/src -L/home/madi/proj/c/raylibw/src -lm -lglfw -lraylib --shell-file src/web/base.html --preload-file res -s ALLOW_MEMORY_GROWTH=1

all: clean linux windows wasm

runweb: wasm
	cd $(webdir) && python3 -m http.server $(port)
	
compilecmd: clean 
	bear -- make
clean:
	-rm -r $(outdir)
	-rm -r $(webdir)
