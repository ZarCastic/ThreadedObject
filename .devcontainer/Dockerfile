FROM ubuntu:bionic

RUN apt update 
RUN apt install -y \
    build-essential \
    cmake \
    git \
    clang-9 \
    wget \
    clang-format-9 \
    gdb \
    zsh \
    python3-dev \
    python3-pip \
    python3-setuptools \ 
    sudo \
    clang-tidy-9 
RUN pip3 install thefuck

RUN wget https://github.com/google/googletest/archive/release-1.10.0.tar.gz ; \
    tar xf release-1.10.0.tar.gz ; rm release-1.10.0.tar.gz; \
    cd googletest-release-1.10.0 ;\
    cmake -DBUILD_SHARED_LIBS=ON .  ;\
    make; make install; \
    cd / ; \
    rm -rf googletest-release-1.10.0

RUN useradd -ms /bin/zsh vscode
USER vscode 
WORKDIR /home/vscode 
