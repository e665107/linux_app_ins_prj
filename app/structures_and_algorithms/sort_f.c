#include <stdio.h>
#include <stdlib.h>

#define USE_NONRECURSIVE
#define N 50

/* bucketsort */
#define LIMIT 20
#define BUCKETSIZE 10
#define MAP(x) (x/2)
/* #define BUCKETSORT */
struct List
{
    int item;
    struct List *next;
};

struct Listhead
{
    struct List *head;
};
/* bucketsort */

/* countsort */
#define LIMIT 20
/* countsort */


/* radixsort_baseon_bucket_sort */
int getvalue(int number, int pos)
{
    while (pos > 1)
    {
        number = number / 10;
        pos--;
    }

    number %= 10;
    return number;
}

static void swap(int *data, int pos1, int pos2)
{
    int tmp = *(data + pos1);
    *(data + pos1) = *(data + pos2);
    *(data + pos2) = tmp;
}

static void bubblesort(int *data, int size)
{
    int i, j;

    for (i = 0; i < size - 1; i++)
        for (j = i + 1; j < size; j++)
            if (*(data + i) > *(data + j))
                swap(data, i, j);  /* put the bit num right */
}

static void displayoutcome(int *data, int size)
{
    int i;

    for (i = 0; i < size; i++)
        printf("%d ", *(data + i));

    printf("\n");
}

static void bubblesort_1(int *data, int size)
{
    int flag = 1;
    int i;
    int k = size;

    while (flag)
    {
        k--;
        flag = 0;

        for (i = 0; i < k; i++)
            if (data[i] > data[i + 1])
            {
                swap(data, i, i + 1);
                flag = 1;
            }
    }
}

static void bubble_t()
{
    /*
      时间复杂度:O(n^2)
      空间复杂度:O(1)
      思路:对于每个位置，找到最小元素；一次循环后对应位置的数一定是当前最小的。
    */
    int data[] = {60, 2, 97, 78, 0, 84, 68, 23, 48, 22, 63, 31, 43, 42, 82, 9,
                  57, 21, 42, 62, 83, 98, 64, 72, 96, 31, 76, 13, 70, 49, 10, 60, 72, 36,
                  26, 4, 56, 54, 13, 9, 98, 45, 61, 90, 88, 80, 30, 50, 77, 83,
    };
    int size = sizeof(data) / sizeof(int);
    /* bubblesort(data, size); */
    bubblesort_1(data, size);
    displayoutcome(data, size);
    exit(0);
}

/*
  思路:从第二个元素开始，不断前移, O(n2)。
*/
static void insertsort(int *data, int size)
{
    int i, j;
    int tmp;

    for (i = 1; i < size; i++)
    {
        tmp = *(data + i);

        for (j = i; j > 0 && *(data + j - 1) > tmp; j--)
            *(data + j) = *(data + j - 1);

        *(data + j) = tmp;
    }
}

static void insert_t()
{
    int data[] = {60, 2, 97, 78, 0, 84, 68, 23, 48, 22, 63, 31, 43, 42, 82, 9,
                  57, 21, 42, 62, 83, 98, 64, 72, 96, 31, 76, 13, 70, 49, 10, 60, 72, 36,
                  26, 4, 56, 54, 13, 9, 98, 45, 61, 90, 88, 80, 30, 50, 77, 83,
    };
    int size = sizeof(data) / sizeof(int);
    insertsort(data, size);
    displayoutcome(data, size);
    exit(0);
}

/*
  思路:对于每个位置，依次选出此位置到尾端之间最小的数，然后放在当前位置。
*/
static void selectsort(int *data, int size)
{
    int min, minpos = -1;
    int i, j;

    for (i = 0; i < size - 1; i++)
    {
        min = *(data + i);
        minpos = i;

        for (j = i + 1; j < size; j++)
            if (*(data + j) < min)
            {
                min = *(data + j);
                minpos = j;
            }

        if (minpos != i)
            swap(data, i, minpos);
    }
}

static void select_t()
{
    int data[] = {60, 2, 97, 78, 0, 84, 68, 23, 48, 22, 63, 31, 43, 42, 82, 9,
                  57, 21, 42, 62, 83, 98, 64, 72, 96, 31, 76, 13, 70, 49, 10, 60, 72, 36,
                  26, 4, 56, 54, 13, 9, 98, 45, 61, 90, 88, 80, 30, 50, 77, 83,
    };
    int size = sizeof(data) / sizeof(int);
    selectsort(data, size);
    displayoutcome(data, size);
    exit(0);
}

int hibbard[] = {1, 3, 5};

