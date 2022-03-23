#include "betshop_printer.h"
#include <chrono>

using namespace std;

FUNCTION_TO_EXPORT(GetDefaultPrinter) {
  Nan::HandleScope scope;
  v8::Local<v8::Object> default_printer_result = GetDefaultPrinterObject();
  FUNCTION_SET_RETURN_VALUE(default_printer_result);
}

FUNCTION_TO_EXPORT(SendToPrinter) {
  Nan::HandleScope scope;
  Nan::Utf8String html(V8_LOCAL_STRING_FROM_VALUE(info[0]));
  Nan::Utf8String page_height(V8_LOCAL_STRING_FROM_VALUE(info[1]));
  Nan::Utf8String page_width(V8_LOCAL_STRING_FROM_VALUE(info[2]));
  Nan::Utf8String papier_size(V8_LOCAL_STRING_FROM_VALUE(info[3]));

  double sum = 0;
  auto begin = std::chrono::high_resolution_clock::now();

  ConvertHtmlToPdf(*html, *page_height, *page_width);
  int job_id = PrintPdfDocument(*papier_size);

  auto end = std::chrono::high_resolution_clock::now();
  auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
  printf("Time measured: %.3f seconds.\n", elapsed.count() * 1e-9);

  FUNCTION_SET_RETURN_VALUE(job_id);
}

FUNCTION_TO_EXPORT(InitSettings) {
  InitSettings();
}

FUNCTION_TO_EXPORT(DeinitSettings) {
  DeinitSettings();
}

void Init(v8::Local<v8::Object> exports) {
  v8::Local<v8::Context> context = Nan::GetCurrentContext();
  FUNCTION_EXPORT(context, GetDefaultPrinter, "getDefaultPrinter");
  FUNCTION_EXPORT(context, SendToPrinter, "sendToPrinter");
  FUNCTION_EXPORT(context, InitSettings, "initSettings");
  FUNCTION_EXPORT(context, DeinitSettings, "deinitSettings");
}

NODE_MODULE(betshop_printer, Init)