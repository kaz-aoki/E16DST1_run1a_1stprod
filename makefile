CXX = g++
CFLAGS = -pg -Wall -O3 -std=c++0x

SRCD = ./src
OBJD = ./obj
INCD = ./include
E16DAQ_DST_INCD = /ccj/u/kkanno/e16/E16DAQ/E16DAQ/E16DST
E16DAQ_LIB = /ccj/u/kkanno/e16/E16DAQ/install/lib64
ZLIB = -L/lib64 -lz
EXAD = ./tmp
BIND = .

ROOTFLAGS = $(shell /opt/FairSoft/jun19p2/bin/root-config --cflags)
ROOTLIBS = -L/opt/FairSoft/jun19p2/lib/root -lCore -lImt -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lROOTVecOps -lTree -lTreePlayer -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lThread -lMultiProc -lMinuit -lROOTDataFrame -pthread -Wl,-rpath,/opt/FairSoft/jun19p2/lib/root -lm -ldl -rdynamic
SRCF = $(wildcard $(SRCD)/*.cc)
OBJF = $(SRCF:%.cc=%.o)
TRGF = $(wildcard $(EXAD)/*.cc)
TARGETS = $(TRGF:$(EXAD)/%.cc=%)

CFLAGS += $(ROOTFLAGS) -I$(INCD) -I$(E16DAQ_DST_INCD)

.PHONY: clean all_clean

all: $(TARGETS)

$(TARGETS): $(OBJF)
	$(CXX) $(CFLAGS) -o $(BIND)/$@ $(EXAD)/$@.cc $(GPIBLIBS) $^ $(ROOTLIBS) -L$(E16DAQ_LIB) -lE16DST $(ZLIB)

.cc.o:
	$(CXX) $(CFLAGS) -o $@ -MMD -c $<

-include $(SRCF:%.cc=%.d)

clean:
	rm -f $(TARGETS)

allclean:
	rm -f $(TARGETS) $(SRCD)/*.o $(SRCD)/*.d
