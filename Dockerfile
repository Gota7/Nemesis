# Debian.
FROM debian:bookworm

# Number of threads used to build.
ENV NUM_CORES=8

# What OS to use. Supports Linux, Darwin, Windows, and 3ds.
ENV OS="Linux"

# Static building.
ENV STATIC_BUILD=ON

# If the build is for debug purposes.
ENV DEBUG=OFF

# Extra cmake args (for toolchains).
ENV CMAKE_EXTRA=""

# Install necessary packages.
RUN apt-get update && apt-get install -y build-essential clang cmake libx11-dev libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev git
RUN apt-get install -y gcc-mingw-w64 g++-mingw-w64
RUN apt-get install -y apt-transport-https &

# Mount the game files and build.
WORKDIR /Nemesis
CMD date > res/BUILDTIME && \
    mkdir -p build && \
    cd build && \
    cmake .. -DOS=${OS} -DSTATIC_BUILD=${STATIC_BUILD} -DDEBUG=${DEBUG} ${CMAKE_EXTRA} && \
    cmake --build . -j${NUM_CORES} && \
    cd ..