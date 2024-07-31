To fill all elemens with a particular value use assign or std::fill>


    result.resize(n);
    std::fill(result.begin(), result.end(), 0);
    result.assign(n, 0);