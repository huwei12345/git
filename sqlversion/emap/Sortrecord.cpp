#include"elemap.h"
extern int hassorted;
void Record::bubblesort()
{
	Record &record = (*this);
	//�Ż�1�����һ����ѭ��δ����������˵����������ɣ�return������flag
//�Ż�2�����һ����ѭ����ĳλ���Ժ�δ����������˵��֮�����ź�������tempposition
	node* p = nullptr;
	int size = record.size();
	int temppposition = 0;
	int len = size - 1;
	unsigned int a = 0, b = 0;
	for (int i = 0; i < size - 1; ++i)
	{
		int flag = 0;
		for (int j = 0; j < len; ++j)
		{
			a = b;
			b = record[j + 1]->LinkID;
			if (a > b)
			{
				flag = 1;
				//swap(record[i], record[j]);
				p = record[j];
				record[j] = record[j + 1];
				record[j + 1] = p;
				temppposition = j;
			}
		}
		len = temppposition;
		if (flag == 0)
			return;
	}
}

int Record::partition(int l, int r)
{
	Record& record = (*this);
	node* tempnode = record[l];
	unsigned int temp = 0;
	while (l < r)
	{
		temp = tempnode->LinkID;
		while (l < r && record[r]->LinkID >= temp)
			r--;
		if (l < r)
			record[l] = record[r];
		while (l < r && record[l]->LinkID <= temp)
			l++;
		if (l < r)
			record[r] = record[l];
	}
	record[l] = tempnode;
	return l;
}
void Record::quicksort(int l, int r)//�ݹ���̫��
{
	Record& record = (*this);
	int index = 0;
	if (l < r)
	{
		index = partition(l, r);
		quicksort(l, index - 1);
		quicksort(index + 1, r);
	}
}
void Record::insertsort()
{
	Record& record = (*this);
	node* p = nullptr;
	int m = record.size();
	for (int i = 1; i < m; i++)
	{
		p = record[i];
		for (int j = i - 1; j >= 0; j--)
		{
			if (record[j]->LinkID > p->LinkID)
			{
				record[j + 1] = record[j];
			}
			else
			{
				record[j + 1] = p;
				break;
			}
		}
	}
}
void Record::perdown(int i, int first, int last)
{
	Record& record = (*this);
	int flag = 0;
	node* p = nullptr;
	int secondchild = i * 2 + 2;
	while (secondchild <= last)//�����ӽڵ�
	{
		flag = 0;
		if (record[secondchild]->LinkID < record[secondchild - 1]->LinkID)
		{
			flag = 1;
			secondchild -= 1;//���Ľڵ�
		}
		if (record[i]->LinkID < record[secondchild]->LinkID)//����������ֵ���ڸ��ڵ�
		{
			p = record[secondchild];
			record[secondchild] = record[i];
			record[i] = p;
			i = secondchild;//���¶�ֵ
			secondchild = i * 2 + 2;//�������ӽڵ�ֵ
		}
		else
		{
			if (flag == 1)
				secondchild += 1;
			break;
		}
	}
	if (secondchild - 1 == last)//�������һ��ֻ�����ӽڵ�
	{
		secondchild = secondchild - 1;
		if (record[i]->LinkID < record[secondchild]->LinkID)
		{
			node* p = record[secondchild];
			record[secondchild] = record[i];
			record[i] = p;
		}
	}
}
void Record::make_heap(int first, int last)
{
	Record& record = (*this);
	//0 1 2 3 4 5 6
		//left=parent*2+1;
		//right=parent*2+2;
		//parent = (child-1) / 2;
	for (int i = (last - 1) / 2; i >= 0; i--)//��һ�����ڵ㿪ʼ
	{
		perdown(i, first, last);
	}
}
void Record::heapsort()
{
	Record& record = (*this);
	make_heap(0, record.size() - 1);
	int first = 0;
	int last = record.size() - 1;//record.size()
	while (last - first >= 1)
	{
		node* temp = record[first];
		record[first] = record[last];
		record[last] = temp;
		--last;
		perdown(0,first, last);
	}
}
//������
void Record::merge(int l, int r, int mid)
{
	Record &a = (*this);
	vector<node*> aux(r-l+1,NULL);//ָ��
	int i, j, k;
	for (k = l; k <= r; k++)//��ֵ���� 
		aux[k - l] = a[k];
	i = l;
	j = mid + 1;
	for (k = l; k <= r; k++)
	{
		if (i > mid)//[0,mid]
		{
			a[k] = aux[j - l];//�Ҳ����η��� 
			j++;
		}
		else if (j > r)//[mid+1,r]
		{
			a[k] = aux[i - l];//�����η��� 
			i++;
		}
		else if (aux[i - l]->LinkID > aux[j - l]->LinkID)//�󲿴��ȷ��Ҳ� 
		{
			a[k] = aux[j - l];
			j++;
		}
		else//�Ҳ����ȷ��� 
		{
			a[k] = aux[i - l];
			i++;
		}
	}
}

void Record::merge_sort(int l,int r)
{
	if (l >= r)
		return;
	int mid = (l + r) / 2;
	merge_sort(l, mid);
	merge_sort(mid + 1, r);
	merge(l, r, mid);
}
void Record::selectsort()
{
	Record& record = (*this);
	int index = 0;
	int size=record.size();
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j <size-i; ++j)
		{
			if (record[index]->LinkID < record[j]->LinkID)
				index = j;
		}
		node* temp= record[index];
		record[index]=record[size-i-1];
		record[size-i-1] = temp;
	}
}
bool cmp(node* a, node* b)
{
	return (a->LinkID) < (b->LinkID) ? true : false;
}
void Record::stlsort()
{
	Record& record = (*this);
	sort(record.begin(), record.end(), cmp);
	//showall(record);
}