rm -f bin/Nemesis
date > res/BUILDTIME
mkdir -p build
cd build
cmake .. $@ -DSTATIC_BUILD=OFF -DDEBUG=ON
cmake --build . -j`nproc`
cd ..
bin/Nemesis