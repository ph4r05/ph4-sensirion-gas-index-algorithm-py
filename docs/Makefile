algorithm_sources = sensirion_gas_index_algorithm.c

LDFLAGS = -lm
CFLAGS = -Os -Wall -fstrict-aliasing -Wstrict-aliasing=1 -Wsign-conversion -fPIC -I.

ifdef CI
    CFLAGS += -Werror
endif

.PHONY: all clean


all: clean algorithm_example_test

.ONESHELL:
algorithm_example_test:
	$(CC) $(CFLAGS) -o $@ ${algorithm_sources} algorithm_example_test.c $(LDFLAGS)

clean:
	$(RM) algorithm_example_test
