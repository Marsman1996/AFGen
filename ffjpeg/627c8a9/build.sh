#!/bin/bash
. ../../common.sh $1

# fetch source code
git clone https://github.com/rockcarry/ffjpeg.git code
git -C code checkout 627c8a922d699bccc7902c149ff658edc0e47bf9
wget -P ./code https://github.com/rockcarry/ffjpeg/files/2305428/CMakeLists.txt

# compile
echo "start compiling $PWD with $MODE"

rm -rf build_$MODE bin_$MODE
mkdir build_$MODE
pushd build_$MODE

cmake ../code -DCMAKE_INSTALL_PREFIX=$PWD/../bin_$MODE -DCMAKE_C_FLAGS="$CFLAGS" -DCMAKE_CXX_FLAGS="$CXXFLAGS"
make || exit 1

popd
mkdir -p bin_$MODE/bin
cp build_$MODE/ffjpeg bin_$MODE/bin


echo "end compiling $PWD with $MODE"