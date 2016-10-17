#include "Conversion.h"//
// Created by zhanggen on 16-10-16.
//

#include "ConversionTable.h"

Status ConversionTable::getNextStatus(const Status &nowStatus, const char &ch) {
    auto pos = conversionTable.equal_range(ch);

    for (pos; pos.first != pos.second; ++pos.first) {
        if (pos.first->second.getNowStatus() == nowStatus) {
            return pos.first->second.getToStatus();
        }
    }

    if (pos.first == pos.second) {
        return statusTable.getStatus("Error");
    }
}