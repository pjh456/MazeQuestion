const gridElem = document.getElementById('grid');
let maze = null;
let show_unexplored = false;

function randomCreateGrid() {
    const rows = parseInt(document.getElementById('rows-input').value);
    const cols = parseInt(document.getElementById('cols-input').value);

    maze = maze_api.create(rows, cols);
    initializeGrid();
}

function initializeGrid() {
    const map_rows = 2 * maze.row_count() + 1;
    const map_cols = 2 * maze.col_count() + 1;

    const map = maze.block_data();

    gridElem.style.gridTemplateColumns = `repeat(${map_cols}, 1fr)`;
    gridElem.style.gridTemplateRows = `repeat(${map_rows}, 1fr)`;
    gridElem.innerHTML = '';
    for (let r = 0; r < map_rows; r++) {
        for (let c = 0; c < map_cols; c++) {
            const cell = document.createElement('div');
            cell.id = `grid_cell{${r},${c}}`;
            if (show_unexplored) {
                cell.className = 'cell ' + map[r][c];
            }
            else if (map[r][c] === 'start' || map[r][c] === 'end' || map[r][c] === 'body') {
                cell.className = 'cell ' + map[r][c];
            }
            else if (r === 0 || r === map_rows - 1 || c === 0 || c === map_cols - 1) {
                cell.className = 'cell ' + map[r][c];
            }
            else {
                cell.className = 'cell unexplored';
            }
            gridElem.appendChild(cell);
        }
    }

    const size = Math.min(500 / map_cols, 500 / map_rows);
    gridElem.style.width = `${map_cols * size}px`;
    gridElem.style.height = `${map_rows * size}px`;
}

function updateGrid() {
    for (const changed_pos of maze_api.changed()) {
        [r, c, t] = changed_pos;
        document.getElementById(`grid_cell{${r},${c}}`).className = `cell ` + t;
    }
}

function changeUnexploredFlag(checkbox) {
    show_unexplored = checkbox.checked;
    initializeGrid();
}

randomCreateGrid();

maze_api.onInit(initializeGrid);
maze_api.onMove(updateGrid);


window.gridModule = {
    randomCreateGrid,
    initializeGrid,
    updateGrid,
    changeUnexploredFlag
}