#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<stdbool.h>
#include<string.h>

typedef struct {
    long compare_count;     //关键字比较次数
    long move_count;        //关键字移动次数
    double time_spent;      //排序时间（秒）
    bool is_stable;         //是否稳定
}SortStats;

//辅助函数：交换两个元素
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

//直接插入排序(从小到大)
void insertion_sort(int arr[], int n, SortStats *stats)
{
    stats->compare_count = 0;
    stats->move_count = 0;
    for(int i = 1; i < n; i++)
    {
        int key = arr[i];
        stats->move_count++;    //取出key算一次移动
        int j = i - 1;
        while (j >= 0)
        {
            stats->compare_count++;
            if(arr[j] > key)
            {
                arr[j + 1] = arr[j];
                stats->move_count++;
                j--;
            }
            else{
                break;
            }
        }
        arr[j + 1] = key;
        stats->move_count++;    //插入key算一次移动
        
    }
    stats->is_stable = true;
}

//冒泡排序
void bubble_sort(int arr[], int n, SortStats *stats)
{
    stats->compare_count = 0;
    stats->move_count = 0;
    for(int i = 0;i < n - 1; i++)
    {
        bool swapped = false;
        for(int j = 0; j< n - 1; j++)
        {
            stats->compare_count++;
            if(arr[j] > arr[j + 1])
            {
                swap(&arr[j], &arr[j+1]);
                stats->move_count += 3;     //交换算三次移动
                swapped = true;
            }
        }
        if(!swapped) break;;
    }
    stats->is_stable = true;
}

//快速排序的分割函数
int partition(int arr[], int low, int high, SortStats *stats)
{
    int pivot = arr[high];
    int i = low - 1;
    for(int j = low; j < high; j++)
    {
        stats->compare_count++;
        if(arr[j] < pivot)
        {
            i++;
            swap(&arr[j], &arr[i]);
            stats->move_count += 3;
        }
    }
    swap(&arr[i + 1], &arr[high]);
    stats->move_count += 3;
    return i + 1;
}

//快速排序递归函数
void quick_sort(int arr[], int low, int high, SortStats *stats)
{
    if(low < high)
    {
        int pivot = partition(arr, low, high, stats);
        quick_sort(arr, low, pivot - 1, stats);
        quick_sort(arr, pivot + 1, high, stats);
    }
}

//快速排序入口
void quick_sort_entrance(int arr[], int n, SortStats *stats)
{
    stats->compare_count = 0;
    stats->move_count = 0;
    quick_sort(arr, 0, n - 1, stats);
    stats->is_stable = false;
}

//简单选择排序
void selection_sort(int arr[], int n, SortStats *stats)
{
    stats->compare_count = 0;
    stats->move_count = 0;
    for(int i = 0; i < n - 1; i++)
    {
        int min_idx = i;
        for(int j = i + 1; j < n ;j++)
        {
            stats->compare_count++;
            if(arr[j] < arr[min_idx])
            {
                min_idx = j;
            }
        }
        if(min_idx != i){
            swap(&arr[min_idx], &arr[i]);
            stats->move_count += 3;
        }
    }
    stats->is_stable = false;
}

//堆排序的堆调整函数
void heapify(int arr[], int n, int i, SortStats *stats)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if(left < n)
    {
        stats->compare_count++;
        if(arr[left] > arr[largest]){
            largest = left;
        }
    }
    if(right < n)
    {
        stats->compare_count++;
        if(arr[right] > arr[largest]){
            largest = right;
        }
    }

    if(largest != i)
    {
        swap(&arr[i], &arr[largest]);
        stats->move_count += 3;
        heapify(arr, n, largest, stats);
    }
}

//堆排序
void heap_sort(int arr[], int n, SortStats* stats)
{
    stats->compare_count = 0;
    stats->move_count = 0;
    //构建最大堆
    for(int i = n / 2 - 1; i >= 0; i--)
    {
        heapify(arr, n, i, stats);
    }
    //逐个提取元素
    for(int i = n - 1; i > 0; i--)
    {
        swap(&arr[0], &arr[i]);
        stats->move_count += 3;
        heapify(arr, i, 0, stats);
    }
    stats->is_stable = false;
}

