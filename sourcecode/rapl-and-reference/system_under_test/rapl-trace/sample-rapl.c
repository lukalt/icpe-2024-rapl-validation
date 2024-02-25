#ifndef _DEFAULT_SOURCE
#define _DEFAULT_SOURCE
#endif
#ifndef _XOPEN_SOURCE
#define _XOPEN_SOURCE 500
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <inttypes.h>
#include <unistd.h>
#include <math.h>
#include <string.h>
#include <sys/time.h>
#include <sys/wait.h>
#define TOGGLE_GPIO 1
#ifdef TOGGLE_GPIO
#include <Python.h>
#endif
#define MSR_RAPL_POWER_UNIT		0x606
/* Package RAPL Domain */
#define MSR_PKG_ENERGY_STATUS		0x611

/* PP0 RAPL Domain */
#define MSR_PP0_ENERGY_STATUS		0x639

/* PP1 RAPL Domain, may reflect to uncore devices */
#define MSR_PP1_ENERGY_STATUS		0x641

/* DRAM RAPL Domain */
#define MSR_DRAM_ENERGY_STATUS		0x619

/* PSYS RAPL Domain */
#define MSR_PLATFORM_ENERGY_STATUS	0x64d

static int open_msr(int core) {

    char msr_filename[BUFSIZ];
    int fd;

    sprintf(msr_filename, "/dev/cpu/%d/msr", core);
    fd = open(msr_filename, O_RDONLY);
    if (fd < 0) {
        if (errno == ENXIO) {
            fprintf(stderr, "rdmsr: No CPU %d\n", core);
            exit(2);
        } else if (errno == EIO) {
            fprintf(stderr, "rdmsr: CPU %d doesn't support MSRs\n",
                    core);
            exit(3);
        } else {
            perror("rdmsr:open");
            fprintf(stderr, "Trying to open %s\n", msr_filename);
            exit(127);
        }
    }

    return fd;
}

double get_wall_time(){
    struct timeval time;
    if (gettimeofday(&time,NULL)){
        //  Handle error
        return 0;
    }
    return (double)time.tv_sec + (double)time.tv_usec * .000001;
}

static long long read_msr(int fd, int which) {

    uint64_t data;

    if ( pread(fd, &data, sizeof data, which) != sizeof data ) {
        perror("rdmsr:pread");
        exit(127);
    }

    return (long long)data;
}

#define CPU_SANDYBRIDGE		42
#define CPU_SANDYBRIDGE_EP	45
#define CPU_IVYBRIDGE		58
#define CPU_IVYBRIDGE_EP	62
#define CPU_HASWELL		60
#define CPU_HASWELL_ULT		69
#define CPU_HASWELL_GT3E	70
#define CPU_HASWELL_EP		63
#define CPU_BROADWELL		61
#define CPU_BROADWELL_GT3E	71
#define CPU_BROADWELL_EP	79
#define CPU_SKYLAKE		78
#define CPU_SKYLAKE_HS		94
#define CPU_SKYLAKE_X		85
#define CPU_ICELAKE_SP	    106
#define CPU_KNIGHTS_LANDING	87
#define CPU_KNIGHTS_MILL	133
#define CPU_KABYLAKE_MOBILE	142
#define CPU_KABYLAKE		158
#define CPU_ATOM_GOLDMONT	92
#define CPU_ATOM_GEMINI_LAKE	122
#define CPU_ATOM_DENVERTON	95

