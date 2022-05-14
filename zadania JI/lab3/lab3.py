from random import sample

class Pytanie:
  def __init__(self, nr, pyt, odp, a, b, c, d):
    self.nr = nr
    self.pyt = pyt
    self.odp = odp
    self.a = a
    self.b = b
    self.c = c
    self.d = d

  def wypisz(self, odp):
    print("\q", self.pyt)
    print("\\b")
    if 'a' == odp:
      print("\\a", self.a)
    else:
      print("\i", self.a)
    if 'b' == odp:
      print("\\a", self.b)
    else:
        print("\i", self.b)
    if 'c' == odp:
      print("\\a", self.c)
    else:
        print("\i", self.c)
    if 'd' == odp:
      print("\\a", self.d)
    else:
        print("\i", self.d)
    print("\e")
    print("Odpowiedz:")

  def odpowiedz(self):
    return self.odp

file1 = open("pytania.txt", encoding="utf8")
linez = file1.readlines()
dlugosc = len(linez)
pytania = []
u = 0

nr1 = 0
pyt1 = ""
odp1 = ""
a1 = ""
b1 = ""
c1 = ""
d1 = ""

for i in linez:
  if len(i) > 1:
    znak = i[1]
    xx = len(i)
  if znak == "q":
    nr1 += 1
    pyt1 = i[9:xx]
  if u % 8 == 2:

    znak = i[1]

    if znak == "c":
      odp1 = "a"
      a1 = i[3:xx]
    if znak == "i":
      a1 = i[4:xx]
  if u % 8 == 3:
    znak = i[1]
    if znak == "c":
      odp1 = "b"
      b1 = i[3:xx]
    if znak == "i":
      b1 = i[4:xx]
  if u % 8 == 4:
    znak = i[1]
    if znak == "c":
      odp1 = "c"
      c1 = i[3:xx]
    if znak == "i":
      c1 = i[4:xx]
  if u % 8 == 5:
    znak = i[1]
    if znak == "c":
      odp1 = "d"
      d1 = i[3:xx]
    if znak == "i":
      d1 = i[4:xx]
  if u != 0 and u % 7 == 0:
    pytania.append(Pytanie(nr1, pyt1, odp1, a1, b1, c1, d1))
  u += 1
pytania[len(pytania) - 1] = Pytanie(nr1, pyt1, odp1, a1, b1, c1, d1)

losowanie = sample([0, 1, 2, 3], 3)

pytania[losowanie[0]].wypisz(pytania[losowanie[0]].odpowiedz())

char = input()[0]

if char == pytania[losowanie[0]].odpowiedz():
  print("Prawidlowa odpowiedz")
else:
  print("Bledna odpowiedz")

print(" ")

pytania[losowanie[1]].wypisz(pytania[losowanie[1]].odpowiedz())

char = input()[0]

if char == pytania[losowanie[1]].odpowiedz():
  print("Prawidlowa odpowiedz")
else:
  print("Blędna odpowiedz")

pytania[losowanie[2]].wypisz(pytania[losowanie[2]].odpowiedz())

char = input()[0]

if char == pytania[losowanie[2]].odpowiedz():
  print("Prawidlowa odpowiedz")
else:
  print("Blędna odpowiedz")

print("Prawidlowymi odpowiedziami były:", pytania[losowanie[0]].odpowiedz(), pytania[losowanie[1]].odpowiedz(), pytania[losowanie[2]].odpowiedz())