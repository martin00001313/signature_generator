#include <iostream>
#include <filesystem>

#include "./file_handler.h"

int main(int argc, char* argv[])
{
    if (argc != 3 && argc != 4) {
        std::cerr<<"Arguments list is incorrect! Should be input_file_path, output_file_path, batch_size(optional)";
        return 1;
    }
    
    std::string input_path{argv[1]};
    std::string output_path{argv[2]};
    const size_t batch_size = (argc == 4) ? atoi(argv[3]) : file_handler::MB;

    file_handler handler(std::move(input_path), std::move(output_path), batch_size);
    if (!handler.is_data_valid()) {
        std::cerr<<"The input data is incorrect. Please check!";
        return 1;
    }

    const bool state = handler.create_signature_safe();
    if (!state) {
        std::cerr<<"The operation has been failed!";
        return 1;
    }

    std::cout<<"The operation passed successfully!";

    return 0;
}
