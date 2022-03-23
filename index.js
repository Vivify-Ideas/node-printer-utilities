const betshop_printer = require('./build/Release/betshop_printer');

function getDefaultPrinter() {
    return betshop_printer.getDefaultPrinter();
}

function sendToPrinter(html, pageHeight, pageWidth, page_size, success, error) {
  return betshop_printer.sendToPrinter(html, pageHeight, pageWidth, page_size, success, error);
}

function deinitSettings() {
    return betshop_printer.deinitSettings();
}

function initSettings() {
    return betshop_printer.initSettings();
}

module.exports.getDefaultPrinter = getDefaultPrinter;
module.exports.sendToPrinter = sendToPrinter;
module.exports.deinitSettings = deinitSettings;
module.exports.initSettings = initSettings;