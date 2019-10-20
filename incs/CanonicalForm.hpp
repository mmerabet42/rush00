#ifndef CANONICALFORM_HPP
# define CANONICALFORM_HPP

# define CANONICALFORM(CLASSNAME) \
	CLASSNAME() {} \
	~CLASSNAME () {} \
	CLASSNAME(const CLASSNAME &p_a) { *this = p_a; } \
	CLASSNAME &operator=(const CLASSNAME &) { return *this; }

# define CANONICALFORM2(CLASSNAME) \
	~CLASSNAME () {} \
	CLASSNAME(const CLASSNAME &p_a) { *this = p_a; } \
	CLASSNAME &operator=(const CLASSNAME &) { return *this; }

# define CANONICALFORM3(CLASSNAME) \
	CLASSNAME(const CLASSNAME &p_a) { *this = p_a; } \
	CLASSNAME &operator=(const CLASSNAME &) { return *this; }

#endif // CANONICALFORM_HPP
