/*=====================
 * ͼ���ڽӶ��ر�洢��ʾ
 ======================*/

#include "AMLGraph.h"

// ¼�����ݵ�Դ�ļ���fpΪnullʱ��˵����Ҫ�ӿ���̨¼��
FILE* fp = NULL;

/*
 * IncInfoָʾ��ͼ�ı����Ƿ���ڸ�����Ϣ��
 * �����ֵ��Ϊ0�����ʾ�޸�����Ϣ�����򣬱�ʾ���ڸ�����Ϣ��
 */
Boolean IncInfo = FALSE;

// ���ʱ�־���飬��¼���ʹ��Ķ���
Boolean visited[MAX_VERTEX_NUM];

// ��������
Status (* VisitFunc)(VertexType e);


/*
 * ����
 *
 *����ע��
 *
 * �̲���Ĭ�ϴӿ���̨��ȡ���ݡ�
 * ����Ϊ�˷�����ԣ�����ÿ�����ж��ֶ��������ݣ�
 * �������ѡ���Ԥ����ļ�path�ж�ȡ�������ݡ�
 *
 * �����Ҫ�ӿ���̨��ȡ���ݣ���pathΪNULL����path[kind]Ϊ""��
 * �����Ҫ���ļ��ж�ȡ���ݣ�����Ҫ��path����д�ļ�����Ϣ��
 */
Status CreateGraph(AMLGraph* G, char* path[]) {
    int readFromConsole;    // �Ƿ�ӿ���̨��ȡ����
    int kind;
    Status flag;
    
    printf("������ͼ������(2-����ͼ �� 3-������)��");
    scanf("%d", &kind);
    
    // ���Ͳ��Ϲ�(ֻ���������ͼ/��)
    if(kind < 2 || kind > 3) {
        return ERROR;
    }
    
    // ���û���ļ�·����Ϣ����ӿ���̨��ȡ����
    readFromConsole = (path == NULL) || strcmp(path[kind], "") == 0;
    
    // ��Ҫ���ļ���ȡ
    if(readFromConsole) {
        // ע��C++�ļ��У�����תö����Ҫǿ��ת��
        (*G).kind = GraphKind(kind);   // ��¼ͼ/��������
    } else {
        // ���ļ���׼����ȡ��������
        fp = fopen(path[kind], "r");
        if(fp == NULL) {
            return ERROR;
        }
        
        // ¼��ͼ������
        ReadData(fp, "%d", &((*G).kind));
    }
    
    // �����������ͼ����������һ��
    switch((*G).kind) {
        case UDG:
            flag = CreateUDG(G);
            break;
        case UDN:
            flag = CreateUDN(G);
            break;
        default:
            flag = ERROR;
            break;
    }
    
    if(fp != NULL) {
        fclose(fp);
        fp = NULL;
    }
    
    return flag;
}

/*
 * ��������ͼ
 */
