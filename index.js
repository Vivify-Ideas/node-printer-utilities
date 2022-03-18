const betshop_printer = require('./build/Release/betshop_printer');

function getDefaultPrinter() {
    return betshop_printer.getDefaultPrinter();
}

function sendToPrinter() {
    return betshop_printer.sendToPrinter();
}

module.exports.getDefaultPrinter = getDefaultPrinter;
module.exports.sendToPrinter = sendToPrinter;