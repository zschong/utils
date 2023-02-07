#include <functional>
#include <iostream>
#include <sstream>
#include <stdio.h>

/*************************************
 *  (Y * H)
 *        |
 *        |
 *        |
 *        |
 *        |_______.(W, H)
 *        |       |
 *        | block |
 *        |_______|_____________ (X * W)
 *      (0,0) 
 *
 *************************************/

template<
    int Y,
    int X,
    int H, 
    int W> 
class MapDivider {
public:
    MapDivider(void) {
        for (int y = 0; y < Y; y++) {
            for (int h = 0; h < H; h++) {
                for (int x = 0; x < X; x++) {
                    for (int w = 0; w < W; w++) {
                        buffer_[y][h][x][w] = y * X + x;
                    }
                }
            }
        } 

    }

    void Foreach(std::function<void(int i, uint8_t value)> f) {
        for (int i = 0; i < data_size; i++) {
            f(i, data[i]);
        }
    }

    void ForeachReverse(std::function<void(int i, uint8_t value)> f) {
        for (int i = 0; i < data_size; i++) {
            f(i, data[data_size - i - 1]);
        }
    }

    void Print(std::ostream& out) {
        Foreach([&](int i, uint8_t value) {
            if (i % (width) == 0) {
                out << "\n";
            }
            else if (i % W == 0) {
                out << " |";
            }
            if (i > 0 && i % session == 0) {
                out << " ";
                for (int n = 0; n < width; n++) {
                    out << "----";
                }
                for (int n = 1; n < X; n++) {
                    out << "--";
                }
                out << "\n";
            }
            char buf[8];
            snprintf(buf, sizeof(buf), " %2d ", value);
            out << buf;
        });
        out << "\n\n";
    }

 public:
    const uint32_t width     = X * W;
    const uint32_t height    = Y * H;
    const uint32_t session   = H * X * W;
    const uint32_t data_size = Y * X * H * W;
    const uint8_t *data      = (uint8_t*)buffer_;

 private:
    uint8_t buffer_[Y][H][X][W];
};


/*******************************************
    int main(void) {
        MapDivider<2,3,4,5>().Flatten(std::cout);
        MapDivider<5,4,3,2>().Flatten(std::cout);

        return 0;
    }

    output:
    0   0  |  1   1 
    0   0  |  1   1 
    0   0  |  1   1 
    ------------------
    2   2  |  3   3 
    2   2  |  3   3 
    2   2  |  3   3 

    0   0   0  |  1   1   1  |  2   2   2 
    0   0   0  |  1   1   1  |  2   2   2 
    0   0   0  |  1   1   1  |  2   2   2 
    0   0   0  |  1   1   1  |  2   2   2 
    ---------------------------------------
    3   3   3  |  4   4   4  |  5   5   5 
    3   3   3  |  4   4   4  |  5   5   5 
    3   3   3  |  4   4   4  |  5   5   5 
    3   3   3  |  4   4   4  |  5   5   5 
    ---------------------------------------
    6   6   6  |  7   7   7  |  8   8   8 
    6   6   6  |  7   7   7  |  8   8   8 
    6   6   6  |  7   7   7  |  8   8   8 
    6   6   6  |  7   7   7  |  8   8   8 

*******************************************/

