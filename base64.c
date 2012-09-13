/*
 
Copyright (c) 2012, Cameron Harper
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met: 

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer. 
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution. 

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/
#include <stddef.h>
#include <stdint.h>

#define VERSION "0.01"

#define PADCHAR '='
#define CHAR62  '+'
#define CHAR63  '/'

static uint8_t encode_char(uint8_t in)
{
    in &= 0x3f;

    if(in <= 25)
        return ('A' + in);
    else if(in <= 51)
        return ('a' + in - 26);
    else if(in <= 61)
        return ('0' + in - 52);
    else
        return (in==62)?CHAR62:CHAR63;        
}

static int decode_char(uint8_t in)
{   
    if((in >= 'A') && (in <= 'Z'))
        return (in - 'A');    
    else if((in >= 'a') && (in <= 'z'))
        return (in - 'a' + 26);
    else if((in >= '0') && (in <= '9'))
        return (in - '0' + 52);
    else{
        switch(in){
        case CHAR62:
            return 62;
        case CHAR63:
            return 63;
        case PADCHAR:
            return 64;
        default:
            return 255;
        }
    }        
}

size_t b64_encode(uint8_t *out, uint8_t *in, size_t len)
{
    uint8_t c, acc = 0;
    size_t i, ret = 0;

    for(i=0; i < len; i++){

        c = in[i];

        switch(i%3){
        case 0:
            out[ret++] = encode_char(c >> 2);
            acc = (c << 4);
            break;
        case 1:
            out[ret++] = encode_char(acc | (c >> 4));
            acc = (c << 2);
            break;            
        case 2:
            out[ret++] = encode_char(acc | (c >> 6));
            out[ret++] = encode_char(c);
        }        
    }

    if(len % 3){
        out[ret++] = encode_char(acc);
        out[ret++] = PADCHAR;

        if((len % 3) == 2)
            out[ret++] = PADCHAR;
    }
        
    return ret;
}

int b64_decode(uint8_t *out, uint8_t *in, size_t inlen, size_t *outlen)
{
    uint8_t c, acc = 0;
    size_t i;

    *outlen = 0;

    for(i=0; i < inlen; i++){

        switch((c = decode_char(in[i]))){
        case 255:
            return -1;
        case 64:
            continue;
        }
        
        switch(i%4){
        case 0:
            acc = (c << 2);
            break;
        case 1:
            out[(*outlen)++] = acc | (c >> 4);
            acc = (c << 4);
            break;
        case 2:
            out[(*outlen)++] = acc | (c >> 2);
            acc = (c << 6);
            break;
        case 3:
            out[(*outlen)++] = acc | c;
        }
    }
        
    return 0;
}

/* return output encoded size (exact including padding) */
size_t b64_encoded_size(size_t size)
{    
    return (((size%3)?size+3-(size%3):size) / 3) * 4;
}