static void shellsort(int *data, int size)
{
    int step, stepsp = sizeof(hibbard) / sizeof(int) -1;
    int i, j, tmp;

    while (stepsp >= 0)
    {
        step = hibbard[stepsp--];

        for (i = step; i < size; i++)
        {
            tmp = data[i];

            for (j = i; j >= step && data[j - step] > tmp; j -= step)
                data[j] = data[j - step];

            data[j] = tmp;
        }

        displayoutcome(data, size);
    }
}

/*
  思路:对于每个位置，找到最小元素；一次循环后对应位置的数一定是当前最小的。

*/
static void shell_t()
{
    int data[] = {81, 94, 11, 96, 12, 35, 17, 95, 28, 58, 41, 75, 15};
    int size = sizeof(data) / sizeof(int);
    shellsort(data, size);
    displayoutcome(data, size);
    exit(0);
}

/*
  heap sort
*/
static void heap_hold(int *data, int heapsize, int pos)
{
    int left = (pos << 1) + 1, right = (pos << 1) + 2, minpos = pos;

    if (right < heapsize && data[right] < data[minpos])
        minpos = right;

    if (left < heapsize && data[left] < data[minpos])
        minpos = left;

    if (minpos != pos)
    {
        swap(data, minpos, pos);
        heap_hold(data, heapsize, minpos);
    }
}

static void init_heap(int *data, int heapsize)
{
    int lasthasleaf = (heapsize >> 1) - 1;

    for (int i = lasthasleaf; i >= 0; i--)
        heap_hold(data, heapsize, i);
}

static int delete_min(int *data, int *heapsize)
{
    int top = data[0];
    swap(data, 0, *heapsize - 1);
    *heapsize = *heapsize - 1;
    heap_hold(data, *heapsize, 0);
    return top;
}

void heap_sort_t()
{
    int data[] = {81, 94, 11, 96, 12, 35, 17, 95, 28, 58, 41, 75, 15};
    int size = sizeof(data) / sizeof(int);
    int heapsize;
    heapsize = size;
    //create heap
    init_heap(data, heapsize);

    //get min
    for (int i = 0; i < size; i++)
        delete_min(data, &heapsize);

    //printf
    for (int i = size - 1; i >= 0; i--)
        printf("%d ", data[i]);

    printf("\n");
    exit(0);
}

static void merge(int *data, int head, int mid, int rear)
{
    int copydata[N], sp = -1;
    int i = head, j = mid;

    while (i < mid && j < rear)
        if (data[i] <= data[j])
            copydata[++sp] = data[i++];

        else
            copydata[++sp] = data[j++];

    while (i < mid)
        copydata[++sp] = data[i++];

    while (j < rear)
        copydata[++sp] = data[j++];

    for (i = head; i < rear; i++)
        data[i] = copydata[i - head];
}

static void mergesort_recursive(int *data, int head, int rear)
{
    if (head >= rear - 1)
        return;

    int mid = (head + rear) / 2;
    mergesort_recursive(data, head, mid);
    mergesort_recursive(data, mid, rear);
    merge(data, head, mid, rear);
}

static void mergesort_nonrecursive(int *data, int size)
{
    int subsize, i;
    int head, mid, rear;

    for (subsize = 2; subsize < size * 2; subsize *= 2)
    {
        for (i = 0; i < size; i += subsize)
        {
            head = i;
            mid = head + subsize / 2;
            rear = head + subsize;

            if (rear > size)
                rear = size;

            merge(data, head, mid, rear);
        }
    }
}

void merger_sort_t()
{
    /*
      时间复杂度:O(n)
      空间复杂度:O()
      适用于属于一定范围内的数的排序。
      思路:。
    */
    int data[] = {60, 2, 97, 78, 0, 84, 68, 23, 48, 22, 63, 31, 43, 42, 82, 9,
                  57, 21, 42, 62, 83, 98, 64, 72, 96, 31, 76, 13, 70, 49, 10, 60, 72, 36,
                  26, 4, 56, 54, 13, 9, 98, 45, 61, 90, 88, 80, 30, 50, 77, 83,
    };
    int size = sizeof data / sizeof * data;
#ifdef USE_RECURSIVE
    printf("use recursive\n");
    mergesort_recursive(data, 0, size);
#elif defined(USE_NONRECURSIVE)
    printf("use non recursive\n");
    mergesort_nonrecursive(data, size);
#endif
    displayoutcome(data, size);
}

void quicksort(int *data, int head, int rear)
{
    if (head >= rear)
        return ;

    int pivot = *(data + head);
    int first_bigger = head + 1;

    for (int i = head; i < rear; i++)
        if (data[i] < pivot)
            swap(data, i, first_bigger++);

    swap(data, head, first_bigger - 1);
    quicksort(data, head, first_bigger - 1);
    quicksort(data, first_bigger, rear);
}

