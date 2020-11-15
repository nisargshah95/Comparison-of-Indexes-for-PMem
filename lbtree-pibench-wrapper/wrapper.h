#pragma once
// A wrapper for the lbtree

#include <iostream>
#include <string.h>
#include <stdlib.h>

#include "tree_api.hpp"
#include "../lbtree-src/lbtree.h"
#include "tree.h"
#include "mempool.h"


class lbtree_wrapper : public tree_api
{
public:
    lbtree_wrapper(const tree_options_t &opt);
    virtual ~lbtree_wrapper();

    virtual bool find(const char *key, size_t key_sz, char *value_out) override;
    virtual bool insert(const char *key, size_t key_sz, const char *value, size_t value_sz) override;
    virtual bool update(const char *key, size_t key_sz, const char *value, size_t value_sz) override;
    virtual bool remove(const char *key, size_t key_sz) override;
    virtual int scan(const char *key, size_t key_sz, int scan_sz, char *&values_out) override;

private:
    tree *tree_;
};
