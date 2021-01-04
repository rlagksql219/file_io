#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[])
{
	char buf1[BUFFER_SIZE], buf2[BUFFER_SIZE], buf3[BUFFER_SIZE];
	off_t offset;
	int rdbytes;
	int fd1, fd2;
	int length;

	if(argc != 4) { //인자로 파일명, 오프셋, 삭제 바이트 수를 모두 받았는지 확인
		fprintf(stderr, "Usage : %s filein fileout\n", argv[0]);
		exit(1);
	}

	if((fd1=open(argv[1], O_RDWR)) <0) { //인자로 받은 파일을 읽기&쓰기 전용으로 open
		fprintf(stderr, "open error for %s\n", argv[1]);
		exit(1);
	}

	offset = atol(argv[2]); //인자로 받은 오프셋을 off_t타입으로 변경
	rdbytes = atoi(argv[3]); //인자로 받은 삭제 바이트 수를 int타입으로 변경
	length = lseek(fd1, 0, SEEK_END); //fd1이 의미하는 파일의 크기 계산

	if((lseek(fd1, 0, SEEK_SET)) <0) { //fd1이 의미하는 파일의 오프셋을 파일 처음으로 변경
		fprintf(stderr, "lseek error\n");
		exit(1);
	}

	read(fd1, buf1, offset); //fd1이 의미하는 파일에서 인자로 받은 오프셋만큼을 읽어 buf1에 저장
	read(fd1, buf2, rdbytes); //fd1이 의미하는 파일에서 인자로 받은 삭제 바이트 수만큼을 읽어 buf2에 저장
	while((read(fd1, buf3, BUFFER_SIZE)) >0) { //fd가 의미하는 파일에서 BUFFER_SIZE만큼을 읽어 buf3에 저장(파일을 다 읽을 때까지 반복)
	}

	if((fd2=creat(argv[1], 0666)) <0) { //인자로 받은 파일을 fd2에 새로 생성
		fprintf(stderr, "creat error for %s\n", argv[1]);
		exit(1);
	}

	write(fd2, buf1, offset); //buf1에 저장된 값을 offset만큼 fd2가 의미하는 파일에 write
	write(fd2, buf3, length-(offset+rdbytes)); //buf3에 저장된 값을 해당 크기만큼 fd2가 의미하는 파일에 write
	//length-(offset+rdbytes)는 파일에서 삭제 바이트 수 만큼을 읽은 뒤, 오프셋의 위치부터 파일 끝까지의 크기를 의미

	if(offset>length) { //인자로 받은 오프셋이 파일 크기보다 큰 경우
		printf("삭제할 데이터가 존재하지 않습니다.\n");
		exit(1);
	}

	exit(0);
}
