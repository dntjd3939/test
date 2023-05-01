#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <time.h>

int main() {

    // 이미지 파일을 읽어올 포인터 선언
    FILE* inFile = fopen("/Users/jeon-woosung/Downloads/image.ppm", "rb");

    // 파일 열기 실패 시 오류 출력
    if(!inFile) {
        fprintf(stderr, "Cannot open file!\n");
        return 1;
    }

    //ppm 파일 헤더 정보 읽어오기
    char magicNumber[3];
    int width, height, maxVal;
    fscanf(inFile, "%2s %d %d %d", magicNumber, &width, &height, &maxVal);

    // 새로운 파일에 쓸 포인터 선언
    FILE* outFile = fopen("/Users/jeon-woosung/Downloads/newimage.bin", "wb");

        if(!outFile) {
        fprintf(stderr, "Cannot open file!\n");
        fclose(inFile);
        return 1;
    }

    // 새로운 파일에 읽어온 헤더 정보 쓰기
    fprintf(outFile, "%2s\n", magicNumber);
    fprintf(outFile, "%d %d\n", width, height);
    fprintf(outFile, "%d\n", maxVal);

    // 이미지 파일에서 데이터 읽어와 메모리에 저장할 버퍼 할당
    unsigned char* data = (unsigned char*)malloc(width * height * 3);
    fread(data, sizeof(unsigned char), width * height * 3, inFile);

    // 선그리기 함수 시간 측정 시작
    clock_t start, end;
    double result;

    start = clock();

    // 선의 좌표와 색상값 정의
    int x1 = 100, y1 = 200;
    int x2 = 1000, y2 = 300;
    int x3 = 800, y3 = 900;
    int x4 = 50, y4 = 700;
    int r = 0, g = 0, b = 0;


  
// 좌표를 순서대로 연결하는 함수
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

    // 선그리기 함수 시간 측정 종료
    end = clock();
    result = (double)(end - start);

    printf("running time = %f", result);

    // 메모리에 저장된 이미지 데이터 새로운 파일에 쓰기
    fwrite(data, sizeof(unsigned char), width * height * 3, outFile);
    // 파일 닫기
    fclose(inFile);
    fclose(outFile);
    // 동적으로 할당된 메모리 해제
    free(data);

    return 0;

}


