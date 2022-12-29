#include "Cube.h"

// Global cube helper object for Animation sub classes
RGBLedCube Cube = RGBLedCube();

// Enables safe voxel guard
#define SAFE_VOXEL_ON 1

#if SAFE_VOXEL_ON
// Checks if invalid index is trying to be accessed and stops the program if so
#define SAFE_VOXEL_GUARD(index) \
    if (index >= LED_COUNT)     \
        while (1)               \
            ;
#else
#define SAFE_VOXEL_GUARD(index)
#endif

// Set 'SERPENT_LAYOUT' to true if leds are like this:
//
//     0 >  1 >  2 >  3 >  4
//                         |
//                         |
//     9 <  8 <  7 <  6 <  5
//     |
//     |
//    10 > 11 > 12 > 13 > 14
//
// Set 'SERPENT_LAYOUT' to false if leds are like this:
//
//     0 >  1 >  2 >  3 >  4
//                         |
//     .----<----<----<----'
//     |
//     5 >  6 >  7 >  8 >  9
//                         |
//     .----<----<----<----'
//     |
//    10 > 11 > 12 > 13 > 14
//
#define SERPENT_LAYOUT false

/*---------------------------------------------------------------------------------------
 * CUBE CLASS - 3D RGB LED Cube
 *-------------------------------------------------------------------------------------*/

RGBLedCube::RGBLedCube()
{
}

void RGBLedCube::setVoxel(Point p, CRGB col)
{
    setVoxel(p.x, p.y, p.z, col);
}

void RGBLedCube::setVoxel(uint8_t x, uint8_t y, uint8_t z, CRGB col)
{
    setVoxel(getIndex(x, y, z), col);
}

void RGBLedCube::setVoxel(uint16_t index, CRGB col)
{
    SAFE_VOXEL_GUARD(index)
    leds[index] = col;
}

CRGB RGBLedCube::getVoxel(Point p)
{
    return getVoxel(p.x, p.y, p.z);
}

CRGB RGBLedCube::getVoxel(uint8_t x, uint8_t y, uint8_t z)
{
    return getVoxel(getIndex(x, y, z));
}

CRGB RGBLedCube::getVoxel(uint16_t index)
{
    SAFE_VOXEL_GUARD(index)
    return CRGB(leds[index].r, leds[index].g, leds[index].b);
}

void RGBLedCube::fadeVoxel(Point p, uint8_t scale)
{
    fadeVoxel(p.x, p.y, p.z, scale);
}

void RGBLedCube::fadeVoxel(uint8_t x, uint8_t y, uint8_t z, uint8_t scale)
{
    fadeVoxel(getIndex(x, y, z), scale);
}

void RGBLedCube::fadeVoxel(uint16_t index, uint8_t scale)
{
    SAFE_VOXEL_GUARD(index)
    leds[index].nscale8(scale);
}

void RGBLedCube::fadeAll(uint8_t scale) // scale / 256 * color
{
    for (uint16_t i = 0; i < LED_COUNT; i++)
        fadeVoxel(i, scale);
}

void RGBLedCube::fill(CRGB col)
{
    for (uint16_t i = 0; i < LED_COUNT; i++)
        setVoxel(i, col);
}

void RGBLedCube::clear()
{
    fill(CRGB::Black);
}

