using v8::Null;

#define VALIDATE_AND_RETURN_STRING(args, argi, variable) \
  if (args.Length() <= argi || !args[argi]->IsString()) { \
    return Nan::ThrowTypeError("Argument  " #argi " has to be string!"); \
  } \
  Nan::Utf8String variable(args[argi]->ToString(Nan::GetCurrentContext()).FromMaybe(v8::Local<v8::String>()));

#define VALIDATE_AND_RETURN_INTEGER(args, argi, variable) \
  if (args.Length() <= argi || !args[argi]->IsNumber()) { \
    return Nan::ThrowTypeError("Argument  " #argi " has to be integer!"); \
  } \
  int variable = args[argi]->Int32Value(Nan::GetCurrentContext()).FromJust(); 

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

