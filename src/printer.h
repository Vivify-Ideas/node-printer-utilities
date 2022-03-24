#include <cups/cups.h>
#include <cups/ppd.h>
#include "macros.h"

#define DEFAULT_PRINTER 1

std::string FormatJobStatus(ipp_jstate_t job_state);
void PrintPdfDocument(char* papier_size);
v8::Local<v8::Object> GetDefaultPrinterObject();
v8::Local<v8::Object> FormatPrinterOptions(cups_option_t *options, int option_size);