/*
 *  PROGRAM SOURCE: https://github.com/tud-zih-energy/2021-rome-ee/blob/main/RAPL_resoultion/test.c
 */

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define NR_MEASUREMENTS 10000
static long long cycles[NR_MEASUREMENTS+1];


#define MSR_DRAM 0x619
#define MSR_PACKAGE 0x611
static long long MSR=MSR_PACKAGE;


#define sync_rdtsc2(val) \
   do {\
      unsigned int cycles_low, cycles_high;\
      asm volatile("RDTSCP\n\t"\
      "mov %%edx, %0\n\t"\
      "mov %%eax, %1\n\t"\
      "CPUID\n\t": "=r" (cycles_high), "=r" (cycles_low):: "%rax", "%rbx", "%rcx", "%rdx");\
      (val) = ((unsigned long) cycles_low) | (((unsigned long) cycles_high) << 32);\
   } while (0)


void main()
{
        long long start_cyc = 0;
        long long end_cyc = 0;
        sync_rdtsc2(start_cyc);
        sleep(1);
        sync_rdtsc2(end_cyc);
        // First measure the cycles per second
        printf("Cycles per second: %d\n", end_cyc - start_cyc);
        long long status;
        long long cur_status;
        char buffer[256];
        sprintf(buffer,"/dev/cpu/0/msr");
        int fd = open(buffer,O_RDWR);
        pread(fd,&status,8,MSR);
        sync_rdtsc2(cycles[0]);
        for ( int i=1 ; i<NR_MEASUREMENTS ; i++ )
        {
                do
                {
                        pread(fd,&cur_status,8,MSR);
                } while(cur_status==status);
                status=cur_status;
                sync_rdtsc2(cycles[i]);
        }

        for ( int i=2 ; i<NR_MEASUREMENTS-1 ; i++ )
        {
                printf("%lli\n",cycles[i]-cycles[i-1]);
        }

}