#include <vector>
#include <complex>
#include <cmath>

#define PI 3.1415926535897932384626433832795
/**
 * @class SimpleFFT
 * @brief Klasa odpowiedzialna za Klasa SimpleFFT implementuje uproszczony algorytm DFT 
 * (dyskretnej transformaty Fouriera), który przekształca sygnał czasowy (wektor wartości float) 
 * na widmo amplitudowe w domenie częstotliwości.
 */
class SimpleFFT {
public:
    /**
     * @brief Statyczna metoda obliczająca widmo amplitudowe (moduł wartości zespolonych)
     */
    static std::vector<float> computeMagnitude(const std::vector<float>& input) {
        const size_t N = input.size();                                      ///< liczba próbek w sygnale
        std::vector<std::complex<float>> output(N);                         ///< wektor wynikowy liczb zespolonych

        for (size_t k = 0; k < N; ++k) {                                    ///< Główna pętla DFT - obliczanie każdej próbki widma w dziedzinie częstotliwości iterując po częstotliwościach
            std::complex<float> sum(0.0f, 0.0f);                            ///< Inicjalizacja sumy zespolonej na 0
            for (size_t n = 0; n < N; ++n) {                                ///< Iteracja po próbkach sygnału czasowego
                float angle = 2.0f * PI * k * n / static_cast<float>(N);    ///< Obliczenie kąta w radianach
                sum += std::polar(input[n], -angle);                        ///< Dodawnie wartości zespolonej
            }
            output[k] = sum;                                                ///< zapisanie wyniku DFT dla częstotliwości k
        }

        std::vector<float> magnitudes(N / 2);                               ///< Wektor na wartości amplitudy -> połowa spektrum -> symetria
        for (size_t i = 0; i < N / 2; ++i) {                                ///< Iteracja przez połowę próbek w sygnale
            magnitudes[i] = std::abs(output[i]);                            ///< obliczenie modułu liczby zespolonej 
        }   

        return magnitudes;                                                  ///< Zwrócenie wektora z amplitudami częstotliwości
    }
};

