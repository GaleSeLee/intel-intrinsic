#include<iostream>
#include<chrono>
#include<cstring>
#include<cstdlib>
#include<immintrin.h>
#define N 1<<25

void vecadd_avx(float *a, float *b); 
void vecadd(float *a, float *b);
void vecinit(float *a, float *b);
void checkcorrect(float *c_1, float *c_2);

std::chrono::system_clock::time_point get_time();
void get_time_gap(std::chrono::system_clock::time_point start);

int main(int argc, char **argv) {
    float *a = (float *)_mm_malloc((N) * sizeof(float),4);
    float *b = (float *)_mm_malloc((N) * sizeof(float),4);
    vecinit(a, b);
    vecadd(a, b);
    vecadd_avx(a, b);
    return 0;
}

std::chrono::system_clock::time_point get_time() {
    return std::chrono::system_clock::now();
}

void get_time_gap(std::chrono::system_clock::time_point start) {
    auto end = get_time();
    auto gap = std::chrono::duration_cast<std::chrono::microseconds>(end-start);
    std::cout<<"Times : "<<double(gap.count()) / 1000000 <<std::endl;
}

void vecinit(float *a, float *b) {
    for(int ii = 0; ii < N; ii++) {
        a[ii] = std::rand()%10000;
        b[ii] = std::rand()%10000;
    }
}

void vecadd(float *a, float *b) {
    float *c = (float *)malloc((N) * sizeof(float));
    std::chrono::system_clock::time_point start = get_time();
    for(int ii = 0; ii < N; ii++) {
        c[ii] = a[ii] + b[ii];
    }
    get_time_gap(start);
    std::free(c);
}

void vecadd_avx(float *a, float *b) {
    float *c = (float *)_mm_malloc((N) * sizeof(float),4);
    std::chrono::system_clock::time_point start = get_time();
    // for(int ii = 0; ii < N; ii+=8) {
    //     __m256 a_256 = _mm256_load_ps(a+ii);
    //     __m256 b_256 = _mm256_load_ps(b+ii);
    //     __m256 c_256 = _mm256_add_ps(a_256, b_256);
    //     _mm256_store_ps(c+ii, c_256);
    // }
        for(int ii = 0; ii < N; ii+=16) {
        __m512 a_512 = *(__m512 *)(a);
        __m512 b_512 = _mm512_load_ps(b+ii);
        __m512 c_512 = _mm512_add_ps(a_512, b_512);
        _mm512_store_ps(c+ii, c_512);
    }
    get_time_gap(start);
}