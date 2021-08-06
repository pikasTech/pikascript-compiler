"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
var fs = require("fs-extra");
var path = require("path");
var dirPath = path.resolve("$(__dirname)", '../');
console.log(dirPath);
fs.readdir(dirPath, function (err, files) {
    if (err) {
        return console.log("err" + err);
    }
    files.forEach(function (f) {
        console.log("f-", f);
    });
});
//# sourceMappingURL=hello.js.map