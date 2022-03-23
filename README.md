# Node Printer utility for Electron/NodeJS Applications

## Installation

```bash
npm install --save node-printer-utility
```

## Usage
This package offers printing of a HTML string through conversion to PDF using native ```wkhtmltox``` package, and then printing using native ```CUPS``` package.
If you wish to use printing capabilities of this package, you first have to call ```initSettings()``` method at the app startup, so the wkhtmltox initiates its configuration, and also be sure to to call ```deinitSettings()``` the application exit.

```js
const printer = require('node-printer-utility');

console.log(getDefaultPrinter());
```

## Exported Methods

```js
initSettings()
```
```js
deinitSettings()
```
```js
getDefaultPrinter()
```

Html prop is a HTML string that will be converted to the PDF and then printer. Be sure to use PDF safe CSS.
PageHeight and PageWidth props are needed so that the PDF converter knows the dimensions of the page.
PaperSize property is used for the CUPS package to set the MEDIA property.
Success and Error props are callbacks used for additional JS work needed to be done after printing operation finishes.
Success callback returns JobID integer, and error callback returns string message with some information about the error.
```js
sendToPrinter(html, pageHeight, pageWidth, paper_size, success, error)
```
