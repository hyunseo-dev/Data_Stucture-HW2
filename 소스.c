#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#pragma warning(disable:4996)
#define MAX_ELEMENT 200

typedef struct {
	int data;
} element; // �� ���� ������

typedef struct {
	element heap[MAX_ELEMENT];
	int heapsize;
} MinHeap; // �ּ��� ����

MinHeap heap; // �� ����

void init(MinHeap* h)
{
	h->heapsize = 0; // �� �ʱ�ȭ; ���� ũ�� 0
}

void insert_min_heap(MinHeap* h, element item) // ���� ����; ���� ������ ���� �Ʒ��� ���ο� �ڽ� ��带 �߰��Ѵ�
{
	int i;
	i = ++(h->heapsize); // ���� ������� +1

	while ((i != 1) && (item.data < h->heap[i/2].data)) // �ִ� ������ �ε�ȣ �ݴ��; �θ��� �����Ͱ� �� Ŭ��
	{
		h->heap[i] = h->heap[i / 2]; // �θ�� �ڽ��� �ٲ���ϱ� ����; �θ��� �ڽĿ� ����
		i /= 2;
	}

	h->heap[i] = item;
}

element delete_min_heap(MinHeap* h)
{
	int parent, child;
	element item, temp;

	item = h->heap[1];
	temp = h->heap[(h->heapsize)--];
	parent = 1;
	child = 2;

	while (child <= h->heapsize)
	{
		if ((child < h->heapsize) && (h->heap[child].data) > h->heap[child + 1].data)
			// �ִ� ������ �ε�ȣ �ݴ��; �ڽ� ��� �߿��� �� ���� ���� ã�� �����ؾ���; ��, �պκ��� child�� heapsize���� ������������ ����Ǿ�� �ϹǷ� �ε�ȣ ����
			child++;
		if (temp.data <= h->heap[child].data) // �ִ� ������ �ε�ȣ �ݴ��; �� �κ��� ���� �ȴٸ� �ڽ� ��尡 �� Ŀ���Ƿ� ���� �� �̻� �������� �ʾƵ� ��
			break;

		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2; // ������ �ٲٴ� �۾� ���� �� ���� �ܰ�� �Ѿ�� ���� ������ ����
	}

	h->heap[parent] = temp; // �ùٸ� ��ġ�� ����
	return item; // ������ ��Ʈ ��� �� ��ȯ
}

void print_heap(MinHeap* h)
{
	int i, level = 1, count = 0;

	for (i = 1; i <= h->heapsize; i++)
	{
		if (i == level)
		{
			printf("\n");
			level *= 2; // Ʈ���� ���� �� 2�辿 ��尡 �����ϴ� Ư���� �̿�
			count = 0; // ���ֵ� ���� �۵���.
		}

		printf("%d ", h->heap[i].data); // �̷��� ������ ���� ���� �� ����� ������
		count++;
	}

	printf("\n");
}

void change_priority(MinHeap* h, int find_val, int new_val)
{
	int i;
	int found = 0;
	for (i = 1; i <= h->heapsize; i++)
	{
		if (h->heap[i].data == find_val) // ���� ã����
		{
			printf("\n������ ���� ã�ҽ��ϴ�.\n");
			found++; // ���� ã������ flag�� ���� �Ʒ� ���� ã�� �� ���� ��� ��Ȱ��
			h->heap[i].data = new_val; // �� ��ġ�� ���ο� ���� ��ü

			// ���� �����Ѵٰ� �˾Ƽ� �������� ���� �ƴϱ⿡, �ٽ� �θ�, �ڽ� ���� �񱳸� ���� upheap, downheap ������ �ٽ� ������ �־����; ������ ����ߴ� �ڵ带 ������ ����
			while ((i != 1) && (h->heap[i].data < h->heap[i / 2].data)) // insert_min_heap�� Ȱ��; upheap ����
			{
				element temp = h->heap[i];
				h->heap[i] = h->heap[i / 2];
				h->heap[i / 2] = temp;
				i /= 2;
			}

			int child;
			while ((child = i * 2) <= h->heapsize) // delete_min_heap�� Ȱ��; downheap ����
			{
				if (child < h->heapsize && h->heap[child].data > h->heap[child + 1].data)
					child++;
				if (h->heap[i].data <= h->heap[child].data)
					break;
				element temp = h->heap[i];
				h->heap[i] = h->heap[child];
				h->heap[child] = temp;
				i = child;
			}
		
		}

	}
	if(found == 0)
		printf("\n������ ���� ã�� �� �����ϴ�.\n");
	return;
}

int menu_choice() // �޴� ����
{
	int choice;

	printf("\n------ Menu ------\n");
	printf("1. �ּ� �� ����(�߰�) / ���� ���� �ִ� ���� ���� %d�� (�ִ� 199��)\n", heap.heapsize);
	printf("2. �ּڰ� ����\n");
	printf("3. �� �������� ����(�� ���� ����)\n");
	printf("4. ������� �ۼ��� �� ���\n");
	printf("5. �ۼ��� ������ �켱���� ����\n");
	printf("6. ����\n");
	printf("------------------\n");
	printf("�����ϼ��� : ");

	choice = integer_check(); // ���ڸ� �Է¹ް�

	printf("\n\n");

	return choice; // ������
}

