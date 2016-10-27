#include <iostream>
#include <range/v3/all.hpp>

using namespace ranges;

int main()
{
    // Lazy ranges for generating integer sequences
    auto const intsFrom = view::iota;
    auto const ints = [=](int i, int j)
        {
            return view::take(intsFrom(i), j - i + 1);
        };

    // Define an infinite range of all the Pythagorean
    // triples:
    auto triples = view::for_each(intsFrom(1), [=](int z)
        {
            return view::for_each(ints(1, z), [=](int x)
            {
                return view::for_each(ints(x, z), [=](int y)
                {
                    return yield_if(x*x + y*y == z*z,
                        std::make_tuple(x, y, z));
                });
            });
        });

    // Display the first 10 triples
    for (auto triple : triples | view::take(10)) {
        std::cout << '('
            << std::get<0>(triple) << ','
            << std::get<1>(triple) << ','
            << std::get<2>(triple) << ')' << '\n';
    }
}
