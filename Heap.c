#include"Heap.h"
void HeapInit(Heap* hp, HeapDatatype* a, int n)//�ѵĴ���
{
	assert(a&&hp);
	hp->capacity = n;
	hp->size = n;
	hp->arry = (HeapDatatype*)malloc(sizeof(HeapDatatype)*hp->capacity);
	int i = 0;
	for (i = 0; i < hp->size; i++)
		hp->arry[i] = a[i];
}
void HeapPrint(Heap *hp)//��ӡ��
{
	int i = 0;
	for (i = 0; i < hp->size; i++)
		printf("%d ", hp->arry[i]);
	printf("\n");
}
int HeapEmpty(Heap* hp)
{
	if (hp->size == 0)
		return 0;
	return 1;
}
int HeapSize(Heap* hp)
{
	return hp->size;
}

void Swap(HeapDatatype *a1, HeapDatatype*a2)
{
	HeapDatatype a = *a1;
	*a1 = *a2;
	*a2 = a;
}
void HeapPop(Heap *hp)//��pop
{   //��popָpop�ĶѶ�Ԫ�أ����Ѷ�Ԫ�غ����һ�������н�����size--
	assert(hp);
	Swap(&hp->arry[0], &hp->arry[hp->size - 1]);
	hp->size--;
	BigHeapAdjustDown(hp, 0);//���µ���
}
void HeapSort(Heap *hp)//�����򣬴��
{
	//�������ǽ��Ѷ�Ԫ�غ����һ����������ӡ���һ��Ԫ�أ�
	//����hp->size--���ٵ���Ϊ��ѣ�ѭ��ǰ�����
	int n = hp->size;
	assert(hp);
	while (hp->size > 0)
	{
		Swap(&hp->arry[0], &hp->arry[hp->size - 1]);
		hp->size--;
		BigHeapAdjustDown(hp, 0);//���µ���
	}
	hp->size = n;//��������¸�ֵ����hp->size=0
}
void HeapPush(Heap *hp, HeapDatatype data)//������������
{
	if (hp->size == hp->capacity)//����
	{
		hp->arry = (HeapDatatype*)realloc(hp->arry, sizeof(HeapDatatype)*(hp->capacity) * 2);
		/*assert(hp->arry);*/
		hp->capacity *= 2;
	}
	hp->arry[hp->size] = data;
	hp->size++;
	HeapAdjustUp(hp, hp->size - 1);//���ϵ���
}

void HeapAdjustUp(Heap*hp, int child)//���ϵ���
{   //����ֻ���뺢�ӵ������й�
	int parent = (child - 1) / 2;
	while (child > 0)//������parent>0���жϣ���Ϊparent = (child - 1) / 2;��Զ����0
	{
		if (hp->arry[parent] < hp->arry[child])
		{
			Swap(&hp->arry[parent], &hp->arry[child]);
			child = parent;
			parent = (child - 1) / 2;
		}
		else  //������ױȺ��Ӵ󣬾�û��Ҫ����
			break;
	}
}
void SmallHeapAdjustDown(Heap*hp, int parent, int k)//���µ���С��
{
	int child = parent * 2 + 1;
	while (parent < k)
	{    //������Ӵ����Һ��ӣ���child�����Һ��ӣ���child�����Һ��ӽ�С����
		if (child + 1 < hp->size && hp->arry[child] > hp->arry[child + 1])
			child = child + 1;
		if (child < k &&hp->arry[parent] > hp->arry[child])//�����ں���
		{
			Swap(&hp->arry[parent], &hp->arry[child]);
			// ����֮����Ҫ��childΪ���ٵ���һ�Σ���Ϊ��������ܵ��¸�С�����Һ���
			parent = child;
			child = parent * 2 + 1;
		}
		else  //˵�����������Һ��ӻ���child����hp->size���˳�ѭ��
			break;
	}
}


