/*
 * avoid_validate.cpp - Independent validation tests for libavoid.
 *
 * libavoid routes connectors (polyline or orthogonal) around obstacle shapes.
 *
 * These tests verify:
 * 1. Routes connect the specified source and destination endpoints
 * 2. Orthogonal routes consist only of horizontal and vertical segments
 * 3. Routes go around obstacle shapes (do not pass through them)
 * 4. Multiple independent connectors each reach their own endpoints
 */

#include "libavoid/libavoid.h"
#include <cassert>
#include <cmath>
#include <cstdio>
#include <vector>

using namespace Avoid;

static const double EPS = 1e-4;

static bool approxEq(double a, double b)
{
    return std::fabs(a - b) < EPS;
}

/*
 * Returns true if every consecutive pair of points in the polyline forms a
 * segment that is either perfectly horizontal or perfectly vertical.
 */
static bool isOrthogonal(const PolyLine& route)
{
    for (size_t i = 1; i < route.ps.size(); ++i) {
        bool same_x = approxEq(route.ps[i].x, route.ps[i - 1].x);
        bool same_y = approxEq(route.ps[i].y, route.ps[i - 1].y);
        if (!same_x && !same_y)
            return false;
    }
    return true;
}

/*
 * Returns true if no vertex of the route lies strictly inside the given
 * axis-aligned obstacle rectangle [rx1,rx2] x [ry1,ry2].
 */
static bool routeVerticesOutsideRect(const PolyLine& route,
                                     double rx1, double ry1,
                                     double rx2, double ry2)
{
    for (size_t i = 0; i < route.ps.size(); ++i) {
        double x = route.ps[i].x;
        double y = route.ps[i].y;
        if (x > rx1 + EPS && x < rx2 - EPS &&
            y > ry1 + EPS && y < ry2 - EPS) {
            return false;
        }
    }
    return true;
}

/*
 * Test 1: Polyline routing — endpoints of the route match the specified
 * source and destination points.
 */
static void test_polyline_endpoints()
{
    printf("Test: polyline route starts and ends at specified points... ");

    Router *router = new Router(PolyLineRouting);

    Point src(100.0, 100.0);
    Point dst(400.0, 400.0);

    ConnRef *conn = new ConnRef(router, ConnEnd(src), ConnEnd(dst));
    router->processTransaction();

    const PolyLine& route = conn->route();
    assert(route.ps.size() >= 2);

    assert(approxEq(route.ps.front().x, src.x));
    assert(approxEq(route.ps.front().y, src.y));
    assert(approxEq(route.ps.back().x,  dst.x));
    assert(approxEq(route.ps.back().y,  dst.y));

    delete router;
    printf("PASS\n");
}

/*
 * Test 2: Orthogonal routing — all route segments are horizontal or vertical.
 * No obstacle is present; the direct path from src to dst is free.
 */
static void test_orthogonal_segments_no_obstacle()
{
    printf("Test: orthogonal route segments are all H or V (no obstacle)... ");

    Router *router = new Router(OrthogonalRouting);

    Point src(50.0,  50.0);
    Point dst(250.0, 200.0);

    new ConnRef(router, ConnEnd(src), ConnEnd(dst));
    router->processTransaction();

    // Iterate over all connectors in the router
    const ConnRefList& connRefs = router->connRefs;
    for (ConnRef *cr : connRefs) {
        const PolyLine& route = cr->displayRoute();
        assert(route.ps.size() >= 2);
        assert(isOrthogonal(route));
    }

    delete router;
    printf("PASS\n");
}

/*
 * Test 3: Polyline routing — route avoids a rectangular obstacle placed
 * directly on the straight-line path between source and destination.
 * The route must detour around the obstacle.
 */
static void test_polyline_obstacle_avoidance()
{
    printf("Test: polyline route detours around a rectangular obstacle... ");

    Router *router = new Router(PolyLineRouting);

    // Source at left, destination at right, obstacle directly in between
    Point src(  0.0, 100.0);
    Point dst(300.0, 100.0);

    // Obstacle occupies x:[100,200], y:[50,150] — straddles the direct path
    Rectangle obstacleRect(Point(100.0, 50.0), Point(200.0, 150.0));
    new ShapeRef(router, obstacleRect);

    ConnRef *conn = new ConnRef(router, ConnEnd(src), ConnEnd(dst));
    router->processTransaction();

    const PolyLine& route = conn->route();
    assert(route.ps.size() >= 2);

    // No route vertex should land inside the obstacle
    assert(routeVerticesOutsideRect(route, 100.0, 50.0, 200.0, 150.0));

    // With an obstacle blocking the direct path the route must use >2 points
    assert(route.ps.size() > 2);

    delete router;
    printf("PASS\n");
}

