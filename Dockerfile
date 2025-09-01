FROM debian:latest AS builder

RUN apt-get update && apt-get install -y \
    build-essential \
    nasm \
    xorriso \
    mtools \
    gdisk \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /splenkOS

COPY . .

RUN make
RUN ./iso.sh

RUN mkdir -p containerbuild
RUN cp image.iso containerbuild/
RUN cp -r bin containerbuild/
RUN cp -r obj containerbuild/

FROM scratch

COPY --from=builder /splenkOS/containerbuild .