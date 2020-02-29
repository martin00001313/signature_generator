#include <filesystem>
#include <functional>
#include <string>

class file_handler
{
public:
    template<class T = std::string>
    file_handler(T&& input_file_path, T&& output_file_path, size_t batch_size)
        : m_input_file_path(std::forward<T>(input_file_path)), m_output_file_path(std::forward<T>(output_file_path))
        , m_batch_size(batch_size)
    {}

    file_handler(const file_handler&) = delete;
    file_handler(file_handler&&) = delete;

    file_handler& operator=(file_handler&) = delete;
    file_handler& operator=(file_handler&&) = delete;

    void create_signature();

    bool create_signature_safe() noexcept;

    inline bool is_data_valid() const noexcept
    {
        return m_batch_size != 0 && std::filesystem::exists(m_input_file_path)
        && (!std::filesystem::exists(m_output_file_path)
            || std::filesystem::canonical(m_input_file_path) != std::filesystem::canonical(m_output_file_path));
    }

private:
    const std::string m_input_file_path;
    const std::string m_output_file_path;
    const size_t m_batch_size;

public:
    static constexpr size_t MB = 1024 * 1024;
};