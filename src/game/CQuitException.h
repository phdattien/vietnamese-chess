
// Created by tiendat on 26.05.22.
//
#pragma once
#include "exception"

/**
 * Exception handeling quit command
 */
class CQuitException : std::exception {
public:
    const char * what () const noexcept override {
        return "";
    }
};
