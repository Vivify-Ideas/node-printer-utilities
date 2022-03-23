#define V8_STRING_NEW_UTF8(value)   Nan::New<v8::String>(value).ToLocalChecked()
#define V8_LOCAL_STRING_FROM_VALUE(value) value->ToString(Nan::GetCurrentContext()).FromMaybe(v8::Local<v8::String>())
#define V8_VALUE_NEW(type, value)   v8::type::New(value)
#define V8_NEW_OBJECT() Nan::New<v8::Object>()
