import json
import json2table
from tabulate import tabulate


class Osoba:
  def __init__(self):
    self.nazwisko = ""
    self.imie = ""
    self.adres = Adres()

  def toString(self):
      return self.imie, self.nazwisko, self.adres.ulica, self.adres.numer, self.adres.miasto

class Adres:
  def __init__(self):
    self.ulica = "Def"
    self.numer = 0
    self.miasto = "Def"

#zad3
def getJSON(filePathAndName):
    with open(filePathAndName, encoding="utf8") as fp:
        return json.load(fp)

listaOsob = []
myObj = getJSON('osoby.json')

myObj2 = myObj['dane']
for x in myObj2:
    osoba=Osoba()
    for i in range(len(myObj2)):
        osoba.imie = x['student']['imie']
        osoba.nazwisko = x['student']['nazwisko']
        osoba.adres.ulica = x['student']['adres']['ulica']
        osoba.adres.numer = x['student']['adres']['numer']
        osoba.adres.miasto = x['student']['adres']['miejscowosc']
    listaOsob.append(osoba)

print(myObj.get("dane",""))
for osoba in listaOsob:
    print(osoba.imie, osoba.nazwisko, osoba.adres.miasto, osoba.adres.numer, osoba.adres.ulica)

print(" ")

#zad4
infoFromJson = getJSON('osoby.json')
build_direction = "LEFT_TO_RIGHT"
table_attributes = {"style": "width:100%"}

table= []
for osoba in listaOsob:
    table.append(osoba.toString())

print(tabulate(table, tablefmt='html'))
print(" ")

print(json2table.convert(infoFromJson, build_direction=build_direction, table_attributes=table_attributes))
