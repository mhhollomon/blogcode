#if ! defined(BASE_ID_HPP)
#define BASE_ID_HPP

#include <iostream>

//
// base_id
//
// A simple blind key identifier. Meant to be used to
// derive a new type that is guaranteed not to interchange
// with other types:
//
// struct my_id : public base_id<my_id> { using base_id<my_id>::base_id; };
// 

template <typename Derived>
class base_id;

template<typename T>
std::ostream& operator<<(std::ostream& strm, const base_id<T>& o);

template <typename Derived>
class base_id {
    static inline int next_value = -1;
    int id = -1;

    base_id(int t) : id(t) {}

  public:

    using tag_t = Derived;

    static tag_t get_next_id() {
        return tag_t(++next_value);
    }

    // default
    base_id() = default;

    // copy
    base_id(const base_id &o) = default;
    base_id &operator=(const base_id &o) = default;

    // move
    base_id(base_id &&o) = default;
    base_id &operator=(base_id &&o) = default;

    explicit operator int() const { return id; }

    bool operator ==(const base_id& o) const {
        return (o.id == id);
    }
    bool operator <(const base_id& o) const {
        return (id < o.id);
    }
    bool operator >(const base_id& o) const {
        return (id > o.id);
    }

    friend std::ostream& operator<< <>(std::ostream& strm, const base_id& o);
};

template<typename T>
std::ostream& operator<<(std::ostream& strm, const base_id<T>& o) {
    strm << o.id;
    return strm;
}



#endif
