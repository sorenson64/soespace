#ifndef _STACK
#define _STACK

class stack
{
  uint32_t items[16];
  int top;

  public:
  stack() { top=0; }
  inline void push(int x) { items[top++]=x; }
  inline uint32_t pop() { return items[--top]; }
  inline bool isempty() { return(top==0); }
  inline uint32_t gettop() { return items[top-1]; }
  inline void makeempty() { top=0; }
};

#endif

