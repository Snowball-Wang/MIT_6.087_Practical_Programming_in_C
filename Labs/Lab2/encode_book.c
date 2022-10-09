#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SYMBOLS 255
#define MAX_LEN     32

typedef unsigned char uchar;

struct tnode
{
    struct tnode* left;    /* used when in tree */
    struct tnode* right;   /* used when in tree */
    struct tnode* parent;  /* used when in tree */
    struct tnode* next;    /* used when in list */
    long freq;
    int isleaf;
    uchar symbol;    
};

/* global variables */
char code[MAX_SYMBOLS][MAX_LEN];
int freq[MAX_SYMBOLS] = {0};
struct tnode* root = NULL;    /* tree of symbols */
struct tnode* qhead = NULL;   /* list of current symbols */

/*
    @function   talloc
    @desc       allocates new node
*/
struct tnode* talloc(uchar symbol, long freq)
{
    struct tnode* p = (struct tnode*)malloc(sizeof(struct tnode));
    if (p != NULL)
    {
        p->left = p->right = p->parent = p->next = NULL;
        p->symbol = symbol;
        p->freq = freq;
        p->isleaf = 1;
    }
    return p;
}

/*
    @function   pg_display
    @desc       displays the constructed priority queue
*/
void pq_display(struct tnode* head)
{
    struct tnode* p = NULL;
    printf("list: ");
    for (p = head; p != NULL; p = p->next)
    {
        printf("(%x, %ld) ", p->symbol, p->freq);
    }
    printf("\n");
}

/*
    @function   pq_insert
    @desc       inserts an element into the priority queue
*/
void pq_insert(struct tnode* p)
{
    struct tnode* curr = NULL;
    /* qhead is NULL */
    if (qhead == NULL)
        qhead = curr = p;
    else
    {
        /* new node's freq is less than head node */
        if (p->freq <= qhead->freq)
        {
            p->next = qhead;
            qhead = p;
        }
        else
        {
            curr = qhead;
            while (curr->next != NULL && curr->next->freq < p->freq)
            {
                curr = curr->next;
            }
            /* either at the end of the list or at required position */
            p->next = curr->next;
            curr->next = p;
        }
    }
}

/*
    @function   pq_pop
    @desc       pops out the head element
*/
struct tnode* pq_pop()
{
    struct tnode* p = NULL;
    p = qhead;
    if (p != NULL)
    {
        qhead = p->next;
    }
    return p;
}

/*
    @function   generate_code
    @desc       generates the string code given the huffman tree
*/
void generate_code(struct tnode* root, int depth)
{
    int symbol;
    int len;

    if (root->isleaf)
    {
        symbol = root->symbol;
        len = depth;
        /* follow parent pointer to the root to generate the code string */
        code[symbol][len] = '\0';
        for (int i = len - 1; i >= 0; i--)
        {
            if (root == root->parent->left)
                code[symbol][i] = '0';
            else
                code[symbol][i] = '1';
            root = root->parent;
        }
    }
    else
    {
        generate_code(root->left, depth+1);
        generate_code(root->right, depth+1);
    }
}

/*
    @function   dump_code
    @desc       output code file
*/
void dump_code(FILE* fp)
{
    int i = 0;
    for (i = 0; i < MAX_SYMBOLS; i++)
    {
        /* non empty */
        if (code[i][0])
            fprintf(fp, "%x %s\n", i, code[i]);
    }
}

/*
    @function   encode
    @desc       outputs compressed stream
*/
void encode(FILE *fin, FILE* fout)
{
    int ch;
    while ((ch = fgetc(fin)) != EOF)
        fprintf(fout, "%s", code[ch]);

}

/*
    @function   getfreq
    @desc       generate the frequency of occurrence for each letter
*/
long getfreq(FILE* fp)
{
    int ch;
    long sum = 0;
    
    while ((ch = fgetc(fp)) != EOF)
    {
        freq[ch]++;
        sum++;
    }
    return sum;
}

/*
    @function   freetree
    @desc       cleans up resources for tree
*/
void freetree(struct tnode* root)
{
    if (root == NULL)
        return;
    freetree(root->left);
    freetree(root->right);
    free(root);
}

int main()
{
    /* the number of letters in book.txt */
    int letter_num = 0;

    const char *INPUT_FILE = "book.txt";
    const char *CODE_FILE = "book_code.txt";
    const char *RESULT_FILE = "book_encoded.txt";
    FILE* in;

    /* open book.txt */
    in = fopen(INPUT_FILE, "r");
    if (!in)
    {
        fprintf(stderr, "Fail to open book.txt\n");
        abort();
    }

    /* get the freq */
    long sum = getfreq(in);
    printf("Total characters: %ld\n", sum);
    fclose(in);

    /* build the priority queue */
    qhead = NULL;
    for (int i = 0; i < MAX_SYMBOLS; i++)
    {
        if (freq[i] != 0)
        {
            pq_insert(talloc(i, freq[i]));
            letter_num++;
        }
    }

    /* display the priority queue */
    pq_display(qhead);

    /* build the huffman tree */
    struct tnode* p = NULL;
    struct tnode* lc, *rc;
    for (int i = 0; i < letter_num - 1; i++)
    {
        lc = pq_pop();
        rc = pq_pop();
        /* create parent node */
        p = talloc(0, lc->freq + rc->freq);
        /* set parent link */
        lc->parent = rc->parent = p;
        /* set child link */
        p->left = lc;
        p->right = rc;
        /* make it non-leaf */
        p->isleaf = 0;
        /* add the new node to the priority queue */
        pq_insert(p);
    }

    /* build string code */
    memset(code, 0, sizeof(code));
    root = pq_pop();
    generate_code(root, 0);

    /* output string code */
    //puts("code:");
    FILE* out = fopen(CODE_FILE, "w");
    if (!out)
    {
        fprintf(stderr, "Fail to open book_code.txt\n");
        abort();
    }
    //dump_code(stdout);
    dump_code(out);

    /* encode book.txt */
    /* reopen book.txt */
    in = fopen(INPUT_FILE, "r");
    if (!in)
    {
        fprintf(stderr, "Fail to open book.txt\n");
        abort();
    }
    /* open book_encoded.txt to store code string */
    FILE* result = fopen(RESULT_FILE, "w");
    if (!result)
    {
        fprintf(stderr, "Fail to open book_encoded.txt\n");
        abort();
    }
    encode(in, result);

    fclose(in);
    fclose(out);
    fclose(result);

    getchar();

    /* reopen book_encoded.txt to calculate compression ratio */
    result = fopen(RESULT_FILE, "r");
    if (!result)
    {
        fprintf(stderr, "Fail to open book_encoded.txt\n");
        abort();
    }
    long bits_encoded = getfreq(result);
    printf("Original Bits: %ld\n", sum * 8);
    printf("Encoded Bits: %ld\n", bits_encoded);
    printf("Compression Ratio: %.4f\n", (sum * 8)/(float)bits_encoded);

    /* clear resources */

    freetree(root);

    return 0;
}
