#include "Solution.h"
#include <iostream>
#include <algorithm>
#include <cassert>
#include <numeric>
#include <vector>

#include "../utils/random_generator.h"
#include "../utils/utils.h"

int Solution::best_score_wvcp = std::numeric_limits<int>::max();
int Solution::best_nb_colors = std::numeric_limits<int>::max();

const std::string Solution::header_csv = "nb_colors,penalty,score,solution";

Solution::Solution()
    : _colors(Graph::g->nb_vertices, -1), _free_vertices(Graph::g->nb_vertices) {
    // init _free_vertices
    int n{Graph::g->nb_vertices};
    std::generate(_free_vertices.begin(), _free_vertices.end(), [&n] {
        return --n;
    });
}

int Solution::add_to_color(const int vertex, int color) {
    assert(vertex < Graph::g->nb_vertices);
    assert(_colors[vertex] == -1);

    // if the color is -1 (ask for a new color group)
    if (color == -1) {
        if (_empty_colors.empty()) {
            // create a new color if needed
            _conflicts_colors.emplace_back(Graph::g->nb_vertices, 0);
            _colors_vertices.emplace_back();
            _colors_weights.emplace_back();
            _non_empty_colors.push_back(_nb_colors);
            color = _nb_colors;
            ++_nb_colors;
        } else {
            // reuse an old color currently empty
            color = _empty_colors.back();
            _empty_colors.pop_back();
            _non_empty_colors.push_back(color);
        }
    }

    // Update penalty
    _penalty += _conflicts_colors[color][vertex];

    // update conflicts for neighbors
    for (const auto &neighbor : Graph::g->neighborhood[vertex]) {
        ++_conflicts_colors[color][neighbor];
    }

    const int old_max_weight = max_weight(color);
    const int vertex_weight = Graph::g->weights[vertex];

    // update weights and vertices for the color class
    insert_sorted(_colors_weights[color], vertex_weight);
    insert_sorted(_colors_vertices[color], vertex);

    // update colors
    _colors[vertex] = color;

    // update score if the vertex increase the class weight
    if (vertex_weight > old_max_weight) {
        _score_wvcp += (vertex_weight - old_max_weight);
    }

    return color;
}

int Solution::delete_from_color(const int vertex) {
    const int color = _colors[vertex];
    assert(color != -1);
    assert(vertex < Graph::g->nb_vertices);

    // Update conflict score
    _penalty -= _conflicts_colors[color][vertex];

    // update conflicts for neighbors
    for (const int neighbor : Graph::g->neighborhood[vertex]) {
        --_conflicts_colors[color][neighbor];
    }

    // update wvcp score
    _score_wvcp += delta_wvcp_score_old_color(vertex);

    // remove from color group
    erase_sorted(_colors_weights[color], Graph::g->weights[vertex]);
    erase_sorted(_colors_vertices[color], vertex);

    _colors[vertex] = -1;

    // delete color if needed
    if (_colors_weights[color].empty()) {
        const auto it =
            std::find(_non_empty_colors.begin(), _non_empty_colors.end(), color);
        _non_empty_colors[std::distance(_non_empty_colors.begin(), it)] =
            _non_empty_colors.back();
        _non_empty_colors.pop_back();
        _empty_colors.push_back(color);
    }

    return color;
}

[[nodiscard]] int Solution::first_available_color(const int &vertex) {
    for (const int &color : _non_empty_colors) {
        if (_conflicts_colors[color][vertex] == 0) {
            return color;
        }
    }
    return -1;
}

[[nodiscard]] std::vector<int> Solution::available_colors(const int &vertex) const {
    std::vector<int> available_colors;
    for (const auto &color : _non_empty_colors) {
        if (_conflicts_colors[color][vertex] == 0) {
            available_colors.emplace_back(color);
        }
    }
    if (available_colors.empty()) {
        return {-1};
    }
    return available_colors;
}

