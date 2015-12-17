OSNAME= $(shell uname)
vpath %.h include

ifeq ($(OSNAME), Linux)
	CC=g++
else ifeq ($(OSNAME), Darwin)
	CC=clang++
else
	echo "Use Linux or MacOS to compile, please."
	exit
endif

TARGETS= problem_2
all: ${TARGETS}

${TARGETS}: include/*.h problem_2.cc

problem_2:
	${CC} problem_2.cc Graph_Matrix.cc -o problem_2 -g

clean:
	rm -f ${TARGETS}