static int detect_cpu(void) {

    FILE *fff;

    int family,model=-1;
    char buffer[BUFSIZ],*result;
    char vendor[BUFSIZ];

    fff=fopen("/proc/cpuinfo","r");
    if (fff==NULL) return -1;

    while(1) {
        result=fgets(buffer,BUFSIZ,fff);
        if (result==NULL) break;

        if (!strncmp(result,"vendor_id",8)) {
            sscanf(result,"%*s%*s%s",vendor);

            if (strncmp(vendor,"GenuineIntel",12) != 0) {
                printf("%s not an Intel chip\n",vendor);
                return -1;
            }
        }

        if (!strncmp(result,"cpu family",10)) {
            sscanf(result,"%*s%*s%*s%d",&family);
            if (family!=6) {
                printf("Wrong CPU family %d\n",family);
                return -1;
            }
        }

        if (!strncmp(result,"model",5)) {
            sscanf(result,"%*s%*s%d",&model);
        }

    }

    fclose(fff);

    printf("Found ");

    switch(model) {
        case CPU_SANDYBRIDGE:
            printf("Sandybridge");
            break;
        case CPU_SANDYBRIDGE_EP:
            printf("Sandybridge-EP");
            break;
        case CPU_IVYBRIDGE:
            printf("Ivybridge");
            break;
        case CPU_IVYBRIDGE_EP:
            printf("Ivybridge-EP");
            break;
        case CPU_HASWELL:
        case CPU_HASWELL_ULT:
        case CPU_HASWELL_GT3E:
            printf("Haswell");
            break;
        case CPU_HASWELL_EP:
            printf("Haswell-EP");
            break;
        case CPU_BROADWELL:
        case CPU_BROADWELL_GT3E:
            printf("Broadwell");
            break;
        case CPU_BROADWELL_EP:
            printf("Broadwell-EP");
            break;
        case CPU_SKYLAKE:
        case CPU_SKYLAKE_HS:
            printf("Skylake");
            break;
        case CPU_SKYLAKE_X:
            printf("Skylake-X");
            break;
        case CPU_KABYLAKE:
        case CPU_KABYLAKE_MOBILE:
            printf("Kaby Lake");
            break;
        case CPU_KNIGHTS_LANDING:
            printf("Knight's Landing");
            break;
        case CPU_KNIGHTS_MILL:
            printf("Knight's Mill");
            break;
        case CPU_ATOM_GOLDMONT:
        case CPU_ATOM_GEMINI_LAKE:
        case CPU_ATOM_DENVERTON:
            printf("Atom");
            break;
        case CPU_ICELAKE_SP:
            printf("Icelake-SP");
            break;
        default:
            printf("Unsupported model %d\n",model);
            model=-1;
            break;
    }

    printf(" Processor type\n");

    return model;
}

#define MAX_CPUS	1024
#define MAX_PACKAGES	16

static int total_cores=0,total_packages=0;
static int package_map[MAX_PACKAGES];

static int detect_packages(void) {

    char filename[BUFSIZ];
    FILE *fff;
    int package;
    int i;

    for(i=0;i<MAX_PACKAGES;i++) package_map[i]=-1;

    printf("\t");
    for(i=0;i<MAX_CPUS;i++) {
        sprintf(filename,"/sys/devices/system/cpu/cpu%d/topology/physical_package_id",i);
        fff=fopen(filename,"r");
        if (fff==NULL) break;
        fscanf(fff,"%d",&package);
        fclose(fff);

        if (package_map[package]==-1) {
            total_packages++;
            package_map[package]=i;
        }

    }

    printf("\n");

    total_cores=i;

    printf("\tDetected %d cores in %d packages\n\n",
           total_cores,total_packages);
    return 0;
}



struct PowerPlane {
    char name[64];
    double energyUnit;
    int msr;
};

