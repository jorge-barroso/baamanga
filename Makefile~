CC=gcc
GG=g++
NAME=baamanga
srcdir=src
CFLAGS=-Wall -O2 -c
DBLAGS=-Wall -g -c
LDFLAGS=-lcurl
SOURCES=animea.c baamanga.c bmhelp.c bmopt.c bmver.c danboru.c dirs_check.c ehentai.c futahentai.c mangafox.c mangahere.c mangareader.c mangashare.c pown.c submanga.c write_data.c zerochan.c
OBJ=animea.o baamanga.o bmhelp.o bmopt.o bmver.o danboru.o dirs_check.o ehentai.o futahentai.o mangafox.o mangahere.o mangareader.o mangashare.o pown.o submanga.o write_data.o zerochan.o
DATA={AUTHORS,changelog,README.md}


all:

	cd $(srcdir);				\
	$(CC) $(SOURCES) $(CFLAGS);		\
	$(CC) $(OBJ) -o ../baamanga $(LDFLAGS)
	
debug:

	cd $(srcdir);				\
	$(CC) $(SOURCES) $(DBLAGS);		\
	$(CC) $(OBJ) -o ../baamanga $(LDFLAGS)
	

EXECUTABLE=$(NAME)
INSTALL = /usr/bin/install -c
INSTALLDATA = /usr/bin/install -c -m 644
prefix=/usr
bindir=$(DESTDIR)$(prefix)/bin
datadir=$(DESTDIR)$(docdir)/$(NAME)
licensedir=$(DESTDIR)$(prefix)/share/licenses/$(NAME)
docdir=$(prefix)/share/doc/
DESTDIR=

install:
	if [ ! -d $(bindir) ]; then mkdir -p $(bindir); fi
	if [ ! -d $(datadir) ]; then mkdir -p $(datadir); fi
	if [ ! -d $(licensedir) ]; then mkdir -p $(licensedir); fi	
	$(INSTALL) $(EXECUTABLE) $(bindir)/baamanga
	$(INSTALLDATA) $(DATA) $(datadir)
	$(INSTALLDATA) COPYING $(licensedir)
	
clean:
	if [ -f ./baamanga ];then rm baamanga; fi
	rm $(srcdir)/*.o
	
remove:
	rm $(DESTDIR)$(bindir)/baamanga
	rm -r $(DESTDIR)$(docdir)/
	rm -r $(DESTDIR)$(prefix)/share/licenses/$(NAME)