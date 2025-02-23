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
void AddNewNode(int age, const char* pszName, const char* pszPhone)
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
		USERDATA* pTail = g_pHeadNode;
		while (pTail->pNext != NULL)
			pTail = pTail->pNext;

		pTail->pNext = pNewNode;
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

void InitDummyData(void)
{
	//Input INPUT 할 때도 함수로 만드는게 좋다.
	AddNewNode(10, "Hoon", "010-1111-1111");
	AddNewNode(11, "Choi", "010-2222-2222");
	AddNewNode(13, "Jang", "010-3333-3333");
}

USERDATA* SearchByName(const char* pszName)
{
	USERDATA* pTmp = g_pHeadNode;
	while (pTmp != NULL)
	{
		if (strcmp(pTmp->name, pszName) == 0)
		{
			printf("\"%s\" : Found\n", pszName);
			return pTmp;
		}

		pTmp = pTmp->pNext;
	}
	printf("\"%s\" : Not Found\n", pszName);
	return NULL;
}

USERDATA* SearchToRemove(USERDATA **ppPrev, const char* pszName)
{
	USERDATA* pCurrent = g_pHeadNode;
	USERDATA* pPrev = NULL;
	while (pCurrent != NULL)
	{
		if (strcmp(pCurrent->name, pszName) == 0)
		{
			*ppPrev = pPrev;
			return pCurrent;
		}
		pPrev = pCurrent;
		pCurrent = pCurrent->pNext;
	}
	printf("\"%s\" : Not Found\n", pszName);
	return NULL;
}

void RemoveNode(USERDATA* pPrev)
{
	USERDATA* pRemove = NULL;
	if (pPrev == NULL)
	{
		if (g_pHeadNode == NULL)
			return;
		else
		{
			pRemove = g_pHeadNode;
			g_pHeadNode = pRemove->pNext;
			printf("RemoveNode(): %s\n", pRemove->name);
			free(pRemove);
		}
		return;
	}
	pRemove = pPrev->pNext;
	pPrev->pNext = pRemove->pNext;
	free(pRemove);
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
	AddNewNode(10, "Hoon", "010-1111-1111");
	PrintList();

	USERDATA* pPrev = NULL;
	if (SearchToRemove(&pPrev, "Hoon") != NULL)
		RemoveNode(pPrev);

	PrintList();

	AddNewNode(10, "Choi", "010-2222-2222");
	AddNewNode(10, "Hoon", "010-1111-1111");
	AddNewNode(13, "Jang", "010-3333-3333");
	PrintList();
	pPrev = NULL;
	if (SearchToRemove(&pPrev, "Choi") != NULL)
		RemoveNode(pPrev);

	PrintList();

	AddNewNode(10, "Choi", "010-1111-1111");
	pPrev = NULL;
	if (SearchToRemove(&pPrev, "Jang") != NULL)
		RemoveNode(pPrev);
	PrintList();

	AddNewNode(13, "Jang", "010-3333-3333");
	PrintList();

	pPrev = NULL;
	if (SearchToRemove(&pPrev, "Jang") != NULL)
		RemoveNode(pPrev);
	PrintList();





	ReleaseList();

	return 0;
}