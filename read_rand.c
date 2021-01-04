#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

//필요하면 header file 추가 가능

#define BUFFER_SIZE 1024
#define SUFFLE_NUM 10000 // 이 값은 마음대로 수정할 수 있음

void GenRecordSequence(int *list, int n);
void swap(int *a, int *b);
// 필요한 함수가 있으면 더 추가할 수 있음

//
// argv[1]: 레코드 파일명
//
int main(int argc, char *argv[])
{
	 int *read_order_list = NULL;
	 int num_of_records;
	 int fd;
	 off_t fsize;
	 char buf[BUFFER_SIZE];

	 struct timeval start, end;


	 if(argc < 2) {
		 fprintf(stderr, "usage : %s file\n", argv[0]);
		 exit(1);
	 }

	 if((fd = open(argv[1], O_RDONLY)) < 0) {
		 fprintf(stderr, "open error for %s]\n", argv[1]);
		 exit(1);
	 }

	 if((fsize = lseek(fd, 0, SEEK_END)) < 0) {
		 fprintf(stderr, "lseek error\n");
		 exit(1);
	 }

	 lseek(fd, 0, SEEK_SET);

	 num_of_records = fsize/100;

	 read_order_list=(int*)calloc(num_of_records, sizeof(int));


	 // 아래 함수를 실행하면 'read_order_list' 배열에 추후 랜덤하게 읽어야 할 레코드 번호들이 순서대로 나열되어 저장됨
		     // 'num_of_records'는 레코드 파일에 저장되어 있는 전체 레코드의 수를 의미함
	 GenRecordSequence(read_order_list, num_of_records);


	 // 'read_order_list'를 이용하여 표준 입력으로 받은 레코드 파일로부터 레코드를 random 하게 읽어들이고,
		     // 이때 걸리는 시간을 측정하는 코드 구현함

	 gettimeofday(&start, NULL);


	 for(int i=0; i<num_of_records; i++) {
		 lseek(fd, (read_order_list[i]*100), SEEK_SET);
		 read(fd, buf, 100);
		 memset(buf, 0, BUFFER_SIZE);
	 }


	 gettimeofday(&end, NULL);
	
	 end.tv_usec = end.tv_usec - start.tv_usec;
	 end.tv_sec = end.tv_sec - start.tv_sec;
	 end.tv_usec += (end.tv_sec*1000000);
	 
	 printf("#records: %d timecost: %ld us\n", num_of_records, end.tv_usec);


	 free(read_order_list);

	 return 0;
}


void GenRecordSequence(int *list, int n)
{
	 int i, j, k;

	 srand((unsigned int)time(0));

	 for(i=0; i<n; i++)
	 {
		 list[i] = i;
	 }
			    
	 for(i=0; i<SUFFLE_NUM; i++)
	 {
		 j = rand() % n;
		 k = rand() % n;
		 swap(&list[j], &list[k]);
	 }

	 return;
}


void swap(int *a, int *b)
{
	 int tmp;

	 tmp = *a;
	 *a = *b;
	 *b = tmp;

	 return;
}

