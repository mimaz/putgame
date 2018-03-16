##
 # Mieszko Mazurek <mimaz@gmx.com> 
 # 2018
 ##


PROJECT = putgame
BUILD_DIR = /tmp/${PROJECT}-build


TARGET = ${BUILD_DIR}/${PROJECT}.elf
PRECOMPILER = ${BUILD_DIR}/precompiler.elf

TARGET_CXXFLAGS = -Wall -O0 -MMD -I${BUILD_DIR}/pch
TARGET_LDFLAGS = -lglfw -lGLESv2

PRECOMPILER_CFLAGS = -Wall -O0
PRECOMPILER_LDFLAGS = 

TARGET_SRC = ${shell find . world/ common/ glutils/ -maxdepth 1 -name "*.cxx"}
PRECOMPILER_SRC = ${shell find precompiler/ -name "*.c"}

CC = gcc
CXX = g++

RESOURCE_IN_DIR = resources
RESOURCE_OUT_DIR = ${BUILD_DIR}/${RESOURCE_IN_DIR}
RESOURCE_HEADER = ${RESOURCE_OUT_DIR}/resource.h

${shell mkdir -p ${RESOURCE_OUT_DIR}}

RESOURCE_C_SRC = ${shell find ${RESOURCE_OUT_DIR} -name "*.c"}


TARGET_PCH_SRC = pch/putgame-std.hxx
TARGET_PCH_OBJ = ${BUILD_DIR}/${TARGET_PCH_SRC}.gch


TARGET_OBJ = ${TARGET_SRC:%=${BUILD_DIR}/%.o}
PRECOMPILER_OBJ = ${PRECOMPILER_SRC:%=${BUILD_DIR}/%.o}


ALL_OBJ = ${TARGET_OBJ} ${PRECOMPILER_OBJ}
ALL_DEP = ${OBJ:%.o=%.d}


all: ${TARGET}

run: ${TARGET}
	$<

clean:
	rm -rf ${BUILD_DIR}

precompiler: ${PRECOMPILER}

debug:
	gdb ${TARGET}


${BUILD_DIR}/%.gch: %
	@mkdir -p ${dir $@}
	${CXX} ${TARGET_CXXFLAGS} -c -xc++-header $< -o $@

${BUILD_DIR}/%.c.o: %.c
	@mkdir -p ${dir $@}
	${CC} ${PRECOMPILER_CFLAGS} -c $< -o $@

${BUILD_DIR}/%.cxx.o: %.cxx ${TARGET_PCH_OBJ} ${RESOURCE_HEADER}
	@mkdir -p ${dir $@}
	${CXX} ${TARGET_CXXFLAGS} -c $< -o $@

${TARGET}: ${TARGET_OBJ}
	${CXX} ${TARGET_LDFLAGS} $^ -o $@

${PRECOMPILER}: ${PRECOMPILER_OBJ}
	${CC} ${PRECOMPILER_LDFLAGS} $< -o $@

${RESOURCE_HEADER}: ${PRECOMPILER} ${RES_SRC}
	@mkdir -p ${dir $@} ${RESOURCE_IN_DIR}
	$< ${RESOURCE_OUT_DIR} $@ ${shell find ${RESOURCE_IN_DIR}}

-include ${ALL_DEP}
