Intel intrinsic guide: https://www.intel.com/content/www/us/en/docs/intrinsics-guide/index.html

#### 数据类型

\_\_mxxxy

- 其数据类型以\_\_m开头
- xxx表示vector的长度(bit)，SSE支持128位，AVX支持256位，AVX-512支持512位
- y可有可无，没有的话表示float数据类型，d代表double，i代表int，

#### 函数命名

\_\_mmxxx_operation_yy

- 其函数命名以\_\_mm开头
- xxx代表vector的向量长度，常见为64，128，256，512
- operation代表要进行的算术操作，例如add, sub, addsub, 建议看guide的description和operation
- 最后yy为数据类型，ps为single-float, pd为double-float, epix为x位有符号整数, epux为x位无符号整数，si表示未指定

#### 头文件

intrin.h   All Architectures
mmintrin.h   MMX
xmmintrin.h   SSE
emmintrin.h   SSE2
pmmintrin.h   SSE3
smmintrin.h   SSE4.1
nmmintrin.h   SSE4.2
immintrin.h   AVX
zmmintrin.h   AVX512

使用avx gcc编译加-mavx

动态分配使用\_mm\_malloc(size, align_size)

0.4与0.3的区别

reference:https://zzqcn.github.io/perf/simd_demo.html