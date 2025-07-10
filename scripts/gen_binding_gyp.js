const fs = require('fs');
const path = require('path');

function findCppFiles(dir) {
    let results = [];
    const list = fs.readdirSync(dir, { withFileTypes: true });
    list.forEach((item) => {
        const fullPath = path.join(dir, item.name);
        if (item.isDirectory()) {
            results = results.concat(findCppFiles(fullPath));
        } else if (item.isFile() && item.name.endsWith('.cpp')) {
            results.push(path.relative(process.cwd(), fullPath).replace(/\\/g, '/'));
        }
    });
    return results;
}

const sources = findCppFiles('./maze_generator/');

const binding = {
    targets: [
        {
            target_name: 'maze',
            sources: sources,
            include_dirs: [
                "<!(node -p \"require('node-addon-api').include\")",
                "<!(node -p \"require('node-addon-api').include_dir\")",
                "node_modules/node-addon-api"],
            dependencies: ["<!(node -p \"require('node-addon-api').gyp\")"],
            cflags_cc: ["-std=c++17"],
            defines: ["NAPI_CPP_EXCEPTIONS"]
        }
    ]
};

fs.writeFileSync('binding.gyp', JSON.stringify(binding, null, 2), 'utf8');
console.log('binding.gyp generated with sources:', sources);