////////////////////////////////////////////////////////////
//
// SFML - Simple and Fast Multimedia Library
// Copyright (C) 2007-2018 Laurent Gomila (laurent@sfml-dev.org)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////
//
// This file was edited to fit the needs of the Octalot project
//
////////////////////////////////////////////////////////////

#pragma once

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Vector3.hpp"
#include <algorithm>


////////////////////////////////////////////////////////////
/// \brief Utility class for manipulating 3D axis aligned cubes
///
/// Throughout this class we will use
/// X as width
/// Y as height
/// Z as depth
////////////////////////////////////////////////////////////
template <typename T>
class Cube
{
public:

    ////////////////////////////////////////////////////////////
    /// \brief Default constructor
    ///
    /// Creates an empty Cube (it is equivalent to calling
    /// Cube(0, 0, 0, 0, 0, 0)).
    ///
    ////////////////////////////////////////////////////////////
    Cube();

    ////////////////////////////////////////////////////////////
    /// \brief Construct the Cube from its coordinates
    ///
    /// Be careful, the last three parameters are the width, height
    /// and depth, not the right, bottom, and rear coordinates!
    ///
    /// \param CubeX   Left coordinate of the Cube
    /// \param CubeY   Top coordinate of the Cube
    /// \param CubeZ   Front coordinate of the Cube
    /// \param CubeWidth  Width of the Cube
    /// \param CubeHeight Height of the Cube
    /// \param CubeDepth Depth of the Cube
    ///
    ////////////////////////////////////////////////////////////
    Cube(T CubeLeft, T CubeTop, T CubeFront, T CubeWidth, T CubeHeight, T CubeDepth);

    ////////////////////////////////////////////////////////////
    /// \brief Construct the Cube from position and size
    ///
    /// Be careful, the last parameter is the size,
    /// not the bottom-right-rear corner!
    ///
    /// \param position Position of the top-left-front corner of the Cube
    /// \param size     Size of the Cube
    ///
    ////////////////////////////////////////////////////////////
    Cube(const Vector3<T>& position, const Vector3<T>& size);

    ////////////////////////////////////////////////////////////
    /// \brief Construct the Cube from another type of Cube
    ///
    /// This constructor doesn't replace the copy constructor,
    /// it's called only when U != T.
    /// A call to this constructor will fail to compile if U
    /// is not convertible to T.
    ///
    /// \param Cube Cube to convert
    ///
    ////////////////////////////////////////////////////////////
    template <typename U>
    explicit Cube(const Cube<U>& Cube);

    ////////////////////////////////////////////////////////////
    /// \brief Check if a point is inside the Cube's area
    ///
    /// This check is non-inclusive. If the point lies on the
    /// edge of the Cube, this function will return false.
    ///
    /// \param x X coordinate of the point to test
    /// \param y Y coordinate of the point to test
    /// \param z Z coordinate of the point to test
    ///
    /// \return True if the point is inside, false otherwise
    ///
    /// \see intersects
    ///
    ////////////////////////////////////////////////////////////
    bool contains(T x, T y, T z) const;

    ////////////////////////////////////////////////////////////
    /// \brief Check if a point is inside the Cube's area
    ///
    /// This check is non-inclusive. If the point lies on the
    /// edge of the Cube, this function will return false.
    ///
    /// \param point Point to test
    ///
    /// \return True if the point is inside, false otherwise
    ///
    /// \see intersects
    ///
    ////////////////////////////////////////////////////////////
    bool contains(const Vector3<T>& point) const;

    ////////////////////////////////////////////////////////////
    /// \brief Check the intersection between two Cubes
    ///
    /// \param Cube Cube to test
    ///
    /// \return True if Cubes overlap, false otherwise
    ///
    /// \see contains
    ///
    ////////////////////////////////////////////////////////////
    bool intersects(const Cube<T>& cube) const;

    ////////////////////////////////////////////////////////////
    /// \brief Check the intersection between two Cubes
    ///
    /// This overload returns the overlapped Cube in the
    /// \a intersection parameter.
    ///
    /// \param Cube         Cube to test
    /// \param intersection Cube to be filled with the intersection
    ///
    /// \return True if Cubes overlap, false otherwise
    ///
    /// \see contains
    ///
    ////////////////////////////////////////////////////////////
    bool intersects(const Cube<T>& cube, Cube<T>& intersection) const;

    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    T left;   ///< Left coordinate of the Cube
    T top;    ///< Top coordinate of the Cube
    T front;  ///< Front coordinate of the Cube
    T width;  ///< Width of the Cube
    T height; ///< Height of the Cube
    T depth;  ///< Depth of the Cube
};

////////////////////////////////////////////////////////////
/// \relates Cube
/// \brief Overload of binary operator ==
///
/// This operator compares strict equality between two Cubes.
///
/// \param left  Left operand (a Cube)
/// \param right Right operand (a Cube)
///
/// \return True if \a left is equal to \a right
///
////////////////////////////////////////////////////////////
template <typename T>
bool operator ==(const Cube<T>& left, const Cube<T>& right);

