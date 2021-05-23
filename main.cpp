#include "application.h"

constexpr int rows = 3;
constexpr int columns = 3;

int main(int argc, char *argv[])
{
    Application a(rows, columns, argc, argv);
    return a.exec();
}
