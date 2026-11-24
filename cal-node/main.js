import assert from 'node:assert'
import { parseArgs, styleText } from 'node:util'


const { values, positionals } = parseArgs({
    allowPositionals: true,
    // options: {
    //     year: { type: "string" },
    //     month: { type: "string" }
    // }
})

const now = new Date()
let month = now.getMonth() + 1;
let year = now.getFullYear();

switch (positionals.length) {
    case 0:
        // show current month current year
        // printMonth(month, year)
        break;
    case 1:

}




console.log(assert(Object.keys(values).length === 0, "error"))
console.log(assert(positionals.length === 0, "error"))