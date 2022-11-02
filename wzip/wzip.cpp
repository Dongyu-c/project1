#include<iostream>
#include<string.h>
#include<stdio.h>

#include<fcntl.h>
#include<stdlib.h>

#include<sys/types.h>
#include<unistd.h>


void fold(char* path) {

	int fd = open(path, O_RDONLY);

	if (fd < 0) {
		printf("wzip: cannot open file\n");
		exit(1);
	}

	char pre;
	char cur;
	int count = 0;

	if (read(fd, &cur, 1) > 0) {
		pre = cur;
		count = 1;
	}
	while(read(fd,&cur,1)>0) {
		
		if (cur != pre) {
			if (count > 0) {
				write(STDOUT_FILENO, &count, 4);
				write(STDOUT_FILENO, &pre, 1);
			}
			count = 0;
		}

		count += 1;
		pre = cur;
	}
	if (count > 0) {
		write(STDOUT_FILENO, &count, 4);
		write(STDOUT_FILENO, &pre, 1);
	}
	close(fd);
}



int main(int argc, char* argv[]){
	
	if (argc > 1) {
		for (int i = 1; i < argc; i++) {
			fold(argv[i]);
		}
		exit(0);
		
	}else
	{
		printf("wunzip: file1 [file2 ...]\n");
		exit(1);
	}
	
}