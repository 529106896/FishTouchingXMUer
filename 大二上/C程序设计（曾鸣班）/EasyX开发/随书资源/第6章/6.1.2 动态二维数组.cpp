#include<stdio.h>
#include<stdlib.h>
int main()
{
	int high,width,i,j;
	scanf("%d%d",&high,&width);  // 用户自定义输入长宽

	// 分配动态二维数组的内存空间
	int **canvas=(int**)malloc(high*sizeof(int*)); 
	for(i=0;i<high;i++)
		canvas[i]=(int*)malloc(width*sizeof(int));
	
	// canvas可以当成一般二维数组来使用了
	for (i=0;i<high;i++)
		for (j=0;j<width;j++)
			canvas[i][j] = i+j;
	for (i=0;i<high;i++)
	{
		for (j=0;j<width;j++)
			printf("%d ",canvas[i][j]);
		printf("\n");
	}
		
	// 使用完后清除动态数组的内存空间
	for(i=0; i<high; i++)
		free(canvas[i]);
	free(canvas);
	
	return 0;
}
