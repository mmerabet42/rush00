#ifndef UTILS_HPP
# define UTILS_HPP

# include <string>
# include <sstream>

template <typename T>
std::string toString(const T &p_t)
{
	std::ostringstream ss;

	ss << p_t;
	return ss.str();
}

# define TAB_SIZE(TAB) sizeof(TAB) / sizeof(TAB[0])

#endif // UTILS_HPP
