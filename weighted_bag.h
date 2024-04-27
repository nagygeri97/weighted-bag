#include <iostream>
#include <map>
#include "uniform_random_generator.h"

template <typename Key, typename Weight>
class WeightedBag {
public:
    void put(const Key& key, const Weight& weight);
    Key get() const;
    friend std::ostream& operator<< <Key, Weight>(std::ostream&, const WeightedBag<Key, Weight>&);
private:
    void recreate();
    std::map<Key, Weight> kw_map;
    std::map<Weight, Key> wk_map;
    Weight total_weight = 0;
};

template <typename Key, typename Weight>
void WeightedBag<Key, Weight>::put(const Key& key, const Weight& weight) {
    total_weight += weight;
    kw_map[key] += weight;

    if (2*kw_map.size() < (wk_map.size() + 1)) {
        recreate();
    } else {
        wk_map[total_weight] = key;
    }
};

template <typename Key, typename Weight>
Key WeightedBag<Key, Weight>::get() const {
    Weight rand = UniformRandomGenerator<Weight>::generateInRange(0, total_weight);
    return wk_map.lower_bound(rand)->second;
};

template <typename Key, typename Weight>
void WeightedBag<Key, Weight>::recreate() {
    wk_map.clear();
    int cw = 0;
    for (const auto& [key, weight] : kw_map) {
        cw += weight;
        wk_map[cw] = key;
    }
}

template <typename Key, typename Weight>
std::ostream& operator<<(std::ostream& os, const WeightedBag<Key, Weight>& wb) {
    os << "total_weight=" << wb.total_weight << "\n";
    os << "kw_map.size()=" << wb.kw_map.size() << "\n";
    os << "kw_map=[\n";
    for (const auto& [key, weight] : wb.kw_map) {
        os << key << "->" << weight << "\n";
    }
    os << "]\n";
    os << "wk_map.size()=" <<wb.wk_map.size() << "\n";
    os << "wk_map=[\n";
    for (const auto& [weight, key] : wb.wk_map) {
        os << weight << "->" << key << "\n";
    }
    os << "]\n";
    os << "r=" << static_cast<double>(wb.wk_map.size()) / wb.kw_map.size() << "\n";
    return os;
}