// 归并排序的合并函数
void merge(int arr[], int l, int m, int r, SortStats *stats) {
    int n1 = m - l + 1;
    int n2 = r - m;

    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++) {
        L[i] = arr[l + i];
        stats->move_count++;
    }
    for (int j = 0; j < n2; j++) {
        R[j] = arr[m + 1 + j];
        stats->move_count++;
    }

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        stats->compare_count++;
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            stats->move_count++;
            i++;
        } else {
            arr[k] = R[j];
            stats->move_count++;
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        stats->move_count++;
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        stats->move_count++;
        j++;
        k++;
    }

    free(L);
    free(R);
}

// 归并排序递归函数
void merge_sort(int arr[], int l, int r, SortStats *stats) {
    if (l < r) {
        int m = l + (r - l) / 2;
        merge_sort(arr, l, m, stats);
        merge_sort(arr, m + 1, r, stats);
        merge(arr, l, m, r, stats);
    }
}

// 归并排序入口
void merge_sort_entrance(int arr[], int n, SortStats *stats) {
    stats->compare_count = 0;
    stats->move_count = 0;
    merge_sort(arr, 0, n - 1, stats);
    stats->is_stable = true;
}

//从文件中读取数组
int *read_array_from_file(const char* filename, int *n)
{
    FILE *fp = fopen(filename, "r");
    if(!fp)
    {
        printf("无法打开文件%s", filename);
        return;
    }
    int count = 0;
    int num;
    while(fscanf(fp, "%d", &num) == 1) count++;

    rewind(fp);
    int *arr = (int *)malloc(count * sizeof(int));
    if(!arr){
        fclose(fp);
        return NULL;
    }
    for(int i = 0; i < count; i++) fscanf(fp, "%d", &arr[i]);
    fclose(fp);
    return arr;
}

//检查数组是否已经排序
bool is_sorted(int arr[], int n)
{
    for(int i = 0; i < n - 1; i++) {
        if(arr[i] > arr[i + 1]) return false;
    }
    return true;
}

void test_sort_algorithm(
    void (*sort_func)(int[], int, SortStats*),
    const char *filename,
    int arr[],
    int n,
    bool is_stable
){
    int *temp = (int *)malloc(n * sizeof(int));
    memcpy(temp, arr, n*sizeof(int));

    SortStats stats = {0};
    stats.is_stable = is_stable;

    clock_t start = clock();
    sort_func(temp, n, &stats);
    clock_t end = clock();
    stats.time_spent = (double)(end - start)/CLOCKS_PER_SEC;

    if(!is_sorted(temp, n)){
        printf("%s排序失败！\n", filename);
    }
    printf("| %-14s | %8d | %15ld | %15ld | %10.3f | %-7s |\n",
        filename, n, stats.compare_count, stats.move_count,
        stats.time_spent, stats.is_stable ? "是" : "否");

    free(temp);
}
int main() {
    const char *files[] = {"data1.txt", "data2.txt", "data3.txt", "data4.txt", "data5.txt"};
    const int num_files = 5;

    printf("| 算法          | 数据量   | 比较次数        | 移动次数        | 时间(秒)   | 稳定性  |\n");
    printf("|---------------|----------|-----------------|-----------------|------------|---------|\n");

    for (int i = 0; i < num_files; i++) {
        int n;
        int *arr = read_array_from_file(files[i], &n);
        if (!arr) {
            printf("无法读取文件: %s\n", files[i]);
            continue;
        }

        printf("\n测试文件: %s (数据量: %d)\n", files[i], n);
        test_sort_algorithm(insertion_sort, "直接插入", arr, n, true);
        test_sort_algorithm(bubble_sort, "冒泡", arr, n, true);
        test_sort_algorithm(quick_sort_entrance, "快速", arr, n, false);
        test_sort_algorithm(selection_sort, "简单选择", arr, n, false);
        test_sort_algorithm(heap_sort, "堆", arr, n, false);
        test_sort_algorithm(merge_sort_entrance, "归并", arr, n, true);

        free(arr);
    }

    return 0;
}