# Use Alpine Linux base image
FROM alpine:latest AS prolog-base

# Install basic dependencies and tools
RUN apk update && apk upgrade && \
    apk add --no-cache \
        alpine-sdk \
        bash \
        musl-dev \
        build-base \
        g++ \
        make \
        ncurses-dev \
        ncurses-libs \
        swig \
        net-tools \
        netcat-openbsd \
        curl \
        gnupg

# Add the SWI-Prolog repository
RUN echo "@testing http://dl-cdn.alpinelinux.org/alpine/edge/testing" >> /etc/apk/repositories && \
    apk add --no-cache swi-prolog@testing

# Set the default stack limit via environment variable
ENV SWI_PROLOG_STACK_LIMIT=100M

# Set the working directory
WORKDIR /app
