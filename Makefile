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
	

INSTALL = /usr/bin/install -D
INSTALLDATA = /usr/bin/install -D -m 644
prefix=/usr
bindir=$(prefix)/bin
docdir=$(prefix)/share/doc/$(NAME)
DESTDIR=

install:
	if [ ! -d $(DESTDIR)$(bindir) ]; then mkdir -p $(DESTDIR)$(bindir); fi
	$(INSTALL) $(EXECUTABLE) $(DESTDIR)$(bindir)/baamanga
	$(INSTALLDATA) $(DATA) $(DESTDIR)$(docdir)/
	$(INSTALLDATA) COPYING $(DESTDIR)$(prefix)/share/licenses/$(NAME)/
	
clean:
	if [ -f ./baamanga ];then rm baamanga; fi
	
remove:
	rm $(DESTDIR)$(bindir)/baamanga
	rm -r $(DESTDIR)$(docdir)/
	rm -r $(DESTDIR)$(prefix)/share/licenses/$(NAME)