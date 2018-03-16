##
 # Mieszko Mazurek <mimaz@gmx.com> 
 # 2018
 ##

ifndef PUTGAME_BUILD
$(error PUTGAME_BUILD is not set)
endif

TARGET = ${PUTGAME_BUILD}/precompiler
BUILD_DIR = ${PUTGAME_BUILD}/precompiler-obj
CFLAGS = -Wall -O0

OBJ = ${BUILD_DIR}/main.o

all: ${TARGET}

clean:
	rm -rf ${BUILD_DIR}

run: ${TARGET}
	$<

${TARGET}: ${OBJ}
	${CC} ${LDFLAGS} $^ -o $@

${BUILD_DIR}/%.o: %.c
	@mkdir -p ${dir $@}
	${CC} ${CFLAGS} -c $< -o $@

.PHONY: all clean
