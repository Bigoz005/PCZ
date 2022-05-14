// zad1

for (let i = 1; i <= 100; i++) {
  let textToPrint = "";
  if (i % 3 === 0) {
    textToPrint += "Fizz";
  }
  if (i % 5 === 0) {
    textToPrint += "Buzz";
  }
  if (!textToPrint) {
    textToPrint = i;
  }
  console.log(textToPrint);
}

// zad2

function triPascal(rows) {
  let triangle = [];
  if (rows > 0) {
    triangle.push([1]);
    for (let i = 1; i < rows; i++) {
      let row = [];
      let previousRow = triangle[i - 1];
      for (let j = 0; j <= i; j++) {
        if (j === 0) {
          row.push(previousRow[0]);
        } else if (j === i) {
          row.push(previousRow[j - 1]);
        } else {
          row.push(previousRow[j] + previousRow[j - 1]);
        }
      }
      triangle.push(row);
    }
    for (let i = 0; i < rows; i++) {
      let row = triangle[i];
      let stringRow = new Array(rows - i).join("\xa0") + row.join(" ");
      console.log(stringRow);
    }
  }
}
triPascal(6);

// zad3

function saper(matrix) {
  let resultMatrix = [];
  for (let i = 0; i < matrix.length; i++) {
    let row = [];
    for (let j = 0; j < matrix[i].length; j++) {
      if (isPositionMined(matrix, i, j)) {
        row[j] = "*";
      } else {
        let neighbourMinesCount = 0;

        neighbourMinesCount += isPositionMined(matrix, i - 1, j) ? 1 : 0;
        neighbourMinesCount += isPositionMined(matrix, i + 1, j) ? 1 : 0;
        neighbourMinesCount += isPositionMined(matrix, i, j - 1) ? 1 : 0;
        neighbourMinesCount += isPositionMined(matrix, i, j + 1) ? 1 : 0;

        row[j] = neighbourMinesCount;
      }
    }
    resultMatrix.push(row);
  }

  return resultMatrix;

  function isPositionMined(matrix, x, y) {
    return matrix[x] && matrix[x][y] === "*";
  }
}

let minefield = [["", "*", ""], ["*", "", "*"], ["", "*", ""]];

console.log(saper(minefield));

//zad4

function czyPierwsza(liczba) {
  if (liczba <= 1) {
    return false;
  }

  var wynik = true;
  for (i = 2; i < Math.sqrt(liczba); i++) {
    if (liczba % i === 0) {
      wynik = false;
      break;
    }
  }

  return wynik;
}
console.log(czyPierwsza(11));
console.log(czyPierwsza(8));

//zad5

function czyPierwszaZHistoria(liczba) {
  var historia = [];
  if (liczba <= 1) {
    return false;
  }

  var wynik = true;
  for (i = 2; i < Math.sqrt(liczba); i++) {
    historia.push(`${liczba} % ${i} === 0`);
    if (liczba % i === 0) {
      wynik = false;
      break;
    }
  }
  console.log(historia);
  return wynik;
}

var historia = [];
console.log(czyPierwszaZHistoria(11));

historia = [];
console.log(czyPierwszaZHistoria(8));

//zad6
function wartoscReki(karty) {
  var wartoscBezAsow = 0;
  var liczbaAsow = 0;

  if (karty && karty.length) {
    karty.forEach(karta => {
      if (!isNaN(karta) && karta >= 2 && karta <= 10) {
        wartoscBezAsow += karta;
      } else if (karta === "W" || karta === "D" || karta === "K") {
        wartoscBezAsow += 10;
      } else if (karta === "A") {
        liczbaAsow++;
      }
    });
  }

  var wartosc = wartoscBezAsow + liczbaAsow;
  for (i = 1; i <= liczbaAsow; i++) {
    if (wartosc + 10 <= 21) {
      wartosc += 10;
    }
  }

  if (wartoscBezAsow + liczbaAsow > 21) {
    return "FURA";
  }

  return wartosc;
}

console.log(wartoscReki(["A", 10]));
console.log(wartoscReki(["A", "A", 10]));
console.log(wartoscReki([10, 10, 10]));

//zad7

var regex;
regex = new RegExp(/123/g);
console.log(regex.test("123aaaaaaaa"));
console.log(regex.test("aaaa123aaaa"));
console.log(regex.test("aaaaaaaa123"));

//zad8

regex = new RegExp(/^123/);
console.log(regex.test("123aaaaaaaa"));
console.log(regex.test("aaaa123aaaa"));
console.log(regex.test("aaaaaaaa123"));

//zad9

regex = new RegExp(/123$/);
console.log(regex.test("123aaaaaaaa"));
console.log(regex.test("aaaa123aaaa"));
console.log(regex.test("aaaaaaaa123"));

//zad10

regex = new RegExp(/^[+-]?(?:\d+\.?\d*|\d*\.\d+)$/);
console.log(regex.test("123"));
console.log(regex.test("-215"));
console.log(regex.test("+215"));
console.log(regex.test("-123.325"));
console.log(regex.test("+12a3.325"));

//zad11

regex = new RegExp(/^[a-zA-Z_][a-zA-Z0-9_]*$/g);
console.log(regex.test("_variable"));
console.log(regex.test("variable_"));
console.log(regex.test("9variable"));
console.log(regex.test("variable"));

//zad12

regex = new RegExp(/(for|while|if)/g);
console.log(regex.test("for"));
console.log(regex.test("while"));
console.log(regex.test("if"));
console.log(regex.test("else"));

//zad13

regex = new RegExp(//^(((0[1-9]|[12]\d|3[01])\/(0[13578]|1[02])\/((19|[2-9]\d)\d{2}))|((0[1-9]|[12]\d|30)\/(0[13456789]|1[012])\/((19|[2-9]\d)\d{2}))|((0[1-9]|1\d|2[0-8])\/02\/((19|[2-9]\d)\d{2}))|(29\/02\/((1[6-9]|[2-9]\d)(0[48]|[2468][048]|[13579][26])|((16|[2468][048]|[3579][26])00))))$
);
console.log(regex.test("01/03/1000"));
console.log(regex.test("32/03/2000"));

//zad14

console.log(
  "02/23/1996".replace(/([0-9]{2})\/([0-9]{2})\/([0-9]{4})/, "$2/$1/$3")
);
