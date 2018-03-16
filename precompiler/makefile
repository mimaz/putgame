##
 # Mieszko Mazurek <mimaz@gmx.com> 
 # 2018
 ##

ifndef BUILD_DIR
$(error BUILD_DIR is not defined)
endif

ifndef TARGET
$(error TARGET is not defined)
endif

CFLAGS = -Wall -O0
CC = gcc

SRC = ${shell find . -name "*.c"}
OBJ = ${SRC:./%.c=%.o}

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
