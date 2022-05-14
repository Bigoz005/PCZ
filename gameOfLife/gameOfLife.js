const defaultRows = 20;
const defaultColumns = 20;
const defaultSurvivalRule = "12345";
const defaultBirthRule = "3";
const defaultEvolutionIntervalTime = 500;

let rows;
let columns;
let survivalRule;
let survivalRuleNumbers;
let birthRule;
let birthRuleNumbers;
let gameStarted = false;
let Timer;
let evolutionIntervalTime;
let currentGeneration = [rows];
let nextGeneration = [rows];
let generation;

function createArrays() {
  for (let i = 0; i < rows; i++) {
    currentGeneration[i] = new Array(columns);
    nextGeneration[i] = new Array(columns);
  }
}

function initArrays() {
  for (let i = 0; i < rows; i++) {
    for (let j = 0; j < columns; j++) {
      currentGeneration[i][j] = 0;
      nextGeneration[i][j] = 0;
    }
  }
}

function createGrid() {
  let grid = document.querySelector("#grid");

  let table = document.createElement("table");
  table.setAttribute("id", "gameGrid");
  for (let i = 0; i < rows; i++) {
    let tableRow = document.createElement("tr");
    for (let j = 0; j < columns; j++) {
      let cell = document.createElement("td");
      cell.setAttribute("id", i + "_" + j);
      cell.setAttribute("class", "empty");
      cell.addEventListener("click", onClick);
      tableRow.appendChild(cell);
    }
    table.appendChild(tableRow);
  }
  grid.appendChild(table);
}

function onClick() {
  let cellLocation = this.id.split("_");
  let row = Number(cellLocation[0]);
  let col = Number(cellLocation[1]);

  if (this.className === "empty") {
    this.setAttribute("class", "alive");
    currentGeneration[row][col] = 1;
  } else {
    this.setAttribute("class", "empty");
    currentGeneration[row][col] = 0;
  }
}

function createNextGeneration() {
  for (row in currentGeneration) {
    for (col in currentGeneration[row]) {
      let neighbors = getNeighborCount(row, col);

      if (currentGeneration[row][col] == 1) {
        if (survivalRuleNumbers.includes(neighbors)) {
          nextGeneration[row][col] = 1;
        } else {
          nextGeneration[row][col] = 0;
        }
      } else if (currentGeneration[row][col] == 0) {
        if (birthRuleNumbers.includes(neighbors)) {
          nextGeneration[row][col] = 1;
        }
      }
    }
  }
}

function getNeighborCount(row, col) {
  let count = 0;
  let rowIndex = Number(row);
  let columnIndex = Number(col);

  if (rowIndex - 1 >= 0) {
    if (currentGeneration[rowIndex - 1][columnIndex] == 1) count++;
  }

  if (rowIndex - 1 >= 0 && columnIndex - 1 >= 0) {
    if (currentGeneration[rowIndex - 1][columnIndex - 1] == 1) count++;
  }

  if (rowIndex - 1 >= 0 && columnIndex + 1 < columns) {
    if (currentGeneration[rowIndex - 1][columnIndex + 1] == 1) count++;
  }

  if (columnIndex - 1 >= 0) {
    if (currentGeneration[rowIndex][columnIndex - 1] == 1) count++;
  }

  if (columnIndex + 1 < columns) {
    if (currentGeneration[rowIndex][columnIndex + 1] == 1) count++;
  }

  if (rowIndex + 1 < rows && columnIndex - 1 >= 0) {
    if (currentGeneration[rowIndex + 1][columnIndex - 1] == 1) count++;
  }

  if (rowIndex + 1 < rows && columnIndex + 1 < columns) {
    if (currentGeneration[rowIndex + 1][columnIndex + 1] == 1) count++;
  }

  if (rowIndex + 1 < rows) {
    if (currentGeneration[rowIndex + 1][columnIndex] == 1) count++;
  }

  return count;
}

function updateCurrentGeneration() {
  for (row in currentGeneration) {
    for (col in currentGeneration[row]) {
      currentGeneration[row][col] = nextGeneration[row][col];
      nextGeneration[row][col] = 0;
    }
  }
}

