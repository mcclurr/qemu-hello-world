# =============================================================================
# QEMU builder
# =============================================================================

FROM registry.access.redhat.com/ubi9/ubi:9.4 AS builder

ENV LANG=C.UTF-8
ENV LC_ALL=C.UTF-8

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
        --target-list=arm-softmmu \
    && make -j"$(nproc)" \
    && make install \
    && strip /usr/local/bin/qemu-* || true \
    && rm -rf /opt/qemu


# =============================================================================
# Runtime image
# =============================================================================

FROM registry.access.redhat.com/ubi9/ubi:9.4

ARG ARM_TOOLCHAIN_VERSION=15.2.rel1

ENV LANG=C.UTF-8
ENV LC_ALL=C.UTF-8

ENV ARM_TOOLCHAIN_DIR=/opt/arm-none-eabi
ENV PATH="${ARM_TOOLCHAIN_DIR}/bin:${PATH}"

RUN dnf -y install \
        ca-certificates \
        gdb \
        gzip \
        make \
        python3 \
        tar \
        xz \
    && dnf clean all \
    && rm -rf /var/cache/dnf

# ---------------------------------------------------------------------------
# QEMU
# ---------------------------------------------------------------------------
COPY --from=builder /usr/local/bin/qemu-* /usr/local/bin/
COPY --from=builder /usr/local/share/qemu /usr/local/share/qemu

# ---------------------------------------------------------------------------
# Arm GNU bare-metal toolchain for STM32
# ---------------------------------------------------------------------------
RUN curl --fail --location --retry 3 \
        --output /tmp/arm-toolchain.tar.xz \
        "https://developer.arm.com/-/media/Files/downloads/gnu/${ARM_TOOLCHAIN_VERSION}/binrel/arm-gnu-toolchain-${ARM_TOOLCHAIN_VERSION}-x86_64-arm-none-eabi.tar.xz" \
    && mkdir -p "${ARM_TOOLCHAIN_DIR}" \
    && tar \
        --extract \
        --file=/tmp/arm-toolchain.tar.xz \
        --directory="${ARM_TOOLCHAIN_DIR}" \
        --strip-components=1 \
    && rm /tmp/arm-toolchain.tar.xz \
    && arm-none-eabi-gcc --version \
    && qemu-system-arm --version

WORKDIR /workspace

CMD ["/bin/bash"]