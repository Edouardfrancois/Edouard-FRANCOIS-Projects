FROM ubuntu:latest
FROM gcc:latest

RUN apt-get update && apt-get -y install cmake protobuf-compiler
RUN apt-get -y install libgl1-mesa-dev udev libx11-dev xorg-dev freeglut3-dev libudev-dev
RUN apt-get -y install libopenal-dev
RUN apt-get -y install libvorbis-dev
RUN apt-get -y install libflac-dev
RUN apt-get -y install libsfml-dev

WORKDIR '/home/mayeul/Bureau/B-CPP-500-PAR-5-1-rtype-pierre.tran'


RUN groupadd -g 1000 mayeul
RUN useradd -u 1000 -g 1000 mayeul

USER mayeul

CMD cd build && cmake .. && make -j8
