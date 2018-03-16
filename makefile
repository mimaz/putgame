##
 # Mieszko Mazurek <mimaz@gmx.com> 
 # 2018
 ##

PROJECT = putgame
BUILD_DIR = /tmp/${PROJECT}-build
ELF = ${BUILD_DIR}/${PROJECT}.elf
CXXFLAGS = -Wall -O0 -MMD -I${BUILD_DIR}/pch
LDFLAGS = -lglfw -lGLESv2

PRECOMPILER = ${BUILD_DIR}/precompiler
PRECOMPILER_MAKE = ${MAKE} -C precompiler/ PUTGAME_BUILD=${BUILD_DIR}

SRC_DIRS = . world/ common/ glutils/
SRC = ${shell find ${SRC_DIRS} -maxdepth 1 -name "*.cxx"}
PCH = pch/putgame-std.hxx

OBJ = ${SRC:%.cxx=${BUILD_DIR}/%.o}

DEP = ${OBJ:%.o=%.d}


all: ${ELF}

run: ${ELF}
	$<

clean: 
	rm -rf ${BUILD_DIR}

precompiler: ${PRECOMPILER}

debug:
	gdb ${ELF}

${ELF}: ${OBJ}
	${CXX} ${LDFLAGS} $^ -o $@

${BUILD_DIR}/${PCH}.gch: ${PCH}
	@mkdir -p ${dir $@}
	${CXX} ${CXXFLAGS} -c -xc++-header $< -o $@

${BUILD_DIR}/%.o: %.cxx ${BUILD_DIR}/${PCH}.gch
	@mkdir -p ${dir $@}
	${CXX} ${CXXFLAGS} -c $< -o $@

${PRECOMPILER}: 
	${PRECOMPILER_MAKE} all

-include ${DEP}
