CC=gcc
NAME=baamanga
#CFLAGS=-c -Isrc
#LDFLAGS=-Og -Wall -lcurl
CFLAGS=-Og -Wall -lcurl
srcdir=./src
#SOURCES=$(srcdir)/{baamanga.c,bmver.c,danboru.c,dirs_check.c,ehentai.c,futahentai.c,mangafox.c,mangahere.c,mangareader.c,mangashare.c,pown.c,submanga.c,zerochan.c}
#OBJ=bmver.o danboru.o dirs_check.o ehentai.o futahentai.o mangafox.o mangahere.o mangareader.o mangashare.o pown.o submanga.o zerochan.o
MAIN=$(srcdir)/baamanga.c
DATA={AUTHORS,changelog,README.md}
EXECUTABLE=$(NAME)

all:
	$(CC) $(CFLAGS) $(MAIN) -o $(EXECUTABLE)
	

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
	
remove:
	rm $(DESTDIR)$(bindir)/baamanga
	rm -r $(DESTDIR)$(docdir)/
	rm -r $(DESTDIR)$(prefix)/share/licenses/$(NAME)