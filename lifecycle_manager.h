//
// Created by lucian on 02.12.2017.
//

#ifndef LIFECYCLEMANAGER_LIFECYCLEMANAGER_H
#define LIFECYCLEMANAGER_LIFECYCLEMANAGER_H

#include "heap.h"

#define EVENT_COUNT 20

class lifecycle_manager;

typedef void (*action)(lifecycle_manager&, key_type);

class lifecycle_manager {
    heap<action, EVENT_COUNT> queue;

public:
    lifecycle_manager();

    void register_function(action func, key_type exec_time);

    void execute(key_type up_to);

    int size() {
        return queue.get_size();
    }

    void clear() {
        while (queue.remove_first()) {
            // remove_first() does all the job.
        }
    }
};


#endif //LIFECYCLEMANAGER_LIFECYCLEMANAGER_H
