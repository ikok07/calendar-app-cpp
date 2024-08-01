//
// Created by Kaloyan Petkov on 31.07.24.
//

#include "Coordinates.h"
#include <iostream>
using namespace std;

Coordinates::Coordinates(Data& data) {
    set_data(data);
}

Coordinates Coordinates::generate_from_input() {
    Coordinates coordinates;
    while (coordinates.get_data().lng == -1 || coordinates.get_data().lat == -1) {
        try {
            double longitude;
            double latitude;
            cout << "Enter longitude: ";
            cin >> longitude;
            cout << "Enter latitude: ";
            cin >> latitude;

            Data coordinates_data = {latitude, longitude};
            coordinates.set_data(coordinates_data);
        } catch (const exception& ex) {
            cout << ex.what() << endl;
        }
    }

    return coordinates;
}

Data Coordinates::get_data() const {
    Data data = {lat, lng};
    return data;
}

void Coordinates::set_data(Data &data) {
    if (data.lng < -180 || data.lng > 180) throw invalid_argument("Longitude must be between -180 and 180 degrees");
    if (data.lat < -90 || data.lat > 90) throw invalid_argument("Latitude must be between -90 and 90 degrees");
    this->lng = data.lng;
    this->lat = data.lat;
}