/*******************************/
/* MSR code                    */
/*******************************/
static int rapl_msr(int cpu_model, char* args, long sampling_interval_micros) {
    int j;
    int fd;
    long long result;
    double result_d;
    double power_units,time_units;
    double cpu_energy_units[MAX_PACKAGES],dram_energy_units[MAX_PACKAGES];

    int dram_avail=0,pp0_avail=0,pp1_avail=0,psys_avail=0;
    int different_units=0;

    printf("\nTrying /dev/msr interface to gather results\n\n");

    if (cpu_model<0) {
        printf("\tUnsupported CPU model %d\n",cpu_model);
        return -1;
    }

    switch(cpu_model) {

        case CPU_SANDYBRIDGE_EP:
        case CPU_IVYBRIDGE_EP:
            pp0_avail=1;
            pp1_avail=0;
            dram_avail=1;
            different_units=0;
            psys_avail=0;
            break;

        case CPU_HASWELL_EP:
        case CPU_BROADWELL_EP:
        case CPU_SKYLAKE_X:
        case CPU_ICELAKE_SP:
            pp0_avail=0;
            pp1_avail=0;
            dram_avail=1;
            different_units=1;
            psys_avail=0;
            break;

        case CPU_KNIGHTS_LANDING:
        case CPU_KNIGHTS_MILL:
            pp0_avail=0;
            pp1_avail=0;
            dram_avail=1;
            different_units=1;
            psys_avail=0;
            break;

        case CPU_SANDYBRIDGE:
        case CPU_IVYBRIDGE:
            pp0_avail=1;
            pp1_avail=1;
            dram_avail=0;
            different_units=0;
            psys_avail=0;
            break;

        case CPU_HASWELL:
        case CPU_HASWELL_ULT:
        case CPU_HASWELL_GT3E:
        case CPU_BROADWELL:
        case CPU_BROADWELL_GT3E:
        case CPU_ATOM_GOLDMONT:
        case CPU_ATOM_GEMINI_LAKE:
        case CPU_ATOM_DENVERTON:
            pp0_avail=1;
            pp1_avail=1;
            dram_avail=1;
            different_units=0;
            psys_avail=0;
            break;

        case CPU_SKYLAKE:
        case CPU_SKYLAKE_HS:
        case CPU_KABYLAKE:
        case CPU_KABYLAKE_MOBILE:
            pp0_avail=1;
            pp1_avail=1;
            dram_avail=1;
            different_units=0;
            psys_avail=1;
            break;
        default:
            printf("Invalid CPU Model: %d\n", cpu_model);
            break;

    }

    int avail_power_planes = 0;
    struct PowerPlane power_planes[8];

    struct PowerPlane pkg = {.name="package", .energyUnit=0, .msr=MSR_PKG_ENERGY_STATUS};
    power_planes[avail_power_planes] = pkg;
    avail_power_planes += 1;

    if(pp0_avail) {
        struct PowerPlane pp0 = {.name="pp0", .energyUnit=0, .msr = MSR_PP0_ENERGY_STATUS};
        power_planes[avail_power_planes] = pp0;
        avail_power_planes += 1;
    }
    if(pp1_avail) {
        struct PowerPlane pp1 = {.name="pp1", .energyUnit=0, .msr = MSR_PP1_ENERGY_STATUS};
        power_planes[avail_power_planes] = pp1;
        avail_power_planes += 1;
    }
    if(dram_avail) {
        struct PowerPlane dram = {.name="ram", .energyUnit=1, .msr = MSR_DRAM_ENERGY_STATUS};
        power_planes[avail_power_planes] = dram;
        avail_power_planes += 1;
    }
    if(psys_avail) {
        struct PowerPlane psys = {.name="psys", .energyUnit=1, .msr = MSR_PLATFORM_ENERGY_STATUS};
        power_planes[avail_power_planes] = psys;
        avail_power_planes += 1;
    }

    printf("Number of power planes available: %d\n", avail_power_planes);
    for(j=0;j<total_packages;j++) {
        printf("\tListing parameters for package #%d\n",j);

        fd=open_msr(package_map[j]);

        /* Calculate the units used */
        result=read_msr(fd,MSR_RAPL_POWER_UNIT);

        power_units=pow(0.5,(double)(result&0xf));
        cpu_energy_units[j]=pow(0.5,(double)((result>>8)&0x1f));
        time_units=pow(0.5,(double)((result>>16)&0xf));

        /* On Haswell EP and Knights Landing */
        /* The DRAM units differ from the CPU ones */
        if (different_units) {
            dram_energy_units[j]=pow(0.5,(double)16);
            printf("DRAM: Using %lf instead of %lf\n",
                   dram_energy_units[j],cpu_energy_units[j]);
        }
        else {
            dram_energy_units[j]=cpu_energy_units[j];
        }

        printf("\t\tPower units = %.3fW\n",power_units);
        printf("\t\tCPU Energy units = %.8fJ\n",cpu_energy_units[j]);
        printf("\t\tDRAM Energy units = %.8fJ\n",dram_energy_units[j]);
        printf("\t\tTime units = %.8fs\n",time_units);
        printf("\n");
        close(fd);

    }

    double last_value[avail_power_planes][total_packages];
    double last_time[avail_power_planes][total_packages];
    int firstPass = 1;
    printf("\n");
#ifdef TOGGLE_GPIO
    Py_Initialize();
PyRun_SimpleString("from PyMCP2221A import PyMCP2221A\n"
"gpio = PyMCP2221A.PyMCP2221A()\n"
"gpio.GPIO_Init()\n"
"gpio.GPIO_2_OutputMode()\n"
"gpio.GPIO_2_Output(0)\n");
#endif

    fprintf(stderr, "#timestamp,interval,socket,domain,energy,power");
    double start = get_wall_time();
#ifdef TOGGLE_GPIO
    PyRun_SimpleString("gpio.GPIO_2_Output(1)\n");
#endif
    int pid = fork();
    if(pid == 0) {
        system(args); // fork a new process, execute delegate command in child process
        return 0;
    } else {
        double start_ts = 0.0;
        // poll rapl data by directly reading MSR while the child process is running
        while (1) {
            for (j = 0; j < total_packages; j++) {

                fd = open_msr(package_map[j]);
                for (int i = 0; i < avail_power_planes; i++) {
                    double unit;
                    if (power_planes[i].energyUnit == 0) {
                        unit = cpu_energy_units[j];
                    } else {
                        unit = dram_energy_units[j];
                    }
                    result_d = ((double) (read_msr(fd, power_planes[i].msr)) * unit); // read the msr value containing the discrete energy counter value and multiply by energy unit to get energy consumption in millijoule
                    double ts = get_wall_time();
                    if (firstPass != 1) { // first run is just to get a reference point for the start, do not print anything here
                        double delay = ts - last_time[i][j];
                        double energy = result_d - last_value[i][j];
                        fprintf(stderr, "%.6f,%.6f,N%d,%s,%.4f,%.4f\n", ts - start_ts, delay, j,
                                power_planes[i].name,
                                energy, energy / delay);

                    } else {
                        start_ts = ts;
                    }
                    last_value[i][j] = result_d;
                    last_time[i][j] = ts;

                }
                close(fd);
            }
            firstPass = 0;
            int status;
            if (waitpid(pid, &status, WNOHANG) == 0) { // checks if child process has terminated. If not terminated yet, 0 is returned
                usleep(sampling_interval_micros);
            } else {
                printf("Child process exited with %d\n", status);
                break;
            }
        }
    }
double end = get_wall_time();
#ifdef TOGGLE_GPIO
    PyRun_SimpleString("gpio.GPIO_2_Output(0)\n"); // set GPIO back to zero
#endif
    printf("time %.4fs\n", end - start);

#ifdef TOGGLE_GPIO
    PyMem_RawFree(NULL); // clean up python code
#endif

    return 0;
}

