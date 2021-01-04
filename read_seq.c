#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define BUFFER_SIZE 1024

//�ʿ��ϸ� header file �߰� ����

//
// argv[1]: ���ڵ� ���ϸ�
//
int main(int argc, char *argv[])
{

	// ǥ���Է����� ���� ���ڵ� ���Ͽ� ����Ǿ� �ִ� ��ü ���ڵ带 "������"���� �о���̰�, �̶�
	// �ɸ��� �ð��� �����ϴ� �ڵ� ������

	int fd;
	off_t fsize;
	char buf[BUFFER_SIZE];
	
	struct timeval start, end;


	if(argc < 2) {
		fprintf(stderr, "usage : %s file\n", argv[0]);
		exit(1);
	}

	if((fd = open(argv[1], O_RDONLY)) < 0) {
		fprintf(stderr, "open error for %s\n", argv[1]);
		exit(1);
	}
	
	if((fsize = lseek(fd, 0, SEEK_END)) < 0) {
		fprintf(stderr, "lseek error\n");
		exit(1);
	}

	lseek(fd, 0, SEEK_SET);

	gettimeofday(&start, NULL);


	while((read(fd, buf, BUFFER_SIZE)) > 0) {
		memset(buf, 0, BUFFER_SIZE);
	}

	gettimeofday(&end, NULL);

	end.tv_usec = end.tv_usec - start.tv_usec;
	end.tv_sec = end.tv_sec - start.tv_sec;
	end.tv_usec += (end.tv_sec*1000000);


	printf("#records: %ld timecost: %ld us\n", fsize/100, end.tv_usec);

	exit(0);
}