static Status CreateUDG(AMLGraph* G) {
    int i, k;
    int vexnum, arcnum;
    VertexType v1, v2;
    InfoType* info = NULL;
    
    (*G).vexnum = (*G).edgenum = 0;
    
    if(fp == NULL) {
        printf("����������ͼ�Ķ�������");
        scanf("%d", &vexnum);
        printf("����������ͼ�ı�����");
        scanf("%d", &arcnum);
        printf("������ͼ�ı����Ƿ��������������Ϣ(0-��������1-����)��");
        scanf("%d", &IncInfo);
    
        // ¼�붥�㼯
        printf("��¼�� %d �����㣬��ͬ����֮���ÿո������", vexnum);
        for(i = 0; i < vexnum; i++) {
            // �����հף�Ѱ����һ��"�ɶ�"����
            skipBlank(stdin);
            scanf("%c", &((*G).adjmulist[i].data));
            (*G).adjmulist[i].firstedge = NULL;
            (*G).vexnum++;
        }
    } else {
        ReadData(fp, "%d", &vexnum); // ¼�붥����
        ReadData(fp, "%d", &arcnum); // ¼�����
        ReadData(fp, "%d", &IncInfo);// �жϱ����Ƿ����������Ϣ
        
        // ¼�붥�㼯
        for(i = 0; i < vexnum; i++) {
            // �����հף�Ѱ����һ��"�ɶ�"����
            skipBlank(fp);
            ReadData(fp, "%c", &((*G).adjmulist[i].data));
            (*G).adjmulist[i].firstedge = NULL;
            (*G).vexnum++;
        }
    }
    
    // ���ڿ���̨¼����Ϣʱ�������ʾ
    if(fp == NULL && arcnum != 0) {
        printf("��Ϊ����ͼ����¼�� %d ���ߵ���Ϣ������֮���ÿո������\n", arcnum);
    }
    
    // ¼��ߵ���Ϣ
    for(k = 0; k < arcnum; k++) {
        if(fp == NULL) {
            printf("�� %2d ���ߣ�", k + 1);
            skipBlank(stdin);   // �����հף�Ѱ����һ���ɶ�����
            scanf("%c", &v1);
            skipBlank(stdin);   // �����հף�Ѱ����һ���ɶ�����
            scanf("%c", &v2);
        } else {
            // �����հף�Ѱ����һ���ɶ�����
            skipBlank(fp);
            ReadData(fp, "%c%c", &v1, &v2);
        }
        
        // �����Ҫ¼��ߵ�����������Ϣ
        if(IncInfo) {
            // ���¼�븽����Ϣ
            Input(*G, &info);
        }
        
        // �����<v1, v2>
        InsertArc(G, v1, v2, info);
    }
    
    // ���ļ��ж�ȡ����ʱ�������ʵӦ���ж�һ���Ƿ�������㹻����Ϣ
    return OK;
}

/*
 * ����������
 */
static Status CreateUDN(AMLGraph* G) {
    int i, k;
    int vexnum, arcnum;
    VertexType v1, v2;
    InfoType* info = NULL;
    
    (*G).vexnum = (*G).edgenum = 0;
    
    if(fp == NULL) {
        printf("�������������Ķ�������");
        scanf("%d", &vexnum);
        printf("�������������ı�����");
        scanf("%d", &arcnum);
        printf("���������ı��ϱ����������������Ϣ����Ϊ�˴���Ȩֵ��Ҫ�洢��������Ϣ��...\n");
        IncInfo = 1;
    
        // ¼�붥�㼯
        printf("��¼�� %d �����㣬��ͬ����֮���ÿո������", vexnum);
        for(i = 0; i < vexnum; i++) {
            // �����հף�Ѱ����һ��"�ɶ�"����
            skipBlank(stdin);
            scanf("%c", &((*G).adjmulist[i].data));
            (*G).adjmulist[i].firstedge = NULL;
            (*G).vexnum++;
        }
    } else {
        ReadData(fp, "%d", &vexnum); // ¼�붥����
        ReadData(fp, "%d", &arcnum); // ¼�����
        ReadData(fp, "%d", &IncInfo);// �жϱ����Ƿ����������Ϣ
        IncInfo = 1;    // ǿ�ƽ�Ȩֵ¼�뵽������Ϣ��
        
        // ¼�붥�㼯
        for(i = 0; i < vexnum; i++) {
            // �����հף�Ѱ����һ��"�ɶ�"����
            skipBlank(fp);
            ReadData(fp, "%c", &((*G).adjmulist[i].data));
            (*G).adjmulist[i].firstedge = NULL;
            (*G).vexnum++;
        }
    }
    
    // ���ڿ���̨¼����Ϣʱ�������ʾ
    if(fp == NULL && arcnum != 0) {
        printf("��Ϊ����������¼�� %d ����(��Ȩֵ)����Ϣ�����㼰Ȩֵ֮���ÿո������\n", arcnum);
    }
    
    // ¼��ߵ���Ϣ
    for(k = 0; k < arcnum; k++) {
        if(fp == NULL) {
            printf("�� %2d ���߼���Ȩֵ��", k + 1);
            skipBlank(stdin);   // �����հף�Ѱ����һ���ɶ�����
            scanf("%c", &v1);
            skipBlank(stdin);   // �����հף�Ѱ����һ���ɶ�����
            scanf("%c", &v2);
        } else {
            // �����հף�Ѱ����һ���ɶ�����
            skipBlank(fp);
            ReadData(fp, "%c%c", &v1, &v2);
        }
    
        // �����Ҫ¼��ߵ�����������Ϣ
        if(IncInfo) {
            // ���¼�븽����Ϣ(�˴���Ҫ¼������Ȩֵ)
            Input(*G, &info);
        }
    
        // �����<v1, v2>
        InsertArc(G, v1, v2, info);
    }
    
    // ���ļ��ж�ȡ����ʱ�������ʵӦ���ж�һ���Ƿ�������㹻����Ϣ
    return OK;
}