void menu_handler(int choice) // �޴� ���ÿ� ���� ������ ��� ����
{
	switch (choice) { 
		// ����ġ�� ���������ν� ��� ���� ��ȿ�� �˻簡 �����. �׷��� ���� �Է��� ����� �� ��, ���� �Է��� ���� �Է��� �ƴ� ��쿣 ���ۿ� ���� �Է��� ���ڰ� ���� ������ ������ �߻��ϴ� ��� �߻�(���� �׽�Ʈ �غ�����).
		// ���� �޴� �������� integer_check�� ���� ��ȿ�� �˻縦 ��ȭ��-> �˸��� '����' ���� �޾ƿ� �Ѱ���. ���� ����ġ�������� ��ȿ�� 1~6 ���� ���Դ��� Ȯ�� �� �� ���� ���� �Է��ϸ� �߸��� ������ �˷��ְԵ�.
	case 1:
		if (heap.heapsize >= MAX_ELEMENT-1) // �� á���� �����Ұ� �ǵ��
			printf("���� ����á���ϴ�.\n\n");
		else
		{
			printf("���� ���� �ִ� ������ ������ %d�� �Դϴ�\n", heap.heapsize);
			printf("�ִ� �߰� ������ ������ ������ %d�� �Դϴ�\n", 199 - heap.heapsize);
			int add_elements;
			do {
				printf("���� �Էµ� ������ ������ �Է��ϼ��� : ");
				add_elements = integer_check();
				if (heap.heapsize + add_elements >= MAX_ELEMENT)
					printf("���� 199�� �̻��� ���Ҹ� �߰��� �� �����ϴ�. �ٽ� �Է��ϼ���\n");
			} while (heap.heapsize + add_elements >= MAX_ELEMENT); // 199���� �Ѿ�� ����� �۵����� ����. ���� ���� 199���� ���Ұ� ����Ǿ� ���� �� �� �޴��� �����ߴٸ� �߰��� ������ ������ 0�� �Է��ؾ߸� �Ѿ��.

			int input;
			printf("	1) �������� �Է�\n"); // ���� �Է�
			printf("	2) ���� �Է�\n"); // ���� �Է� ���� ����
			printf("�����ϼ��� : ");
			input = integer_check(); // �� ��쿡�� ��ȿ�� �˻�� �⺻������ ����; ���� �Է¹޴� ��쿡 ��� ��ȿ�� �˻縦 �����Ѵٰ� �����Ͻø� �˴ϴ�.
			while (input != 1 && input != 2) // 1 �Ǵ� 2�� �ƴ� ��쿣 �ٽ� ����
			{
				printf("�߸��� ���Դϴ�. �ٽ� �����ϼ���.\n");
				printf("�����ϼ��� : ");
				input = integer_check();
			}
			for (int i = 0; i < add_elements; i++) // �ʿ��� ��ŭ �߰� : 1 ���ý� 1~100 ���� ������, 2 ���ý� ���� �Է¹���
			{
				element e;
				if (input == 1)
					e.data = rand() % 100 + 1;
				else // ������ 1�Ǵ� 2������ �۵��ϵ��� ó�������Ƿ� ���� ���⼭ �� ������ ���ʿ�� ����
				{
					printf("%d ��° ���ڸ� �Է��ϼ��� : ", i + 1);
					e.data = integer_check();
				}
				insert_min_heap(&heap, e);
				print_heap(&heap); 
				// 189��° ������ �ּ� ó�� �� for�� �տ� �� ����� ���ָ� �� ���� �߰����� �����ִ� ���� �ƴ�, ����� �����ְ� �� �� ����
				// �׷��� �Ϲ������� �߰��� ���� ������ 10�� ���ܶ�� �����Ͽ� �߰��Ǵ� ������ �ϳ��� �����ֵ��� �Ͽ��� -> ���ȿ�� : ���� ���� ���� �ľǿ� ������ �� ��
			}
/*			do {
				switch (input) {
				case 1:
					for (int i = 0; i < add_elements; i++)
					{
						element e;
						e.data = rand() % 100 + 1;
						insert_min_heap(&heap, e);
						print_heap(&heap);
					}
					break;
				case 2:
					for (int i = 0; i < add_elements; i++)
					{
						element e;
						printf("%d ��° ���ڸ� �Է��ϼ��� : ", i + 1);
						scanf("%d", &(e.data));
						insert_min_heap(&heap, e);
						print_heap(&heap);
					}
					break;
				default:
					printf("�߸��� ���Դϴ� �ٽ� �����ϼ���.");
				}
			} while (input != 1 && input != 2);*/ // �ڵ� ���� �ʿ�
		}
		break;

	case 2:
		if (heap.heapsize == 0) // ���� ��Ȳ���� �ǵ���� ���ֵ��� �Ͽ���. �Ʒ� ���̽��� ������
			printf("���� ������ϴ�.\n\n");
		else
		{
			element d = delete_min_heap(&heap);
			printf("������ : < %d > \n", d.data); // ���ŵ� �κ��� ������. ���� �ִ� �� �ڵ� �ο�.
			print_heap(&heap);
		}
		break;

	case 3:
		if (heap.heapsize == 0)
			printf("���� ������ϴ�.\n\n");
		else
		{
			while (heap.heapsize > 0) // case 2�� 1���� ���ڸ� ��������. case 3�� ��� ���ڸ� ������ ���� ���
			{
				element d = delete_min_heap(&heap);
				printf("������ : < %d > \n", d.data);
				print_heap(&heap);
			}
		}
		break;

	case 4: // �׽�Ʈ �� ���� �� ���¸� Ʈ��ŷ�ϴ� ���� �ʿ伺�� ���� �߰��Ͽ���
		if (heap.heapsize == 0)
			printf("���� ������ϴ�.\n\n");
		else
			print_heap(&heap); // �ܼ� �� ��� ������ ��.
		break;

	case 5:

		printf("----���� ��----\n"); 
		// �켱������ ������ �ܼ��ϰ� �ּڰ��� �����ϴ� �Ͱ��� ���� �ٸ� ���̽���.
		// �� ���¸� ���� ������ ���� Ȯ���ؾ� �ϹǷ� �� ���¸� Ʈ��ŷ �� �� �ֵ��� ���� ������ֵ��� �Ͽ���.
		print_heap(&heap);
		if (heap.heapsize == 0)
			printf("���� ������ϴ�.\n\n");
		else
		{
			int find_val, new_val; // ���ڴ� �׻� ��ȿ�� ������ �޾� �ѱ� (������ �̿��� �����ϱ� ���� ����)
			printf("\n\n������ ��� ���ڸ� �Է����ּ��� : ");
			find_val = integer_check();
			printf("���ο� ���ڸ� �Է����ּ��� : ");
			new_val = integer_check();

			change_priority(&heap, find_val, new_val); // �� �Լ������� �����ϰ� ���������, ���Է��� �̷������ �ֱ� ������ '���� ã�Ҵ�/�� ã�Ҵ�' �� ���� �ǵ���� �߰��ߴ� ��
			print_heap(&heap); // ������ �ưų� �� �ưų� ���� Ȥ�� �ٲ��� ���� ���� ������; Ʈ��ŷ ����
		}
		break;


	case 6: // ���� ���� �� ���� Ż��
		break;


	default: // �߸��� ���� ���� �ǵ��
		printf("�߸��� ���Դϴ� �ٽ� �����ϼ���.\n");

	}
}

