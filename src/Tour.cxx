#include "Tour.hxx"

mt19937 Tour::rng;

Tour::Tour(const uint16_matrix& distance_matrix)
    : permutation(distance_matrix.size(), 0),
      uint_dist(0, distance_matrix.size() - 1),
      distance_matrix(distance_matrix) {
    for (int i = 0; i < size(); i++) {
        permutation.at(i) = i;
    }
    for (int i = 0; i < size() - 1; i++) {
        value +=
            distance_matrix.at(permutation.at(i)).at(permutation.at(i + 1));
    }
    value +=
        distance_matrix.at(permutation.at(0)).at(permutation.at(size() - 1));
}

int Tour::get_nearest(int i, const uint16_uset& remaining) {
    int distance_min = numeric_limits<int>::max();
    int nearest = i;
    for (uint16_uset::const_iterator it = remaining.cbegin();
         it != remaining.cend(); it++) {
        int distance = distance_matrix.at(i).at(*it);
        if (distance < distance_min) {
            distance_min = distance;
            nearest = *it;
        }
    }
    value += distance_min;
    return nearest;
}

uint16_t Tour::distance(int i, int j) {
    return distance_matrix.at(permutation.at(i)).at(permutation.at(j));
}

void Tour::nearest_neighbor() {
    value = 0;
    uint16_uset remaining;
    for (int i = 0; i < size(); i++) {
        remaining.insert(i);
    }
    int nearest = uint_dist(Tour::rng);
    permutation.at(0) = nearest;
    remaining.erase(nearest);
    int i = 1;
    while (!remaining.empty()) {
        nearest = get_nearest(nearest, remaining);
        permutation.at(i++) = nearest;
        remaining.erase(nearest);
    }
    value +=
        distance_matrix.at(permutation.at(0)).at(permutation.at(size() - 1));
}

bool Tour::improvement_2opt() {
    bool improvement = true;
    while (improvement) {
        improvement = false;
        for (int i = 0; i < size() - 1; i++) {
            for (int j = i + 1; j < size(); j++) {
                int16_t delta = distance(i, j) +
                                distance((i + 1) % size(), (j + 1) % size()) -
                                distance(i, (i + 1) % size()) -
                                distance(j, (j + 1) % size());
                if (delta < 0) {
                    reverse(permutation.begin() + i + 1,
                            permutation.begin() + j + 1);
                    value += delta;
                    improvement = true;
                }
            }
        }
    }
    return improvement;
}