#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[])
{

	char buf[BUFFER_SIZE];
	off_t offset, fsize;
	int rdbytes;
	int fd;
	int length;
	
	if(argc != 4) { //인자로 파일명, 오프셋, 읽기 바이트 수를 모두 받았는지 확인
		fprintf(stderr, "Usage : %s filein fileout\n", argv[0]);
		exit(1);
	}

	if((fd=open(argv[1], O_RDONLY)) <0) { //인자로 받은 파일명을 읽기전용으로 open
		fprintf(stderr, "open error for %s\n", argv[1]);
		exit(1);
	}

	offset = atol(argv[2]); //인자로 받은 오프셋을 off_t 타입으로 변경
	rdbytes = atoi(argv[3]); //인자로 받은 읽기 바이트 수를 int 타입으로 변경

	fsize=lseek(fd,0,SEEK_END); //인자로 받은 파일의 크기 저장

	if((lseek(fd, offset, SEEK_SET)) <0) { //오프셋의 위치를 인자로 받은 오프셋으로 변경
		fprintf(stderr, "lseek error\n");
		exit(1);
	}

	length=read(fd, buf, rdbytes); //fd가 의미하는 파일에서 rdbytes만큼을 읽어 buf에 저장
	write(1, buf, length); //buf에서 length만큼을 표준출력

	if(offset>fsize) { //인자로 받은 오프셋이 파일 크기보다 큰 경우
		printf("읽을 데이터가 존재하지 않습니다.\n");
		exit(1);
	}

	exit(0);
}