function updateGrid() {
  let cell = "";
  for (row in currentGeneration) {
    for (col in currentGeneration[row]) {
      cell = document.getElementById(row + "_" + col);
      if (currentGeneration[row][col] == 0) {
        if (cell.className === "alive") {
          cell.setAttribute("class", "dead");
        } else {
          cell.setAttribute("class", "empty");
        }
      } else {
        cell.setAttribute("class", "alive");
      }
    }
  }
}

function evolve() {
  createNextGeneration();
  updateCurrentGeneration();
  updateGrid();
  generation++;
  updateCounter();
}

function startStopGame() {
  let startStopButton = document.querySelector("#start-stop-button");

  if (!gameStarted) {
    gameStarted = true;
    startStopButton.value = "Stop game";
    Timer = setInterval(evolve, evolutionIntervalTime);
  } else {
    gameStarted = false;
    startStopButton.value = "Start game";
    clearInterval(Timer);
  }
}

function configureGame() {
  let rowsInput = document.querySelector("#rows-input");
  let columnsInput = document.querySelector("#columns-input");
  let survivalRuleInput = document.querySelector("#survival-rule-input");
  let birthRuleInput = document.querySelector("#birth-rule-input");
  let intervalTimeInput = document.querySelector("#interval-time-input");

  rows = rowsInput.value ? rowsInput.value : defaultRows;
  columns = columnsInput.value ? columnsInput.value : defaultColumns;
  survivalRule = survivalRuleInput.value
    ? survivalRuleInput.value
    : defaultSurvivalRule;
  birthRule = birthRuleInput.value ? birthRuleInput.value : defaultBirthRule;
  evolutionIntervalTime = intervalTimeInput.value
    ? intervalTimeInput.value
    : defaultEvolutionIntervalTime;

  survivalRuleNumbers = survivalRule.split("").map((item) => Number(item));
  birthRuleNumbers = birthRule.split("").map((item) => Number(item));

  resetGrid();
}

function resetGame() {
  if (gameStarted) {
    startStopGame();
  }

  generation = 0;
  updateCounter();

  let rowsInput = document.querySelector("#rows-input");
  let columnsInput = document.querySelector("#columns-input");
  let survivalRuleInput = document.querySelector("#survival-rule-input");
  let birthRuleInput = document.querySelector("#birth-rule-input");
  let intervalTimeInput = document.querySelector("#interval-time-input");

  rowsInput.value = defaultRows;
  columnsInput.value = defaultColumns;
  survivalRuleInput.value = defaultSurvivalRule;
  birthRuleInput.value = defaultBirthRule;
  intervalTimeInput = defaultEvolutionIntervalTime;

  configureGame();
}

function resetGrid() {
  let grid = document.querySelector("#grid");

  while (grid.firstChild) {
    grid.removeChild(grid.firstChild);
  }

  createGrid();
  createArrays();
  initArrays();
}

function updateCounter() {
  let generationCounter = document.querySelector("#generation-counter");
  if (generationCounter) {
    generationCounter.textContent = generation;
  }
}

window.onload = () => {
  resetGame();
};

dragElement(document.getElementById("flex-container"));

function dragElement(elmnt) {
  var pos1 = 0, pos2 = 0, pos3 = 0, pos4 = 0;
  if (document.getElementById(elmnt.id + "-header")) {
    document.getElementById(elmnt.id + "-header").onmousedown = dragMouseDown;
  } else {
    elmnt.onmousedown = dragMouseDown;
  }

  function dragMouseDown(e) {
    e = e || window.event;
    e.preventDefault();
    pos3 = e.clientX;
    pos4 = e.clientY;
    document.onmouseup = closeDragElement;
    document.onmousemove = elementDrag;
  }

  function elementDrag(e) {
    e = e || window.event;
    e.preventDefault();
    pos1 = pos3 - e.clientX;
    pos2 = pos4 - e.clientY;
    pos3 = e.clientX;
    pos4 = e.clientY;
    elmnt.style.top = (elmnt.offsetTop - pos2) + "px";
    elmnt.style.left = (elmnt.offsetLeft - pos1) + "px";
  }

  function closeDragElement() {
    document.onmouseup = null;
    document.onmousemove = null;
  }
}