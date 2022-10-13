#include <stdio.h>
#include "Status.h"             //**▲01 绪论**//
#include "ALGraph.h"            //**▲07 图**//
#include "TopologicalSorting.h" //**▲07 图**//

/*
 * 对无回路的有向图中的顶点适当地编号，使其邻接矩阵为下三角形且主对角线为全零。
 * 调整成功后，输出新旧编号对照表。
 *
 * 注：本质上求拓扑排序的逆序列
 */
void Algo_7_26(ALGraph G);

/*
 * 以图形化形式输出调整结点顺序后的图结构
 *
 * 注：在图/网中，使用"-"来表示两顶点不直接连通
 */
static void PrintGraph_7_26(ALGraph G, int topo[MAX_VERTEX_NUM]);


int main(int argc, char* argv[]) {
    ALGraph G;
    
    printf("████████ 创建并输出图...\n");
    {
        char* path[4];
        
        path[0] = "TestData_DG.txt";
        path[1] = "";
        path[2] = "";
        path[3] = "";
        
        CreateGraph(&G, path);
        PrintGraph(G);
        printf("\n");
    }
    
    printf("████████ 输出有向图的顶点顺序...\n");
    {
        Algo_7_26(G);
        printf("\n");
    }
    
    return 0;
}


/*
 * 对无回路的有向图中的顶点适当地编号，使其邻接矩阵为下三角形且主对角线为全零。
 * 调整成功后，输出新旧编号对照表。
 *
 * 注：本质上求拓扑排序的逆序列
 */
void Algo_7_26(ALGraph G) {
    int i;
    int tmp;
    int topo[MAX_VERTEX_NUM];
    
    if(TopologicalSort(G, topo) == ERROR) {
        printf("给定的有向图存在回路，无法获取其拓扑序列...\n");
        return;
    }
    
    printf("调整前：");
    for(i = 0; i < G.vexnum; i++) {
        printf("%c ", G.vertices[i].data);
    }
    printf("\n");
    
    // 对得到的拓扑序列做一个简单的逆置
    for(i = 0; i < G.vexnum / 2; i++) {
        tmp = topo[i];
        topo[i] = topo[G.vexnum - i - 1];
        topo[G.vexnum - i - 1] = tmp;
    }
    
    printf("调整后：");
    for(i = 0; i < G.vexnum; i++) {
        printf("%c ", G.vertices[topo[i]].data);
    }
    printf("\n\n");
    
    printf("████████ 根据调整后的顶点次序，打印其存储结构(此步骤可选)...\n");
    PrintGraph_7_26(G, topo);
}

/*
 * 以图形化形式输出调整结点顺序后的图结构
 *
 * 注：在图/网中，使用"-"来表示两顶点不直接连通
 */
static void PrintGraph_7_26(ALGraph G, int topo[MAX_VERTEX_NUM]) {
    int i, j;
    int pos[MAX_VERTEX_NUM];
    int adjs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
    ArcNode* p;
    
    // 记录各顶点在拓扑序列中的索引
    for(i = 0; i < G.vexnum; i++) {
        pos[topo[i]] = i;
    }
    
    // 初始化
    for(i = 0; i < G.vexnum; i++) {
        for(j = 0; j < G.vexnum; j++) {
            adjs[i][j] = 0;
        }
    }
    
    // 遍历有向图各弧之间的关系
    for(i = 0; i < G.vexnum; i++) {
        p = G.vertices[i].firstarc;
        
        while(p != NULL) {
            adjs[pos[i]][pos[p->adjvex]] = 1;
            p = p->nextarc;
        }
    }
    
    
    printf("  ");
    for(i = 0; i < G.vexnum; i++) {
        printf("  %c", G.vertices[topo[i]].data);
    }
    printf("\n");
    
    for(i = 0; i < G.vexnum; i++) {
        printf("%c ", G.vertices[topo[i]].data);
        
        for(j = 0; j < G.vexnum; j++) {
            if(adjs[i][j] == 0) {
                printf("  -");
            } else {
                printf("%3d", adjs[i][j]);
            }
        }
        
        printf("\n");
    }
}
