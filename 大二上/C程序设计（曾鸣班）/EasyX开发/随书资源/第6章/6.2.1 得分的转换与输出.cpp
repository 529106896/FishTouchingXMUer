#include<stdio.h>
#include<stdlib.h>
void Int2Str(int x,char *istr) // ��������xת��Ϊ�ַ���istr
{
    char ch,*p,*t;
    int r;
    p=t=istr;
    while(x>0)  
    {    
        r=x%10;
        x=x/10;
        *p=48+r; //����0��ascII��ֵ
		p++;
    }
    *p='\0';
    p--;
    while(t<p) //��p�е����ַ�����������		
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
	Int2Str(score,s);   // ʹ���Զ��庯����������xת��Ϊ�ַ���istr
	//sprintf(s, "%d", score);  // ʹ��sprintf����������xת��Ϊ�ַ���istr
    printf("%s\n",s); 	
	return 0;
}
