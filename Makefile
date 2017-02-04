all:
	gcc -g -std=c99 -DXK_MISCELLANY -DXK_LATIN1 *.c -lX11 -lm
