#include <stdio.h>
#include <stdlib.h>

int find_max_budget(int n, int requests[], int total_budget)
{
	//end : ���� ��ȯ��(������ �ִ밪)
	int start = 0, end = 0;
	for (int i = 0; i < n; i++) {
		// end�� ���� ū ���� ��û �ݾ� ����.
		if (requests[i] > end) {
			end = requests[i];
		}
	}
	
	//�̺�Ž�� �˰���
	while (start <= end) {
		int mid = (start + end) / 2;
		//allocated -> ������ �� ������ ���� ����ϱ� ����.
		int allocated = 0;
		for (int i = 0; i < n; i++) {
			//�� ������ ��û �ݾ��� mid���� ������ ��û �ݾ� �״�� ����
			allocated += (requests[i] < mid) ? requests[i] : mid;
		}

		if (allocated <= total_budget) {
			start = mid + 1;
		}
		else {
			end = mid - 1;
		}
	}
	return end;
}



int main(void)
{
	//���� ��
	int n;
	scanf_s("%d", &n);
	int* requests = (int*)malloc(n * sizeof(int));
	if (requests == NULL)
	{
		printf("�޸�� �����Ҵ� ����\n");
		return 1;
	}
	//�� ������ ���� ��û �Է�.
	for (int i = 0; i < n; i++)
	{
		scanf_s("%d", &requests[i]);
	}

	//�� ���� �Է�
	int total_budget;
	scanf_s("%d", &total_budget);

	//�ִ� ���Ѿ� ��� �� ���
	int result = find_max_budget(n, requests, total_budget);
	printf("%d\n", result);

	free(requests);

	return 0;
}