/*
 * ¼��ߵ���ظ�����Ϣ
 */
static void Input(AMLGraph G, InfoType** info) {
    int weight;
    
    // ��"��"����������Ҫ¼��Ȩֵ��Ϣ
    if(G.kind == UDN) {
        *info = (InfoType*) malloc(sizeof(InfoType));
        
        if(fp == NULL) {
            scanf("%d", &weight);
        } else {
            ReadData(fp, "%d", &weight);
        }
        
        (*info)->weight = weight;
    }
}

/*
 * ����
 *
 * �ڽӱ�洢��ͼ��Ҫ�ͷ��ڴ档
 */
Status DestroyGraph(AMLGraph* G) {
    int k, other;
    EBox* p, * r;
    
    // �������
    for(k = G->vexnum-1; k >=0; k--) {
        p = NULL;
        r = G->adjmulist[k].firstedge;
        
        // ɾ��ivex��Ϊk�ıߣ�����jvex��Ϊk�ı�
        while(r != NULL) {
            if(r->ivex == k) {
                other = r->jvex;
            } else if(r->jvex==k) {
                other = r->ivex;
            } else {
                // ��������
            }
    
            // ��ʱ����������
            if(other<k) {
                p = r;
                
                if(r->ivex == k) {
                    r = r->ilink;
                } else if(r->jvex==k) {
                    r = r->jlink;
                } else {
                    // ��������
                }
                
                // ɾ��������
            } else {
                if(p==NULL) {
                    if(r->ivex == k) {
                        G->adjmulist[k].firstedge = r->ilink;
                    } else if(r->jvex==k) {
                        G->adjmulist[k].firstedge = r->jlink;
                    } else {
                        // ��������
                    }
                    
                    free(r);
                    r = G->adjmulist[k].firstedge;
                } else {
                    if(p->ivex==k) {
                        if(r->ivex == k) {
                            p->ilink = r->ilink;
                        } else if(r->jvex==k) {
                            p->ilink = r->jlink;
                        } else {
                            // ��������
                        }
    
                        free(r);
                        r = p->ilink;
                    } else if(p->jvex==k) {
                        if(r->ivex == k) {
                            p->jlink = r->ilink;
                        } else if(r->jvex==k) {
                            p->jlink = r->jlink;
                        } else {
                            // ��������
                        }
    
                        free(r);
                        r = p->jlink;
                    } else {
                        // ��������
                    }
                }
            }
        }
    }
    
    (*G).vexnum = 0;
    (*G).edgenum = 0;
    IncInfo = 0;
    
    return OK;
}

/*
 * ����
 *
 * ���ض���u��ͼ/���е�λ��
 */
int LocateVex(AMLGraph G, VertexType u) {
    int i;
    
    for(i = 0; i < G.vexnum; i++) {
        if(G.adjmulist[i].data == u) {
            return i;
        }
    }
    
    return -1;
}

/*
 * ȡֵ
 *
 * ��������v���Ķ���ֵ
 */
VertexType GetVex(AMLGraph G, int v) {
    if(v < 0 || v >= G.vexnum) {
        return '\0';    // ָ���Ķ��㲻����
    }
    
    return G.adjmulist[v].data;
}

/*
 * ��ֵ
 *
 * ������v��ֵΪvalue
 */
Status PutVex(AMLGraph* G, VertexType v, VertexType value) {
    int k;
    
    // ������Ҫ�жϸö����Ƿ����
    k = LocateVex((*G), v);
    if(k == -1) {
        return ERROR;    // ָ���Ķ��㲻����
    }
    
    // �滻ͷ���
    (*G).adjmulist[k].data = value;
    
    /* �����е�Ԫ�ش洢���Ƕ����λ�ã�������������������滻Ŀ��ֵ */
    
    return OK;
}

/*
 * �׸��ڽӵ�
 *
 * ���ض���v���׸��ڽӵ�
 */
