CYSTUFF?=https://github.com/cyisfor/cystuff.git
CFLAGS+=-ggdb
CFLAGS+=-Icystuff/src
LINK=$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LDLIBS)

all: pack unpack

pack: pack.c cystuff/src/itoa.c
	$(LINK) -lm
unpack: unpack.c
	$(LINK)

cystuff/src/itoa.c:
	git clone $(CYSTUFF) cystuff
