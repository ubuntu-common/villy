#include <getopt.h>
#include <iostream>
#include <memory>
#include <list>

constexpr std::size_t transfer_block_size = 1024 * 1024;

struct UsbDevice
{
    using volume = std::list<std::string>;
public:
    UsbDevice(std::string _device_name): 
            sector_size(2048), device_size(0), 
            physical_name(""), device_name(_device_name)
    {   }
public:
    std::int32_t sector_size;
    std::int64_t device_size;
    volume volumes;
    std::string physical_name;    
    std::string device_name;
};

static struct option long_opts[] =
{
    { "help",       no_argument,            NULL,   'h' },
    { "version",    no_argument,            NULL,   'v' },
    { "src",        required_argument,      NULL,   's' },
    { "dst",        required_argument,      NULL,   'd' },
    { NULL,         0,                      NULL,    0  }
};

//valgrind --leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes \
         --verbose \
         --log-file=valgrind-out.txt \
         ./villy -h

template<class T>
void write_image(T _src, T _dst)
{
    std::unique_ptr<char> buffer(new char[transfer_block_size]());

    //

    //
}

int main(int argc, char **argv)
{
    std::string source, destination;
    int short_char = 0;
   
    while ((short_char = getopt_long(argc, argv, "hvs:d:", long_opts, NULL)) != -1)
    {
        switch (short_char)
        {
        case 'h':
            std::cout << "-h/--help" << std::endl;
            break;
        case 'v':
            std::cout << "-v/--version" << std::endl;
            break;
        case 's':
            source = optarg;
            break;
        case 'd':
            destination = optarg;
            break;
        }
    }

    try{
        write_image<std::string>(source, destination);
    }catch(const std::runtime_error& err){
        std::cerr << err.what() << std::endl;
    }   
    
    return EXIT_SUCCESS;
}