int FirstAdjVex(AMLGraph G, VertexType v) {
    int k;
    EBox* r;
    
    // ������Ҫ�жϸö����Ƿ����
    k = LocateVex(G, v);
    if(k == -1) {
        return -1;    // ָ���Ķ��㲻����
    }
    
    r = G.adjmulist[k].firstedge;
    if(r == NULL) {
        return -1;
    } else {
        if(r->ivex == k) {
            return r->jvex;
        } else if(r->jvex==k) {
            return r->ivex;
        } else {
            return -1;  // ��������
        }
    }
}

/*
 * ��һ���ڽӵ�
 *
 * ���ض���v��(�����w��)��һ���ڽӵ�
 */
int NextAdjVex(AMLGraph G, VertexType v, VertexType w) {
    int kv, kw;
    EBox* r;
    
    // ������Ҫ�жϸö����Ƿ����
    kv = LocateVex(G, v);
    if(kv == -1) {
        return -1;    // ָ���Ķ��㲻����
    }
    
    // ������Ҫ�жϸö����Ƿ����
    kw = LocateVex(G, w);
    if(kw == -1) {
        return -1;    // ָ���Ķ��㲻����
    }
    
    r = G.adjmulist[kv].firstedge;
    if(r == NULL) {
        return -1;    // ����Ϊ��
    }
    
    // �������в���w
    while(r != NULL) {
        if(r->ivex == kv && r->jvex < kw) {
            r = r->ilink;
        } else if(r->jvex == kv && r->ivex < kw) {
            r = r->jlink;
        } else {
            break;
        }
    }
    
    // ���û�ҵ�w
    if(r == NULL) {
        return -1;
    }
    
    // ����ҵ���w������w����û�б�Ķ��㣬��ôҲ�޷������ڽӵ�
    if(r->ivex == kv && r->jvex == kw && r->ilink!=NULL) {
        r = r->ilink;
    } else if(r->jvex == kv && r->ivex == kw && r->jlink!=NULL) {
        r = r->jlink;
    } else {
        return -1;
    }
    
    // �����ڵı��л�ȡ�����ڶ���
    if(r->ivex==kv) {
        return r->jvex;
    } else if(r->jvex==kv) {
        return r->ivex;
    } else {
        return -1;  // ��������
    }
}

/*
 * ���붥��
 *
 * ��ָ���Ķ���v׷�ӵ����㼯�У�δ�����ö�������������Ĺ�ϵ
 */
Status InsertVex(AMLGraph* G, VertexType v) {
    int k;
    
    // ����������
    if((*G).vexnum == MAX_VERTEX_NUM) {
        return ERROR;
    }
    
    // ������Ҫ�жϸö����Ƿ����
    k = LocateVex(*G, v);
    if(k >= 0) {
        return ERROR;    // ָ���Ķ������ʱ�������ظ����
    }
    
    G->adjmulist[(*G).vexnum].data = v;
    G->adjmulist[(*G).vexnum].firstedge = NULL;
    
    (*G).vexnum++;
    
    return OK;
}

/*
 * ɾ������
 *
 * �Ӷ��㼯��ɾ��ָ���Ķ���v��ע����Ҫ������صĶ����ϵ
 */
