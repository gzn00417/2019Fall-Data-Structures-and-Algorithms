na=int(input())
a=[]
for i in range(0,na):
    x=int(input())
    a.append(x)
nb=int(input())
b=[]
for i in range(0,nb):
    x=int(input())
    b.append(x)
i=0
j=0
while (b[j]<=a[i]):
    a.insert(i,b[j])
    i+=1
    j+=1
while (i<na and j<nb):
    while (j<nb-1 and b[j]>a[i]): i+=1
    while (b[j]<=a[i]):
        a.insert(i,b[j])
        i+=1
        j+=1
while (j<nb):
    a.append(b[j])
    j+=1
print (a)