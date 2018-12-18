#include <iostream>
#include <array>
#include <algorithm>
#include <chrono>
#include <ctime>
#include <initializer_list>

// 3d vector POD
class Vector3D
{
public:
  inline Vector3D(){}

  inline Vector3D(std::initializer_list<double> xyz2) noexcept
  {
    std::copy(xyz2.begin(), xyz2.end(), xyz.begin());
  }

  static constexpr std::size_t const DIM = 3;
  std::array<double,DIM> xyz;
};

inline Vector3D operator-(Vector3D const &lhs, Vector3D const &rhs)
{
  Vector3D subtraction;
  subtraction.xyz[0] = lhs.xyz[0]-rhs.xyz[0];
  subtraction.xyz[1] = lhs.xyz[1]-rhs.xyz[1];
  subtraction.xyz[2] = lhs.xyz[2]-rhs.xyz[2];
  return subtraction;
}

// array of vector3D
constexpr int const N = 256;
using Vector3DField = std::array<Vector3D,N>;

// Subtract 2 arrays of 3d vectors
void subtract(Vector3DField const &lhs, Vector3DField const &rhs, Vector3DField &subtraction)
{
  #pragma ivdep
  for(int i=0; i<N; ++i)
    subtraction[i] = lhs[i] - rhs[i];
};

int main (int argc, char *argv[])
{
    // Define unpredictable number at compile time
    double const numA = static_cast<double>(argc);
    Vector3D const vecA = {numA, numA, numA};
    Vector3D const vecB = {numA*2,numA*3,numA*4};

    // Array of structures of 3 doubles to test
    Vector3DField fieldVecA, fieldVecB, fieldVecC;
    std::fill(fieldVecA.begin(), fieldVecA.end(), vecA);
    std::fill(fieldVecB.begin(), fieldVecB.end(), vecB);

    // Start chrono
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();

    // Function to vectorize (10M times to get a relevant computation time)
    int const nLoop = 10000000 - argc; // unpredictable loop count
    for(int n=0; n<nLoop; n++)
      subtract(fieldVecA, fieldVecB, fieldVecC);

    // Stop chrono
    int elapsed_seconds = std::chrono::duration_cast<std::chrono::milliseconds>
      (std::chrono::system_clock::now()-start).count();
    std::cout << "Elapsed time: " << elapsed_seconds << " ms " << std::endl;
    std::cout << fieldVecC[0].xyz[0] << std::endl; // to forbid compiler to skip the whole computation
};
