#include <array>

//! point class.
//! T is the type.
//! D is the dimension of the space.

namespace georhiau {
namespace core {
template <typename T, std::size_t D>
class point {
public:
    point<typename... Ts,
          typename std::enable_if<
              std::conjunction<std::is_same<T, Ts>...>::value &&
                  (sizeof...(Ts) == R * C),
              int>::type = 0> constexpr matrix(Ts&&... elements) noexcept {
        m_data = std::array<T, R * C>{std::forward<Ts>(elements)...};
        //! We could end up only having D = 2,3.
        //! As these are the most commonly used dims.
        static_assert(D == 2, "Only implemented for D == 2.");
    }

    bool operator<(const point<T, D>& r) {
        return m_data[0] < r.m_data[0] ||
               (m_data[0] == r.m_data[0] && m_data[1] < r.m_data[1]);
    }

private:
    std::array<T, D> m_data;
};
}  // namespace core
}  // namespace georhiau

