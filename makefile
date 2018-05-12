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
EXECUTABLE = ${BUILD_DIR}/putgame.elf

##
 # compile flags
 ##
PRECOMPILER_CFLAGS = -O0 -Wall -MMD
PRECOMPILER_LDFLAGS = 

LIBCORE_CFLAGS = -O2 -Wall -MMD -fPIC -std=c11
LIBCORE_CXXFLAGS = -O2 -Wall -MMD -fPIC -std=c++17
LIBCORE_CXXFLAGS += -I${BUILD_DIR}/ -Iinclude/
LIBCORE_LDFLAGS = -pthread -lGL

LIBGAME_DFLAGS = -O -fPIC
LIBGAME_LDFLAGS =

EXECUTABLE_DFLAGS = -O
EXECUTABLE_LDFLAGS = 

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

LIBGAME_SRC = ${shell find game/ -name "*.d"}

EXECUTABLE_SRC = ${shell find elf/ -name "*.d"}

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
${EXECUTABLE}: ${EXECUTABLE_OBJ} ${LIBGAME}
	${CD} -of=$@ ${EXECUTABLE_LDFLAGS} $^

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
