//
// Created by tiendat on 26.05.22.
//
#pragma once
#include "exception"


class CQuitException : std::exception {
public:
    const char * what () const noexcept override {
        return "BEY";
    }
};


