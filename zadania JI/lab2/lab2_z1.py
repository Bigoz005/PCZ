import xml.sax


# zad1

class ExampleFileHandler(xml.sax.ContentHandler):
    def __init__(self):
        self.InStudent = False
        self.InAdres = False
        self.text = ""
        self.textToPrint = ""
        self.listaOsob = []
        self.iterObject = 0
        self.iter = 0

    def startElement(self, name, attrs):
        if name == "student":
            self.InStudent = True
            global osoba
            osoba = Osoba()
            for (k, v) in attrs.items():
                self.text += k + " " + v + " "
                if (k == "nazwisko"):
                    osoba.nazwisko = v
                if (k == "imie"):
                    osoba.imie = v
        if name == "adres":
            self.listaOsob.append(osoba)
            self.InAdres = True

    def characters(self, ch):
        if self.InStudent and self.InAdres:
            tempText = ch.replace("\n", "").replace("\t", "")

            if (tempText is not ""):
                if (self.iter == 0):
                    self.listaOsob[self.iterObject].adres.ulica = tempText
                if (self.iter == 1):
                    self.listaOsob[self.iterObject].adres.numer = int(tempText)
                if (self.iter == 2):
                    self.listaOsob[self.iterObject].adres.miasto = tempText
                self.iter += 1
                if (self.iter == 3):
                    self.iterObject += 1
                    self.iter = 0
            self.text += ch + " "

    def endElement(self, name):
        if name == "student":
            self.text += "#"
            self.InElement = False
        if name == "adres":
            self.InAdres = False
        self.textToPrint = self.text.replace("\n", "").replace("\t", "").split("#")


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


parser = xml.sax.make_parser()
ExampleFileHandler = ExampleFileHandler()
parser.setContentHandler(ExampleFileHandler)
parser.parse(open("osoby.xml", encoding="utf8"))
#print(ExampleFileHandler.textToPrint)
for osoba in ExampleFileHandler.listaOsob:
    print(osoba.imie, osoba.nazwisko, osoba.adres.miasto, osoba.adres.numer, osoba.adres.ulica)
