#pragma once
#include <cuda_runtime.h>

// GPU tensor in NCHW layout. Move-only (no copies — GPU alloc is expensive).
class Tensor {
public:
    float* d_data;   // device pointer
    int n, c, h, w;

    Tensor(int n, int c, int h, int w);
    ~Tensor();

    Tensor(Tensor&& o) noexcept;
    Tensor& operator=(Tensor&& o) noexcept;
    Tensor(const Tensor&) = delete;
    Tensor& operator=(const Tensor&) = delete;

    Tensor clone()               const;  // deep copy on GPU
    void   fromHost(const float* src);   // host → device
    void   toHost(float* dst)    const;  // device → host
    void   zero();

    int size()  const { return n * c * h * w; }
    int bytes() const { return size() * (int)sizeof(float); }
};
