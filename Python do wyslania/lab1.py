#zad1
print("zad1")
def main():
    liczba = int(input("Podaj liczbe:"))
    return liczba

if __name__ == "__main__":
    n = main()

str0 = ("*     *\n")
str1 = (" *   * \n")
str2 = ("  * *  \n")
str3 = ("   *   \n")


if n > 5:
    print(str0)
if n > 2:
    print(str1)
    print(str2)

if n==1:
    print(str3)

if n==2:
    print(str3)
    print(str3)

else:
    for i in range(0, n-2):
        print(str3)


print()

#zad2
print("zad2")
n = 5
x = []
for i in range(0,n):
    x.append([i+1])
    for j in range(0,i):
        x[i].append(i+1)

print(x)
print()

#zad3
print("zad3")
#a
n = 10
y = []
for i in range (1, n+1):
    y.append((i,i**2))

print(y)
#b
u = [1998,1999,2004,1982]

k = len(u)

f = []

for i in range(0,k):
    f.append((2020-u[i]))

print(f)
#c
d = []
i=0
while i<1000:
    if i%7==0 and not(i%5==0):
        d.append(i)
    i=i+1

print(d)
print()

#zad4
print("zad4")
#a
kw = [(x,x**2) for x in range(1,11)]
print(kw)
#b
wiek = [(2020-u[x]) for x in range(0,k)]
print(wiek)
#c
modulo = [(x) for x in range (1,1000) if x%7==0 and not(x%5==0)]
print(modulo)
print()


#zad5
print("zad5")
def rev_pack_dict(dict):
    b = {}
    for key in dict:
        b[dict.get(key)] = b.get(dict.get(key), []) + [key]
    return (b)


dict = {'a': 10, 'b': 20, 'c': 30, 'd': 30}
dict = rev_pack_dict(dict)
print(dict)
dict = {8: 6, 2: 6, 4: 6, 6: 6}
dict = rev_pack_dict(dict)
print(dict)