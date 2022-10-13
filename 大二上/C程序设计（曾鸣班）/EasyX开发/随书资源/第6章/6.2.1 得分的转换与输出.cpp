#include<stdio.h>
#include<stdlib.h>
void Int2Str(int x,char *istr) // 将正整数x转换为字符串istr
{
    char ch,*p,*t;
    int r;
    p=t=istr;
    while(x>0)  
    {    
        r=x%10;
        x=x/10;
        *p=48+r; //数字0的ascII码值
		p++;
    }
    *p='\0';
    p--;
    while(t<p) //将p中的数字符串倒序排列		
    {
        ch=*t; 
		*t=*p; 
		*p=ch;
        t++; 
		p--;
    }
}   

int main()
{
    char s[30];
    int score=15;
	Int2Str(score,s);   // 使用自定义函数将正整数x转换为字符串istr
	//sprintf(s, "%d", score);  // 使用sprintf函数将整数x转换为字符串istr
    printf("%s\n",s); 	
	return 0;
}
