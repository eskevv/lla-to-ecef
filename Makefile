CC = g++

CFLAGS = -Wall -g

SRCS = src/main.cpp 

OBJS = $(SRCS:.cpp=.o)

MAIN = lla-to-ecef

.PHONY: clean 

all: $(MAIN)

$(MAIN): $(OBJS) 
	$(CC) $(CFLAGS) -o $(MAIN) $(OBJS)

.cpp.o:
	$(CC) $(CFLAGS) -c $<  -o $@

clean:
	$(RM) src/*.o
