#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 25
struct books_temp 
{
	char name[N];
	char surname[N];
	char book[N];
	int year;
	int pages;
	double price;
};
struct books
{
	char name[N];
	char surname[N];
	char book[N];
	int year;
	int pages;
	double price;

	struct books* next;
};
int ScaningAndCreatingList( struct books* pr)
{
	FILE* ptr;
	ptr = fopen("C:\\Проекти\\1 Семестр\\Лаба 8\\list.bin", "rb+");
	if (!ptr) return 0;
	struct books* pd = NULL;
	struct books_temp* p_temp = (struct books_temp*)malloc(sizeof(struct books_temp));;
	int counter = 0;
	while(1)
	{
		fread(p_temp, sizeof(struct books_temp), 1, ptr);
		strcpy(pr->name,p_temp->name);
		strcpy(pr->surname, p_temp->surname);
		strcpy(pr->book, p_temp->book);
		pr->year = p_temp->year;
		pr->pages = p_temp->pages;
		pr->price = p_temp->price;

		if (feof(ptr))
		{
			pr->next = NULL;
			break;
		}

		pd = (struct books*)malloc(sizeof(struct books));
		if (!pd) {
			printf("Error allocation!");
			return 0;
		}
		pd->next = NULL;
		pr->next = pd;
		pr = pd;
		counter++;
	}

	fclose(ptr);
	free(p_temp);
	p_temp = NULL;
	return counter;
}
void Delete(struct books** start)
{
	struct books* pr=NULL, * pd=NULL;
	pr = *start;
	while(1)
	{
		pd = pr->next;
		if (!pd)//якщо дійшли до останнього екземпляра - вихід
		{
			break;
		}
		if (pr->year > 2015)//якщо елемент стоїть на початку
		{
			if (pr)free(pr);
			pr = pd;
			*start = pd;

		}
		else if (pd->year > 2015)//якщо елемент стоїть на другій позиції
		{
			pr->next = pd->next;
			if (pd)free(pd);
		}
		else
		{
			(pr) ? pr = pr->next : 0;
		}
	}
}
void PlusNew(struct books** start, struct books* pp)
{
	struct books* pd=NULL, * pr=NULL;
	pr = *start;
	while(1)
	{
		pd = pr->next;
		int count = 0;
		while (pd->year > 1975 && (pd->next) != NULL)
		{
			pd = pd->next;
		}
		while (pr->next != pd)
		{
			pr = pr->next;
			count++;//якщо спочатку не сортовані книги, щоб новий елемент не вставився після першої не відсортованої
		}
		if (pd->next == NULL)
		{
			pr->next = pp;
			pp->next = pd;
			break;
		}
		else if (pp->price > pr->price && !count)
		{
			pp->next = pr;
			(*start) = pp;
			break;
		}
		else if (pp->price > pd->price)
		{
			pr->next = pp;
			pp->next = pd;
			break;
		}
		else
		{
			pr = pr->next;
		}
	}
}
void PrintList(struct books* pr)
{
	for (; pr->next != NULL;)
	{
		
		printf("%-10s %-10s %-15s %-7d %-7d %-6.2lf\n", pr->name, pr->surname, pr->book, pr->year, pr->pages, pr->price);
		pr = pr->next;
	}

}
void FreeMemory(struct books* pr )
{
	struct books* pd = NULL;
	for (;;)
	{
		if (pr->next == NULL)
		{
			if (pr)free(pr);
			break;
		}
		pd = pr->next;
		if (pr)free(pr);
		pr = pd;
	}
}
void LoadingToTxtFile(struct books* pr)
{
	FILE* pf = fopen("C:\\Проекти\\ВІПЗ\\Лаба 10\\listbooks.txt","wt");
	for (; pr->next != NULL;)
	{
		fprintf(pf,"%s %s %s %d %d %lf\n", pr->name, pr->surname, pr->book, pr->year, pr->pages, pr->price);
		pr = pr->next;
	}
}

void main(){
	int counter = 0;
	struct books* start = NULL;
	struct books* pr = (struct books*)malloc(sizeof(struct books));
	if (!pr)
	{
		printf("Error allocation");
		return;
	}

	start = pr;
	counter = ScaningAndCreatingList(pr);
	if (!counter)return;

	PrintList(pr);
	pr = NULL;

	pr = (struct books*)malloc(sizeof(struct books));
	if (!pr)
	{
		printf("Error allocation");
		return;
	}

	printf("Enter the author(name and surname), title, year of publication, number of pages and price:\n");
	scanf("%s %s %s %d %d %lf", &pr->name, &pr->surname, &pr->book, &pr->year, &pr->pages, &pr->price);
	PlusNew(&start, pr);
	pr = NULL;

	Delete(&start);
	pr = NULL;

	PrintList(start);

	LoadingToTxtFile(start);

	FreeMemory(start);
	start = NULL;
}