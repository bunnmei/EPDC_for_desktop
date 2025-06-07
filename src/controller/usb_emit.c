#include "usb_emit.h"
#include "object_common.h"


#define VENDOR_ID 0x0000
#define PRODUCT_ID 0x0001

// static gpointer usb_communication_thread(gpointer data) {
//   PopUp *pop_up = (PopUp *)data;
//   libusb_device **list;
//   libusb_context *ctx = NULL;
//   libusb_device_handle *handle;
//   struct libusb_device_descriptor desc;
//   unsigned char text[512];
//   int r, i;
//   int actual_length;

//   r = libusb_init(NULL);
//   if (r < 0) {
//     fprintf(stderr, "Error initializing libusb: %s\n", libusb_error_name(r));
//     return false;
//   }

//   int cnt = libusb_get_device_list(NULL, &list);
//   printf("%d個のデバイスが見つかりました。\n", cnt);

//   libusb_device *target_device = NULL;
//   for (i = 0; i < cnt; i++)
//   {
//     libusb_device *device = list[i];
//     libusb_get_device_descriptor(device, &desc);
//     printf("vid %d\n", desc.idVendor);
//     if(desc.idVendor == 0) {
//       target_device = list[i];
//     }
//   }

//   if(target_device != NULL) {
//     printf("target deviceが見つかったよ\n");
//     libusb_get_device_descriptor(target_device, &desc);
//     r = libusb_open(target_device, &handle);
//     printf("open status %d\n", r);
//   } else {
//     printf("デバイスがみつかりません。\n");
//     libusb_close(handle);
//     libusb_free_device_list(list, 1);
//     libusb_exit(ctx);
//     return 0;
//   }

//   struct libusb_config_descriptor *config;
//   r = libusb_get_active_config_descriptor(target_device, &config);
  
//   const struct libusb_interface *interface = NULL;
//   const struct libusb_interface_descriptor *altsetting = NULL;
//   int ep_bulk_in = -1;
//   int ep_bulk_out = -1;

//   for (int i = 0; i < config->bNumInterfaces; i++) {
//       interface = &config->interface[i];
//       for (int j = 0; j < interface->num_altsetting; j++) {
//           altsetting = &interface->altsetting[j];
          
//             for (int k = 0; k < altsetting->bNumEndpoints; k++) {
//                 const struct libusb_endpoint_descriptor *ep = &altsetting->endpoint[k];
//                 // 転送タイプが BULK かチェック
//                 if ((ep->bmAttributes & LIBUSB_TRANSFER_TYPE_MASK) == LIBUSB_TRANSFER_TYPE_BULK) {
//                     if ((ep->bEndpointAddress & LIBUSB_ENDPOINT_DIR_MASK) == LIBUSB_ENDPOINT_IN) {
//                         ep_bulk_in = ep->bEndpointAddress;
//                     } else {
//                         ep_bulk_out = ep->bEndpointAddress;
//                     }
//                 }
//             }
//             goto found_bulk_ep;
//       }
//   }

//   // return 0;
//   found_bulk_ep:
//     if (ep_bulk_out >= 0) {
//       printf("Bulk OUT endpoint: 0x%02x\n", ep_bulk_out);
//       int toggle = 1;
//       unsigned char off_data[] = "off";
//       unsigned char on_data[] = "on";
//       while(1)
//       {
//         g_mutex_lock(&pop_up->thread_mutex);
//         if(!pop_up->keep_running){
//           g_mutex_unlock(&pop_up->thread_mutex);
//           break; 
//         }
//         g_mutex_unlock(&pop_up->thread_mutex);
//         if(toggle) {
//           r = libusb_bulk_transfer(handle, ep_bulk_out, on_data, strlen((char*)on_data), &actual_length, 1000);
//           if (r < 0) {
//             fprintf(stderr, "Error sending 'on': %s\n", libusb_error_name(r));
//           } else {
//             toggle = 0;
//             printf("Sent %d bytes: '%s'\n", actual_length, on_data);
//           }
//         } else {
//           r = libusb_bulk_transfer(handle, ep_bulk_out, off_data, strlen((char*)off_data), &actual_length, 1000);
//           if (r < 0) {
//             fprintf(stderr, "Error sending 'on': %s\n", libusb_error_name(r));
//           } else {
//             toggle = 1;
//             printf("Sent %d bytes: '%s'\n", actual_length, off_data);
//           }
//         }
//         usleep(1000 * 1000);
//       }
//     }
//     else
//     printf("Bulk OUT endpoint not found.\n");
    
//     printf("検索完了\n");
//     libusb_free_config_descriptor(config);
//     libusb_close(handle);
//     libusb_free_device_list(list, 1);
//     libusb_exit(ctx);
// }


