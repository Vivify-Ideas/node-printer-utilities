#include "betshop_printer.h"

using namespace std;

NAN_METHOD(getDefaultPrinter) {
  Nan::HandleScope scope;
  v8::Local<v8::Object> default_printer_result = GetDefaultPrinterObject();
  info.GetReturnValue().Set(default_printer_result);
}

NAN_METHOD(getJobStatus) {
  VALIDATE_AND_RETURN_INTEGER(info, 0, job_id);
  v8::Local<v8::String> job_status = GetJobStatus(job_id);
  info.GetReturnValue().Set(job_status);
}

NAN_METHOD(checkIsJobCompleted) {
  VALIDATE_AND_RETURN_INTEGER(info, 0, job_id);
  v8::Local<v8::String> job_status = CheckIsJobCompleted(job_id);
  info.GetReturnValue().Set(job_status);
}

NAN_METHOD(sendToPrinter) {
  int job_id = 0;

  VALIDATE_AND_RETURN_STRING(info, 0, html);
  VALIDATE_AND_RETURN_STRING(info, 1, page_height);
  VALIDATE_AND_RETURN_STRING(info, 2, page_width);
  VALIDATE_AND_RETURN_STRING(info, 3, paper_size);
  VALIDATE_AND_RETURN_FUNCTION(info, 4, success_callback);
  VALIDATE_AND_RETURN_FUNCTION(info, 5, error_callback);

  ConvertHtmlToPdf(*html, *page_height, *page_width);
  PrintPdfDocument(*paper_size, &job_id);

  if (job_id == 0) {
    v8::Local<v8::Value> error_response(Nan::New<v8::String>("Error while printing.").ToLocalChecked());
    v8::MaybeLocal<v8::Value> error = error_callback->Call(Nan::GetCurrentContext(), Null(info.GetIsolate()), 1, &error_response);
    return;
  }
  
  v8::Local<v8::Value> success_response(Nan::New<v8::Number>(job_id));
  v8::MaybeLocal<v8::Value> success = success_callback->Call(Nan::GetCurrentContext(), Null(info.GetIsolate()), 1, &success_response);
  info.GetReturnValue().Set(job_id);
}

NAN_METHOD(initSettings) {
  InitSettings();
}

NAN_METHOD(deinitSettings) {
  DeinitSettings();
}

NAN_MODULE_INIT(Init) {
  NAN_EXPORT(target, getDefaultPrinter);
  NAN_EXPORT(target, sendToPrinter);
  NAN_EXPORT(target, initSettings);
  NAN_EXPORT(target, deinitSettings);
  NAN_EXPORT(target, getJobStatus);
  NAN_EXPORT(target, checkIsJobCompleted);
}

NODE_MODULE(betshop_printer, Init)