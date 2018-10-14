#ifndef _CATCH_
#define _CATCH_
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <jpeglib.h>
void quit(const char * msg);

int xioctl(int fd, int request, void* arg);
typedef struct {
  uint8_t* start;
  size_t length;
} buffer_t;

typedef struct {
  int fd;
  uint32_t width;
  uint32_t height;
  size_t buffer_count;
  buffer_t* buffers;
  buffer_t head;
} camera_t;

typedef struct timeval timeval;

camera_t* camera_open(const char * device, uint32_t width, uint32_t height);
//typedef struct timeval timeval;
void camera_init(camera_t* camera);
void camera_start(camera_t* camera);
void camera_stop(camera_t* camera);
void camera_finish(camera_t* camera);
void camera_close(camera_t* camera);
int camera_capture(camera_t* camera);
int camera_frame(camera_t* camera, timeval timeout);
void
jpeg(FILE* dest, uint8_t* rgb, uint32_t width, uint32_t height, int quality);
int minmax(int min, int v, int max);
uint8_t* yuyv2rgb(uint8_t* yuyv, uint32_t width, uint32_t height);

int catchimage(int i);








#endif

