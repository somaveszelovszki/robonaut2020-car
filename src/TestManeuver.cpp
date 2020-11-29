#include <micro/math/numeric.hpp>
#include <TestManeuver.hpp>

using namespace micro;

TestManeuver::TestManeuver()
    : Maneuver() {}

void TestManeuver::initialize(const CarProps& car) {
    Maneuver::initialize();
    this->trajectory_.clear();
}

void TestManeuver::update(const CarProps& car, const LineInfo& lineInfo, MainLine& mainLine, ControlData& controlData) {

    if (this->trajectory_.length() == meter_t(0)) {
        this->buildTrajectory(car);
    }

    controlData = this->trajectory_.update(car);

    if (this->trajectory_.finished(car, lineInfo)) {
        this->finish();
    }
}

void TestManeuver::buildTrajectory(const micro::CarProps& car) {

    const m_per_sec_t speed = m_per_sec_t(1);

    const radian_t forwardAngle = speed >= m_per_sec_t(0) ? car.pose.angle : car.pose.angle + PI;

    this->trajectory_.setStartConfig(Trajectory::config_t{
        Pose{ car.pose.pos, forwardAngle },
        speed
    }, car.distance);

    this->trajectory_.appendSineArc(Trajectory::config_t{
        Pose{
            this->trajectory_.lastConfig().pose.pos + vec2m{ centimeter_t(75), centimeter_t(30) }.rotate(forwardAngle),
            forwardAngle
        },
        speed
    }, car.pose.angle, Trajectory::orientationUpdate_t::PATH_ORIENTATION, radian_t(0), PI);

    this->trajectory_.appendLine(Trajectory::config_t{
        Pose{
            this->trajectory_.lastConfig().pose.pos + vec2m{ centimeter_t(30), centimeter_t(0) }.rotate(forwardAngle),
            forwardAngle
        },
        speed
    });

    this->trajectory_.appendSineArc(Trajectory::config_t{
        Pose{
            this->trajectory_.lastConfig().pose.pos + vec2m{ centimeter_t(75), -centimeter_t(30) }.rotate(forwardAngle),
            forwardAngle
        },
        speed
    }, car.pose.angle, Trajectory::orientationUpdate_t::PATH_ORIENTATION, radian_t(0), PI_2);

    this->trajectory_.appendLine(Trajectory::config_t{
        Pose{
            this->trajectory_.lastConfig().pose.pos + vec2m{ centimeter_t(100), centimeter_t(0) }.rotate(forwardAngle),
            forwardAngle
        },
        speed
    });
}