int integer_check()
// �߿��� ��Ʈ : ���� ���� ������ �Էµ� ��, ���ڰ� �Է� �ƴٸ� ����� �νĵ�
// ex) '1eeeeeeee' �Է� �ÿ��� 1�� �޴��� �۵���, �׷��� 'e1'�� ���� ���ڰ� ���� �Էµƴٸ� �ٽ� �Է��ؾ���.
// �۵��� �־� critical�� ���״� �ƴϳ�, ���� ������ ���� Ž���غ� �ʿ䰡 �ִٰ� ������.
{
	int input;
	while (1) // ����� �� ���� ���ö����� ���� �ݺ���
	{
		if (scanf("%d", &input) == 1) // ���� �Է��� ������ �´ٸ�
		{
			while (getchar() != '\n'); // ���۸� ����
			break; // Ż����
		}
		else // �� ���� ��Ȳ����
		{
			printf("���ڸ� �Է��ϼ���.\n"); // ���ڰ� �ƴ��� �ǵ�����ְ�
			while (getchar() != '\n'); // ���۸� ���
		}
	}
	return input; // �Է¹��� �ùٸ� ���� ��ȯ ���ֵ��� ��
}

int main()
{
	init(&heap);		// �ʱ�ȭ
	srand(time(NULL)); // �ð��� ������� �õ带 �޾ƿ� ������ ����

	int choice;
	do {
		system("cls"); // �� ���� ��, �ܼ�â�� �����ϰ� �����ϱ� ���� �߰���.
		choice = menu_choice();
		menu_handler(choice);
		printf("����Ϸ��� �ƹ� Ű�� ��������");
		getchar(); // �� �κ��� �ֱ⶧����, ������ Ű�� �����߸� ȭ���� ��������� ��.(��� ����)
		getchar(); // �� �κ��� ���ٸ�, �ǵ���� Ȯ������ ���ϰ� �ٷ� system("cls")�� �۵���.
		// getchar();�� 2�� �߰��� ������ ���๮�ڿ� ���� ���۵� ���� ������. 1���� ���� ��� ���� ������� �ʰ� �ٷ� ���� �ݺ����� ����Ǵ� ��� �߻���.
		} while (choice != 6); // 6. ���ᰡ �ƴ϶�� ���� �ݺ�

		return 0;
}