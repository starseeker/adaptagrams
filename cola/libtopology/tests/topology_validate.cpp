/*
 * topology_validate.cpp - Independent validation tests for libtopology.
 *
 * libtopology builds topology constraints that preserve non-overlap when
 * nodes are repositioned during layout.  It extends the VPSC solver with
 * constraints derived from the current arrangement of rectangles so that
 * any movement along the solve direction cannot introduce new overlaps.
 *
 * These tests verify:
 * 1. removeoverlaps() produces a configuration with no pairwise overlaps
 * 2. TopologyConstraints preserve non-overlap when desired positions change
 * 3. The same property holds across both axis dimensions
 */

#include <libvpsc/rectangle.h>
#include <libvpsc/variable.h>
#include <libvpsc/constraint.h>
#include <libtopology/topology_constraints.h>
#include <cassert>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <functional>

using namespace vpsc;
using namespace topology;

// ---------------------------------------------------------------------------
// Helpers

static bool anyOverlapX(const Rectangles& rs)
{
    for (size_t i = 0; i < rs.size(); ++i)
        for (size_t j = i + 1; j < rs.size(); ++j)
            if (rs[i]->overlapX(rs[j]) > 0 && rs[i]->overlapY(rs[j]) > 0)
                return true;
    return false;
}

// Build a topology::Node for each rectangle, allocating one vpsc::Variable
// per node and collecting all variables into vs.
static void buildNodes(const Rectangles& rs, Nodes& nodes, Variables& vs)
{
    for (size_t i = 0; i < rs.size(); ++i) {
        Variable *v = new Variable(static_cast<int>(i),
                                   rs[i]->getCentreX(), 1.0);
        nodes.push_back(new topology::Node(static_cast<unsigned>(i),
                                           rs[i], v));
        vs.push_back(v);
    }
}

// Move all variables to desired positions that are random small perturbations
// from the current centre positions (but staying within [0, maxCoord]).
static void perturbDesiredPositions(const Nodes& nodes,
                                    double maxCoord, unsigned seed)
{
    srand(seed);
    for (Node *n : nodes) {
        double delta = (static_cast<double>(rand()) / RAND_MAX - 0.5) * 10.0;
        double newPos = n->rect->getCentreX() + delta;
        if (newPos < 0) newPos = 0;
        if (newPos > maxCoord) newPos = maxCoord;
        n->var->desiredPosition = newPos;
    }
}

// ---------------------------------------------------------------------------

/*
 * Test 1: removeoverlaps() eliminates all pairwise overlaps.
 *
 * Place several rectangles so that they obviously overlap, then call the
 * libvpsc overlap-removal routine and verify no overlaps remain.
 */
static void test_removeoverlaps_eliminates_overlaps()
{
    printf("Test: removeoverlaps() eliminates all pairwise overlaps... ");

    Rectangles rs;
    // All rectangles placed at nearly the same location — all overlap
    rs.push_back(new Rectangle( 0, 30,  0, 30));
    rs.push_back(new Rectangle( 5, 35,  5, 35));
    rs.push_back(new Rectangle(10, 40, 10, 40));
    rs.push_back(new Rectangle(15, 45, 15, 45));

    // Verify they really do overlap at the start
    assert(anyOverlapX(rs));

    removeoverlaps(rs);

    // After removal there should be no overlaps
    assert(!anyOverlapX(rs));

    for (Rectangle *r : rs) delete r;
    printf("PASS\n");
}

/*
 * Test 2: TopologyConstraints in the X dimension preserve non-overlap when
 * desired positions are perturbed.
 *
 * Start with a non-overlapping configuration, build X-dimension topology
 * constraints, perturb the desired positions, solve, and confirm that no
 * overlaps have been introduced.
 */
