#include <wkhtmltox/pdf.h>
#include "macros.h"

void CleanupObjects();
void SetGlobalSettings(char* page_height, char* page_width);
void ConvertHtmlToPdf(char* html);
void error(wkhtmltopdf_converter * c, const char * msg);