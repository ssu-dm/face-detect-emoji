cmake_minimum_required(VERSION 3.14)
project(FaceDetectEmoji)

# C++ 표준 설정
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# FetchContent 모듈 포함 (OpenCV 자동 다운로드를 위해)
include(FetchContent)

# OpenCV 다운로드 및 빌드
message(STATUS "Downloading OpenCV...")
FetchContent_Declare(
    opencv
    GIT_REPOSITORY https://github.com/opencv/opencv.git
    GIT_TAG 4.10.0  # 최신 안정 버전
    GIT_SHALLOW TRUE
    GIT_PROGRESS TRUE
)

# OpenCV 빌드 옵션 설정 (빌드 시간 단축)
set(BUILD_LIST "core,imgproc,imgcodecs,highgui" CACHE STRING "" FORCE)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(BUILD_PERF_TESTS OFF CACHE BOOL "" FORCE)
set(BUILD_opencv_apps OFF CACHE BOOL "" FORCE)
set(BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(WITH_CUDA OFF CACHE BOOL "" FORCE)
set(WITH_FFMPEG OFF CACHE BOOL "" FORCE)
set(WITH_GSTREAMER OFF CACHE BOOL "" FORCE)
set(WITH_OBSENSOR OFF CACHE BOOL "" FORCE)
set(BUILD_opencv_python2 OFF CACHE BOOL "" FORCE)
set(BUILD_opencv_python3 OFF CACHE BOOL "" FORCE)
set(BUILD_opencv_videoio OFF CACHE BOOL "" FORCE)

# OpenCV를 사용 가능하게 만들기
FetchContent_MakeAvailable(opencv)

# 실행 파일 생성
add_executable(face_detect main.cpp)

# OpenCV include 디렉토리 추가
target_include_directories(face_detect PRIVATE 
    ${opencv_SOURCE_DIR}/include
    ${opencv_SOURCE_DIR}/modules/core/include
    ${opencv_SOURCE_DIR}/modules/imgproc/include
    ${opencv_SOURCE_DIR}/modules/imgcodecs/include
    ${opencv_SOURCE_DIR}/modules/highgui/include
)

# OpenCV 라이브러리 링크
target_link_libraries(face_detect PRIVATE 
    opencv_core
    opencv_imgproc
    opencv_imgcodecs
    opencv_highgui
)

# 컴파일 경고 활성화
if(MSVC)
    target_compile_options(face_detect PRIVATE /W4)
else()
    target_compile_options(face_detect PRIVATE -Wall -Wextra -Wpedantic)
endif()

# 빌드 타입이 지정되지 않은 경우 Release로 설정
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