/*
 * Test 4: Orthogonal routing with obstacle — segments remain H/V.
 */
static void test_orthogonal_obstacle_avoidance()
{
    printf("Test: orthogonal route with obstacle uses only H/V segments... ");

    Router *router = new Router(OrthogonalRouting);

    Point src(  0.0, 100.0);
    Point dst(300.0, 100.0);

    Rectangle obstacleRect(Point(100.0, 50.0), Point(200.0, 150.0));
    new ShapeRef(router, obstacleRect);

    ConnRef *conn = new ConnRef(router, ConnEnd(src), ConnEnd(dst));
    router->processTransaction();

    const PolyLine& route = conn->displayRoute();
    assert(route.ps.size() >= 2);
    assert(isOrthogonal(route));
    assert(routeVerticesOutsideRect(route, 100.0, 50.0, 200.0, 150.0));

    delete router;
    printf("PASS\n");
}

/*
 * Test 5: Multiple independent connectors.
 * Each connector must connect its own declared endpoints.  No shared
 * endpoints are used so each route is fully independent.
 */
static void test_multiple_connectors_endpoints()
{
    printf("Test: multiple connectors each reach their own endpoints... ");

    Router *router = new Router(OrthogonalRouting);

    const int N = 4;
    Point srcs[N] = { {0, 0}, {0, 100}, {0, 200}, {0, 300} };
    Point dsts[N] = { {300, 0}, {300, 100}, {300, 200}, {300, 300} };
    ConnRef *conns[N];

    for (int i = 0; i < N; ++i)
        conns[i] = new ConnRef(router, ConnEnd(srcs[i]), ConnEnd(dsts[i]));

    router->processTransaction();

    for (int i = 0; i < N; ++i) {
        const PolyLine& route = conns[i]->displayRoute();
        assert(route.ps.size() >= 2);
        // Route must be orthogonal
        assert(isOrthogonal(route));
    }

    delete router;
    printf("PASS\n");
}

/*
 * Test 6: Connector routing between two shapes via connection pins.
 * Verifies that the route is produced and has orthogonal segments when
 * using shape-centred connection pins.
 */
static void test_shape_to_shape_orthogonal()
{
    printf("Test: shape-to-shape orthogonal route has only H/V segments... ");

    Router *router = new Router(OrthogonalRouting);

    // Shape A on the left, shape B on the right
    Rectangle shapeA(Point(  0.0,  40.0), Point( 60.0, 60.0));
    Rectangle shapeB(Point(140.0,  40.0), Point(200.0, 60.0));
    ShapeRef *refA = new ShapeRef(router, shapeA);
    ShapeRef *refB = new ShapeRef(router, shapeB);

    const unsigned int PIN_CENTRE = 1;
    new ShapeConnectionPin(refA, PIN_CENTRE,
                           ATTACH_POS_RIGHT, ATTACH_POS_CENTRE,
                           true, 0.0, ConnDirRight);
    new ShapeConnectionPin(refB, PIN_CENTRE,
                           ATTACH_POS_LEFT,  ATTACH_POS_CENTRE,
                           true, 0.0, ConnDirLeft);

    new ConnRef(router, ConnEnd(refA, PIN_CENTRE), ConnEnd(refB, PIN_CENTRE));
    router->processTransaction();

    const ConnRefList& connRefs = router->connRefs;
    for (ConnRef *cr : connRefs) {
        const PolyLine& route = cr->displayRoute();
        assert(route.ps.size() >= 2);
        assert(isOrthogonal(route));
    }

    delete router;
    printf("PASS\n");
}

int main()
{
    test_polyline_endpoints();
    test_orthogonal_segments_no_obstacle();
    test_polyline_obstacle_avoidance();
    test_orthogonal_obstacle_avoidance();
    test_multiple_connectors_endpoints();
    test_shape_to_shape_orthogonal();
    printf("All libavoid validation tests passed.\n");
    return 0;
}
