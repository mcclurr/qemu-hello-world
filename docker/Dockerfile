FROM registry.access.redhat.com/ubi9/ubi:9.4

ENV LANG=C.UTF-8
ENV LC_ALL=C.UTF-8

RUN cat > /etc/yum.repos.d/rocky.repo <<'EOF'
[rocky-appstream]
name=Rocky Linux 9 AppStream
baseurl=https://download.rockylinux.org/pub/rocky/9/AppStream/x86_64/os/
enabled=1
gpgcheck=0

[rocky-crb]
name=Rocky Linux 9 CRB
baseurl=https://download.rockylinux.org/pub/rocky/9/CRB/x86_64/os/
enabled=1
gpgcheck=0
EOF

RUN dnf -y update && \
    dnf -y install \
        gcc \
        gcc-c++ \
        make \
        cmake \
        gdb \
        git \
        diffutils \
        file \
        which \
        tar \
        gzip \
        bzip2 \
        flex \
        bison \
        xz \
        unzip \
        wget \
        curl-minimal \
        python3 \
        python3-pip \
        glib2-devel \
        zlib-devel \
        ninja-build \
    && dnf clean all

RUN python3 -m pip install tomli

WORKDIR /opt

RUN wget https://download.qemu.org/qemu-11.0.2.tar.xz && \
    tar xf qemu-11.0.2.tar.xz && \
    cd qemu-11.0.2 && \
    ./configure && \
    make

CMD ["/bin/bash"]