FROM ubuntu:22.04

RUN apt-get update && \
    apt-get install -y build-essential cmake libjpeg-dev libboost-program-options-dev libboost-log-dev \
    pkg-config


WORKDIR /app
COPY src /app/src/

RUN mkdir build
WORKDIR /app/build
RUN cmake ../src && make
    