int main(int argc, char *argv[]) {
    unsigned int totalArgCharLength = 0;
    if(argc <= 1) {
        printf("usage: ./<command> <sampling_microseconds> [command...]\n");
        return EINVAL;
    }
    int sampling_us;
    sampling_us = atoi(argv[1]); // converts string to int
    if(sampling_us <= 0) {
        printf("error: sampling interval can't be negative\n");
        return EINVAL;
    }
    printf("Sampling interval: %d microseconds\n", sampling_us);
#ifdef TOGGLE_GPIO
    printf("GPIO triggering for measurements enabled\n");
#else
    printf("GPIO triggering for measurements is NOT enabled. Compile with -DTOGGLE_GPIO if you wish so\n");
#endif
    for (int i = 2; i < argc; i++) {
        totalArgCharLength += strlen(argv[i]) + 1; // count how many bytes be need to allocate to hold the whole, joined string
    }
    char *args = malloc(sizeof(char) * (totalArgCharLength + 1));
    strcpy(args, "");
    for (int i = 2; i < argc; i++) { // join arguments into a single string and skip the first argument
        if (i > 1) {
            strcat(args, " ");
        }
        strcat(args, argv[i]);
    }

    detect_packages();
    printf("Command to execute: %s\n", args);

    rapl_msr(detect_cpu(),  args, sampling_us);
    free(args);
    return 0;
}
