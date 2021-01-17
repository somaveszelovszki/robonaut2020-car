#include <micro/test/utils.hpp>

#include <LabyrinthGraph.hpp>
#include <LabyrinthRoute.hpp>
#include <track.hpp>

#include "route.hpp"

using namespace micro;

TEST(test_labyrinth, valid) {
    LabyrinthGraph graph = buildTestLabyrinthGraph();
    ASSERT_TRUE(graph.valid());
}

TEST(test_labyrinth, P_T) {
    LabyrinthGraph graph = buildTestLabyrinthGraph();

    const Segment& src         = *graph.findSegment('P');
    const Segment& dest        = *graph.findSegment('T');
    const Junction& prevJunc   = *graph.findJunction(1);
    const Connection& prevConn = **std::find_if(src.edges.begin(), src.edges.end(), [&prevJunc](const Connection *c) {
        return c->junction == &prevJunc;
    });

    checkRoute(prevConn, src, dest, {
        { graph.findJunction(2), JunctionDecision(radian_t(0), Direction::LEFT)   },
        { graph.findJunction(4), JunctionDecision(radian_t(0), Direction::CENTER) },
        { graph.findJunction(5), JunctionDecision(radian_t(0), Direction::CENTER) },
        { graph.findJunction(6), JunctionDecision(radian_t(0), Direction::LEFT)   },
        { graph.findJunction(7), JunctionDecision(radian_t(0), Direction::CENTER) }
    });
}

TEST(test_labyrinth, P_L) {
    LabyrinthGraph graph = buildTestLabyrinthGraph();

    const Segment& src         = *graph.findSegment('P');
    const Segment& dest        = *graph.findSegment('L');
    const Junction& prevJunc   = *graph.findJunction(2);
    const Connection& prevConn = **std::find_if(src.edges.begin(), src.edges.end(), [&prevJunc](const Connection *c) {
        return c->junction == &prevJunc;
    });

    checkRoute(prevConn, src, dest, {
        { graph.findJunction(1),  JunctionDecision(PI,          Direction::LEFT)   },
        { graph.findJunction(1),  JunctionDecision(radian_t(0), Direction::RIGHT)  },
        { graph.findJunction(2),  JunctionDecision(radian_t(0), Direction::LEFT)   },
        { graph.findJunction(4),  JunctionDecision(radian_t(0), Direction::CENTER) },
        { graph.findJunction(5),  JunctionDecision(radian_t(0), Direction::CENTER) },
        { graph.findJunction(6),  JunctionDecision(radian_t(0), Direction::CENTER) },
        { graph.findJunction(8),  JunctionDecision(radian_t(0), Direction::CENTER) },
        { graph.findJunction(10), JunctionDecision(radian_t(0), Direction::LEFT)   },
        { graph.findJunction(11), JunctionDecision(radian_t(0), Direction::RIGHT)  }
    });
}

TEST(test_labyrinth, M_O) {
    LabyrinthGraph graph = buildTestLabyrinthGraph();

    const Segment& src         = *graph.findSegment('M');
    const Segment& dest        = *graph.findSegment('O');
    const Junction& prevJunc   = *graph.findJunction(11);
    const Connection& prevConn = **std::find_if(src.edges.begin(), src.edges.end(), [&prevJunc](const Connection *c) {
        return c->junction == &prevJunc;
    });

    checkRoute(prevConn, src, dest, {
        { graph.findJunction(12), JunctionDecision(radian_t(0), Direction::CENTER) },
        { graph.findJunction(13), JunctionDecision(radian_t(0), Direction::RIGHT)  }
    });
}

TEST(test_labyrinth, O_W_no_route) {
    LabyrinthGraph graph = buildTestLabyrinthGraph();

    const Segment& src         = *graph.findSegment('O');
    const Segment& dest        = *graph.findSegment('W');
    const Junction& prevJunc   = *graph.findJunction(13);
    const Connection& prevConn = **std::find_if(src.edges.begin(), src.edges.end(), [&prevJunc](const Connection *c) {
        return c->junction == &prevJunc;
    });

    checkRoute(prevConn, src, dest, {});
}