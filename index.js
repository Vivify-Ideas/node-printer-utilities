const betshop_printer = require('./build/Release/betshop_printer');

function getDefaultPrinter() {
    return betshop_printer.getDefaultPrinter();
}

function sendToPrinter(html) {
    return betshop_printer.sendToPrinter(html);
}

module.exports.getDefaultPrinter = getDefaultPrinter;
module.exports.sendToPrinter = sendToPrinter;