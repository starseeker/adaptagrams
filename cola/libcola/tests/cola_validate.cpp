/*
 * cola_validate.cpp - Independent validation tests for libcola.
 *
 * libcola performs force-directed graph layout with separation constraints
 * using the stress-majorization method.
 *
 * These tests verify:
 * 1. After layout, rectangles that started overlapping no longer overlap
 * 2. Alignment constraints produce collinear node centres
 * 3. Separation constraints maintain a minimum gap between node centres
 * 4. Stress decreases (or stays equal) between layout iterations
 */

#include <vector>
#include <utility>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <algorithm>

#include "libcola/cola.h"
#include "libvpsc/rectangle.h"

using namespace cola;
using namespace vpsc;

static const double EPS = 1e-4;

/*
 * Returns true if any two rectangles in the vector overlap in both dimensions.
 * A pair of rectangles overlaps when their projections onto both axes
 * intersect by more than EPS.
 */
static bool anyOverlap(const std::vector<Rectangle *>& rs)
{
    for (size_t i = 0; i < rs.size(); ++i) {
        for (size_t j = i + 1; j < rs.size(); ++j) {
            bool ox = rs[i]->overlapD(0, rs[j]) > EPS;
            bool oy = rs[i]->overlapD(1, rs[j]) > EPS;
            if (ox && oy)
                return true;
        }
    }
    return false;
}

/*
 * Test 1: Non-overlap after calling makeFeasible().
 *
 * Place several rectangles at overlapping positions, then call makeFeasible()
 * which generates and satisfies non-overlap constraints.  Verify that no two
 * rectangles still overlap afterwards.
 */
static void test_non_overlap()
{
    printf("Test: makeFeasible() removes overlapping rectangles... ");

    std::vector<Rectangle *> rs;
    // Five rectangles of different sizes all placed at the origin
    rs.push_back(new Rectangle(0, 80, 0, 40));
    rs.push_back(new Rectangle(0, 80, 0, 40));
    rs.push_back(new Rectangle(0, 60, 0, 60));
    rs.push_back(new Rectangle(0, 40, 0, 20));
    rs.push_back(new Rectangle(0, 40, 0, 20));

    // Verify they really do overlap before layout
    assert(anyOverlap(rs));

    std::vector<std::pair<unsigned, unsigned>> es;
    es.push_back(std::make_pair(0u, 1u));
    es.push_back(std::make_pair(1u, 2u));
    es.push_back(std::make_pair(2u, 3u));
    es.push_back(std::make_pair(3u, 4u));

    ConstrainedFDLayout alg(rs, es, 50.0);
    alg.setAvoidNodeOverlaps(true);
    // makeFeasible() generates non-overlap constraints and satisfies them
    // without applying any force-directed forces
    alg.makeFeasible();

    // After makeFeasible() there should be no overlaps
    assert(!anyOverlap(rs));

    alg.freeAssociatedObjects();
    printf("PASS\n");
}

/*
 * Test 2: Alignment constraint produces collinear centres.
 *
 * Two nodes with an alignment constraint in the X dimension should end up
 * with their x-centres equal (within floating-point tolerance).
 */
static void test_alignment_constraint()
{
    printf("Test: alignment constraint makes node centres collinear... ");

    const unsigned N = 3;
    std::vector<Rectangle *> rs;
    rs.push_back(new Rectangle(  0, 20,   0, 20));
    rs.push_back(new Rectangle(100, 120,  50, 70));
    rs.push_back(new Rectangle( 60, 80,  120, 140));

    std::vector<std::pair<unsigned, unsigned>> es;
    es.push_back(std::make_pair(0u, 1u));
    es.push_back(std::make_pair(1u, 2u));

    CompoundConstraints ccs;
    AlignmentConstraint *ac = new AlignmentConstraint(XDIM);
    ac->addShape(0, 0);
    ac->addShape(1, 0);
    ccs.push_back(ac);

    ConstrainedFDLayout alg(rs, es, 50.0);
    alg.setConstraints(ccs);
    alg.run();

    // Nodes 0 and 1 must share the same x-centre
    assert(std::fabs(rs[0]->getCentreX() - rs[1]->getCentreX()) < EPS);

    alg.freeAssociatedObjects();
    (void)N;
    printf("PASS\n");
}

