#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#pragma warning(disable:4996)
#define MAX_ELEMENT 200

typedef struct {
	int data;
} element; // 힙 내부 데이터

typedef struct {
	element heap[MAX_ELEMENT];
	int heapsize;
} MinHeap; // 최소힙 구성

MinHeap heap; // 힙 선언

void init(MinHeap* h)
{
	h->heapsize = 0; // 힙 초기화; 최초 크기 0
}

void insert_min_heap(MinHeap* h, element item) // 삽입 연산; 삽입 연산은 가장 아래에 새로운 자식 노드를 추가한다
{
	int i;
	i = ++(h->heapsize); // 최초 사이즈에서 +1

	while ((i != 1) && (item.data < h->heap[i/2].data)) // 최대 힙에서 부등호 반대로; 부모의 데이터가 더 클때
	{
		h->heap[i] = h->heap[i / 2]; // 부모와 자식을 바꿔야하기 때문; 부모값을 자식에 대입
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
			// 최대 힙에서 부등호 반대로; 자식 노드 중에서 더 작은 것을 찾아 삭제해야함; 단, 앞부분은 child가 heapsize보다 작을때까지만 수행되어야 하므로 부등호 유지
			child++;
		if (temp.data <= h->heap[child].data) // 최대 힙에서 부등호 반대로; 이 부분이 참이 된다면 자식 노드가 더 커지므로 힙을 더 이상 조정하지 않아도 됨
			break;

		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2; // 실제로 바꾸는 작업 수행 후 다음 단계로 넘어가기 위해 변수들 조정
	}

	h->heap[parent] = temp; // 올바른 위치에 삽입
	return item; // 삭제된 루트 노드 값 반환
}

