##
 # Mieszko Mazurek <mimaz@gmx.com> 
 # 2018
 ##

BUILD_DIR = /tmp/putgame-build

##
 # targets
 ##
PRECOMPILER = ${BUILD_DIR}/putgame-precompiler
LIBCORE = ${BUILD_DIR}/libputgame-core.so
LIBGAME = ${BUILD_DIR}/libputgame.so
RES_HEADER = ${BUILD_DIR}/putgame/res
STD_HEADER = ${BUILD_DIR}/putgame/std.gch
EXECUTABLE = ${BUILD_DIR}/putgame.elf

##
 # compile flags
 ##
COMMON_FLAGS = -O0 -Wall -MMD -fPIC -Iinclude/ -I${BUILD_DIR}
COMMON_CFLAGS = ${COMMON_FLAGS} -std=c11
COMMON_CXXFLAGS = ${COMMON_FLAGS} -std=c++17

PRECOMPILER_CFLAGS = ${COMMON_FLAGS} -O1
PRECOMPILER_LDFLAGS = 

LIBCORE_CFLAGS = ${COMMON_CFLAGS}
LIBCORE_CXXFLAGS = ${COMMON_CXXFLAGS}
LIBCORE_LDFLAGS = -pthread -lGL

LIBGAME_CXXFLAGS = ${COMMON_CXXFLAGS}
LIBGAME_LDFLAGS =

EXECUTABLE_CFLAGS = ${COMMON_CFLAGS}
EXECUTABLE_LDFLAGS =

CC = gcc
CXX = g++

##
 # sources
 ##
LIBCORE_SRC_DIRS = world/ common/ glutils/ text/ gui/ math/

PRECOMPILER_SRC = ${shell find precompiler/ -name "*.c"}

LIBCORE_GLSL = ${shell find glsl/ -type f}
LIBCORE_GLSL_SRC = ${LIBCORE_GLSL:%=${BUILD_DIR}/%.c}
LIBCORE_SRC = ${shell find ${LIBCORE_SRC_DIRS} -maxdepth 1 -name "*.cxx"}

LIBGAME_SRC = ${shell find game/ -name "*.cxx"}

EXECUTABLE_SRC = ${shell find elf/ -name "*.c"}

##
 # objects
 ##
PRECOMPILER_OBJ = ${PRECOMPILER_SRC:%=${BUILD_DIR}/%.o}

LIBCORE_GLSL_OBJ = ${LIBCORE_GLSL_SRC:%=%.o}
LIBCORE_OBJ = ${LIBCORE_SRC:%=${BUILD_DIR}/%.o} ${LIBCORE_GLSL_OBJ}

LIBGAME_OBJ = ${LIBGAME_SRC:%=${BUILD_DIR}/%.o}

EXECUTABLE_OBJ = ${EXECUTABLE_SRC:%=${BUILD_DIR}/%.o}

##
 # basic rules
 ##

all: executable

precompiler: ${PRECOMPILER}

libcore: ${LIBCORE}

libgame: ${LIBGAME}

executable: ${EXECUTABLE}

clean:
	rm -rf ${BUILD_DIR}

run: ${EXECUTABLE}
	${EXECUTABLE}

##
 # executable rules
 ##
${EXECUTABLE}: ${EXECUTABLE_OBJ} ${LIBGAME} ${LIBCORE}
	${CC} -o $@ ${EXECUTABLE_LDFLAGS} $^

${BUILD_DIR}/%.c.o: %.c
	@mkdir -p ${dir $@}
	${CC} -o $@ ${EXECUTABLE_CFLAGS} -c $<

##
 # libgame rules
 ##
${LIBGAME}: ${LIBGAME_OBJ}
	@mkdir -p ${dir $@}
	${CXX} -o ${LIBGAME_LDFLAGS} $@ -shared $^

##
 # libcore rules
 ##
${LIBCORE}: ${LIBCORE_OBJ}
	${CXX} ${LIBCORE_LDFLAGS} -o $@ -shared $^

${BUILD_DIR}/%.cxx.o: %.cxx ${STD_HEADER} ${RES_HEADER}
	@mkdir -p ${dir $@}
	${CXX} ${LIBCORE_CXXFLAGS} -o $@ -c $<

${BUILD_DIR}/glsl/%.c.o: ${BUILD_DIR}/glsl/%.c
	@mkdir -p ${dir $@}
	${CC} ${LIBCORE_CFLAGS} -o $@ -c $<

${BUILD_DIR}/glsl/%.c: glsl/% ${PRECOMPILER}
	@mkdir -p ${dir $@}
	${PRECOMPILER} glsl $< $@

${STD_HEADER}: putgame/std
	@mkdir -p ${dir $@}
	${CXX} -o $@ ${LIBCORE_CXXFLAGS} -xc++-header -c $<

${RES_HEADER}: ${LIBCORE_GLSL_SRC}
	@mkdir -p ${dir $@}
	${PRECOMPILER} header $@ $^

##
 # precompiler rules
 ##
${PRECOMPILER}: ${PRECOMPILER_OBJ}
	${CC} -o $@ ${PRECOMPILER_LDFLAGS} $^

${BUILD_DIR}/precompiler/%.c.o: precompiler/%.c
	@mkdir -p ${dir $@}
	${CC} -o $@ ${PRECOMPILER_CFLAGS} -c $< 
