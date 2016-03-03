



compile:
	cc65 -tnes tests.c  -I../neslib/include -O3
	ca65 -tnes tests2.s
	ca65 -tnes tests.s 
	cl65 -tnes *.o -l../neslib/lib/nes.lib ../neslib/lib/neslib.o -otest.nes