void print_heap(MinHeap* h)
{
	int i, level = 1, count = 0;

	for (i = 1; i <= h->heapsize; i++)
	{
		if (i == level)
		{
			printf("\n");
			level *= 2; // 트리의 레벨 당 2배씩 노드가 증가하는 특성을 이용
			count = 0; // 없애도 정상 작동함.
		}

		printf("%d ", h->heap[i].data); // 이러한 과정을 통해 레벨 당 출력을 보여줌
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
		if (h->heap[i].data == find_val) // 값을 찾으면
		{
			printf("\n힙에서 값을 찾았습니다.\n");
			found++; // 값을 찾았으니 flag를 통해 아래 값을 찾을 수 없다 출력 비활성
			h->heap[i].data = new_val; // 그 위치에 새로운 값을 대체

			// 값을 대입한다고 알아서 맞춰지는 것이 아니기에, 다시 부모, 자식 간의 비교를 통해 upheap, downheap 연산을 다시 수행해 주어야함; 위에서 사용했던 코드를 응용해 구현
			while ((i != 1) && (h->heap[i].data < h->heap[i / 2].data)) // insert_min_heap의 활용; upheap 연산
			{
				element temp = h->heap[i];
				h->heap[i] = h->heap[i / 2];
				h->heap[i / 2] = temp;
				i /= 2;
			}

			int child;
			while ((child = i * 2) <= h->heapsize) // delete_min_heap의 활용; downheap 연산
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
		printf("\n힙에서 값을 찾을 수 없습니다.\n");
	return;
}

int menu_choice() // 메뉴 구현
{
	int choice;

	printf("\n------ Menu ------\n");
	printf("1. 최소 힙 생성(추가) / 현재 힙에 있는 숫자 개수 %d개 (최대 199개)\n", heap.heapsize);
	printf("2. 최솟값 삭제\n");
	printf("3. 힙 오름차순 정렬(힙 전부 삭제)\n");
	printf("4. 현재까지 작성된 힙 출력\n");
	printf("5. 작성된 힙에서 우선순위 변경\n");
	printf("6. 종료\n");
	printf("------------------\n");
	printf("선택하세요 : ");

	choice = integer_check(); // 숫자를 입력받고

	printf("\n\n");

	return choice; // 리턴함
}

void menu_handler(int choice) // 메뉴 선택에 따른 실질적 기능 구현
{
	switch (choice) { 
		// 스위치를 구현함으로써 어느 정도 유효성 검사가 보장됨. 그러나 앞의 입력이 제대로 들어간 후, 뒤의 입력이 정수 입력이 아닌 경우엔 버퍼에 이전 입력한 숫자가 남아 여전히 오류가 발생하는 경우 발생(직접 테스트 해보았음).
		// 따라서 메뉴 구현에서 integer_check를 통해 유효성 검사를 강화함-> 알맞은 '숫자' 값만 받아와 넘겨줌. 따라서 스위치문에서는 유효한 1~6 값이 들어왔는지 확인 후 그 외의 값을 입력하면 잘못된 값임을 알려주게됨.
	case 1:
		if (heap.heapsize >= MAX_ELEMENT-1) // 꽉 찼을때 생성불가 피드백
			printf("힙이 가득찼습니다.\n\n");
		else
		{
			printf("현재 힙에 있는 숫자의 개수는 %d개 입니다\n", heap.heapsize);
			printf("최대 추가 가능한 숫자의 개수는 %d개 입니다\n", 199 - heap.heapsize);
			int add_elements;
			do {
				printf("힙에 입력될 원소의 개수를 입력하세요 : ");
				add_elements = integer_check();
				if (heap.heapsize + add_elements >= MAX_ELEMENT)
					printf("힙에 199개 이상의 원소를 추가할 수 없습니다. 다시 입력하세요\n");
			} while (heap.heapsize + add_elements >= MAX_ELEMENT); // 199개가 넘어가면 절대로 작동하지 않음. 따라서 현재 199개의 원소가 저장되어 있을 때 이 메뉴로 접근했다면 추가할 원소의 개수를 0을 입력해야만 넘어가짐.

			int input;
			printf("	1) 랜덤으로 입력\n"); // 랜덤 입력
			printf("	2) 직접 입력\n"); // 직접 입력 선택 가능
			printf("선택하세요 : ");
			input = integer_check(); // 이 경우에도 유효성 검사는 기본적으로 실행; 숫자 입력받는 경우에 모두 유효성 검사를 수행한다고 생각하시면 됩니다.
			while (input != 1 && input != 2) // 1 또는 2가 아닌 경우엔 다시 실행
			{
				printf("잘못된 값입니다. 다시 선택하세요.\n");
				printf("선택하세요 : ");
				input = integer_check();
			}
			for (int i = 0; i < add_elements; i++) // 필요한 만큼 추가 : 1 선택시 1~100 사이 랜덤값, 2 선택시 직접 입력받음
			{
				element e;
				if (input == 1)
					e.data = rand() % 100 + 1;
				else // 위에서 1또는 2에서만 작동하도록 처리했으므로 굳이 여기서 또 제한을 걸필요는 없음
				{
					printf("%d 번째 숫자를 입력하세요 : ", i + 1);
					e.data = integer_check();
				}
				insert_min_heap(&heap, e);
				print_heap(&heap); 
				// 189번째 라인은 주석 처리 후 for문 앞에 힙 출력을 해주면 매 숫자 추가마다 보여주는 것이 아닌, 결과만 보여주게 할 수 있음
				// 그러나 일반적으로 추가할 힙의 개수가 10개 내외라고 가정하여 추가되는 과정을 하나씩 보여주도록 하였음 -> 기대효과 : 힙의 구성 과정 파악에 도움이 될 것
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
						printf("%d 번째 숫자를 입력하세요 : ", i + 1);
						scanf("%d", &(e.data));
						insert_min_heap(&heap, e);
						print_heap(&heap);
					}
					break;
				default:
					printf("잘못된 값입니다 다시 선택하세요.");
				}
			} while (input != 1 && input != 2);*/ // 코드 수정 필요
		}
		break;

	case 2:
		if (heap.heapsize == 0) // 예외 상황에는 피드백을 해주도록 하였음. 아래 케이스도 동일함
			printf("힙이 비었습니다.\n\n");
		else
		{
			element d = delete_min_heap(&heap);
			printf("삭제됨 : < %d > \n", d.data); // 제거된 부분을 보여줌. 기존 최대 힙 코드 인용.
			print_heap(&heap);
		}
		break;

	case 3:
		if (heap.heapsize == 0)
			printf("힙이 비었습니다.\n\n");
		else
		{
			while (heap.heapsize > 0) // case 2는 1개의 숫자만 빼내었음. case 3은 모든 숫자를 빼내서 힙을 비움
			{
				element d = delete_min_heap(&heap);
				printf("삭제됨 : < %d > \n", d.data);
				print_heap(&heap);
			}
		}
		break;

	case 4: // 테스트 중 현재 힙 상태를 트래킹하는 것의 필요성을 느껴 추가하였음
		if (heap.heapsize == 0)
			printf("힙이 비었습니다.\n\n");
		else
			print_heap(&heap); // 단순 힙 출력 연산을 함.
		break;

	case 5:

		printf("----현재 힙----\n"); 
		// 우선순위의 변경은 단순하게 최솟값을 삭제하는 것과는 조금 다른 케이스임.
		// 힙 상태를 보고 무엇을 뺄지 확인해야 하므로 힙 상태를 트래킹 할 수 있도록 힙을 출력해주도록 하였음.
		print_heap(&heap);
		if (heap.heapsize == 0)
			printf("힙이 비었습니다.\n\n");
		else
		{
			int find_val, new_val; // 숫자는 항상 유효성 검증을 받아 넘김 (오류를 미연에 방지하기 위한 목적)
			printf("\n\n변경할 대상 숫자를 입력해주세요 : ");
			find_val = integer_check();
			printf("새로운 숫자를 입력해주세요 : ");
			new_val = integer_check();

			change_priority(&heap, find_val, new_val); // 위 함수에서는 간략하게 언급했지만, 오입력이 이루어질수 있기 때문에 '값을 찾았다/못 찾았다' 에 대한 피드백을 추가했던 것
			print_heap(&heap); // 변경이 됐거나 안 됐거나 수정 혹은 바뀌지 않은 힙을 보여줌; 트래킹 목적
		}
		break;


	case 6: // 종료 원할 시 루프 탈출
		break;


	default: // 잘못된 값에 대한 피드백
		printf("잘못된 값입니다 다시 선택하세요.\n");

	}
}

