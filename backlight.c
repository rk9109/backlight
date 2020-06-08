#include <fcntl.h>
#include <getopt.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define LEN 10

const char* brightness_path     = "/sys/class/backlight/intel_backlight/brightness";
const char* brightness_max_path = "/sys/class/backlight/intel_backlight/max_brightness";

int brightness;
int brightness_max;

static void
error_exit(const char* format, ...)
{
    va_list arglist;

    va_start(arglist, format);
    vfprintf(stderr, format, arglist);
    va_end(arglist);

    exit(EXIT_FAILURE);
}

static void
set_prop_int(const char* path, const int prop_value)
{
    int fd;
    int numwrite;
    char prop[LEN];

    fd = open(path, O_WRONLY | O_TRUNC);
    if (fd == -1) {
        error_exit("Unable to open %s\n", path);
    }

    numwrite = snprintf(prop, LEN, "%d", prop_value);

    if (write(fd, prop, numwrite) == -1) {
        error_exit("Unable to write %s\n", path);
    }
}

static int
get_prop_int(const char* path)
{
    int fd;
    ssize_t numread;
    char prop[LEN];

    fd = open(path, O_RDONLY);
    if (fd == -1) {
        error_exit("Unable to open %s\n", path);
    }

    if ((numread = read(fd, prop, LEN)) == -1) {
        error_exit("Unable to read %s\n", path);
    }
    prop[numread] = '\0';

    return atoi(prop);
}

static int
get_brightness(void)
{
    brightness     = get_prop_int(brightness_path);
    brightness_max = get_prop_int(brightness_max_path);

    return ((float)brightness / brightness_max) * 100;
}

static void
set_brightness(int percentage)
{
    set_prop_int(brightness_path, ((float)percentage / 100 * brightness_max));
}

static void
usage(void)
{
    printf("Usage: backlight [-h] [-s percent | -i percent | -d percent]\n"
           "    -h Print this help\n"
           "    -s Set current brightness percentage\n"
           "    -i Increment brightness percentage\n"
           "    -d Decrement brightness percentage\n");
    exit(EXIT_SUCCESS);
}

int main(int argc, char** argv)
{
    int opt;
    int percentage;
    bool update = false;

    percentage = get_brightness();

    while ((opt = getopt(argc, argv, "hs:i:d:")) != -1) {
        switch (opt) {
        case 'h':
            usage();
            break;
        case 's':
            percentage = atoi(optarg);
            update = true;
            break;
        case 'i':
            percentage += atoi(optarg);
            update = true;
            break;
        case 'd':
            percentage -= atoi(optarg);
            update = true;
            break;
        }
    }

    if (update) {
        if (percentage > 100) {
            percentage = 100;
        } else if (percentage < 0) {
            percentage = 0;
        }
        set_brightness(percentage);
    }

    printf("%d\n", percentage);

    exit(EXIT_SUCCESS);
}
