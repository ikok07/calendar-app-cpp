//
// Created by Kaloyan Petkov on 1.08.24.
//

#include "FriendlyDateResponse.h"

fdate_t FriendlyDateResponse::data() {
    fdate_t date = {friendlyDateTime};
    return date;
}