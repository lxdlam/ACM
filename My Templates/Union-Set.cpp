class UF
{
  public:
    UF(int n)
    {
        count = length = n;
        id = new int[n];
        for (int i = 0; i < length; i++)
            id[i] = i;
        sz = new int[n];
        for (int i = 0; i < length; i++)
            sz[i] = 1;
    }

    ~UF()
    {
        delete[] id;
        delete[] sz;
    }

    int getCount()
    {
        return count;
    }

    bool connected(int p, int q)
    {
        return find(p) == find(q);
    }

    int find(int p)
    {
        int k = p, j;
        while (p != id[p])
            p = id[p];
        while (k != p)
        {
            j = id[k];
            id[k] = p;
            k = j;
        }
        return p;
    }

    void Union(int p, int q)
    {
        int pRoot = find(p);
        int qRoot = find(q);

        if (pRoot == qRoot)
            return;

        if (sz[pRoot] < sz[qRoot])
        {
            id[pRoot] = qRoot;
            sz[qRoot] += sz[pRoot];
        }
        else
        {
            id[qRoot] = pRoot;
            sz[pRoot] += sz[qRoot];
        }
        count--;
    }

  private:
    int count;
    int *id;
    int *sz;
    int length;
};