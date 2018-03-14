##
 # Mieszko Mazurek <mimaz@gmx.com> 
 # 2018
 ##

PROJECT = putgame
BUILD_DIR = /tmp/${PROJECT}-build
ELF = ${BUILD_DIR}/${PROJECT}.elf
CXXFLAGS = -Wall -O0 -MMD -I${BUILD_DIR}/ `pkg-config --cflags glfw3`
LDFLAGS = `pkg-config --libs glfw3`

SRC = ${shell find . -name "*.cxx"}
PCH = putgame-std.hxx


OBJ = ${SRC:./%.cxx=${BUILD_DIR}/%.o}

DEP = ${OBJ:%.o=%.d}


all: ${ELF}

run: ${ELF}
	$<

clean: 
	rm -rf ${BUILD_DIR}

${ELF}: ${OBJ}
	${CXX} ${LDFLAGS} $^ -o $@

${BUILD_DIR}/${PCH}.gch: ${PCH}
	@mkdir -p ${dir $@}
	${CXX} ${CXXFLAGS} -c -xc++-header $< -o $@

${BUILD_DIR}/%.o: %.cxx ${BUILD_DIR}/${PCH}.gch
	@mkdir -p ${dir $@}
	${CXX} ${CXXFLAGS} -c $< -o $@

-include ${DEP}
