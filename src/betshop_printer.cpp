#include "betshop_printer.h"
#include <chrono>

using namespace std;

static udev *udev;
static udev_enumerate *enumerate;
static udev_list_entry *devices, *dev_list_entry;
static udev_device *dev;

FUNCTION_TO_EXPORT(GetDefaultPrinter) {
  Nan::HandleScope scope;

  cups_dest_t *printers = NULL;
  int printers_size = cupsGetDests(&printers);

  v8::Local<v8::Object> default_printer_result = GetDefaultPrinterObject(printers, printers_size);
  cupsFreeDests(printers_size, printers);
  FUNCTION_SET_RETURN_VALUE(default_printer_result);
}

FUNCTION_TO_EXPORT(SendToPrinter) {
  Nan::HandleScope scope;
  Nan::Utf8String html(V8_LOCAL_STRING_FROM_VALUE(info[0]));
  Nan::Utf8String page_height(V8_LOCAL_STRING_FROM_VALUE(info[1]));
  Nan::Utf8String page_width(V8_LOCAL_STRING_FROM_VALUE(info[2]));
  Nan::Utf8String papier_size(V8_LOCAL_STRING_FROM_VALUE(info[3]));

  double sum = 0;
  auto begin = std::chrono::high_resolution_clock::now();

  ConvertHtmlToPdf(*html, *page_height, *page_width);
  int job_id = PrintPdfDocument(*papier_size);

  auto end = std::chrono::high_resolution_clock::now();
  auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
  printf("Time measured: %.3f seconds.\n", elapsed.count() * 1e-9);

  FUNCTION_SET_RETURN_VALUE(job_id);
}

int PrintPdfDocument(char* papier_size) {
 
  cups_dest_t *dest = cupsGetNamedDest(CUPS_HTTP_DEFAULT, NULL, NULL);
  if (dest == NULL) {
    printf("Default printer is not connected.\n");
    return 0;
  }

  int num_options = 0;
  cups_option_t *options = NULL;
 printf(papier_size);
  // num_options = cupsAddOption(CUPS_COPIES, "1", num_options, &options);
  num_options = cupsAddOption(CUPS_MEDIA, papier_size, num_options, &options);

  int job_id = cupsPrintFile2(CUPS_HTTP_DEFAULT, dest->name, "test.pdf", "test", num_options, options);
  // int job_id = cupsPrintFile(dest->name, "test.pdf", "test", num_options, options);
  // cupsFreeOptions(num_options, options);

  return job_id;
}

FUNCTION_TO_EXPORT(InitSettings) {
  InitSettings();
}

FUNCTION_TO_EXPORT(DeinitSettings) {
  DeinitSettings();
}

v8::Local<v8::Object> GetDefaultPrinterObject(cups_dest_t *printer, int printers_size) {
  v8::Local<v8::Object> default_printer_result = V8_NEW_OBJECT();
  for(int i = 0; i < printers_size; ++i, ++printer) {
    if (printer->is_default != DEFAULT_PRINTER) {
      continue;
    }

    v8::Local<v8::Object> result_printer_options = FormatPrinterOptions(printer->options, printer->num_options);

    Nan::Set(default_printer_result, Nan::New<v8::String>("name").ToLocalChecked(), Nan::New<v8::String>(printer->name).ToLocalChecked());
    Nan::Set(default_printer_result, Nan::New<v8::String>("options").ToLocalChecked(), result_printer_options);
    break;
  }

  BuildInitialDeviceList();
  return default_printer_result;
}

v8::Local<v8::Object> FormatPrinterOptions(cups_option_t *options, int option_size) {
  v8::Local<v8::Object> result_printer_options = V8_NEW_OBJECT();
  for(int j = 0; j < option_size; ++j, ++options) {
    Nan::Set(result_printer_options, V8_STRING_NEW_UTF8(options->name), V8_STRING_NEW_UTF8(options->value));
  }

  return result_printer_options;
}

