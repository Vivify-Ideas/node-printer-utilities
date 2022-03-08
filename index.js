const betshop_printer = require('./build/Release/betshop_printer');

function getDefaultPrinter() {
    return betshop_printer.getDefaultPrinter();
}

module.exports.getDefaultPrinter = getDefaultPrinter;