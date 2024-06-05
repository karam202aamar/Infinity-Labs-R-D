/******************************************************************************/
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include <stdlib.h>
/******************************************************************************/
#define FUNCS 2
#define NUM_OF_THREADS 8

#define TIMES 2
#define SIZE DICT_SIZE *TIMES
#define CHUNK (SIZE / NUM_OF_THREADS)

#define DICT_SIZE 102401

#define MAX 50
#define WORD_MAX 30
#define NSEC_PER_SEC 1000000000
/******************************************************************************/
enum{SUCCESS, FAILURE};
enum{LEFT, RIGHT, RANGE};
enum{INVALID = -1, NO_SWAP = 0, SWAPPED = 1};
/******************************************************************************/
typedef struct stuff
{
    char **input;
    char **part;
    int range[RANGE];
    int size;
    int choice;
} stuff_ty;

char *names[] = {"bubble sort results: \n", "selection sort results:\n"};
char funcs[] = {'1', '2'};
/******************************************************************************/
static void DictionarySetUp(char **dict);
static void DictionatyClose(char **dict);

static void StartTesting(char **dict);
static void ScrumbleDict(char **, char **);

static int RandomCmp(const void *, const void *);
static int RealCmp(const void *, const void *);
static int CharToInt(char c);
static int SetStuff(stuff_ty *, char **, int, int);
static int Merge(char **final, char **part, int final_size, int part_size, int size);

static int DoSort(char **input, size_t size, int sort_type);
static void *WhichSort(void *);

static void BubbleSort(char **, int);
static int BubbleHelperFunc(char **, int);
static void Swap(char **, char **);

static void SelectionSort(char **, int);
static int SelectionFindMin(char **, int);

