CXX=g++
LD=g++
CFLAGS=-Wall -pedantic -std=c++17 -g

OBJS=main.o CVATRegister.o Company.o

all: headerify

headerify: $(OBJS)
	$(LD) -o $@ $^
	rm -f $(OBJS)

clean:
	rm -f headerify $(OBJS)

%.o: %.cpp
	$(CXX) $(CFLAGS) -c $<

