/*
 *  Program adopted from: https://github.com/tud-zih-energy/2021-rome-ee/blob/main/RAPL_resoultion/test.c
 */

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <errno.h>
#include <time.h>
#include <sys/file.h>

// Number of MSRs to profile
#define NUM_MSR 2
// Number of samples to profile per MSR
#define NR_MEASUREMENTS 10000
// The CPU to profile MSRs for
#define CPU_INDEX 0

#define MSR_DRAM 0x619
#define MSR_PACKAGE 0x611

/**
 * Represents a model-specific register (MSR) containing the human-readable name and the id of the MSR
 */
typedef struct {
    int m_msr;
    char* m_name;
} named_msr_t;

/**
 * Array of MSRs to profile
 */
static named_msr_t s_msrs[NUM_MSR] =
{
    { MSR_PACKAGE, "package" },
    { MSR_DRAM, "dram" }
};
static long long s_cycles[NUM_MSR][NR_MEASUREMENTS+1];

// reads the current processor timestamp in number of cycles into the provided variable
#define SYNC_RDTSC2(val) \
   do {\
      unsigned int cycles_low, cycles_high;\
      asm volatile("RDTSCP\n\t"\
      "mov %%edx, %0\n\t"\
      "mov %%eax, %1\n\t"\
      "CPUID\n\t": "=r" (cycles_high), "=r" (cycles_low):: "%rax", "%rbx", "%rcx", "%rdx");\
      (val) = ((unsigned long) cycles_low) | (((unsigned long) cycles_high) << 32);\
   } while (0)


void printResults(long long cyclesPerSecond, char* resultFileName)
{
    FILE* file = fopen(resultFileName, "w+");
    if (file == NULL)
    {
        printf("Failed top open result file: %s\n", resultFileName);
        return;
    }
    // Print header
    fprintf(file, "index");
    for (int mi = 0; mi < NUM_MSR; mi++)
    {
        fprintf(file, ",%s_cycles", s_msrs[mi].m_name);
    }
    for (int mi = 0; mi < NUM_MSR; mi++)
    {
        fprintf(file, ",%s_ms", s_msrs[mi].m_name);
    }
    fprintf(file, "\n");

    for (int i = 2; i < NR_MEASUREMENTS - 1 ; i++)
    {
        fprintf(file, "%d", i - 1);
        for (int mi = 0; mi <  NUM_MSR; mi++)
        {
            fprintf(file, ",%lli", s_cycles[mi][i] - s_cycles[mi][i-1]);
        }
        for (int mi = 0; mi <  NUM_MSR; mi++)
        {
            fprintf(file, ",%.6f", (float) ((s_cycles[mi][i] - s_cycles[mi][i-1]) / (double) cyclesPerSecond));
        }
        fprintf(file, "\n");
    }

    fclose(file);
}

long long measureCyclesPerSecond()
{
    // Measure the number of cycles within a second
    long long start_cyc;
    long long end_cyc;
    SYNC_RDTSC2(start_cyc);
    sleep(1);
    SYNC_RDTSC2(end_cyc);
    return end_cyc - start_cyc;
}

int profileMSR(int mi, long long cyclesPerSecond)
{
    named_msr_t msr = s_msrs[mi];
    printf("Profiling MSR: %s (%x)\n", msr.m_name, msr.m_msr);

    long long status;
    long long cur_status;

    // Open the MSR virtual file
    char buffer[256];
    snprintf(buffer, 256, "/dev/cpu/%d/msr", CPU_INDEX);
    int fd = open(buffer, O_RDWR);
    if (fd == -1)
    {
        printf("Failed to open msr %x: %s\n", msr.m_msr, strerror(errno));
        return -1;
    }
    // Initially read MSR value and current timestamp
    pread(fd, &status, 8, msr.m_msr);
    SYNC_RDTSC2(s_cycles[mi][0]);
    for (int i = 1; i < NR_MEASUREMENTS; i++)
    {
        // Wait for the MSR value to update
        do
        {
            pread(fd, &cur_status, 8, msr.m_msr);
        }
        while (cur_status == status);
        // store current MSR value and the timestamp
        status = cur_status;
        SYNC_RDTSC2(s_cycles[mi][i]);
    }
    close(fd);
    return 0;
}

int main(int argc, char** argv)
{
    long long cyclesPerSecond = measureCyclesPerSecond();
    printf("Cycles per second: %lld\n", cyclesPerSecond);

    for (int mi = 0; mi < NUM_MSR; mi++)
    {
        int ret = profileMSR(mi, cyclesPerSecond);
        if (ret != 0)
        {
            return ret;
        }
    }
    char resultFileName[256];
    snprintf(resultFileName, 256, "rapl-update-interval-%ld.csv", time(NULL));
    printResults(cyclesPerSecond, resultFileName);
    printf("Results have been written to %s\n", resultFileName);
    return 0;
}