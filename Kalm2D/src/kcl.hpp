
#include <stdexcept>
#include <cassert>

class GeneralException : public std::runtime_error {
public:
    GeneralException() : std::runtime_error("General exception") {}
    GeneralException(const std::string& message) : std::runtime_error(message) {}
private:

};
