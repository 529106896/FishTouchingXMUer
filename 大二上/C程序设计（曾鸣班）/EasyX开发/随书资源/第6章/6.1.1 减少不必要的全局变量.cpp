#include <stdio.h>
void addScore(int *sc)
{
	*sc = *sc + 1;
}
void minusScore(int *sc)
{
	*sc = *sc - 1;
}
void printScore(int sc)
{
	printf("%d\n",sc);
}	

int main()
{	
	int score = 5; // 局部变量
	addScore(&score);
	printScore(score);
	minusScore(&score);
	printScore(score);	
	return 0;
}