void RGBLedCube::line(int x1, int y1, int z1, int x2, int y2, int z2, CRGB col)
{
    Point currentPoint = Point(x1, y1, z1);

    int dx = x2 - x1;
    int dy = y2 - y1;
    int dz = z2 - z1;
    int x_inc = (dx < 0) ? -1 : 1;
    int l = abs(dx);
    int y_inc = (dy < 0) ? -1 : 1;
    int m = abs(dy);
    int z_inc = (dz < 0) ? -1 : 1;
    int n = abs(dz);
    int dx2 = l << 1;
    int dy2 = m << 1;
    int dz2 = n << 1;

    if ((l >= m) && (l >= n))
    {
        int err_1 = dy2 - l;
        int err_2 = dz2 - l;

        for (int i = 0; i < l; i++)
        {
            setVoxel(currentPoint, col);

            if (err_1 > 0)
            {
                currentPoint.y += y_inc;
                err_1 -= dx2;
            }

            if (err_2 > 0)
            {
                currentPoint.z += z_inc;
                err_2 -= dx2;
            }

            err_1 += dy2;
            err_2 += dz2;
            currentPoint.x += x_inc;
        }
    }
    else if ((m >= l) && (m >= n))
    {
        int err_1 = dx2 - m;
        int err_2 = dz2 - m;

        for (int i = 0; i < m; i++)
        {
            setVoxel(currentPoint, col);

            if (err_1 > 0)
            {
                currentPoint.x += x_inc;
                err_1 -= dy2;
            }

            if (err_2 > 0)
            {
                currentPoint.z += z_inc;
                err_2 -= dy2;
            }

            err_1 += dx2;
            err_2 += dz2;
            currentPoint.y += y_inc;
        }
    }
    else
    {
        int err_1 = dy2 - n;
        int err_2 = dx2 - n;

        for (int i = 0; i < n; i++)
        {
            setVoxel(currentPoint, col);

            if (err_1 > 0)
            {
                currentPoint.y += y_inc;
                err_1 -= dz2;
            }

            if (err_2 > 0)
            {
                currentPoint.x += x_inc;
                err_2 -= dz2;
            }

            err_1 += dy2;
            err_2 += dx2;
            currentPoint.z += z_inc;
        }
    }

    setVoxel(currentPoint, col);
}

void RGBLedCube::line(Point p1, Point p2, CRGB col)
{
    line(p1.x, p1.y, p1.z, p2.x, p2.y, p2.z, col);
}

void RGBLedCube::sphere(int x, int y, int z, int r, CRGB col)
{
    for (int dx = -r; dx <= r; dx++)
    {
        for (int dy = -r; dy <= r; dy++)
        {
            for (int dz = -r; dz <= r; dz++)
            {
                if (sqrt(dx * dx + dy * dy + dz * dz) <= r)
                {
                    setVoxel(x + dx, y + dy, z + dz, col);
                }
            }
        }
    }
}

void RGBLedCube::sphere(Point p, int r, CRGB col)
{
    sphere(p.x, p.y, p.z, r, col);
}

void RGBLedCube::shell(float x, float y, float z, float r, CRGB col)
{
    float thickness = 0.1;
    for (int i = 0; i < CUBE_SIZE; i++)
        for (int j = 0; j < CUBE_SIZE; j++)
            for (int k = 0; k < CUBE_SIZE; k++)
                if (abs(sqrt((i - x, 2) + pow(j - y, 2) + pow(k - z, 2)) - r) < thickness)
                    setVoxel(i, j, k, col);
}

void RGBLedCube::shell(Point p, float r, CRGB col)
{
    shell(p.x, p.y, p.z, r, col);
}

void RGBLedCube::shell(float x, float y, float z, float r, float thickness, CRGB col)
{
    for (int i = 0; i < CUBE_SIZE; i++)
        for (int j = 0; j < CUBE_SIZE; j++)
            for (int k = 0; k < CUBE_SIZE; k++)
                if (abs(sqrt(pow(i - x, 2) + pow(j - y, 2) + pow(k - z, 2)) - r) < thickness)
                    setVoxel(i, j, k, col);
}

void RGBLedCube::shell(Point p, float r, float thickness, CRGB col)
{
    shell(p.x, p.y, p.z, r, thickness, col);
}

/*--------------------------- PRIVATE FUNCTIONS --------------------------*/
uint16_t RGBLedCube::getIndex(uint8_t x, uint8_t y, uint8_t z)
{
#if SERPENT_LAYOUT

    uint16_t xy = 0;
    if (y & 0x01) // Odd rows run backwards
    {
        uint8_t reverseX = (CUBE_SIZE - 1) - x;
        xy = (y * CUBE_SIZE) + reverseX;
    }
    else // Even rows run forwards
    {
        xy = (y * CUBE_SIZE) + x;
    }
    return (z * CUBE_SIZE * CUBE_SIZE) + xy;
#else
    return (z * CUBE_SIZE * CUBE_SIZE) + (x * CUBE_SIZE) + y;
#endif
}

Point RGBLedCube::getPoint(uint16_t index)
{
    uint8_t z = index / (CUBE_SIZE * CUBE_SIZE);              // get layer
    uint8_t layerIndex = index - (z * CUBE_SIZE * CUBE_SIZE); // get 2D index of layer
    uint8_t y = layerIndex / CUBE_SIZE;                       // get y on layer
    uint8_t x = layerIndex % CUBE_SIZE;                       // get x on layer

    return Point(x, y, z);
}
