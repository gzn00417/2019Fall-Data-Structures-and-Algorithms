import os
class Stack(object):
    def __init__(self): self.stack=[]
    def push(self,val): self.stack.append(val)
    def pop(self):
        if (not self.empty()): return self.stack.pop()
    def empty(self): return bool(not self.stack)
    def top(self):
        if (not self.empty()): return self.stack[-1]

NUM='0123456789.'
ops='+-*/^'
lv={'(':5,')':0,'#':1,'+':2,'-':2,'*':3,'/':3,'^':4}
chs=[chr(i) for i in range(97,123)]
vals={}

def Shift(str_list):
    sta=Stack()
    ans_str=[]
    for x in str_list:
        if (x[0] in NUM or x[0] in chs):
            ans_str.append(x)
        else:
            while (not sta.empty() and (sta.top() in ops) and lv[x]<=lv[sta.top()]):
                ans_str.append(sta.pop())
                if (ans_str[-1] in '()#'): ans_str.pop()
            sta.push(x)
            if (x!='('):
                while (not sta.empty() and (sta.top() not in ops)): sta.pop()
    while (not sta.empty()):
        ans_str.append(sta.pop())
        if (ans_str[-1] in '()#'): ans_str.pop()
    return ans_str

def op(x2,x1,op):
    if   (op=='+'): return x1+x2
    elif (op=='-'): return x1-x2
    elif (op=='*'): return x1*x2
    elif (op=='/'): return x1/x2
    elif (op=='^'): return x1**x2

def Calc(shift_list):
    ans_num=[]
    for x in shift_list:
        if (x in ops):
            ans_num.append(op(ans_num.pop(),ans_num.pop(),x))
        else:
            if (x[0] in chs):
                ans_num.append(float(vals[x]))
            else:
                ans_num.append(float(x))
    return round(ans_num[0],2)

fin=open("D:\\GZN\\HIT\\个人文件\\数据结构与算法\\Lab1\\test.txt","r")
for str1 in fin:
    s=str1.strip()
    str_list=[]
    s_len=len(s)
    i=0
    j=1
    while (i<=j and j<s_len):
        while (s[j] in NUM or (s[j] not in ops and s[j] not in lv.keys())): j+=1
        str_list.append(s[i:i+1])
        if (i+1<j): str_list.append(s[i+1:j])
        i=j
        j+=1
    for x in str_list:
        if (x=='#'): str_list.remove(x)
    print (str_list)
    shift_list=Shift(str_list)
    print (' '.join(shift_list))
    
    vals.clear()
    for item in shift_list:
        if (item[0] not in NUM and item[0] not in lv.keys() and item not in vals.keys()):
            print (item+'=',end='')
            vals[item]=input()
    print (' '.join(str_list),'=',Calc(shift_list))
    os.system("pause")