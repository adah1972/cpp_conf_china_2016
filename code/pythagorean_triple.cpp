#include <iostream>
#include <range/v3/all.hpp>

using namespace ranges;

int main()
{
    // Define an infinite range of all the Pythagorean
    // triples:
    auto triples = view::for_each(view::ints(1), [=](int z)
        {
            return view::for_each(view::ints(1, z), [=](int x)
            {
                return view::for_each(view::ints(x, z), [=](int y)
                {
                    return yield_if(x*x + y*y == z*z,
                        std::make_tuple(x, y, z));
                });
            });
        });

    // Display the first 10 triples
    for (auto triple : triples | view::take(10) | view::bounded) {
        std::cout << '('
            << std::get<0>(triple) << ','
            << std::get<1>(triple) << ','
            << std::get<2>(triple) << ')' << '\n';
    }
}
