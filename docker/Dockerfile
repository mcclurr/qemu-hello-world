FROM registry.access.redhat.com/ubi9/ubi:9.4

ENV LANG=C.UTF-8
ENV LC_ALL=C.UTF-8

# ---------------------------------------------------------------------------
# Package repositories
# ---------------------------------------------------------------------------
RUN cat > /etc/yum.repos.d/almalinux.repo <<'EOF'
[almalinux-baseos]
name=AlmaLinux 9 BaseOS
baseurl=https://repo.almalinux.org/almalinux/9/BaseOS/x86_64/os/
enabled=1
gpgcheck=0

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
includepkgs=flex,bison,nasm
EOF

# ---------------------------------------------------------------------------
# QEMU build dependencies
# ---------------------------------------------------------------------------
RUN dnf -y install \
        gcc \
        gcc-c++ \
        make \
        git \
        diffutils \
        flex \
        bison \
        glib2-devel \
        ninja-build \
        bzip2 \
        python3 \
        python3-pip \
        xz \
    && dnf clean all \
    && rm -rf /var/cache/dnf

# ---------------------------------------------------------------------------
# Python tools
# ---------------------------------------------------------------------------
RUN python3 -m pip install --no-cache-dir tomli

# ---------------------------------------------------------------------------
# Build QEMU from local source
# ---------------------------------------------------------------------------
WORKDIR /opt/qemu

COPY libs/qemu/ ./

RUN ./configure \
    && make -j"$(nproc)" \
    && make install

# ---------------------------------------------------------------------------
# General development and OS-building tools
# ---------------------------------------------------------------------------
RUN dnf -y install \
        cmake \
        gdb \
        nasm \
        xorriso \
        grub2-tools-extra \
        grub2-pc-modules \
    && dnf clean all \
    && rm -rf /var/cache/dnf

WORKDIR /workspace

CMD ["/bin/bash"]