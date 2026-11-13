
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <memory>
#include <algorithm>
#include <utility>

using namespace std;

// Represents a position (x, y)
struct Point {
    double x{0}, y{0};
};

// Calculate distance between two points
double distanceBetween(const Point& a, const Point& b) {
    return hypot(a.x - b.x, a.y - b.y);
}

// Different vehicle modes
enum class Mode {
    IDLE,
    PATROL,
    RTL,
    LANDED
};

// Convert mode into readable text
string modeName(Mode m) {
    switch (m) {
        case Mode::IDLE:   return "IDLE";
        case Mode::PATROL: return "PATROL";
        case Mode::RTL:    return "RTL";
        case Mode::LANDED: return "LANDED";
    }
    return "UNKNOWN";
}

// Base class
class Vehicle {
public:

    // Constructor
    Vehicle(string name, Point home, double speed,
            double geofenceRadius)
        : name_(move(name)),
          pos_(home),
          home_(home),
          speed_(speed),
          fence_(geofenceRadius) {}

    // Virtual destructor
    virtual ~Vehicle() = default;

    // Pure virtual functions
    virtual string type() const = 0;
    virtual double drainPerUnit() const = 0;

    // Assign mission waypoints
    void setMission(const vector<Point>& wps) {
        waypoints_ = wps;
        nextWp_ = 0;
        reason_.clear();

        if (waypoints_.empty()) {
            mode_ = Mode::IDLE;
        } else {
            mode_ = Mode::PATROL;
        }
    }

    // Move vehicle one step
    void step() {

        if (mode_ == Mode::IDLE || mode_ == Mode::LANDED)
            return;

        // Check safety conditions
        if (mode_ == Mode::PATROL) {

            if (battery_ < 30.0) {
                reason_ = "LOW BATTERY";
                mode_ = Mode::RTL;
            }
            else if (distanceBetween(pos_, home_) > fence_) {
                reason_ = "GEOFENCE BREACH";
                mode_ = Mode::RTL;
            }
        }

        // Select destination
        Point target;

        if (mode_ == Mode::PATROL) {
            target = waypoints_[nextWp_];
        } else {
            target = home_;
        }

        moveToward(target);

        // Check if destination reached
        if (distanceBetween(pos_, target) < 0.5) {

            if (mode_ == Mode::RTL) {
                mode_ = Mode::LANDED;
            }
            else {
                nextWp_++;

                if (nextWp_ >= waypoints_.size()) {
                    reason_ = "MISSION COMPLETE";
                    mode_ = Mode::RTL;
                }
            }
        }
    }

    // Check whether vehicle has landed
    bool finished() const {
        return mode_ == Mode::LANDED;
    }

    // Display vehicle information
    void printStatus(int tick) const {

        cout << fixed << setprecision(1)
             << "t=" << setw(3) << tick
             << " | " << setw(6) << name_
             << " (" << type() << ") "
             << "pos=(" << pos_.x << "," << pos_.y << ") "
             << "bat=" << battery_ << "% "
             << "mode=" << modeName(mode_);

        if (!reason_.empty()) {
            cout << " [" << reason_ << "]";
        }

        cout << "\n";
    }

    // Save vehicle information to CSV
    void logCsv(ofstream& out, int tick) const {

        out << tick << ","
            << name_ << ","
            << pos_.x << ","
            << pos_.y << ","
            << battery_ << ","
            << modeName(mode_) << "\n";
    }

protected:

    string name_;
    Point pos_, home_;

    double speed_;
    double fence_;
    double battery_{100.0};

    Mode mode_{Mode::IDLE};

    string reason_;

    vector<Point> waypoints_;
    size_t nextWp_{0};

private:

    // Move towards a destination
    void moveToward(const Point& target) {

        double d = distanceBetween(pos_, target);

        double movement = min(speed_, d);

        if (d > 0) {

            pos_.x += (target.x - pos_.x) / d * movement;
            pos_.y += (target.y - pos_.y) / d * movement;
        }

        // Reduce battery
        battery_ -= movement * drainPerUnit();

        if (battery_ < 0) {
            battery_ = 0;
        }
    }
};

// Drone class
class Drone : public Vehicle {
public:

    using Vehicle::Vehicle;

    string type() const override {
        return "UAV";
    }

    double drainPerUnit() const override {
        return 0.8;
    }
};

// Boat class
class Boat : public Vehicle {
public:

    using Vehicle::Vehicle;

    string type() const override {
        return "USV";
    }

    double drainPerUnit() const override {
        return 0.4;
    }
};

// Main function
int main() {

    // Store different vehicles using base-class pointers
    vector<unique_ptr<Vehicle>> fleet;

    // Create a drone
    fleet.push_back(
        make_unique<Drone>(
            "Spot-1", Point{0, 0}, 5.0, 60.0
        )
    );

    // Create a boat
    fleet.push_back(
        make_unique<Boat>(
            "Sea-1", Point{0, 0}, 2.0, 60.0
        )
    );

    // Assign patrol routes
    fleet[0]->setMission({
        {20, 0}, {20, 20}, {0, 20}, {0, 0}
    });

    fleet[1]->setMission({
        {30, 10}, {70, 10}, {70, 40}
    });

    // Create CSV file
    ofstream log("patrol_log.csv");

    if (!log.is_open()) {
        cout << "Unable to create log file!" << endl;
        return 1;
    }

    log << "tick,name,x,y,battery,mode\n";

    vector<bool> landedShown(fleet.size(), false);

    // Simulation loop
    for (int tick = 0; tick < 500; tick++) {

        bool allDone = true;

        for (size_t i = 0; i < fleet.size(); i++) {

            auto& v = fleet[i];

            if (landedShown[i])
                continue;

            v->step();

            bool justLanded = v->finished();

            if (tick % 5 == 0 || justLanded) {
                v->printStatus(tick);
            }

            v->logCsv(log, tick);

            if (justLanded) {
                landedShown[i] = true;
            } else {
                allDone = false;
            }
        }

        if (allDone) {
            cout << "All vehicles landed. "
                 << "Log saved to patrol_log.csv"
                 << endl;
            break;
        }
    }

    return 0;
}
