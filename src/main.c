/*
 * main.c
 * Creates a Window, Layer and assigns an `update_proc` to draw 
 * the 'P' in the Pebble logo.
 */


#include <main.h>
#include <twd_detail.h>
static Window *s_main_window;
char * imageData;

//static int imageDataLength;
Tuple *dataReceived;

static void main_window_load(Window *window) {
 // Layer *window_layer = window_get_root_layer(window);
		printf("main.c window_load heap_bytes_free: %d   ",heap_bytes_free() );
}

static void main_window_unload(Window *window) {
  // Destroy Layer  
}
static void in_received_handler(DictionaryIterator *iter, void *context) {
	 dataReceived =dict_read_first(iter);
	 while (dataReceived != NULL){	
		 switch( dataReceived->key ) {
			 /*  windDirImageRecent ------- */
			 case 201: // windDirImageRecent
			 	imageDataSize = dataReceived->length;
			 	printf("in_received_handler. length %d",(int) dataReceived->length);
			    *histDataSize = (int) dataReceived->length;
				twdWindDirImageRecentBitArray = malloc(imageDataSize);
				memcpy(twdWindDirImageRecentBitArray, dataReceived->value->data, dataReceived->length) ;		
				printf("twdWindDirImageRecentBitArray[26] %d ",twdWindDirImageRecentBitArray[26]);

			 	break;
				
			
			 case 0: // getting wind detail background image
			 	imageDataSize = dataReceived->length;
			 	//printf("data %s",dataReceived->value->data);
				twdBackgroundImageBitArray = malloc(imageDataSize);
			 	memcpy(twdBackgroundImageBitArray, dataReceived->value->data, dataReceived->length) ;	
			 	*start = 0;
			 	//twd_detail();
			 	break;
			 case 1: // new start point for display background
			 	//printf("start received %d",(int) dataReceived->value->int32);
			 	*start = (int) dataReceived->value->int32;
			 	twd_detail();
				//layer_mark_dirty(s_canvas_layer);
				break;
				
			default:
			 	printf("in_received_handler Key %d", (int) dataReceived->key);
				break;
		 }
		 dataReceived = dict_read_next(iter);
	 }
}
static void init(void) {
	start = malloc(sizeof(int));
	histDataSize = malloc(sizeof(int));

	app_message_register_inbox_received(in_received_handler);
	//app_message_register_inbox_dropped(in_dropped_handler);
	const uint32_t inbound_size = app_message_inbox_size_maximum();
	APP_LOG(APP_LOG_LEVEL_INFO, "inbound_size %d: ",(int) inbound_size);
	const uint32_t outbound_size =30;
   	app_message_open(inbound_size, outbound_size);
	  // Create main Window
	 s_main_window = window_create();
	 window_set_window_handlers(s_main_window, (WindowHandlers) {
		.load = main_window_load,
		.unload = main_window_unload,
	  });
	  window_stack_push(s_main_window, true);
	}

static void deinit(void) {
  // Destroy main Window
  window_destroy(s_main_window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}