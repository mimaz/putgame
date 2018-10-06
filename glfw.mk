##
 # Mieszko Mazurek <mimaz@gmx.com> 
 # 2018
 ##

PLATFORM = GLFW

include build.mk

GLFW_APP = ${BUILD_DIR}/putgame.elf

GLFW_APP_CFLAGS = ${COMMON_CFLAGS}
GLFW_APP_LDFLAGS = ${COMMON_LDFLAGS} -lGL -lglfw -lpthread

GLFW_APP_SRC = ${shell find glfw/ -name "*.c"}
GLFW_APP_OBJ = ${GLFW_APP_SRC:%=${BUILD_DIR}/%.o}

all: ${GLFW_APP}

run: ${GLFW_APP}
	${GLFW_APP}

debug: ${GLFW_APP}
	gdb $<

##
 # executable rules
 ##
${GLFW_APP}: ${LIBGAME} ${GLFW_APP_OBJ} 
	${TARGET_CC} ${GLFW_APP_LDFLAGS} -o $@ $^

${BUILD_DIR}/glfw/%.c.o: glfw/%.c ${RES_HEADER}
	@mkdir -p ${dir $@}
	${TARGET_CC} ${GLFW_APP_CFLAGS} -o $@ -c $<
