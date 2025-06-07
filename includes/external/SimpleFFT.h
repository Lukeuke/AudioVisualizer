#include <vector>
#include <complex>
#include <cmath>

#define PI 3.1415926535897932384626433832795

class SimpleFFT {
public:
    static std::vector<float> computeMagnitude(const std::vector<float>& input) {
        const size_t N = input.size();
        std::vector<std::complex<float>> output(N);

        for (size_t k = 0; k < N; ++k) {
            std::complex<float> sum(0.0f, 0.0f);
            for (size_t n = 0; n < N; ++n) {
                float angle = 2.0f * PI * k * n / static_cast<float>(N);
                sum += std::polar(input[n], -angle);
            }
            output[k] = sum;
        }

        std::vector<float> magnitudes(N / 2);
        for (size_t i = 0; i < N / 2; ++i) {
            magnitudes[i] = std::abs(output[i]);
        }

        return magnitudes;
    }
};

