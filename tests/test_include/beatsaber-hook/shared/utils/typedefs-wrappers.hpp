#pragma once
template<typename T = bool>
struct EventCallback{
    T t;
    void invoke(){};
};

inline __attribute__((noreturn)) void safeAbort(const char *, const char *, int){
    asm("int3");
    while(1);
}