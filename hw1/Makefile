.PHONY: all clean

CXX:=clang++-8
CXXFLAGS:=-std=c++17 -stdlib=libc++ -Wall -Wextra --include="${CURDIR}/core_ext/ostream.hxx"
LDFLAGS:=-lc++abi -lc++fs

OBJS=main.o \
		 core_ext/ostream.o \
		 netstat/application.o \
		 netstat/connection_parser.o

%.o: %.cxx
	$(CXX) $(CXXFLAGS) -c $^ -o $@

all: hw1
clean:
	@rm $(OBJS) 2>/dev/null || true

hw1: $(OBJS)
	$(CXX) $(CXXFLAGS) -o hw1 $(OBJS) $(LDFLAGS)
