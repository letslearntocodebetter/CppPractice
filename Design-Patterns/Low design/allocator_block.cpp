class BitmapAllocator {
    uint8_t* memory_pool;      // Raw memory
    std::vector<bool> bitmap;  // One bit per block
    size_t block_size;         // e.g., 64 bytes
    size_t block_count;

public:
    BitmapAllocator(size_t total_size, size_t block_size)
        : block_size(block_size),
          block_count(total_size / block_size),
          bitmap(block_count, false)
    {
        memory_pool = new uint8_t[total_size];
    }

    void* allocate() {
        for (size_t i = 0; i < block_count; ++i) {
            if (!bitmap[i]) {
                bitmap[i] = true;
                return memory_pool + i * block_size; //point to the actual block;
            }
        }
        return nullptr; // Out of memory
    }

    void deallocate(void* ptr) {
        size_t offset = static_cast<uint8_t*>(ptr) - memory_pool; //start of the block
        size_t index = offset / block_size; // block size;
        bitmap[index] = false;
    }

    ~BitmapAllocator() {
        delete[] memory_pool;
    }
};