Status DeleteVex(AMLGraph* G, VertexType v) {
    int i, k, other;
    EBox* p;
    EBox* pre, * r;
    
    // ������Ҫ�жϸö����Ƿ����
    k = LocateVex(*G, v);
    if(k == -1) {
        return ERROR;    // ָ���Ķ��㲻����
    }
    
    while((p = G->adjmulist[k].firstedge) != NULL) {
        if(p->ivex == k) {
            G->adjmulist[k].firstedge = p->ilink;
            other = p->jvex;
        } else if(p->jvex == k) {
            G->adjmulist[k].firstedge = p->jlink;
            other = p->ivex;
        } else {
            // û����������
        }
        
        pre = NULL;
        r = G->adjmulist[other].firstedge;
        
        // ���ұ�<other, k>���϶����ҵ�
        while(r != NULL) {
            if(r->ivex == other && r->jvex < k) {
                pre = r;
                r = r->ilink;
            } else if(r->jvex == other && r->ivex < k) {
                pre = r;
                r = r->jlink;
            } else {
                break;
            }
        }
        
        if(r != NULL && r->ivex == other && r->jvex == k) {
            if(pre == NULL) {
                G->adjmulist[other].firstedge = r->ilink;
            } else {
                if(pre->ivex == other) {
                    pre->ilink = r->ilink;
                } else if(pre->jvex == other) {
                    pre->jlink = r->ilink;
                } else {
                    // û����������
                }
            }
        } else if(r != NULL && r->jvex == other && r->ivex == k) {
            if(pre == NULL) {
                G->adjmulist[other].firstedge = r->jlink;
            } else {
                if(pre->ivex == other) {
                    pre->ilink = r->jlink;
                } else if(pre->jvex == other) {
                    pre->jlink = r->jlink;
                } else {
                    // û����������
                }
            }
        } else {
            // �������ˣ���Ϊ�϶����ҵ�
        }
        
        free(p);
        
        (*G).edgenum--;  // ������һ
    }
    
    // �±곬��k�Ķ��㣬��Ҫ�ݼ����±�
    for(i = k + 1; i < (*G).vexnum; i++) {
        r = G->adjmulist[i].firstedge;
    
        while(r!=NULL){
            if(r->ivex==i) {
                r->ivex--;
                r = r->ilink;
            } else if(r->jvex==i) {
                r->jvex--;
                r = r->jlink;
            } else {
                // ��������
            }
        }
    }
    
    // ���㼯ǰ��
    for(i = k + 1; i < (*G).vexnum; i++) {
        G->adjmulist[i - 1] = G->adjmulist[i];
    }
    
    // �������ݼ�
    (*G).vexnum--;
    
    return OK;
}

/*
 * ����һ���߽��(�����ڲ�ʹ��)
 */
static EBox* newEBoxPtr(VisitIf mark, int ivex, int jvex, EBox* ilink, EBox* jlink, InfoType* info) {
    EBox* p = (EBox*) malloc(sizeof(EBox));
    if(!p) {
        exit(OVERFLOW);
    }
    
    p->mark = mark;
    
    p->ivex = ivex;
    p->jvex = jvex;
    
    p->ilink = ilink;
    p->jlink = jlink;
    
    p->info = info;
    
    return p;
}

/*
 * �����<v, w>
 *
 * ��ǰͼ/��������ģ�����������Ľṹ��ʹ�ò���һ����ʱֻ��Ҫ����һ�Զ����ϵ���ߵ�������Ȼ��һ��
 * ����ͼ/����˵�������ڿɱ�������г��ߵĸ�����Ϣ��
 *
 * ע���˴����յĲ�����MGraph��Щ��һ�������ĸ�����Ϣ�а����˸����ߵ�Ȩֵ��
 */
Status InsertArc(AMLGraph* G, VertexType v, VertexType w, ...) {
    int tail, head, k;
    EBox* p;
    EBox* pre;
    EBox* r;
    Boolean overlay = FALSE;   // �Ƿ�Ϊ�������
    InfoType* info = NULL;     // �ߵĸ�����Ϣ
    va_list ap;
    
    tail = LocateVex(*G, v); // ��ȡ����v�ڶ��㼯�е�λ��
    if(tail == -1) {
        return ERROR;  // ָ���Ķ��㲻����
    }
    
    head = LocateVex(*G, w); // ��ȡ����w�ڶ��㼯�е�λ��
    if(head == -1) {
        return ERROR;  // ָ���Ķ��㲻����
    }
    
    // �ܾ���
    if(tail == head) {
        return ERROR;
    }
    
    // ������ϴ��ڸ�����Ϣ
    if(IncInfo) {
        va_start(ap, w);                // ��w���ѯ�׸��ɱ����
        info = va_arg(ap, InfoType*);   // ��ȡ������Ϣ
        va_end(ap);
    }
    
    /* ����������Ҫ���Һ��ʵĲ���λ�� */
    
    pre = NULL;
    r = G->adjmulist[tail].firstedge;
    
    while(r != NULL) {
        if(r->ivex == tail && r->jvex < head) {
            pre = r;
            r = r->ilink;
        } else if(r->jvex == tail && r->ivex < head) {
            pre = r;
            r = r->jlink;
        } else {
            break;
        }
    }
    
    if(r != NULL && r->ivex == tail && r->jvex == head) {
        r->info = info; // ���øý��
        overlay = TRUE; // �����˸���
    } else if(r != NULL && r->jvex == tail && r->ivex == head) {
        r->info = info; // ���øý��
        overlay = TRUE; // �����˸���
    } else {
        p = newEBoxPtr(unvisit, tail, head, r, NULL, info);
        
        if(pre == NULL) {
            G->adjmulist[tail].firstedge = p;
        } else {
            if(pre->ivex == tail) {
                pre->ilink = p;
            } else if(pre->jvex == tail) {
                pre->jlink = p;
            } else {
                // û����������
            }
        }
    }
    
    if(!overlay) {
        pre = NULL;
        r = G->adjmulist[head].firstedge;
        
        while(r != NULL) {
            if(r->ivex == head && r->jvex < tail) {
                pre = r;
                r = r->ilink;
            } else if(r->jvex == head && r->ivex < tail) {
                pre = r;
                r = r->jlink;
            } else {
                break;
            }
        }
        
        p->jlink = r;
        
        if(pre == NULL) {
            G->adjmulist[head].firstedge = p;
        } else {
            if(pre->ivex == head) {
                pre->ilink = p;
            } else if(pre->jvex == head) {
                pre->jlink = p;
            } else {
                // û����������
            }
        }
    }
    
    (*G).edgenum++;  // ������һ
    
    return OK;
}

