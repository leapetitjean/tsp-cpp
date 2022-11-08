#include <gtest/gtest.h>

#include "Tour.hxx"
#include "types.hxx"

TEST(TourTest, Initialisation) {
    uint16_matrix distance_matrix{{0, 1, 1, 1, 1},
                                  {1, 0, 1, 1, 1},
                                  {1, 1, 0, 1, 1},
                                  {1, 1, 1, 0, 1},
                                  {1, 1, 1, 1, 0}};
    Tour t1(distance_matrix);
    Tour t2(distance_matrix);
    ASSERT_EQ(5, t1.size());
    ASSERT_EQ(5, t1.get_permutation().size());
    uint16_vector vec{0, 1, 2, 3, 4};
    ASSERT_EQ(vec, t1.get_permutation());
    ASSERT_EQ(t1, t2);
}

TEST(TourTest, NearestNeighbor) {
    uint16_matrix distance_matrix{{0, 1, 1, 1, 1},
                                  {1, 0, 1, 1, 1},
                                  {1, 1, 0, 1, 1},
                                  {1, 1, 1, 0, 1},
                                  {1, 1, 1, 1, 0}};
    Tour t1(distance_matrix);
    t1.nearest_neighbor();
    ASSERT_EQ(5, t1.fitness());
}

TEST(TourTest, Rng) {
    uint16_matrix distance_matrix{{0, 1, 1, 1, 1},
                                  {1, 0, 1, 1, 1},
                                  {1, 1, 0, 1, 1},
                                  {1, 1, 1, 0, 1},
                                  {1, 1, 1, 1, 0}};
    Tour t1(distance_matrix);
    Tour t2(distance_matrix);
    t1.nearest_neighbor();
    t2.nearest_neighbor();
    ASSERT_NE(t1, t2);
}

TEST(TourTest, Operators) {
    uint16_matrix m1{{0, 1, 1, 1, 1},
                     {1, 0, 1, 1, 1},
                     {1, 1, 0, 1, 1},
                     {1, 1, 1, 0, 1},
                     {1, 1, 1, 1, 0}};
    uint16_matrix m2{{0, 1, 1, 1}, {1, 0, 1, 1}, {1, 1, 0, 1}, {1, 1, 1, 0}};
    Tour t1(m1);
    Tour t2(m2);
    Tour t3(m2);
    t1.nearest_neighbor();
    t2.nearest_neighbor();
    t3.nearest_neighbor();
    ASSERT_FALSE(t1 < t2);
    ASSERT_FALSE(t1 <= t2);
    ASSERT_TRUE(t1 > t2);
    ASSERT_TRUE(t1 >= t2);
    ASSERT_TRUE(t2 <= t3);
    ASSERT_TRUE(t3 <= t2);
    ASSERT_TRUE(t2 >= t3);
    ASSERT_TRUE(t3 >= t2);
}

TEST(TourTest, Fitness) {
    uint16_matrix m1{{0, 5, 2, 4, 5, 3, 6, 7},
                     {5, 0, 3, 6, 5, 5, 7, 1},
                     {2, 3, 0, 2, 4, 9, 8, 5},
                     {4, 6, 2, 0, 7, 3, 4, 5},
                     {5, 5, 4, 7, 0, 9, 7, 3},
                     {3, 5, 9, 3, 9, 0, 7, 3},
                     {6, 7, 8, 4, 7, 7, 0, 3},
                     {7, 1, 5, 5, 3, 3, 3, 0}};
    Tour t1(m1);
    uint16_t distance = 0;
    uint16_vector v = t1.get_permutation();
    for (int i = 0; i < t1.size() - 1; i++) {
        distance += m1.at(v.at(i)).at(v.at(i + 1));
    }
    distance += m1.at(v.at(0)).at(v.at(t1.size() - 1));
    ASSERT_EQ(t1.fitness(), distance);
    ASSERT_EQ(t1.fitness(), 43);
}