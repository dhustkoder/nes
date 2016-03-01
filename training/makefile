



compile:
	cc65 -tnes tests2.c -I../neslib/ -O3
	cc65 -tnes tests.c  -I../neslib/ -O3
	ca65 -tnes tests2.s
	ca65 -tnes tests.s 
	cl65 -tnes *.o -l../neslib/nes.lib ../neslib/neslib.o  -otest.nes
