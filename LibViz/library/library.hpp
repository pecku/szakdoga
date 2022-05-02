#include <cstddef>
#include <iostream>
#include <vector>
#include <fstream>
#include <typeinfo>
#include <sstream>

//Felsorolók őssztály-sablonja
//Műveletek: first(), next(), end(), current()
//Sablon paraméterek: Item - a felsorolt elemek típusa
template <typename Item>
class Enumerator
{
    public:
        virtual void first() = 0;
        virtual void next() = 0;
        virtual bool end() const = 0;
        virtual Item current() const = 0;
        virtual ~Enumerator(){}
};

template < typename Item, typename Value> class Summation;
template < typename Item> class Summation<Item, std::ostream>;
template < typename Item, typename Value > class Summation<Item, std::vector<Value> > ;
template < typename Value> class Greater;
template < typename Value> class Less;
template < typename Item, typename Value = Item, typename Compare = Greater<Value> > class MaxSearch;
template < typename Item, bool optimist = false> class LinSearch;
template < typename Item> class Selection;

//template class of general programing theorems
//template parameters:  Item    - the type of the elements that are enumerated
//new virtual methods:  init()          - initializes the programming theorem
//                      body()          - one iteration of the programming theorem
//                      first()         - first step of the enumerator
//                      whileCond()     - can stop the enumerator earlier
//                      loopCond()      - loop condition of the programming theorem
//                      run()           - executes the programing theorem
//                      addEnumerator() - gives an enumerator to the programming theorem
//representation:       Enumerator<Item> *_enor
template <typename Item, typename Value = Item, typename Compare = Greater<Value>, bool optimist = false >
class Procedure
{
    friend class Summation<Item, Value>;
    friend class MaxSearch<Item, Value, Compare>;
    friend class LinSearch<Item, optimist>;
    friend class Selection<Item>;

    protected:
        Enumerator<Item> *_enor;

        Procedure():_enor(nullptr){}
        virtual void init() = 0;
        virtual void body(const Item& e) = 0;
        virtual void first() {_enor->first();}
        virtual bool whileCond(const Item& current) const { return true; }
        virtual bool loopCond() const
                   { return !_enor->end() && whileCond(_enor->current()) ; }
    public:
        enum Exceptions { MISSING_ENUMERATOR};
        virtual void run() final;
        virtual void addEnumerator(Enumerator<Item>* en) final { _enor = en;}
        virtual ~Procedure(){}
};

//Task: 	runs the programming theorem
//Input:    Enumerator<Item> *_enor - enumerator
//Activity: algorithm of programming theorem
template <typename Item, typename Value, typename Compare, bool optimist>
void Procedure<Item, Value, Compare, optimist>::run()
{
    if(_enor==nullptr) throw MISSING_ENUMERATOR;
    init();
    for(first(); loopCond(); _enor->next()){
        body(_enor->current());
    }
}

//template class of linear search
//template parameters:  Item        - the type of the elements that are enumerated
//overrode methods:     init(), loopCond(), body()
//new methods:          result()    - gives back the result of selection
//new virtual methods:  cond()      - defines a condition on an Item type element
template < typename Item >
class Selection : public Procedure<Item>
{
protected:
    void init() final override {}
    void body(const Item& e) final override {}
    bool loopCond() const final override {
        return !cond(Procedure<Item>::_enor->current());
    }
    virtual bool cond(const Item& e) const = 0;
public:
    Item result() const {
        return Procedure<Item>::_enor->current();
    }
};

//template class of summation
//template parameters:  Item    - the type of the elements that are enumerated
//                      Value   - the type of the values of the elements that are enumerated
//overrode methods:     body()
//new methods:          result()    - gives back the result of summation
//new virtual methods:  neutral()   - gives the neutral element of the operator summation over Value
//                      add()       - defines the operator summation over Value
//                      func()      - computes the value of an Item type element
//                      cond()      - defines a condition on an Item type element
//representation:       Value _result-  result of summation
template < typename Item, typename Value = Item >
class Summation : public Procedure<Item>
{
private:
    Value _result;
protected:
    void init() final override  { _result = neutral(); }
    void body(const Item& e) final override  {
        if(cond(e)) _result = add(_result, func(e));
    }
    virtual Value func(const Item& e) const = 0;
    virtual Value neutral() const = 0;
    virtual Value add( const Value& a, const Value& b) const = 0;
    virtual bool  cond(const Item& e) const { return true; }
public:
    Summation(){}
    Summation(const Value &v) : _result(v) {}
    const Value& result() const { return _result; }
};

