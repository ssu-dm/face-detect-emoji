# OpenCV 이미지 뷰어 예제

OpenCV를 CMake로 자동 다운로드하여 빌드하는 간단한 이미지 표시 예제입니다.

## 특징

- CMake `FetchContent`를 사용해 OpenCV를 자동으로 다운로드하고 빌드
- 최소한의 OpenCV 모듈만 빌드하여 빌드 시간 단축
- `muller.webp` 이미지 파일을 읽어서 윈도우에 표시

## 요구사항

- CMake 3.14 이상
- C++17 지원 컴파일러
- Git

## 빌드 및 실행

```bash
# 1. 빌드 디렉토리 생성 및 이동
mkdir build && cd build

# 2. CMake 설정 (OpenCV 자동 다운로드)
cmake ..

# 3. 빌드 (첫 빌드는 10-20분 소요)
cmake --build . --config Release -j8

./bin/face_detect
```

**참고**: 아무 키나 누르면 프로그램이 종료됩니다.

## 빌드되는 OpenCV 모듈

빌드 시간 단축을 위해 최소한의 모듈만 빌드합니다:
- `opencv_core` - 기본 데이터 구조
- `opencv_imgproc` - 이미지 처리
- `opencv_imgcodecs` - 이미지 읽기/쓰기 (WebP 지원)
- `opencv_highgui` - GUI 윈도우

## 프로젝트 구조

```
face-detect-emoji/
├── CMakeLists.txt    # OpenCV 자동 다운로드 설정
├── main.cpp          # 이미지 표시 코드
├── muller.webp       # 표시할 이미지
└── build/            # 빌드 디렉토리 (생성됨)
```

