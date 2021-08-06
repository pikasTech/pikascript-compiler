import * as fs from 'fs-extra';
import * as path from 'path';
const dirPath = path.resolve(`$(__dirname)`, '../');
console.log(dirPath);
fs.readdir(dirPath, function (err, files) {
    if (err) {
        return console.log("err" + err);
    }

    files.forEach(function (f: string) {
        console.log("f-", f);
    });
});
