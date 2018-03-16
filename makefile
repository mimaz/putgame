##
 # Mieszko Mazurek <mimaz@gmx.com> 
 # 2018
 ##


PROJECT = putgame

##
 # build directories
 ##
TARGET_BUILD_DIR = /tmp/${PROJECT}-build
GEN_SRC_DIR = ${TARGET_BUILD_DIR}/gen-src
GEN_OBJ_DIR = ${TARGET_BUILD_DIR}/gen-obj
PRECOMPILER_BUILD_DIR = ${TARGET_BUILD_DIR}/precompiler-build

##
 # targets
 ##
TARGET = ${TARGET_BUILD_DIR}/${PROJECT}
PRECOMPILER = ${PRECOMPILER_BUILD_DIR}/precompiler/precompiler

##
 # resources
 ##
RESOURCE_GLSL = ${shell find . -name "*.glsl"}
RESOURCE_ALL = ${RESOURCE_GLSL}

RESOURCE_C_HEADER = ${GEN_SRC_DIR}/putgame-resource.h
RESOURCE_C_SRC = ${RESOURCE_ALL:%=${GEN_SRC_DIR}/%.c}
RESOURCE_C_OBJ = ${RESOURCE_C_SRC:${GEN_SRC_DIR}/%=${GEN_OBJ_DIR}/%.o}

##
 # compile flags
 ##
CFLAGS = -Wall -O0 -MMD
LDFLAGS = 

TARGET_CFLAGS = -I${GEN_SRC_DIR} ${CFLAGS}
TARGET_CXXFLAGS = -I${TARGET_BUILD_DIR}/pch ${TARGET_CFLAGS}
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
TARGET_OBJ = ${TARGET_SRC:%=${TARGET_BUILD_DIR}/%.o} ${RESOURCE_C_OBJ}
PRECOMPILER_OBJ = ${PRECOMPILER_SRC:%=${PRECOMPILER_BUILD_DIR}/%.o}

ALL_OBJ = ${TARGET_OBJ} ${PRECOMPILER_OBJ} ${RESOURCE_C_OBJ}
ALL_DEP = ${OBJ:%.o=%.d}

##
 # phony rules
 ##
all: ${TARGET}

run: ${TARGET}
	$<

clean:
	rm -rf ${TARGET_BUILD_DIR} ${PRECOMPILER_BUILD_DIR}

pch: ${TARGET_PCH_OBJ}

prec: ${PRECOMPILER}

res: ${RESOURCE_C_HEADER}

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
${GEN_OBJ_DIR}/%.c.o: ${GEN_SRC_DIR}/%.c
	@mkdir -p ${dir $@}
	${CC} ${TARGET_CXXFLAGS} -c $< -o $@

# auto-generated sources
${GEN_SRC_DIR}/%.c: % ${PRECOMPILER}
	@mkdir -p ${dir $@}
	${PRECOMPILER} resource $< $@
	
# auto-generated header
${RESOURCE_C_HEADER}: ${RESOURCE_C_SRC}
	${PRECOMPILER} header $@ $^

##############################################

# target objects
${TARGET_BUILD_DIR}/%.cxx.o: %.cxx ${TARGET_PCH_OBJ} ${RESOURCE_C_HEADER}
	@mkdir -p ${dir $@}
	${CXX} ${TARGET_CXXFLAGS} -c $< -o $@

# target executable
${TARGET}: ${TARGET_OBJ}
	${CXX} ${TARGET_LDFLAGS} $^ -o $@

-include ${ALL_DEP}
