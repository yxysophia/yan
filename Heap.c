#include"Heap.h"
void HeapInit(Heap* hp, HeapDatatype* a, int n)//堆的创建
{
	assert(a&&hp);
	hp->capacity = n;
	hp->size = n;
	hp->arry = (HeapDatatype*)malloc(sizeof(HeapDatatype)*hp->capacity);
	int i = 0;
	for (i = 0; i < hp->size; i++)
		hp->arry[i] = a[i];
}
void HeapPrint(Heap *hp)//打印堆
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
void HeapPop(Heap *hp)//堆pop
{   //堆pop指pop的堆顶元素，将堆顶元素和最后一个数进行交换，size--
	assert(hp);
	Swap(&hp->arry[0], &hp->arry[hp->size - 1]);
	hp->size--;
	BigHeapAdjustDown(hp, 0);//向下调整
}
void HeapSort(Heap *hp)//堆排序，大堆
{
	//堆排序是将堆顶元素和最后一个交换，打印最后一个元素，
	//并且hp->size--，再调整为大堆，循环前面操作
	int n = hp->size;
	assert(hp);
	while (hp->size > 0)
	{
		Swap(&hp->arry[0], &hp->arry[hp->size - 1]);
		hp->size--;
		BigHeapAdjustDown(hp, 0);//向下调整
	}
	hp->size = n;//如果不重新赋值，则hp->size=0
}
void HeapPush(Heap *hp, HeapDatatype data)//向堆里插入数据
{
	if (hp->size == hp->capacity)//扩容
	{
		hp->arry = (HeapDatatype*)realloc(hp->arry, sizeof(HeapDatatype)*(hp->capacity) * 2);
		/*assert(hp->arry);*/
		hp->capacity *= 2;
	}
	hp->arry[hp->size] = data;
	hp->size++;
	HeapAdjustUp(hp, hp->size - 1);//向上调整
}

void HeapAdjustUp(Heap*hp, int child)//向上调整
{   //调整只会与孩子的祖先有关
	int parent = (child - 1) / 2;
	while (child > 0)//不能用parent>0来判断，因为parent = (child - 1) / 2;永远大于0
	{
		if (hp->arry[parent] < hp->arry[child])
		{
			Swap(&hp->arry[parent], &hp->arry[child]);
			child = parent;
			parent = (child - 1) / 2;
		}
		else  //如果父亲比孩子大，就没必要调整
			break;
	}
}
void SmallHeapAdjustDown(Heap*hp, int parent, int k)//向下调成小堆
{
	int child = parent * 2 + 1;
	while (parent < k)
	{    //如果左孩子大于右孩子，将child等于右孩子，即child存左右孩子较小坐标
		if (child + 1 < hp->size && hp->arry[child] > hp->arry[child + 1])
			child = child + 1;
		if (child < k &&hp->arry[parent] > hp->arry[child])//根大于孩子
		{
			Swap(&hp->arry[parent], &hp->arry[child]);
			// 调整之后需要以child为跟再调整一次，因为调整后可能导致根小于左右孩子
			parent = child;
			child = parent * 2 + 1;
		}
		else  //说明根大于左右孩子或者child大于hp->size，退出循环
			break;
	}
}


void BigHeapAdjustDown(Heap*hp, int parent)//向下调整成大堆
{
	int child = parent * 2 + 1;
	while (parent < hp->size)
	{    //如果左孩子小于右孩子，将child等于右孩子，即child存左右孩子较大坐标
		if (child + 1 < hp->size && hp->arry[child] < hp->arry[child + 1])
			child = child + 1;
		if (child < hp->size &&hp->arry[parent] < hp->arry[child])//根小于孩子
		{
			Swap(&hp->arry[parent], &hp->arry[child]);
			// 调整之后需要以child为跟再调整一次，因为调整后可能导致根小于左右孩子
			parent = child;
			child = parent * 2 + 1;
		}
		else  //说明根大于左右孩子或者child大于hp->size，退出循环
			break;
	}
}
void SmallHeapMake(Heap* hp,int k)//小堆的创建
{
	int i = 0;//从大堆最后一个非叶子结点开始
	for (i = (k - 1 - 1) / 2; i >= 0; i--)
	{
		SmallHeapAdjustDown(hp, i,k);
	}
}
void BigHeapMake(Heap* hp)//大堆的创建
{
	int i = 0;//从大堆最后一个非叶子结点开始
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
	FindTopK(a, k, size);//找出最大的前K个数
	
	for (i = 0; i < k; i++)
		printf("%d ", a[i]);
	printf("\n");
}
void AdjustDown(int *a, int k, int root)//k个数据向下调整,没有建堆
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
	//HeapInit(&hp, a, sz);//堆的初始化
	//HeapPrint(&hp);//堆的打印
	//BigHeapMake(&hp);//大堆的创建
	//HeapPrint(&hp);//堆的打印
	//HeapPush(&hp, 21);//向堆里插入数据
	//HeapPrint(&hp);//堆的打印
	//HeapPop(&hp);//堆pop
	//HeapPrint(&hp);//堆的打印
	//HeapSort(&hp);//堆排序  
	//HeapPrint(&hp);//堆的打印
	TestFindTopK();

	system("pause");
	return 0;
}

void FindTopK(int *a, int k, int n)//找一组数据里最大的前K个数
{    //没有建堆
	//先将前k个数调整成a[0]是最小数，k+1的数与a[0]元素进行比较，
	//如果大于，则交换，再将这K个数调整为a[0]最小，循环直至全部比较
	//那么数组里前k个数是最大的前k个数
	int i = 0;
	for (i = (k - 1 - 1) / 2; i >= 0; i--)
	{
		AdjustDown(a, k, i);//调整为a[0]最小
	}
	for (int j = k; j <n; j++)
	{
		if (a[j] > a[0])
			Swap(&a[j], &a[0]);
		AdjustDown(a, k, 0);
	}
}
void HeapFindTopK(Heap *hp, int k, int n)//找一组数据里最大的前K个数,利用堆
{
	SmallHeapMake(hp,k);//建成小堆
	for (int j = k; j < n; j++)
	{
		if (hp->arry[0] < hp->arry[j])
			Swap(&hp->arry[0], &hp->arry[j]);
		SmallHeapAdjustDown(hp,  0,k);//小堆向下调整
	}
}