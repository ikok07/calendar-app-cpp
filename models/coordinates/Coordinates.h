//
// Created by Kaloyan Petkov on 31.07.24.
//

#ifndef CALENDAR_APP_CPP_COORDINATES_H
#define CALENDAR_APP_CPP_COORDINATES_H

struct Data {
    double lat;
    double lng;
};

class Coordinates {
public:
    Coordinates() = default;
    explicit Coordinates(Data& data);

    static Coordinates generate_from_input();

    Data get_data() const;
    void set_data(Data& data);
private:
    double lat = -1;
    double lng = -1;
};


#endif //CALENDAR_APP_CPP_COORDINATES_H
