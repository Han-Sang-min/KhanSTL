# KhanSTL

KhanSTL는 임베디드 시스템 환경에서 사용할 수 있도록 설계된 경량 STL 대체 라이브러리입니다. 동적 메모리 할당을 지양하고, 정적 배열 기반의 자료 구조를 제공하여 제한된 자원 환경에서도 효율적인 메모리 사용과 안정적인 성능을 보장합니다.

## 주요 특징

- 동적 메모리 할당 없이 정적 배열 기반의 자료 구조(Vector, Array, Ring Buffer 등) 구현
- 간결한 인터페이스를 통한 메모리 사용량 및 코드 크기 최소화
- CMake 기반의 빌드 시스템과 테스트 환경 제공
- 임베디드 시스템에서의 안정적인 성능 보장

## 설치 및 사용 방법

1. 저장소를 클론합니다.
   ```bash
   git clone https://github.com/Han-Sang-min/KhanSTL.git
빌드 디렉토리를 생성하고 이동합니다.

bash
복사
편집
mkdir build && cd build
CMake를 사용하여 빌드합니다.

bash
복사
편집
cmake ..
make
테스트를 실행합니다.

bash
복사
편집
./test/KhanSTL_tests
