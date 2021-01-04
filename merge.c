#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int  main(int argc, char *argv[])
{
	char buf[BUFFER_SIZE];
	int fd1, fd2;
	int length;

	if(argc !=3) { //인자로 2개의 파일을 모두 받았는지 확인
		fprintf(stderr, "Usage : %s filein fileout\n", argv[0]);
		exit(1);
	}

	if((fd1=open(argv[1], O_RDWR)) <0) { //인자로 받은 파일1을 읽기&쓰기 전용으로 open
		fprintf(stderr, "open error for %s\n", argv[1]);
		exit(1);
	}

	if((fd2=open(argv[2], O_RDONLY)) <0) { //인자로 받은 파일2를 읽기전용으로 open
		fprintf(stderr, "open error for %s\n", argv[1]);
		exit(1);
	}

	if(lseek(fd1, 0, SEEK_END) <0) { //fd1이 의미하는 파일1의 오프셋의 위치를 맨 끝으로 변경
		fprintf(stderr, "lseek error\n");
		exit(1);
	}

	while ((length = read(fd2, buf, BUFFER_SIZE)) >0) //fd2가 의미하는 파일2에서 BUFFER_SIZE만큼 읽어 buf에 저장(파일을 다 읽을 때까지 반복)
		write(fd1, buf, length); //buf에서 length만큼을 fd1이 의미하는 파일에 write

	exit(0);
}
