#include "printer.h"

int PrintPdfDocument(char* papier_size) {
  cups_dest_t *dest = cupsGetNamedDest(CUPS_HTTP_DEFAULT, NULL, NULL);
  if (dest == NULL) {
    printf("Default printer is not connected.\n");
    // throw "Default printer is not connected.\n";
  }

  int num_options = 0;
  cups_option_t *options = NULL;

  num_options = cupsAddOption(CUPS_MEDIA, papier_size, num_options, &options);
  int job_id = cupsPrintFile2(CUPS_HTTP_DEFAULT, dest->name, "test.pdf", "test", num_options, options);

  if (job_id == 0) {
    // throw "Error while printing, job_id is 0";
  }

  cupsFreeOptions(num_options, options);
  return job_id;
}

v8::Local<v8::Object> GetDefaultPrinterObject() {
  cups_dest_t *printer = NULL;
  int printers_size = cupsGetDests(&printer);

  v8::Local<v8::Object> default_printer_result = V8_NEW_OBJECT();
  for(int i = 0; i < printers_size; ++i, ++printer) {
    if (printer->is_default != DEFAULT_PRINTER) {
      continue;
    }

    v8::Local<v8::Object> result_printer_options = FormatPrinterOptions(printer->options, printer->num_options);

    Nan::Set(default_printer_result, Nan::New<v8::String>("name").ToLocalChecked(), Nan::New<v8::String>(printer->name).ToLocalChecked());
    Nan::Set(default_printer_result, Nan::New<v8::String>("options").ToLocalChecked(), result_printer_options);
    break;
  }

  cupsFreeDests(printers_size, printer);
  return default_printer_result;
}

v8::Local<v8::Object> FormatPrinterOptions(cups_option_t *options, int option_size) {
  v8::Local<v8::Object> result_printer_options = V8_NEW_OBJECT();
  for(int j = 0; j < option_size; ++j, ++options) {
    Nan::Set(result_printer_options, V8_STRING_NEW_UTF8(options->name), V8_STRING_NEW_UTF8(options->value));
  }

  return result_printer_options;
}