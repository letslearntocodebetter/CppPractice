push_back and emplace_back are common in std::vector and std::deque.
push and emplace are found in std::stack, std::queue, and std::priority_queue.
insert and emplace are used in std::set, std::map, and their multi variants.

For unorded_map hash and equality operators are need
std::set or std::map (ordered variants), you would need a custom comparison function (usually a less comparator)

std::unordered_map<Person, std::string, decltype(personHash), decltype(personEqual)> people(10, personHash, personEqual);
// Step 4: Use std::unordered_set with custom object
std::unordered_set<Person, PersonHash, PersonEqual> people;

  auto personHash = [](const Person& p) -> std::size_t {
        std::size_t h1 = std::hash<std::string>()(p.name);
        std::size_t h2 = std::hash<int>()(p.age);
        return h1 ^ (h2 << 1); // or use any other combining method
    };

    // Lambda function for comparing two Person objects
    auto personEqual = [](const Person& p1, const Person& p2) -> bool {
        return p1.name == p2.name && p1.age == p2.age;
    };

    // Step 4: Use std::unordered_map with custom object and lambda functions

    // Step 4: Use std::unordered_map with custom object and lambda functions
  
    std::less{} for min hea default
    std::greater{} for max heap default

    std::greater<int> for max heap defaul   
    std::less<int> for min heap default
    