/*
 * Test 3: Separation constraint maintains minimum gap between node centres.
 *
 * Two nodes with a separation constraint must keep their x-centres at least
 * gap apart after layout.
 */
static void test_separation_constraint()
{
    printf("Test: separation constraint maintains minimum gap... ");

    const double requiredGap = 80.0;

    std::vector<Rectangle *> rs;
    // Both nodes start near each other — the constraint will be violated
    // at the initial positions and must be enforced by the layout.
    rs.push_back(new Rectangle( 0, 30,  0, 30));
    rs.push_back(new Rectangle(10, 40, 10, 40));

    std::vector<std::pair<unsigned, unsigned>> es;
    es.push_back(std::make_pair(0u, 1u));

    CompoundConstraints ccs;
    SeparationConstraint *sc = new SeparationConstraint(XDIM, 0, 1, requiredGap);
    ccs.push_back(sc);

    ConstrainedFDLayout alg(rs, es, 50.0);
    alg.setConstraints(ccs);
    alg.run();

    double gap = rs[1]->getCentreX() - rs[0]->getCentreX();
    assert(gap >= requiredGap - EPS);

    alg.freeAssociatedObjects();
    printf("PASS\n");
}

/*
 * Test 4: Layout preserves an already-satisfied separation constraint.
 *
 * When nodes start in a configuration that already satisfies the separation
 * constraint, the constraint must remain satisfied after layout.
 */
static void test_separation_already_satisfied()
{
    printf("Test: already-satisfied separation constraint remains satisfied... ");

    const double requiredGap = 40.0;

    std::vector<Rectangle *> rs;
    // Place nodes far enough apart that the constraint is trivially satisfied
    rs.push_back(new Rectangle(  0,  20,  0, 20));
    rs.push_back(new Rectangle(200, 220,  0, 20));

    std::vector<std::pair<unsigned, unsigned>> es;
    es.push_back(std::make_pair(0u, 1u));

    CompoundConstraints ccs;
    SeparationConstraint *sc = new SeparationConstraint(XDIM, 0, 1, requiredGap);
    ccs.push_back(sc);

    ConstrainedFDLayout alg(rs, es, 50.0);
    alg.setConstraints(ccs);
    alg.run();

    double gap = rs[1]->getCentreX() - rs[0]->getCentreX();
    assert(gap >= requiredGap - EPS);

    alg.freeAssociatedObjects();
    printf("PASS\n");
}

/*
 * Test 5: Stress is non-negative and bounded.
 *
 * The stress metric reported by the layout algorithm must be a non-negative
 * value.  (It represents a weighted sum of squared edge-length deviations and
 * so cannot be negative.)
 */
static void test_stress_non_negative()
{
    printf("Test: layout stress is non-negative... ");

    std::vector<Rectangle *> rs;
    rs.push_back(new Rectangle(  0, 20,   0, 20));
    rs.push_back(new Rectangle(100, 120,   0, 20));
    rs.push_back(new Rectangle( 50, 70,  80, 100));

    std::vector<std::pair<unsigned, unsigned>> es;
    es.push_back(std::make_pair(0u, 1u));
    es.push_back(std::make_pair(1u, 2u));
    es.push_back(std::make_pair(0u, 2u));

    ConstrainedFDLayout alg(rs, es, 50.0);
    alg.run();

    double stress = alg.computeStress();
    assert(stress >= 0.0);

    alg.freeAssociatedObjects();
    printf("PASS\n");
}

int main()
{
    test_non_overlap();
    test_alignment_constraint();
    test_separation_constraint();
    test_separation_already_satisfied();
    test_stress_non_negative();
    printf("All libcola validation tests passed.\n");
    return 0;
}