[[nodiscard]] int Solution::delta_wvcp_score_old_color(const int vertex) const {
    const int color = _colors[vertex];
    const int vertex_weight = Graph::g->weights[vertex];
    // if the vertex was the only one in the color
    if (_colors_weights[color].size() == 1) {
        return -vertex_weight;
    }
    // if the vertex is the heaviest one and the second heaviest is lighter
    if (vertex_weight == max_weight(color) and
        _colors_weights[color].end()[-2] < vertex_weight) {
        return _colors_weights[color].end()[-2] - vertex_weight;
    }
    // else
    return 0;
}

[[nodiscard]] int Solution::delta_wvcp_score(const int vertex, const int color) const {
    const int vertex_weight{Graph::g->weights[vertex]};
    int diff{0};
    // if the vertex already have a color
    if (_colors[vertex] != -1) {
        diff = delta_wvcp_score_old_color(vertex);
    }
    // if the new color is empty
    if (color == -1 or is_color_empty(color)) {
        return vertex_weight + diff;
    }
    const int old_max_weight{max_weight(color)};
    // if the vertex is heavier than the heaviest of the new color class
    if (vertex_weight > old_max_weight) {
        // the delta is the difference between the vertex weight and the heavier
        // vertex
        return vertex_weight - old_max_weight + diff;
    }
    return diff;
}

[[nodiscard]] int Solution::delta_conflicts(const int vertex, const int color) const {
    if (color == -1) {
        return -_conflicts_colors[_colors[vertex]][vertex];
    }
    return _conflicts_colors[color][vertex] - _conflicts_colors[_colors[vertex]][vertex];
}

int Solution::pop_first_free_vertex() {
    int first_free_vertex{_free_vertices.back()};
    _free_vertices.pop_back();
    return first_free_vertex;
}

void Solution::shuffle_non_empty_color() {
    std::shuffle(_non_empty_colors.begin(), _non_empty_colors.end(), rd::generator);
}

bool Solution::check_solution() const {
    std::vector<int> max_colors_weights(_nb_colors, 0);
    int score = 0;

    for (int vertex = 0; vertex < Graph::g->nb_vertices; ++vertex) {
        if (Graph::g->neighborhood[vertex].empty() or _colors[vertex] == -1)
            continue;
        const int color = _colors[vertex];

        if (max_colors_weights[color] < Graph::g->weights[vertex]) {
            max_colors_weights[color] = Graph::g->weights[vertex];
        }
    }

    for (int color = 0; color < _nb_colors; ++color) {
        if (_colors_weights[color].empty())
            continue;

        assert(max_weight(color) == max_colors_weights[color]);
        score += max_colors_weights[color];
    }

    for (const int &color : _empty_colors) {
        (void)color;
        assert(max_colors_weights[color] == 0);
        assert(_colors_weights[color].empty());
    }

    assert(score == _score_wvcp);
    return true;
}

[[nodiscard]] int Solution::max_weight(const int &color) const {
    if (color == -1 or color >= _nb_colors or _colors_weights[color].empty()) {
        return 0;
    }
    return _colors_weights[color].back();
}

[[nodiscard]] bool Solution::has_conflicts(const int vertex) const {
    return _conflicts_colors[_colors[vertex]][vertex] != 0;
}

[[nodiscard]] bool Solution::is_color_empty(const int color) const {
    return color >= _nb_colors or _colors_vertices[color].empty();
}

[[nodiscard]] std::string Solution::line_csv() const {
//    return fmt::format("{},{},{},{}",
//                       _non_empty_colors.size(),
//                       _penalty,
//                       _score_wvcp,
//                       fmt::join(_colors, ":"));
    //TODO!!!
   // ????????????????????????????????????????????????
//    for (int i = 0; i < this->_colors.size(); ++i) {
//        std::cout << this->_colors[i]<<":";
//
//    }
//    std::cout<<std::endl;
//    std::cout<<"_score_wvcp"<<_score_wvcp <<std::endl;

    return "we";
}


[[nodiscard]] const std::vector<int> &Solution::colors() const {
    return _colors;
}

[[nodiscard]] int Solution::color(const int &vertex) const {
    return _colors[vertex];
}

[[nodiscard]] int Solution::nb_colors() const {
    return _nb_colors;
}

[[nodiscard]] const std::vector<int> &Solution::free_vertices() const {
    return _free_vertices;
}

[[nodiscard]] int Solution::score_wvcp() const {
    return _score_wvcp;
}

