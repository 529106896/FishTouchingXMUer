#include<stdio.h>
#include<stdlib.h>
int main()
{
	int high,width,i,j;
	scanf("%d%d",&high,&width);  // �û��Զ������볤��

	// ���䶯̬��ά������ڴ�ռ�
	int **canvas=(int**)malloc(high*sizeof(int*)); 
	for(i=0;i<high;i++)
		canvas[i]=(int*)malloc(width*sizeof(int));
	
	// canvas���Ե���һ���ά������ʹ����
	for (i=0;i<high;i++)
		for (j=0;j<width;j++)
			canvas[i][j] = i+j;
	for (i=0;i<high;i++)
	{
		for (j=0;j<width;j++)
			printf("%d ",canvas[i][j]);
		printf("\n");
	}
		
	// ʹ����������̬������ڴ�ռ�
	for(i=0; i<high; i++)
		free(canvas[i]);
	free(canvas);
	
	return 0;
}
