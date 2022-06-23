#include <getopt.h>
#include <iostream>

static struct option long_opts[] =
{
    { "help",       no_argument,    NULL,   'h' },
    { "version",    no_argument,    NULL,   'v' },
    { NULL,         0,              NULL,   0   }
};

int main(int argc, char **argv)
{
    int short_char;
    while ((short_char = getopt_long(argc, argv, "hv", long_opts, NULL)) != -1)
    {
        switch (short_char)
        {
        case 'h':
            std::cout << "-h/--help" << std::endl;
            break;
        case 'v':
            std::cout << "-v/--version" << std::endl;
            break;
        }
    }

    return EXIT_SUCCESS;
}