[[nodiscard]] int Solution::penalty() const {
    return _penalty;
}

[[nodiscard]] int Solution::conflicts_colors(const int &color, const int &vertex) const {
    return _conflicts_colors[color][vertex];
}

[[nodiscard]] const std::vector<int> &Solution::colors_vertices(const int &color) const {
    return _colors_vertices[color];
}

[[nodiscard]] long Solution::nb_non_empty_colors() const {
    return static_cast<long>(_non_empty_colors.size());
}

[[nodiscard]] const std::vector<int> &Solution::non_empty_colors() const {
    return _non_empty_colors;
}

[[nodiscard]] int Solution::first_free_vertex() const {
    return _free_vertices.back();
}

[[nodiscard]] std::vector<int>
Solution::nb_vertices_per_color(const int nb_colors_max) const {
    std::vector<int> nb_colors_per_col(nb_colors_max, 0);
    for (size_t i{0}; i < _colors_vertices.size(); ++i) {
        nb_colors_per_col[i] = static_cast<int>(_colors_vertices[i].size());
    }
    return nb_colors_per_col;
}

[[nodiscard]] const std::vector<std::vector<int>> &Solution::colors_weights() const {
    return _colors_weights;
}

[[nodiscard]] const std::vector<std::vector<int>> &Solution::conflicts_colors() const {
    return _conflicts_colors;
}

[[nodiscard]] int distance_approximation(const Solution &sol1, const Solution &sol2) {
    const int max_k{std::max(sol1.nb_colors(), sol2.nb_colors()) + 1};
    std::vector<std::vector<int>> same_color(max_k, std::vector<int>(max_k, 0));
    std::vector<int> maxi(max_k, 0);
    std::vector<int> sigma(max_k, 0);
    const auto &col1{sol1.colors()};
    const auto &col2{sol2.colors()};
    for (int vertex{0}; vertex < Graph::Graph::g->nb_vertices; ++vertex) {
        ++same_color[col1[vertex]][col2[vertex]];
        if (same_color[col1[vertex]][col2[vertex]] > maxi[col1[vertex]]) {
            maxi[col1[vertex]] = same_color[col1[vertex]][col2[vertex]];
            sigma[col1[vertex]] = col2[vertex];
        }
    }
    int sum{0};
    for (int color{0}; color < max_k; ++color) {
        sum += same_color[color][sigma[color]];
    }
    return Graph::Graph::g->nb_vertices - sum;
}

[[nodiscard]] int distance(const Solution &sol1, const Solution &sol2) {
    // get the max number of colors
    const int max_k{std::max(sol1.nb_colors(), sol2.nb_colors()) + 1};

    // compute the number of same color in sol1 and sol2
    std::vector<std::vector<int>> same_color(max_k, std::vector<int>(max_k, 0));

    const auto &col1{sol1.colors()};
    const auto &col2{sol2.colors()};
    for (int vertex{0}; vertex < Graph::Graph::g->nb_vertices; ++vertex) {
        ++same_color[col1[vertex]][col2[vertex]];
    }

    // find the corresponding color of sol1 in sol2
    std::vector<int> corresponding_color(max_k, 0);

    int distance{0};

    for (int c{0}; c < max_k; ++c) {
        // find highest number of same color
        int max_val{-1};
        int max_c1{-1};
        int max_c2{-1};
        for (int c1{0}; c1 < max_k; ++c1) {
            const auto max_element{
                std::max_element(same_color[c1].begin(), same_color[c1].end())};
            const int max_val_tmp{*max_element};
            if (max_val_tmp > max_val) {
                max_val = max_val_tmp;
                max_c1 = c1;
                max_c2 =
                    static_cast<int>(std::distance(same_color[c1].begin(), max_element));
            }
        }
        // add the highest number to the corresponding color
        corresponding_color[max_c1] = max_c2;
        distance += max_val;

        // delete same color
        std::fill(same_color[max_c1].begin(), same_color[max_c1].end(), -1);
        for (int i{0}; i < max_k; ++i) {
            same_color[i][max_c2] = -1;
        }
    }

    return Graph::g->nb_vertices - distance;
}
