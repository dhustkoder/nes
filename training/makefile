
compile:
	../cc65/bin/cc65.exe -tnes *.c -I../neslib/  -O0  # compile
	../cc65/bin/ca65.exe -tnes *.s       # assemble
	../cc65/bin/cl65.exe -tnes *.o -l../cc65/bin/lib/nes.lib -o test.nes  # link