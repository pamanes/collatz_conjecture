#include "qcommon.h"
#include "list.h"
  //test
#ifdef _WIN32
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
//#include <stdlib.h>
#include <crtdbg.h>
#endif
#endif

struct nlist
{
	unsigned long long result;
	struct list_head list;
};

static __inline void add_item(struct list_head *head, unsigned long long n)
{	
	struct nlist *temp;
	temp = Z_Malloc(sizeof(struct nlist));//malloc(sizeof(struct nlist));
	temp->result = n;
	list_add(&(temp->list), head);
}

void printToCSV(FILE *f, struct list_head *head)
{
	struct list_head *pos;
	struct nlist *temp;

	__list_for_each(pos, head)
	{
		//pointer, type , member	
		temp = (struct nlist *)container_of(pos, struct nlist, list);
		//temp = (struct nlist *) ((char *)pos - offsetof(struct nlist,list));
		fprintf(f, "%llu,",temp->result);
	}
	fprintf(f, "\n");
}

void delList(struct list_head *head)
{
	struct nlist *temp;
	struct list_head *pos, *q;

	list_for_each_safe(pos, q, head)
	{
		temp = (struct nlist *)container_of(pos, struct nlist, list);
		list_del(pos->prev, pos->next);
		Z_Free(temp);
	}

}

void collatz(struct list_head *head, unsigned long long i)
{
	if(i%2 == 0)
		i = i / 2;
	else
		i = i*3 + 1;

	add_item(head, i);
	if(i != 1)
		collatz(head, i);
}

FILE *openCSV()
{
	FILE *f;
	f = fopen("csvfile.csv","w+");
	if(f == NULL)
		Sys_Error("cannot create file!");
	return f;
}

void ask(unsigned long long *n)
{
	Com_Printf("Give me an integer greater than 0:");
	if(scanf("%llu", n) != 1) 
		Sys_Error("error getting input from user");
	b_flush;//flush the buffer
}


int main(int argc, char *argv[])
{
	int ch = 0;
	struct nlist mylist;
	unsigned long long n = 2;
	unsigned long long x = 2;
	FILE *f;	
	
	//Z chain init
	z_chain.next = z_chain.prev = &z_chain;	
	//init the list
	INIT_LIST_HEAD(&mylist.list);

	f = openCSV();	
	ask(&n);

	if(n > 1)
	{
		for(;x<=n;x++)
		{
			collatz(&(mylist.list), x);
			//Z_Stats_f();
			printToCSV(f, &(mylist.list));
			delList(&(mylist.list));
		}
	}
	else 
		if (n == 1)
			Com_Printf("The number is 1, nothing to do here\n");
		else
			Com_Printf("bad arguments!\n");
	
	Com_Printf("done.\n");
	if((ch = getchar()) == EOF)
		Sys_Error("error stopping program");

/*
#ifdef _WIN32
#ifdef _DEBUG
	_CrtDumpMemoryLeaks();
#endif
#endif*/
	return 0;
}
