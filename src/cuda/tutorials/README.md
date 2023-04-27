## How to start?
```
docker build -t cuda_gtest:latest .
docker run cuda_gtest
docker run --gpus all cuda_gtest # use gpu in your host
```