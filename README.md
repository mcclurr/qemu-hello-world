# Quick Start

## Prerequisites

- Git
- Docker Desktop (or Docker Engine with Docker Compose)

> **Windows users:** QEMU uses symbolic links. Before cloning the repository, enable Git symlink support:

```bash
git config --global core.symlinks true
```

## Clone the Repository

Clone the repository:

```bash
git clone git@github.com:mcclurr/qemu-hello-world.git
cd qemu-hello-world
```

Initialize the project's submodules:

```bash
git submodule update --init
```

> **Note:** This project intentionally initializes only its own submodules. It does **not** recursively initialize nested submodules contained within them.

## Build the Docker Image

Build the development environment:

```bash
docker compose build
```

## Start the Container

Launch the container in the background:

```bash
docker compose up -d
```

To stop the container:

```bash
docker compose down
```