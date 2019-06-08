#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_BUCKETS 1000
#define MULTIPLIER 31
#define MAX_LEN    100

struct wordrec
{
    char* word;
    unsigned long count;
    struct wordrec* next;
};

/*
  @function walloc
  @desc     produces a new node
*/
struct wordrec* walloc(const char* str)
{
    struct wordrec* p=(struct wordrec*)malloc(sizeof(struct wordrec));
    if(p!=NULL)
    {
        p->count=0;
        p->word=strdup(str); /*creates a duplicate*/
        p->next=NULL;
    }
    return p;
}

/*hash bucket*/
struct wordrec* table[MAX_BUCKETS]; /* changed from MAX_LEN -- dsw */

/*
  @function hashstring
  @desc     produces hash code for a string
            multipliers 31,35 have been found to work well
*/
unsigned long hashstring(const char* str)
{
    unsigned long hash=0;
    while(*str)
    {
        hash= hash*MULTIPLIER+*str;
        str++;
    }
    return hash%MAX_BUCKETS;
}


/*
  @function lookup
  @desc     returns a pointer to the word or creates
            it if required
*/
struct wordrec*  lookup(const char* str,int create)
{
    struct wordrec* curr=NULL;
    unsigned long hash=hashstring(str);/*starting point*/
    struct wordrec* wp=table[hash];
    /* write code to
    follow the linked list to find str
    if found return pointer*/
    curr = wp;
    while (curr)
    {
        if (!strcmp(curr->word, str))
            return curr;
        else
        {
            curr = curr->next; 
        }
    }

  /*if not found and create specified*/
    if(create)
    {
        /* write code to  
         create new node
        update linked list*/
        curr = walloc(str);
        curr->count = 0;
        curr->next = table[hash];
        table[hash] = curr;
    }
    return curr;
}

/*
  @function cleartable()
  @desc     reclaims memory
*/
void cleartable()
{
    struct wordrec* wp=NULL,*p=NULL;
    int i=0;
    /*write code to
      reclaim memory 
    */
    for (i = 0; i < MAX_BUCKETS; i++)
    {
        wp = table[i];
        while (wp)
        {
            p = wp->next;
            free(wp->word);
            free(wp);
            wp = p;
        }
    }
}

int main(int argc,char* argv[])
{
    FILE* fp=fopen("book.txt","r");
    char  word[1024]; /*big enough*/
    struct wordrec* wp=NULL;
    int i=0;

    memset(table,0,sizeof(table));
    /*read from input*/
    while(1)
    {
        if(fscanf(fp,"%s",word)!=1)
            break;
        wp=lookup(word,1); /*create if doesn't exist*/
        wp->count++;
    }
    fclose(fp);

   /*
     print all words have frequency>100
   */
    for(i=0;i<MAX_BUCKETS;i++)
    {
        for(wp=table[i];wp!=NULL;wp=wp->next)
	    {
	        if(wp->count>1000)
	        {
	            printf("%s-->%ld\n",wp->word,wp->count);
	        }
	    }
    }
    cleartable();
    return 0;
}
