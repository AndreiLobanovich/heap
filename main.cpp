#include <iostream>

#include <assert.h>
#include <string.h>
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
        bool verify_heap();
        ~heap();
};

template <typename T> bool heap<T>::verify_heap()
{
    for (int i = 1; i <= size; i++)
    {
        if (2*i + 1 <= size)
        {
            if (get_right_child(i) < max_size)
            {
                if (mode)
                {
                    if ((values[i] < values[get_right_child(i)]) || (values[i] < values[get_left_child(i)]))
                        return false;
                    
                }
                else
                {
                    if ((values[i] > values[get_right_child(i)]) || (values[i] > values[get_left_child(i)]))
                        return false;
                }
            } 
        }
    }
    return true;
}

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
            if ((get_left_child(pos) < max_size) && (get_right_child(pos) < max_size))
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
            
        }
        else
        {
            if ((get_left_child(pos) < max_size) && (get_right_child(pos) < max_size))
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



template <typename T> T inp(string s)
{
    cout << s << endl;
    T v;
    cin>>v;
    return v;
}

int main()
{
    int seed = time(NULL);
	srandom(seed);
    string msg;
    int size, mode, lastPopped, whereAmI, v; 
    heap<int>* h;
    cout << "// --------------------------------------------------------\n// Test #1 : heap interface works properly\n// --------------------------------------------------------\n";
    for (int i = 0; i < 100; i++)
    {
        size = rand()%100 + 5; 
        mode = rand()%2;
        h = new heap<int>(size, mode);
        for (int j = 0; j < size; j++)
        {
            v = rand()%1000-500;
            h->add_value(v);
        }
        if (mode == 1)
        {
            whereAmI = 1001;
            cout << "size = " + to_string(size) + " mode = " + to_string(mode) << endl;
            for (int i = 0 ; i < size ; i++)
            {
                lastPopped = h->pop();
                assert(lastPopped <= whereAmI);
                whereAmI = lastPopped;
                cout << lastPopped << ' ';
            }
            cout << endl << endl;
        }
        else
        {
            whereAmI = -1000;
            cout << "size = " + to_string(size) + " mode = " + to_string(mode) << endl;
            for (int i = 0 ; i < size ; i++)
            {
                lastPopped = h->pop();
                assert(lastPopped >= whereAmI);
                whereAmI = lastPopped;
                cout << lastPopped << ' ';
            }
            cout << endl << endl;
        }
        free(h);
    }
    cout << "Interface works propperly\n";
    cout << "// --------------------------------------------------------\n// Test #2 : Limit cases\n// --------------------------------------------------------\n";
    h = new heap<int>(10, 0);
    h->pop();
    cout << "Popping empty heap doesnt break the code\n";
    for (int i = 0 ; i < 10001 ; i++)
		h->add_value(rand() % 1000 );
    free(h);
    cout << "Adding too much values fails, but doesn't break\n";
    cout << "// --------------------------------------------------------\n// Test #3 : Internal tests\n// --------------------------------------------------------\n";
    h = new heap<int>(10, 1);
    for (int i = 0 ; i < 10 ; i++)
	{
		h->add_value(rand() % 1000 );
		assert(h->verify_heap());
	}
	for (int i = 0 ; i < 10 ; i++)
	{
		h->pop();
		assert(h->verify_heap());
	}
    free(h);
    cout << "Verified" << endl;
}


