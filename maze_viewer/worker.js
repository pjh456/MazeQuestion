
const { parentPort } = require('worker_threads');
const vm = require('vm');
const { profileEnd } = require('console');

const move_functions = ['move_up', 'move_down', 'move_left', 'move_right'];
const async_functions = [
    'look_up', 'look_down', 'look_left', 'look_right', 'stand',
    ...move_functions,
    'start_pos', 'end_pos', 'current_pos',
    'copy_pos', 'remove_pos',
    'row_count', 'col_count', 'pos_size',
    'print'
];

const delayms = 50;
const delay = (ms) => new Promise(res => setTimeout(res, ms));

let requestIdCount = 0;
const requestMap = new Map();

function getId() { return `req_${requestIdCount++}`; }

function sendAndWait(type, data) {
    const id = getId();

    return new Promise((resolve) => {
        requestMap.set(id, resolve);
        parentPort.postMessage({ id, type, data });
    });
}

async function send(type, data) {
    if (move_functions.includes(type)) {
        parentPort.postMessage({ type, data });
        const val = await sendAndWait('changed');

        // console.log("receive val:", val);

        await delay(delayms);
        parentPort.postMessage({ type: 'update', data: val });
    }
    else if (type === 'print') {
        parentPort.postMessage({ type, data });
    }
    else {
        const val = await sendAndWait(type, data);

        // console.log("receive val:", val);

        return val;
    }
}

const context = vm.createContext({
    look_up: async (idx = 0) => await send('look_up', idx),
    look_down: async (idx = 0) => await send('look_down', idx),
    look_left: async (idx = 0) => await send('look_left', idx),
    look_right: async (idx = 0) => await send('look_right', idx),
    stand: async (idx = 0) => await send('stand', idx),

    move_up: async (idx = 0) => await send('move_up', idx),
    move_down: async (idx = 0) => await send('move_down', idx),
    move_left: async (idx = 0) => await send('move_left', idx),
    move_right: async (idx = 0) => await send('move_right', idx),

    start_pos: async () => await send('start_pos'),
    end_pos: async () => await send('end_pos'),
    current_pos: async (idx = 0) => await send('current_pos', idx),

    copy_pos: async (idx = 0) => await send('copy_pos', idx),
    remove_pos: async (idx = 0) => await send('remove_pos', idx),

    row_count: async () => await send('row_count'),
    col_count: async () => await send('col_count'),
    pos_size: async () => await send('pos_size'),

    print: async (...args) => await send('print', args.join(' '))
});

function insertAwait(code, fnList) {
    const fnPattern = new RegExp(`\\b(${fnList.join('|')})\\s*\\(`, 'g');
    return code.replace(fnPattern, 'await $1(');
}

parentPort.on('message', async (msg) => {
    if (msg.id && requestMap.has(msg.id)) {
        requestMap.get(msg.id)(msg.data);
        requestMap.delete(msg.id);
    }
    else {
        try {
            const awaitCode = insertAwait(msg.code, async_functions);
            const asyncCode = `(async () => { ${awaitCode} })()`;
            console.log(asyncCode);
            await vm.runInContext(asyncCode, context);
            send('done');
        } catch (e) {
            send('error', e.message);
        }
    }
});