static void test_topology_preserves_nonoverlap_xdim()
{
    printf("Test: TopologyConstraints (XDIM) preserve non-overlap... ");

    Rectangles rs;
    // Non-overlapping rectangles arranged in a row
    rs.push_back(new Rectangle(  0,  40,  0, 40));
    rs.push_back(new Rectangle( 60, 100,  0, 40));
    rs.push_back(new Rectangle(120, 160,  0, 40));
    rs.push_back(new Rectangle(180, 220, 10, 50));
    rs.push_back(new Rectangle(240, 280,  0, 40));

    Nodes nodes;
    Edges edges;  // no edges for this topology test
    Variables vs;
    buildNodes(rs, nodes, vs);

    try {
        Constraints cs;
        TopologyConstraints t(XDIM, nodes, edges, nullptr, vs, cs);
        perturbDesiredPositions(nodes, 300.0, 42);
        t.solve();

        // No overlaps must remain
        assert(!anyOverlapX(rs));

        for (Constraint *c : cs) delete c;
    } catch (const char *e) {
        fprintf(stderr, "Exception in test: %s\n", e);
        assert(false);
    }

    for (Node *n : nodes) delete n;
    for (Variable *v : vs) delete v;
    for (Rectangle *r : rs) delete r;
    printf("PASS\n");
}

/*
 * Test 3: TopologyConstraints in the Y dimension preserve non-overlap.
 *
 * Same as Test 2 but operating in the Y dimension.
 */
static void test_topology_preserves_nonoverlap_ydim()
{
    printf("Test: TopologyConstraints (YDIM) preserve non-overlap... ");

    Rectangles rs;
    // Non-overlapping rectangles arranged in a column
    rs.push_back(new Rectangle( 0, 40,   0,  40));
    rs.push_back(new Rectangle( 0, 40,  60, 100));
    rs.push_back(new Rectangle( 0, 40, 120, 160));
    rs.push_back(new Rectangle( 0, 40, 180, 220));

    // For YDIM constraints, variable positions represent Y coordinates
    Nodes nodes;
    Edges edges;
    Variables vs;
    for (size_t i = 0; i < rs.size(); ++i) {
        Variable *v = new Variable(static_cast<int>(i),
                                   rs[i]->getCentreY(), 1.0);
        nodes.push_back(new topology::Node(static_cast<unsigned>(i),
                                           rs[i], v));
        vs.push_back(v);
    }

    try {
        Constraints cs;
        TopologyConstraints t(YDIM, nodes, edges, nullptr, vs, cs);

        // Perturb desired Y positions
        srand(99);
        for (Node *n : nodes) {
            double delta = (static_cast<double>(rand()) / RAND_MAX - 0.5) * 10.0;
            n->var->desiredPosition = n->rect->getCentreY() + delta;
        }
        t.solve();

        assert(!anyOverlapX(rs));

        for (Constraint *c : cs) delete c;
    } catch (const char *e) {
        fprintf(stderr, "Exception in test: %s\n", e);
        assert(false);
    }

    for (Node *n : nodes) delete n;
    for (Variable *v : vs) delete v;
    for (Rectangle *r : rs) delete r;
    printf("PASS\n");
}

/*
 * Test 4: Non-overlap after multiple perturbations.
 *
 * Repeatedly perturb and resolve to confirm that the constraint solver
 * continues to maintain non-overlap across several iterations.
 */
static void test_topology_repeated_perturbations()
{
    printf("Test: non-overlap maintained across repeated perturbations... ");

    Rectangles rs;
    rs.push_back(new Rectangle(  0,  30,  0, 30));
    rs.push_back(new Rectangle( 50,  80,  0, 30));
    rs.push_back(new Rectangle(100, 130,  0, 30));

    Nodes nodes;
    Edges edges;
    Variables vs;
    buildNodes(rs, nodes, vs);

    try {
        for (unsigned iter = 0; iter < 5; ++iter) {
            Constraints cs;
            TopologyConstraints t(XDIM, nodes, edges, nullptr, vs, cs);
            perturbDesiredPositions(nodes, 200.0, iter + 1);
            t.solve();
            assert(!anyOverlapX(rs));
            for (Constraint *c : cs) delete c;
        }
    } catch (const char *e) {
        fprintf(stderr, "Exception in test: %s\n", e);
        assert(false);
    }

    for (Node *n : nodes) delete n;
    for (Variable *v : vs) delete v;
    for (Rectangle *r : rs) delete r;
    printf("PASS\n");
}

int main()
{
    test_removeoverlaps_eliminates_overlaps();
    test_topology_preserves_nonoverlap_xdim();
    test_topology_preserves_nonoverlap_ydim();
    test_topology_repeated_perturbations();
    printf("All libtopology validation tests passed.\n");
    return 0;
}
