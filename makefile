##
 # Mieszko Mazurek <mimaz@gmx.com> 
 # 2018
 ##


PROJECT = putgame

##
 # build directories
 ##
BASE_BUILD_DIR = /tmp/${PROJECT}-build
TARGET_BUILD_DIR = ${BASE_BUILD_DIR}/target
GLSL_C_DIR = ${BASE_BUILD_DIR}/glsl-src
GLSL_O_DIR = ${BASE_BUILD_DIR}/glsl-obj
PRECOMPILER_BUILD_DIR = ${BASE_BUILD_DIR}/precompiler-build

##
 # targets
 ##
TARGET = ${TARGET_BUILD_DIR}/${PROJECT}
PRECOMPILER = ${PRECOMPILER_BUILD_DIR}/precompiler/precompiler

##
 # resources
 ##
RESOURCE_H = ${TARGET_BUILD_DIR}/putgame-resource.h

GLSL = ${shell find glsl/ -type f}
GLSL_C = ${GLSL:%=${GLSL_C_DIR}/%.c}
GLSL_O = ${GLSL_C:${GLSL_C_DIR}/%=${GLSL_O_DIR}/%.o}

##
 # compile flags
 ##
CFLAGS = -Wall -O0 -MMD
LDFLAGS = 

TARGET_CFLAGS = ${CFLAGS}
TARGET_CXXFLAGS = -I${TARGET_BUILD_DIR}/pch -I${TARGET_BUILD_DIR} ${TARGET_CFLAGS}
TARGET_LDFLAGS = -lglfw -lGLESv2 ${LDFLAGS}

PRECOMPILER_CFLAGS = ${CFLAGS}
PRECOMPILER_LDFLAGS = ${LDFLAGS}

CC = gcc
CXX = g++


##
 # target sources
 ##
TARGET_SRC = ${shell find . world/ common/ glutils/ -maxdepth 1 -name "*.cxx"}
PRECOMPILER_SRC = ${shell find precompiler/ -name "*.c"}


##
 # pre-compiler header
 ##
TARGET_PCH_SRC = pch/putgame-std.hxx
TARGET_PCH_OBJ = ${TARGET_BUILD_DIR}/${TARGET_PCH_SRC}.gch


##
 # target objects
 ##
TARGET_OBJ = ${TARGET_SRC:%=${TARGET_BUILD_DIR}/%.o} ${GLSL_O}
PRECOMPILER_OBJ = ${PRECOMPILER_SRC:%=${PRECOMPILER_BUILD_DIR}/%.o}

ALL_OBJ = ${TARGET_OBJ} ${PRECOMPILER_OBJ}
ALL_DEP = ${OBJ:%.o=%.d}

##
 # phony rules
 ##
all: ${TARGET}

run: ${TARGET}
	$<

clean:
	rm -rf ${BASE_BUILD_DIR}

pch: ${TARGET_PCH_OBJ}

prec: ${PRECOMPILER}

res: ${RESOURCE_H}

debug:
	gdb ${TARGET}

.PHONY: all run clean pch prec res debug

##
 # build rules
 ##

# precompiler objects
${PRECOMPILER_BUILD_DIR}/%.c.o: %.c
	@mkdir -p ${dir $@}
	${CC} ${PRECOMPILER_CFLAGS} -c $< -o $@

# precompiler executable
${PRECOMPILER}: ${PRECOMPILER_OBJ}
	${CC} ${PRECOMPILER_LDFLAGS} $^ -o $@
	
##############################################

# pre-compiled header
${TARGET_BUILD_DIR}/%.gch: % 
	@mkdir -p ${dir $@}
	${CXX} ${TARGET_CXXFLAGS} -c -xc++-header $< -o $@

##############################################

# auto-generated objects
${GLSL_O_DIR}/%.c.o: ${GLSL_C_DIR}/%.c
	@mkdir -p ${dir $@}
	${CC} ${TARGET_CXXFLAGS} -c $< -o $@

# auto-generated sources
${GLSL_C_DIR}/%.c: % ${PRECOMPILER}
	@mkdir -p ${dir $@}
	${PRECOMPILER} glsl $< $@
	
# auto-generated header
${RESOURCE_H}: ${GLSL_C}
	${PRECOMPILER} header $@ $^

##############################################

# target objects
${TARGET_BUILD_DIR}/%.cxx.o: %.cxx ${TARGET_PCH_OBJ} ${RESOURCE_H}
	@mkdir -p ${dir $@}
	${CXX} ${TARGET_CXXFLAGS} -c $< -o $@

# target executable
${TARGET}: ${TARGET_OBJ}
	${CXX} ${TARGET_LDFLAGS} $^ -o $@

-include ${ALL_DEP}
