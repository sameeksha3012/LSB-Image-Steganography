#include <stdio.h>
#include "decode.h"
#include "type.h"
#include <string.h>
#include "main.h"
#include <stdlib.h>


//read and validate decode args
Status_d read_and_validate_decode_args(char *argv[], DecodeInfo *decInfo)
{
    if (strcmp(strstr(argv[2], "."), ".bmp") == 0)
        decInfo->src_image_fname_d  = argv[2];
    else
        return d_failure;

    if (argv[3] != NULL)
        decInfo->secret_fname_d = argv[3];
    else
        decInfo->secret_fname_d = "decode.txt";

    return d_success;
}


//open files for decoding
Status_d open_files_dec(DecodeInfo *decInfo)
{
    // Stego Image file
    decInfo->fptr_src_image_d  = fopen(decInfo->src_image_fname_d, "r");
    // Do Error handling
    if (decInfo->fptr_src_image_d == NULL)
    {
        perror("fopen");
        fprintf(stderr, "ERROR: Unable to open file %s\n", decInfo->src_image_fname_d);
        return d_failure;
    }
    // Dest file
    decInfo->fptr_secret_d = fopen(decInfo->secret_fname_d, "w");
    // Do Error handling
    if (decInfo->fptr_secret_d == NULL)
    {
        perror("fopen");
        fprintf(stderr, "ERROR: Unable to open file %s\n", decInfo->secret_fname_d);
        return d_failure;
    }
    // If no failure then return d_success
    return d_success;
}

//decode magic string
Status_d decode_magic_string(DecodeInfo *decInfo)
{
    fseek(decInfo->fptr_src_image_d, 54, SEEK_SET);
    int i = strlen(MAGIC_STRING);
    decInfo->magic_data = malloc(strlen(MAGIC_STRING) + 1);
    decode_data_from_image(strlen(MAGIC_STRING), decInfo->fptr_src_image_d, decInfo);
    decInfo->magic_data[i] = '\0';
    if (strcmp(decInfo->magic_data, MAGIC_STRING) == 0)
        return d_success;
    else
        return d_failure;
}

//decoding data fom image
Status_d decode_data_from_image(int size, FILE *fptr_src_image_d, DecodeInfo *decInfo)
{
    int i;
    char str[8];
    for (i = 0; i < size; i++)
    {
        fread(str, 8, sizeof(char), fptr_src_image_d);
        decode_byte_from_lsb(&decInfo->magic_data[i], str);
    }
    return d_success;
}

//decode byte from lsb
Status_d decode_byte_from_lsb(char *data, char *image_buffer)
{
    int bit = 7;
    unsigned char ch = 0x00;
    for (int i = 0; i < 8; i++)
    {
        ch = ((image_buffer[i] & 0x01) << bit--) | ch;
    }
    *data = ch;
    return d_success;
}

//decode file extn size
Status_d decode_file_extn_size(int size, FILE *fptr_src_image_d)
{
    char str[32];
    int length;
    fread(str, 32, sizeof(char), fptr_src_image_d);
    decode_size_from_lsb(str, &length);
    if (length == size)
        return d_success;
    else
        return d_failure;
}

//decode size from lsb
Status_d decode_size_from_lsb(char *buffer, int *size)
{
    int j = 31;
    int num = 0x00;
    for (int i = 0; i < 32; i++)
    {
        num = ((buffer[i] & 0x01) << j--) | num;
    }
    *size = num;
}

//decode secret file extn
Status_d decode_secret_file_extn(char *file_ext, DecodeInfo *decInfo)
{
    file_ext = ".txt";
    int i = strlen(file_ext);
    decInfo->extn_secret_file_d = malloc(i + 1);
    decode_extn_data_from_image(strlen(file_ext), decInfo->fptr_src_image_d, decInfo);
    decInfo->extn_secret_file_d[i] = '\0';
    if (strcmp(decInfo->extn_secret_file_d, file_ext) == 0)
        return d_success;
    else
        return d_failure;
}

//decode extension data from image
Status_d decode_extn_data_from_image(int size, FILE *fptr_src_image_d, DecodeInfo *decInfo)
{
    for (int i = 0; i < size; i++)
    {
        fread(decInfo->src_image_fname_d, 8, 1, fptr_src_image_d);
        decode_byte_from_lsb(&decInfo->extn_secret_file_d[i], decInfo->src_image_fname_d);
    }
    return d_success;
}

//decode secret file size
Status_d decode_secret_file_size(int file_size, DecodeInfo *decInfo)
{
    char str[32];
    fread(str, 32, sizeof(char), decInfo->fptr_src_image_d);
    decode_size_from_lsb(str, &file_size);
    decInfo->size_secret_file = file_size;
    return d_success;
}

//decode secret file data
Status_d decode_secret_file_data(DecodeInfo *decInfo)
{
    char ch;
    for (int i = 0; i < decInfo->size_secret_file; i++)
    {
        fread(decInfo->src_image_fname_d, 8, sizeof(char), decInfo->fptr_src_image_d);
        decode_byte_from_lsb(&ch, decInfo->src_image_fname_d);
        fputc(ch, decInfo->fptr_secret_d);
    }
    return d_success;
}

//do decoding
Status_d do_decoding(DecodeInfo *decInfo)
{
    if (open_files_dec(decInfo) == d_success)
    {
        printf("Open files is a successfully\n");
        if (decode_magic_string(decInfo) == d_success)
        {
            printf("Decoded magic string Successfully\n");
            if (decode_file_extn_size(strlen(".txt"), decInfo->fptr_src_image_d) == d_success)
            {
                printf("Decoded file extension size Succesfully\n");
                if (decode_secret_file_extn(decInfo->extn_secret_file_d, decInfo) == d_success)
                {
                    printf("Decoded Secret File Extension Succesfully\n");
                    if (decode_secret_file_size(decInfo->size_secret_file, decInfo) == d_success)
                    {
                        printf("Decoded secret file size Successfully\n");
                        if (decode_secret_file_data(decInfo) == d_success)
                        {
                            printf("Decoded secret file data Succuessfully\n");
                        }
                        else
                        {
                            printf("Decoding of secret file data is a failure\n");
                        }
                    }
                    else
                    {
                        printf("Decode of secret file size is a failure\n");
                        return d_failure;
                    }
                }
                else
                {
                    printf("Decode of Secret file extension is a failure\n");
                    return d_failure;
                }
            }
            else
            {
                printf("Decoded of file extension size is a failure\n");
                return d_failure;
            }
        }
        else
        {
            printf("Decoding of magic string is a failure\n");
            return d_failure;
        }
    }
    else
    {
        printf("Open files is a failure\n");
        return d_failure;
    }
    return d_success;
}
