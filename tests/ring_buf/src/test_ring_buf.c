/*
 * Ring Buffer Module - Homework Test Skeleton
 *
 * test_fresh_state is provided as a worked example. Fill in the remaining
 * 7 ZTEST bodies according to TEST_SPEC.md. Stubs call ztest_test_skip()
 * so the binary builds and runs cleanly before each test is implemented.
 *
 * Run:
 *   west twister -T tests/ring_buf -p native_sim
 */

#include <zephyr/ztest.h>
#include <errno.h>

#include "ring_buf.h"

/*
 * Shared before hook: every suite reinitialises the ring buffer with a
 * capacity of 4 so tests start from a clean, known state. Capacity 4 is
 * enough to exercise FIFO order (push 1, 2, 3) and overflow (full at 4).
 */
static void before(void *f)
{
	ARG_UNUSED(f);
	rb_init(4);
}

/*
 * ============================================================================
 * Test Suite: ring_buf_init
 *
 * Initial state and re-initialization behaviour.
 * ============================================================================
 */
ZTEST_SUITE(ring_buf_init, NULL, NULL, before, NULL, NULL);

/* PROVIDED — study this test before writing the rest. */
ZTEST(ring_buf_init, test_fresh_state)
{
	zassert_true(rb_is_empty(), "Fresh buffer must be empty");
	zassert_equal(rb_count(), 0, "Fresh buffer count must be 0");
}

ZTEST(ring_buf_init, test_reinit_clears_state)
{
	/* TODO(l8-task1): Push a value, call rb_init(4) again, then
	 * verify the buffer is empty and count is 0.
	 * See TEST_SPEC.md "Suite ring_buf_init" #2.
	 */
	int ret = rb_push(99);
        zassert_equal(ret, 0, "The first push is succeed! (%d)", ret);
	zassert_false(rb_is_empty(), "The buffer must not be empty after the first push of 99");

	/* Initialize the buffer */
	rb_init(4);

	zassert_true(rb_is_empty(), "Fresh buffer must be empty");
	zassert_equal(rb_count(), 0, "Fresh buffer count must be 0");
}

/*
 * ============================================================================
 * Test Suite: ring_buf_push_pop
 *
 * Single push/pop round-trip, FIFO order, full error path.
 * ============================================================================
 */
ZTEST_SUITE(ring_buf_push_pop, NULL, NULL, before, NULL, NULL);

ZTEST(ring_buf_push_pop, test_single_push_pop)
{
	/* TODO(l8-task1): rb_push(42), rb_pop(&v) -> v == 42, buffer empty after.
	 * See TEST_SPEC.md "Suite ring_buf_push_pop" #1.
	 */
	int input_value = 42;
        int output_value = 0;
        int ret;

	/* Write */
	ret = rb_push(input_value);
	zassert_equal(ret, 0, "The push is correctly achieved (%d)", ret);
	
	/* Pop */ 
        ret = rb_pop(&output_value); 
        zassert_equal(ret, 0, "The pop is succeed (%d)", ret); 
        zassert_equal(output_value, input_value, "Both are identique (%d) - (%d)", output_value, input_value); 
        zassert_true(rb_is_empty(), "The buffer is empty after the pop");
}

ZTEST(ring_buf_push_pop, test_fifo_order)
{
	/* TODO(l8-task1): rb_push(1), rb_push(2), rb_push(3); pop three times
	 * and verify the values come out as 1, 2, 3 in that order.
	 * See TEST_SPEC.md "Suite ring_buf_push_pop" #2.
	 */
	 int output_value;
	 int ret;
	 /* Push three values sequentially */
	 rb_push(1);
	 rb_push(2);
	 rb_push(3);
	 
	 /* Pop 1 */
	 ret = rb_pop(&output_value); 
	 zassert_equal(ret, 0, "The pop is succeed");
	 zassert_equal(output_value, 1, "expected %d", output_value);
	 
	 /* Pop 2 */
	 ret = rb_pop(&output_value); 
	 zassert_equal(ret, 0, "The pop is succeed");
	 zassert_equal(output_value, 2, "expected %d", output_value);
	 
	 /* Pop 1 */
	 ret = rb_pop(&output_value); 
	 zassert_equal(ret, 0, "The pop is succeed");
	 zassert_equal(output_value, 3, "expected %d", output_value);
	 /* Test an empty buffer*/
	 zassert_true(rb_is_empty(), "The buffer is empty after all pop!");
	
}

ZTEST(ring_buf_push_pop, test_push_full_returns_enospc)
{
	/* TODO(l8-task1): Fill the buffer to its capacity of 4, then push
	 * one more value -> -ENOSPC.
	 * See TEST_SPEC.md "Suite ring_buf_push_pop" #3.
	 */
	int ret = 0;
	/* Push three values sequentially */
	rb_push(1);
	rb_push(2);
	rb_push(3);
	rb_push(4);
	zassert_true(rb_is_full(), "The buffer reached its full size");
	
	/* Insert the fifth */
	ret = rb_push(5);
	zassert_equal(ret, -ENOSPC, "Enable to push the fifth element -ENOSPC");
	zassert_equal(rb_count(), 4, "The full capacity is reached");
}

/*
 * ============================================================================
 * Test Suite: ring_buf_boundaries
 *
 * Peek semantics and NULL-pointer boundary conditions.
 * ============================================================================
 */
ZTEST_SUITE(ring_buf_boundaries, NULL, NULL, before, NULL, NULL);

ZTEST(ring_buf_boundaries, test_peek_does_not_consume)
{
	/* TODO(l8-task1): rb_push(7); rb_peek(&v) -> v == 7; rb_peek(&v) again
	 * -> v == 7; rb_count() still == 1.
	 * See TEST_SPEC.md "Suite ring_buf_boundaries" #1.
	 */
	 int ret;
	 int peek_value = 0;
	 /* Push the 7 */
	 rb_push(7);
	 
	 /* Peek operation */
	 ret = rb_peek(&peek_value);
	 zassert_equal(ret, 0, "The peek operation is succeed (%d)", ret);
	 zassert_equal(peek_value, 7, "The peek value is (%d) - 7", peek_value);
	 
	 /* The second peek */
	 peek_value = 0;
	 ret = rb_peek(&peek_value);
	 zassert_equal(ret, 0, "The second peek operation is succeed (%d)", ret);
	 zassert_equal(rb_count(), 1, "The capacity is always one after the second peek %d", peek_value);
}

ZTEST(ring_buf_boundaries, test_pop_null_returns_einval)
{
	/* TODO(l8-task1): rb_pop(NULL) -> -EINVAL.
	 * See TEST_SPEC.md "Suite ring_buf_boundaries" #2.
	 */
	 int ret;
	 ret = rb_pop(NULL);
	 zassert_equal(ret, -EINVAL, "The pop return -EINVAL");
}

ZTEST(ring_buf_boundaries, test_is_full_after_fill)
{
	/* TODO(l8-task1): push 4 values -> rb_is_full() == true, rb_count() == 4.
	 * See TEST_SPEC.md "Suite ring_buf_boundaries" #3.
	 */
	int ret;
	for (int i = 0; i < 4; i++) 
	{
	    ret = rb_push((i+1));
	    zassert_equal(ret, 0, "The %dth push is succeed");
	}
	zassert_true(rb_is_full(), "The buffer is full");
	zassert_equal(rb_count(), 4, "The full capacity is reached");
}

