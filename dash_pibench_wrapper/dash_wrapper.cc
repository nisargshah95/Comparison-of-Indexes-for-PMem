#include "dash_wrapper.h"


extern "C" tree_api *create_tree(const tree_options_t &opt) {
    return new dash_wrapper(opt);
}

dash_wrapper::dash_wrapper(const tree_options_t &opt) {

// pool path and name
//static const char *pool_name = "/pmem/dash";
static const char *pool_name = opt.pool_path.c_str();

// pool size
//static const size_t pool_size = 1024ul * 1024ul * 1024ul * 1ul;
static const size_t pool_size = opt.pool_size;

bool file_exist = false;
if (FileExists(pool_name)) file_exist = true;
Allocator::Initialize(pool_name, pool_size);

// Step 2: Allocate the initial space for the hash table on PM and get the
// root; we use Dash-EH in this case.
hash_table_ = reinterpret_cast<Hash<long long> *>(
    Allocator::GetRoot(sizeof(extendible::Finger_EH<long long>)));

// Step 3: Initialize the hash table
if (!file_exist) {
    // During initialization phase, allocate 64 segments for Dash-EH
    size_t segment_number = 64;
    new (hash_table_) extendible::Finger_EH<long long>(
    segment_number, Allocator::Get()->pm_pool_);
}else {
    new (hash_table_) extendible::Finger_EH<long long>();
  }
}

dash_wrapper::~dash_wrapper() {
    //delete hash_table_;
}

bool dash_wrapper::find(const char *key, size_t key_sz, char *value_out) {
    std::cout << "lookup " << key << "\n";
    std::string key_str(key);
    long long key_ll = (long long) str_hash(key_str);
    uint64_t not_found = 0;
    auto epoch_guard = Allocator::AquireEpochGuard();
    //TODO: Populate value_out
    return (hash_table_->Get(key_ll, true) != NONE);
}


bool dash_wrapper::insert(const char *key, size_t key_sz, const char *value, size_t value_sz) {
    std::cout << "Insert : Key is " << key << ", Value is "<<value<<"\n";
    std::string key_str(key);
    long long key_ll = (long long) str_hash(key_str);
    auto epoch_guard = Allocator::AquireEpochGuard();
    return (hash_table_->Insert(key_ll, value, true) == 0);
}


bool dash_wrapper::update(const char *key, size_t key_sz, const char *value, size_t value_sz) {
    std::cout << "Update : Key is " << key << ", Value is "<<value<<"\n";
    std::string key_str(key);
    long long key_ll = (long long) str_hash(key_str);
    return (hash_table_->Insert(key_ll, value, true) == 0);
}

bool dash_wrapper::remove(const char *key, size_t key_sz) {
    std::cout << "Delete : Key is " << key<<"\n";
    std::string key_str(key);
    long long key_ll = (long long) str_hash(key_str);
    auto epoch_guard = Allocator::AquireEpochGuard();
    hash_table_->Delete(key_ll, true);
    return true;
}

int dash_wrapper::scan(const char *key, size_t key_sz, int scan_sz, char *&values_out) {
    // Operation not implemented in lbtree
    return -1;
}
