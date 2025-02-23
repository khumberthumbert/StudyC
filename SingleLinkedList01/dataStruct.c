#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

typedef struct USERDATA
{
	int age;
	char name[32];
	char phone[32];
	struct USERDATA* pNext;
} USERDATA;

USERDATA* g_pHeadNode = NULL;

//읽기만 할 때 const 활용.
void AddNewNode(int age, const char *pszName, const char *pszPhone)
{
	USERDATA* pNewNode = (USERDATA*)malloc(sizeof(USERDATA));
	pNewNode->age = age;
	strcpy_s(pNewNode->name, sizeof(pNewNode->name), pszName);
	strcpy_s(pNewNode->phone, sizeof(pNewNode->phone), pszPhone);
	pNewNode->pNext = NULL;

	if (g_pHeadNode == NULL)
		g_pHeadNode = pNewNode;
	else
	{
		pNewNode->pNext = g_pHeadNode;
		g_pHeadNode = pNewNode;
	}
}

void ReleaseList(void)
{
	USERDATA* pTmp = g_pHeadNode;
	USERDATA* pDelete;
	while (pTmp != NULL)
	{
		pDelete = pTmp;
		pTmp = pTmp->pNext;

		printf("Delete: [%p] %d, %s, %s [%p]\n", pDelete,
			pDelete->age, pDelete->name, pDelete->phone, pDelete->pNext);

		free(pDelete);
	}
	g_pHeadNode = NULL;
}

void initDummyData(void)
{
	//Input INPUT 할 때도 함수로 만드는게 좋다.
	AddNewNode(10, "Hoon", "010-1111-1111");
	AddNewNode(11, "choi", "010-2222-2222");
	AddNewNode(13, "Jang", "010-3333-3333");
}

void PrintList(void)
{
	USERDATA* pTmp = g_pHeadNode;
	while (pTmp != NULL)
	{
		printf("[%p] %d, %s, %s [%p]\n", pTmp,
			pTmp->age, pTmp->name, pTmp->phone, pTmp->pNext);
		pTmp = pTmp->pNext;
	}
}

int main(void)
{
	initDummyData();

	//Print List
	PrintList();

	ReleaseList();

	return 0;
}