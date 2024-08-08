To fill all elemens with a particular value use assign or std::fill>


    result.resize(n);
    std::fill(result.begin(), result.end(), 0);
    result.assign(n, 0);

    // not to use but good to know that 
    std::memset(result.data(), 0, result.size() * sizeof(int));


    // otherwise use resize, it take 2 argument, one is number of elment and the init value

    result.resize(n, -1);
