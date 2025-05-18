#ifndef ENCODE_H
#define ENCODE_H

#include"type.h"
#include<stdio.h>


#define MAX_SECRET_BUF_SIZE 256
#define MAX_IMAGE_BUF_SIZE (MAX_SECRET_BUF_SIZE * 8)
#define MAX_FILE_SUFFIX 4

typedef struct _EncodeInfo
{
    /*source image info*/
    char *src_image_fname;              // Name of source image file 
    FILE *fptr_src_image;               // File ptr to source image
    uint image_capacity;                // How much data can be stored (w*h*3)
    uint bits_per_pixel;                // No. of bit per pixel (24 for bmp - 8 bits for each RGB)
    char image_data[MAX_IMAGE_BUF_SIZE];// Buffer to hold image data for reading or writting  

    /*secret file info*/
    char *secret_fname;                    // Name of secret file to be hiden in the bmp file
    FILE *fptr_secret;                     // File ptr to secret file
    char extn_secret_file[MAX_FILE_SUFFIX];// File ext of the secrte file(.txt,.docx,.c)
    char secret_data[MAX_SECRET_BUF_SIZE]; // Buffer to hold actual secret data
    long size_secret_file;                // Size of secret file

    /*stego Image Info*/
    char *stego_image_fname;            // Name of output image file (having hidden data)
    FILE *fptr_stego_image;              // File ptr to stego image

} EncodeInfo;

/*Prototype*/

/*To check operation type*/
OperationType check_operation_type(char *argv[]);

/*Read and validate encode arguments*/
Status_e read_and_validate_encode_args(char *argv[], EncodeInfo *encInfo);


/*Perform encoding*/
Status_e do_encoding(EncodeInfo *encInfo);


/*Get file pointers for input and output files*/
Status_e open_files(EncodeInfo *encInfo);

/*Check capacity*/
Status_e check_capacity(EncodeInfo *encInfo);

/*Get image size*/
uint get_image_size_for_bmp(FILE *fptr_image);

/*Get file size*/
uint get_file_size(FILE *fptr);

/*Copy bmp heaer*/
Status_e copy_bmp_header(FILE *fptr_src_image, FILE *fptr_dest_image);

/*Store magic string*/
Status_e encode_magic_string(char *magic_string, EncodeInfo*encInfo);

/*Encode secretfile Ext size*/
Status_e encode_secret_file_ext_size(int size, FILE *fptr_src_image, FILE *fptr_stego_image);

/* Encode secret file extenstion */
Status_e encode_secret_file_extn(char *file_extn, EncodeInfo *encInfo);

/*Encode secret_file  size*/
Status_e encode_secre_file_size(int file_size, EncodeInfo *encInfo);

/* Encode secret file data*/
Status_e encode_secret_file_data(EncodeInfo *encInfo);

/*Encode function: real encoding part */
Status_e encode_data_to_image(char *data, int size, FILE *fptr_src_image, FILE *fptr_stego_image, EncodeInfo *encInfo);

/*Encode byte into lsb of image data array*/
Status_e encode_byte_to_lsb(char data, char *image_buffer);

/*encode size to lsb*/
Status_e encode_size_to_lsb(int size, char *image_buffer);

/*copy remaining bytes from src to stego image after encoding*/
Status_e copy_remaining_image_data(FILE *fptr_src, FILE *fptr_dest);


#endif 