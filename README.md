# 개요
임베디드 시스템에 최적화된 Container를 만드는 것이 목적인 프로젝트입니다. 
일반 STL과 달리 스택기반으로 메모리를 형성하고 일정한 실행 시간을 가지도록 의도하였습니다.

## 컨테이너 종류
| 컨테이너 타입        | 설명                                    | 참고(기반 컨테이너)               |
| -------------- | ------------------------------------- | ------------------------- |
| [`Array`](https://github.com/Han-Sang-min/KhanSTL/blob/main/include/Array.hpp)        | 고정된 크기의 배열 컨테이너로 빠른 접근 성능 제공          | `std::array`              |
| [`Vector`](https://github.com/Han-Sang-min/KhanSTL/blob/main/include/Vector.hpp)      | 크기가 가변적이지만 스택 기반 메모리 관리로 성능 최적화       | `std::vector`             |
| [`String`](https://github.com/Han-Sang-min/KhanSTL/blob/main/include/String.hpp)       | 효율적인 문자열 처리 및 스택 기반 메모리 관리            | `std::string`             |
| [`Function`](https://github.com/Han-Sang-min/KhanSTL/blob/main/include/Function.hpp)     | 함수 객체를 효율적으로 래핑하며, 실행 시간을 예측 가능하게 최적화 | `std::function`           |
| [`AVLTree`](https://github.com/Han-Sang-min/KhanSTL/blob/main/include/BST/AVLTree.hpp)      | 균형 이진 트리로 구현된 고성능 검색/삽입/삭제 지원         | AVL Balanced Tree         |
| [`Meta Util1`](https://github.com/Han-Sang-min/KhanSTL/blob/main/include/meta/meta.hpp) <br> [`Meta Util2`](https://github.com/Han-Sang-min/KhanSTL/blob/main/include/meta/utility.hpp) | 메타프로그래밍을 통해 컴파일 시간에 타입 처리를 지원         | Template Meta-Programming |

## 사용 방법
헤더 파일만으로 구성된(single-header) 구조로, 별도의 빌드 과정 없이 필요한 헤더 파일만 복사하여 즉시 사용할 수 있습니다.
- 기본 사용: /include 폴더의 헤더 파일을 복사하여 프로젝트에 포함합니다.
- 테스트 및 예제 실행:
    - CMake를 사용하여 테스트를 실행할 수 있습니다.
    - Windows의 경우 제공된 스크립트 build_and_run.ps1을 실행하여 간편하게 테스트 가능합니다.
    - 테스트 및 예제 코드는 /src 및 /test 디렉터리를 참조하세요.

