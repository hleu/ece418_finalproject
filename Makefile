CC = g++
LD = g++
CCFLAGS = -c -g
LDFLAGS = -lm -lpng -lz -L/usr/local/lib
BASE = image.o

all: final-part1 final-part2 final-part3 final-part4

final-part1:	final-part1.o $(BASE)
	$(LD) final-part1.o $(BASE) $(LDFLAGS) -o final-part1
final-part2:	final-part2.o imagefft.o $(BASE)
	$(LD) final-part2.o imagefft.o $(BASE) $(LDFLAGS) -o final-part2
final-part3:	final-part3.o $(BASE)
	$(LD) final-part3.o $(BASE) $(LDFLAGS) -o final-part3
final-part4:	final-part4.o $(BASE)
	$(LD) final-part4.o $(BASE) $(LDFLAGS) -o final-part4
final-part5:	final-part5.o $(BASE)
	$(LD) final-part5.o $(BASE) $(LDFLAGS) -o final-part5
lab10-bitplanes:	lab10-bitplanes.o $(BASE)
	$(LD) lab10-bitplanes.o $(BASE) $(LDFLAGS) -o lab10-bitplanes

clean:
	rm  $(BASE) final-part1.o final-part1 final-part2.o final-part2 final-part3.o final-part3 final-part4.o final-part4 final-part5.o final-part5 lab10-bitplanes.o lab10-bitplanes

.cc.o:
	$(CC) $(CCFLAGS) $<
