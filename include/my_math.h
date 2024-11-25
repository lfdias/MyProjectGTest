#ifndef MY_MATH_H
#define MY_MATH_H

class MyMath {
public:
    virtual ~MyMath() = default;
    virtual int add(int a, int b);
    virtual int multiply(int a, int b);
};

#endif // MY_MATH_H