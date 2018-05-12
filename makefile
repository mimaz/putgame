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
EXECUTABLE = ${BUILD_DIR}/putgame.elf
LIBCORE_PCH = ${BUILD_DIR}/putgame/std.gch
LIBCORE_RES = ${BUILD_DIR}/putgame/res

##
 # compile flags
 ##
PRECOMPILER_CFLAGS = -O0 -Wall -MMD
PRECOMPILER_LDFLAGS = 

LIBCORE_CFLAGS = -O2 -Wall -MMD -fPIC -std=c11
LIBCORE_CXXFLAGS = -O2 -Wall -MMD -fPIC -std=c++17
LIBCORE_CXXFLAGS += -I${BUILD_DIR}/ -Iinclude/
LIBCORE_LDFLAGS = -pthread

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

##
 # objects
 ##
PRECOMPILER_OBJ = ${PRECOMPILER_SRC:%=${BUILD_DIR}/%.o}
LIBCORE_GLSL_OBJ = ${LIBCORE_GLSL_SRC:%=%.o}
LIBCORE_OBJ = ${LIBCORE_SRC:%=${BUILD_DIR}/%.o} ${LIBCORE_GLSL_OBJ}

all: libcore

precompiler: ${PRECOMPILER}

libcore: ${LIBCORE}

clean:
	rm -rf ${BUILD_DIR}

##
 # libcore rules
 ##
${LIBCORE}: ${LIBCORE_OBJ}
	${CXX} ${LIBCORE_LDFLAGS} -o $@ -shared $^

${BUILD_DIR}/%.cxx.o: %.cxx ${LIBCORE_PCH} ${LIBCORE_RES}
	@mkdir -p ${dir $@}
	${CXX} ${LIBCORE_CXXFLAGS} -o $@ -c $<

${BUILD_DIR}/glsl/%.c.o: ${BUILD_DIR}/glsl/%.c
	@mkdir -p ${dir $@}
	${CC} ${LIBCORE_CFLAGS} -o $@ -c $<

${BUILD_DIR}/glsl/%.c: glsl/% ${PRECOMPILER}
	@mkdir -p ${dir $@}
	${PRECOMPILER} glsl $< $@

${LIBCORE_PCH}: putgame/std
	@mkdir -p ${dir $@}
	${CXX} ${LIBCORE_CXXFLAGS} -o $@ -xc++-header -c $<

${LIBCORE_RES}: ${LIBCORE_GLSL_SRC}
	@mkdir -p ${dir $@}
	${PRECOMPILER} header $@ $^

##
 # precompiler rules
 ##
${PRECOMPILER}: ${PRECOMPILER_OBJ}
	${CC} ${PRECOMPILER_LDFLAGS} -o $@ $^

${BUILD_DIR}/precompiler/%.c.o: precompiler/%.c
	@mkdir -p ${dir $@}
	${CC} ${PRECOMPILER_CFLAGS} -o $@ -c $< 
