// preload.js
const path = require('path');
const maze_api = require(path.resolve(__dirname, 'build/Release/maze.node'));
const vm = require('vm');
const { parentPort } = require('worker_threads');
const { contextBridge } = require('electron');

let nativeMaze = null;
let logCallback = (msg) => console.log(msg);
let moveCallback = () => console.log("move!");
let initCallback = () => console.log("init!");

let maze_object_map = {
    context_maze: nativeMaze
};

let delayms = 300;

function delay(ms) {
    return new Promise(resolve => setTimeout(resolve, ms));
}

function buildMazeApiMap() {
    return {
        look_up: (idx = 0) => maze_object_map.context_maze.look_up(idx),
        look_down: (idx = 0) => maze_object_map.context_maze.look_down(idx),
        look_left: (idx = 0) => maze_object_map.context_maze.look_left(idx),
        look_right: (idx = 0) => maze_object_map.context_maze.look_right(idx),
        stand: (idx = 0) => maze_object_map.context_maze.stand(idx),

        move_up: (idx = 0) => {
            maze_object_map.context_maze.move_up(idx);
            moveCallback();
            return new Promise(resolve => {
                setTimeout(() => {
                    resolve();
                }, delayms);
            });
        },
        move_down: (idx = 0) => {
            maze_object_map.context_maze.move_down(idx);
            moveCallback();
            return new Promise(resolve => {
                setTimeout(() => {
                    resolve();
                }, delayms);
            });
        },
        move_left: (idx = 0) => {
            maze_object_map.context_maze.move_left(idx);
            moveCallback();
            return new Promise(resolve => {
                setTimeout(() => {
                    resolve();
                }, delayms);
            });
        },
        move_right: (idx = 0) => {
            maze_object_map.context_maze.move_right(idx);
            moveCallback();
            return new Promise(resolve => {
                setTimeout(() => {
                    resolve();
                }, delayms);
            });
        },
        // move_up: (idx = 0) => { maze_object_map.context_maze.move_up(idx); moveCallback(); },
        // move_down: (idx = 0) => { maze_object_map.context_maze.move_down(idx); moveCallback(); },
        // move_left: (idx = 0) => { maze_object_map.context_maze.move_left(idx); moveCallback(); },
        // move_right: (idx = 0) => { maze_object_map.context_maze.move_right(idx); moveCallback(); },

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

// Object.freeze(maze_api_map);

// vm

function buildAllowedContext() {
    return {
        print: (...args) => {
            const output = args.map(String).join(' ');
            logCallback(output);
        },
        ...buildMazeApiMap()
    };
}

contextBridge.exposeInMainWorld('sandbox', {
    run: async (code) => {
        const context = vm.createContext(buildAllowedContext());
        try {
            await vm.runInContext(code, context);
        }
        catch (err) {
            logCallback('[Error]' + err.message);
            console.error(err.message);
        }
    },
    onPrint: (callback) => { logCallback = callback; }
});

// maze api

contextBridge.exposeInMainWorld('maze_api', {
    create: (rows, cols) => {
        maze_object_map.context_maze = new maze_api.MazeAdapter(rows, cols);
        const maze_api_map = buildMazeApiMap();
        return {
            ...maze_api_map,
            block_data: () => { return maze_object_map.context_maze.block_data(); }
        }
    },
    reset: () => { maze_object_map.context_maze.reset(); console.log("reset!"); initCallback(); },
    changed: () => maze_object_map.context_maze.changed_pos(),
    onMove: (callback) => { moveCallback = callback; },
    onInit: (callback) => { initCallback = callback; }
});