////////////////////////////////////////////////////////////
/// \relates Cube
/// \brief Overload of binary operator !=
///
/// This operator compares strict difference between two Cubes.
///
/// \param left  Left operand (a Cube)
/// \param right Right operand (a Cube)
///
/// \return True if \a left is not equal to \a right
///
////////////////////////////////////////////////////////////
template <typename T>
bool operator !=(const Cube<T>& left, const Cube<T>& right);

// Create typedefs for the most common types
typedef Cube<int>   IntCube;
typedef Cube<float> FloatCube;

template <typename T>
Cube<T>::Cube() :
        left  (0),
        top   (0),
        front (0),
        width (0),
        height(0),
        depth(0)
{

}

template <typename T>
Cube<T>::Cube(T CubeLeft, T CubeTop, T CubeFront, T CubeWidth, T CubeHeight, T CubeDepth) :
        left  (CubeLeft),
        top   (CubeTop),
        front (CubeFront),
        width (CubeWidth),
        height(CubeHeight),
        depth (CubeDepth)
{

}

template <typename T>
Cube<T>::Cube(const Vector3<T>& position, const Vector3<T>& size) :
        left  (position.x),
        top   (position.y),
        front (position.z),
        width (size.x),
        height(size.y),
        depth (size.z)
{

}

template <typename T>
template <typename U>
Cube<T>::Cube(const Cube<U>& Cube) :
        left  (static_cast<T>(Cube.left)),
        top   (static_cast<T>(Cube.top)),
        front (static_cast<T>(Cube.front)),
        width (static_cast<T>(Cube.width)),
        height(static_cast<T>(Cube.height)),
        depth (static_cast<T>(Cube.depth))
{
}

template <typename T>
bool Cube<T>::contains(T x, T y, T z) const
{
    // Cubes with negative dimensions are allowed, so we must handle them correctly

    // Compute the real min and max of the Cube on both axes
    T minX = std::min(left, static_cast<T>(left + width));
    T maxX = std::max(left, static_cast<T>(left + width));
    T minY = std::min(top, static_cast<T>(top + height));
    T maxY = std::max(top, static_cast<T>(top + height));
    T minZ = std::min(top, static_cast<T>(front + depth));
    T maxZ = std::max(top, static_cast<T>(front + depth));

    return (x >= minX) && (x < maxX) && (y >= minY) && (y < maxY) && (z >= minZ) && (z < maxZ);
}

template <typename T>
bool Cube<T>::contains(const Vector3<T>& point) const
{
    return contains(point.x, point.y, point.z);
}

template <typename T>
bool Cube<T>::intersects(const Cube<T>& cube) const
{
    Cube<T> intersection;
    return intersects(cube, intersection);
}

template <typename T>
bool Cube<T>::intersects(const Cube<T>& cube, Cube<T>& intersection) const
{
    // Cubes with negative dimensions are allowed, so we must handle them correctly

    // Compute the min and max of the first Cube on both axes
    T r1MinX = std::min(left, static_cast<T>(left + width));
    T r1MaxX = std::max(left, static_cast<T>(left + width));
    T r1MinY = std::min(top, static_cast<T>(top + height));
    T r1MaxY = std::max(top, static_cast<T>(top + height));
    T r1MaxZ = std::max(front, static_cast<T>(front + depth));
    T r1MinZ = std::min(front, static_cast<T>(front + depth));

    // Compute the min and max of the second Cube on both axes
    T r2MinX = std::min(cube.left, static_cast<T>(cube.left + cube.width));
    T r2MaxX = std::max(cube.left, static_cast<T>(cube.left + cube.width));
    T r2MinY = std::min(cube.top, static_cast<T>(cube.top + cube.height));
    T r2MaxY = std::max(cube.top, static_cast<T>(cube.top + cube.height));
    T r2MinZ = std::min(cube.front, static_cast<T>(cube.front + cube.depth));
    T r2MaxZ = std::max(cube.front, static_cast<T>(cube.front + cube.depth));

    // Compute the intersection boundaries
    T interLeft   = std::max(r1MinX, r2MinX);
    T interTop    = std::max(r1MinY, r2MinY);
    T interFront  = std::max(r1MinZ, r2MinZ);
    T interRight  = std::min(r1MaxX, r2MaxX);
    T interBottom = std::min(r1MaxY, r2MaxY);
    T interBack   = std::min(r1MaxZ, r2MaxZ);

    // If the intersection is valid (positive non zero area), then there is an intersection
    if ((interLeft < interRight) && (interTop < interBottom)&& (interFront < interBack))
    {
        intersection = Cube<T>(interLeft, interTop, interFront, interRight - interLeft, interBottom - interTop, interBack - interFront);
        return true;
    }
    else
    {
        intersection = Cube<T>(0, 0, 0, 0, 0, 0);
        return false;
    }
}

template <typename T>
inline bool operator ==(const Cube<T>& left, const Cube<T>& right)
{
    return (left.left == right.left) && (left.width == right.width) &&
           (left.top == right.top) && (left.height == right.height) &&
           (left.front == right.front) && (left.depth == right.depth);
}

template <typename T>
inline bool operator !=(const Cube<T>& left, const Cube<T>& right)
{
    return !(left == right);
}