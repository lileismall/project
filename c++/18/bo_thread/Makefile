SRC:=$(wildcard *.cc)
OBJS:=$(patsubst %.cc,%.o,$(SRC))
ELF:=testThread
CC:=g++
CFLAGS:=-Wall 
$(ELF):$(OBJS)
	g++ $^ -o $@ -lpthread
.PYONY:clean
clean:
	rm -rf $(OBJS) $(ELF)
