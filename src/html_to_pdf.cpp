#include <wkhtmltox/pdf.h>

/* Print a message to stderr when an error occurs */
void error(wkhtmltopdf_converter * c, const char * msg) {
	fprintf(stderr, "Error: %s\n", msg);
}

void ConvertHtmlToPdf(char* html) {
  wkhtmltopdf_global_settings * gs;
	wkhtmltopdf_object_settings * os;
	wkhtmltopdf_converter * c;

	wkhtmltopdf_init(false);
	gs = wkhtmltopdf_create_global_settings();
	wkhtmltopdf_set_global_setting(gs, "out", "test.pdf");
	os = wkhtmltopdf_create_object_settings();

  wkhtmltopdf_set_object_setting(os, "page", html);
  c = wkhtmltopdf_create_converter(gs);
  
  wkhtmltopdf_add_object(c, os, NULL);

  wkhtmltopdf_set_error_callback(c, error);

  if (!wkhtmltopdf_convert(c)) {
    printf("Convertion failed!");
  }

  wkhtmltopdf_destroy_converter(c);
  wkhtmltopdf_deinit();
}