static int CheckIfWork(char **, int);
void Timespec(struct timespec t1, struct timespec t2, struct timespec *td);
/******************************************************************************/
int main()
{
    char **dict = (char **)malloc(SIZE * (sizeof(char *)));

    if (NULL == dict)
    {
        printf("malloc failed\n");
    }

    DictionarySetUp(dict);
    StartTesting(dict);
    DictionatyClose(dict);

    return 0;
}
/******************************************************************************/
static void DictionarySetUp(char **dict)
{
    FILE *fptr = NULL;
    char buff[WORD_MAX] = {0};
    char *char_ptr = 0;
    int i = 0;

    fptr = fopen("/usr/share/dict/words", "r");

    for (i = 0; SIZE > i; ++i)
    {
        if (!fgets(buff, WORD_MAX, fptr))
        {
            break;
        }

        dict[i] = strdup(buff);
        char_ptr = dict[i];

        while (*char_ptr != '\n')
        {
            ++char_ptr;
        }
        *char_ptr = '\0';
    }
    fclose(fptr);
}
/******************************************************************************/
static void DictionatyClose(char **dict)
{
    int i = 0;

    for (i = 0; DICT_SIZE > i; ++i)
    {
        free(dict[i]);
        dict[i] = NULL;
    }
}
/******************************************************************************/
static void StartTesting(char **dict)
{
    int i = 0;
    char *scrumbled[SIZE] = {0};
    struct timespec start_t = {0};
    struct timespec finish_t = {0};
    struct timespec delta_t = {0};

    memcpy(scrumbled, dict, DICT_SIZE * sizeof(char *));

    for (i = 0; FUNCS > i; ++i)
    {
        ScrumbleDict(dict, scrumbled);

        printf("%s", names[i]);
        clock_gettime(CLOCK_REALTIME, &start_t);

        if (DoSort(scrumbled, SIZE, funcs[i]))
        {
            printf("Sort failed\n");
        }

        clock_gettime(CLOCK_REALTIME, &finish_t);

        Timespec(start_t, finish_t, &delta_t);

        if (CheckIfWork(scrumbled, SIZE))
        {
            printf("arr not sorted\n");
            fflush(stdout);
        }
        else
        {
            printf("arr is sorted\n");
        }

        printf("\nsorting time:\n");
        printf("%d.%.9ld\n", (int)delta_t.tv_sec, delta_t.tv_nsec);
    }
}
/******************************************************************************/
static void ScrumbleDict(char **dict, char **scrumbled)
{
    int i = 0;

    qsort(scrumbled, DICT_SIZE, sizeof(char *), RandomCmp);

    for (i = DICT_SIZE; SIZE > i; ++i)
    {
        scrumbled[i] = scrumbled[i % DICT_SIZE];
    }
}
/******************************************************************************/
static int DoSort(char **input, size_t size, int sort_type)
{
    pthread_t tid[NUM_OF_THREADS] = {0};
    stuff_ty stuff[NUM_OF_THREADS] = {{0}};
    char **output = NULL;
    int i = 0, merge_size = 0;

    if (SetStuff(stuff, input, (int)size, sort_type))
    {
        printf("set stuff failed\n");

        return FAILURE;
    }

    for (i = 0; NUM_OF_THREADS > i; ++i)
    {
        if (pthread_create(&tid[i], NULL, WhichSort, &stuff[i]))
        {
            printf("pthread creation failed ");
            return FAILURE;
        }
    }
    output = (char **)calloc(size, sizeof(char *));

    if (!output)
    {
        return FAILURE;
    }

    for (i = 0; NUM_OF_THREADS > i; ++i)
    {
        if (pthread_join(tid[i], NULL))
        {
            printf("pthread join failed\n");
            return FAILURE;
        }

        merge_size += stuff[i].size;

        if (Merge(output, stuff[i].part, merge_size, stuff[i].size, 
                                                    merge_size - stuff[i].size))
        {
            printf("merge failed\n");
            return FAILURE;
        }

        free(stuff[i].part);
        stuff[i].part = NULL;
    }

    memcpy(input, output, size * sizeof(char *));

    free(output);
    output = NULL;

    return SUCCESS;
}
/******************************************************************************/
static int SetStuff(stuff_ty *stuff, char **input, int size, int choice)
{
    int i = 0;

    stuff[0].choice = choice;
    stuff[0].input = input;
    stuff[0].part = (char **)calloc(CHUNK, sizeof(char *));

    if (!stuff[0].part)
    {
        return FAILURE;
    }

    stuff[0].range[LEFT] = 0;
    stuff[0].range[RIGHT] = CHUNK - 1;
    stuff[0].size = CHUNK;

    for (i = 1; NUM_OF_THREADS > i; ++i)
    {
        stuff[i].choice = choice;
        stuff[i].input = input;

        if ((NUM_OF_THREADS - 1) == i)
        {
            stuff[i].range[LEFT] = stuff[i - 1].range[RIGHT] + 1;
            stuff[i].range[RIGHT] = size - 1;
            stuff[i].size = stuff[i].range[RIGHT] - stuff[i].range[LEFT] + 1;
        }
        else
        {
            stuff[i].range[LEFT] = stuff[i - 1].range[RIGHT] + 1;
            stuff[i].range[RIGHT] = stuff[i].range[LEFT] + CHUNK;
            stuff[i].size = stuff[i].range[RIGHT] - stuff[i].range[LEFT] + 1;
        }

        stuff[i].part = (char **)calloc(stuff[i].size, sizeof(char *));

        if (!stuff[i].part)
        {
            return FAILURE;
        }
    }
    return SUCCESS;
}
/******************************************************************************/
static void *WhichSort(void *arg)
{
    int i = 0;
    int j = 0;
    stuff_ty *stuff = ((stuff_ty *)(arg));
    int left = stuff->range[LEFT];
    int right = stuff->range[RIGHT];
    char **input = stuff->input;
    char **part = stuff->part;
    
    for (i = left; right >= i; ++i, ++j)
    {
        part[j] = input[i];
    }
    switch (stuff->choice)
    {
        case '1':
            BubbleSort(part, stuff->size);
            break;
        case '2':
            SelectionSort(part, stuff->size);
            break;
        default:
            break;
    }
    return NULL;
}
/******************************************************************************/
static void BubbleSort(char **arr, int size)
{
    int swapped = NO_SWAP;
    do
    {
        swapped = BubbleHelperFunc(arr, size);

    } while (SWAPPED == swapped);
}
/******************************************************************************/
static int BubbleHelperFunc(char **arr, int size)
{
    int i = 0;
    int swapped = NO_SWAP;

    for (i = 0; i < size - 1; ++i)
    {
        if (CharToInt(*arr[i]) > CharToInt(*arr[i + 1]))
        {
            Swap(&arr[i], &arr[i + 1]);
            swapped = SWAPPED;
        }
    }
    return swapped;
}
/******************************************************************************/
static void Swap(char **a, char **b)
{
    char *temp = *a;
    *a = *b;
    *b = temp;
}
/******************************************************************************/
static void SelectionSort(char **arr, int size)
{
    int min_idx = INVALID;
    int next_swap_idx = 0;
    do
    {
        min_idx = SelectionFindMin(&arr[next_swap_idx], size - next_swap_idx);
        min_idx += next_swap_idx;
        if (min_idx != next_swap_idx)
        {
            Swap(&arr[min_idx], &arr[next_swap_idx]);
        }
        ++next_swap_idx;
    } while (next_swap_idx != (size - 1));
}
/******************************************************************************/
static int SelectionFindMin(char **arr, int size)
{
    int i = 0;
    int min = MAX;
    int min_idx = INVALID;

    for (; size > i; ++i)
    {
        if (min > CharToInt(*arr[i]))
        {
            min = CharToInt(*arr[i]);
            min_idx = i;
        }
    }
    return min_idx;
}
/******************************************************************************/
static int CharToInt(char c)
{
    int i = MAX - 1;

    if ('a' <= c && c <= 'z')
    {
        i = c - 'a';
    }
    else if ('A' <= c && c <= 'Z')
    {
        i = c - 'A';
    }
    return i;
}
/******************************************************************************/
static int CheckIfWork(char **arr, int size)
{
    int i = 0;

    for (i = 1; size > i; ++i)
    {
        if (CharToInt(*arr[i]) < CharToInt(*arr[i - 1]))
        {
            return FAILURE;
        }
    }
    return SUCCESS;
}
/******************************************************************************/
static int Merge(char **final, char **part, int size, int part_size, int final_size)
{
    int t = 0;
    int f = 0;
    int p = 0;
    char **temp = (char **)calloc(size, sizeof(char *));

    if (!temp)
    {
        return FAILURE;
    }
    while (size > t && final_size > f && part_size > p)
    {
        if (CharToInt(*final[f]) > CharToInt(*part[p]))
        {
            temp[t] = part[p];
            ++p;
        }
        else
        {
            temp[t] = final[f];
            ++f;
        }
        ++t;
    }
    while (final_size > f && size > t)
    {
        temp[t] = final[f];
        ++f;
        ++t;
    }
    while (part_size > p && size > t)
    {
        temp[t] = part[p];
        ++p;
        ++t;
    }
    for (t = 0; size > t && temp[t]; ++t)
    {
        final[t] = temp[t];
    }

    free(temp);
    temp = NULL;

    return SUCCESS;
}
/******************************************************************************/
static int RealCmp(const void *one, const void *two)
{
    return CharToInt(**(char **)one) - CharToInt(**(char **)two);
}
/******************************************************************************/
static int RandomCmp(const void *one, const void *two)
{
    return rand() % 2;
}
/******************************************************************************/
void Timespec(struct timespec t1, struct timespec t2, struct timespec *td)
{
    td->tv_nsec = t2.tv_nsec - t1.tv_nsec;
    td->tv_sec = t2.tv_sec - t1.tv_sec;

    if (td->tv_sec > 0 && td->tv_nsec < 0)
    {
        td->tv_nsec += NSEC_PER_SEC;
        td->tv_sec--;
    }
    else if (td->tv_sec < 0 && td->tv_nsec > 0)
    {
        td->tv_nsec -= NSEC_PER_SEC;
        td->tv_sec++;
    }
}
/******************************************************************************/