/*
 * ɾ����<v, w>
 */
Status DeleteArc(AMLGraph* G, VertexType v, VertexType w) {
    int tail, head;
    EBox* r;
    EBox* pre;
    
    tail = LocateVex(*G, v);
    if(tail == -1) {
        return ERROR;    // ָ���Ķ��㲻����
    }
    
    head = LocateVex(*G, w);
    if(head == -1) {
        return ERROR;    // ָ���Ķ��㲻����
    }
    
    pre = NULL;
    r = G->adjmulist[tail].firstedge;
    
    while(r != NULL) {
        if(r->ivex == tail && r->jvex < head) {
            pre = r;
            r = r->ilink;
        } else if(r->jvex == tail && r->ivex < head) {
            pre = r;
            r = r->jlink;
        } else {
            break;
        }
    }
    
    if(r != NULL && r->ivex == tail && r->jvex == head) {
        if(pre == NULL) {
            G->adjmulist[tail].firstedge = r->ilink;
        } else {
            if(pre->ivex == tail) {
                pre->ilink = r->ilink;
            } else if(pre->jvex == tail) {
                pre->jlink = r->ilink;
            } else {
                // û����������
            }
        }
    } else if(r != NULL && r->jvex == tail && r->ivex == head) {
        if(pre == NULL) {
            G->adjmulist[tail].firstedge = r->jlink;
        } else {
            if(pre->ivex == tail) {
                pre->ilink = r->jlink;
            } else if(pre->jvex == tail) {
                pre->jlink = r->jlink;
            } else {
                // û����������
            }
        }
    } else {
        return ERROR;   // δ�ҵ�
    }
    
    
    pre = NULL;
    r = G->adjmulist[head].firstedge;
    
    while(r != NULL) {
        if(r->ivex == head && r->jvex < tail) {
            pre = r;
            r = r->ilink;
        } else if(r->jvex == head && r->ivex < tail) {
            pre = r;
            r = r->jlink;
        } else {
            break;
        }
    }
    
    if(r != NULL && r->ivex == head && r->jvex == tail) {
        if(pre == NULL) {
            G->adjmulist[head].firstedge = r->ilink;
        } else {
            if(pre->ivex == head) {
                pre->ilink = r->ilink;
            } else if(pre->jvex == head) {
                pre->jlink = r->ilink;
            } else {
                // û����������
            }
        }
    } else if(r != NULL && r->jvex == head && r->ivex == tail) {
        if(pre == NULL) {
            G->adjmulist[head].firstedge = r->jlink;
        } else {
            if(pre->ivex == head) {
                pre->ilink = r->jlink;
            } else if(pre->jvex == head) {
                pre->jlink = r->jlink;
            } else {
                // û����������
            }
        }
    } else {
        // �������ˣ���Ϊǰ���ҵ��ˣ��˴��϶�Ҳ���ҵ�
    }
    
    free(r); // �ͷ��ڴ�
    
    (*G).edgenum--;  // ������һ
    
    return OK;
}

