/*
 * vpsc_validate.cpp - Independent validation tests for libvpsc.
 *
 * libvpsc solves: minimize sum_i w_i * (x_i - d_i)^2
 *                 subject to: x_right - x_left >= gap  for all constraints
 *
 * These tests verify the solver produces mathematically correct results by:
 * 1. Checking that unconstrained variables reach their desired positions
 * 2. Checking analytically computed expected positions for simple cases
 * 3. Checking that all constraints are satisfied after solving
 * 4. Checking that symmetric configurations produce symmetric solutions
 *
 * All tests use IncSolver, which is the preferred interface and correctly
 * handles both inequality and equality constraints.
 */

#include <libvpsc/variable.h>
#include <libvpsc/constraint.h>
#include <libvpsc/solve_VPSC.h>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace vpsc;

static const double EPS = 1e-6;

static bool approxEq(double a, double b)
{
    return std::fabs(a - b) < EPS;
}

// Verify all constraints are satisfied: x_right - x_left >= gap
static void checkConstraintsSatisfied(const Variables& vars,
                                      const Constraints& cs)
{
    for (const Constraint *c : cs) {
        double diff = c->right->finalPosition - c->left->finalPosition;
        assert(diff >= c->gap - EPS);
    }
    (void)vars;
}

/*
 * Test 1: Unconstrained case.
 * With no constraints, every variable should settle exactly at its
 * desired position (the quadratic objective is minimised individually).
 */
static void test_unconstrained()
{
    printf("Test: unconstrained variables settle at desired positions... ");

    Variables vars;
    vars.push_back(new Variable(0,  1.0, 1.0));
    vars.push_back(new Variable(1,  5.0, 1.0));
    vars.push_back(new Variable(2, -3.0, 1.0));
    vars.push_back(new Variable(3,  0.0, 2.0));   // different weight

    Constraints cs;   // empty

    IncSolver solver(vars, cs);
    solver.solve();

    assert(approxEq(vars[0]->finalPosition,  1.0));
    assert(approxEq(vars[1]->finalPosition,  5.0));
    assert(approxEq(vars[2]->finalPosition, -3.0));
    assert(approxEq(vars[3]->finalPosition,  0.0));

    for (Variable *v : vars) delete v;
    printf("PASS\n");
}

/*
 * Test 2: Two variables with one active constraint.
 *
 * Variables: d_0 = 2, d_1 = 3, w_0 = w_1 = 1
 * Constraint: x_1 - x_0 >= 4  (desired gap = 1, required gap = 4, so active)
 *
 * Optimal solution (constraint active at boundary):
 *   minimise (x_0-2)^2 + (x_0+4-3)^2 = (x_0-2)^2 + (x_0+1)^2
 *   d/dx_0: 2(x_0-2) + 2(x_0+1) = 0  =>  x_0 = 0.5, x_1 = 4.5
 */
static void test_active_constraint()
{
    printf("Test: two variables with one active constraint... ");

    Variables vars;
    vars.push_back(new Variable(0, 2.0, 1.0));
    vars.push_back(new Variable(1, 3.0, 1.0));

    Constraints cs;
    cs.push_back(new Constraint(vars[0], vars[1], 4.0));

    IncSolver solver(vars, cs);
    solver.solve();

    checkConstraintsSatisfied(vars, cs);
    assert(approxEq(vars[0]->finalPosition, 0.5));
    assert(approxEq(vars[1]->finalPosition, 4.5));

    for (Constraint *c : cs) delete c;
    for (Variable *v : vars) delete v;
    printf("PASS\n");
}

/*
 * Test 3: Symmetric chain of constraints.
 *
 * 5 variables all desired at 0 with chain constraints x_{i+1} - x_i >= 1.
 * By symmetry every constraint is active: x_i = x_0 + i.
 *
 *   minimise sum_{i=0}^{4} (x_0 + i)^2 = 5 x_0^2 + 20 x_0 + 30
 *   d/dx_0 = 10 x_0 + 20 = 0  =>  x_0 = -2
 *
 * Expected positions: -2, -1, 0, 1, 2
 */
static void test_chain_constraints()
{
    printf("Test: symmetric chain constraints produce centred positions... ");

    const int n = 5;
    Variables vars;
    for (int i = 0; i < n; ++i)
        vars.push_back(new Variable(i, 0.0, 1.0));

    Constraints cs;
    for (int i = 0; i < n - 1; ++i)
        cs.push_back(new Constraint(vars[i], vars[i + 1], 1.0));

    IncSolver solver(vars, cs);
    solver.solve();

    checkConstraintsSatisfied(vars, cs);

    double expected[] = { -2.0, -1.0, 0.0, 1.0, 2.0 };
    for (int i = 0; i < n; ++i)
        assert(approxEq(vars[i]->finalPosition, expected[i]));

    for (Constraint *c : cs) delete c;
    for (Variable *v : vars) delete v;
    printf("PASS\n");
}

/*
 * Test 4: All constraints satisfied for a general constraint graph.
 * Uses a graph with both chain and shortcut constraints.
 */
