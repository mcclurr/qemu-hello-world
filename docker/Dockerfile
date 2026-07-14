FROM registry.access.redhat.com/ubi9/ubi:9.4

ENV LANG=C.UTF-8
ENV LC_ALL=C.UTF-8

RUN cat > /etc/yum.repos.d/almalinux.repo <<'EOF'
[almalinux-appstream]
name=AlmaLinux 9 AppStream
baseurl=https://repo.almalinux.org/almalinux/9/AppStream/x86_64/os/
enabled=1
gpgcheck=0
includepkgs=flex,bison,xorriso,libisoburn,libisofs,libburn

[almalinux-crb]
name=AlmaLinux 9 CRB
baseurl=https://repo.almalinux.org/almalinux/9/CRB/x86_64/os/
enabled=1
gpgcheck=0
includepkgs=flex,bison, nasm
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
        bzip2 \
        flex \
        bison \
        nasm \
        xz \
        wget \
        python3 \
        python3-pip \
        xorriso \
        glib2-devel \
        ninja-build \
    && dnf clean all

RUN python3 -m pip install tomli

WORKDIR /opt

RUN wget https://download.qemu.org/qemu-11.0.2.tar.xz && \
    tar xf qemu-11.0.2.tar.xz && \
    cd qemu-11.0.2 && \
    ./configure && \
    make && \
    make install

CMD ["/bin/bash"]