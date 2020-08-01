//
// Created by Tobias Fuchs on 01.08.20.
//

#include "ThreadedObject.h"
ThreadedObject::ThreadedObject(ThreadLib::ThreadHolder &share)
    : ThreadLib::ThreadHolder(share) {}

ThreadedObject::ThreadedObject(const std::string &name)
    : ThreadLib::ThreadHolder(name) {}

void ThreadedObject::asyncVoidWithParams() {}

void ThreadedObject::asyncVoidWithoutParams() {}
