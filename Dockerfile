FROM    ubuntu:latest
COPY    . /app
WORKDIR /app
RUN apt-get update \
    && apt-get install -y make \
    && apt-get install -y build-essential
