CFLAGS+=-ggdb
LINK=$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LDLIBS)

all: pack unpack

pack: pack.c
	$(LINK) -lm
unpack: unpack.c
	$(LINK)
