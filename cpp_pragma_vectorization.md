# cpp 向量化

# 利用 simd 预处理指令实现向量化
```c++
#pragma simd
```
 SIMD (Single Instruction, Multiple Data) 单指令多数据流

 该向量化操作使用`#pragma simd` 预处理指令强制将循环向量化。

 考虑如下的例子，下面的c++函数`add_floats()`使用了许多未知的指针。为了阻止自动的向量化，你可以用过一个预处理指令`#pragma ivdep`提示编译器这里可以向量化，但是具体是否进行向量化优化由编译器决定，相当于通过该预处理指令给出一个是否自动向量化的断言。或者使用`#pragma simd`强制将这个循环向量化

 ```c++
 void add_floats(float* a, float* b, float* c, float* d, float* e, int n)
 {
     int i；
     #pargma simd
     for(i = 0; i < n; ++i)
     {
         a[i] = b[i] + c[i] + d[i] + e[i];
     }
 }
 ```

 SIMD 预处理指令与自动向量化提示的不同在于， 使用`#pragma simd`时，当编译器不能将一个循环向量化时会生成一个警告。使用自动向量化提示，编译器掌握着实际的向量化裁决权，即使使用了`#pragma vector always`提示

 SIMD编译预处理指令有一个可选的子句来指导编译器如何向量化。正确的使用这些子句可以给编译器足够的信息去生成正确的向量化代码。具体子句指令并没有找到
