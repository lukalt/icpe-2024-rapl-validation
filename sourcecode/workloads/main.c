#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <unistd.h>
#include <mkl.h>
#include <mkl_cblas.h>
#include <math.h>
#define WORKLOAD_BUSY_WAIT 0
#define WORKLOAD_IDLE 1
#define WORKLOAD_COMPUTE 2
#define WORKLOAD_ADDPD 3
#define WORKLOAD_MATMUL 4
#define WORKLOAD_MEMORY_READ 5
#define WORKLOAD_MULPD 6
#define WORKLOAD_SQRT 7
#define WORKLOAD_MEMORY_WRITE 8
#define WORKLOAD_MEMORY_COPY 9

#ifndef WORKLOAD
#define WORKLOAD WORKLOAD_BUSY_WAIT
#endif

#if WORKLOAD == WORKLOAD_MULPD
unsigned long mulpd_kernel(double *buffer, unsigned long repeat)
{
    unsigned long long passes,addr;
    unsigned long long a,b,c,d;
    unsigned long ret=0;

    passes=repeat/32; // 32 128-Bit accesses in inner loop

    addr=(unsigned long long) buffer;

    if (!passes) return ret;
    /*
     * Input:  RAX: addr (pointer to the buffer)
     *         RBX: passes (number of iterations)
     *         RCX: length (total number of accesses)
     */
    __asm__ __volatile__(
        "mov %%rax,%%r9;"   // addr
        "mov %%rbx,%%r10;"  // passes

        //initialize registers
        "movaps 0(%%r9), %%xmm0;"
        "movaps 16(%%r9), %%xmm1;"
        "movaps 32(%%r9), %%xmm2;"
        "movaps 48(%%r9), %%xmm3;"
        "movaps 64(%%r9), %%xmm4;"
        "movaps 80(%%r9), %%xmm5;"
        "movaps 96(%%r9), %%xmm6;"
        "movaps 112(%%r9), %%xmm7;"
        "movapd 0(%%r9), %%xmm8;"
        "movapd 16(%%r9), %%xmm9;"
        "movapd 32(%%r9), %%xmm10;"
        "movapd 48(%%r9), %%xmm11;"
        "movapd 64(%%r9), %%xmm12;"
        "movapd 80(%%r9), %%xmm13;"
        "movapd 96(%%r9), %%xmm14;"
        "movapd 112(%%r9), %%xmm15;"

        ".align 64;"
        "_work_loop_mul_pd%=:"
        "mulpd %%xmm8, %%xmm0;"
        "mulpd %%xmm9, %%xmm1;"
        "mulpd %%xmm10, %%xmm2;"
        "mulpd %%xmm11, %%xmm3;"
        "mulpd %%xmm12, %%xmm4;"
        "mulpd %%xmm13, %%xmm5;"
        "mulpd %%xmm14, %%xmm6;"
        "mulpd %%xmm15, %%xmm7;"

        "mulpd %%xmm8, %%xmm0;"
        "mulpd %%xmm9, %%xmm1;"
        "mulpd %%xmm10, %%xmm2;"
        "mulpd %%xmm11, %%xmm3;"
        "mulpd %%xmm12, %%xmm4;"
        "mulpd %%xmm13, %%xmm5;"
        "mulpd %%xmm14, %%xmm6;"
        "mulpd %%xmm15, %%xmm7;"

        "mulpd %%xmm8, %%xmm0;"
        "mulpd %%xmm9, %%xmm1;"
        "mulpd %%xmm10, %%xmm2;"
        "mulpd %%xmm11, %%xmm3;"
        "mulpd %%xmm12, %%xmm4;"
        "mulpd %%xmm13, %%xmm5;"
        "mulpd %%xmm14, %%xmm6;"
        "mulpd %%xmm15, %%xmm7;"

        "mulpd %%xmm8, %%xmm0;"
        "mulpd %%xmm9, %%xmm1;"
        "mulpd %%xmm10, %%xmm2;"
        "mulpd %%xmm11, %%xmm3;"
        "mulpd %%xmm12, %%xmm4;"
        "mulpd %%xmm13, %%xmm5;"
        "mulpd %%xmm14, %%xmm6;"
        "mulpd %%xmm15, %%xmm7;"

        "sub $1,%%r10;"
        "jnz _work_loop_mul_pd%=;"

        : "=a" (a), "=b" (b), "=c" (c), "=d" (d)
        : "a"(addr), "b" (passes)
        : "%r9", "%r10", "xmm0", "xmm1", "xmm2", "xmm3", "xmm4", "xmm5", "xmm6", "xmm7", "xmm8", "xmm9", "xmm10", "xmm11", "xmm12", "xmm13", "xmm14", "xmm15"

    );
    ret=passes;

    return ret;
}
#endif
#if WORKLOAD == WORKLOAD_ADDPD
unsigned long addpd_kernel(double *buffer, unsigned long repeat)
{
    unsigned long long passes,addr;
    unsigned long long a,b,c,d;
    unsigned long ret=0;

    passes=repeat/32; // 32 128-Bit accesses in inner loop

    addr=(unsigned long long) buffer;

    if (!passes) return ret;
    /*
     * Input:  RAX: addr (pointer to the buffer)
     *         RBX: passes (number of iterations)
     *         RCX: length (total number of accesses)
     */
    __asm__ __volatile__(
            "mov %%rax,%%r9;"   // addr
            "mov %%rbx,%%r10;"  // passes

            //initialize registers
            "movaps 0(%%r9), %%xmm0;"
            "movaps 16(%%r9), %%xmm1;"
            "movaps 32(%%r9), %%xmm2;"
            "movaps 48(%%r9), %%xmm3;"
            "movaps 64(%%r9), %%xmm4;"
            "movaps 80(%%r9), %%xmm5;"
            "movaps 96(%%r9), %%xmm6;"
            "movaps 112(%%r9), %%xmm7;"
            "movapd 0(%%r9), %%xmm8;"
            "movapd 16(%%r9), %%xmm9;"
            "movapd 32(%%r9), %%xmm10;"
            "movapd 48(%%r9), %%xmm11;"
            "movapd 64(%%r9), %%xmm12;"
            "movapd 80(%%r9), %%xmm13;"
            "movapd 96(%%r9), %%xmm14;"
            "movapd 112(%%r9), %%xmm15;"

            ".align 64;"
            "_work_loop_add_pd%=:"
            "addpd %%xmm8, %%xmm0;"
            "addpd %%xmm9, %%xmm1;"
            "addpd %%xmm10, %%xmm2;"
            "addpd %%xmm11, %%xmm3;"
            "addpd %%xmm12, %%xmm4;"
            "addpd %%xmm13, %%xmm5;"
            "addpd %%xmm14, %%xmm6;"
            "addpd %%xmm15, %%xmm7;"

            "addpd %%xmm8, %%xmm0;"
            "addpd %%xmm9, %%xmm1;"
            "addpd %%xmm10, %%xmm2;"
            "addpd %%xmm11, %%xmm3;"
            "addpd %%xmm12, %%xmm4;"
            "addpd %%xmm13, %%xmm5;"
            "addpd %%xmm14, %%xmm6;"
            "addpd %%xmm15, %%xmm7;"

            "addpd %%xmm8, %%xmm0;"
            "addpd %%xmm9, %%xmm1;"
            "addpd %%xmm10, %%xmm2;"
            "addpd %%xmm11, %%xmm3;"
            "addpd %%xmm12, %%xmm4;"
            "addpd %%xmm13, %%xmm5;"
            "addpd %%xmm14, %%xmm6;"
            "addpd %%xmm15, %%xmm7;"

            "addpd %%xmm8, %%xmm0;"
            "addpd %%xmm9, %%xmm1;"
            "addpd %%xmm10, %%xmm2;"
            "addpd %%xmm11, %%xmm3;"
            "addpd %%xmm12, %%xmm4;"
            "addpd %%xmm13, %%xmm5;"
            "addpd %%xmm14, %%xmm6;"
            "addpd %%xmm15, %%xmm7;"

            "sub $1,%%r10;"
            "jnz _work_loop_add_pd%=;"

            : "=a" (a), "=b" (b), "=c" (c), "=d" (d)
            : "a"(addr), "b" (passes)
            : "%r9", "%r10", "xmm0", "xmm1", "xmm2", "xmm3", "xmm4", "xmm5", "xmm6", "xmm7", "xmm8", "xmm9", "xmm10", "xmm11", "xmm12", "xmm13", "xmm14", "xmm15"

            );
    ret=passes;

    return ret;
}
#endif
#if WORKLOAD == WORKLOAD_SQRT
unsigned long sqrtsd_kernel(double *buffer, unsigned long elems, unsigned long repeat)
{
    unsigned long long passes,length,addr;
    unsigned long long a,b,c,d;
    unsigned long ret=0;
    #ifdef REGONLY
    assert(elems >= 256/sizeof(*buffer));
    #endif

    passes=elems/64; // 32 128-Bit accesses in inner loop
    length=passes*32*repeat;
    addr=(unsigned long long) buffer;

    if (!passes) return ret;
    /*
     * Input:  RAX: addr (pointer to the buffer)
     *         RBX: passes (number of iterations)
     *         RCX: length (total number of accesses)
     */
    __asm__ __volatile__(
        "mfence;"
        "mov %%rax,%%r9;"   // addr
        "mov %%rbx,%%r10;"  // passes
        "mov %%rcx,%%r15;"  // length
        "mov %%r9,%%r14;"   // store addr
        "mov %%r10,%%r8;"   // store passes
        "mov %%r15,%%r13;"  // store length

        //initialize registers
        "movapd 0(%%r9), %%xmm0;"
        #ifdef REGONLY
        "movapd 0(%%r9), %%xmm8;"
        "movapd 16(%%r9), %%xmm9;"
        "movapd 32(%%r9), %%xmm10;"
        "movapd 48(%%r9), %%xmm11;"
        "movapd 64(%%r9), %%xmm12;"
        "movapd 80(%%r9), %%xmm13;"
        "movapd 96(%%r9), %%xmm14;"
        "movapd 112(%%r9), %%xmm15;"
        #endif

        ".align 64;"
        "_work_loop_sqrt_sd%=:"
        #ifdef REGONLY
        "sqrtsd %%xmm8, %%xmm0;"
        "sqrtsd %%xmm9, %%xmm0;"
        "sqrtsd %%xmm10, %%xmm0;"
        "sqrtsd %%xmm11, %%xmm0;"
        "sqrtsd %%xmm12, %%xmm0;"
        "sqrtsd %%xmm13, %%xmm0;"
        "sqrtsd %%xmm14, %%xmm0;"
        "sqrtsd %%xmm15, %%xmm0;"
        "sqrtsd %%xmm8, %%xmm0;"
        "sqrtsd %%xmm9, %%xmm0;"
        "sqrtsd %%xmm10, %%xmm0;"
        "sqrtsd %%xmm11, %%xmm0;"
        "sqrtsd %%xmm12, %%xmm0;"
        "sqrtsd %%xmm13, %%xmm0;"
        "sqrtsd %%xmm14, %%xmm0;"
        "sqrtsd %%xmm15, %%xmm0;"
        "sqrtsd %%xmm8, %%xmm0;"
        "sqrtsd %%xmm9, %%xmm0;"
        "sqrtsd %%xmm10, %%xmm0;"
        "sqrtsd %%xmm11, %%xmm0;"
        "sqrtsd %%xmm12, %%xmm0;"
        "sqrtsd %%xmm13, %%xmm0;"
        "sqrtsd %%xmm14, %%xmm0;"
        "sqrtsd %%xmm15, %%xmm0;"
        "sqrtsd %%xmm8, %%xmm0;"
        "sqrtsd %%xmm9, %%xmm0;"
        "sqrtsd %%xmm10, %%xmm0;"
        "sqrtsd %%xmm11, %%xmm0;"
        "sqrtsd %%xmm12, %%xmm0;"
        "sqrtsd %%xmm13, %%xmm0;"
        "sqrtsd %%xmm14, %%xmm0;"
        "sqrtsd %%xmm15, %%xmm0;"
        #else

        "sqrtsd 0(%%r9), %%xmm0;"
        "sqrtsd 16(%%r9), %%xmm0;"
        "sqrtsd 32(%%r9), %%xmm0;"
        "sqrtsd 48(%%r9), %%xmm0;"

        "sqrtsd 64(%%r9), %%xmm0;"
        "sqrtsd 80(%%r9), %%xmm0;"
        "sqrtsd 96(%%r9), %%xmm0;"
        "sqrtsd 112(%%r9), %%xmm0;"

        "sqrtsd 128(%%r9), %%xmm0;"
        "sqrtsd 144(%%r9), %%xmm0;"
        "sqrtsd 160(%%r9), %%xmm0;"
        "sqrtsd 176(%%r9), %%xmm0;"

        "sqrtsd 192(%%r9), %%xmm0;"
        "sqrtsd 208(%%r9), %%xmm0;"
        "sqrtsd 224(%%r9), %%xmm0;"
        "sqrtsd 240(%%r9), %%xmm0;"

        "sqrtsd 256(%%r9), %%xmm0;"
        "sqrtsd 272(%%r9), %%xmm0;"
        "sqrtsd 288(%%r9), %%xmm0;"
        "sqrtsd 304(%%r9), %%xmm0;"

        "sqrtsd 320(%%r9), %%xmm0;"
        "sqrtsd 336(%%r9), %%xmm0;"
        "sqrtsd 352(%%r9), %%xmm0;"
        "sqrtsd 368(%%r9), %%xmm0;"

        "sqrtsd 384(%%r9), %%xmm0;"
        "sqrtsd 400(%%r9), %%xmm0;"
        "sqrtsd 416(%%r9), %%xmm0;"
        "sqrtsd 432(%%r9), %%xmm0;"

        "sqrtsd 448(%%r9), %%xmm0;"
        "sqrtsd 464(%%r9), %%xmm0;"
        "sqrtsd 480(%%r9), %%xmm0;"
        "sqrtsd 496(%%r9), %%xmm0;"
        #endif
        "add $512,%%r9;"
        "sub $1,%%r10;"
        "jnz _skip_reset_sqrt_sd%=;" // reset buffer if the end is reached
        "mov %%r14,%%r9;"   //restore addr
        "mov %%r8,%%r10;"   //restore passes
        "_skip_reset_sqrt_sd%=:"
        "sub $32,%%r15;"
        "jnz _work_loop_sqrt_sd%=;"

        "mov %%r13,%%rcx;" //restore length
        : "=a" (a), "=b" (b), "=c" (c), "=d" (d)
        : "a"(addr), "b" (passes), "c" (length)
        : "%r8", "%r9", "%r10", "%r11", "%r12", "%r13", "%r14", "%r15", "xmm0", "xmm1", "xmm2", "xmm3", "xmm4", "xmm5", "xmm6", "xmm7", "xmm8", "xmm9", "xmm10", "xmm11", "xmm12", "xmm13", "xmm14", "xmm15"

    );
    ret=c;

    return ret;
}