void BuildInitialDeviceList() {
	enumerate = udev_enumerate_new(udev);
	udev_enumerate_scan_devices(enumerate);
	devices = udev_enumerate_get_list_entry(enumerate);
	udev_list_entry_foreach(dev_list_entry, devices) {
	  const char *path;

	
		path = udev_list_entry_get_name(dev_list_entry);
		dev = udev_device_new_from_syspath(udev, path);
    struct udev_device *parent = udev_device_get_parent(dev);

		/* usb_device_get_devnode() returns the path to the device node
		   itself in /dev. */
		if(udev_device_get_devnode(dev) == NULL || udev_device_get_sysattr_value(dev, "idVendor") == NULL) {
			continue;
		}
    printf("%ld\n", strtol(udev_device_get_sysattr_value(dev, "idVendor"), NULL, 16));
    printf("%ld\n", strtol(udev_device_get_sysattr_value(dev, "idProduct"), NULL, 16));
    if(udev_device_get_sysattr_value(dev, "product") != NULL) {
			printf("%s\n", udev_device_get_sysattr_value(dev, "product"));
		}
    if(udev_device_get_sysattr_value(dev, "manufacturer") != NULL) {
			printf("%s\n", udev_device_get_sysattr_value(dev, "manufacturer"));
		}
    if (udev_device_get_sysattr_value(parent, "product") != NULL) {
      printf("Parent: %s\n", udev_device_get_sysattr_value(parent, "product"));
    }
    // printf("%s\n", udev_device_get_sysattr_value(dev, "devnum"));
    // printf("%s\n", udev_device_get_sysattr_value(dev, "busnum"));
    printf("%s\n", udev_device_get_sysname(dev));
    // printf("%s\n", udev_device_get_devnode(dev));
    // printf("%s\n", udev_device_get_devpath(dev));
    // printf("%s\n", udev_device_get_devtype(dev));

    // if (udev_device_get_sysattr_value(dev, "address") != NULL) {
    //   printf("%s\n", udev_device_get_sysattr_value(dev, "address"));
    // }
    // if (udev_device_get_sysattr_value(dev, "portNumbers") != NULL) {
    //   printf("%s\n", udev_device_get_sysattr_value(dev, "portNumbers"));
    // }

    // printf("%s\n", path);
    printf("\n");

		// item->deviceParams.vendorId = strtol (udev_device_get_sysattr_value(dev,"idVendor"), NULL, 16);
		// item->deviceParams.productId = strtol (udev_device_get_sysattr_value(dev,"idProduct"), NULL, 16);
		// if(udev_device_get_sysattr_value(dev,"product") != NULL) {
		// 	item->deviceParams.deviceName = udev_device_get_sysattr_value(dev,"product");
		// }
		// if(udev_device_get_sysattr_value(dev,"manufacturer") != NULL) {
		// 	item->deviceParams.manufacturer = udev_device_get_sysattr_value(dev,"manufacturer");
		// }
		// if(udev_device_get_sysattr_value(dev,"serial") != NULL) {
		// 	item->deviceParams.serialNumber = udev_device_get_sysattr_value(dev, "serial");
		// }
		// item->deviceParams.deviceAddress = strtol(udev_device_get_sysattr_value(dev,"devnum"), NULL, 10);
		// item->deviceParams.locationId = strtol(udev_device_get_sysattr_value(dev,"busnum"), NULL, 10);

		// item->deviceState = DeviceState_Connect;

		// AddItemToList((char *)udev_device_get_devnode(dev), item);

		udev_device_unref(dev);
	}
	/* Free the enumerator object */
	udev_enumerate_unref(enumerate);
}


void Init(v8::Local<v8::Object> exports) {
  v8::Local<v8::Context> context = Nan::GetCurrentContext();
  FUNCTION_EXPORT(context, GetDefaultPrinter, "getDefaultPrinter");
  FUNCTION_EXPORT(context, SendToPrinter, "sendToPrinter");
  FUNCTION_EXPORT(context, InitSettings, "initSettings");
  FUNCTION_EXPORT(context, DeinitSettings, "deinitSettings");
}

NODE_MODULE(betshop_printer, Init)