FROM registry.access.redhat.com/ubi9/ubi:9.4

ENV LANG=C.UTF-8
ENV LC_ALL=C.UTF-8

RUN dnf -y update && \
    dnf -y install \
        gcc \
        gcc-c++ \
        make \
        cmake \
        gdb \
        git \
        vim \
        nano \
        findutils \
        diffutils \
        file \
        which \
        tar \
        gzip \
        xz \
        unzip \
        wget \
        curl-minimal \
        python3 \
    && dnf clean all

WORKDIR /workspace

CMD ["/bin/bash"]