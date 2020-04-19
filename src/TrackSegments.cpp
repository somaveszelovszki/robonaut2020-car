#include <globals.hpp>
#include <TrackSegments.hpp>
#include <TrackSpeeds.hpp>

using namespace micro;

namespace {

const TrackSpeeds& getSpeeds(uint8_t lap) {
    return globals::trackSpeeds[lap - 1];
}

bool hasBecomeActive_Fast(const TrackInfo& trackInfo, const LinePattern& pattern) {
    static bool signDetected = false;
    static meter_t lastSignDist = meter_t(0);

    bool active = false;
    if (LinePattern::ACCELERATE == pattern.type) {
        signDetected = true;
        lastSignDist = globals::car.distance;
    } else if (globals::car.distance - lastSignDist > meter_t(5)) {
        signDetected = false;
    }

    if (signDetected && globals::car.orientedDistance > centimeter_t(25)) {
        signDetected = false;
        active = true;
    }
    return active;
}

bool hasBecomeActive_Slow1_prepare(const TrackInfo& trackInfo, const LinePattern& pattern) {
    return LinePattern::BRAKE == pattern.type;
}

bool hasBecomeActive_Slow1_round(const TrackInfo& trackInfo, const LinePattern& pattern) {
    return globals::car.distance - trackInfo.segStartCarProps.distance > meter_t(3);
}

bool hasBecomeActive_Slow2_prepare(const TrackInfo& trackInfo, const LinePattern& pattern) {
    return LinePattern::BRAKE == pattern.type;
}

bool hasBecomeActive_Slow2_begin(const TrackInfo& trackInfo, const LinePattern& pattern) {
    return globals::car.distance - trackInfo.segStartCarProps.distance > meter_t(3);
}

bool hasBecomeActive_Slow2_round(const TrackInfo& trackInfo, const LinePattern& pattern) {
    return globals::car.distance - trackInfo.segStartCarProps.distance > centimeter_t(120);
}

bool hasBecomeActive_Slow3_prepare(const TrackInfo& trackInfo, const LinePattern& pattern) {
    return LinePattern::BRAKE == pattern.type;
}

bool hasBecomeActive_Slow3_round(const TrackInfo& trackInfo, const LinePattern& pattern) {
    return LinePattern::BRAKE == pattern.type;
}

bool hasBecomeActive_Slow3_end(const TrackInfo& trackInfo, const LinePattern& pattern) {
    return globals::car.distance - trackInfo.segStartCarProps.distance > meter_t(1) * PI.get();
}

bool hasBecomeActive_Slow4_prepare(const TrackInfo& trackInfo, const LinePattern& pattern) {
    return LinePattern::BRAKE == pattern.type;
}

bool hasBecomeActive_Slow4_round(const TrackInfo& trackInfo, const LinePattern& pattern) {
    return globals::car.distance - trackInfo.segStartCarProps.distance > meter_t(3);
}

ControlData getControl_CommonFast(const TrackInfo& trackInfo, const MainLine& mainLine) {
    static bool fastSpeedEnabled = true;

    if (fastSpeedEnabled && abs(mainLine.centerLine.pos) > centimeter_t(12)) {
        fastSpeedEnabled = false;
    } else if (!fastSpeedEnabled && globals::car.orientedDistance > centimeter_t(50)) {
        fastSpeedEnabled = true;
    }

    ControlData controlData;
    controlData.speed                = fastSpeedEnabled ? getSpeeds(trackInfo.lap).fast : m_per_sec_t(2.0f);
    controlData.rampTime             = millisecond_t(500);
    controlData.controlType          = ControlData::controlType_t::Line;
    controlData.lineControl.baseline = mainLine.centerLine;
    controlData.lineControl.offset   = millimeter_t(0);
    controlData.lineControl.angle    = radian_t(0);
    return controlData;
}

ControlData getControl_CommonSlow(const TrackInfo& trackInfo, const MainLine& mainLine) {
    ControlData controlData;
    controlData.rampTime             = millisecond_t(500);
    controlData.controlType          = ControlData::controlType_t::Line;
    controlData.lineControl.baseline = mainLine.centerLine;
    controlData.lineControl.offset   = millimeter_t(0);
    controlData.lineControl.angle    = radian_t(0);
    return controlData;
}

ControlData getControl_Fast1(const TrackInfo& trackInfo, const LinePattern&, const MainLine& mainLine) {
    ControlData controlData = getControl_CommonFast(trackInfo, mainLine);

    return controlData;
}

ControlData getControl_Slow1_prepare(const TrackInfo& trackInfo, const LinePattern& pattern, const MainLine& mainLine) {
    ControlData controlData = getControl_CommonSlow(trackInfo, mainLine);

    controlData.speed = getSpeeds(trackInfo.lap).slow1_prepare;

    return controlData;
}

ControlData getControl_Slow1_round(const TrackInfo& trackInfo, const LinePattern& pattern, const MainLine& mainLine) {
    ControlData controlData = getControl_CommonSlow(trackInfo, mainLine);

    controlData.speed = getSpeeds(trackInfo.lap).slow1_round;

    return controlData;
}

ControlData getControl_Fast2(const TrackInfo& trackInfo, const LinePattern&, const MainLine& mainLine) {
    ControlData controlData = getControl_CommonFast(trackInfo, mainLine);

    return controlData;
}

ControlData getControl_Slow2_prepare(const TrackInfo& trackInfo, const LinePattern& pattern, const MainLine& mainLine) {
    ControlData controlData   = getControl_CommonSlow(trackInfo, mainLine);

    controlData.speed = getSpeeds(trackInfo.lap).slow2_begin;

    return controlData;
}


ControlData getControl_Slow2_begin(const TrackInfo& trackInfo, const LinePattern& pattern, const MainLine& mainLine) {
    ControlData controlData   = getControl_CommonSlow(trackInfo, mainLine);

    controlData.speed = getSpeeds(trackInfo.lap).slow2_begin;

    return controlData;
}

ControlData getControl_Slow2_round(const TrackInfo& trackInfo, const LinePattern& pattern, const MainLine& mainLine) {
    ControlData controlData   = getControl_CommonSlow(trackInfo, mainLine);

    controlData.speed = getSpeeds(trackInfo.lap).slow2_round;

    return controlData;
}

ControlData getControl_Fast3(const TrackInfo& trackInfo, const LinePattern&, const MainLine& mainLine) {
    ControlData controlData = getControl_CommonFast(trackInfo, mainLine);

    return controlData;
}

ControlData getControl_Slow3_prepare(const TrackInfo& trackInfo, const LinePattern& pattern, const MainLine& mainLine) {
    ControlData controlData   = getControl_CommonSlow(trackInfo, mainLine);

    controlData.speed = getSpeeds(trackInfo.lap).slow3_round;

    return controlData;
}

ControlData getControl_Slow3_round(const TrackInfo& trackInfo, const LinePattern& pattern, const MainLine& mainLine) {
    ControlData controlData   = getControl_CommonSlow(trackInfo, mainLine);

    controlData.speed = getSpeeds(trackInfo.lap).slow3_round;

    return controlData;
}

ControlData getControl_Slow3_end(const TrackInfo& trackInfo, const LinePattern& pattern, const MainLine& mainLine) {
    ControlData controlData   = getControl_CommonSlow(trackInfo, mainLine);

    controlData.speed = getSpeeds(trackInfo.lap).slow3_end;

    return controlData;
}

ControlData getControl_Fast4(const TrackInfo& trackInfo, const LinePattern&, const MainLine& mainLine) {
    ControlData controlData = getControl_CommonFast(trackInfo, mainLine);

    return controlData;
}

ControlData getControl_Slow4_prepare(const TrackInfo& trackInfo, const LinePattern& pattern, const MainLine& mainLine) {
    ControlData controlData = getControl_CommonSlow(trackInfo, mainLine);

    controlData.speed = getSpeeds(trackInfo.lap).slow4_prepare;

    return controlData;
}

ControlData getControl_Slow4_round(const TrackInfo& trackInfo, const LinePattern& pattern, const MainLine& mainLine) {
    ControlData controlData = getControl_CommonSlow(trackInfo, mainLine);

    controlData.speed = getSpeeds(trackInfo.lap).slow4_round;

    return controlData;
}

} // namespace

const TrackSegments trackSegments = {
    { true,  hasBecomeActive_Fast,          getControl_Fast1         },
    { false, hasBecomeActive_Slow1_prepare, getControl_Slow1_prepare },
    { false, hasBecomeActive_Slow1_round,   getControl_Slow1_round   },
    { true,  hasBecomeActive_Fast,          getControl_Fast2         },
    { false, hasBecomeActive_Slow2_prepare, getControl_Slow2_prepare },
    { false, hasBecomeActive_Slow2_begin,   getControl_Slow2_begin   },
    { false, hasBecomeActive_Slow2_round,   getControl_Slow2_round   },
    { true,  hasBecomeActive_Fast,          getControl_Fast3         },
    { false, hasBecomeActive_Slow3_prepare, getControl_Slow3_prepare },
    { false, hasBecomeActive_Slow3_round,   getControl_Slow3_round   },
    { false, hasBecomeActive_Slow3_end,     getControl_Slow3_end     },
    { true,  hasBecomeActive_Fast,          getControl_Fast4         },
    { false, hasBecomeActive_Slow4_prepare, getControl_Slow4_prepare },
    { false, hasBecomeActive_Slow4_round,   getControl_Slow4_round   }
};
