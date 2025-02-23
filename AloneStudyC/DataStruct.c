#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

typedef struct USERDATA
{
	int age;
	char name[32];
	char phone[32];
	struct USERDATA* pPrev;
	struct USERDATA* pNext;
} USERDATA;

//USERDATA* g_pHeadNode = NULL;
USERDATA g_HeadNode = { 0, "__Dummy Head__" };
USERDATA g_TailNode = { 0, "__Dummy Tail__"};

void AddNewNode(int age, const char *pszName, const char *pszPhone)
{
	USERDATA* pNewNode = (USERDATA*)malloc(sizeof(USERDATA));
	pNewNode->age = age;
	strcpy_s(pNewNode->name, sizeof(pNewNode->name), pszName);
	strcpy_s(pNewNode->phone, sizeof(pNewNode->phone), pszPhone);
	pNewNode->pPrev = NULL;
	pNewNode->pNext = NULL;

	USERDATA* pPrevNode = g_TailNode.pPrev;
	pNewNode->pPrev = g_TailNode.pPrev;
	pNewNode->pNext = &g_TailNode;

	pPrevNode->pNext = pNewNode;
	g_TailNode.pPrev = pNewNode;

}  

void InitList(void)
{
	g_HeadNode.pNext = &g_TailNode;
	g_TailNode.pPrev = &g_HeadNode;

	//g_TailNode.pNext = &g_HeadNode; //¼øÈ¯ Å¥.
}

void ReleaseList()
{
	USERDATA* pTmp = g_HeadNode.pNext;
	USERDATA* pDelete;
	while (pTmp != NULL && pTmp != &g_TailNode)
	{	
		pDelete = pTmp;
		pTmp = pTmp->pNext;

		printf("Delete : [%p]\t %d\t %s\t %s\t pNext : [%p]\n", pDelete,
			pDelete->age, pDelete->name, pDelete->phone, pDelete->pNext);

		free(pDelete);
	}									

	InitList();
}

void InitDummyData(void)
{
	AddNewNode(10, "Hoon", "010-1111-1111");
	AddNewNode(11, "Choi", "010-2222-2222");
	AddNewNode(12, "Jang", "010-3333-3333");
}

USERDATA* SearchByName(const char* pszName)
{
	USERDATA* pTmp = g_HeadNode.pNext;
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

void RemoveNode(USERDATA* pRemove)
{
	USERDATA* pPrev = pRemove->pPrev;
	USERDATA* pNext = pRemove->pNext;

	pPrev->pNext = pRemove->pNext;
	pNext->pPrev = pRemove->pPrev;

	printf("RemoveNode(): %s\n", pRemove->name);
	free(pRemove);
}

void PrintList(void)
{
	USERDATA* pTmp = &g_HeadNode;
	while (pTmp != NULL)
	{
		printf("[%p]\t %d\t %s\t %s\t pNext : [%p]\n", pTmp,
			pTmp->age, pTmp->name, pTmp->phone, pTmp->pNext);
		pTmp = pTmp->pNext;
	}
	putchar('\n');
}

void PrintListReverse(void)
{
	USERDATA* pTmp = g_TailNode.pPrev;
	while (pTmp != NULL)
	{
		printf("[%p]\t %d\t %s\t %s\t pNext : [%p]\n", pTmp,
			pTmp->age, pTmp->name, pTmp->phone, pTmp->pNext);
		pTmp = pTmp->pPrev;
	}
	putchar('\n');
}

void TestStemp01(void)
{
	puts("TestStemp01()-------------------");
	AddNewNode(10, "Choi", "010-2222-2222");
	AddNewNode(10, "Hoon", "010-1111-1111");
	AddNewNode(13, "Jang", "010-3333-3333");
	PrintList();

	USERDATA* pPrev = SearchByName("Choi");
	if (pPrev != NULL)
		RemoveNode(pPrev);
	ReleaseList();
	putchar('\n');
}

void TestStemp02(void)
{
	puts("TestStemp02()-------------------");
	AddNewNode(10, "Choi", "010-2222-2222");
	AddNewNode(10, "Hoon", "010-1111-1111");
	AddNewNode(13, "Jang", "010-3333-3333");
	PrintList();

	USERDATA* pPrev = SearchByName("Hoon");
	if (pPrev != NULL)
		RemoveNode(pPrev);
	ReleaseList();
	putchar('\n');
}

void TestStemp03(void)
{
	puts("TestStemp03()-------------------");
	AddNewNode(10, "Choi", "010-2222-2222");
	AddNewNode(10, "Hoon", "010-1111-1111");
	AddNewNode(13, "Jang", "010-3333-3333");
	PrintList();

	USERDATA* pPrev = SearchByName("Jang");
	if (pPrev != NULL)
		RemoveNode(pPrev);
	ReleaseList();
	putchar('\n');
}

int IsEmpty(void)
{
	if (g_HeadNode.pNext == &g_TailNode)
		return 1;

	return 0;
}

void Push(USERDATA* pUser)
{
	USERDATA* pNewNode = (USERDATA*)malloc(sizeof(USERDATA));
	memcpy(pNewNode, pUser, sizeof(USERDATA));
	pNewNode->pPrev = NULL;
	pNewNode->pNext = NULL;

	USERDATA* pNextNode = g_HeadNode.pNext;
	pNewNode->pPrev = &g_HeadNode;
	pNewNode->pNext = g_HeadNode.pNext;

	pNextNode->pPrev = pNewNode;
	g_HeadNode.pNext = pNewNode;
}

USERDATA* Pop()
{
	if (IsEmpty())
	{
		puts("Error: Stack Underflow.");
		return NULL;
	}

	USERDATA* pPop = g_HeadNode.pNext;
	g_HeadNode.pNext = pPop->pNext;
	pPop->pNext->pPrev = pPop->pPrev;

	return pPop;
}

USERDATA* Dequeue(void)
{
	return Pop();
}

void Enqueue(USERDATA* pUser)
{
	AddNewNode(pUser->age, pUser->name, pUser->phone);
}

int main(void)
{
	InitList();
	USERDATA user = { 10, "Test01"};
	//Push(&user);
	Enqueue(&user);

	user.age = 11;
	strcpy_s(user.name, sizeof(user.name), "Test02");
	//Push(&user);
	Enqueue(&user);

	user.age = 12;
	strcpy_s(user.name, sizeof(user.name), "Test03");
	//Push(&user);
	Enqueue(&user);

	for (int i = 0; i < 3; i++) {
		//USERDATA* pUser = Pop();
		USERDATA* pUser = Dequeue();
		printf("Pop : %d, %s\n", pUser->age, pUser->name);
		free(pUser);
	}
	ReleaseList();

	return 0;
}