/*
 * ������ȱ���(�˴������ݹ�ʵ��)
 */
void DFSTraverse(AMLGraph G, Status(Visit)(VertexType)) {
    int v;
    
    // ʹ��ȫ�ֱ���VisitFunc��ʹ��DFS�������ú���ָ�����
    VisitFunc = Visit;
    
    // ���ʱ�־�����ʼ��
    for(v = 0; v < G.vexnum; v++) {
        visited[v] = FALSE;
    }
    
    // �˴���Ҫ������ԭ���ǲ����ܱ�֤���ж��㶼��������һ��
    for(v = 0; v < G.vexnum; v++) {
        if(!visited[v]) {
            DFS(G, v);  // ����δ���ʵĶ������DFS
        }
    }
}

/*
 * ������ȱ������ĺ���
 */
static void DFS(AMLGraph G, int v) {
    int w;
    
    // �ӵ�v����������ݹ��������ȱ���ͼG
    visited[v] = TRUE;
    
    // ���ʵ�v������
    VisitFunc(G.adjmulist[v].data);
    
    for(w = FirstAdjVex(G, G.adjmulist[v].data);
        w >= 0;
        w = NextAdjVex(G, G.adjmulist[v].data, G.adjmulist[w].data)) {
        if(!visited[w]) {
            DFS(G, w);  // ����δ���ʵĶ������DFS
        }
    }
}

/*
 * ������ȱ���(�˴���������ʵ��)
 */
void BFSTraverse(AMLGraph G, Status(Visit)(VertexType)) {
    int v, w;
    LinkQueue Q;
    QElemType u;
    
    // ��ʼ��Ϊδ����
    for(v = 0; v < G.vexnum; v++) {
        visited[v] = FALSE;
    }
    
    // �ÿո�������
    InitQueue(&Q);
    
    for(v = 0; v < G.vexnum; v++) {
        // ����ö����ѷ��ʹ�����ֱ�Ӻ���
        if(visited[v]) {
            continue;
        }
        
        // ��Ǹö����ѷ���
        visited[v] = TRUE;
        
        // ���ʶ���
        Visit(G.adjmulist[v].data);
        
        EnQueue(&Q, v);
        
        while(!QueueEmpty(Q)) {
            DeQueue(&Q, &u);
            
            // �ȼ��з��ʶ���v���ڽӶ��㣬����ٷ����ڽӶ�����ڽӶ���
            for(w = FirstAdjVex(G, G.adjmulist[u].data);
                w >= 0;
                w = NextAdjVex(G, G.adjmulist[u].data, G.adjmulist[w].data)) {
                if(!visited[w]) {
                    visited[w] = TRUE;
                    Visit(G.adjmulist[w].data);
                    EnQueue(&Q, w);
                }
            }
        }
    }
}

/*
 * ��ͼ�λ���ʽ�����ǰ�ṹ
 */
void PrintGraph(AMLGraph G) {
    int i, cur, pos;
    EBox* p;
    
    if(G.vexnum == 0) {
        printf("��ͼ�������ӡ��\n");
        return;
    }
    
    printf("��ǰͼ/������ %2d �����㣬 %2d ����...\n", G.vexnum, G.edgenum);
    
    for(i = 0; i < G.vexnum; i++) {
        printf("%c ===> ", G.adjmulist[i].data);
        
        cur = 0;
        p = G.adjmulist[i].firstedge;
        
        while(p != NULL) {
            if(p->ivex == i) {
                pos = p->jvex;
            } else {
                pos = p->ivex;
            }
            
            if(cur < pos) {
                if(IncInfo == 0) {
                    printf(" ");
                    
                    // ������������丽����Ϣ�л�ȡ��Ȩֵ
                } else {
                    printf("     ");
                }
            } else {
                if(IncInfo == 0) {
                    printf("%c", G.adjmulist[pos].data);
                    
                    // ������������丽����Ϣ�л�ȡ��Ȩֵ
                } else {
                    printf("%c[%2d]", G.adjmulist[pos].data, p->info->weight);
                }
                
                if(p->ivex == i) {
                    p = p->ilink;
                } else {
                    p = p->jlink;
                }
            }
            
            cur++;
            
            if(p != NULL) {
                printf("  ");
            }
        }
        
        printf("\n");
    }
}
