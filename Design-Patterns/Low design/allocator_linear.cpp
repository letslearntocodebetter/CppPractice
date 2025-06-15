/*
 * Simple Memory Allocator with Linked List Management
 * 
 * Features:
 * - Fixed-size memory pool
 * - Linked list of blocks with headers
 * - First-fit allocation strategy
 * - Automatic coalescing on free
 * - Block splitting to minimize waste
 */
class MemoryAllocator {
private:
    // Block header containing metadata for each memory block
    struct BlockHeader {
        size_t size;            // Size of usable data (excluding header)
        bool is_free;           // Whether this block is available
        BlockHeader* next;      // Next block in the linked list
        BlockHeader* prev;      // Previous block in the linked list
        
        BlockHeader(size_t block_size = 0, bool free = true) 
            : size(block_size), is_free(free), next(nullptr), prev(nullptr) {}
    };
    
    // Configuration constants
    static constexpr size_t TOTAL_MEMORY = 1024;                    // 1 KB memory pool
    static constexpr size_t MIN_SPLIT_SIZE = sizeof(BlockHeader) + 8; // Minimum size for splitting
    static constexpr size_t HEADER_SIZE = sizeof(BlockHeader);
    
    // Memory pool and management
    alignas(std::max_align_t) char memory_pool_[TOTAL_MEMORY];  // Aligned memory pool
    BlockHeader* head_;                                         // First block in the list
    
public:
    MemoryAllocator() {
        initializePool();
    }
   
/**/   
 * Simple Memory Allocator with Linked List Management
 * 
 * Features:
 * - Fixed-size memory pool
 * - Linked list of blocks with headers
 * - First-fit allocation strategy
 * - Automatic coalescing on free
 * - Block splitting to minimize waste
 */
class MemoryAllocator {
private:
    // Block header containing metadata for each memory block
    struct BlockHeader {
        size_t size;            // Size of usable data (excluding header)
        bool is_free;           // Whether this block is available
        BlockHeader* next;      // Next block in the linked list
        BlockHeader* prev;      // Previous block in the linked list
        
        BlockHeader(size_t block_size = 0, bool free = true) 
            : size(block_size), is_free(free), next(nullptr), prev(nullptr) {}
    };
    
    // Configuration constants
    static constexpr size_t TOTAL_MEMORY = 1024;                    // 1 KB memory pool
    static constexpr size_t MIN_SPLIT_SIZE = sizeof(BlockHeader) + 8; // Minimum size for splitting
    static constexpr size_t HEADER_SIZE = sizeof(BlockHeader);
    
    // Memory pool and management
    alignas(std::max_align_t) char memory_pool_[TOTAL_MEMORY];  // Aligned memory pool
    BlockHeader* head_;                                         // First block in the list
    
    // Statistics for debugging
    mutable size_t total_allocated_ = 0;
    mutable size_t num_blocks_ = 1;
    
public:
    
    MemoryAllocator() {
        initializePool();
    }
    /**
     * Initialize the memory pool with one large free block
     */
    void initializePool() {
        head_ = reinterpret_cast<BlockHeader*>(memory_pool_);
        head_->size = TOTAL_MEMORY - HEADER_SIZE;
        head_->is_free = true;
        head_->next = nullptr;
        head_->prev = nullptr;
    }
    
    /**
     * Align size to prevent alignment issues
     */
    static size_t alignSize(size_t size) {
        constexpr size_t alignment = alignof(std::max_align_t);
        return (size + alignment - 1) & ~(alignment - 1);
    }
   
    /**
     * Find the first block that can accommodate the requested size
     */
    BlockHeader* findSuitableBlock(size_t size) {
        BlockHeader* current = head_;
        
        while (current) {
            if (current->is_free && current->size >= size) {
                return current;
            }
            current = current->next;
        }
        
        return nullptr; // No suitable block found
    }
      
    void* allocate(size_t size) {
        if (size == 0) {
            return nullptr;
        }
        
        // Align size to prevent alignment issues
        size_t aligned_size = alignSize(size);
        
        // Find first suitable block
        BlockHeader* block = findSuitableBlock(aligned_size);
        if (!block) {
            return nullptr; // Out of memory
        }
        
        // Split block if it's significantly larger than needed
        if (shouldSplitBlock(block, aligned_size)) {
            splitBlock(block, aligned_size);
        }
        
        // Mark block as allocated
        block->is_free = false;
        return getDataPointer(block); //reinterpret_cast<char*>(block) + HEADER_SIZE
    }
   
    bool shouldSplitBlock(const BlockHeader* block, size_t requested_size) const {
        return block->size >= requested_size + MIN_SPLIT_SIZE;
    }
    
