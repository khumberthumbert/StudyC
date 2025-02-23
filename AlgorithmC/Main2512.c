#include <stdio.h>
#include <stdlib.h>

int find_max_budget(int n, int requests[], int total_budget)
{
	//end : 최적 상환액(가능한 최대값)
	int start = 0, end = 0;
	for (int i = 0; i < n; i++) {
		// end에 가장 큰 예산 요청 금액 설정.
		if (requests[i] > end) {
			end = requests[i];
		}
	}
	
	//이분탐색 알고리즘
	while (start <= end) {
		int mid = (start + end) / 2;
		//allocated -> 배정된 총 예산의 합을 계산하기 위함.
		int allocated = 0;
		for (int i = 0; i < n; i++) {
			//각 지방의 요청 금액이 mid보다 작으면 요청 금액 그대로 배정
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
	//지방 수
	int n;
	scanf_s("%d", &n);
	int* requests = (int*)malloc(n * sizeof(int));
	if (requests == NULL)
	{
		printf("메모미 동적할당 실패\n");
		return 1;
	}
	//각 지방의 예산 요청 입력.
	for (int i = 0; i < n; i++)
	{
		scanf_s("%d", &requests[i]);
	}

	//총 예산 입력
	int total_budget;
	scanf_s("%d", &total_budget);

	//최대 상한액 계산 및 출력
	int result = find_max_budget(n, requests, total_budget);
	printf("%d\n", result);

	free(requests);

	return 0;
}