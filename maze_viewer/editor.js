function log(msg) {
    const logElem = document.getElementById('log');
    logElem.textContent += msg + '\n';
    logElem.scrollTop = logElem.scrollHeight;
}

function cleanLog() {
    const logElem = document.getElementById('log');
    logElem.textContent = '';
}

sandbox.onPrint(log);

require.config({ paths: { vs: '../node_modules/monaco-editor/min/vs' } });

require(['vs/editor/editor.main'], function () {

    monaco.languages.typescript.javascriptDefaults.setCompilerOptions({
        noLib: true, // 不加载默认库
        allowNonTsExtensions: true
    });

    monaco.languages.registerCompletionItemProvider('javascript', {
        provideCompletionItems: () => {
            const fn = (label, insertText, doc) => ({
                label,
                kind: monaco.languages.CompletionItemKind.Function,
                insertText: insertText,
                documentation: { value: doc }
            });

            const suggestions = [
                fn('look_up', 'look_up();', '查看上方的格子类型（start, end, wall, air, body）\n@param idx 观察者编号，默认0'),
                fn('look_down', 'look_down();', '查看下方的格子类型（start, end, wall, air, body）\n@param idx 观察者编号，默认0'),
                fn('look_left', 'look_left();', '查看左方的格子类型（start, end, wall, air, body）\n@param idx 观察者编号，默认0'),
                fn('look_right', 'look_right();', '查看右方的格子类型（start, end, wall, air, body）\n@param idx 观察者编号，默认0'),
                fn('stand', 'stand();', '查看当前位置格子的类型（start, end, wall, air, body）\n@param idx 观察者编号，默认0'),

                fn('move_up', 'move_up();', '向上移动地图上两格，即点坐标一格（若前方为 wall 则无效）\n@param idx 观察者编号，默认0'),
                fn('move_down', 'move_down();', '向下移动地图上两格，即点坐标一格（若前方为 wall 则无效）\n@param idx 观察者编号，默认0'),
                fn('move_left', 'move_left();', '向左移动地图上两格，即点坐标一格（若前方为 wall 则无效）\n@param idx 观察者编号，默认0'),
                fn('move_right', 'move_right();', '向右移动地图上两格，即点坐标一格（若前方为 wall 则无效）\n@param idx 观察者编号，默认0'),

                fn('start_pos', 'start_pos();', '返回起点坐标'),
                fn('end_pos', 'end_pos();', '返回终点坐标'),
                fn('current_pos', 'current_pos();', '返回指定观察者当前位置\n@param idx 观察者编号，默认0'),

                fn('copy_pos', 'copy_pos();', '复制指定观察者位置生成新观察者，其编号为 pos_size().\n@param idx 被复制观察者编号，默认0'),
                fn('remove_pos', 'remove_pos();', '移除指定观察者（弃用）\n@param idx 被移除观察者编号，默认0'),

                fn('row_count', 'row_count();', '返回迷宫节点行数'),
                fn('col_count', 'col_count();', '返回迷宫节点列数'),
                fn('pos_size', 'pos_size();', '返回观察者的总数'),

                fn('print', 'print();', '打印输出调试信息，接受多个参数')
            ];

            return { suggestions };
        }
    });

    window.editor = monaco.editor.create(document.getElementById('editor'), {
        value: `move_up();`,
        language: 'javascript',
        theme: 'vs-dark',
        mouseWheelZoom: true
    });

    window.addEventListener('resize', () => {
        window.editor.layout();
    });
});


function runBFS() {
    log('Loading BFS');
    editor.getModel().setValue(
        `async function bfs_turn() {
    let size = pos_size();
    while(size>0){
        if (stand() === "end") {
            return true;
        }

        if (look_up() == "air") {
            copy_pos();
            move_up(pos_size() - 1);
        }

        if (look_down() == "air") {
            copy_pos();
            move_down(pos_size() - 1);
        }

        if (look_left() == "air") {
            copy_pos();
            move_left(pos_size() - 1);
        }

        if (look_right() == "air") {
            copy_pos();
            move_right(pos_size() - 1);
        }

        remove_pos();
    }
    
    return false;
}

async function bfs() {
    while (!await bfs_turn());
}

await bfs();`
    );
}

function runDFS() {
    log('Loading DFS:');
    editor.getModel().setValue(
        `async function dfs() {
    if (stand() === "end") {
        return true;
    }

    if (look_up() === "air") {
        move_up();
        if (await dfs()) return true;
        move_down();
    }

    if (look_down() === "air") {
        move_down();
        if (await dfs()) return true;
        move_up();
    }

    if (look_left() === "air") {
        move_left();
        if (await dfs()) return true;
        move_right();
    }

    if (look_right() === "air") {
        move_right();
        if (await dfs()) return true;
        move_left();
    }

    return false;
}

await dfs();`
    );
}
function runUserCode() {
    const code = editor.getValue();
    maze_api.reset();
    sandbox.run(code);
}

window.editorModule = {
    runBFS,
    runDFS,
    runUserCode
}

window.loggerModule = {
    log,
    cleanLog
}

// window.addEventListener('keydown', (event) => {
//     if (event.key === "Enter") { runUserCode(); }
// });