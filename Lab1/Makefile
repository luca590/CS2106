CC = gcc
CCOPTS = -03 -Wall
DEPS = db.h

%.o: %.c $(DEPS)
	$(CC) $(CCOPTS) -c -o $@ $<

BINARIES = db.o
ALL = phonebook

all: $(ALL)

clean:
	rm -f $(ALL) $(BINARIES)

phonebook: phonebook.o $(BINARIES)
	$(CC) $(CCOPTS) $^ -o $@
