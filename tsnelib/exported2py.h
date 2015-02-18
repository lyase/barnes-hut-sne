#ifndef EXPORTED2PY
#define EXPORTED2PY

/*
 *  SELECTING functions to be exported to python thru swig
 *  Header file so swig generates python module.
/* the following Math  class is used to test the python wrapper work for basic pointer manipulation
*/
class  Math4py {
public:
    Math4py();
    int pi() const;
    void pi(int pi);
private:
    int _pi;
};
int  fact(int n);

#endif
