#include <cups/cups.h>
#include <cups/ppd.h>
#include "macros.h"

#define DEFAULT_PRINTER 1
std::string FindJobState(int jobs_count, cups_job_t* jobs, int job_id);
std::string FormatJobStatus(ipp_jstate_t job_state);
void PrintPdfDocument(v8::Local<v8::Object> page_info, int* job_id, v8::Local<v8::Object> file_info);
v8::Local<v8::Object> GetDefaultPrinterObject();
v8::Local<v8::Object> FormatPrinterOptions(cups_option_t *options, int option_size);