void quick_sort_t()
{
    /*
      时间复杂度:O(n)
      空间复杂度:O()
      适用于属于一定范围内的数的排序。
      思路:。
    */
    int data[] = {60, 2, 97, 78, 0, 84, 68, 23, 48, 22, 63, 31, 43, 42, 82, 9,
                  57, 21, 42, 62, 83, 98, 64, 72, 96, 31, 76, 13, 70, 49, 10, 60, 72, 36,
                  26, 4, 56, 54, 13, 9, 98, 45, 61, 90, 88, 80, 30, 50, 77, 83,
    };
    int size = sizeof data / sizeof * data;
    quicksort(data, 0, size);
    displayoutcome(data, size);
}

static void bucket_init(struct Listhead **buckets, int bucketsize)
{
    int i;

    for (i = 0; i < bucketsize; i++)
    {
        buckets[i] = malloc(sizeof(struct Listhead));
        buckets[i]->head = NULL;
    }
}

static void list_add(struct Listhead **buckets, int item, int position)
{
    printf("%d save in %d\n", item, position );
    struct Listhead *list = buckets[position];
    struct List *new = malloc(sizeof(struct List));
    new->item = item;
    new->next = NULL;

    if (list->head)
    {
        struct List *current = list->head, *prev = NULL;

        while (current)
        {
            if (current->item >= item)
            {
                new->next = current;

                if (prev)
                    prev->next = new;

                else
                    list->head = new;

                break;
            }

            prev = current;
            current = current->next;
        }

        if (prev)
            prev->next = new;
    }

    else
        list->head = new;
}


#ifdef BUCKETSORT
static void bucket_add(struct Listhead **buckets, int item)
{
    list_add(buckets, item, MAP(item));
}
#else
void bucket_add(struct Listhead **buckets, int item, int pos)
{
    int newmap = getvalue(item, pos);
    list_add(buckets, item, MAP(newmap));
}
#endif


static void bucket_scan(struct Listhead **buckets, int *data, int bucketsize)
{
    int sp = -1, i, nowvalue;
    struct List *list;

    for (i = 0; i < bucketsize; i++)
    {
        list = buckets[i]->head;

        while (list)
        {
            nowvalue = list->item;
            printf("nowvalue=%d\n", nowvalue);
            data[++sp] = nowvalue;
            list = list->next;
        }
    }
}

#ifdef BUCKETSORT
void bucketsort(int *data, int size)
{
    struct Listhead *buckets[BUCKETSIZE];
    bucket_init(buckets, BUCKETSIZE);
    int i;

    for (i = 0; i < size; i++)
    {
        printf("add %d\n", data[i] );
        bucket_add(buckets, data[i]);
    }

    bucket_scan(buckets, data, BUCKETSIZE);
}
#else
void bucketsort(int *data, int size, int pos)
{
    struct Listhead *buckets[BUCKETSIZE];
    bucket_init(buckets, BUCKETSIZE);
    int i;

    for (i = 0; i < size; i++)
        bucket_add(buckets, data[i], pos);

    bucket_scan(buckets, data, BUCKETSIZE);
}
#endif

void bucket_sort_t()
{
    /*
      时间复杂度:O(n)
      空间复杂度:O()
      适用于属于一定范围内的数的排序。
      思路:。
    */
    int data[] = {5, 4, 3, 19, 3, 9, 16, 15, 0,
                  0, 9, 12, 9, 10, 10, 4, 19, 15, 12, 16,
                  0, 0, 1, 1, 3, 4, 14, 3, 6, 12, 1, 3, 14,
                  4, 15, 4, 4, 7, 11, 13, 2, 1, 15, 13, 1,
                  12, 9, 17, 13, 16,
    };
    int size = sizeof(data) / sizeof(int);
#ifdef BUCKETSORT
    bucketsort(data, size);
#endif // MACRO
    displayoutcome(data, size);
}

void countsort(int *data, int size)
{
    int counts[LIMIT] = {}, i;
    int datacopy[size];

    for (i = 0; i < size; i++)
    {
        counts[data[i]]++;
        datacopy[i] = data[i];
    }

    for (i = 1; i < LIMIT; i++)
        counts[i] += counts[i - 1];

    for (i = size - 1; i >= 0; i--)
        data[--counts[datacopy[i]]] = datacopy[i];
}


void count_sort_t()
{
    int data[] = {5, 4, 3, 19, 3, 9, 16, 15, 0,
                  0, 9, 12, 9, 10, 10, 4, 19, 15, 12, 16,
                  0, 0, 1, 1, 3, 4, 14, 3, 6, 12, 1, 3, 14,
                  4, 15, 4, 4, 7, 11, 13, 2, 1, 15, 13, 1,
                  12, 9, 17, 13, 16,
    };
    int size = sizeof(data) / sizeof(int);
    countsort(data, size);
    displayoutcome(data, size);
}


