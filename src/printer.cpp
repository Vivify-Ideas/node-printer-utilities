#include "printer.h"
#include <string.h>

void PrintPdfDocument(v8::Local<v8::Object> page_info, int* job_id, v8::Local<v8::Object> file_info) {
  cups_dest_t *dest = cupsGetNamedDest(CUPS_HTTP_DEFAULT, NULL, NULL);
  if (dest == NULL) {
    printf("Default printer is not connected.\n");
    return Nan::ThrowTypeError("Default printer is not connected.\n");
  }

  int num_options = 0;
  cups_option_t *options = NULL;
  TO_CHAR_FROM_LOCAL(page_info, "pageSize", papier_size, papier_size_local);
  TO_CHAR_FROM_LOCAL(file_info, "fileName", file_name, file_name_local);
  TO_CHAR_FROM_LOCAL(file_info, "path", path, path_local);
  num_options = cupsAddOption(CUPS_MEDIA, *papier_size, num_options, &options);
  *job_id = cupsPrintFile2(CUPS_HTTP_DEFAULT, dest->name, strcat(*path, *file_name), "File", num_options, options);

  cupsFreeOptions(num_options, options);
}

v8::Local<v8::String> GetJobStatus(int job_id, int cups_which_jobs = CUPS_WHICHJOBS_ALL) {
  cups_job_t* jobs = NULL;
  cups_dest_t* dest = cupsGetNamedDest(CUPS_HTTP_DEFAULT, NULL, NULL);
  int jobs_count = cupsGetJobs2(CUPS_HTTP_DEFAULT, &jobs, dest->name, 0, cups_which_jobs);

  std::string job_state = FindJobState(jobs_count, jobs, job_id);
  v8::Local<v8::String> job_state_response(Nan::New<v8::String>(job_state).ToLocalChecked());
  cupsFreeJobs(jobs_count, jobs);
  return job_state_response;
}

v8::Local<v8::String> CheckIsJobCompleted(int job_id) {
  v8::Local<v8::String> job_state_response(GetJobStatus(job_id, CUPS_WHICHJOBS_COMPLETED));
  return job_state_response;
}

std::string FindJobState(int jobs_count, cups_job_t* job, int job_id) {
  std::string job_state = "";
  for(int i = 0; i < jobs_count; ++i, ++job) {
    if (job->id != job_id) {
      continue;
    }

    job_state = FormatJobStatus(job->state);
    break;
  }

  return job_state;
}

std::string FormatJobStatus(ipp_jstate_t job_state) {
  switch (job_state) {
    case IPP_JOB_PENDING:
      return "IPP_JOB_PENDING";
    case IPP_JOB_HELD:
      return "IPP_JOB_HELD";
    case IPP_JOB_PROCESSING:
      return "IPP_JOB_PROCESSING";
    case IPP_JOB_STOPPED:
      return "IPP_JOB_STOPPED";
    case IPP_JOB_CANCELED:
      return "IPP_JOB_CANCELED";
    case IPP_JOB_COMPLETED:
      return "IPP_JOB_COMPLETED";
    case IPP_JOB_ABORTED:
      return "IPP_JOB_ABORTED";
    default:
      return "IPP_JOB_UNIDENTIFIED";
  }
}

v8::Local<v8::Object> GetDefaultPrinterObject() {
  cups_dest_t *printer = NULL;
  int printers_size = cupsGetDests(&printer);

  v8::Local<v8::Object> default_printer_result = Nan::New<v8::Object>();
  for(int i = 0; i < printers_size; ++i, ++printer) {
    if (printer->is_default != DEFAULT_PRINTER) {
      continue;
    }

    v8::Local<v8::Object> result_printer_options = FormatPrinterOptions(printer->options, printer->num_options);

    Nan::Set(default_printer_result, Nan::New<v8::String>("name").ToLocalChecked(), Nan::New<v8::String>(printer->name).ToLocalChecked());
    Nan::Set(default_printer_result, Nan::New<v8::String>("options").ToLocalChecked(), result_printer_options);
    break;
  }

  cupsFreeDests(printers_size, printer);
  return default_printer_result;
}

v8::Local<v8::Object> FormatPrinterOptions(cups_option_t *options, int option_size) {
  v8::Local<v8::Object> result_printer_options = Nan::New<v8::Object>();
  for(int j = 0; j < option_size; ++j, ++options) {
    Nan::Set(result_printer_options, Nan::New<v8::String>(options->name).ToLocalChecked(), Nan::New<v8::String>(options->value).ToLocalChecked());
  }

  return result_printer_options;
}