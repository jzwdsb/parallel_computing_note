#include <mkl.h>

#ifdef MKL_ILP64
#define MKL_INT long long 
#else 
#define MKL_INT int
#endif


extern MKL_INT pardiso
		(void* pt , MKL_INT* maxfct , MKL_INT* mnum, MKL_INT*mtype , MKL_INT* phase, MKL_INT* n,
		 double *a, MKL_INT*ia, MKL_INT*ja, MKL_INT*perm, MKL_INT*nrhs, MKL_INT*iparm,
		 MKL_INT*msglvl, double*b, double *x, MKL_INT*error);

/* pt  包含64void*的数组，内部数据结构的句柄，必须在第一次调用pardiso之前全部初始化为0
 *
 *
 * maxfct  相同稀疏矩阵结构的最大数量，必须同时保留在内存中，大部分情况下这个值设置为1
 *
 * mnum  指明实际用来求解的矩阵，这个标量可以定义用来insula分解的矩阵，1  <=  mnum <=maxfct
 * 		大部分情况下这个值为1
 * mtype  定义矩阵的类型，这个值影响了转轴方法
 * 				1 			实数结构对称矩阵
 * 				2			实数对称正定矩阵
 * 				-2 			实数对称阵非正定阵
 *				11 			实数非对阵阵
 *
 * phase  控制求解器的行为，通常情况下是2位或3位的整数
 * 		  第一位指明求解的开始阶段，第二位指明求解的结束阶段
 * 		  		1			填充消元分析和符号分解
 * 		  		2			因数分解
 * 		  		3			前向和后向回代，带有可选的反复求解
 *
 * 		 		阶段			求解步骤
 *
 * 		 		11				分析
 * 		 		12				分析，因数分解
 * 		 		13				分析，因数分解，求解，反复求解
 *				22				因数分解
 *				23				因数分解，求解，反复求解
 *				33				求解
 *				331				和 33 一样，但是只有前向回代
 *				332				和 33 一样, 但是只有对角回代
 *				333				和 33 一样，但是只有反向回代
 *
 * n		 稀疏线性系统中的 A * X = B 类型的等式数量
 * a   		 稀疏系数矩阵 A 中的非 0 元素
 * ia  	     csr3格式中的行偏移量，ia[i]对应与第i行第一列的起始位置
 * ja  		 csr3格式中的列号，ja[i]对应于第i个元素的列号
 * perm		 大小为n的数组，取决于iparm[4]和ipram[30]，保留了置换n维向量或求解局部所用的特殊元素
 * 			 该数组默认是以 1 为基的
 * nrhs		 右侧需要求解的元素数量
 * iparm	 64字节长度的向量，这个数组是用来向pardiso传递多种参数并且在求解完成后返回有用的信息
 * msglvl	 信息传递等级，如果msglvl == 0, pardiso输出信息;如果 msglvl == 1 求解器会向屏幕输出
 * b 		 长度为 n * nrhs 字节的数组，包含右侧偏置向量或矩阵，在内存中的分布必须相邻
 *
 * 输出参数
 *
 * pt		内部数据结构的句柄
 * perm		在输入参数中参考描述
 * iparm	在输出中，一些iparm值报告了关于因数中非零元素的信息
 * b		在输出中，如果 iparm[1]== 1 这个数组将会被替换
 * x		长度为 n*nrhs .如果 iparm == 0 他就包含计算结果或矩阵，该向量在内存中紧密排布
 * error	错误码
 * */

