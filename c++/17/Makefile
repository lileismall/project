SRC:=$(wildcard *.cc)
OBJS:=$(patsubst %.cc,%.o,$(SRC))
ELF:=asmoshou
CC:=g++
CFLAGS:=-Wall
$(ELF):$(OBJS)
	g++ $^ -o $@
.PYONY:clean
clean:
	rm -rf $(OBJS) $(ELF)
