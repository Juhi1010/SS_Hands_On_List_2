#include <stdio.h>
#include <sys/resource.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {

	struct rlimit old_lim, new_lim;

	if (getrlimit(RLIMIT_FSIZE, &old_lim) == 0) {
              printf("RLIMIT_FSIZE old limits - soft limit= %llu \t"
			" hard limit= %llu \n", old_lim.rlim_cur,old_lim.rlim_max);
	}

	new_lim.rlim_cur = 16;
	new_lim.rlim_max = 2048;

	if (setrlimit(RLIMIT_FSIZE, &new_lim) == -1)
	    fprintf(stderr, "%s\n", strerror(errno));

	if (getrlimit(RLIMIT_FSIZE, &new_lim) == 0) {
      	printf("RLIMIT_FSIZE new limits - soft limit= %llu "
	 	"\t hard limit= %llu \n", new_lim.rlim_cur,new_lim.rlim_max);
	}

	else
	    fprintf(stderr, "%s\n", strerror(errno));	
	return 0;
}