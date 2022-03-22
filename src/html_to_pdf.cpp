#include "html_to_pdf.h"

wkhtmltopdf_converter* converter = NULL;
wkhtmltopdf_global_settings* global_settings;
wkhtmltopdf_object_settings* object_settings;

void error(wkhtmltopdf_converter * c, const char * msg) {
	fprintf(stderr, "Error: %s\n", msg);
}

void warning(wkhtmltopdf_converter * c, const char * msg) {
	fprintf(stderr, "Warning: %s\n", msg);
}

void InitSettings() {
	wkhtmltopdf_init(true);
}

void DeinitSettings() {
  wkhtmltopdf_deinit();
}

void ConvertHtmlToPdf(char* html, char* page_height, char* page_width) {

	global_settings = wkhtmltopdf_create_global_settings();
	wkhtmltopdf_set_global_setting(global_settings, "out", "test.pdf");
	wkhtmltopdf_set_global_setting(global_settings, "margin.top", "0");
	wkhtmltopdf_set_global_setting(global_settings, "margin.bottom", "0");
	wkhtmltopdf_set_global_setting(global_settings, "margin.left", "0");
	wkhtmltopdf_set_global_setting(global_settings, "margin.right", "0");
	wkhtmltopdf_set_global_setting(global_settings, "size.height", page_height);
	wkhtmltopdf_set_global_setting(global_settings, "size.width", page_width);

	object_settings = wkhtmltopdf_create_object_settings();

  wkhtmltopdf_set_object_setting(object_settings, "page", html);

  converter = wkhtmltopdf_create_converter(global_settings);
  wkhtmltopdf_add_object(converter, object_settings, NULL);

  wkhtmltopdf_set_error_callback(converter, error);
  wkhtmltopdf_set_warning_callback(converter, warning);

  if (!wkhtmltopdf_convert(converter)) {
    printf("Convertion failed!");
  }

  wkhtmltopdf_destroy_global_settings(global_settings);
  wkhtmltopdf_destroy_object_settings(object_settings);
  wkhtmltopdf_destroy_converter(converter);
}