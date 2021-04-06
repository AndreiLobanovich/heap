#include <iostream>
using namespace std;



template <typename T> class heap
{
    private://property
        T *values;
        int size = 0;
        int max_size;//static
        int mode = 0;

    public://processes
        heap(int n, int mod);
        int add_value(T n);
        inline int get_parent(int pos);
        inline int get_right_child(int pos);
        inline int get_left_child(int pos);
        bool is_leaf(int pos);
        void swap(int a, int b);
        T pop();
        void heapify(int pos);
        void display();
        ~heap();
};

template <typename T> heap<T>::heap(int n, int mod)//constructor
{
    values = new T[n + 1];
    max_size = n;
    mode = mod;
}

template <typename T> int heap<T>::add_value(T n)
{
    if(size >= max_size)
        return 1;
    size++;
    values[size] = n;
    int  temp = size;
    if (!mode)
    {
        while(values[temp] < values[get_parent(temp)] && temp != 1)
        {
            swap(temp, get_parent(temp));
            temp = get_parent(temp);
        }
    }
    else
    {
        while(values[temp] > values[get_parent(temp)] && temp != 1)
        {
            swap(temp, get_parent(temp));
            temp = get_parent(temp);
        }
    }
    
    return 0;
}

template <typename T> inline int heap<T>::get_parent(int pos)
{
    int n = pos/2;
    return n;
}

template <typename T> inline int heap<T>::get_right_child(int pos)
{
    int n = (pos * 2) +1; 
    return n; 
}

template <typename T> inline int heap<T>::get_left_child(int pos)
{
    int n = pos * 2;
    return n;
}

template <typename T> bool heap<T>::is_leaf(int pos)//is it at the bottom
{
    if((pos > size / 2) && (pos <= size))
        return true;    
    
    return false;
}

template <typename T> void heap<T>::swap(int a, int b)//swaps any 2 values
{
    T buf;
    buf = values[a];
    values[a] = values[b];
    values[b] = buf;
}

template <typename T> T heap<T>::pop()
{
    if (size > 0)
    {
        T temp = values[1];
        values[1] = values[size];
        size--;
        heapify(1);
        return temp;
    }
    return 0;
}

template <typename T> void heap<T>::heapify(int pos)
{
    if(!is_leaf(pos))
    {
        if (!mode)
        {
            if(values[pos] > values[get_left_child(pos)] || values[pos] > values[get_right_child(pos)])
            {
                if(values[get_left_child(pos)] < values[get_right_child(pos)])
                {
                    swap(pos, get_left_child(pos));
                    heapify(get_left_child(pos));
                }
                else
                {
                    swap(pos, get_right_child(pos));
                    heapify(get_right_child(pos));
                }
            }
        }
        else
        {
            if(values[pos] < values[get_left_child(pos)] || values[pos] < values[get_right_child(pos)])
            {
                if(values[get_left_child(pos)] > values[get_right_child(pos)])
                {
                    swap(pos, get_left_child(pos));
                    heapify(get_left_child(pos));
                }
                else
                {
                    swap(pos, get_right_child(pos));
                    heapify(get_right_child(pos));
                }
            }
        }
    }
}

template <typename T> void heap<T>::display()
{   
    for (int i = 1; i < size + 1; i++)
        cout << values[i] << ' ';          // delete later
    cout << endl;

    for(int i = 1; i < (size/2) + 1; i++)
    {
        cout <<"Parent: " <<values[i] << " Left Child: " << values[2*i];
        if (2*i + 1 <= size)
            cout << " Right Child: "<< values[2*i + 1] << '-' << size << endl;
        else
            cout << endl;
    }
}

template <typename T> heap<T>::~heap()
{
    free(values);
}
