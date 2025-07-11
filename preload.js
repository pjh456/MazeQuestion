// preload.js
const path = require('path');
const maze_api = require(path.resolve(__dirname, 'build/Release/maze.node'));
const vm = require('vm');
const { contextBridge, ipcRenderer } = require('electron');

let nativeMaze = null;
let logCallback = (msg) => console.log(msg);
let moveCallback = (changed_pos_arr) => console.log("move!");
let initCallback = () => console.log("init!");

let maze_object_map = { context_maze: nativeMaze };
let updateCounter = 0;

const move_functions = ['move_up', 'move_down', 'move_left', 'move_right'];

function buildMazeApiMap() {
    return {
        look_up: (idx = 0) => maze_object_map.context_maze.look_up(idx),
        look_down: (idx = 0) => maze_object_map.context_maze.look_down(idx),
        look_left: (idx = 0) => maze_object_map.context_maze.look_left(idx),
        look_right: (idx = 0) => maze_object_map.context_maze.look_right(idx),
        stand: (idx = 0) => maze_object_map.context_maze.stand(idx),

        move_up: (idx = 0) => maze_object_map.context_maze.move_up(idx),
        move_down: (idx = 0) => maze_object_map.context_maze.move_down(idx),
        move_left: (idx = 0) => maze_object_map.context_maze.move_left(idx),
        move_right: (idx = 0) => maze_object_map.context_maze.move_right(idx),

        start_pos: () => maze_object_map.context_maze.start_pos(),
        end_pos: () => maze_object_map.context_maze.end_pos(),
        current_pos: (idx = 0) => maze_object_map.context_maze.current_pos(idx),

        copy_pos: (idx = 0) => maze_object_map.context_maze.copy_pos(idx),
        remove_pos: (idx = 0) => maze_object_map.context_maze.remove_pos(idx),

        row_count: () => maze_object_map.context_maze.row_count(),
        col_count: () => maze_object_map.context_maze.col_count(),
        pos_size: () => maze_object_map.context_maze.pos_size()
    };
}

contextBridge.exposeInMainWorld('sandbox', {
    run: async (code) => {
        updateCounter = 0;
        ipcRenderer.send('run-user-code', code);
    },
    onPrint: (callback) => { logCallback = callback; }
});

ipcRenderer.on('from-vm', (event, msg) => {
    const maze_api_map = buildMazeApiMap();
    console.log(msg);

    switch (msg.type) {
        case 'done':
            if (updateCounter === 0) moveCallback();
            break;
        case 'changed':
            ipcRenderer.send('get-data', { id: msg.id, data: maze_object_map.context_maze.changed_pos() });
            break;
        case 'update':
            break;
        case 'print':
            logCallback(msg.data);
            break;
        default:
            if (move_functions.includes(msg.type)) {
                updateCounter++;
                maze_api_map[msg.type](msg.data);
            }
            else {
                ipcRenderer.send('get-data', { id: msg.id, data: maze_api_map[msg.type](msg.data) });
            }
            break;
    }
});

ipcRenderer.on('from-system', (event, msg) => {
    // const maze_api_map = buildMazeApiMap();
    console.log('from-system', msg);
    if (msg.type === 'update') {
        updateCounter--;
        moveCallback(msg.data);
    }
    else if (msg.type === 'done' || msg.type === 'changed' || msg.type === 'print') return;
    else if (move_functions.includes(msg.type)) return;
});

// maze api

contextBridge.exposeInMainWorld('maze_api', {
    create: (rows, cols) => {
        maze_object_map.context_maze = new maze_api.MazeAdapter(rows, cols);
        const maze_api_map = buildMazeApiMap();
        return {
            ...maze_api_map,
            map_data: () => maze_object_map.context_maze.map_data(),
            block_type: (r, c) => maze_object_map.context_maze.block_type(r, c)
        }
    },
    reset: () => { maze_object_map.context_maze.reset(); console.log("reset!"); initCallback(); },
    changed: () => maze_object_map.context_maze.changed_pos(),
    onMove: (callback) => { moveCallback = callback; },
    onInit: (callback) => { initCallback = callback; },
});

