"use strict"

import { readdir, stat } from 'fs'
import { styleText } from 'node:util';

// global variable
let count = { dir: 0, files: 0 }

// utils function
const dirStyleText = (text) => styleText(['bold', 'blue'], text)
const fileStyleText = (text) => styleText(['reset'], text)
const calculateIndent = (indent) => '  '.repeat(indent)
const print = (name, isDir, indent) => {
    if (isDir) console.log(`${calculateIndent(indent)}${dirStyleText(name)}`)
    else console.log(`${calculateIndent(indent)}${fileStyleText(name)}`)
}

// main recursive function
const walk = async (path, indent) => {
    const files = await new Promise((res, rej) => {
        readdir(path, function (err, _) {
            if (err) rej(err)
            res(_)
        });
    })

    for (let i = 0; i < files.length; i++) {
        const _name = files[i];
        const _path = `${path}/${_name}`
        const _file = await new Promise((res, rej) => {
            stat(_path, (err, _) => {
                if (err) rej(err)
                res(_)
            })
        })
        if (_file.isDirectory()) {
            count.dir += 1;
            print(_name, true, indent)
            await walk(_path, indent + 1)
        } else {
            count.files += 1;
            print(_name, false, indent)
        }
    }
}

const start = async () => {
    // current directory
    let dir = process.cwd();
    // console.log(process.cwd())   // /Users/salvatore/Documents/dev/no-ai-smanetting
    // console.log(__dirname)       // /Users/salvatore/Documents/dev/no-ai-smanetting/tree-node // console.log(import.meta.dirname)
    // console.log(__filename)      // /Users/salvatore/Documents/dev/no-ai-smanetting/tree-node/index.js // console.log(import.meta.filename)

    // args
    const argv = process.argv;
    // i primi due argomenti sono già popolati:
    // 1. path eseguibile node
    // 2. path index.js
    if (argv.length > 2) {
        // 3. directory
        dir = argv[2];
    }
    console.time('walk')
    // console.log('beforewalk')
    await walk(dir, 0)
    // console.log('afterwalk')
    console.timeEnd('walk')
    return count
}

start().then(console.log)
// start().then(function () { console.log('then afterstart') }).catch(function () { console.log('catch afterstart') })