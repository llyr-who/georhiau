BUILD_TYPE ?= Debug

CMAKE_ARGS := -DCMAKE_BUILD_TYPE=${BUILD_TYPE}

BUILDDIR := ./build

.PHONY: all
all: ${BUILDDIR}/Makefile
	@$(MAKE) -C ${BUILDDIR}

.PHONY: clean
clean:
	rm -rf ${BUILDDIR}

${BUILDDIR}/Makefile:
	cmake -S . -B ${BUILDDIR} ${CMAKE_ARGS}
