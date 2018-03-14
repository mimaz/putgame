##
 # Mieszko Mazurek <mimaz@gmx.com> 
 # 2018
 ##

PROJECT = putgame
BUILDDIR = /tmp/${PROJECT}-build
ELF = ${BUILDDIR}/${PROJECT}.elf
CXXFLAGS = -Wall -O0
LDFLAGS =

SRC = ${shell find . -name "*.cxx"}

OBJ = ${SRC:./%.cxx=${BUILDDIR}/%.o}
DEP = ${OBJ:%.o=%.d}

all: ${ELF}

run: ${ELF}
	./$<

clean: 
	rm -rf ${BUILDDIR}

${ELF}: ${OBJ}
	${CXX} ${LDFLAGS} $^ -o $@

${BUILDDIR}/%.o: %.cxx
	@mkdir -p ${dir $@}
	${CXX} ${CXXFLAGS} -c $< -o $@
