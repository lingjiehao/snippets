CFLAGS	?= -O2
WARNING_CFLAGS ?= -Wall -Wextra -Wformat=2 -Wno-format-nonliteral
WARNING_CXXFLAGS ?= -Wall -Wextra -Wformat=2 -Wno-format-nonliteral
LDFLAGS ?=

LOCAL_CFLAGS = $(WARNING_CFLAGS) -I./include -D_FILE_OFFSET_BITS=64
LOCAL_CXXFLAGS = $(WARNING_CXXFLAGS) -I./include -D_FILE_OFFSET_BITS=64
LOCAL_LDFLAGS =	\
		-L./lib\
		-lmbedcrypto

ifdef DEBUG
LOCAL_CFLAGS += -g3
endif

APPS = \
	hash/generic_sum \
	hash/hello

EXES = $(patsubst %,%$(EXEXT),$(APPS))

.SILENT:

.PHONY: all clean list

all: $(EXES)

hash/generic_sum$(EXEXT): hash/generic_sum.c
	echo "  CC    hash/generic_sum.c"
	$(CC) $(LOCAL_CFLAGS) $(CFLAGS) hash/generic_sum.c $(LOCAL_LDFLAGS) $(LDFLAGS) -o $@

hash/hello$(EXEXT): hash/hello.c
	echo "  CC    hash/hello.c"
	$(CC) $(LOCAL_CFLAGS) $(CFLAGS) hash/hello.c       $(LOCAL_LDFLAGS) $(LDFLAGS) -o $@

clean:
	rm -f $(EXES)
list:
	echo $(EXES)
