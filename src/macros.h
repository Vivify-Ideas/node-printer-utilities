#define VALIDATE_AND_RETURN_STRING(args, argi, variable) \
  if (args.Length() <= argi || !args[argi]->IsString()) { \
    return Nan::ThrowTypeError("Argument  " #argi " has to be string!"); \
  } \
  Nan::Utf8String variable(V8_LOCAL_STRING_FROM_VALUE(args[argi]));

#define VALIDATE_AND_RETURN_OBJECT(args, argi, variable) \
  if (args.Length() <= argi || !args[argi]->IsObject()) { \
    return Nan::ThrowTypeError("Argument  " #argi " has to be object!"); \
  } \
  v8::Local<v8::Object> variable = args[argi].As<v8::Object>();

#define VALIDATE_AND_RETURN_FUNCTION(args, argi, variable) \
  if (args.Length() <= argi || !args[argi]->IsFunction()) { \
    return Nan::ThrowTypeError("Argument  " #argi " has to be function!"); \
  } \
  v8::Local<v8::Function> variable = args[argi].As<v8::Function>();

#define V8_STRING_NEW_UTF8(value)   Nan::New<v8::String>(value).ToLocalChecked()
#define V8_LOCAL_STRING_FROM_VALUE(value) value->ToString(Nan::GetCurrentContext()).FromMaybe(v8::Local<v8::String>())
#define V8_VALUE_NEW(type, value)   v8::type::New(value)
#define V8_NEW_OBJECT() Nan::New<v8::Object>()
