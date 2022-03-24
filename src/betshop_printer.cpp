#include "betshop_printer.h"

using namespace std;

FUNCTION_TO_EXPORT(GetDefaultPrinter) {
  Nan::HandleScope scope;
  v8::Local<v8::Object> default_printer_result = GetDefaultPrinterObject();
  FUNCTION_SET_RETURN_VALUE(default_printer_result);
}

FUNCTION_TO_EXPORT(SendToPrinter) {
  Nan::HandleScope scope;

  int job_id = 0;

  VALIDATE_AND_RETURN_STRING(args, 0, html);
  VALIDATE_AND_RETURN_STRING(args, 1, page_height);
  VALIDATE_AND_RETURN_STRING(args, 2, page_width);
  VALIDATE_AND_RETURN_STRING(args, 3, paper_size);
  VALIDATE_AND_RETURN_FUNCTION(args, 4, success_callback);
  VALIDATE_AND_RETURN_FUNCTION(args, 5, error_callback);

  ConvertHtmlToPdf(*html, *page_height, *page_width);
  PrintPdfDocument(*paper_size, &job_id);

  if (job_id == 0) {
    v8::Local<v8::Value> error_response(Nan::New<v8::String>("Error while printing.").ToLocalChecked());
    error_callback->Call(Nan::GetCurrentContext(), Null(args.GetIsolate()), 1, &error_response);
    return;
  }
  
  v8::Local<v8::Value> success_response(Nan::New<v8::Number>(job_id));
  success_callback->Call(Nan::GetCurrentContext(), Null(args.GetIsolate()), 1, &success_response);
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