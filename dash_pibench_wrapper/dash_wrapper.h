#include <iostream>
#include <stdlib.h>
#include <string.h>

#include "../util/pair.h"
#ifdef PMEM
#include <libpmemobj.h>
#endif

#include "allocator.h"
#include "ex_finger.h"
#include "tree_api.hpp"



class dash_wrapper: public tree_api
{
public:
    dash_wrapper(const tree_options_t &opt);
    virtual ~dash_wrapper();

    //virtual Value_t find(T) override;
    //virtual int insert(T, Value_t) override;
    //virtual int update(T, Value_t) override;
    //virtual bool remove(T) override;

    virtual bool find(const char *key, size_t key_sz, char *value_out) override;
    virtual bool insert(const char *key, size_t key_sz, const char *value, size_t value_sz) override;
    virtual bool update(const char *key, size_t key_sz, const char *value, size_t value_sz) override;
    virtual bool remove(const char *key, size_t key_sz) override;
    virtual int scan(const char *key, size_t key_sz, int scan_sz, char *&values_out) override;

private:
    std::hash<std::string> str_hash;
    Hash<long long> *hash_table_;
};
