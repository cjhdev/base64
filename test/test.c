#include "../base64.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
    const char test[] =
"Redistribution and use in source and binary forms, with or without\n"
"modification, are permitted provided that the following conditions are met:\n"
"\n"
"1. Redistributions of source code must retain the above copyright notice, this\n"
"   list of conditions and the following disclaimer.\n"
"2. Redistributions in binary form must reproduce the above copyright notice,\n"
"   this list of conditions and the following disclaimer in the documentation\n"
"   and/or other materials provided with the distribution.\n"

"THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS \"AS IS\" AND\n"
"ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED\n"
"WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE\n"
"DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR\n"
"ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES\n"
"(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;\n"
"LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND\n"
"ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT\n"
"(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS\n"
"SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.";


    printf("message:\n");
    printf("%s\n\n", test);

    uint8_t *b1 = malloc(b64_encoded_size(strlen(test))+1);
    uint8_t *b2 = malloc(strlen(test)+1);
    
    size_t size = b64_encode(b1, (uint8_t *)test, strlen(test));
    b1[size] = 0;

    printf("encoded base64: \n%s\n\n",  b1);
    
    if(b64_decode(b2, b1, size, &size)){
        printf("decoding error!\n");
        exit(EXIT_SUCCESS);
    }

    b2[size] = 0;
    
    printf("decoded again: \n%s\n\n",  b2);
    
    exit(EXIT_SUCCESS);
}
