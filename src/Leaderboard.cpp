#include "Leaderboard.hpp"
#include <algorithm>

void quicksort_leader(std::vector<std::pair<std::string,int>> &arr, int l, int r) {
    if (l >= r) return;
    int pivot = arr[(l + r) / 2].second;
    int i = l, j = r;
    while (i <= j) {
        while (arr[i].second > pivot) ++i; // descending
        while (arr[j].second < pivot) --j;
        if (i <= j) { std::swap(arr[i], arr[j]); ++i; --j; }
    }
    if (l < j) quicksort_leader(arr, l, j);
    if (i < r) quicksort_leader(arr, i, r);
}
