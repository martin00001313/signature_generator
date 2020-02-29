#include <fstream>
#include <iostream>
#include <memory>
#include <string_view>

#include "./file_handler.h"
#include "./custom_exception.h"

void file_handler::create_signature()
{
    if (!is_data_valid()) {
        throw custom_exception(std::string{"The input data is not valid for the operation!"});
    }

    try {
        std::ifstream reader(m_input_file_path);
        const std::hash<std::string_view> hasher;
        std::ofstream writer(m_output_file_path);

        const size_t file_size = std::filesystem::file_size(m_input_file_path);
        const size_t batch_size = (m_batch_size < file_size) ? m_batch_size : file_size;

        const std::unique_ptr<char[]> data = std::make_unique<char[]>(batch_size);
        while (reader.read(data.get(), batch_size)) {
            const std::string_view viewer{data.get()};
            const size_t hash_value = hasher(viewer);
            writer << hash_value<<'\n';
        }

        // As fstream is RAII object, there is no need to call close method for reader and/or writer
    }
    catch (std::ios_base::failure &exp) {
        throw custom_exception{std::string{"Exception during signature geenration: "} + std::string{exp.what()}};
    }
}

bool file_handler::create_signature_safe() noexcept
{
    try {
        create_signature();
    }
    catch(const custom_exception& exp) {
        std::cerr<<exp.what();
        return false;
    }
    return true;
}