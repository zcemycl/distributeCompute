FROM nvidia/cuda:11.4.1-cudnn8-devel-ubuntu18.04 
ARG DEBIAN_FRONTEND=noninteractive
RUN apt-get update -y
# RUN apt-get install gcc-10 g++-10 -y
RUN apt-get install build-essential cmake libgtest-dev  -y
RUN apt-get install libpthread-stubs0-dev libboost-all-dev -y
# ENV CC=/usr/bin/gcc-10
# ENV CXX=/usr/bin/g++-10
WORKDIR /usr/src/googletest
RUN mkdir -p build 
WORKDIR /usr/src/googletest/build
RUN cmake .. && make && make install
COPY . /tmp
WORKDIR /tmp
RUN mkdir -p build 
WORKDIR /tmp/build
RUN cmake .. && make
CMD nvidia-smi ; ./runTests
