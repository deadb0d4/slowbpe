set -ex

BUILD_DIR="./build"

# 1. wipe the previous build
mkdir -p $BUILD_DIR && rm -rf ${BUILD_DIR}

# default behaviour is to build with asan, and run tests
if [[ "$1" == "" ]]; then
	# 2. generate files via cmake
	cmake -Wno-dev \
			-DCMAKE_BUILD_TYPE=Debug \
			-DASAN=1 \
			-B ${BUILD_DIR}

	# 3. build
	make -j4 -C ${BUILD_DIR}

	# 4. test
	ctest --test-dir ${BUILD_DIR} --output-on-failure --stop-on-failure
fi

if [[ "$1" == "bench" ]]; then
	# 2. generate files via cmake
	cmake -Wno-dev \
		-DCMAKE_BUILD_TYPE=Release \
		-B ${BUILD_DIR}

	# 3. build
	make -j4 -C ${BUILD_DIR}

	# TODO: 4. run benchmarks
fi
