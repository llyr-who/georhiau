#include <array>

template <typename T>
class point {
public:
    point(){};

private:
    std::array<T, 2> m_data;
}

