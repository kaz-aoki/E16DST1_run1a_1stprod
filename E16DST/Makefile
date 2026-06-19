CC = g++
CCFLAGS = -O3 -Wall -g -std=c++0x
INCDIR = -I./
AR = ar
ARFLAGS = rv

SRCD = ./
SRCS = $(SRCD)E16DST_DST0.cc \
       $(SRCD)E16DST_File.cc

LIB_STAT = ../lib64/libE16DST.a
OBJD = ../obj/

OBJS = $(SRCS:$(SRCD)%.cc=$(OBJD)%.o)

#all:
all: $(LIB_STAT)

$(LIB_STAT): $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

$(OBJD)%.o : $(SRCD)%.cc
	$(CC) $(CCFLAGS) $(INCDIR) -c $< -o $@

clean:
	rm -rf $(OBJD)*.o $(LIB_STAT)

