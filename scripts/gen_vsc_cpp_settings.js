// scripts/gen_vscode_config.js
const fs = require('fs');
const path = require('path');

const findnodeapih = () => {
    const gypi = fs.readFileSync("./build/config.gypi", 'utf8');
    const match = gypi.match(/"nodedir": "([^"]+)"/);
    if (!match) throw new Error("Cannot find nodedir");
    return match[1] + "/include/node";
};

const nodeApiPath = findnodeapih();

const config = {
    configurations: [
        {
            name: "Win32",
            includePath: [
                "${default}",
                // "${workspaceFolder}/maze_generator",
                "${workspaceFolder}/node_modules/node-addon-api",
                nodeApiPath.replace(/\\/g, "/")
            ],
            defines: [
                "_DEBUG",
                "UNICODE",
                "_UNICODE",
                "NAPI_DISABLE_CPP_EXCEPTIONS"
            ],
            cStandard: "c11",
            cppStandard: "c++17",
            intelliSenseMode: "windows-msvc-x64"
        }
    ],
    version: 4
};

fs.writeFileSync(
    path.join(".vscode", "c_cpp_properties.json"),
    JSON.stringify(config, null, 2)
);

console.log('c_cpp_properties.json generated with nodeApiPath:', nodeApiPath);