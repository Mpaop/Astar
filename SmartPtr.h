#ifndef SMARTPTR
#define SMARTPTR

template <class T>
class SmartPtr
{
    T *ptr;
public:
    explicit SmartPtr(T *p = NULL){ptr = p;}
    ~SmartPtr(){delete(ptr);}

    T & operator * () {return *ptr;}

    T * operator -> () {return ptr;}

    bool operator==(const SmartPtr<T> p) const {return ptr == p; }

    bool operator!=(const SmartPtr<T> p) const {return ptr != p; }

    bool IsNull() const {return ptr == nullptr;}
};

#endif