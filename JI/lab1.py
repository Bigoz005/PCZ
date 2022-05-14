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

#zad2 [[1], [2, 2], [3, 3, 3], [4, 4, 4, 4], [5, 5, 5, 5, 5]]
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
#[(1, 1), (2, 4), (3, 9), (4, 16), (5, 25), (6, 36), (7, 49), (8, 64), (9, 81), (10, 100)]
#[22, 21, 16, 38]
#[7, 14, 21, 28, 42, 49, 56, 63, 77, 84, 91, 98, 112, 119, 126, 133, 147, 154, 161, 168, 182, 189, 196, 203, 217, 224, 231, 238, 252, 259, 266, 273, 287, 294, 301, 308, 322, 329, 336, 343, 357, 364, 371, 378, 392, 399, 406, 413, 427, 434, 441, 448, 462, 469, 476, 483, 497, 504, 511, 518, 532, 539, 546, 553, 567, 574, 581, 588, 602, 609, 616, 623, 637, 644, 651, 658, 672, 679, 686, 693, 707, 714, 721, 728, 742, 749, 756, 763, 777, 784, 791, 798, 812, 819, 826, 833, 847, 854, 861, 868, 882, 889, 896, 903, 917, 924, 931, 938, 952, 959, 966, 973, 987, 994]

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