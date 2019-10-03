#include "base_id.hpp"

#include <iostream>

class my_id_t : public base_id<my_id_t> {
    using base_id<my_id_t>::base_id;
};

class my_other_id_t : public base_id<my_other_id_t> {
    using base_id<my_other_id_t>::base_id;
};


int main() {

    my_id_t id_1 = my_id_t::get_next_id();
    my_other_id_t id_o_1 = my_other_id_t::get_next_id();

    auto id_2 = id_1;

    std::cout << "Both of these should show 0 : " << id_1 << ' ' << id_2 << "\n";

    auto id_o_2 = my_other_id_t::get_next_id();

    std::cout << "This should be 1 : " << id_o_2 << "\n";

    // This should fail to compile
    // id_o_2 = id_1;
}
