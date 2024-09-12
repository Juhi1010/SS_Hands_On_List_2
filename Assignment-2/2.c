#include <sys/resource.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>

int main () {

    struct rlimit no_file, rl_cpu, rl_stack, rl_fsize;

	if (getrlimit(RLIMIT_NOFILE, &no_file) == 0)
	{
              printf("RLIMIT_NOFILE limits - soft limit= %llu \t"
			" hard limit= %llu \n", no_file.rlim_cur,no_file.rlim_max);
	}  

    if (getrlimit(RLIMIT_CPU, &rl_cpu) == 0)
	{
              printf("RLIMIT_CPU limits - soft limit= %llu \t"
			" hard limit= %llu \n", rl_cpu.rlim_cur,rl_cpu.rlim_max);
	}

    if (getrlimit(RLIMIT_STACK, &rl_stack) == 0)
	{
              printf("RLIMIT_STACK limits - soft limit= %llu \t"
			" hard limit= %llu \n", rl_stack.rlim_cur,rl_stack.rlim_max);
	}

    if (getrlimit(RLIMIT_FSIZE, &rl_fsize) == 0)
	{
              printf("RLIMIT_FSIZE limits - soft limit= %llu \t"
			" hard limit= %llu \n", rl_fsize.rlim_cur,rl_fsize.rlim_max);
	}

    return 0;
}