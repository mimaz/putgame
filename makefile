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
GLFWAPP = ${BUILD_DIR}/putgame.elf

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

GLFWAPP_CXXFLAGS = ${COMMON_CFLAGS}
GLFWAPP_LDFLAGS = -lGL -lglfw

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

GLFWAPP_SRC = ${shell find glfw/ -name "*.cxx"}

##
 # objects
 ##
PRECOMPILER_OBJ = ${PRECOMPILER_SRC:%=${BUILD_DIR}/%.o}

LIBCORE_GLSL_OBJ = ${LIBCORE_GLSL_SRC:%=%.o}
LIBCORE_OBJ = ${LIBCORE_SRC:%=${BUILD_DIR}/%.o} ${LIBCORE_GLSL_OBJ}

LIBGAME_OBJ = ${LIBGAME_SRC:%=${BUILD_DIR}/%.o}

GLFWAPP_OBJ = ${GLFWAPP_SRC:%=${BUILD_DIR}/%.o}

##
 # basic rules
 ##

all: executable

precompiler: ${PRECOMPILER}

libcore: ${LIBCORE}

libgame: ${LIBGAME}

executable: ${GLFWAPP}

debug: ${GLFWAPP}
	gdb $<

clean:
	rm -rf ${BUILD_DIR}

run: ${GLFWAPP}
	${GLFWAPP}

##
 # executable rules
 ##
${GLFWAPP}: ${GLFWAPP_OBJ} ${LIBGAME} ${LIBCORE}
	${CXX} -o $@ ${GLFWAPP_LDFLAGS} $^

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
	${CXX} -o $@ ${LIBCORE_LDFLAGS} -shared $^

${BUILD_DIR}/%.cxx.o: %.cxx ${STD_HEADER} ${RES_HEADER}
	@mkdir -p ${dir $@}
	${CXX} -o $@ ${LIBCORE_CXXFLAGS} -c $<

${BUILD_DIR}/glsl/%.c.o: ${BUILD_DIR}/glsl/%.c
	@mkdir -p ${dir $@}
	${CC} -o $@ ${LIBCORE_CFLAGS} -c $<

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
