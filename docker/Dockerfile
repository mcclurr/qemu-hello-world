FROM registry.access.redhat.com/ubi9/ubi:9.4 AS builder

ENV LANG=C.UTF-8
ENV LC_ALL=C.UTF-8

# ---------------------------------------------------------------------------
# Build repositories
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

RUN python3 -m pip install --no-cache-dir tomli

# ---------------------------------------------------------------------------
# Build QEMU
# ---------------------------------------------------------------------------
WORKDIR /opt/qemu

COPY libs/qemu/ ./

RUN ./configure \
    && make -j"$(nproc)" \
    && make install \
    && strip /usr/local/bin/qemu-* || true \
    && rm -rf /opt/qemu


# =============================================================================
# Runtime image
# =============================================================================

FROM registry.access.redhat.com/ubi9/ubi:9.4

ENV LANG=C.UTF-8
ENV LC_ALL=C.UTF-8

# ---------------------------------------------------------------------------
# QEMU runtime files
# ---------------------------------------------------------------------------
COPY --from=builder /usr/local/bin/qemu-* /usr/local/bin/
COPY --from=builder /usr/local/share/qemu /usr/local/share/qemu

# ---------------------------------------------------------------------------
# OS-building tools
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

RUN dnf -y install \
        gdb \
        xorriso \
        grub2-tools-extra \
        grub2-pc-modules \
        nasm \
        python3 \
    && dnf clean all \
    && rm -rf /var/cache/dnf

WORKDIR /workspace

CMD ["/bin/bash"]