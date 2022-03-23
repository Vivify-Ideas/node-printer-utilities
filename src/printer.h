#include <cups/cups.h>
#include <cups/ppd.h>
#include "macros.h"

#define DEFAULT_PRINTER 1

void PrintPdfDocument(char* papier_size);
v8::Local<v8::Object> GetDefaultPrinterObject();
v8::Local<v8::Object> FormatPrinterOptions(cups_option_t *options, int option_size);