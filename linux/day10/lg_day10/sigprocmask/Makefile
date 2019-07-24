SRCS:=$(wildcard *.c)
TARGETS:=$(SRCS:%.c=%)
all:$(TARGETS)
%:%.c
	gcc $< -g -o $@
clean:
	rm $(TARGETS)