int integer_check()
// 중요한 노트 : 앞의 값이 정수가 입력된 후, 문자가 입력 됐다면 제대로 인식됨
// ex) '1eeeeeeee' 입력 시에는 1번 메뉴가 작동함, 그러나 'e1'과 같이 문자가 먼저 입력됐다면 다시 입력해야함.
// 작동에 있어 critical한 버그는 아니나, 버그 개선을 위해 탐구해볼 필요가 있다고 생각함.
{
	int input;
	while (1) // 제대로 된 값이 나올때까지 무한 반복함
	{
		if (scanf("%d", &input) == 1) // 정수 입력을 받은게 맞다면
		{
			while (getchar() != '\n'); // 버퍼를 비우고
			break; // 탈출함
		}
		else // 그 외의 상황에는
		{
			printf("숫자를 입력하세요.\n"); // 숫자가 아님을 피드백해주고
			while (getchar() != '\n'); // 버퍼를 비움
		}
	}
	return input; // 입력받은 올바른 값은 반환 해주도록 함
}

int main()
{
	init(&heap);		// 초기화
	srand(time(NULL)); // 시간을 기반으로 시드를 받아와 랜덤값 생성

	int choice;
	do {
		system("cls"); // 매 실행 시, 콘솔창을 깨끗하게 유지하기 위해 추가함.
		choice = menu_choice();
		menu_handler(choice);
		printf("계속하려면 아무 키나 누르세요");
		getchar(); // 이 부분이 있기때문에, 임의의 키를 눌러야만 화면이 사라지도록 함.(대기 목적)
		getchar(); // 이 부분이 없다면, 피드백을 확인하지 못하고 바로 system("cls")가 작동됨.
		// getchar();을 2번 추가한 이유는 개행문자에 따른 오작동 방지 목적임. 1개만 있을 경우 종종 대기하지 않고 바로 다음 반복문이 실행되는 경우 발생함.
		} while (choice != 6); // 6. 종료가 아니라면 무한 반복

		return 0;
}