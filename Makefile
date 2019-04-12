CC = g++
LD = g++
CCFLAGS = -c -g
LDFLAGS = -lm -lpng -lz -L/usr/local/lib
BASE = image.o

all: final-part1 final-part2

final-part1:	final-part1.o $(BASE)
	$(LD) final-part1.o $(BASE) $(LDFLAGS) -o final-part1
final-part2:	final-part2.o $(BASE)
	$(LD) final-part2.o $(BASE) $(LDFLAGS) -o final-part2

clean:
	rm  $(BASE) final-part1.o final-part1 final-part2.o final-part2

.cc.o:
	$(CC) $(CCFLAGS) $<
