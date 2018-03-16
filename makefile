##
 # Mieszko Mazurek <mimaz@gmx.com> 
 # 2018
 ##


PROJECT = putgame
BUILD_DIR = /tmp/${PROJECT}-build

CC = gcc
CXX = g++

CXXFLAGS = -Wall -O0 -MMD -I${BUILD_DIR}/pch
CFLAGS = -Wall -O0
LDFLAGS = -lglfw -lGLESv2

TARGET = ${BUILD_DIR}/${PROJECT}.elf
PRECOMPILER = ${BUILD_DIR}/precompiler.elf

RES_SRC = resouces/
RES_DST = ${BUILD_DIR}/resources
RES_INC = ${RES_DST}/resources.h

${shell mkdir -p ${RES_DST}}

RES_SRC = ${shell find ${RES_DST} -name "*.c"}


PCH = pch/putgame-std.hxx


TARGET_SRC = ${shell find . world/ common/ glutils/ -maxdepth 1 -name "*.cxx"}

PRECOMPILER_SRC = ${shell find precompiler/ -name "*.c"}


TARGET_OBJ = ${TARGET_SRC:%=${BUILD_DIR}/%.o}
PRECOMPILER_OBJ = ${PRECOMPILER_SRC:%=${BUILD_DIR}/%.o}

OBJ = ${TARGET_OBJ} ${PRECOMPILER_OBJ}
DEP = ${OBJ:%.o=%.d}


all: ${TARGET}

run: ${TARGET}
	$<

clean:
	rm -rf ${BUILD_DIR}

precompiler: ${PRECOMPILER}

debug:
	gdb ${TARGET}

${TARGET}: ${TARGET_OBJ}
	${CXX} ${LDFLAGS} $^ -o $@

${BUILD_DIR}/%.gch: %
	@mkdir -p ${dir $@}
	${CXX} ${CXXFLAGS} -c -xc++-header $< -o $@

${BUILD_DIR}/%.c.o: %.c
	@mkdir -p ${dir $@}
	${CC} ${CFLAGS} -c $< -o $@

${BUILD_DIR}/%.cxx.o: %.cxx ${BUILD_DIR}/${PCH}.gch ${RES_INC}
	@mkdir -p ${dir $@}
	${CXX} ${CXXFLAGS} -c $< -o $@

${PRECOMPILER}: ${PRECOMPILER_OBJ}
	${CC} ${LDFLAGS} $< -o $@

${RES_INC}: ${PRECOMPILER} ${RES_SRC}
	@mkdir -p ${dir $@} ${RES_SRC}
	$< ${RES_DST} $@ ${RES_SRC}

-include ${DEP}