void BigHeapAdjustDown(Heap*hp, int parent)//���µ����ɴ��
{
	int child = parent * 2 + 1;
	while (parent < hp->size)
	{    //�������С���Һ��ӣ���child�����Һ��ӣ���child�����Һ��ӽϴ�����
		if (child + 1 < hp->size && hp->arry[child] < hp->arry[child + 1])
			child = child + 1;
		if (child < hp->size &&hp->arry[parent] < hp->arry[child])//��С�ں���
		{
			Swap(&hp->arry[parent], &hp->arry[child]);
			// ����֮����Ҫ��childΪ���ٵ���һ�Σ���Ϊ��������ܵ��¸�С�����Һ���
			parent = child;
			child = parent * 2 + 1;
		}
		else  //˵�����������Һ��ӻ���child����hp->size���˳�ѭ��
			break;
	}
}
void SmallHeapMake(Heap* hp,int k)//С�ѵĴ���
{
	int i = 0;//�Ӵ�����һ����Ҷ�ӽ�㿪ʼ
	for (i = (k - 1 - 1) / 2; i >= 0; i--)
	{
		SmallHeapAdjustDown(hp, i,k);
	}
}
void BigHeapMake(Heap* hp)//��ѵĴ���
{
	int i = 0;//�Ӵ�����һ����Ҷ�ӽ�㿪ʼ
	for (i = (hp->size - 1 - 1) / 2; i >= 0; i--)
	{
		BigHeapAdjustDown(hp, i);
	}
}
void TestFindTopK()
{
	int a[] = {44 ,2 ,71 ,8,12,67,89};
	int i = 0;
	int k = 3;
	Heap hp;
	int size = sizeof(a) / sizeof(int);
	HeapInit(&hp, a, size);
	HeapFindTopK(&hp, k, size);
	for (i = 0; i < k; i++)
	{
		printf("%d ", hp.arry[i]);
	}
	printf("\n");
	FindTopK(a, k, size);//�ҳ�����ǰK����
	
	for (i = 0; i < k; i++)
		printf("%d ", a[i]);
	printf("\n");
}
void AdjustDown(int *a, int k, int root)//k���������µ���,û�н���
{
	int parent = root;
	int child = parent * 2 + 1;
	if ((child+1)<k&&a[child] >a[child + 1])
		child++;
	while (child < k)
	{
		if (a[parent] >a[child])
		{
			Swap(&a[parent], &a[child]);
			parent = child;
			child = parent * 2 + 1;
		}
		else
			break;
	}
}
int main()
{
	//Heap hp;
	//HeapDatatype a[] = { 10,16,18,12,11,22,15,17,14,19 };
	//int sz = sizeof(a) / sizeof(HeapDatatype);
	//HeapInit(&hp, a, sz);//�ѵĳ�ʼ��
	//HeapPrint(&hp);//�ѵĴ�ӡ
	//BigHeapMake(&hp);//��ѵĴ���
	//HeapPrint(&hp);//�ѵĴ�ӡ
	//HeapPush(&hp, 21);//������������
	//HeapPrint(&hp);//�ѵĴ�ӡ
	//HeapPop(&hp);//��pop
	//HeapPrint(&hp);//�ѵĴ�ӡ
	//HeapSort(&hp);//������  
	//HeapPrint(&hp);//�ѵĴ�ӡ
	TestFindTopK();

	system("pause");
	return 0;
}

void FindTopK(int *a, int k, int n)//��һ������������ǰK����
{    //û�н���
	//�Ƚ�ǰk����������a[0]����С����k+1������a[0]Ԫ�ؽ��бȽϣ�
	//������ڣ��򽻻����ٽ���K��������Ϊa[0]��С��ѭ��ֱ��ȫ���Ƚ�
	//��ô������ǰk����������ǰk����
	int i = 0;
	for (i = (k - 1 - 1) / 2; i >= 0; i--)
	{
		AdjustDown(a, k, i);//����Ϊa[0]��С
	}
	for (int j = k; j <n; j++)
	{
		if (a[j] > a[0])
			Swap(&a[j], &a[0]);
		AdjustDown(a, k, 0);
	}
}
void HeapFindTopK(Heap *hp, int k, int n)//��һ������������ǰK����,���ö�
{
	SmallHeapMake(hp,k);//����С��
	for (int j = k; j < n; j++)
	{
		if (hp->arry[0] < hp->arry[j])
			Swap(&hp->arry[0], &hp->arry[j]);
		SmallHeapAdjustDown(hp,  0,k);//С�����µ���
	}
}