    void splitBlock(BlockHeader* block, size_t size) {
        // Calculate position for the new block
        char* new_block_addr = reinterpret_cast<char*>(block) + HEADER_SIZE + size;
        BlockHeader* new_block = reinterpret_cast<BlockHeader*>(new_block_addr);
        
        // Initialize the new free block
        new_block->size = block->size - size - HEADER_SIZE; // the size of newly splited block 
        new_block->is_free = true;
        new_block->next = block->next;
        new_block->prev = block;
        
        if (block->next) {
            block->next->prev = new_block;
        }
        block->next = new_block;
        
        // Update the original block
        block->size = size;
    }
    
    static void* getDataPointer(BlockHeader* block) {
        return reinterpret_cast<char*>(block) + HEADER_SIZE;
    }
    
    static BlockHeader* getBlockHeader(void* ptr) {
        return reinterpret_cast<BlockHeader*>(static_cast<char*>(ptr) - HEADER_SIZE);
    }
    
    void deallocate(void* ptr) {
        if (!ptr) {
            return;
        }
        
        BlockHeader* block = getBlockHeader(ptr); //reinterpret_cast<char*> ptr - HEADER_SIZE;
         
        // Validate the pointer
		//return block_addr >= memory_pool_ && 
        //    block_addr < memory_pool_ + TOTAL_MEMORY/
        if (!isValidBlock(block)) { 
            throw std::invalid_argument("Invalid pointer - not from this allocator");
        }
        
        if (block->is_free) {
            throw std::runtime_error("Double free detected");
        }
        
        // Mark as free and update statistics
        block->is_free = true;
        // Coalesce with adjacent free blocks
        coalesceAdjacentBlocks(block);
    }
   
    
    void coalesceAdjacentBlocks(BlockHeader* block) {
        // Coalesce with next block
        if(block->next && block->next->is_free) {
            BlockHeader* next_block = block->next;
            // Merge the blocks
            block->size += HEADER_SIZE + next_block->size; // CURENT BLOCK
            block->next = next_block->next;
            
            if (next_block->next) {
                next_block->next->prev = block;
            }
            
        }
        
        // Coalesce with previous block
        if (block->prev && block->prev->is_free ) {
            BlockHeader* prev_block = block->prev;
            
            // Merge the blocks
            prev_block->size += HEADER_SIZE + block->size; //previousBlock
            prev_block->next = block->next;
            
            if (block->next) {
                block->next->prev = prev_block;
            }
        }
    }
    
};

// RAII wrapper for automatic memory management
template<typename T>
class AllocatorGuard {
private:
    MemoryAllocator& allocator_;
    T* ptr_;
    
public:
    template<typename... Args>
    explicit AllocatorGuard(MemoryAllocator& alloc, Args&&... args) 
        : allocator_(alloc), ptr_(nullptr) {
        
        void* raw_ptr = allocator_.allocate(sizeof(T));
        if (raw_ptr) {
            ptr_ = new(raw_ptr) T(std::forward<Args>(args)...);
        }
    }
    
    ~AllocatorGuard() {
        if (ptr_) {
            ptr_->~T();
            allocator_.deallocate(ptr_);
        }
    }
    
    // Disable copying, enable moving
    AllocatorGuard(const AllocatorGuard&) = delete;
    AllocatorGuard& operator=(const AllocatorGuard&) = delete;
    
    AllocatorGuard(AllocatorGuard&& other) noexcept 
        : allocator_(other.allocator_), ptr_(other.ptr_) {
        other.ptr_ = nullptr;
    }
    
    AllocatorGuard& operator=(AllocatorGuard&& other) noexcept {
        if (this != &other) {
            if (ptr_) {
                ptr_->~T();
                allocator_.deallocate(ptr_);
            }
            ptr_ = other.ptr_;
            other.ptr_ = nullptr;
        }
        return *this;
    }
    
    T* operator->() { return ptr_; }
    const T* operator->() const { return ptr_; }
    T& operator*() { return *ptr_; }
    const T& operator*() const { return *ptr_; }
    T* get() { return ptr_; }
    const T* get() const { return ptr_; }
    
    explicit operator bool() const { return ptr_ != nullptr; }
};

// Example usage and testing
void demonstrateCleanAllocator() {
    std::cout << "=== Clean Memory Allocator Demo ===\n\n";
    
    try {
        MemoryAllocator allocator;
        
        // Test RAII wrapper
        std::cout << "5. Testing RAII wrapper:\n";
        {
            AllocatorGuard<int> guard(allocator, 42);
            if (guard) {
                std::cout << "RAII managed value: " << *guard << '\n';
            }
            // Automatically deallocated when guard goes out of scope
        }
        
                
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

int main() {
    demonstrateCleanAllocator();
    return 0;
}

