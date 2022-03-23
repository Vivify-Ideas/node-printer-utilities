#include "betshop_printer.h"
#include <chrono>

using v8::Null;
using namespace std;

FUNCTION_TO_EXPORT(GetDefaultPrinter) {
  Nan::HandleScope scope;
  v8::Local<v8::Object> default_printer_result = GetDefaultPrinterObject();
  FUNCTION_SET_RETURN_VALUE(default_printer_result);
}

FUNCTION_TO_EXPORT(SendToPrinter) {
  Nan::HandleScope scope;

  VALIDATE_AND_RETURN_STRING(args, 0, html);
  VALIDATE_AND_RETURN_STRING(args, 1, page_height);
  VALIDATE_AND_RETURN_STRING(args, 2, page_width);
  VALIDATE_AND_RETURN_STRING(args, 3, paper_size);
  VALIDATE_AND_RETURN_FUNCTION(args, 4, successCallback);
  VALIDATE_AND_RETURN_FUNCTION(args, 5, errorCallback);

  int job_id = 0;
  double sum = 0;
  auto begin = std::chrono::high_resolution_clock::now();

  ConvertHtmlToPdf(*html, *page_height, *page_width);
  PrintPdfDocument(*paper_size, &job_id);

  if (job_id == 0) {
    v8::Local<v8::Value> responseError(Nan::New<v8::String>("Error while printing.").ToLocalChecked());
    errorCallback->Call(Nan::GetCurrentContext(), Null(args.GetIsolate()), 1, &responseError);
    return;
  }

  auto end = std::chrono::high_resolution_clock::now();
  auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
  printf("Time measured: %.3f seconds.\n", elapsed.count() * 1e-9);
  
  v8::Local<v8::Value> responseSuccess(Nan::New<v8::Number>(job_id));
  successCallback->Call(Nan::GetCurrentContext(), Null(args.GetIsolate()), 1, &responseSuccess);
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