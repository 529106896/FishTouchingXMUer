/*=======================
 * �洢����������ϰ��8.16
 ========================*/

#include "MemoryManager.h"

// ��ʼ��һƬ���õĴ洢
void InitSpace(Space* space) {
    void* base;    // �ڴ���ʼ��ַ
    Record* record; // ��һ����¼
    
    // ��ʼ����MAXSIZE���ֽڵ��ڴ棬������
    base = calloc(MAXSIZE, BYTE);
    space->base = base;
    
    // ��ʼ���ڴ�ʹ�ü�¼
    InitList(&(space->recordList));
    
    record = (Record*) malloc(sizeof(Record));
    
    record->addr = 0;
    record->size = MAXSIZE;
    record->tag = 0;
    record->pre = -1;
    record->next = -1;
    record->oldAddr = -1;
    
    // �����һ���ڴ�ʹ�ü�¼(����)
    ListInsert(&(space->recordList), 1, record);
    
    // ��һ�����õĿ��п�
    space->cur = 1;
    
    // ��ʼ����ַ����
    InitList(&(space->ptrList));
}

// �����СΪn���ڴ棬������ָ����ڴ�������ַ
int* AllocMemory(Space* space, int n) {
    int found;  // ����Ƿ��ҵ����õĿ��п�
    int i, cur, len;
    Record* record;
    Record* newRecord;
    int* ptr;
    
    // ���µ�ǰ�Ŀ��п��¼λ��
    i = cur = space->cur;
    found = 0;
    
    // ��ȡ��ǰ�ڴ��¼��ĳ���
    len = ListLength(space->recordList);
    
    // ���ҿ��õĿ����ڴ��
    while(1) {
        // ��ȡ��ǰ����ڴ�ʹ����Ϣ
        GetElem(space->recordList, i, (ElemType*) &record);
        
        // ����ռ�ÿ飬�Ѿ�������������Ŀ��п�
        if(record->tag == 1 || record->size < n) {
            // ǰ������һ����¼��ע����ѭ����
            i = (i + 1) % len == 0 ? len : (i + 1) % len;
            if(i == cur) {
                break;  // ����ֻص��˱�����������㣬˵��û���ҵ����ʵĿ��п�
            }
            continue;
        }
        
        // �ҵ����ʵĿ��п�
        found = 1;
        break;
    }
    
    // û�ҵ����ʵĿ��п�
    if(found == 0) {
        return NULL;
    }
    
    // ���ݲΧ�ڣ����������
    if(record->size - e <= n) {
        record->tag = 1;                    // ת��Ϊռ��״̬
        
        // ������Ҫ��ֿ��п�
    } else {
        // �½�һ�����м�¼
        newRecord = (Record*) malloc(sizeof(Record));
        newRecord->addr = record->addr + n;
        newRecord->size = record->size - n;
        newRecord->tag = 0;
        newRecord->pre = -1;
        newRecord->next = -1;
        newRecord->oldAddr = -1;
        
        // �����µĿ��м�¼
        ListInsert(&(space->recordList), len + 1, newRecord);
        len += 1;    // ��������һ
        
        // ��ǰ�Ŀ��м�¼תΪʹ�ü�¼
        record->size = n;
        record->tag = 1;
    }
    
    // ����һ�������ַ
    ptr = (int*) malloc(sizeof(int));
    ListInsert(&(space->ptrList), ListLength(space->ptrList)+1, ptr);
    *ptr = record->addr;
    
    // ���α�curָ����һ�����м�¼
    while(1) {
        // ��ȡ��ǰ����ڴ�ʹ����Ϣ
        GetElem(space->recordList, i, (ElemType*) &record);
        
        // ����ռ�ÿ�
        if(record->tag == 1) {
            // ǰ������һ����¼��ע����ѭ����
            i = (i + 1) % len == 0 ? len : (i + 1) % len;
            if(i == cur) {
                break;  // ����ֻص��˱�����������㣬˵��û���ҵ����ʵĿ��п�
            }
            continue;
        }
        
        // �洢��һ�����ÿ��п��λ��(������û�ҵ����洢)
        space->cur = i;
        
        break;
    }
    
    return ptr;  // ���ؿ����ڴ�������ַ
}

// �ͷ������ַp�����ڴ�
void FreeMemory(Space* space, int* p) {
    int i, len;
    Record* record;
    
    // ��ȡ��ǰ�ڴ��¼�ĳ���
    len = ListLength(space->recordList);
    
    // ���������ڴ��¼�����Ҵ��ͷ��ڴ����ڵļ�¼
    for(i = 1; i <= len; i++) {
        // ��ȡ��ǰ����ڴ�ʹ����Ϣ
        GetElem(space->recordList, i, (ElemType*) &record);
        
        // ������ƥ��ļ�¼
        if(*p != record->addr) {
            continue;
        }
        
        // ����ü�¼�������ǿ��У���ֱ�ӷ���
        if(record->tag == 0) {
            return;
        }
        
        // ��ʹ�ü�¼����Ϊ����
        record->tag = 0;
        
        // ���α�ָ��ոջ��յ��ڴ�
        space->cur = i;
        
        // ���õ�ַ��Ӧ���ڴ洦������Ĩ��(���Ǹ���ѡ����)
        memset(getPtr(*space, p), 0, record->size*BYTE);
        
        // ���Ҹ������ַ�ڵ�ַ���е�λ��
        for(i = 0; i < space->ptrList.length; i++) {
            if(space->ptrList.elem[i] == p) {
                break;
            }
        }
        
        // ɾ���������ַ���������������ݸ���ǰ������ݣ�
        memmove(&(space->ptrList.elem[i]), &(space->ptrList.elem[i + 1]), (space->ptrList.length - i - 1) * sizeof(void*));
        
        space->ptrList.length -= 1;
        
        return;
    }
    
}

// �������ַaddrת��Ϊ�ײ����ʵ��ַ
void* getPtr(Space space, const int* addr) {
    if(addr == NULL) {
        return NULL;
    } else {
        if(*addr < 0 || *addr > MAXSIZE) {
            return NULL;
        }
        
		// VS��������Ҫָ��ָ�����ͣ������趨Ϊһ���ֽ�
        return (char*)(space.base) + (*addr * BYTE);
    }
}

// ��ӡ�ڴ沼�֣���ʾ��ʽΪ���׵�ַ ���С ��־�� | ǰ�� ��� | ����
void PrintMemoryLayout(Space space) {
    Record* record;
    int i, len;
    char* data;
    
    len = ListLength(space.recordList);
    
    for(i = 0; i < len; i++) {
        record = space.recordList.elem[i];
        
        printf("%2d ", record->addr);
        printf("%2d ", record->size);
        printf("%1d ", record->tag);
        
        // ���������ǰ���ͺ����Ϣ
        printf(" | ");
        
        if(record->tag == 0) {
            printf("       ��\n");
            continue;
        }
        
        if(record->pre == -1) {
            printf("   ");
        } else {
            printf("%2d ", record->pre);
        }
        
        if(record->next == -1) {
            printf("   ");
        } else {
            printf("%2d ", record->next);
        }
    
        // ������������ڴ��е����ݣ�����ֻ�����һ���ֽ��д洢�����ݣ�ֻ�����ڲ���
        printf(" �� ");
        
        data = (char*)calloc(1, sizeof(char));
        memmove(data, getPtr(space, &(record->addr)), 1);
        printf("%d", *data);
        
        printf("\n");
    }
    
    printf("\n");
}
