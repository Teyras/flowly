PROG=flowly
OBJDIR=build
SRCDIR=src
CFLAGS=-std=gnu89 -Wall
LDFLAGS=-lrt -lpthread

FILES=config flowstat list output sflow utils routing
OBJS=$(FILES:%=$(OBJDIR)/%.o)

all: $(OBJDIR) $(PROG)

$(PROG): $(OBJS) $(SRCDIR)/$(PROG).c
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(SRCDIR)/$(PROG).c $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) -c $(CFLAGS) -o $@  $<

$(OBJDIR):
	mkdir -p $@

clean:
	- rm -f $(PROG)
	- rm -rf $(OBJDIR)
