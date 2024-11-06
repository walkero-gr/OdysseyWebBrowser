
default: build

.PHONY: configure
configure:
	@echo "Configuring os4 build..."
	@rm -rf build && mkdir build
	@cd build && \
		cmake -DCMAKE_TOOLCHAIN_FILE=../Source/cmake/amigaos.cmake \
			-DCMAKE_CROSSCOMPILING=ON \
			-DPORT=MUI \
			..

.PHONY: build
build:
	@echo "Building os4..."
	@cd build && \
		make -j1

.PHONY: clean
clean:
	@echo "Cleaning os4..."
	@rm -rf build



# cmake -DUSE_CLIB4=$(USE_CLIB4) \
# -DCMAKE_CROSSCOMPILING=ON -DCMAKE_BUILD_TYPE=RelWithDebugInfo \
# -DCMAKE_TOOLCHAIN_FILE=$(realpath amigaos.cmake) -DCMAKE_DL_LIBS="syscall" \
# -DCMAKE_MODULE_PATH=$(realpath Source/cmake) \
# -DBUILD_SHARED_LIBS=NO -DPORT=AmigaOS -DENABLE_WEBCORE=1 -DENABLE_WEBKIT_LEGACY=1 -DLOG_DISABLED=0 \
# -DENABLE_OPENTYPE_MATH=0 \
# -DAMIGAOS_MINIMAL=1 -DROOTPATH="$(ROOTPATH)" \
# $(realpath ./))