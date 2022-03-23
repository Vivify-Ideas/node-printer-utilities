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
  Nan::Utf8String html(V8_LOCAL_STRING_FROM_VALUE(info[0]));
  Nan::Utf8String page_height(V8_LOCAL_STRING_FROM_VALUE(info[1]));
  Nan::Utf8String page_width(V8_LOCAL_STRING_FROM_VALUE(info[2]));
  Nan::Utf8String papier_size(V8_LOCAL_STRING_FROM_VALUE(info[3]));

  v8::Local<v8::Function> successCallback = info[4].As<v8::Function>();
  v8::Local<v8::Function> errorCallback = info[5].As<v8::Function>();

  double sum = 0;
  auto begin = std::chrono::high_resolution_clock::now();
  int job_id = 0;
  try {
    ConvertHtmlToPdf(*html, *page_height, *page_width);
    job_id = PrintPdfDocument(*papier_size);
  } 
  catch (char* errorMessage) {
    v8::Local<v8::Value> responseError(Nan::New<v8::String>(errorMessage).ToLocalChecked());
    errorCallback->Call(Nan::GetCurrentContext(), Null(info.GetIsolate()), 1, &responseError);
    info.GetIsolate()->ThrowException(Nan::Error(errorMessage));
    return;
  }

  auto end = std::chrono::high_resolution_clock::now();
  auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
  printf("Time measured: %.3f seconds.\n", elapsed.count() * 1e-9);

  
  v8::Local<v8::Value> responseSuccess(Nan::New<v8::Number>(job_id));
  successCallback->Call(Nan::GetCurrentContext(), Null(info.GetIsolate()), 1, &responseSuccess);
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