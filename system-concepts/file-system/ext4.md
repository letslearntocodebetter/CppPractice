Here's a low-level architecture overview of the **EXT4 file system** in an **RFC-style document**, complete with an **architecture diagram** and thorough breakdown of core components.

---

# **RFC: Low-Level Architecture of EXT4 File System**

## **1. Introduction**
This RFC describes the **low-level architecture** of the **EXT4 file system**, the fourth extended filesystem used in Linux. EXT4 is an evolution of EXT3 and includes several improvements in performance, scalability, and reliability. This document includes a diagram and detailed breakdown of each component.

---

## **2. EXT4 Architecture Diagram**

```
+----------------------------------------------------------------------------------------+
|                                      EXT4 Filesystem                                  |
|                                                                                        |
|  +------------------------+    +-------------------------+    +---------------------+  |
|  |     Superblock         |    |     Block Group         |    |     Journal (Optional) |
|  +------------------------+    +-------------------------+    +---------------------+  |
|  | Filesystem info        |    | Block Bitmap            |                               |
|  | Magic number           |    | Inode Bitmap            |                               |
|  | Block size             |    | Inode Table             |                               |
|  | Total blocks/inodes    |    | Data Blocks             |                               |
|  +------------------------+    +-------------------------+                               |
|                                                                                        |
|       +-------------------------+     +----------------------------+                    |
|       |        Inodes           |     |        Directories         |                    |
|       +-------------------------+     +----------------------------+                    |
|       | Metadata (mode, uid)    |     | Directory entries (dentry) |                    |
|       | File size, timestamps   |     | Filename -> Inode          |                    |
|       | Pointers to blocks      |     +----------------------------+                    |
|       +-------------------------+                                                        |
|                                                                                        |
+----------------------------------------------------------------------------------------+
```

---

## **3. Component-Level Breakdown**

### **3.1 Superblock**
- Located at a fixed offset (usually block 0 or 1).
- Holds **metadata** about the entire filesystem:
  - Block size
  - Total number of blocks/inodes
  - Mount state
  - Supported features
- Every block group has a backup copy.

---

### **3.2 Block Groups**
EXT4 divides the disk into **block groups** to improve performance and reduce fragmentation. Each group contains:

#### a. **Block Bitmap**
- Bit array marking used/free data blocks.

#### b. **Inode Bitmap**
- Bit array marking used/free inodes.

#### c. **Inode Table**
- Array of **inodes** (metadata for files/directories).

#### d. **Data Blocks**
- Actual content of files, directories, symlinks, etc.

---

### **3.3 Inodes**
Each **inode** represents a file or directory.
Contains:
- Metadata: file permissions, ownership, timestamps
- File size
- **Block pointers**:
  - 12 direct pointers
  - 1 indirect
  - 1 double indirect
  - 1 triple indirect

This hierarchical block structure enables large file support.

---

### **3.4 Directories**
- Stored as **special files**.
- Contain entries in the form:
  ```
  struct ext4_dir_entry {
      uint32_t inode;
      uint16_t rec_len;
      uint8_t  name_len;
      char     name[];
  };
  ```
- EXT4 uses **HTree (hashed B-tree)** indexing for faster lookups.

---

### **3.5 Journal (JBD2)**
- Optional journaling support.
- Uses a **write-ahead log** to store metadata changes before committing.
- Helps in crash recovery and consistency.

Journaling Modes:
- **Journal** (metadata + data)
- **Ordered** (default, metadata journaled, data flushed)
- **Writeback** (fastest, least safe)

---

## **4. Advanced Features**
- **Extents**: Replaces block mapping with extent trees (start + length), reducing fragmentation and improving large file performance.
- **Delayed Allocation**: Defers block allocation to improve performance.
- **Multiblock Allocation**: Allocates multiple blocks in one go.
- **Persistent Preallocation**: Reserve disk space in advance.
- **Online Defragmentation** support.

---

## **5. Block Allocation Overview**

```
Write Request ->
  Inode Lookup ->
    Find Free Block(s) via Bitmap ->
      Update Inode Pointers ->
        Update Bitmap, Metadata ->
          Journal (if enabled) ->
            Commit to Disk
```

---

## **6. Summary**

The EXT4 file system is a high-performance journaling filesystem that blends traditional block group layout with modern enhancements like extents and delayed allocation. It is designed for scalability, stability, and backward compatibility with EXT3/EXT2.

---

Would you like a **labeled image diagram** of the architecture to go with this text?
