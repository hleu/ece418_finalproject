CC = g++
LD = g++
CCFLAGS = -c -g 
LDFLAGS = -lm -lpng -lz -L/usr/local/lib
BASE = image.o

lab1:	lab1.o $(BASE)
	$(LD) lab1.o $(BASE) $(LDFLAGS) -o lab1

clean:
	rm  $(BASE) lab1 lab1.o 

.cc.o:
	$(CC) $(CCFLAGS) $<
