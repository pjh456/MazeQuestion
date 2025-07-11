const addon = require('../build/Release/maze.node');

// 创建一个 10x10 的迷宫实例
const maze = new addon.MazeAdapter(10, 10);

// 打印地图结构
function printMaze() {
    const map = maze.block_data(); // 这是一个二维数组

    console.log("Maze Map:");
    for (let row of map) {
        let line = row.map(cell => {
            switch (cell) {
                case "wall": return "#";
                case "air": return " ";
                case "start": return "S";
                case "end": return "E";
                case "head": return "?";
                case "body": return "*";
                default: return "?";
            }
        }).join("");
        console.log(line);
    }
}

// 执行打印
printMaze();

maze.move_up();
// maze.move_up();

printMaze();

console.log(maze.start_pos()[0]);
