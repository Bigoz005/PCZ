const ships = document.querySelectorAll('.ship');
const turnIndicator = document.getElementById('turnIndicator');
const boardSize = 10;
const playerCellPrefix = "P"
const computerCellPrefix = "C"
let notHorizontal = false;
let playerTurn = true;
let playerBoard = [];
let computerBoard = [];
const shipTypes = [{ size: 1, count: 4 }, { size: 2, count: 3 }, { size: 3, count: 2 }, { size: 4, count: 1 }]
let draggedShip;
let allShipsPlaced = true;

function initBoardArrays() {
  for (let i = 0; i < boardSize; i++) {
    playerBoard[i] = new Array(boardSize);
    computerBoard[i] = new Array(boardSize);
    playerBoard[i].fill(0);
    computerBoard[i].fill(0);
  }
}

function createGrid(gridContainerId, gridId, cellIdPrefix) {
  let grid = document.getElementById(gridContainerId);

  let table = document.createElement("table");
  table.setAttribute("id", gridId);
  for (let i = 0; i < boardSize; i++) {
    let tableRow = document.createElement("tr");
    for (let j = 0; j < boardSize; j++) {
      let cell = document.createElement("td");
      cell.setAttribute("id", cellIdPrefix + "_" + i + "_" + j);
      if (cellIdPrefix === computerCellPrefix) {
        cell.addEventListener("click", cellClick);

      } else {
        cell.addEventListener('dragover', dragOver);
        cell.addEventListener('dragenter', dragEnter);
        cell.addEventListener('drop', dragDrop);
      }

      tableRow.appendChild(cell);
    }
    table.appendChild(tableRow);
  }
  grid.appendChild(table);
}

function cellClick() {
  if (playerTurn) {
    let cellLocation = this.id.split("_");
    let row = Number(cellLocation[1]);
    let col = Number(cellLocation[2]);
    fire(row, col);
  }
}

function fire(row, col) {
  if (allShipsPlaced) {
    const boardToShoot = playerTurn ? computerBoard : playerBoard;
    const gridCell = getGridCell(playerTurn ? computerCellPrefix : playerCellPrefix, row, col);
    if (!gridCell.hasChildNodes()) {
      const shot = document.createElement('div');
      shot.classList.add("shot");
      if (boardToShoot[row][col] !== 0) {
        shot.classList.add('hit');
        boardToShoot[row][col] = 0;
        checkWin();
      } else {
        shot.classList.add('miss');
        playerTurn = !playerTurn;
      }

      if (!playerTurn) {
        prepareComputerAttack();
        turnIndicator.innerText = "Computer turn";

      } else {
        turnIndicator.innerText = "Your turn";
      }

      gridCell.appendChild(shot);

      return true;
    }

    return false;
  } else {
    alert('Place all ships');
  }

  return true;
}

function prepareComputerAttack() {
  setTimeout(computerAttack, 500);
}

function computerAttack() {
  let result = false;

  while (!result) {
    result = fire(randomInt(boardSize), randomInt(boardSize));
  }
}

function rotate() {
  notHorizontal = !notHorizontal;
  ships.forEach(ship => ship.classList.toggle('notHorizontal'));
}

function dragStart() {
  draggedShip = this;
}

function dragOver(e) {
  e.preventDefault();
}

function dragEnter(e) {
  e.preventDefault();
}

function dragDrop() {
  const cellLocation = this.id.split("_");
  const startRow = Number(cellLocation[1]);
  const startCol = Number(cellLocation[2]);
  const endRow = notHorizontal ? startRow + draggedShip.childElementCount - 1 : startRow;
  const endColumn = notHorizontal ? startCol : startCol + draggedShip.childElementCount - 1;
  dropShip(startRow, startCol, endRow, endColumn)
  if (!document.querySelector('.ship')) {
    allShipsPlaced = true
  };
}

function dropShip(startRow, startCol, endRow, endColumn) {
  if (placeShip(startRow, startCol, endRow, endColumn, playerBoard)) {
    for (let i = startRow; i <= endRow; i++) {
      for (let j = startCol; j <= endColumn; j++) {
        getGridCell(playerCellPrefix, i, j).classList.add('occupied');
      }
    }
    draggedShip.remove();
    draggedShip = null;
  }
}

function placeShip(startRow, startCol, endRow, endColumn, board) {
  if (spaceForShipAvailable(startRow, startCol, endRow, endColumn, board)) {
    for (let i = startRow; i <= endRow; i++) {
      for (let j = startCol; j <= endColumn; j++) {
        board[i][j] = 1;
      }
    }
    return true;
  }
  return false;
}

function spaceForShipAvailable(startRow, startCol, endRow, endColumn, board) {
  if (endRow >= boardSize || endColumn >= boardSize) {
    return false;
  }

  for (let i = startRow - 1; i <= endRow + 1; i++) {
    for (let j = startCol - 1; j <= endColumn + 1; j++) {
      if (i >= 0 && i < boardSize && j >= 0 && j < boardSize) {
        if (board[i][j] !== 0) return false;
      }
    }
  }
  return true;
}

function getGridCell(prefix, row, column) {
  const cellId = prefix + "_" + row + "_" + column;
  return document.getElementById(cellId);
}

function generateComputerBoard() {
  shipTypes.forEach(shipType => {
    for (let i = 0; i < shipType.count; i++) {
      let result = false;
      while (!result) {
        const horizontal = Math.random() < 0.5
        const startRow = horizontal ? randomInt(boardSize) : randomInt(boardSize - shipType.size + 1);
        const startCol = horizontal ? randomInt(boardSize - shipType.size + 1) : randomInt(boardSize);
        const endRow = horizontal ? startRow : startRow + shipType.size - 1;
        const endColumn = horizontal ? startCol + shipType.size - 1 : startCol;
        result = placeShip(startRow, startCol, endRow, endColumn, computerBoard);
      }
    }
  })
}

function checkGameStart() {
  allShipsPlaced = !document.querySelectorAll(".ship").length

  if (!allShipsPlaced) {
    return false;
  } else {
    document.getElementById('startButton').disabled = true;
    return true;
  }
}

function checkWin() {
  const boardToCheck = playerTurn ? computerBoard : playerBoard;
  let shipInBoard = false;
  for (let i = 0; i < boardSize; i++) {
    for (let j = 0; j < boardSize; j++) {
      if (boardToCheck[i][j]) {
        shipInBoard = true;
        break;
      }
    }
  }
  if (!shipInBoard) {
    const msg = playerTurn ? "You Won " : "You lost";
    alert(msg);
    window.location.reload();
  }
}

function startGame() {

  allShipsPlaced = checkGameStart();

  if (allShipsPlaced) {
    turnIndicator.innerText = "Your Turn";
  } else {
    alert('Place all ships');
  }
}

function randomInt(max) {
  return Math.floor(Math.random() * Math.floor(max));
}

window.onload = () => {
  initBoardArrays()
  createGrid("playerGridContainer", "playerGrid", playerCellPrefix);
  createGrid("computerGridContainer", "computerGrid", computerCellPrefix);
  generateComputerBoard();
  ships.forEach(ship => {
    ship.addEventListener('dragstart', dragStart);
  })
  document.getElementById('rotateButton').addEventListener('click', rotate);
  document.getElementById('startButton').addEventListener('click', startGame);
  startGame();
};
