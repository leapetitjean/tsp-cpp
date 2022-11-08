#include <Tour.hxx>
#include <fstream>
#include <string>
#include <types.hxx>

using std::stoi;
using std::string;

uint16_matrix get_distance_matrix(string file_name) {
    string line;
    std::ifstream file(file_name);
    if (file.is_open()) {
        getline(file, line);
        int n = stoi(line);
        uint16_matrix matrix(n, uint16_vector(n, 0));
        int i = 0, j = 0;
        while (getline(file, line, ' ')) {
            matrix.at(i).at(j) = stoi(line);
            j++;
            if (j >= n) {
                j = 0;
                i++;
            }
        }
        file.close();
        return matrix;
    }
    exit(EXIT_FAILURE);
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cerr << "Usage: ./tsp <distance_matrix_file> <rng_seed>" << endl;
        return EXIT_FAILURE;
    }
    string file_name(argv[1]);
    Tour::rng.seed(stoi(argv[2]));
    uint16_matrix distance_matrix = get_distance_matrix(file_name);

    Tour t1(distance_matrix);
    cout << t1 << endl;
    cout << "-> Nearest Neighbor" << endl;
    t1.nearest_neighbor();
    cout << t1 << endl;
    cout << "-> 2opt" << endl;
    t1.improvement_2opt();
    cout << t1 << endl;
    return EXIT_SUCCESS;
}