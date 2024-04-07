outname=corn_healing_blade
outdir=out/
webdir=web/
port=8808


run: linux
	./$(outdir)$(outname)
linux:
	-mkdir $(outdir)
	gcc src/main.c  -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -lm -o $(outdir)$(outname)
wasm:
	-mkdir $(outdir)
	-mkdir $(webdir)
	emcc src/main.c src/util/*.c --shell-file src/web/base.html   -s USE_SDL=2 -s USE_SDL_IMAGE=2 -lSDL --preload-file res -s ALLOW_MEMORY_GROWTH=1 -s SDL2_IMAGE_FORMATS='["png"]' -o $(webdir)$(outname).html
runweb: wasm
	cd $(webdir) && python3 -m http.server $(port)
	
compilecmd: clean 
	bear -- make
clean:
	-rm -r $(outdir)
	-rm -r $(webdir)
