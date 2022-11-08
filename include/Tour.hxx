#ifndef HEADER_TOUR
#define HEADER_TOUR

#include <limits>
#include <random>
#include <algorithm>

#include "types.hxx"

using std::mt19937;
using std::numeric_limits;
using std::random_device;
using std::uniform_int_distribution;
using std::reverse;

class Tour {
   private:
    uint16_vector permutation;
    uint16_t value = 0;
    uniform_int_distribution<int> uint_dist;
    const uint16_matrix& distance_matrix;
    int get_nearest(int i, const uint16_uset& remaining);
    uint16_t distance(int i, int j);

   public:
    static mt19937 rng;
    Tour(const uint16_matrix& distance_matrix);
    void nearest_neighbor();
    bool improvement_2opt();
    uint16_t size() const { return permutation.size(); }
    const uint16_vector& get_permutation() { return permutation; }
    uint16_t fitness() { return value; }

    friend bool operator==(const Tour& lhs, const Tour& rhs) {
        if (lhs.size() != rhs.size()) {
            return false;
        }
        for (int i = 0; i < lhs.size(); i++) {
            if (lhs.permutation.at(i) != rhs.permutation.at(i)) {
                return false;
            }
        }
        return true;
    }
    friend bool operator!=(const Tour& lhs, const Tour& rhs) {
        return !(lhs == rhs);
    }
    friend bool operator<(const Tour& lhs, const Tour& rhs) {
        return lhs.value < rhs.value;
    }
    friend bool operator>(const Tour& lhs, const Tour& rhs) {
        return rhs < lhs;
    }
    friend bool operator<=(const Tour& lhs, const Tour& rhs) {
        return !(lhs > rhs);
    }
    friend bool operator>=(const Tour& lhs, const Tour& rhs) {
        return !(lhs < rhs);
    }
    friend std::ostream& operator<<(std::ostream& out, const Tour& tour) {
        out << "Value: " << tour.value << endl;
        out << "Permutation: ";
        for (uint16_vector::const_iterator it = tour.permutation.begin();
             it != tour.permutation.end(); it++) {
            out << *it << " ";
        }
        return out << endl;
    }
};

#endif