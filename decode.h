#ifndef DECODE_H
#define DECODE_H

#include "type.h"
#include <stdio.h>

#define MAX_SECRET_BUF_SIZE 256
#define MAX_IMAGE_BUF_SIZE (MAX_SECRET_BUF_SIZE * 8)

typedef struct _DecodeInfo
{
    char *src_image_fname_d;
    FILE *fptr_src_image_d;

    char image_data_d[MAX_IMAGE_BUF_SIZE];
    char *magic_data;
    char *extn_secret_file_d;

    int size_secret_file;
    FILE *fptr_dest_image_d;

    char *secret_fname_d;
    FILE *fptr_secret_d;
} DecodeInfo;

/* DECODING FUNCTION PROTOTYPE*/

/*Read and validate*/
Status_d read_and_validate_decode_args(char *argv[], DecodeInfo *decInfo);

/* Perform do_decoding*/
Status_d do_decoding(DecodeInfo *decInfo);

/* Get File pointer for i/p and o/p files*/
Status_d open_files_dec(DecodeInfo *decInfo);

/* Decode Magic String*/
Status_d decode_magic_string(DecodeInfo *decInfo);

/* Decode data from image*/
Status_d decode_data_from_image(int size, FILE *fptr_src_image_d, DecodeInfo *decInfo);

/* Decode byte from lsb*/
Status_d decode_byte_from_lsb(char *data, char *image_buffer);

/* Decode file extension size*/
Status_d decode_file_extn_size(int size, FILE *fptr_src_image_d);

/* Decode size from lsb*/
Status_d decode_size_from_lsb(char *buffer, int *size);

/* Decode secret file extention*/
Status_d decode_secret_file_extn(char *file_extn, DecodeInfo *decInfo);

/* Decode extention data from image*/
Status_d decode_extn_data_from_image(int size, FILE *fptr_src_image_d, DecodeInfo *decInfo);

/* Decode secret file size*/
Status_d decode_secret_file_size(int file_size, DecodeInfo *decInfo);

/* Decode secret file data*/
Status_d decode_secret_file_data(DecodeInfo *decInfo);

#endif