#include <stdio.h>
#include <string.h>
#include "encode.h"
#include "decode.h"
#include "main.h"
#include "type.h"

int main(int argc, char *argv[])
{
    if (argc < 5) 
    {
        printf(RED "Insufficient arguments provided. Usage: ./a.out -e image.bmp secret.txt stego.bmp\n" RESET);
        return e_failure;
    }
    //Check operation type
    if(check_operation_type(argv) == e_encode)
    {
        //selected encoded -e
        printf(CYAN "SELECTED ENCODING\n" RESET);

        //declare stucture variable
        EncodeInfo encInfo;

        //read and validation
        if(read_and_validate_encode_args(argv, &encInfo) == e_success)
        {
            printf(CYAN "READ AND VALIDATED ARGUMENTS SUCCESSFULLY\n"RESET);
            printf(MAGENTA "******************** STARTED ENCODING ********************\n");
            //function do_encoding
            if(do_encoding(&encInfo) == e_success)
            {
                printf(CYAN "***<<<<<<COMPLETED ENCODING>>>>>>***\n" RESET);
                return e_success;
            }
        }
        else
        {
            printf(RED "ENCODING FAILED\n" RESET);
            return e_failure;
        }
    }
    if(check_operation_type(argv) == e_decode)
    {
        //selected encoded -e
        printf(CYAN "SELECTED ENCODING\n" RESET);

        //declare stucture variable
        DecodeInfo decInfo;

        //read and validation
        if(read_and_validate_decode_args(argv, &decInfo) == d_success)
        {
            printf(CYAN "READ AND VALIDATED ARGUMENTS SUCCESSFULLY\n"RESET);
            printf(MAGENTA "******************** STARTED DECODING ********************\n");
            //function do_encoding
            if(do_decoding(&decInfo) == d_success)
            {
                printf(CYAN "***<<<<<<COMPLETED DECODING>>>>>>***\n" RESET);
                return d_success;
            }
        }
        
        else
        {
            printf(RED "DECODING FAILED\n" RESET);
            return d_failure;
        }
    }
    else
    {
        printf(RED "Invalid Operation\n Enter ./a.out -e beautiful.bmp secret.txt stego.bmp\n Enter ./a.out -d stego.bmp secret1.txt beautiful.bmp \n" RESET);
        return e_failure;
    }
}
