#include "usb_emit.h"
#include "object_common.h"
#include "canvas.h"
#include <unistd.h> 

#define VENDOR_ID 0xcafe
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

static unsigned int emit_array_cretate(GPtrArray *pixels, unsigned char *emit_arr, ColorMode mode) {
  int size_w = CANVAS_WIDTH / 3;
  int size_h = CANVAS_HEIGHT / 3;
  int count = 0;
  int index = 0;
  unsigned char byte = 0;
  printf("max len %d\n", pixels->len);
  if (mode == BLACK) {
    for (int w = 0; w < size_w; w++)
    {
      for (int h = 0; h < size_h; h++){
        int i = h * size_w + w;
        int *pixel = (int *)g_ptr_array_index(pixels, i);
        byte |= (*pixel << (7 - count));
        count++;
        if(count >= 8) {
          printf("byte %d\n", byte);
          emit_arr[index] = byte;
          index++;
          byte = 0;
          count = 0;
        }
      }
    }
  } else if (mode == RED)
  {
    for (int w = 0; w < size_w; w++)
    {
      for (int h = 0; h < size_h; h++){
        int i = h * size_w + w;
        int *pixel = (int *)g_ptr_array_index(pixels, i);
        byte |= (*pixel << (7 - count));
        count++;
        if(count >= 8) {
          printf("byte %d\n", byte);
          emit_arr[index] = ~byte;
          index++;
          byte = 0;
          count = 0;
        }
      }
    }
  }

  // g_print("index %d\n", emit_arr[index-1]);
  // g_print("index %d\n", index);
  // for (int i = 0; i < pixels->len; i++) {
  //   unsigned char byte = 0;
  //   int *pixel = (int *)g_ptr_array_index(pixels, i);
  //   byte |= (*pixel << i);
  //   int p = size
  // }
  // for (int w = 0; w < size_w; w++){
  //   unsigned char byte = 0;
  //   for (int h = 0; h < size_h; h++){

  //       for (int i = 0; i < 8; i++) {

  //         int *pixel = (int *)g_ptr_array_index(pixels, count);
  //         byte |= (*pixel << i);
  //         count++;
  //       }
  //       // emit_arr[h*size_w + w] = ~byte;
  //       g_print("index %d\n",(w*size_h));
  //   }
  // }

  return count;
  // for (unsigned int i = 0; i < pixels->len; i += 8)
  // {
  //   unsigned char byte = 0;
  //   for (int j = 0; j < 8; ++j)
  //   {
  //     int *pixel = (int *)g_ptr_array_index(pixels, i + j);
  //     byte |= (*pixel << j); // 下位から上位へ
  //   }
  //   emit_arr[emit_arr_idx++] = byte;
  // }
}

static gpointer usb_emit_thread(gpointer data) {
  PopUp *pop_up = (PopUp *)data;
  libusb_device **list;
  libusb_context *ctx = NULL;
  libusb_device_handle *handle;
  struct libusb_device_descriptor desc;
  unsigned char emit_arr[4736] = {0};
  unsigned char emit_arr_red[4736] = {0xff};
  unsigned int emit_len = emit_array_cretate(pop_up->pixels, emit_arr, BLACK);
  unsigned int emit_len_red = emit_array_cretate(pop_up->pixels_red, emit_arr_red, RED);
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
    if(desc.idVendor == VENDOR_ID) {
      target_device = list[i];
    }
  }

  if(target_device != NULL) {
    printf("target deviceが見つかったよ\n");
    libusb_get_device_descriptor(target_device, &desc);
    // r = libusb_open_device_with_vid_pid(ctx, VENDOR_ID, PRODUCT_ID);
    r = libusb_open(target_device, &handle);
    printf("open status %d\n", r);
  } else {
    printf("デバイスがみつかりません。\n");
    libusb_close(handle);
    libusb_free_device_list(list, 1);
    libusb_exit(ctx);
    goto end;
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

      while(offset < sizeof(emit_arr)){
        int bytes_to_send = 64;
        if (offset + 64 > sizeof(emit_arr))
        {
          bytes_to_send = sizeof(emit_arr) - offset;
        }
        r = libusb_bulk_transfer(
          handle,
          ep_bulk_out,
          (unsigned char *)&emit_arr[offset],
          bytes_to_send,
          &actual_length,
          1000);

        if (r < 0) {
          fprintf(stderr, "Error sending: %s\n", libusb_error_name(r));
        } else {
          printf("Sent %d bytes (total: %d/%zu)\n", actual_length, offset + actual_length, sizeof(emit_arr));
          offset += actual_length;
        }
      }

      offset = 0;
      actual_length = 0;
      usleep(100 * 1000);

      while (offset < sizeof(emit_arr_red))
      {
        int bytes_to_send = 64;
        if (offset + 64 > sizeof(emit_arr_red))
        {
          bytes_to_send = sizeof(emit_arr_red) - offset;
        }
        r = libusb_bulk_transfer(
          handle,
          ep_bulk_out,
          (unsigned char *)&emit_arr_red[offset],
          bytes_to_send,
          &actual_length,
          1000);

        if (r < 0) {
          fprintf(stderr, "Error sending: %s\n", libusb_error_name(r));
        } else {
          printf("Sent %d bytes (total: %d/%zu)\n", actual_length, offset + actual_length, sizeof(emit_arr));
          offset += actual_length;
        }
      }

      printf("Bulk OUT End.\n");
      libusb_free_config_descriptor(config);
      libusb_close(handle);
      libusb_free_device_list(list, 1);
      libusb_exit(ctx);
      goto end;
    }

  end:
}
bool usb_emit(GPtrArray *array, PopUp *pop_up){
  printf("usb_emit\n");
  usb_emit_thread(pop_up);
  return true;
}
// pop_up->usb_thread = g_thread_new("usb_thread", usb_emit_thread, pop_up);
