# Linux (default)
#https://pt.stackoverflow.com/questions/331749/n%C3%A3o-foi-possivel-localizar-lgl
EXE = main
LDFLAGS = -lGL -lGLU -lglut -lm -lSDL2 -lSDL2_mixer

$(EXE) : pong.c
	gcc -o $@ $< $(CFLAGS) $(LDFLAGS)