static gpointer usb_emit_thread(gpointer data) {
  PopUp *pop_up = (PopUp *)data;
  libusb_device **list;
  libusb_context *ctx = NULL;
  libusb_device_handle *handle;
  struct libusb_device_descriptor desc;
  unsigned char text[512];
  int r, i;
  int actual_length;

  r = libusb_init(NULL);
  if (r < 0) {
    fprintf(stderr, "Error initializing libusb: %s\n", libusb_error_name(r));
    return false;
  }

  int cnt = libusb_get_device_list(NULL, &list);
  printf("%d個のデバイスが見つかりました。\n", cnt);

  libusb_device *target_device = NULL;
  for (i = 0; i < cnt; i++)
  {
    libusb_device *device = list[i];
    libusb_get_device_descriptor(device, &desc);
    printf("vid %d\n", desc.idVendor);
    if(desc.idVendor == 0) {
      target_device = list[i];
    }
  }

  if(target_device != NULL) {
    printf("target deviceが見つかったよ\n");
    libusb_get_device_descriptor(target_device, &desc);
    r = libusb_open(target_device, &handle);
    printf("open status %d\n", r);
  } else {
    printf("デバイスがみつかりません。\n");
    libusb_close(handle);
    libusb_free_device_list(list, 1);
    libusb_exit(ctx);
    return 0;
  }

  struct libusb_config_descriptor *config;
  r = libusb_get_active_config_descriptor(target_device, &config);
  
  const struct libusb_interface *interface = NULL;
  const struct libusb_interface_descriptor *altsetting = NULL;
  int ep_bulk_in = -1;
  int ep_bulk_out = -1;

  for (int i = 0; i < config->bNumInterfaces; i++) {
      interface = &config->interface[i];
      for (int j = 0; j < interface->num_altsetting; j++) {
          altsetting = &interface->altsetting[j];
          
            for (int k = 0; k < altsetting->bNumEndpoints; k++) {
                const struct libusb_endpoint_descriptor *ep = &altsetting->endpoint[k];
                // 転送タイプが BULK かチェック
                if ((ep->bmAttributes & LIBUSB_TRANSFER_TYPE_MASK) == LIBUSB_TRANSFER_TYPE_BULK) {
                    if ((ep->bEndpointAddress & LIBUSB_ENDPOINT_DIR_MASK) == LIBUSB_ENDPOINT_IN) {
                        ep_bulk_in = ep->bEndpointAddress;
                    } else {
                        ep_bulk_out = ep->bEndpointAddress;
                    }
                }
            }
            goto found_bulk_ep;
      }
  }

  // return 0;
  found_bulk_ep:
    if (ep_bulk_out >= 0) {
      printf("Bulk OUT endpoint: 0x%02x\n", ep_bulk_out);
      int toggle = 1;
      unsigned int offset = 0;
      while(offset < sizeof(gImage1_BW)){
        int bytes_to_send = 64;
        if (offset + 64 > sizeof(gImage1_BW))
        {
          bytes_to_send = sizeof(gImage1_BW) - offset;
        }
        r = libusb_bulk_transfer(
          handle,
          ep_bulk_out,
          (unsigned char *)&gImage1_BW[offset],
          bytes_to_send,
          &actual_length,
          1000);

        if (r < 0) {
          fprintf(stderr, "Error sending: %s\n", libusb_error_name(r));
        } else {
          printf("Sent %d bytes (total: %d/%zu)\n", actual_length, offset + actual_length, sizeof(gImage1_BW));
          offset += actual_length;
        }
      }
      
      printf("Bulk OUT End.\n");
      libusb_free_config_descriptor(config);
      libusb_close(handle);
      libusb_free_device_list(list, 1);
      libusb_exit(ctx);
    }
}
bool usb_emit(GPtrArray *array, PopUp *pop_up){
  printf("usb_emit\n");
  pop_up->usb_thread = g_thread_new("usb_thread", usb_emit_thread, pop_up);
  return true;
}
// if(pop_up->keep_running) {
//   printf("usb_stop\n");
//   g_mutex_lock(&pop_up->thread_mutex);
//   g_mutex_unlock(&pop_up->thread_mutex);
//     // スレッドの終了を待つ (オプションだが推奨)
//   pop_up->keep_running = false;
//   g_thread_join(pop_up->usb_thread);
//   pop_up->usb_thread = NULL;
//   g_mutex_clear(&pop_up->thread_mutex);
// }
// else
// {
//   printf("usb_start\n");
//   g_mutex_init(&pop_up->thread_mutex);
//   pop_up->keep_running = true;
//   pop_up->usb_thread = g_thread_new("usb_thread", usb_emit_thread, pop_up);
// }