#endif

int main() {


    double targetDurationSeconds = 10.0;

    const char* WORKLOAD_NAMES[] = { "busywait", "idle", "compute", "addpd", "matmul", "memoryread", "mulpd", "sqrt", "memorywrite", "memorycopy"};
    if (WORKLOAD < 0 || WORKLOAD > WORKLOAD_MEMORY_COPY) {
        printf("Invalid workload: %d\n", WORKLOAD);
        return 1;
    }
    printf("Running workload: %s\n", WORKLOAD_NAMES[WORKLOAD]);

{
    double start = omp_get_wtime();
    double target = start + targetDurationSeconds;
    double m = 0.0;
#if WORKLOAD == WORKLOAD_COMPUTE || WORKLOAD == WORKLOAD_SQRT || WORKLOAD == WORKLOAD_MATMUL || WORKLOAD == WORKLOAD_MEMORY_READ || WORKLOAD == WORKLOAD_MEMORY_WRITE || WORKLOAD == WORKLOAD_MEMORY_COPY || WORKLOAD == WORKLOAD_ADDPD || WORKLOAD == WORKLOAD_MULPD
#define A_N (1024 * 1024 * 8)
    double* A = malloc(sizeof(double) * A_N);
    if(A == NULL) {
        printf("Failed to allocate array A");
        return 0;
    }
    for(int i = 0; i < A_N; i++) {
        A[i] = 1.0;
    }
#endif
#if WORKLOAD == WORKLOAD_COMPUTE || WORKLOAD == WORKLOAD_MATMUL
#define B_N (1024 * 1024 * 8)
    double* B = malloc(sizeof(double) * B_N);
    if(B == NULL) {
        printf("Failed to allocate array B");
        return 0;
    }
    for(int i = 0; i < B_N; i++) {
        B[i] = 1.0;
    }
#endif
#if WORKLOAD == WORKLOAD_MATMUL
#define C_N A_N
    double* C = malloc(sizeof(double) * C_N);
    if(C == NULL) {
        printf("Failed to allocate array C");
        return 0;
    }
    for(int i = 0; i < C_N; i++) {
        C[i] = 1.0;
    }
#endif
    int n_reps = 0;
    do {
        n_reps += 1;
#if WORKLOAD == WORKLOAD_BUSY_WAIT
        m += 1;
#elif WORKLOAD == WORKLOAD_IDLE
        sleep(targetDurationSeconds);
        m = 137.42;
#elif WORKLOAD == WORKLOAD_COMPUTE
        for(int i = 0; i < A_N; i++) {
            m += A[i] * B[i];
        }
#elif WORKLOAD == WORKLOAD_ADDPD
        m += addpd_kernel(A, 32) % 5;
#elif WORKLOAD == WORKLOAD_MATMUL
        double matrix_size = 512;
        cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, matrix_size, matrix_size, matrix_size, 1.0, A, matrix_size, B, matrix_size,
                            1.0, C, matrix_size);
        m = C[C_N - 1];
#elif WORKLOAD == WORKLOAD_MEMORY_READ
        #pragma omp parallel for
        for(int i = 0; i < A_N; i++) {
            m += A[i];
        }
#elif WORKLOAD == WORKLOAD_MULPD
        m += mulpd_kernel(A, 32) % 5;
#elif WORKLOAD == WORKLOAD_SQRT
        m += sqrtsd_kernel(A, A_N, 1) % 5;
#elif WORKLOAD == WORKLOAD_MEMORY_WRITE
        #pragma omp parallel for
        for(int i = 0; i < A_N; i++) {
            A[i] = i;
        }
        m += A[A_N - 1];
#elif WORKLOAD == WORKLOAD_MEMORY_COPY
        #pragma omp parallel for
        for(int i = 0; i < A_N; i++) {
            A[i] += A[i];
        }
        m += A[A_N - 1];
#else
#error "Invalid workload configured"
#endif

    } while(omp_get_wtime() < target);
    printf("Result: %.2f Repetitions: %d Elapsed time: %.4fs\n", m, n_reps, omp_get_wtime() - start);
#ifdef A_n
    free(A);
#endif
#ifdef B_N
    free(B);
#endif
#ifdef C_N
    free(C);
#endif
}
    return 0;
}
