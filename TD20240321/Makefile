#
# Makefile
#

# set the executable name
EXEC=app

CC=gcc
CFLAGS+= -std=c99 -Wall -g
CFLAGS+= -D=_XOPEN_SOURCE
LDLIBS:= -lm 

ODIR:=obj

SRC := $(wildcard *.c)
OBJS = $(patsubst %,$(ODIR)/%,$(SRC:.c=.o))

all: clean $(EXEC)

-include $(ODIR)/*.d

$(EXEC): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS) $(LDLIBS)

$(ODIR)/%.o: %.c | $(ODIR)
	$(CC) $(CFLAGS) -c $< -o $@ -MMD -MF $(@:.o=.d)

$(ODIR):
	mkdir $@

clean:
	$(RM) $(EXEC)
	$(RM) -rf $(ODIR)

.PHONY:	clean all test
.DEFAULT: all 
