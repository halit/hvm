TARGET = main

SRC_EXT = .cpp
OBJ_EXT = .o
HDR_EXT = .h

COMPILER = g++
COMPILER_FLAGS = ${CFLAGS}

SRC = $(shell ls *${SRC_EXT})
HDR = $(shell ls *${HDR_EXT})
OBJ = $(shell ls *${SRC_EXT} | sed s\/${SRC_EXT}$$\/${OBJ_EXT}\/)

all: ${OBJ}
	${COMPILER} ${COMPILER_FLAGS} -o ${TARGET} ${OBJ}

%${OBJ_EXT}: %${SRC_EXT}
	${COMPILER} ${COMPILER_FLAGS} -c $< -o $@

tar:
	tar -czf $(TARGET).tar.gz $(SRC) $(HDR) Makefile

clean:
	@if `test -e ${TARGET}`; then \
	  rm ${TARGET}; \
	fi

	@for file in ${OBJ}; do \
	  if `test -e $$file`; \
	    then rm $$file; \
	  fi \
	done

	@if `test -e ${TARGET}.tar.gz`; then \
	  rm ${TARGET}.tar.gz; \
	fi

.PHONY: clean pkg
