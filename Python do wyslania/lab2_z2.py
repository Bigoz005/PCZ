import  xml.dom.minidom

#zad2

class Osoba:
  def __init__(self):
    self.nazwisko = ""
    self.imie = ""
    self.adres = Adres()


class Adres:
  def __init__(self):
    self.ulica = "Def"
    self.numer = 0
    self.miasto = "Def"

document = xml.dom.minidom.parse("osoby.xml")

mapping = {}
listaOsob = []
i = 0

for nodeOsoby in document.getElementsByTagName("student"):
  osoba = Osoba()

  osoba.imie = nodeOsoby.getAttribute("imie")
  osoba.nazwisko = nodeOsoby.getAttribute("nazwisko")
  adresy = nodeOsoby.getElementsByTagName("adres")
  ulica = nodeOsoby.getElementsByTagName("ulica")
  osoba.adres.ulica = str(ulica[0].firstChild.data).replace("\n", "").replace("\t", "")
  numer = nodeOsoby.getElementsByTagName("numer")
  osoba.adres.numer = str(numer[0].firstChild.data).replace("\n", "").replace("\t", "")
  miejscowosc = nodeOsoby.getElementsByTagName("miejscowosc")
  osoba.adres.miasto = str(miejscowosc[0].firstChild.data).replace("\n", "").replace("\t", "")
  listaOsob.append(osoba)

  nodeText = osoba.imie + " " + osoba.nazwisko + " " + str(ulica[0].firstChild.data) + " " + str(numer[0].firstChild.data) + " " + str(miejscowosc[0].firstChild.data)
  mapping[i] = nodeText.replace("\n","").replace("\t","")
  i += 1

print(mapping)

for osoba in listaOsob:
    print(osoba.imie, osoba.nazwisko, osoba.adres.miasto, osoba.adres.numer, osoba.adres.ulica)