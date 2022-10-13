#include <stdio.h>
#include <string.h>
#include <stdarg.h> // �ṩ��va_list��va_start��va_arg��va_end
#include <ctype.h>  // �ṩisprintԭ��
#include "Status.h"

/* ȫ�ֱ���*/
Boolean debug = FALSE;  // �Ƿ�ʹ��debugģʽ������ʱ������ΪTRUE������ʱ������ΪFALSE(�޸�debugֵ��һ����Ҫ�������ɾ�̬��)��


/*
 * ���ļ��ж�ȡԤ���Ӣ�ķ���
 *
 * �����Զ��������¼�뺯�������ڴ��ļ�fp�ж�ȡ��ʽ�������룬
 * ��fscanf�Ĳ�֮ͬ�����ڴ˺���ֻ���ȡӢ���ַ������������ַ�����ֱ��������
 *
 * ע��
 * 1. ����Լ�����и�ʽ��Ϊ����ʽ���磺%d%c%s�ȣ�������%2d%5s��
 * 2. ��ȡ�ַ���ʱ�������ո��Ǵ�ӡ�ַ���ֹͣ��ȡ
 */
int ReadData(FILE* fp, char* format, ...) {
    int* i;     // �洢��ȡ��������
    float* f;   // �洢��ȡ���ĸ�����
    char* ch;   // �洢��ȡ�����ַ���
    char* s;    // �洢��ȡ�����ַ�����
    
    int n;      // �����洢�ַ������ַ�����
    
    int len;    // ��ʽ��format�ĳ���
    int k;      // ������ʽ��ʱ���α�
    
    int tmp;    // �ݴ���ļ��ж�ȡ�����ַ�
    
    va_list ap; // �ɱ����ָ�룬ָ��洢���ݵı���
    
    // �ۼƳɹ���ȡ�����ַ���
    int count = 0;
    
    
    /*
     * ��ȡ��ʽ���ĳ���
     * ����Ԥ���ʽ�����ɼ�
     */
    len = strlen(format);
    
    // apָ���׸��ɱ����
    va_start(ap, format);
    
    // ֻ����������������Ϊż�������¶���%
    for(k = 1; k <= len; k = k + 2) {
        // �������з������ַ�
        while((tmp = getc(fp)) != EOF) {
            // �����׸������ַ������������ַ����·���������
            if((tmp >= 0 && tmp <= 127)) {
                ungetc(tmp, fp);
                break;
            }
        }
        
        // ����Ѷ����ļ���β��������ȡ
        if(tmp == EOF) {
            break;
        }
        
        // ������"%c"��Ӧ�ö�ȡ�ַ�
        if(format[k] == 'c') {
            ch = va_arg(ap, char*);
            
            count += fscanf(fp, "%c", ch);
        }
        
        // ������"%d"��Ӧ�ö�ȡ����
        if(format[k] == 'd') {
            i = va_arg(ap, int*);
            
            while((tmp = getc(fp)) != EOF) {
                // Ѱ����������
                if((tmp >= '0' && tmp <= '9') || tmp == '-' || tmp == '+') {
                    ungetc(tmp, fp);
                    break;
                }
            }
            
            if(tmp != EOF) {
                count += fscanf(fp, "%d", i);
            }
        }
        
        // ��ȡ�����ͣ�һ�ɴ洢Ϊdouble����
        if(format[k] == 'f') {
            f = va_arg(ap, float*);
            
            while((tmp = getc(fp)) != EOF) {
                if((tmp >= '0' && tmp <= '9') || tmp == '-' || tmp == '+' || tmp == '.') {
                    ungetc(tmp, fp);
                    break;
                }
            }
            
            if(tmp != EOF) {
                count += fscanf(fp, "%f", f);
            }
        }
        
        // ��ȡ�ַ���
        if(format[k] == 's') {
            s = va_arg(ap, char*);
            
            n = 0;
            
            // �����ų��ո�Ŀɴ�ӡ�ַ�
            while((tmp = getc(fp)) != EOF && (!isprint(tmp) || tmp == ' ')) {
            }
            
            // ���δ���ļ���β
            if(!feof(fp)) {
                
                // ������������ַ����·�������
                ungetc(tmp, fp);
                
                while((tmp = getc(fp)) != EOF) {
                    // �洢�ų��ո�Ŀɴ�ӡ�ַ�
                    if(isprint(tmp) && tmp != ' ') {
                        s[n++] = tmp;
                    } else {
                        ungetc(tmp, fp);
                        break;
                    }
                }
                
                count++;
            }
            
            // �ַ������һ���ַ�Ϊ���ַ�
            s[n] = '\0';
        }
    }// for
    
    va_end(ap);
    
    return count;
}

/*
 * ���»س����Լ������С�
 *
 * ͨ���ڲ��Խ׶�ʱ����Ҫ��ÿһ�����Զ���ͣ�������Թ۲����������ʱ������debug=TRUE��
 * �ڷ���ʱ��������debug=FALSE����ʱ�������Կ齫������ͣ��
 */
void PressEnterToContinue(Boolean debug) {
    fflush(stdin);
    
    // ���ڲ��Խ׶�ʱ��������debug=TRUE���ֶ����뻻�У��Ա��ó�����ͣ�������۲�ÿһ�������
    if(debug) {
        printf("\nPress Enter to Continue...");
        getchar();
        
        // ����ʱ��������debug=FALSE���Զ���ӻ��У�ֱ�ӳ����
    } else {
        printf("\n");
    }
    
    fflush(stdin);
}

/*
 * ������ͣһ��ʱ�䡣
 *
 * time����������ʱ�䣬ֻ�Ǵ���һ��ʱ������
 * ͨ������time�Ĵ�С������ʹ������ͣ�ʵ���ʱ���������С�
 */
void Wait(long time) {
    double i;
    
    if(time<0) {
        time = -time;
    }
    
    for(i = 0.01; i <= 100000.0 * time; i += 0.01) {
        // ��ѭ��
    }
}

/*
 * �����հף�Ѱ����һ��"�ɶ�"���š�
 *
 * �˷��������ڶ�ȡ�ַ������֮ǰ�������������Ŀ���ַ�֮ǰ�Ŀհ׷��ţ�
 * ��������'\r'��'\n'��'\r\n'��' '��'\t'��'\f'��
 */
void skipBlank(FILE* fp) {
    int ch;
    
    if(fp == NULL) {
        return;
    }
    
    while((ch = getc(fp)) != EOF) {
        // �������ANSI��֮��ķ��ţ����纺�֣���ֱ������
        if(ch >= 0 && ch <= 127) {
            // ���������ANSI�벻�ǿհף�����'\r'��'\n'��'\r\n'��' '��'\t'��'\f'�����ʾ�÷���"�ɶ�"
            if(ch != '\r' && ch != '\n' && ch != ' ' && ch != '\t' && ch != '\f') {
                // ��"�ɶ�"���ŷ������������Դ�������������ȡ��
                ungetc(ch, fp);
                break;  // ��������ѭ���ˣ���Ϊ�Ѿ��ҵ���"�ɶ�"����
            }
        }
    }
}
