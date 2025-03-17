#!/bin/bash
. ../../common.sh $1

# fetch source code
git clone https://github.com/miniupnp/ngiflib.git code
git -C code checkout 75b99202e4e57acab399ed07b4e8f94eddf1648a

# compile
echo "start compiling $PWD with $MODE"

rm -rf build_$MODE bin_$MODE
cp -r code build_$MODE || ( echo "[ERROR]: No code folder find!" && exit 1 )
pushd build_$MODE

make
ar cru libngiflib.a *.o

popd

mkdir -p bin_$MODE/bin
mkdir -p bin_$MODE/lib
cp build_$MODE/gif2tga bin_$MODE/bin

echo "end compiling $PWD with $MODE"