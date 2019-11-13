CXX=g++
IDIR=./include
CFLAGS=-I$(IDIR) -fPIC `pkg-config --cflags --libs Qt5Widgets opencv4` 
ODIR=./obj
#OBJ=$(shell ls include |sed -E 's/([^\b]+).hpp/obj\/\1.o/g')
_OBJS = main.o matrics.o
OBJS = $(patsubst %,$(ODIR)/%,$(_OBJS))

#OBJSRC=$(shell ls include |sed -E 's/([^\b]+)/include\/\1/g')

$(ODIR)/%.o:%.cpp 
	$(CXX) -o $@ -c $< $(CFLAGS) 
main:$(OBJS)
	$(CXX) -o $@ $^ $(CFLAGS)
clean:
	rm -rf $(ODIR)/*.o
	rm -f main



