#include<stdio.h>
#include<stdlib.h>



int map[32][32];//��Ҫ��ͼ�� 1~9��Ӧ���֣� 10yuanlei�� 11ը����
int mask[32][32] = { -3,0,-2 };//��ͼ����, 0��ʾ -1δ֪�� -2��ǣ� -3�ʺ�

void duires(int n_x, int n_y, int size);//ѭ���ж϶���
int poi_sum(int x, int y, int size);//̽����Χ������

void do_null(int x, int y);
void not_null(int x, int y, int nums);

int main()
{
	int x, y, z;
	x = 1, y = 1, z = 1;
	duires(x, y, 20);
	return 0;
}

int poi_sum(int x, int y, int size)
{
	int sum;
	int nx, ny;
	int lei;
	lei = 10;
	sum = 0;

	nx = x - 1, ny = y - 1;
	if (nx >= 0 && ny >= 0 && nx < size && ny < size)
	{
		if (map[ny][nx] == lei)
		{
			sum++;
		}
	}
	nx = x - 1, ny = y;
	if (nx >= 0 && ny >= 0 && nx < size && ny < size)
	{
		if (map[ny][nx] == lei)
		{
			sum++;
		}
	}
	nx = x - 1, ny = y + 1;
	if (nx >= 0 && ny >= 0 && nx < size && ny < size)
	{
		if (map[ny][nx] == lei)
		{
			sum++;
		}
	}
	nx = x, ny = y + 1;
	if (nx >= 0 && ny >= 0 && nx < size && ny < size)
	{
		if (map[ny][nx] == lei)
		{
			sum++;
		}
	}
	nx = x + 1, ny = y + 1;
	if (nx >= 0 && ny >= 0 && nx < size && ny < size)
	{
		if (map[ny][nx] == lei)
		{
			sum++;
		}
	}
	nx = x + 1, ny = y;
	if (nx >= 0 && ny >= 0 && nx < size && ny < size)
	{
		if (map[ny][nx] == lei)
		{
			sum++;
		}
	}
	nx = x + 1, ny = y - 1;
	if (nx >= 0 && ny >= 0 && nx < size && ny < size)
	{
		if (map[ny][nx] == lei)
		{
			sum++;
		}
	}
	nx = x, ny = y - 1;
	if (nx >= 0 && ny >= 0 && nx < size && ny < size)
	{
		if (map[ny][nx] == lei)
		{
			sum++;
		}
	}

	return sum;
}

void do_null(int x, int y)//�����յ㴦��
{
	return;
}

void not_null(int x, int y, int nums)//�����ǿմ���
{
	return;
}

void duires(int n_x, int n_y, int size)
{
	typedef struct dui {
		int x;
		int y;
		struct dui * ne;
	}*duis;

	duis head, tail, tem;
	int leis, tx, ty;

	//init
	tail = (duis)malloc(sizeof(dui));
	head = (duis)malloc(sizeof(dui));
	
	head->x = n_x;
	head->y = n_y;
	head->ne = tail;
	
	

	leis = poi_sum(n_x, n_y, size);
	if (leis > 0)
	{
		free(tail);
		free(head);
		not_null(n_x, n_y, leis);
		return;
	}

	while (head != tail)
	{
		n_x = head->x;
		n_y = head->y;
		leis = poi_sum(n_x, n_y, size);
		if (leis > 0)
		{
			not_null(n_x, n_y, leis);
		}
		else
		{
			do_null(n_x, n_y);



			tx = n_x - 1;
			ty = n_y - 1;
			if (tx > 0 && ty >= 0 && tx < size &&ty < size)
			{
				tail->x = tx;
				tail->y = ty;
				tem = (duis)malloc(sizeof(dui));
				tail->ne = tem;
				tail = tem;
			}

			tx = n_x - 1;
			ty = n_y;
			if (tx > 0 && ty >= 0 && tx < size &&ty < size)
			{
				tail->x = tx;
				tail->y = ty;
				tem = (duis)malloc(sizeof(dui));
				tail->ne = tem;
				tail = tem;
			}

			tx = n_x - 1;
			ty = n_y + 1;
			if (tx > 0 && ty >= 0 && tx < size &&ty < size)
			{
				tail->x = tx;
				tail->y = ty;
				tem = (duis)malloc(sizeof(dui));
				tail->ne = tem;
				tail = tem;
			}

			tx = n_x;
			ty = n_y + 1;
			if (tx > 0 && ty >= 0 && tx < size &&ty < size)
			{
				tail->x = tx;
				tail->y = ty;
				tem = (duis)malloc(sizeof(dui));
				tail->ne = tem;
				tail = tem;
			}

			tx = n_x + 1;
			ty = n_y + 1;
			if (tx > 0 && ty >= 0 && tx < size &&ty < size)
			{
				tail->x = tx;
				tail->y = ty;
				tem = (duis)malloc(sizeof(dui));
				tail->ne = tem;
				tail = tem;
			}

			tx = n_x + 1;
			ty = n_y;
			if (tx > 0 && ty >= 0 && tx < size &&ty < size)
			{
				tail->x = tx;
				tail->y = ty;
				tem = (duis)malloc(sizeof(dui));
				tail->ne = tem;
				tail = tem;
			}

			tx = n_x + 1;
			ty = n_y - 1;
			if (tx > 0 && ty >= 0 && tx < size &&ty < size)
			{
				tail->x = tx;
				tail->y = ty;
				tem = (duis)malloc(sizeof(dui));
				tail->ne = tem;
				tail = tem;
			}

			tx = n_x;
			ty = n_y - 1;
			if (tx > 0 && ty >= 0 && tx < size &&ty < size)
			{
				tail->x = tx;
				tail->y = ty;
				tem = (duis)malloc(sizeof(dui));
				tail->ne = tem;
				tail = tem;
			}


		}
		tem = head;
		head = head->ne;
		free(tem);
	}


	//end
	free(tail);
}