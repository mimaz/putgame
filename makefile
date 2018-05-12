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
LIBCORE_PCH = ${BUILD_DIR}/putgame/std.gch
LIBCORE_RES = ${BUILD_DIR}/putgame/res
LIBGAME = ${BUILD_DIR}/libputgame.so

##
 # compile flags
 ##
PRECOMPILER_CFLAGS = -O0 -Wall -MMD
PRECOMPILER_LDFLAGS = 

LIBCORE_CFLAGS = -O2 -Wall -MMD -fPIC -std=c11
LIBCORE_CXXFLAGS = -O2 -Wall -MMD -fPIC -std=c++17
LIBCORE_CXXFLAGS += -I${BUILD_DIR}/ -Iinclude/
LIBCORE_LDFLAGS = -pthread

LIBGAME_DFLAGS = -O -fPIC
LIBGAME_LDFLAGS =

CC = gcc
CXX = g++
CD = dmd

##
 # sources
 ##
LIBCORE_SRC_DIRS = world/ common/ glutils/ text/ gui/ math/

PRECOMPILER_SRC = ${shell find precompiler/ -name "*.c"}
LIBCORE_GLSL = ${shell find glsl/ -type f}
LIBCORE_GLSL_SRC = ${LIBCORE_GLSL:%=${BUILD_DIR}/%.c}
LIBCORE_SRC = ${shell find ${LIBCORE_SRC_DIRS} -maxdepth 1 -name "*.cxx"}
LIBGAME_SRC = ${shell find . -name "*.d"}

##
 # objects
 ##
PRECOMPILER_OBJ = ${PRECOMPILER_SRC:%=${BUILD_DIR}/%.o}
LIBCORE_GLSL_OBJ = ${LIBCORE_GLSL_SRC:%=%.o}
LIBCORE_OBJ = ${LIBCORE_SRC:%=${BUILD_DIR}/%.o} ${LIBCORE_GLSL_OBJ}
LIBGAME_OBJ = ${LIBGAME_SRC:%=${BUILD_DIR}/%.o}

all: libgame

precompiler: ${PRECOMPILER}

libcore: ${LIBCORE}

libgame: ${LIBGAME}

clean:
	rm -rf ${BUILD_DIR}

##
 # libgame rules
 ##
${LIBGAME}: ${LIBGAME_OBJ} ${LIBCORE}
	@mkdir -p ${dir $@}
	${CXX} ${LIBGAME_LDFLAGS} -o $@ -shared $^

${BUILD_DIR}/%.d.o: %.d
	${CD} ${LIBGAME_DFLAGS} -of=$@ -c $<

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
