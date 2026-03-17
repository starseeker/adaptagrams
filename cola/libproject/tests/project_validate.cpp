/*
 * project_validate.cpp - Independent validation tests for libproject.
 *
 * libproject solves the projection problem:
 *   Find x that minimises sum_i w_i * (x_i - d_i)^2
 *   subject to: x_r - x_l >= g  for all constraints
 *   starting from feasible initial positions x_i = p_i.
 *
 * These tests verify:
 * 1. Unconstrained projection: every variable reaches its desired position
 * 2. Active constraint: analytically computed expected final positions
 * 3. Constraint satisfaction: all constraints hold after every solve
 * 4. Already-feasible configuration is not perturbed unnecessarily
 * 5. Weighted variables: heavier variables displace less
 */

#include <libproject/project.h>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace project;

static const double EPS = 1e-5;

static bool approxEq(double a, double b)
{
    return std::fabs(a - b) < EPS;
}

// Verify all constraints are satisfied: x_r - x_l >= g
static void checkConstraintsSatisfied(const Variables& vars,
                                      const Constraints& cs)
{
    for (const Constraint *c : cs) {
        double diff = c->r->getPosition() - c->l->getPosition();
        assert(diff >= c->g - EPS);
    }
    (void)vars;
}

/*
 * Test 1: Unconstrained projection.
 *
 * With no constraints and initial positions equal to desired positions, the
 * solver must leave every variable unchanged.
 */
static void test_unconstrained_at_desired()
{
    printf("Test: unconstrained variables remain at desired positions... ");

    Variables vars;
    vars.push_back(new Variable(Initial(1.0), Desired(1.0)));
    vars.push_back(new Variable(Initial(5.0), Desired(5.0)));
    vars.push_back(new Variable(Initial(9.0), Desired(9.0)));

    Constraints cs;
    Project proj(vars, cs);
    proj.solve();

    assert(approxEq(vars[0]->getPosition(), 1.0));
    assert(approxEq(vars[1]->getPosition(), 5.0));
    assert(approxEq(vars[2]->getPosition(), 9.0));

    for_each(vars.begin(), vars.end(), delete_object());
    for_each(cs.begin(),   cs.end(),   delete_object());
    printf("PASS\n");
}

/*
 * Test 2: Two variables with one active constraint.
 *
 * Initial positions satisfy the constraint (feasibility is maintained).
 * Desired positions violate it, so the solver must enforce the constraint.
 *
 *   initial:  x_0 = 0,  x_1 = 6
 *   desired:  x_0 = 3,  x_1 = 4   (d_1 - d_0 = 1 < required gap = 4)
 *   weights:  w_0 = w_1 = 1
 *
 * Optimal at constraint boundary (x_1 = x_0 + 4):
 *   minimise (x_0-3)^2 + (x_0+4-4)^2 = (x_0-3)^2 + x_0^2
 *   d/dx_0: 2(x_0-3) + 2 x_0 = 0  =>  x_0 = 1.5, x_1 = 5.5
 */
static void test_active_constraint()
{
    printf("Test: active constraint gives analytically correct positions... ");

    Variables vars;
    vars.push_back(new Variable(Initial(0.0), Desired(3.0)));
    vars.push_back(new Variable(Initial(6.0), Desired(4.0)));

    Constraints cs;
    cs.push_back(new Constraint(vars[0], vars[1], 4.0));

    Project proj(vars, cs);
    proj.solve();

    checkConstraintsSatisfied(vars, cs);
    assert(approxEq(vars[0]->getPosition(), 1.5));
    assert(approxEq(vars[1]->getPosition(), 5.5));

    for_each(vars.begin(), vars.end(), delete_object());
    for_each(cs.begin(),   cs.end(),   delete_object());
    printf("PASS\n");
}

/*
 * Test 3: Constraint satisfaction property.
 *
 * For a problem where several constraints are potentially violated by the
 * desired positions, all constraints must hold after solving.
 */