//template specialization if the second parameter is ostream
//it is used to solve collated problems
template < typename Item >
class Summation<Item, std::ostream> : public Procedure<Item, std::ostream>
{
protected:
    std::ostream *_result;
protected:
    void init() override final { }
    void body(const Item& e) override final {
        if(cond(e)) *_result << func(e);
    }
    virtual std::string func(const Item& e) const = 0;
    virtual bool cond(const Item& e) const { return true; }
public:
    Summation(std::ostream *o) : _result(o) {}
};

//template specialization if the second parameter is vector
//it is used to solve problems with multiple answers.
template < typename Item, typename Value >
class Summation<Item, std::vector<Value> > : public Procedure<Item, std::vector<Value> >
{
private:
    std::vector<Value> _result;
protected:
    void init() override final { }
    void body(const Item& e) override final {
        if(cond(e)) _result.push_back(func(e));
    }
    virtual bool loopCond() const override final
        { return !Procedure<Item, std::vector<Value> >::_enor->end()
                 && Procedure<Item, std::vector<Value> >::whileCond(Procedure<Item, std::vector<Value> >::_enor->current()) ; }

    virtual Value func(const Item& e) const = 0;
    virtual bool cond(const Item& e) const { return true; }

public:
    Summation() {}
    Summation(const std::vector<Value> &v) : _result(v) {}
    const std::vector<Value>& result() const { return _result; }
};

//template class of counting
//template parameters:  Item    - the type of the elements that are enumerated
//overrode methods:     init(), add(), neutral()
template < typename Item >
class Counting : public Summation<Item, int>
{
protected:
    int neutral() const final override { return 0; }
    int add(const int &a, const int &b) const final override { return a + b; }
    int func(const Item &e) const final override { return 1; }
};

//template class of linear search
//template parameters:  Item            - the type of the elements that are enumerated
//                      bool optimist   - sets the version of linear search
//overrode methods:     init(), whileCond(), body()
//new methods:          found(), elem() - gives back the result of linear search
//new virtual methods:  cond()          - defines a condition on an Item type element
//representation:       bool _l         - logical variable of linear search
//                      Item _elem      - current element of linear search
template < typename Item, bool optimist >
class LinSearch : public Procedure<Item>
{
protected:
    bool _l;
    Item _elem;

    void init() final override { _l = optimist; }
    void body(const Item& e) final override { _l = cond(_elem = e); }
    bool loopCond() const final override { return (optimist?_l:!_l) && Procedure<Item>::loopCond();}

    virtual bool cond(const Item& e) const = 0;

public:
    bool found()  const{ return _l; }
    Item elem()   const{ return _elem;}
};

//template class including "greatert" relation
//Method: operátor()
//template parameter: Value - type of the values that must be compared
template <typename Value> // Value implements the operator>()
class Greater{
    public:
        bool operator()(const Value& l, const Value& r){
            return l > r;
        }
};

//template class including "less" relation
//Method: operátor()
//template parameter: Value - type of the values that must be compared
template <typename Value> // Value implements the operator>()
class Less{
    public:
        bool operator()(const Value& l, const Value& r){
            return l < r;
        }
};

//template class of general maximum search
//template parameters:  Item    - the type of the elements that are enumerated
//                      Value   - the type of the values of the elements that are enumerated
//                      Compare - it may be Greater or Less
//overrode methods:     init(), body()
//new methods:          found(), opt(), optElem()   -   give back the results of maximum search
//new virtual methods:  func() - computes the value of an Item type element
//                      cond() - defines a condition on an Item type element
//representation:       bool _l       - logical variable of the conditional maximum search
//                      Item _optelem - the best Item type element that is found for a given moment
//                      Value _opt    - the Value type value of the best Item type element that is found for a given moment
//                      Compare _better - object that compares values, its type may be Greater or Less
template <typename Item, typename Value, typename Compare >
class MaxSearch : public Procedure<Item, Value, Compare>
{
protected:
    bool    _l;
    Item    _optelem;
    Value   _opt;
    Compare _better;

    void init() final override { _l = false;}
    void body(const Item& e) final override;

    virtual Value func(const Item& e) const = 0;
    virtual bool  cond(const Item& e) const { return true;}

public:
    bool found()   const { return _l;}
    Value opt()    const { return _opt;}
    Item optElem() const { return _optelem;}
};

