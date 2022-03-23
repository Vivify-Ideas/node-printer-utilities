#include <nan.h>
#include <cups/cups.h>
#include <cups/ppd.h>
#include <libudev.h>
#include "html_to_pdf.h"
#include "html_to_pdf.cpp"

#define V8_STRING_NEW_UTF8(value)   Nan::New<v8::String>(value).ToLocalChecked()
#define V8_LOCAL_STRING_FROM_VALUE(value) value->ToString(Nan::GetCurrentContext()).FromMaybe(v8::Local<v8::String>())
#define V8_VALUE_NEW(type, value)   v8::type::New(value)
#define V8_NEW_OBJECT() Nan::New<v8::Object>()

#define FUNCTION_TO_EXPORT(name) void name(const Nan::FunctionCallbackInfo<v8::Value>& info)
#define FUNCTION_SET_RETURN_VALUE(value) info.GetReturnValue().Set(value);
#define FUNCTION_EXPORT(context, function, function_name) \
  exports->Set( \
    context, \
    Nan::New(function_name).ToLocalChecked(), \
    Nan::New<v8::FunctionTemplate>(function) \
      ->GetFunction(context) \
      .ToLocalChecked() \
  ); \

#define DEFAULT_PRINTER 1

v8::Local<v8::Object> GetDefaultPrinterObject(cups_dest_t *printer, int printers_size);
v8::Local<v8::Object> FormatPrinterOptions(cups_option_t *options, int option_size);
void BuildInitialDeviceList();
void ConvertHtmlToPdf(char* html);
int PrintPdfDocument(char* papier_size);