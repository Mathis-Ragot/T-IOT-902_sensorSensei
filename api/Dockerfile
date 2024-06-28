FROM rust:bookworm AS builder
WORKDIR /usr/src/api
COPY ./api .
RUN cargo install --path .

FROM debian:bookworm-slim
RUN apt-get update \ 
    && apt-get install -y openssl ca-certificates \ 
    && rm -rf /var/lib/apt/lists/*
COPY --from=builder /usr/local/cargo/bin/api /usr/local/bin/api
COPY .env .env
CMD ["api"]