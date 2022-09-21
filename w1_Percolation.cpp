#include <bits/stdc++.h>
using namespace std;

void unionn(int id[], int sz[], int p, int q);
int root(int id[], int i);

static unsigned long x = 123456789, y = 362436069, z = 521288629;
unsigned long xorshf96(void)
{
    unsigned long t;
    x ^= x << 16;
    x ^= x >> 5;
    x ^= x << 1;

    t = x;
    x = y;
    y = z;
    z = t ^ x ^ y;

    return z;
}

void Initialize(int array[], int l)
{
    for (int i = 1; i < l - 1; i++)
        array[i] = -1;
    array[0] = 0;
    array[l - 1] = l - 1;
}

void open(int id[], int sz[], int r, int c, int n)
{

    int i = (r - 1) * n + c;
    int flag = 0; // change it to 1 if atleast 1 neighbourhood site is open
    if (r != 1)
    {
        int nor = (r - 2) * n + c;
        if (id[nor] != -1)
        {
            flag = 1;
            unionn(id, sz, i, nor);
        }
    }
    if (r != n)
    {
        int sou = r * n + c;
        if (id[sou] != -1)
        {
            flag = 1;
            unionn(id, sz, i, sou);
        }
    }
    if (c != 1)
    {
        int wes = (r - 1) * n + c - 1;
        if (id[wes] != -1)
        {
            flag = 1;
            unionn(id, sz, i, wes);
        }
    }
    if (c != n)
    {
        int eas = (r - 1) * n + c + 1;
        if (id[eas] != -1)
        {
            flag = 1;
            unionn(id, sz, i, eas);
        }
    }
    if (flag == 0)
        id[i] = i;
}

void unionn(int id[], int sz[], int p, int q)
{
    if (id[p] == -1)
        id[p] = p;

    if (id[q] == -1)
        id[q] = q;

    int pr = root(id, p);
    int qr = root(id, q);

    if (sz[pr] <= sz[qr])
    {
        id[pr] = qr;
        sz[qr] += sz[pr];
    }
    else
    {
        id[qr] = pr;
        sz[pr] += sz[qr];
    }
}

void unionn1(int id[], int p, int q)
{
    if (id[q] == -1)
        return;
    id[root(id, p)] = root(id, q);
}

int root(int id[], int i)
{

    while (i != id[i])
    {
        id[i] = id[id[i]];
        i = id[i];
    }
    return i;
}

bool isOpen(int id[], int r, int c, int n)
{
    if (id[(r - 1) * n + c] == -1)
        return false;
    else
        return true;
}

bool percolates(int id[], int sz[], int n)
{
    int idc[n * n + 2];
    for (int i = 0; i < n * n + 2; i++)
        idc[i] = id[i];

    // now connecting 0 and n+1 to first and last row
    // for first row
    for (int i = 1; i <= n; i++)
        if (idc[i] != -1)
            unionn1(idc, i, 0);

    // for last row
    int l = n * n + 2;

    for (int i = l - 2; i > l - 2 - n; i--)
    {

        if (idc[i] != -1)
            unionn1(idc, i, l - 1);
    }

    if (root(idc, 0) == root(idc, n * n + 1))
        return true;

    else
        return false;
}

int percolation(int id[], int sz[], int n)
{

    int count{};                   // this is the count of number of times we had to open a site
    while (!percolates(id, sz, n)) // will keep running until the site percolates
    {
        // now we have to generate a random row and random column (1 to n)

        int r = (xorshf96() % n) + 1;
        int c = (xorshf96() % n) + 1;

        if (isOpen(id, r, c, n)) // if site at r and c already open, then continue the loop
            continue;
        count++; // as we are going to open a site
        open(id, sz, r, c, n);
    }
    return count;
}

int main()
{
    cout << "Enter N and T\n";
    int n{}, t{};
    cin >> n >> t;
    int id[n * n + 2], x[t];
    int sz[n * n + 2];
    for (int i = 0; i < n * n + 2; i++)
        sz[i] = 1;
    // given row and column, we can find it's id as -> id[(r-1)n + c]
    // id[0] will be connected to all the blocks in the top row and id[n+1] will be connected to all the blocks in the bottom row
    Initialize(id, n * n + 2);

    int i = 0;

    while (i < t)
    {
        x[i++] = percolation(id, sz, n);
        Initialize(id, n * n + 2);
        for (int j = 0; j < n * n + 2; j++)
            sz[j] = 1;
    }

    double sum{};

    for (int hehe = 0; hehe < i; hehe++)
        sum += ((double)x[hehe] / (double)(n * n));

    double mean = sum / t;
    cout << "\nMean is - " << mean;
}