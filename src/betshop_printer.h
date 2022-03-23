#include <nan.h>
#include "converter.h"
#include "converter.cpp"
#include "printer.h"
#include "printer.cpp"
#include "macros.h"

#define FUNCTION_TO_EXPORT(name) void name(const Nan::FunctionCallbackInfo<v8::Value>& info)
#define FUNCTION_SET_RETURN_VALUE(value) info.GetReturnValue().Set(value);
#define FUNCTION_EXPORT(context, function, function_name) \
  exports->Set( \
    context, \
    Nan::New(function_name).ToLocalChecked(), \
    Nan::New<v8::FunctionTemplate>(function) \
      ->GetFunction(context) \
      .ToLocalChecked() \
  );