static void test_all_constraints_satisfied()
{
    printf("Test: all constraints satisfied for general constraint graph... ");

    Variables vars;
    vars.push_back(new Variable(0, 10.0, 1.0));
    vars.push_back(new Variable(1,  1.0, 1.0));
    vars.push_back(new Variable(2,  5.0, 1.0));
    vars.push_back(new Variable(3,  8.0, 1.0));
    vars.push_back(new Variable(4,  3.0, 1.0));

    Constraints cs;
    cs.push_back(new Constraint(vars[0], vars[1], 2.0));
    cs.push_back(new Constraint(vars[1], vars[2], 2.0));
    cs.push_back(new Constraint(vars[2], vars[3], 2.0));
    cs.push_back(new Constraint(vars[0], vars[4], 1.0));
    cs.push_back(new Constraint(vars[4], vars[3], 1.0));

    IncSolver solver(vars, cs);
    solver.solve();

    checkConstraintsSatisfied(vars, cs);

    for (Constraint *c : cs) delete c;
    for (Variable *v : vars) delete v;
    printf("PASS\n");
}

/*
 * Test 5: Equality constraint — exact separation.
 *
 * Variables: d_0 = 0, d_1 = 10, w_0 = w_1 = 1
 * Constraint: x_1 - x_0 == 5 (equality)
 *
 * Optimal solution:
 *   minimise x_0^2 + (x_0+5-10)^2 = x_0^2 + (x_0-5)^2
 *   d/dx_0: 2 x_0 + 2(x_0-5) = 0  =>  x_0 = 2.5, x_1 = 7.5
 */
static void test_equality_constraint()
{
    printf("Test: equality constraint gives exact separation... ");

    Variables vars;
    vars.push_back(new Variable(0,  0.0, 1.0));
    vars.push_back(new Variable(1, 10.0, 1.0));

    Constraints cs;
    cs.push_back(new Constraint(vars[0], vars[1], 5.0, /* equality = */ true));

    IncSolver solver(vars, cs);
    solver.solve();

    // Constraint must be exactly satisfied
    double diff = vars[1]->finalPosition - vars[0]->finalPosition;
    assert(approxEq(diff, 5.0));
    assert(approxEq(vars[0]->finalPosition, 2.5));
    assert(approxEq(vars[1]->finalPosition, 7.5));

    for (Constraint *c : cs) delete c;
    for (Variable *v : vars) delete v;
    printf("PASS\n");
}

/*
 * Test 6: Variable weight influences the solution.
 *
 * Two variables, one active constraint.
 *   d_0 = 0, w_0 = 1
 *   d_1 = 0, w_1 = 3   (heavier weight — resists displacement more)
 *   Constraint: x_1 - x_0 >= 4
 *
 * Optimal (constraint active):
 *   minimise w_0*(x_0)^2 + w_1*(x_0+4)^2
 *   d/dx_0: 2 x_0 + 6(x_0+4) = 0  =>  8 x_0 = -24  =>  x_0 = -3, x_1 = 1
 *
 * The heavier variable (var 1) stays closer to 0 than the lighter one.
 */
static void test_weighted_variables()
{
    printf("Test: heavier variable displaces less from its desired position... ");

    Variables vars;
    vars.push_back(new Variable(0, 0.0, 1.0));
    vars.push_back(new Variable(1, 0.0, 3.0));

    Constraints cs;
    cs.push_back(new Constraint(vars[0], vars[1], 4.0));

    IncSolver solver(vars, cs);
    solver.solve();

    checkConstraintsSatisfied(vars, cs);
    assert(approxEq(vars[0]->finalPosition, -3.0));
    assert(approxEq(vars[1]->finalPosition,  1.0));

    // The heavier variable is closer to its desired position (0)
    assert(std::fabs(vars[1]->finalPosition - vars[1]->desiredPosition) <
           std::fabs(vars[0]->finalPosition - vars[0]->desiredPosition));

    for (Constraint *c : cs) delete c;
    for (Variable *v : vars) delete v;
    printf("PASS\n");
}

/*
 * Test 7: Already-feasible constraints are not perturbed.
 *
 * If the desired positions already satisfy all constraints, the solver
 * should leave all variables at their desired positions.
 */
static void test_feasible_unchanged()
{
    printf("Test: already feasible configuration remains unchanged... ");

    Variables vars;
    vars.push_back(new Variable(0,  0.0, 1.0));
    vars.push_back(new Variable(1,  5.0, 1.0));
    vars.push_back(new Variable(2, 12.0, 1.0));

    // All constraints already satisfied with a surplus
    Constraints cs;
    cs.push_back(new Constraint(vars[0], vars[1], 3.0));  // gap=5 > 3
    cs.push_back(new Constraint(vars[1], vars[2], 3.0));  // gap=7 > 3

    IncSolver solver(vars, cs);
    solver.solve();

    // Variables must remain at their desired positions
    assert(approxEq(vars[0]->finalPosition,  0.0));
    assert(approxEq(vars[1]->finalPosition,  5.0));
    assert(approxEq(vars[2]->finalPosition, 12.0));

    for (Constraint *c : cs) delete c;
    for (Variable *v : vars) delete v;
    printf("PASS\n");
}

int main()
{
    test_unconstrained();
    test_active_constraint();
    test_chain_constraints();
    test_all_constraints_satisfied();
    test_equality_constraint();
    test_weighted_variables();
    test_feasible_unchanged();
    printf("All libvpsc validation tests passed.\n");
    return 0;
}
