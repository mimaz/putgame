##
 # Mieszko Mazurek <mimaz@gmx.com> 
 # 2018
 ##

RELEASE ?= 0
USE_LTO ?= 0

BUILD_DIR = /tmp/putgame-build

##
 # targets
 ##
PRECOMPILER = ${BUILD_DIR}/putgame-precompiler
LIBGAME = ${BUILD_DIR}/libputgame.so
RES_HEADER = ${BUILD_DIR}/putgame/res
STD_HEADER = ${BUILD_DIR}/putgame/std.pch

##
 # compile flags
 ##
COMMON_FLAGS = -MMD -fPIC
COMMON_FLAGS += -Iinclude/ -I${BUILD_DIR}
COMMON_FLAGS += -DPLATFORM_${PLATFORM}
COMMON_CFLAGS = ${COMMON_FLAGS} -std=c11
COMMON_CXXFLAGS = ${COMMON_FLAGS} -std=c++17
COMMON_LDFLAGS = 

PRECOMPILER_CFLAGS = -O1
PRECOMPILER_LDFLAGS = -O1

LIBGAME_CFLAGS = ${COMMON_CFLAGS} -fvisibility=hidden
LIBGAME_CXXFLAGS = ${COMMON_CXXFLAGS} -fvisibility=hidden
LIBGAME_LDFLAGS = ${COMMON_LDFLAGS} 

LIBGAME_SRC_DIRS = world/ common/ glutils/ text/ gui/ math/ game/ putgame/


ifneq (${RELEASE},0)
	LIBGAME_CFLAGS += -O2
	LIBGAME_CXXFLAGS += -O2
	LIBGAME_LDFLAGS = -O2
else
	LIBGAME_CFLAGS += -Og -g -Wall
	LIBGAME_CXXFLAGS += -Og -g -Wall
	LIBGAME_LDFLAGS += -O0
endif

ifneq (${USE_LTO},0)
	LIBGAME_CFLAGS += -flto
	LIBGAME_CXXFLAGS += -flto
	LIBGAME_LDFLAGS += -flto
endif

HOST_CC = gcc
HOST_CXX = g++
TARGET_CC = ${TARGET}clang
TARGET_CXX = ${TARGET}clang++

##
 # sources & objects
 ##
PRECOMPILER_SRC = ${shell find precompiler/ -name "*.c"}
PRECOMPILER_OBJ = ${PRECOMPILER_SRC:%=${BUILD_DIR}/%.o}

GLSL_SRC = ${shell find glsl/ -type f}
GLSL_C_SRC = ${GLSL_SRC:%=${BUILD_DIR}/%.c}
GLSL_C_OBJ = ${GLSL_C_SRC:%=%.o}

LIBGAME_HDR = ${shell find ${LIBGAME_SRC_DIRS} -name "*.hxx"}
LIBGAME_SRC = ${shell find ${LIBGAME_SRC_DIRS} -name "*.cxx" -or -name "*.c"}
LIBGAME_OBJ = ${LIBGAME_SRC:%=${BUILD_DIR}/%.o} ${GLSL_C_OBJ}

##
 # basic rules
 ##

build_dir:
	@echo ${BUILD_DIR}

lib_file:
	@echo ${LIBGAME}

precompiler: ${PRECOMPILER}

libputgame: ${LIBGAME}

pch: ${STD_HEADER}

clean:
	rm -rf ${BUILD_DIR}

cleanall:
	rm -rf ${BUILD_DIR_BASE}

##
 # libgame rules
 ##
${LIBGAME}: ${LIBGAME_OBJ}
	@mkdir -p ${dir $@}
	${TARGET_CXX} ${LIBGAME_LDFLAGS} -shared -o $@ $^

${BUILD_DIR}/%.cxx.o: %.cxx ${STD_HEADER} ${RES_HEADER}
	@mkdir -p ${dir $@}
	${TARGET_CXX} ${LIBGAME_CXXFLAGS} -include-pch ${STD_HEADER} -o $@ -c $<

${BUILD_DIR}/java/%.c.o: java/%.c ${RES_HEADER}
	@mkdir -p ${dir $@}
	${TARGET_CC} ${LIBGAME_CFLAGS} -o $@ -c $<

${BUILD_DIR}/glsl/%.c.o: ${BUILD_DIR}/glsl/%.c
	@mkdir -p ${dir $@}
	${TARGET_CC} ${LIBGAME_CFLAGS} -o $@ -c $<

${BUILD_DIR}/glsl/%.c: glsl/% ${PRECOMPILER}
	@mkdir -p ${dir $@}
	${PRECOMPILER} glsl-source $< $@

${STD_HEADER}: putgame/std
	@mkdir -p ${dir $@}
	${TARGET_CXX} -xc++-header -c $< -o $@ ${LIBGAME_CXXFLAGS}

${RES_HEADER}: ${GLSL_C_SRC}
	@mkdir -p ${dir $@}
	${PRECOMPILER} glsl-header $@ $^

##
 # precompiler rules
 ##
${PRECOMPILER}: ${PRECOMPILER_OBJ}
	${HOST_CC} ${PRECOMPILER_LDFLAGS} -o $@ $^

${BUILD_DIR}/precompiler/%.c.o: precompiler/%.c
	@mkdir -p ${dir $@}
	${HOST_CC} ${PRECOMPILER_CFLAGS} -o $@ -c $< 

##
 # dependencies
 ##

ALL_OBJ = ${PRECOMPILER_OBJ}
ALL_OBJ += ${LIBGAME_OBJ}
ALL_OBJ += ${GLFW_APP_OBJ}
ALL_DEP = ${ALL_OBJ:%.o=%.d}

-include ${ALL_DEP}
