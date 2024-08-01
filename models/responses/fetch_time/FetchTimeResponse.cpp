//
// Created by Kaloyan Petkov on 1.08.24.
//

#include "FetchTimeResponse.h"

rdate_t FetchTimeResponse::data() {
    rdate_t time_obj = {year, month, day, hour, minute, seconds, timeZone};
    return time_obj;
}
