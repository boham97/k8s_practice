# Step 1: Base image 선택 (C 컴파일러가 포함된 이미지)
FROM alpine:latest

# Step 2: GCC 및 필수 빌드 도구 설치
RUN apk add --no-cache gcc musl-dev

# Step 3: 작업 디렉토리 설정
WORKDIR /app

# Step 4: 소스코드 복사
COPY server.c .

# Step 5: 소스코드 빌드
RUN gcc -o server server.c

# Step 6: 실행할 프로그램 지정
CMD ["./server"]
