#ifndef SEQ_LIST_
#define SEQ_LIST_

##include "Assistance.h"        // the

// templale class declaratioin
template <class ElemTpye>
class SeqList{
// the member variables
protected:
    int length_;                    // the SeqList current length
    int max_length_;                // the SeqList max_length
    ElemTpye *elems_;               // the elements head address

// the member functions
public:
    SeqList(int size = DEFAULT_SIZE);                               // construct a null SeqList
    SeqList(ElemTpye v[], int n, int size = DEFAULT_SIZE);          // construct with a vector of Elem
    virtual ~SeqList();                                             // deconstruct the SeqList
    int GetLength() const;                                          // get the length of the SeqList
    int IsEmpty() const;                                            // judge whether the SeqList is empty or not
    void Clear();                                                   // Clear the SeqList
    void Traverse(void (*Visit)(const ElemTpye &)) const;           // Traverse 
    int LocateElem(const ElemTpye &e) const;
    Status GetElem(int i, ElemTpye &e) const;
    Status DeleteElem(int i, ElemTpye &e);
    Status InsertElem(int i, const ElemTpye &e);
    Status InsertElem(const ElemTpye &e);
    SeqList(const SeqList<ElemTpye> &sa);
    SeqList<ElemTpye> &operater =(const SeqList<ElemTpye> &sa);
}

// realization of member function

template <class ElemTpye>
SeqList<ElemTpye>::SeqList(int size){
    elems_ = new ElemTpye[size];
    assert(elems_);
    max_length_ = size;
    length_ = 0;
}

template <class ElemTpye>
SeqList<ElemTpye>::SeqList(ElemTpye v[], int n, int size){
    elems_ = new ElemTpye[size];
    assert(elems_);
    max_length_ = size;
    length_ = n;
    for(int i = 0; i < length_; i++){
        elems_[i] = v[i];
    }
}

template <class ElemTpye>
SeqList<ElemTpye>::~SeqList(){
    delete []elems_;
}

template <class ElemTpye>
SeqList<ElemTpye>::GetLength() const{
    return length_;
}

template <class ElemTpye>
SeqList<ElemTpye>::IsEmpty() const{
    return length_ = 0;
}

template <class ElemTpye>
SeqList<ElemTpye>::clear(){
    length_ = 0;
}

template <class ElemTpye>
SeqList<ElemTpye>::Traverse(void (*Visit)(const ElemTpye &)){
    for(int i = 0; i < length_; i++)
        (*Visit)(elems_[i]);
}

template <class ElemTpye>
SeqList<ElemTpye>::LocateElem(const ElemTpye &e) const{
    int i = 0;
    while(i < length_ && elems_[i] != e)
        i++;
    return i < length_ ? i+1 : 0;
}

template <class ElemTpye>
SeqList<ElemTpye>::GetElem(int i, ElemTpye &e){
    if(i < 1 || i > length_)
        return NOT_PRESENT;
    else{
        e = elems_[i - 1];
        return ENTRY_FOUND;
    }
}

template <class ElemTpye>
SeqList<ElemTpye>::SetElem(int i, const ElemTpye &e){
    if(i < 1 || i > length_)
        return RANGE_ERROR;
    else{
        elems_[i-1] = e;
        return SUCCESS;
    }
}

template <class ElemTpye>
SeqList<ElemTpye>::DeleteElem(int i, ElemTpye &e){
    if(i < 1 || i > length_)
        return RANGE_ERROR;
    else{
        e = elems_[i -1];
        for(int j = i; j < length_; j++)
            elems_[j-1] = elems_[j];
        length_--;
        return SUCCESS;
    }
}

template <class ElemTpye>
SeqList<ElemTpye>::InsertElem(int i, const ElemTpye &e){
    if(length_ == max_length_)
        return OVER_FLOW;
    else if(i < 1 || i > length_+1)
        return RANGE_ERROR;
    else{
        for(int j = length_; j >= i; j--)
            elems_[j] = elems_[j-1];
        elems_[i-1] = e;
        length_++;
        return SUCCESS;
    }
}

template <class ElemTpye>
SeqList<ElemTpye>::InsertElem(const ElemTpye &e){
    if(length_ == max_length_)
        return OVER_FLOW;
    else{
        elems_[length_] = e;
        length_++;
        return SUCCESS;
    }
}

template <class ElemTpye>
SeqList<ElemTpye>::SeqList(const SeqList<ElemTpye> &sa){
    int sa_length = sa.GetLength();
    ElemTpye e;

    max_length_ = sa.max_length_;
    elems_ = new ElemTpye[max_length_];
    assert(elems_);
    length_ = 0;

    for(int i = 0; i < sa_length; i++){
        sa.GetElem(i, e);
        InsertElem(e);
    }
}

template <class ElemTpye>
SeqList<ElemTpye> &SeqList<ElemTpye>::operater =(const SeqList<ElemTpye> &sa){
    if(&sa != this){
        int sa_length = sa.GetElem();
        ElemTpye e;

        max_length_ = sa.max_length_;
        delete []elems_;
        elems_ = new ElemTpye[max_length_];
        assert[elems_];
        length_ = 0;
        for(int i = 0; i <= sa_length; i++){
            sa.GetElem(i, e);
            InsertElem(e);
        }
    }
    return *this;
}

#endif
