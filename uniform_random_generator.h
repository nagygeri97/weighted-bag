#include <concepts>
#include <random>

template <typename NumericType> requires std::integral<NumericType> || std::floating_point<NumericType>
class UniformRandomGenerator {
public:
    static NumericType generateInRange(NumericType lower, NumericType upper);
};

template <std::integral IntegerType>
class UniformRandomGenerator<IntegerType> {
 public:
    static IntegerType generateInRange(IntegerType lower, IntegerType upper) {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_int_distribution<IntegerType> dist(lower + 1, upper);
        return dist(gen);
    }
};

template <std::floating_point FloatingType>
class UniformRandomGenerator<FloatingType> {
 public:
    static FloatingType generateInRange(FloatingType lower, FloatingType upper) {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_real_distribution<FloatingType> dist(lower, upper);
        return dist(gen);
    }
};