#include <iostream>
#include <getopt.h>
#include <fstream>
#include <array>
#include <list>

constexpr std::size_t TRANSFER_BLOCK_SIZE = 1024 * 1024;

struct UsbDevice
{
    using volume = std::list<std::string>;
public:
    UsbDevice(std::string _device_name = "unknown") noexcept: 
            sector_size(512), device_size(0),
            physical_name("physical_device_" + std::to_string(device_counter++)), 
            device_name(_device_name)
    {   }
public:
    std::int32_t sector_size;
    std::int64_t device_size;
public:
    std::string physical_name;
    std::string device_name;
private:
    static int device_counter;
    volume volumes;
};

int UsbDevice::device_counter = 0;

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
void write_image(T _src, T _dst, const UsbDevice& _usb_device)
{
    std::ifstream image(_src, std::ios_base::in | std::ios_base::binary);
    std::ofstream to_file(_dst, std::ios_base::out | std::ios_base::binary);
    std::array<char, TRANSFER_BLOCK_SIZE> buffer;

    buffer.fill(0);

    if(!image.is_open()){
        throw std::runtime_error("error: image not found");
    }

    if(!to_file.is_open()){
        throw std::runtime_error( "error: path to write not found");
    }

    std::streamsize read_bytes = 0, write_bytes = 0;
    
    while(true){   
        if((read_bytes = image.read(buffer.data(), TRANSFER_BLOCK_SIZE).gcount()) <= 0){
            throw std::runtime_error("error: failed to read image file");
        }

        if((write_bytes = to_file.write(buffer.data(), read_bytes).tellp()) <= 0){
            throw std::runtime_error("error: failed to write file");
        }

        if(read_bytes != write_bytes){
            throw std::runtime_error("error: the number of bytes read does not match the number of bytes written");

        }

        //we need to get iso file size and read untill reached iso file size
        //rewrite this, doesnt work
        break;
    }

    std::cout << "succes to write file" << std::endl;   
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
        UsbDevice usb("flash1");
        
        write_image<std::string>("arciso.iso", "tst", usb);
    }catch(const std::runtime_error& err){
        std::cerr << err.what() << std::endl;
    }   
    
    return EXIT_SUCCESS;
}
