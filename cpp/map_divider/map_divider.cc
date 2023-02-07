#include "map_divider.h"

int main(void) {
    MapDivider<2,2,3,2>().Print(std::cout);
    MapDivider<3,3,4,3>().Print(std::cout);

    return 0;
}
