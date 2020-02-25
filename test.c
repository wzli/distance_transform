#include "distance_transform.h"
#include <math.h>
#include <stdio.h>

#define WIDTH (600)
#define PIXEL(IMG, X_LEN, X, Y) (IMG)[(X) + (X_LEN) * (Y)]

static int image[WIDTH * WIDTH];
static int transformed_image[(WIDTH + 1) * (WIDTH + 1)];

static void save_to_pgm(const char* file_name, const int* image, int x_len, int y_len) {
    FILE* pgm_file = fopen(file_name, "wb");
    fprintf(pgm_file, "P5\n%u %u\n%u\n", x_len, y_len, 255);
    for (int y = 0; y < y_len; ++y) {
        for (int x = 0; x < x_len; ++x) {
            unsigned char pixel = PIXEL(image, x_len, x, y) > 255 ? 255 : PIXEL(image, x_len, x, y);
            fwrite(&pixel, 1, 1, pgm_file);
        }
    }
    fclose(pgm_file);
}

int main() {
    // build test image
    for (int i = 0; i < WIDTH * WIDTH; ++i) {
        image[i] = 0xFFFF;
    }
    for (int i = 0; i < WIDTH / 2; ++i) {
        PIXEL(image, WIDTH, WIDTH / 2, WIDTH / 4 + i) = 0;
        PIXEL(image, WIDTH, WIDTH / 4 + i, WIDTH / 4) = 0;
        PIXEL(image, WIDTH, WIDTH / 4 + i, 3 * WIDTH / 4) = 0;
    }
    save_to_pgm("original.pgm", image, WIDTH, WIDTH);
    printf("saved original.pgm\n");

    // test manhattan distance transform
    manhattan_distance_transform_2d(transformed_image, image, WIDTH, WIDTH);
    save_to_pgm("manhattan_distance_transform.pgm", transformed_image, WIDTH, WIDTH);
    printf("saved manhattan_distance_transform.pgm\n");

    // test distance transform
    square_distance_transform_2d(transformed_image, image, WIDTH, WIDTH);
    for (int i = 0; i < WIDTH * WIDTH; ++i) {
        transformed_image[i] = sqrtf(transformed_image[i]);
    }
    save_to_pgm("distance_transform.pgm", transformed_image, WIDTH, WIDTH);
    printf("saved square_distance_transform.pgm\n");

    return 0;
}
