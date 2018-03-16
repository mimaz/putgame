##
 # Mieszko Mazurek <mimaz@gmx.com> 
 # 2018
 ##


PROJECT = putgame
BUILD_DIR = /tmp/${PROJECT}-build
GEN_DIR = gen


TARGET = ${BUILD_DIR}/${PROJECT}
PRECOMPILER = ${BUILD_DIR}/precompiler/precompiler

RESOURCE_GLSL = ${shell find . -name "*.glsl"}
RESOURCE_ALL = ${RESOURCE_GLSL}
RESOURCE_C_HEADER = ${GEN_DIR}/putgame-resource.h

RESOURCE_C_SRC = ${RESOURCE_ALL:%=${GEN_DIR}/%.c}
RESOURCE_C_OBJ = ${RESOURCE_C_SRC:%=${BUILD_DIR}/%.o}

CFLAGS = -Wall -O0 -MMD -I${dir ${RESOURCE_C_HEADER}}

TARGET_CXXFLAGS = -Wall -O0 -MMD -I${BUILD_DIR}/pch ${CFLAGS}
TARGET_LDFLAGS = -lglfw -lGLESv2

PRECOMPILER_CFLAGS = -Wall -O0 ${CFLAGS}
PRECOMPILER_LDFLAGS = 

TARGET_SRC = ${shell find . world/ common/ glutils/ -maxdepth 1 -name "*.cxx"}
PRECOMPILER_SRC = ${shell find precompiler/ -name "*.c"}

CC = gcc
CXX = g++


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

pch: ${TARGET_PCH_OBJ}

precompiler: ${PRECOMPILER}

prec: precompiler

res: ${RESOURCE_C_HEADER}

debug:
	gdb ${TARGET}


${BUILD_DIR}/%.gch: % 
	@mkdir -p ${dir $@}
	${CXX} ${TARGET_CXXFLAGS} -c -xc++-header $< -o $@

${BUILD_DIR}/%.c.o: %.c
	@mkdir -p ${dir $@}
	${CC} ${PRECOMPILER_CFLAGS} -c $< -o $@

${BUILD_DIR}/%.cxx.o: %.cxx ${TARGET_PCH_OBJ} ${RESOURCE_C_HEADER}
	@mkdir -p ${dir $@}
	${CXX} ${TARGET_CXXFLAGS} -c $< -o $@

${GEN_DIR}/%.c: % ${PRECOMPILER}
	@mkdir -p ${dir $@}
	${PRECOMPILER} source $< $@

${TARGET}: ${TARGET_OBJ} ${RESOURCE_C_OBJ}
	${CXX} ${TARGET_LDFLAGS} $^ -o $@

${PRECOMPILER}: ${PRECOMPILER_OBJ}
	${CC} ${PRECOMPILER_LDFLAGS} $^ -o $@

${RESOURCE_C_HEADER}: ${RESOURCE_C_SRC}
	${PRECOMPILER} header $@ $^

-include ${ALL_DEP}
