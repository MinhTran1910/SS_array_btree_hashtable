#include <iostream>
#include <time.h>

using namespace std;

struct btree
{
    int data;
    btree* left, * right;
    void init() {
        left = right = nullptr;
    }
};

struct Tree {
	btree* root = nullptr;
	void init(btree*& node) {
		node = new btree;
		node->init();
	}
	void insert(int value, btree*& parent) {
		if (parent == nullptr) {
			init(parent);
			parent->data = value;
			return;
		}
		//tim vi tri de insert
		if (value < parent->data) {
			insert(value, parent->left);

		}
		else {
			insert(value, parent->right);

		}
		return;
	}
    void FindNode(btree* root, int x)
    {
        if (root != nullptr)
        {
            if (root->data == x) // Tìm thấy
                return ;
            if (x < root->data)
                return FindNode(root->left, x); // Tìm cây con bên trái
            return FindNode(root->right, x); // Tìm cây con bên phải
        }
        return; // Không tìm thấy
    }
};

double KT_Btree(int arr[], int n)
{
    clock_t start, end;
    start = clock();
    Tree binaryTree;
    for (int i = 0; i < n; i++)
    {
        binaryTree.insert(arr[i], binaryTree.root);
    }
    for (int i = 0; i < n; i++)
    {
        binaryTree.FindNode(binaryTree.root, arr[i]);
    }
    end = clock();
    double time = (double)(end - start) / CLOCKS_PER_SEC;
    return time;
}
int partition(int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++)
    {
        if (arr[j] < pivot)
        {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {

        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int binarySearch(int arr[], int l, int r, int x) {
    if (r >= l) {
        int mid = l + (r - l) / 2; 

        if (arr[mid] == x)
            return mid;

        if (arr[mid] > x)
            return binarySearch(arr, l, mid - 1, x);

        return binarySearch(arr, mid + 1, r, x);
    }

    return -1;
}

double luumang(int arr[], int n)
{
    clock_t start, end;
    start = clock();

    int* a = new int[n];
    for (int i = 0; i < n; i++)
    {
        a[i] = arr[i];
    }
    quickSort(a, 0, n - 1);
    for (int i = 0; i < n; i++)
    {
        binarySearch(a, 0, n - 1, arr[rand()%n]);
    }

    end = clock();
    double time = (double)(end - start) / CLOCKS_PER_SEC;
    return time;
}

double hashTable(int* arr, int n)
{
    clock_t start, end;
    start = clock();
    int k = n * 2;
    int key;
    int* table = new int[k];
    for (int i = 0; i < k; i++)
        table[i] = NULL;
    for (int i = 0; i < n; i++)
    {
        key = arr[i] % k;
        while (table[key] != NULL)
        {
            if ((key + 1) < k)
                key++;
            else
            {
                key = 0;
            }

        }
        table[key] = arr[i];
    }
    for (int i = 0; i < n; i++)
    {
        int x=arr[rand() % n];
        key = x % k;
        while (table[key] != NULL && table[key]!= x)
        {
            if ((key + 1) < k)
                key++;
            else
            {
                key = 0;
            }
        }
    }
    end = clock();
    double time = (double)(end - start) / CLOCKS_PER_SEC;
    return time;
}

int main()
{
    
    double sum = 0;
    double sum1 = 0;
    double sum2 = 0;
    int n = 0;
    while (n<=10000)
    {
        sum = 0;
        sum1 = 0;
        sum2 = 0;
        for (int r = 0; r < 100; r++)
        {

            int* arr = new int[n];
            for (int i = 0; i < n; i++)
            {
                arr[i] = rand();
            }
            double time = luumang(arr, n);
            sum += time;
            double time1 =hashTable(arr, n);
            sum1 += time1;
            double time2 = KT_Btree(arr, n);
            sum2 += time2;
        }
        printf("%000000f     ", (double)sum / 100);
        printf("%000000f     ", (double)sum1 / 100);
        printf("%000000f\n", (double)sum2 / 100);
        n += 500;
    }
}
