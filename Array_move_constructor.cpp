#include <iostream>

class Array {
private:
    int* m_ptr;
    int m_size;

public:
    Array()
    {
        std::cout << "Default " << __func__ << "\n";
        m_size = 0;
        m_ptr = nullptr;
    }

    Array(int n)
    {
        std::cout << "Parametrized " << __func__ << "\n";
        m_size = n;
        m_ptr = new int[m_size];
    }

    ~Array()
    {
        std::cout << __func__ << "\n";
        delete[] m_ptr;
    }

    Array(const Array& ob):m_size(ob.m_size)
    {
        std::cout << "Copy " << __func__ << "\n";

        this->m_ptr = new int[m_size];

        for (int i = 0; i < m_size; i++)
        {
            this->m_ptr[i] = ob.m_ptr[i];
        }
    }

    Array(Array&& ob):m_size(ob.m_size) //move constructor
    {
        std::cout << "Move " << __func__ << "\n";

        if (this != &ob)
        {
            this->m_ptr = ob.m_ptr;

            ob.m_ptr = nullptr;
            ob.m_size = 0;
        }
    }

    Array& operator=(const Array& ob)
    {
        std::cout << __func__ << "\n";

        if (this != &ob)
        {
            std::cout <<  __func__ << "\n";
            this->m_size = ob.m_size;
            delete[] m_ptr;

            this->m_ptr = new int[this->m_size];

            for (int i = 0; i < m_size; i++)
            {
                this->m_ptr[i] = ob.m_ptr[i];
            }
        }
        return *this;
    }


    Array& operator =(Array&& ob)   //move operator assignment
    {
        std::cout << "Move " << __func__ << "\n";

        if (this != &ob)
        {
            delete this->m_ptr;
            this->m_size = ob.m_size;

            this->m_ptr = ob.m_ptr;
            
            ob.m_ptr = nullptr;
            ob.m_size = 0;
        }
        return *this;
    }


public: 

    int& operator[](int index) const
    {
        return m_ptr[index];
    }


    int& at(int index) const
    {
        if (index < 0 || index >= m_size)
        {
            std::cout << "Out of range\n";
        }
        //std::cout << "Element with index " << index << " and with value " << ptr[index] << std::endl;
        return m_ptr[index];
    }


    bool operator >(const Array& ob)
    {
        bool flag = false;
        if (this->m_size > ob.m_size)
        {
            flag = true;
        }
        std::cout << std::boolalpha << flag << std::endl;
        return flag;
    }


    bool operator <(const Array& ob)
    {
        bool flag = false;
        if (this->m_size < ob.m_size)
        {
            flag = true;
        }
        std::cout << std::boolalpha << flag << std::endl;
        return flag;
    }


    bool operator ==(const Array& ob)
    {
        bool flag = false;
        if (this->m_size == ob.m_size)
        {
            flag = true;
        }
        std::cout << std::boolalpha << flag << std::endl;
        return flag;
    }


    int* genElements()
    {
        for (int i = 0; i < m_size; i++)
        {
            m_ptr[i] = rand() % 100 + 1;
        }
        return m_ptr;
    }


    int getElement(int index)
    {
        if (index > m_size || m_size < 0)
        {
            std::cout << "Out of range\n";
            return -1;
        }
        else
        {
            std::cout << "Element with value " << m_ptr[index] << " was returned\n";
            return m_ptr[index];
        }
    }

    void printArray()
    {
        for (int i = 0; i < m_size; i++)
        {
            std::cout << "element[" << i << "] = " << m_ptr[i] << std::endl;
        }
    }

};


int main()
{
    int n;
    std::cout << "Enter the number of elements\n";
    std::cin >> n;

    Array ob(n);
    ob.genElements();
    ob.printArray();
    ob.getElement(2);

    /*try {
        ob[-1];
    }
    catch (const std::logic_error& e)
    {
        std::cerr << e.what();
    }*/


    /*try {
         ob[-1];
     }
     catch (const std::logic_error& e)
     {
         std::cerr << e.what();
     }*/

    ob[3];
    ob[2] = 45;
    std::cout << "After operator []\n";
    ob.printArray();

    std::cout << "At\n";
    ob.at(2);
    ob.at(1) = 8;
    ob.printArray();

    Array ob_cp(ob);

    ob > ob_cp;

    Array ob1;
    ob1 = ob_cp;

    //move semantics
    
    Array m_ob1(3);
    m_ob1 = std::move(Array(3));    //move operator assignment

    Array m_ob2 = std::move(Array(2)); //move constructor

    return 0;
}
