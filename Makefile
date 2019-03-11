CC := gcc
TESTOUT := hashmapc_test

SRC := src
INCL := include
BUILD := build
TEST := test
EXTS := externals

override CFLAGS += -std=c99 -g -Wall -I$(INCL) -I$(EXTS)/MurmurHash
LFLAGS := 

DEPS := \
	$(BUILD)/MurmurHash3.o	\
	$(BUILD)/hashmap_c.o

.PHONY: all clean test

all: mkbuilddir $(DEPS) test

lib: $(DEPS)
	@mkdir -p $(BUILD)
	ar rcs $(BUILD)/libhashmapc.a $^

mkbuilddir:
	@mkdir -p $(BUILD)

$(BUILD)/MurmurHash3.o: $(EXTS)/MurmurHash/MurmurHash3.c $(EXTS)/MurmurHash/MurmurHash3.h
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD)/hashmap_c.o: $(SRC)/hashmap_c.c $(INCL)/hashmap_c.h
	$(CC) $(CFLAGS) -c $< -o $@

test: mkbuilddir $(TEST)/test.c $(BUILD)/hashmap_c.o $(BUILD)/MurmurHash3.o
	$(CC) $(CFLAGS) -c $(TEST)/test.c -o $(BUILD)/test.o
	$(CC) $(LFLAGS) $(BUILD)/test.o $(BUILD)/hashmap_c.o $(BUILD)/MurmurHash3.o -o $(TESTOUT) 

clean:
	rm -f *.o
	rm -f $(TESTOUT)
	rm -rf $(BUILD)
	rm -rf *.dSYM
