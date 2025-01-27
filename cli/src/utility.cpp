/*
 *  Copyright (C) 2021-2023 Intel Corporation
 *  SPDX-License-Identifier: MIT
 *  @file utility.cpp
 */

#include <stdarg.h>
#include <syslog.h>
#include <unistd.h>

#include <cstdio>
#include <string>
#include <regex>
#include <iomanip>

#include "utility.h"

namespace xpum::cli {

bool isNumber(const std::string &str) {
    return str.size() && str.find_first_not_of("0123456789") == std::string::npos;
}

bool isInteger(const std::string &str) {
    const std::string bdfFormat = "^-?\\d+$";
    return std::regex_match(str, std::regex(bdfFormat));
}

bool isValidDeviceId(const std::string &str) {
    if (!isNumber(str)) {
        return false;
    }

    int value;
    try {
        value = std::stoi(str);
    } catch (const std::out_of_range &oor) {
        return false;
    }
    if (value < 0) {
        return false;
    }

    return true;
}

bool isValidTileId(const std::string &str) {
    if (!isNumber(str)) {
        return false;
    }

    int value;
    try {
        value = std::stoi(str);
    } catch (const std::out_of_range &oor) {
        return false;
    }
    if (value < 0 || value > 1) {
        return false;
    }

    return true;
}

bool isBDF(const std::string &str) {
    const std::string bdfFormat = "[a-f0-9]{4}:[a-f0-9]{2}:[a-f0-9]{2}\\.[a-f0-9]{1}";
    return std::regex_match(str, std::regex(bdfFormat));
}

bool isShortBDF(const std::string &str) {
    const std::string bdfFormat = "[a-f0-9]{2}:[a-f0-9]{2}\\.[a-f0-9]{1}";
    return std::regex_match(str, std::regex(bdfFormat));
}

std::string to_hex_string(uint64_t val, int width) {
    std::stringstream s;
    if (width == 0)
        s << std::string("0x") << std::hex << val;
    else
        s << std::string("0x") << std::setfill('0') << std::setw(width) << std::hex << val;
    return s.str();
}

std::string add_two_hex_string(std::string str1, std::string str2) {
    uint64_t u1 = std::stoul(str1.c_str(), 0, 16);
    uint64_t u2 = std::stoul(str2.c_str(), 0, 16);

    return to_hex_string(u1 + u2);
}

std::string toString(const std::vector<int> vec) {
    if (vec.empty()) {
        return "";
    }
    std::stringstream ss;
    for (size_t i = 0; i < vec.size(); i++) {
        if (i != 0) {
            ss << ", ";
        }
        ss << vec[i];
    }
    return ss.str();
}

}// end namespace xpum::cli
