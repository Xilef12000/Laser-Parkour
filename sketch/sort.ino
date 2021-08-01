//this is an bubble-sort-algorithm
//visit https://de.wikipedia.org/wiki/Bubblesort for more infos
void sort(userdataFormat sort_arr[]) {
  for (int sort_n = 11; sort_n > 1; --sort_n) {
    for (int sort_i = 0; sort_i < sort_n - 1; ++sort_i) {
      if (sort_arr[sort_i].userdataTime > sort_arr[sort_i + 1].userdataTime) {
        userdataFormat sort_temp = sort_arr[sort_i];
        sort_arr[sort_i] = sort_arr[sort_i + 1];
        sort_arr[sort_i + 1] = sort_temp;
      }
    }
  }
}
