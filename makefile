##
 # Mieszko Mazurek <mimaz@gmx.com> 
 # 2018
 ##

PROJECT = putgame
BUILD_DIR = /tmp/${PROJECT}-build
TARGET = ${BUILD_DIR}/${PROJECT}.elf
CXXFLAGS = -Wall -O0 -MMD -I${BUILD_DIR}/pch
LDFLAGS = -lglfw -lGLESv2


PRECOMPILER = ${BUILD_DIR}/precompiler
PRECOMPILER_MAKE = ${MAKE} -C precompiler/ BUILD_DIR=${BUILD_DIR} TARGET=${PRECOMPILER}


RES_SRC = resouces/
RES_DST = ${BUILD_DIR}/resources
RES_INC = ${RES_DST}/resources.h
RES_SRC = ${shell find ${RES_DST} -name "*.c"}


SRC_DIRS = . world/ common/ glutils/
SRC = ${shell find ${SRC_DIRS} -maxdepth 1 -name "*.cxx"}
PCH = pch/putgame-std.hxx

OBJ = ${SRC:%.cxx=${BUILD_DIR}/%.o}
DEP = ${OBJ:%.o=%.d}


all: ${TARGET}

run: ${TARGET}
	$<

clean:
	rm -rf ${BUILD_DIR}

precompiler: ${PRECOMPILER}

debug:
	gdb ${TARGET}

${TARGET}: ${OBJ}
	${CXX} ${LDFLAGS} $^ -o $@

${BUILD_DIR}/%.gch: %
	@mkdir -p ${dir $@}
	${CXX} ${CXXFLAGS} -c -xc++-header $< -o $@

${BUILD_DIR}/%.o: %.cxx ${BUILD_DIR}/${PCH}.gch ${RES_INC}
	@mkdir -p ${dir $@}
	${CXX} ${CXXFLAGS} -c $< -o $@

${PRECOMPILER}: 
	${PRECOMPILER_MAKE} all

${RES_INC}: ${PRECOMPILER} ${RES_SRC}
	$< --dst ${RES_DST} --header $@ $^

-include ${DEP}
