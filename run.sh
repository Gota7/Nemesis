rm -f bin/Nemesis
date > res/BUILDTIME
mkdir -p build
cd build
cmake .. $@
cmake --build . -j`nproc`
cd ..
bin/Nemesis