// body of the loop of the general maximum search
template <class Item, class Value, class Compare>
void MaxSearch<Item,Value,Compare>::body(const Item& e)
{
    Value val = func(e);
    if ( !cond(e) ) return;
    if (_l){
        if (_better(val,_opt)){
            _opt = val;
            _optelem = e;
        }
    }
    else {
        _l = true;
        _opt = val;
        _optelem = e;
    }
}

//template class of enumerations over arrays
//template parameters:  Item    - the type of the elements that are enumerated
//overrode methods:     first(), next(), end(), current()
//representation:       vector<Item> *_vect - the array that must be enumerated
//                      unsigned int _ind            - index of enumeration
template <typename Item>
class ArrayEnumerator : public Enumerator<Item>
{
    protected:
        const std::vector<Item> *_vect;
        unsigned int             _ind;

    public:
        ArrayEnumerator(const std::vector<Item> *v):_vect(v){}
        void first()         override { _ind = 0; }
        void next()          override { ++_ind; }
        bool end()     const override { return _ind>=_vect->size(); }
        Item current() const override { return (*_vect)[_ind]; }
};

//template class of enumerations over intervals
//template parameters:  Item    - the type of the elements that are enumerated
//overrode methods:     first(), next(), end(), current()
//representation:       int _m, _n  - the ends of the interval that must be enumerated
//                      int _ind    - index of enumeration
class IntervalEnumerator : public Enumerator<int>
{
private:
    int _m, _n;
    int _ind;
public:
    IntervalEnumerator(int m, int n): _m(m), _n(n) {}
    void first() override { _ind = _m;}
    void next() override { ++_ind; }
    int current() const override { return _ind; }
    bool end() const override { return _ind>_n; }
};

//template class of the enumerator of sequential input files
//template parameters:  Item    - the type of the elements that are enumerated
//overrode methods:     first(), next(), current(), end()
//representation:       std::ifstream _f        - text file that contains the elements that must be enumerated
//                      Item          _df       - current element of the current row of the text file
//                      bool          _end      - true, if there are no more element in the text file
//                      std::stringstream _ss   - current row of the text file
template <typename Item>  // Item implements the operator>>()
class SeqInFileEnumerator : public Enumerator<Item>
{
    protected:
        std::ifstream _f;
        Item          _df;
        bool          _end;
        std::stringstream _ss;

        static bool whitespace() {
            return false;
        }

        bool read_next_not_empty_line(){
            std::string line;
            _ss.clear();
            while( getline(_f, line) && line.size()==0 ) ;
            if(!(_f.fail())) _ss.str(line);
            return !_f.fail();
        }
    public:
        enum Exceptions { OPEN_ERROR };
        SeqInFileEnumerator(const std::string& str){
            _f.open(str);
            if(_f.fail()) throw OPEN_ERROR;
            if(whitespace()) _ss.unsetf(std::ios::skipws);
            _end = false;
        }

        SeqInFileEnumerator(std::ifstream& f){
            _f = f;
            if(whitespace()) _ss.unsetf(std::ios::skipws);
            _end = false;
        }

        void first() final override {
            _end = !read_next_not_empty_line();
            next();
        }
        void next() final override {
            _ss >> _df;
            if(_ss.fail()) {
                _end = !read_next_not_empty_line();
                _ss >> _df;
            }
        }
        bool end()     const final override { return _end;}
        Item current() const final override { return _df; }
};

//template specialization if the parameter is char
//switch off the skipping over white spaces
template<>
inline bool SeqInFileEnumerator<char>::whitespace() {
    return true;
}

//template class of the enumerator of strimgstreams
//template parameters:  Item    - the type of the elements that are enumerated
//overrode methods:     first(), next(), current(), end()
//representation:       std::stringstream _ss   - stringstream that contains the elements that must be enumerated
//                      Item          _df       - current element of the current row of the text file
template <typename Item>  // Item implementálja az operator>>-t
class StringStreamEnumerator : public Enumerator<Item>
{
    protected:
        std::stringstream _ss;
        Item              _df;

    public:
        StringStreamEnumerator(std::stringstream& ss) {
            _ss << ss.rdbuf();
        }

        void first()         override { next();}
        void next()          override { _ss >> _df; }
        bool end()     const override { return !_ss;}
        Item current() const override { return _df; }
};
