#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[])
{
	off_t offset;
	char newdata[BUFFER_SIZE], buf[BUFFER_SIZE]={0,};
	int fd;
	int length, length2;

	if(argc != 4) { //인자로 파일명, 오프셋, 데이터를 모두 받았는지 확인
		fprintf(stderr, "Usage : %s filein fileout\n", argv[0]);
		exit(1);
	}

	if((fd=open(argv[1], O_RDWR)) <0) { //인자로 받은 파일을 읽기&쓰기 전용으로 open
		fprintf(stderr, "open error for %s\n", argv[1]);
		exit(1);
	}

	offset = atol(argv[2]); //인자로 받은 오프셋을 off_t 타입으로 변경
	strcpy(newdata, argv[3]); //인자로 받은 데이터를 문자열로 복사
	length = strlen(newdata); //인자로 받은 데이터의 크기를 계산
	length2 = lseek(fd,0,SEEK_END); //fd가 의미하는 파일의 크기를 계산

	if((lseek(fd, offset, SEEK_SET)) <0) { //fd가 의미하는 파일의 오프셋의 위치를 입력받은 오프셋으로 변경
		fprintf(stderr, "lseek error\n");
		exit(1);
	}

	while((read(fd, buf, BUFFER_SIZE)) >0) { //fd가 의미하는 파일에 BUFFER_SIZE만큼을 읽어 buf에 저장(파일을 다 읽을 때까지 반복)
	}

	if((lseek(fd, offset, SEEK_SET)) <0) { //fd가 의미하는 파일의 오프셋의 위치를 입력받은 오프셋으로 변경
		fprintf(stderr, "lseek error\n");
		exit(1);
	}

	if(offset>=length2) { //인자로 받은 오프셋이 파일 크기보다 큰 경우
		printf("오프셋이 파일의 크기보다 큽니다.\n");
		exit(1);
	}

	write(fd, newdata, length); //입력받은 데이터를 해당 크기만큼 fd가 의미하는 파일에 write
	write(fd, buf, length2-offset); //buf에 저장된 값을 해당 크기만큼 fd가 의미하는 파일에 write
	//length2-offset은 입력받은 오프셋의 위치부터 파일 끝까지의 크기를 의미

	exit(0);
}
