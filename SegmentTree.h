#ifndef SEGMENTTREE_H
    #define SEGMENTTREE_H
    #define left(i) (2*i + 1)
    #define right(i) (2*i + 2)
    #define parent(i) ((i-1)/2)
    #include <bits/stdc++.h>
    template<class T>
    class SegmentTree
    {
        public:
            SegmentTree(std::vector<T> data, T value, T (*combine)(T obj1, T obj2));
            SegmentTree(T ar[], int n, T value, T (*combine)(T obj1, T obj2));
            
            T query(int l, int r);
            
            void update(int idx, T val);
        private:
            T *tree;
            void buildTree(std::vector<T> data);

            int segTreeSize;
            T valueForExtraNodes;
            T (*combine)(T obj1, T obj2);
            int calculateSize(int n);
            T get(int l,int r, int st, int ed, int node);
    };

    template<class T> SegmentTree<T>::SegmentTree(std::vector<T> data,
                                                    T value, T (*combine)(T obj1, T obj2))
    {
        this->combine = combine;
        valueForExtraNodes = value;
        segTreeSize = calculateSize(data.size());
        buildTree(data);
    }

    template<class T> SegmentTree<T>::SegmentTree(T ar[], int n,
                                                T value, T (*combine)(T obj1, T obj2))
    {
        this->combine = combine;
        valueForExtraNodes = value;
        segTreeSize = calculateSize(n);

        std::vector<T> data;
        for(int i = 0; i < n; i++)
                data.push_back(ar[i]);

        buildTree(data);
    }


    template<class T> int SegmentTree<T>::calculateSize(int n)
    {
        int pow2 = 1;
        while( pow2 < n) pow2 = pow2 << 1;
        return 2*pow2 - 1;
    }

    template<class T> T SegmentTree<T>::query(int l, int r)
    {
        int st = 0, ed = segTreeSize/2;
        return get(l, r, st, ed, 0);
    }

    template<class T> T SegmentTree<T>::get(int l,int r, int st, int ed, int node)
    {
        if( (r < st) || (l > ed) || (l > r) ) return valueForExtraNodes;
        if(st >= l && ed <= r) return tree[node];
        T leftVal = get(l, r, st, (st + ed)/2, left(node));
        T rightVal = get(l, r, (st+ed)/2 + 1, ed, right(node));
        return combine(leftVal, rightVal);
    }

    template<class T> void SegmentTree<T>::buildTree(std::vector<T> data)
    {
        int n = data.size();
        tree = new T[segTreeSize];
        int extraNodes = (segTreeSize/2 + 1) - n;
        for(int i = segTreeSize - 1; i >= 0; i--)
        {
            if(extraNodes>0)
            {
                tree[i] = valueForExtraNodes;
                extraNodes--;
            }
            else if(n>0)
            {
                tree[i] = data[n-1];
                n--;
            }
            else tree[i] = combine(tree[left(i)], tree[right(i)]);
        }
    }

    template<class T> void SegmentTree<T>::update(int idx, T val)
    {
        int segTreeIdx = (segTreeSize/2) + idx;
        tree[segTreeIdx] = val;
        while(parent(segTreeIdx) >= 0)
        {
            segTreeIdx = parent(segTreeIdx);
            if(right(segTreeIdx) < segTreeSize)
            tree[segTreeIdx] = combine(tree[left(segTreeIdx)], tree[right(segTreeIdx)]);
            if(segTreeIdx == 0) break;
        }
    }

#endif