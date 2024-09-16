FROM alpine:3.20.3 AS base

FROM base AS build

RUN apk add --no-cache \
    build-base \
    cmake \
    git

WORKDIR /usr/src/r-type

COPY . .

RUN cmake -B build -S .
RUN cmake --build build

FROM base AS runtime

COPY --from=build /usr/src/r-type/build/r-type_server /usr/local/bin/r-type_server

CMD ["/usr/local/bin/r-type"]