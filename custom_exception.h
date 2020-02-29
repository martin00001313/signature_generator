#include <exception>
#include <string>

class custom_exception: public std::exception
{
private:
    const std::string data;

public:
    template<class T = std::string>
    explicit custom_exception(T&& message) noexcept:
                data(std::forward<T>(message))
    {}

    custom_exception(const custom_exception&) = delete;
    custom_exception(custom_exception&&) = delete;

    custom_exception& operator=(const custom_exception&) = delete;
    custom_exception& operator=(custom_exception&&) = delete;

    virtual const char* what() const noexcept override
    {
        return data.data();
    }
};