void radix_sort(int *data, int size, int digitsize)
{
    int i;

    for (i = 1; i <= digitsize; i++)
        bucketsort(data, size, i);
}


void radix_sort_t()
{
    int data[] = {64, 8, 216, 512, 27, 729, 0, 1, 343, 125, 93};
    int size = sizeof(data) / sizeof(int);
    radix_sort(data, size, 3);
    displayoutcome(data, size);
}

/* quicksort_k_small */
static void quicksplit_findtopk_small(int *data, int head, int rear, int k)
{
    //找出最小的K个
    if (head >= rear)
        return;

    int pivot = data[rear - 1];
    int i = head, j = rear - 2;

    while (i <= j)
    {
        while (i <= rear - 2 && data[i] < pivot)
            i++;

        while (j >= 0 && data[j] >= pivot)
            j--;

        if (i < j)
            swap(data, i, j);
    }

    swap(data, i, rear - 1);

    if (i > k)
        quicksplit_findtopk_small(data, head, i, k);

    else if (i < k)
        quicksplit_findtopk_small(data, i + 1, rear, k);

    else
    {
        int j = 0;

        while (j < i)
            printf("%d ", data[j++]);

        printf("\n");
    }
}

static void quicksplit_find_kth_min(int *data, int head, int rear, int k)
{
    if (head >= rear)
        return;

    int pivot = data[rear - 1];
    int i = head, j = rear - 2;

    while (i <= j)
    {
        while (i <= rear - 2 && data[i] < pivot)
            i++;

        while (j >= 0 && data[j] >= pivot)
            j--;

        if (i < j)
            swap(data, i, j);
    }

    swap(data, i, rear - 1);

    if (i > k - 1)
        quicksplit_find_kth_min(data, head, i, k);

    else if (i < k - 1)
        quicksplit_find_kth_min(data, i + 1, rear, k);

    else
        printf("%dth minest number=%d\n", k, pivot);
}

static void quicksplit_findtopk_big(int *data, int head, int rear, int k)
{
    //找出最大的K个
    if (head >= rear)
        return;

    int pivot = data[rear - 1];
    int i = head, j = rear - 2;

    while (i <= j)
    {
        while (i <= rear - 2 && data[i] < pivot)
            i++;

        while (j >= 0 && data[j] >= pivot)
            j--;

        if (i < j)
            swap(data, i, j);
    }

    swap(data, i, rear - 1);

    if (k > N - i - 1)
        quicksplit_findtopk_big(data, head, i, k);

    else if (k < N - i - 1)
        quicksplit_findtopk_big(data, i + 1, rear, k);

    else
    {
        int j = i + 1;

        while (j < N)
            printf("%d ", data[j++]);

        printf("\n");
    }
}

static void quicksplit_find_kth_max(int *data, int head, int rear, int k)
{
    if (head >= rear)
        return;

    int pivot = data[rear - 1];
    int i = head, j = rear - 2;

    while (i <= j)
    {
        while (i <= rear - 2 && data[i] < pivot)
            i++;

        while (j >= 0 && data[j] >= pivot)
            j--;

        if (i < j)
            swap(data, i, j);
    }

    swap(data, i, rear - 1);

    if (k > N - i)
        quicksplit_find_kth_max(data, head, i, k);

    else if (k < N - i)
        quicksplit_find_kth_max(data, i + 1, rear, k);

    else
        printf("%dth maxest number=%d\n", k, pivot);
}

void quicksort_k_t()
{
    int data[] = {60, 2, 97, 78, 0, 84, 68, 23, 48, 22, 63, 31, 43, 42, 82, 9,
                  57, 21, 42, 62, 83, 98, 64, 72, 96, 31, 76, 13, 70, 49, 10, 60, 72, 36,
                  26, 4, 56, 54, 13, 9, 98, 45, 61, 90, 88, 80, 30, 50, 77, 83,
    };
    int size = sizeof(data) / sizeof(int);
    int k = atoi("10");  /* 10代表要打印的最小数的个数 */

    if (k > size)
        k = size;

    /* quicksplit_find_kth_min(data, 0, size, k); */
    quicksplit_find_kth_max(data, 0, size, k);

    if (k == size)
        k--;

    printf("top%d minest numbers:\n", k);
    quicksplit_findtopk_big(data, 0, size, k);
}

void sort_t()
{
    /* bubble_t(); */
    /* insert_t(); */
    /* select_t(); */
    /* shell_t(); */
    /* heap_sort_t(); */
    /* merger_sort_t(); */
    /* bucket_sort_t(); */
    /* count_sort_t(); */
    /* radix_sort_t(); */
    quicksort_k_t();
    exit(0);
}
















