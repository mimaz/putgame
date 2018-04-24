##
 # Mieszko Mazurek <mimaz@gmx.com> 
 # 2018
 ##


PROJECT = putgame

##
 # build directories
 ##
BASE_BUILD_DIR = /tmp/${PROJECT}-build

TARGET_BUILD_DIR = ${BASE_BUILD_DIR}
PRECOMPILER_BUILD_DIR = ${BASE_BUILD_DIR}
GLSL_C_DIR = ${BASE_BUILD_DIR}/glsl-src
GLSL_O_DIR = ${BASE_BUILD_DIR}/glsl-obj

##
 # targets
 ##
TARGET = ${TARGET_BUILD_DIR}/bin/${PROJECT}
PRECOMPILER = ${PRECOMPILER_BUILD_DIR}/resource-precompiler

##
 # resources
 ##
RESOURCE_HEADER = ${TARGET_BUILD_DIR}/putgame/res

GLSL = ${shell find glsl/ -type f -not -name ".*"}
GLSL_C = ${GLSL:%=${GLSL_C_DIR}/%.c}
GLSL_O = ${GLSL_C:${GLSL_C_DIR}/%=${GLSL_O_DIR}/%.o}

##
 # compile flags
 ##
CFLAGS = -Wall -O0 -MMD
LDFLAGS = 

TARGET_CFLAGS = -Iinclude/ ${CFLAGS}
TARGET_CXXFLAGS = -I${TARGET_BUILD_DIR} ${TARGET_CFLAGS} -std=c++17
TARGET_LDFLAGS = -lglfw -lGLESv2 ${LDFLAGS}

PRECOMPILER_CFLAGS = ${CFLAGS}
PRECOMPILER_LDFLAGS = ${LDFLAGS}

CC = gcc
CXX = g++


##
 # target sources
 ##
TARGET_SRC_DIRS = . world/ common/ glutils/ text/ gui/ game/ math/
TARGET_SRC = ${shell find ${TARGET_SRC_DIRS} -maxdepth 1 -name "*.cxx"}
PRECOMPILER_SRC = ${shell find precompiler/ -name "*.c"}


##
 # pre-compiler header
 ##
TARGET_PCH_SRC = putgame/std
TARGET_PCH_OBJ = ${TARGET_BUILD_DIR}/${TARGET_PCH_SRC}.gch


##
 # target objects
 ##
TARGET_OBJ = ${TARGET_SRC:%=${TARGET_BUILD_DIR}/%.o} ${GLSL_O}
PRECOMPILER_OBJ = ${PRECOMPILER_SRC:%=${PRECOMPILER_BUILD_DIR}/%.o}

ALL_OBJ = ${TARGET_OBJ} ${PRECOMPILER_OBJ}
ALL_DEP = ${ALL_OBJ:%.o=%.d}

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

res: ${RESOURCE_HEADER}

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
${TARGET_PCH_OBJ}: ${TARGET_PCH_SRC}
	@mkdir -p ${dir $@}
	${CXX} -xc++-header ${TARGET_CXXFLAGS} -c $< -o $@

##############################################

# glsl objects
${GLSL_O_DIR}/%.c.o: ${GLSL_C_DIR}/%.c
	@mkdir -p ${dir $@}
	${CC} ${TARGET_CFLAGS} -c $< -o $@

# glsl sources
${GLSL_C_DIR}/%.c: % ${PRECOMPILER}
	@mkdir -p ${dir $@}
	${PRECOMPILER} glsl $< $@
	
# auto-generated header
${RESOURCE_HEADER}: ${GLSL_C}
	@mkdir -p ${dir $@}
	${PRECOMPILER} header $@ $^

##############################################

# target objects
${TARGET_BUILD_DIR}/%.cxx.o: %.cxx ${RESOURCE_HEADER} ${TARGET_PCH_OBJ}
	@mkdir -p ${dir $@}
	${CXX} ${TARGET_CXXFLAGS} -c $< -o $@

# target executable
${TARGET}: ${TARGET_OBJ}
	@mkdir -p ${dir $@}
	${CXX} ${TARGET_LDFLAGS} $^ -o $@

-include ${ALL_DEP}
