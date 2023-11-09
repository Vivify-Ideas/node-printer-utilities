#include <wkhtmltox/pdf.h>
#include "macros.h"

void CleanupObjects();
void SetGlobalSettings(v8::Local<v8::Object> page_info, v8::Local<v8::Object> file_info);
void ConvertHtmlToPdf(char* html, v8::Local<v8::Object> page_info, v8::Local<v8::Object> file_info);
void error(wkhtmltopdf_converter * c, const char * msg);