static void test_all_constraints_satisfied()
{
    printf("Test: all constraints satisfied for multi-variable problem... ");

    // Initial positions are feasible (monotone increasing by > 2)
    // Desired positions all equal 0 — several constraints will be violated
    Variables vars;
    vars.push_back(new Variable(Initial(0.0),  Desired(0.0)));
    vars.push_back(new Variable(Initial(3.0),  Desired(0.0)));
    vars.push_back(new Variable(Initial(6.0),  Desired(0.0)));
    vars.push_back(new Variable(Initial(9.0),  Desired(0.0)));
    vars.push_back(new Variable(Initial(12.0), Desired(0.0)));

    Constraints cs;
    for (size_t i = 0; i < vars.size() - 1; ++i)
        cs.push_back(new Constraint(vars[i], vars[i + 1], 2.0));

    Project proj(vars, cs);
    proj.solve();

    checkConstraintsSatisfied(vars, cs);

    for_each(vars.begin(), vars.end(), delete_object());
    for_each(cs.begin(),   cs.end(),   delete_object());
    printf("PASS\n");
}

/*
 * Test 4: Already-feasible configuration.
 *
 * When the desired positions already satisfy all constraints the solver
 * should move every variable directly to its desired position.
 */
static void test_feasible_desired_positions()
{
    printf("Test: feasible desired positions are fully achieved... ");

    // desired positions satisfy the gap=2 constraint (gap=5 > 2)
    Variables vars;
    vars.push_back(new Variable(Initial(0.0), Desired(0.0)));
    vars.push_back(new Variable(Initial(7.0), Desired(5.0)));

    Constraints cs;
    cs.push_back(new Constraint(vars[0], vars[1], 2.0));

    Project proj(vars, cs);
    proj.solve();

    // Both variables should reach their desired positions
    assert(approxEq(vars[0]->getPosition(), 0.0));
    assert(approxEq(vars[1]->getPosition(), 5.0));
    checkConstraintsSatisfied(vars, cs);

    for_each(vars.begin(), vars.end(), delete_object());
    for_each(cs.begin(),   cs.end(),   delete_object());
    printf("PASS\n");
}

/*
 * Test 5: Weighted projection — heavier variable displaces less.
 *
 *   initial:  x_0 = 0,  x_1 = 6
 *   desired:  x_0 = 0,  x_1 = 0   (desired gap = 0 < required gap = 4)
 *   weights:  w_0 = 1,  w_1 = 4
 *
 * Optimal at constraint boundary (x_1 = x_0 + 4):
 *   minimise w_0 * x_0^2 + w_1 * (x_0+4)^2
 *   d/dx_0: 2 x_0 + 8(x_0+4) = 0  =>  10 x_0 = -32  =>  x_0 = -3.2, x_1 = 0.8
 *
 * The heavier variable (var 1) ends up closer to its desired position 0.
 */
static void test_weighted_projection()
{
    printf("Test: heavier variable displaces less from its desired position... ");

    Variables vars;
    vars.push_back(new Variable(Initial(0.0), Desired(0.0), Weight(1.0)));
    vars.push_back(new Variable(Initial(6.0), Desired(0.0), Weight(4.0)));

    Constraints cs;
    cs.push_back(new Constraint(vars[0], vars[1], 4.0));

    Project proj(vars, cs);
    proj.solve();

    checkConstraintsSatisfied(vars, cs);
    assert(approxEq(vars[0]->getPosition(), -3.2));
    assert(approxEq(vars[1]->getPosition(),  0.8));

    // Heavier variable must be closer to its desired position
    assert(std::fabs(vars[1]->getPosition() - vars[1]->getDesiredPosition()) <
           std::fabs(vars[0]->getPosition() - vars[0]->getDesiredPosition()));

    for_each(vars.begin(), vars.end(), delete_object());
    for_each(cs.begin(),   cs.end(),   delete_object());
    printf("PASS\n");
}

int main()
{
    test_unconstrained_at_desired();
    test_active_constraint();
    test_all_constraints_satisfied();
    test_feasible_desired_positions();
    test_weighted_projection();
    printf("All libproject validation tests passed.\n");
    return 0;
}
