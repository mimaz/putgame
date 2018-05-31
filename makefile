##
 # Mieszko Mazurek <mimaz@gmx.com> 
 # 2018
 ##

HOST ?= x86_64-pc-linux-gnu-
ARCH ?= x86_64-linux
TARGET ?= x86_64-pc-linux-gnu-
PLATFORM ?= GNU_GLFW
RELEASE ?= 0

BUILD_DIR_BASE = /tmp/putgame-build
BUILD_DIR = ${BUILD_DIR_BASE}/${ARCH}

##
 # targets
 ##
PRECOMPILER = ${BUILD_DIR}/putgame-precompiler
LIBGAME = ${BUILD_DIR}/libputgame.so
RES_HEADER = ${BUILD_DIR}/putgame/res
STD_HEADER = ${BUILD_DIR}/putgame/std.gch
GLFW_APP = ${BUILD_DIR}/putgame.elf

##
 # compile flags
 ##

COMMON_FLAGS = -MMD -fPIC
COMMON_FLAGS += -Iinclude/ -I${BUILD_DIR}
COMMON_FLAGS += -DPLATFORM_${PLATFORM}
COMMON_CFLAGS = ${COMMON_FLAGS} -std=c11
COMMON_CXXFLAGS = ${COMMON_FLAGS} -std=c++14
COMMON_LDFLAGS = 

PRECOMPILER_CFLAGS = ${COMMON_FLAGS} -O1
PRECOMPILER_LDFLAGS = ${COMMON_LDFLAGS} -O0

LIBGAME_CXXFLAGS = ${COMMON_CXXFLAGS}
LIBGAME_CFLAGS = ${COMMON_CFLAGS}
LIBGAME_LDFLAGS = ${COMMON_LDFLAGS} 

ifeq (${RELEASE},0)
	LIBGAME_CFLAGS += -Og -g -Wall
	LIBGAME_CXXFLAGS += -Og -g -Wall
	LIBGAME_LDFLAGS += -O0
else
	LIBGAME_CFLAGS += -O2 -flto -fno-fat-lto-objects
	LIBGAME_CXXFLAGS += -O2 -flto -fno-fat-lto-objects
	LIBGAME_LDFLAGS = -O2 -flto
endif

ifeq (${PLATFORM},ANDROID)
	LIBGAME_SRC_DIRS += jni/
	LIBGAME_LDFLAGS += -lc -lm -lGLESv3 -lz -llog -lstdc++
endif

GLFW_APP_CXXFLAGS = ${COMMON_CFLAGS}
GLFW_APP_LDFLAGS = ${COMMON_LDFLAGS} -lGL -lglfw -lpthread

HOST_CC = ${HOST}gcc
HOST_CXX = ${HOST}g++
TARGET_CC = ${TARGET}gcc
TARGET_CXX = ${TARGET}g++

##
 # sources & objects
 ##
LIBGAME_SRC_DIRS = world/ common/ glutils/ text/ gui/ math/ game/

ifeq (${PLATFORM},ANDROID)
	LIBGAME_SRC_DIRS += jni/
endif

PRECOMPILER_SRC = ${shell find precompiler/ -name "*.c"}
PRECOMPILER_OBJ = ${PRECOMPILER_SRC:%=${BUILD_DIR}/%.o}

GLSL_SRC = ${shell find glsl/ -type f}
GLSL_C_SRC = ${GLSL_SRC:%=${BUILD_DIR}/%.c}
GLSL_C_OBJ = ${GLSL_C_SRC:%=%.o}

LIBGAME_SRC = ${shell find ${LIBGAME_SRC_DIRS} -name "*.cxx"}
LIBGAME_OBJ = ${LIBGAME_SRC:%=${BUILD_DIR}/%.o}

GLFW_APP_SRC = ${shell find glfw/ -name "*.cxx"}
GLFW_APP_OBJ = ${GLFW_APP_SRC:%=${BUILD_DIR}/%.o}

##
 # basic rules
 ##

all: glfw_app

build_dir:
	@echo ${BUILD_DIR}

glfw_app: ${GLFW_APP}

precompiler: ${PRECOMPILER}

libputgame: ${LIBGAME}

executable: ${GLFW_APP}

debug: ${GLFW_APP}
	gdb $<

clean:
	rm -rf ${BUILD_DIR}

cleanall:
	rm -rf ${BUILD_DIR_BASE}

run: ${GLFW_APP}
	${GLFW_APP}

##
 # executable rules
 ##
${GLFW_APP}: ${LIBGAME} ${GLFW_APP_OBJ} 
	${TARGET_CXX} ${GLFW_APP_LDFLAGS} -o $@ $^

##
 # libcore & libgame rules
 ##
${LIBGAME}: ${LIBGAME_OBJ} ${GLSL_C_OBJ}
	@mkdir -p ${dir $@}
	${TARGET_CXX} ${LIBGAME_LDFLAGS} -shared -o $@ $^

${BUILD_DIR}/%.cxx.o: %.cxx ${STD_HEADER} ${RES_HEADER}
	@mkdir -p ${dir $@}
	${TARGET_CXX} ${LIBGAME_CXXFLAGS} -o $@ -c $<

${BUILD_DIR}/glsl/%.c.o: ${BUILD_DIR}/glsl/%.c
	@mkdir -p ${dir $@}
	${TARGET_CC} ${LIBGAME_CFLAGS} -o $@ -c $<

${BUILD_DIR}/glsl/%.c: glsl/% ${PRECOMPILER}
	@mkdir -p ${dir $@}
	${PRECOMPILER} glsl $< $@

${STD_HEADER}: putgame/std
	@mkdir -p ${dir $@}
	${TARGET_CXX} ${LIBGAME_CXXFLAGS} -o $@ -xc++-header -c $<

${RES_HEADER}: ${GLSL_C_SRC}
	@mkdir -p ${dir $@}
	${PRECOMPILER} header $@ $^

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
ALL_OBJ += ${GLSL_C_OBJ}
ALL_OBJ += ${LIBGAME_OBJ}
ALL_OBJ += ${GLFW_APP_OBJ}
ALL_DEP = ${ALL_OBJ:%.o=%.d}

-include ${ALL_DEP}
