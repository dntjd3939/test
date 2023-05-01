#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <time.h>

int main() {
    FILE* inFile = fopen("/Users/jeon-woosung/Downloads/image.ppm", "rb");

    if(!inFile) {
        fprintf(stderr, "Cannot open file!\n");
        return 1;
    }

    char magicNumber[3];
    int width, height, maxVal;
    fscanf(inFile, "%2s %d %d %d", magicNumber, &width, &height, &maxVal);

    FILE* outFile = fopen("/Users/jeon-woosung/Downloads/newimage.bin", "wb");

        if(!outFile) {
        fprintf(stderr, "Cannot open file!\n");
        fclose(inFile);
        return 1;
    }


    fprintf(outFile, "%2s\n", magicNumber);
    fprintf(outFile, "%d %d\n", width, height);
    fprintf(outFile, "%d\n", maxVal);

    unsigned char* data = (unsigned char*)malloc(width * height * 3);
    fread(data, sizeof(unsigned char), width * height * 3, inFile);


    clock_t start, end;
    double result;

    start = clock();

    int x1 = 100, y1 = 200;
    int x2 = 1000, y2 = 300;
    int x3 = 800, y3 = 900;
    int x4 = 50, y4 = 700;
    int r = 0, g = 0, b = 0;


  
// 좌표를 순서대로 연결하는 라인을 그립니다.

for (int x = x1; x <= x2; ++x) { // x1 -> x2
    int y = y1 + (y2 - y1) * (x - x1) / (x2 - x1);
    int index = ((height - y - 1) * width + x) * 3;
    data[index] = r;
    data[index + 1] = g;
    data[index + 2] = b;
}

for (int y = y2; y <= y3; ++y) { // y2 -> y3
    int x = x2 + (x3 - x2) * (y - y2) / (y3 - y2);
    int index = ((height - y - 1) * width + x) * 3;
    data[index] = r;
    data[index + 1] = g;
    data[index + 2] = b;
}

for (int x = x3; x >= x4; --x) { // x3 -> x4
    int y = y3 + (y4 - y3) * (x - x3) / (x4 -x3);
    int index = ((height - y - 1) * width + x) * 3;
    data[index] = r;
    data[index + 1] = g;
    data[index + 2] = b;
}

for (int y = y1; y <= y4; ++y) { // y4 -> y1
    int x = x1 + (x4 - x1) * (y - y1) / (y4 - y1);
    int index = ((height - y - 1) * width + x) * 3;
    data[index] = r;
    data[index + 1] = g;
    data[index + 2] = b;
}

    end = clock();
    result = (double)(end - start);

    printf("계산 시간 = %f", result);

    fwrite(data, sizeof(unsigned char), width * height * 3, outFile);
    fclose(inFile);
    fclose(outFile);
    free(data);

    return 0;

}


