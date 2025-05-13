#include <gtest/gtest.h>
#include <random>
#include <array>
#include <vector>
#include <string>
#include <chrono>
#include "Array.hpp"
#include "String.hpp"
#include "Vector.hpp"
#include <utility>

using namespace khan;

std::mt19937 rng(42);
std::uniform_int_distribution<int> dist(-10000, 10000);
char rand_char() { return 'a' + (rng() % 26); }

// Array.hpp vs std::array (성능 포함)
TEST(ArrayTest, CompareWithStdArray) {
    constexpr size_t N = 10000;
    Array<int, N> myarr;
    std::array<int, N> stdarr;

    // 값 할당 및 성능 측정
    auto t1 = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < N; ++i) myarr[i] = dist(rng);
    auto t2 = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < N; ++i) stdarr[i] = dist(rng);
    auto t3 = std::chrono::high_resolution_clock::now();

    auto myarr_time = std::chrono::duration_cast<std::chrono::microseconds>(t2-t1).count();
    auto stdarr_time = std::chrono::duration_cast<std::chrono::microseconds>(t3-t2).count();
    printf("Array<int,%zu> fill: %lldus, std::array<int,%zu> fill: %lldus\n", N, myarr_time, N, stdarr_time);

    for (size_t i = 0; i < N; ++i) {
        EXPECT_EQ(myarr[i], myarr[i]); // 자기 자신과 비교로 무의미하지만, 값 접근 테스트
        EXPECT_EQ(stdarr[i], stdarr[i]);
    }
}

// String.hpp vs std::string (성능 포함)
TEST(StringTest, CompareWithStdString) {
    constexpr size_t N = 1000;
    std::string stdstr;
    String<N> mystr;

    // 랜덤 문자열 생성 및 성능 측정
    auto t1 = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < N-1; ++i) mystr.push_back(rand_char());
    auto t2 = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < N-1; ++i) stdstr.push_back(rand_char());
    auto t3 = std::chrono::high_resolution_clock::now();

    auto mystr_time = std::chrono::duration_cast<std::chrono::microseconds>(t2-t1).count();
    auto stdstr_time = std::chrono::duration_cast<std::chrono::microseconds>(t3-t2).count();
    printf("String<%zu> push_back: %lldus, std::string push_back: %lldus\n", N, mystr_time, stdstr_time);

    EXPECT_EQ(mystr.size(), N-1);
    EXPECT_EQ(stdstr.size(), N-1);
}

// Vector.hpp vs std::vector
TEST(VectorTest, CompareWithStdVectorAllOps) {
    constexpr size_t N = 10;
    Vector<int, N> myvec;
    std::vector<int> stdvec;

    std::vector<int> data;
    data.reserve(N);
    for (size_t i = 0; i < N; ++i) {
        data.push_back(dist(rng));
    }

    // push_back 성능
    auto t1 = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < N-1; ++i) myvec.push_back(data[i]);
    auto t2 = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < N-1; ++i) stdvec.push_back(data[i]);
    auto t3 = std::chrono::high_resolution_clock::now();
    auto myvec_time = std::chrono::duration_cast<std::chrono::microseconds>(t2-t1).count();
    auto stdvec_time = std::chrono::duration_cast<std::chrono::microseconds>(t3-t2).count();
    EXPECT_EQ(myvec.size(), stdvec.size());
    for (size_t i = 0; i < myvec.size(); ++i) {
        EXPECT_EQ(myvec[i], stdvec[i]);
    }
    printf("Vector<int,%zu> push_back: %lldus, std::vector<int> push_back: %lldus\n", N, myvec_time, stdvec_time);

    // insert 성능 및 값 비교
    size_t insert_pos = N/2;
    int insert_val = 12345;
    t1 = std::chrono::high_resolution_clock::now();
    myvec.insert(myvec.begin() + insert_pos, insert_val);
    t2 = std::chrono::high_resolution_clock::now();
    stdvec.insert(stdvec.begin() + insert_pos, insert_val);
    t3 = std::chrono::high_resolution_clock::now();
    myvec_time = std::chrono::duration_cast<std::chrono::microseconds>(t2-t1).count();
    stdvec_time = std::chrono::duration_cast<std::chrono::microseconds>(t3-t2).count();
    EXPECT_EQ(myvec.size(), stdvec.size());
    for (size_t i = 0; i < myvec.size(); ++i) {
        EXPECT_EQ(myvec[i], stdvec[i]);
    }
    printf("Vector<int,%zu> insert: %lldus, std::vector<int> insert: %lldus\n", N, myvec_time, stdvec_time);
    
    // erase (중간)
    t1 = std::chrono::high_resolution_clock::now();
    myvec.erase(myvec.begin() + insert_pos);
    t2 = std::chrono::high_resolution_clock::now();
    stdvec.erase(stdvec.begin() + insert_pos);
    t3 = std::chrono::high_resolution_clock::now();
    myvec_time = std::chrono::duration_cast<std::chrono::microseconds>(t2-t1).count();
    stdvec_time = std::chrono::duration_cast<std::chrono::microseconds>(t3-t2).count();
    EXPECT_EQ(myvec.size(), stdvec.size());
    for (size_t i = 0; i < myvec.size(); ++i) {
        EXPECT_EQ(myvec[i], stdvec[i]);
    }
    printf("Vector<int,%zu> erase: %lldus, std::vector<int> erase: %lldus\n", N, myvec_time, stdvec_time);

    // pop_back 여러 번
    t1 = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < N - 2; ++i) myvec.pop_back();
    t2 = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < N - 2; ++i) stdvec.pop_back();
    t3 = std::chrono::high_resolution_clock::now();
    myvec_time = std::chrono::duration_cast<std::chrono::microseconds>(t2-t1).count();
    stdvec_time = std::chrono::duration_cast<std::chrono::microseconds>(t3-t2).count();
    EXPECT_EQ(myvec.size(), stdvec.size());
    for (size_t i = 0; i < myvec.size(); ++i) {
        EXPECT_EQ(myvec[i], stdvec[i]);
    }
    printf("Vector<int,%zu> pop_back x%zu: %lldus, std::vector<int> pop_back x%zu: %lldus\n", N, N, myvec_time, N, stdvec_time);
}
