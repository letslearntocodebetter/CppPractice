
Why Are Move Constructor and Move Assignment Declared as noexcept?
1. Performance Optimization
Standard containers like std::vector, std::list, etc., rely on move semantics when resizing or relocating elements.

If a move constructor or move assignment operator is marked as noexcept, the Standard Library can use move operations instead of copy operations, leading to performance improvements.

If they are not marked as noexcept, the compiler may assume they could throw exceptions and instead perform copy operations, which are usually more expensive.

2. Exception Safety Guarantees
If a move constructor throws an exception, the program could end up in an inconsistent state. Declaring it noexcept ensures that move operations are safe to perform without worrying about exception handling overhead.

3. STL Compatibility
Many STL containers (like std::vector, std::deque) check whether move operations are noexcept before deciding whether to use them. If a move operation is not marked noexcept, the container may choose copy instead, which might be less efficient.

What If Move Constructor/Move Assignment Is Not Declared noexcept?
STL containers may avoid move operations in favor of copies.

Move operations might be used but could introduce undefined behavior if they throw exceptions during exception handling.

Advantages of Declaring a Function noexcept
Better Optimizations

The compiler can generate more optimized code because it doesn’t need to consider exception unwinding.

Ensures Strong Exception Safety

Code that relies on strong exception safety can assume noexcept functions won’t leave objects in an inconsistent state.

More Efficient STL Usage

STL algorithms and containers prefer noexcept move operations over copy operations, leading to better performance.

