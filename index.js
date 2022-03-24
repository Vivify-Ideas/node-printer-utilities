const printer = require('node-gyp-build')(__dirname);

function getDefaultPrinter() {
  return printer.getDefaultPrinter();
}

function sendToPrinter(html, pageHeight, pageWidth, page_size, success, error) {
  return printer.sendToPrinter(html, pageHeight, pageWidth, page_size, success, error);
}

function deinitSettings() {
  return printer.deinitSettings();
}

function initSettings() {
  return printer.initSettings();
}

function getJobStatus(job_id) {
  return printer.getJobStatus(job_id);
}

module.exports.getDefaultPrinter = getDefaultPrinter;
module.exports.sendToPrinter = sendToPrinter;
module.exports.initSettings = initSettings;
module.exports.deinitSettings = deinitSettings;
module.exports.getJobStatus = getJobStatus;