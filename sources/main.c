#include "../headers/ShannonFanoFunctions.h"
#include "../headers/LZSFunctions.h"


int main(int argc, char *argv[]) {
    if (strcmp(argv[1], "-c") == 0) {
        unsigned int elementsReaded;
        unsigned char *inputBuffer = (unsigned char *)malloc((4096)*sizeof(unsigned char));
        FILE *fileptr = fopen(argv[2],"rb");
        FILE *compressed = fopen(argv[3], "wb");
        printf("inizio compressione \n\n");
        clock_t inizio = clock();
        setCodedBufferCounter();

        do {
            elementsReaded = fread(inputBuffer, sizeof(unsigned char), 4096, fileptr);
            inputBuffer = realloc(inputBuffer,sizeof(unsigned char)*elementsReaded);
            LZSCompression(inputBuffer,elementsReaded);
        } while (elementsReaded == 4096);
        writeEndMarker();

        int bufferSize = getCodedBufferSize();
        unsigned char *buffer = getCodedBuffer();
        compress(argv[3],buffer,bufferSize,compressed);
        clock_t fine = clock();
        double tempo = (double)(fine - inizio) / CLOCKS_PER_SEC;
        printf("Il tempo di compressione e' pari a: %lf secondi",tempo);

    } else if (strcmp(argv[1], "-d") == 0) {
        clock_t inizio =clock();
        printf("inizio decompressione shannonFano...\n\n");
        unsigned char *buffer = decompress(argv[2]);
        printf("fine decompressione shannon\n\n");

        printf("inizio decompressione LZS...\n\n");
        LZSDecompression(argc,buffer, argv[3]);
        printf("fine decompressione LZS\n\n");

        clock_t fine = clock();
        double tempo = (double)(fine - inizio) / CLOCKS_PER_SEC;
        printf("Il tempo di decompressione e' pari a: %lf secondi",tempo);

    } else {
        printf("errore negli argomenti passati \n");
        return 1;
    }
    return 0;
}
