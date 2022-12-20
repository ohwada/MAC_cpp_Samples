## change log 
## 2022-06-01 K.OHWADA
 ## not read /proc/cpuinfo

rdrand: rdrand.c
#	@grep  -q rdrand /proc/cpuinfo
	cc -O3 rdrand.c -o bin/rdrand

install:
	make rdrand
	install bin/rdrand $(HOME)/bin

clean:
	rm bin/rdrand
