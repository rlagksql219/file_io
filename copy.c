#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 100
#define COPY_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

int main(int argc,char *argv[])
{
	char buf[BUFFER_SIZE];
	int fd1, fd2;
	int length;

	if(argc != 3) { //인자로 원본파일명과 복사본파일명 두개를 모두 받았는지 확인
		fprintf(stderr, "Usage : %s filein fileout\n", argv[0]);
		exit(1);
	}

	if((fd1=open(argv[1], O_RDONLY)) <0) { //인자로 받은 원본파일 읽기전용으로 open
		fprintf(stderr, "open error for %s\n", argv[1]);
		exit(1);
	}

	if((fd2=open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, COPY_MODE)) <0) { //인자로 받은 복사본 파일을 쓰기전용으로 open
		fprintf(stderr, "open error for %s\n", argv[2]);
		exit(1);
	}

	while((length = read(fd1, buf, BUFFER_SIZE)) >0) //fd1이 의미하는 원본파일을 BUFFER_SIZE만큼씩 읽으면서 buf에 저장(다 읽을 때까지 반복)
		write(fd2,buf,length); //buf에서 length만큼을 fd2가 의미하는 복사본 파일에 write

	exit(0);
}
