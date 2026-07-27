# Quick Start

## Prerequisites

- Git
- Docker Desktop (or Docker Engine with Docker Compose)

> **Windows users:** QEMU uses symbolic links. Before cloning the repository, enable Git symlink support:

```bash
git config --global core.symlinks true
```

## Clone the Repository

Clone the repository and all submodules:

```bash
git clone --recursive git@github.com:mcclurr/qemu-hello-world.git
cd qemu-hello-world
```

If you already cloned without submodules, run:

```bash
git submodule update --init --recursive
```

## Build the Docker Image

Build the development environment:

```bash
docker compose build
```

## Start the Container

Launch the container:

```bash
docker compose up -d
```